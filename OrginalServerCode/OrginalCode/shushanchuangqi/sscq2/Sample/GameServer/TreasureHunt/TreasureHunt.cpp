#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "Tokenizer.h"
#include "ItemProt.h"
#include "Loot.h"
#include "SysMsgDefine.h"
#include "Monster.h"
#include "FighterManager.h"
#include "TreasureHunt.h"
#include "TreasureHuntMgr.h"
#include "TreasureHuntProtS.h"
#include "HeroFighter.h"

#include "GUIDMgr.h"

//加载DB
void CTreasureHunt::LoadFromDB(
        UINT8 byCopyID,
        UINT8 byStatus,
        UINT32 dwBossCurHP,
        UINT32 dwLastTime, 
        UINT32 dwTime,
        UINT32 dwNum,
        string strAward
        )
{
    SetTHCopyID(byCopyID);
    SetTHStatus(byStatus);
    SetTHLastTime(dwLastTime);
    SetTHTotalTime(dwTime);
    SetTHTotalNum(dwNum);


    Tokenizer tk(strAward, "|");
    for (size_t i=0; i<tk.size(); i++)
    {
        string strAwardA = tk[i].c_str();

        Tokenizer tkA(strAwardA, ',');
        if (2 != tkA.size())
            continue;

        STHAwardInfo sTHAwardInfo;
        sTHAwardInfo.wItemID = atoi(tkA[0].c_str());
        sTHAwardInfo.dwCount = atoi(tkA[1].c_str());

        AddTHAward(sTHAwardInfo);
    }

    if (eTHProgress == GetTHStatus())
    {
        _bOffLineHandleMark = true;
        OffLineTH(dwBossCurHP);
    }
}


//请求寻宝信息
bool CTreasureHunt::ReqTHInfo(UINT8& byCopyID, ETHStatus& eTHStatus, UINT8& byKillNum, UINT8& byCurrentID)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    byCurrentID = rCGameVar.GetVar(NVarDefine::ePlayerTHCond);
    UINT64 qwKillNum = rCGameVar.GetVar(NVarDefine::ePlayerTHKillNum);
    UINT8 byNum = 0;
    if (MAX_KILLNUM > qwKillNum)
         byNum = MAX_KILLNUM - qwKillNum;
    
    byCopyID = _byCopyID;
    eTHStatus = ETHStatus(GetTHStatus());
    byKillNum = byNum;

    return true;
}

//请求寻宝开始
ETHOptResult CTreasureHunt::ReqTHStart(UINT8 byCopyID)
{
    if (0 == byCopyID)
        return eTHOptResultFailed;
    
    SSearchMapCFG* pSearchMapCFG = CTreasureHuntMgr::Instance().GetSearchMapCFG(byCopyID);
    if (!pSearchMapCFG)
        return eTHOptResultFailed;
    
    if (_rPlayer.GetLevel() < pSearchMapCFG->_Level)
        return eTHOptResultFailed;

    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT8 byCond = rCGameVar.GetVar(NVarDefine::ePlayerTHCond);
    if ((byCond + 1) < byCopyID)
        return eTHOptResultFailed;

    if (eTHNone != GetTHStatus())
        return eTHOptResultFailed;

    UINT64 qwKillNum = rCGameVar.GetVar(NVarDefine::ePlayerTHKillNum);
    if (qwKillNum >= MAX_KILLNUM)
        return eTHMaxKillNumDay;

    Tokenizer tk(pSearchMapCFG->_MonsterGroup, ";");
    for (size_t i=0; i<tk.size(); i++)
    {
        UINT32 dwMonsterGroupID = atoi(tk[i].c_str());
        if (0 == dwMonsterGroupID)
            return eTHOptResultFailed;

        TVecBattleFighterPtr vecBattleFighter;
        vector<TVecBattleFighterPtr> vecvecBattleFighter2;
        UINT64 qwDefenseID = GET_GUID(GUID_MONSTER);
        UINT64 qwMainMonsterID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwMonsterGroupID, qwDefenseID, vecBattleFighter);
        if(!qwMainMonsterID)
        {
            LOG_CRI << "Can't find Monster! GroupID: " << dwMonsterGroupID;
            return eTHOptResultFailed;
        }

        if (0 == vecvecBattleFighter2[0].size())
            return eTHOptResultFailed;

        _TVecBattleFighterVec.push_back(vecvecBattleFighter2[0]);
        _vecMonsterGroupID.push_back(dwMonsterGroupID);
        _vecMonsterID.push_back(qwMainMonsterID);
        _vecDefenseID.push_back(qwDefenseID);
    }

    UINT8 bySize = _TVecBattleFighterVec.size();
    if (0 == bySize)
        return eTHOptResultFailed;

    UINT32 dwMaxBossHP = 0;
    TVecBattleFighterPtr& vecBattleBoss = _TVecBattleFighterVec[bySize-1];
    for (size_t i=0; i<vecBattleBoss.size(); i++)
    {
        if (vecBattleBoss[i])
            dwMaxBossHP += vecBattleBoss[i]->GetHP();
    }

    //设置Boss最大血量
    SetTHBossMaxHP(dwMaxBossHP);

    //设置寻宝副本ID
    SetTHCopyID(byCopyID);

    //设置寻宝状态
    SetTHStatus(eTHProgress);

    //寻宝开始
    THNotify(eTHBegin);

    Update2DB(eOpAdd);

    return eTHOptResultSucc;
}

//请求寻宝立即完成
bool CTreasureHunt::ReqTHQuickFinish()
{
    if (eTHProgress != GetTHStatus())
        return false;

    SSearchMapCFG* pSearchMapCFG = CTreasureHuntMgr::Instance().GetSearchMapCFG(GetTHCopyID());
    if (!pSearchMapCFG)
        return false;

    CUser& rUser = _rPlayer.GetUser();
    if (!rUser.CanSubMoney(EMONEY_GOLD, pSearchMapCFG->_FinishCost))
        return false;

    rUser.SubMoney(EMONEY_GOLD, pSearchMapCFG->_FinishCost, NLogDataDefine::ItemTo_TreasureHunt);

    UINT32 dwSilverNum = 0;
    //UINT32 dwPexp = 0;
    UINT32 dwItemNum = 0;
    UINT32 dwXFCYNum = 0;
    TVecItemGenInfo vecItems;
    TVecResource vecRes;

    //奖励A
    LOOT.Roll(pSearchMapCFG->_TimeAward, vecItems, vecRes);
    for (size_t i=0; i<vecItems.size(); i++)
    {
        STHAwardInfo sTHAwardInfoA;
        sTHAwardInfoA.wItemID = vecItems[i].wItemID;
        sTHAwardInfoA.dwCount = vecItems[i].dwCount;
        AddTHAward(sTHAwardInfoA);

        if (vecItems[i].wItemID>=XFCY_A && vecItems[i].wItemID<=XFCY_D)
            dwXFCYNum += vecItems[i].dwCount;
        else
            dwItemNum += vecItems[i].dwCount;
    }

    for (size_t i=0; i<vecRes.size(); i++)
    {
        STHAwardInfo sTHAwardInfoA;
        sTHAwardInfoA.wItemID = vecRes[i]._eRes;
        sTHAwardInfoA.dwCount = vecRes[i]._dwValue;
        AddTHAward(sTHAwardInfoA);

        if (EMONEY_SILVER == vecRes[i]._eRes)
            dwSilverNum += vecRes[i]._dwValue;
        //else if (EMONEY_PEXP == vecRes[i]._eRes)
            //dwPexp += vecRes[i]._dwValue;
    }

    //奖励B
    STHAwardInfo sTHAwardInfoB;
    sTHAwardInfoB.wItemID = EMONEY_SILVER;
    //sTHAwardInfoB.dwCount = pSearchMapCFG->_Money + pSearchMapCFG->_Money * pSearchMapCFG->_FinishAward / 10000;
    sTHAwardInfoB.dwCount = pSearchMapCFG->_Money * pSearchMapCFG->_FinishAward / 10000;
    AddTHAward(sTHAwardInfoB);
    dwSilverNum += sTHAwardInfoB.dwCount;

    //奖励C
    /*STHAwardInfo sTHAwardInfoC;
    sTHAwardInfoC.wItemID = EMONEY_PEXP;
    sTHAwardInfoC.dwCount = pSearchMapCFG->_Pexp + pSearchMapCFG->_Pexp * pSearchMapCFG->_FinishAward / 10000;
    AddTHAward(sTHAwardInfoC);
    dwPexp += sTHAwardInfoC.dwCount;*/

    if (dwSilverNum > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeC, dwSilverNum, 0, 0));
    /*if (dwPexp > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeD, dwPexp, 0, 0));*/
    if (dwItemNum > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeE, dwItemNum, 0, 0));
    if (dwXFCYNum > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeJ, dwXFCYNum, 0, 0));

    AddTHTotalNum(1);
    AddTHTotalTime(5);

    //本轮战斗结果通知
    {
        STHBattleResult sTHBattleResult;
        sTHBattleResult.byCopyID = _byCopyID;
        sTHBattleResult.dwTotalTimes = _dwTotalTime;
        sTHBattleResult.dwCurBossHP = 0;
        sTHBattleResult.dwCurSilverNUm = dwSilverNum;
        //sTHBattleResult.dwCurPexpNum = dwPexp;
        sTHBattleResult.dwCurItemNum = dwItemNum;
        sTHBattleResult.dwCurXFCYNum = dwXFCYNum;

        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THBattleResultNotify(sTHBattleResult));
    }

    CGameVar& rCGameVar = rUser.GetVars();
    rCGameVar.AddVar(NVarDefine::ePlayerTHKillNum, 1);

    if (GetTHCopyID() > rCGameVar.GetVar(NVarDefine::ePlayerTHCond))
        rCGameVar.AddVar(NVarDefine::ePlayerTHCond, 1);
    
    THNotify(eTHEnd);
    SetTHStatus(eTHWaitGetAward);
    CleanTHBaseInfo();
    Update2DB(eOpUpdate);

    //事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(_byCopyID);
        vecParam.push_back(1);

        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_TreasureSuccess, vecParam);
    }

    rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_FinishTreasureHunt); 

    return true;
}

//寻宝定时器
bool CTreasureHunt::THTimerCheck(UINT32 dwNow)
{
    if (_bOffLineHandleMark || eTHProgress != GetTHStatus())
        return false;

    UINT32 dwTempTime = 0;
    if (dwNow > GetTHLastTime())
        dwTempTime = dwNow - GetTHLastTime();

    if (dwTempTime >= TH_TIMER)
    {
        THBattlePrepare();
        SetTHLastTime(dwNow);
    }

    return true;
}

//寻宝战斗准备
bool CTreasureHunt::THBattlePrepare()
{
    if (eTHProgress != GetTHStatus())
        return false;

    UINT32 byTotalNum = GetTHTotalNum();
    UINT8 byCurIndex = byTotalNum % _vecMonsterGroupID.size();

    UINT8 byLen = byCurIndex + 1;
    if (byLen > _vecMonsterGroupID.size()
            || byLen > _vecMonsterID.size()
            || byLen > _vecDefenseID.size()
            || byLen > _TVecBattleFighterVec.size())
        return false;

    UINT32 dwMonsterGroupID = _vecMonsterGroupID[byCurIndex];
    UINT64 qwMainMonsterID = _vecMonsterID[byCurIndex];
    UINT64 qwDefenseID = _vecDefenseID.size();
    TVecBattleFighterPtr& vecBattleFighter2 = _TVecBattleFighterVec[byCurIndex];

    _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeA, dwMonsterGroupID, 0, 0));

    THBattle(dwMonsterGroupID, qwMainMonsterID, qwDefenseID, vecBattleFighter2, byCurIndex);

    return true;
}

//寻宝战斗
bool CTreasureHunt::THBattle(UINT32 dwMonsterGroupID, UINT64 qwMainMonsterID, UINT64 qwDefenseID, TVecBattleFighterPtr& vecBattleFighter2, UINT8 byCurIndex)
{
    if (0 == vecBattleFighter2.size())
        return false;

    UINT8 bySize = _TVecBattleFighterVec.size();
    if (0 == bySize)
        return false;

    bool bBossMark = false;
    if (bySize == byCurIndex + 1)
        bBossMark = true;

    //设置战斗类型
    _rPlayer.SetBattleType(ETreasureHunt);

    //战斗前的Monster血量
    UINT32 dwOldMonsterHP = 0;
    TVecBattleFighterPtr& vecBattleMonster = _TVecBattleFighterVec[byCurIndex];
    for (size_t i=0; i<vecBattleMonster.size(); i++)
    {
        if (vecBattleMonster[i])
            dwOldMonsterHP += vecBattleMonster[i]->GetHP();
    }

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    TVecBattleFighterPtr vecBattleFighter;
    _rPlayer.GetBattleFighterList(vecBattleFighter);

    IBattleFighterPtr pScene;
    pScene = CMonster::GetSceneFighter(dwMonsterGroupID);
    if (!pScene)
        pScene = _rPlayer.GetSceneFighter();

    pBS->PutFighters(0, _rPlayer.GetMainFighter()->GetInstID(), _rPlayer.GetLevel(), vecBattleFighter, _rPlayer.GetRoleID());
    pBS->PutFighters(1, qwMainMonsterID, CMonster::GetMonsterLevelByGroupID(dwMonsterGroupID), vecBattleFighter2, qwDefenseID, false);
    pBS->PutScene(pScene);
    pBS->Start(EBTMonster);

    _rPlayer.SetBattleType(EBTINVALID);

    //战斗后的Monster血量
    UINT32 dwHP = 0;
    UINT32 dwNewMonsterHP = 0;
    if (bBossMark)
    {
        for (size_t i=0; i<vecBattleMonster.size(); i++)
        {
            if (vecBattleMonster[i])
                dwNewMonsterHP += vecBattleMonster[i]->GetHP();
        }

        if (dwOldMonsterHP > dwNewMonsterHP)
            dwHP = dwOldMonsterHP - dwNewMonsterHP;
    }

    bool bWinMark = false;
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    if(pBS->GetFinalWinner() == EBResultAttackWin)
    {
        CMonster::DropToPlayer(dwMonsterGroupID, vecItems, vecRes);

        if (bBossMark)
        {
            SSearchMapCFG* pSearchMapCFG = CTreasureHuntMgr::Instance().GetSearchMapCFG(_byCopyID);
            if (!pSearchMapCFG)
                return false;

            //通关奖励
            if (_dwTotalTime <= pSearchMapCFG->_ClearTime)
            {
                UINT32 dwDropId = pSearchMapCFG->_TimeAward;
                LOOT.Roll(dwDropId, vecItems, vecRes);
            }

            bWinMark = true;
            _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeF, dwMonsterGroupID, dwHP, 0));
        }
        else
        {
            for (size_t i=0; i<vecBattleMonster.size(); i++)
            {
                if (vecBattleMonster[i])
                    vecBattleMonster[i]->SetHP(dwOldMonsterHP);
            }

            _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeB, dwMonsterGroupID, 0, 0));
        }
    }
    else
    {
        _rPlayer.RegenAllHP();

        if (bBossMark)
            _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeG, dwMonsterGroupID, dwHP, pBS->GetBattleID()));
    }

    //掉落日志通知
    UINT32 dwSilverNum = 0;
    //UINT32 dwPexp = 0;
    UINT32 dwItemNum = 0;
    UINT32 dwXFCYNum = 0;

    for (size_t i=0; i<vecItems.size(); i++)
    {
        STHAwardInfo sTHAwardInfo;
        sTHAwardInfo.wItemID = vecItems[i].wItemID;
        sTHAwardInfo.dwCount = vecItems[i].dwCount;
        AddTHAward(sTHAwardInfo);
    
        if (vecItems[i].wItemID>=XFCY_A && vecItems[i].wItemID<=XFCY_D)
            dwXFCYNum += vecItems[i].dwCount;
        else
            dwItemNum += vecItems[i].dwCount;
    }

    for (size_t i=0; i<vecRes.size(); i++)
    {
        STHAwardInfo sTHAwardInfo;
        sTHAwardInfo.wItemID = vecRes[i]._eRes;
        sTHAwardInfo.dwCount = vecRes[i]._dwValue;
        AddTHAward(sTHAwardInfo);

        if (EMONEY_SILVER == vecRes[i]._eRes)
            dwSilverNum += vecRes[i]._dwValue;
        //else if (EMONEY_PEXP == vecRes[i]._eRes)
            //dwPexp += vecRes[i]._dwValue;
    }

    if (dwSilverNum > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeC, dwSilverNum, 0, 0));
    /*if (dwPexp > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeD, dwPexp, 0, 0));*/
    if (dwItemNum > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeE, dwItemNum, 0, 0));
    if (dwXFCYNum > 0)
        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeJ, dwXFCYNum, 0, 0));
    
    UINT32 dwNewBossHP = 0;
    TVecBattleFighterPtr& vecBattleBoss = _TVecBattleFighterVec[bySize-1];
    for (size_t i=0; i<vecBattleBoss.size(); i++)
    {
        if (vecBattleBoss[i])
            dwNewBossHP += vecBattleBoss[i]->GetHP();
    }

    AddTHTotalNum(1);
    AddTHTotalTime(5);

    //本轮战斗结果通知
    {
        STHBattleResult sTHBattleResult;
        sTHBattleResult.byCopyID = _byCopyID;
        sTHBattleResult.dwTotalTimes = _dwTotalTime;
        sTHBattleResult.dwCurBossHP = dwNewBossHP;
        sTHBattleResult.dwCurSilverNUm = dwSilverNum;
        //sTHBattleResult.dwCurPexpNum = dwPexp;
        sTHBattleResult.dwCurItemNum = dwItemNum;
        sTHBattleResult.dwCurXFCYNum = dwXFCYNum;

        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THBattleResultNotify(sTHBattleResult));
    }

    //寻宝结束
    if (bWinMark)
    {
        THNotify(eTHEnd);
        SetTHStatus(eTHWaitGetAward);
        CleanTHBaseInfo();

        CUser& rUser = _rPlayer.GetUser();
        CGameVar& rCGameVar = rUser.GetVars();
        rCGameVar.AddVar(NVarDefine::ePlayerTHKillNum, 1);

        if (GetTHCopyID() > rCGameVar.GetVar(NVarDefine::ePlayerTHCond))
            rCGameVar.AddVar(NVarDefine::ePlayerTHCond, 1);

        //事件
        {
            TVecINT32 vecParam;
            vecParam.push_back(_byCopyID);
            vecParam.push_back(1);

            CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
            if(pEventMgr)
                pEventMgr->OnEvent(eEventType_TreasureSuccess, vecParam);
        }
        rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_FinishTreasureHunt);
    }

    Update2DB(eOpUpdate);

    return true;
}

//放弃寻宝
bool CTreasureHunt::ReqGiveUpTH()
{
    PlayerLeaveCleanTHInfo();

    return true;
}

//使用Buff(天罡神力/驹过隙/偷梁换柱)
bool CTreasureHunt::UseBuff(UINT8 byBuffID)
{
    if (eTHProgress != GetTHStatus())
        return false;

    if (byBuffID != BUFF_TGSL 
            && byBuffID != BUFF_BJGX
            && byBuffID != BUFF_TLHZ)
        return false;

    UINT64 qwValue = 0;
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    if (BUFF_TGSL == byBuffID)
        qwValue = rCGameVar.GetVar(NVarDefine::ePlayerTGSL);
    else if (BUFF_BJGX == byBuffID)
        qwValue = rCGameVar.GetVar(NVarDefine::ePlayerBJGX);
    else
        qwValue = rCGameVar.GetVar(NVarDefine::ePlayerTLHZ);

    UINT64 qwBuffNum = GET_BIT_32(qwValue, BIT_MARKA);
    UINT64 qwBuffTime = GET_BIT_32(qwValue, BIT_MARKB);

    SSearchBuffCFG* pSearchBuffCFG = CTreasureHuntMgr::Instance().GetSearchBuffCFG(byBuffID);
    if (!pSearchBuffCFG)
        return false;

    UINT64 qwNowTime = time(NULL);
    if (qwNowTime <= qwBuffTime)
        return false;

    if (qwNowTime-qwBuffTime <= pSearchBuffCFG->_BuffCD)
        return false;

    if (qwBuffNum >= pSearchBuffCFG->_DailyTimes)
        return false;

    switch(byBuffID)
    {
        case BUFF_TGSL:
            {
                TVecUINT32 vecParam;
                vecParam.push_back(pSearchBuffCFG->_Effect);
                vecParam.push_back(qwBuffNum+1);
                time_t now = Time::Now();
                UINT32 dwLastEnd = Time::TheDay(1, now) - time(NULL);
                _rPlayer.SetBuff(pSearchBuffCFG->_BuffID, vecParam, dwLastEnd);

                _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeH, BUFF_TGSL, 0, 0));
            }
            break;
        case BUFF_BJGX:
            {
                //直接对Boss造成一次伤害
                UINT8 bySize = _TVecBattleFighterVec.size();
                if (0 == bySize)
                    return false;

                //使用buff总共掉的血量
                UINT32 dwSubBossHP = 0;
                //剩余血量
                UINT32 dwTotalBossHP = 0;
                //参数
                UINT64 qwParamA = GetTHBossMaxHP();
                UINT64 qwParamB = 10000;
                UINT64 qwParamC = pSearchBuffCFG->_Effect;
                UINT64 qwParamD = SParamConfig::wSearchBuffEffect;
                UINT32 dwEffect = qwParamA / qwParamB * qwParamC + qwParamD;
                TVecBattleFighterPtr& vecBattleBoss = _TVecBattleFighterVec[bySize-1];
                for (size_t i=0; i<vecBattleBoss.size(); i++)
                {
                    if (vecBattleBoss[i])
                    {
                        UINT32 dwBossHP = 0;
                        if (vecBattleBoss[i]->GetHP() >= dwEffect)
                        {
                            dwBossHP = vecBattleBoss[i]->GetHP() - dwEffect;
                            dwSubBossHP += dwEffect;
                        }
                        else
                            dwSubBossHP += vecBattleBoss[i]->GetHP();

                        vecBattleBoss[i]->SetHP(dwBossHP);
                        dwTotalBossHP += dwBossHP;
                    }
                }

                _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeH, BUFF_BJGX, 0, 0));

                if (bySize > _vecMonsterGroupID.size())
                    return false;

                UINT32 dwMonsterGroupID = _vecMonsterGroupID[bySize-1];
                _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeI, dwMonsterGroupID, dwSubBossHP, 0));

                if (0 == dwTotalBossHP)
                {
                    TVecItemGenInfo vecItems;
                    TVecResource vecRes;

                    CMonster::DropToPlayer(dwMonsterGroupID, vecItems, vecRes);

                    SSearchMapCFG* pSearchMapCFG = CTreasureHuntMgr::Instance().GetSearchMapCFG(_byCopyID);
                    if (!pSearchMapCFG)
                        return false;

                    //通关奖励
                    if (_dwTotalTime <= pSearchMapCFG->_ClearTime)
                    {
                        UINT32 dwDropId = pSearchMapCFG->_TimeAward;
                        LOOT.Roll(dwDropId, vecItems, vecRes);
                    }

                    //掉落日志通知
                    UINT32 dwSilverNum = 0;
                    //UINT32 dwPexp = 0;
                    UINT32 dwItemNum = 0;
                    UINT32 dwXFCYNum = 0;

                    for (size_t i=0; i<vecItems.size(); i++)
                    {
                        STHAwardInfo sTHAwardInfo;
                        sTHAwardInfo.wItemID = vecItems[i].wItemID;
                        sTHAwardInfo.dwCount = vecItems[i].dwCount;
                        AddTHAward(sTHAwardInfo);

                        if (vecItems[i].wItemID>=XFCY_A && vecItems[i].wItemID<=XFCY_D)
                            dwXFCYNum += vecItems[i].dwCount;
                        else
                            dwItemNum += vecItems[i].dwCount;
                    }

                    for (size_t i=0; i<vecRes.size(); i++)
                    {
                        STHAwardInfo sTHAwardInfo;
                        sTHAwardInfo.wItemID = vecRes[i]._eRes;
                        sTHAwardInfo.dwCount = vecRes[i]._dwValue;
                        AddTHAward(sTHAwardInfo);

                        if (EMONEY_SILVER == vecRes[i]._eRes)
                            dwSilverNum += vecRes[i]._dwValue;
                        //else if (EMONEY_PEXP == vecRes[i]._eRes)
                            //dwPexp += vecRes[i]._dwValue;
                    }

                    if (dwSilverNum > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeC, dwSilverNum, 0, 0));
                    /*if (dwPexp > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeD, dwPexp, 0, 0));*/
                    if (dwItemNum > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeE, dwItemNum, 0, 0));
                    if (dwXFCYNum > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeJ, dwXFCYNum, 0, 0));

                    AddTHTotalNum(1);
                    AddTHTotalTime(5);

                    //本轮战斗结果通知
                    {
                        STHBattleResult sTHBattleResult;
                        sTHBattleResult.byCopyID = _byCopyID;
                        sTHBattleResult.dwTotalTimes = _dwTotalTime;
                        sTHBattleResult.dwCurBossHP = 0;
                        sTHBattleResult.dwCurSilverNUm = dwSilverNum;
                        //sTHBattleResult.dwCurPexpNum = dwPexp;
                        sTHBattleResult.dwCurItemNum = dwItemNum;
                        sTHBattleResult.dwCurXFCYNum = dwXFCYNum;

                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THBattleResultNotify(sTHBattleResult));
                    }

                    CUser& rUser = _rPlayer.GetUser();
                    CGameVar& rCGameVar = rUser.GetVars();
                    rCGameVar.AddVar(NVarDefine::ePlayerTHKillNum, 1);

                    if (GetTHCopyID() > rCGameVar.GetVar(NVarDefine::ePlayerTHCond))
                        rCGameVar.AddVar(NVarDefine::ePlayerTHCond, 1);
                    
                    THNotify(eTHEnd);
                    SetTHStatus(eTHWaitGetAward);
                    CleanTHBaseInfo();
                    Update2DB(eOpUpdate);

                    //事件
                    {
                        TVecINT32 vecParam;
                        vecParam.push_back(_byCopyID);
                        vecParam.push_back(1);

                        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
                        if(pEventMgr)
                            pEventMgr->OnEvent(eEventType_TreasureSuccess, vecParam);
                     }

                    rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_FinishTreasureHunt); 
                }
            }
            break;
        case BUFF_TLHZ:
            {
                TVecItemGenInfo vecItems;
                TVecResource vecRes;

                UINT32 dwDropId = pSearchBuffCFG->_Effect;
                LOOT.Roll(dwDropId, vecItems, vecRes);

                //掉落日志通知
                {
                    UINT32 dwSilverNum = 0;
                    //UINT32 dwPexp = 0;
                    UINT32 dwItemNum = 0;
                    UINT32 dwXFCYNum = 0;
                    TVecTHAwardInfo vecTHAwardInfo;

                    for (size_t i=0; i<vecItems.size(); i++)
                    {
                        STHAwardInfo sTHAwardInfo;
                        sTHAwardInfo.wItemID = vecItems[i].wItemID;
                        sTHAwardInfo.dwCount = vecItems[i].dwCount;
                        AddTHAward(sTHAwardInfo);
                        vecTHAwardInfo.push_back(sTHAwardInfo);

                        if (vecItems[i].wItemID>=XFCY_A && vecItems[i].wItemID<=XFCY_D)
                            dwXFCYNum += vecItems[i].dwCount;
                        else
                            dwItemNum += vecItems[i].dwCount;
                    }

                    for (size_t i=0; i<vecRes.size(); i++)
                    {
                        STHAwardInfo sTHAwardInfo;
                        sTHAwardInfo.wItemID = vecRes[i]._eRes;
                        sTHAwardInfo.dwCount = vecRes[i]._dwValue;
                        AddTHAward(sTHAwardInfo);
                        vecTHAwardInfo.push_back(sTHAwardInfo);

                        if (EMONEY_SILVER == vecRes[i]._eRes)
                            dwSilverNum += vecRes[i]._dwValue;
                        //else if (EMONEY_PEXP == vecRes[i]._eRes)
                            //dwPexp += vecRes[i]._dwValue;
                    }

                    _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeH, BUFF_TLHZ, 0, 0));

                    if (dwSilverNum > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeC, dwSilverNum, 0, 0));
                    /*if (dwPexp > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeD, dwPexp, 0, 0));*/
                    if (dwItemNum > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeE, dwItemNum, 0, 0));
                    if (dwXFCYNum > 0)
                        _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLogNotify(eTHLogTypeJ, dwXFCYNum, 0, 0));

                    _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THLootNotify(vecTHAwardInfo));
                }
            }
            break;
    }

    qwBuffNum++;
    qwValue = SET_BIT_32(qwValue, BIT_MARKA, qwBuffNum);
    qwValue = SET_BIT_32(qwValue, BIT_MARKB, qwNowTime);
    if (BUFF_TGSL == byBuffID)
        rCGameVar.SetVar(NVarDefine::ePlayerTGSL, qwValue);
    else if (BUFF_BJGX == byBuffID)
        rCGameVar.SetVar(NVarDefine::ePlayerBJGX, qwValue);
    else
        rCGameVar.SetVar(NVarDefine::ePlayerTLHZ, qwValue);

    //事件
    {
        TVecINT32 vecParam;
        vecParam.push_back(byBuffID);
        vecParam.push_back(1);

        CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
        if(pEventMgr)
            pEventMgr->OnEvent(eEventType_TreasureUseBuff, vecParam);
    }

    return true;
}

//添加寻宝奖励
bool CTreasureHunt::AddTHAward(STHAwardInfo sTHAwardInfo)
{
    MapTHAward::iterator iter = _MapTHAward.find(sTHAwardInfo.wItemID);
    if (iter != _MapTHAward.end())
        iter->second.dwCount += sTHAwardInfo.dwCount;
    else
        _MapTHAward.insert(std::make_pair(sTHAwardInfo.wItemID, sTHAwardInfo)); 

    return true;
}

//请求寻宝奖励信息
bool CTreasureHunt::ReqTHAwardInfo(UINT8& byCopyID, TVecTHAwardInfo& vecTHAwardInfo)
{
    byCopyID = GetTHCopyID();

    /*CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    byCurrentID = rCGameVar.GetVar(NVarDefine::ePlayerTHCond);*/

    MapTHAward::iterator iter = _MapTHAward.begin();
    for (; iter!=_MapTHAward.end(); iter++)
    {
        vecTHAwardInfo.push_back(iter->second);
    }

    return true;
}

//获取寻宝奖励
bool CTreasureHunt::GetTHAward()
{
    if (eTHWaitGetAward != GetTHStatus())
        return false;

    if (0 == _MapTHAward.size())
        return false;

    std::vector<SItemGenInfo> vecItems;
    MapTHAward::iterator iter = _MapTHAward.begin();
    for (; iter!=_MapTHAward.end(); iter++)
    {
        SItemGenInfo sItemGenInfo;
        sItemGenInfo.wItemID = iter->second.wItemID;
        sItemGenInfo.dwCount = iter->second.dwCount;
        sItemGenInfo.eBindType = eBindGet;
        vecItems.push_back(sItemGenInfo);
    }

    if (0 == vecItems.size())
        return false;

    CPack& oPack = _rPlayer.GetUser().GetPack();
    if(!oPack.CanAddItem(vecItems))
    {
        _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgStovePackageFull));
        return false;
    }
    else
    {
        oPack.AddItem(vecItems, NLogDataDefine::ItemFrom_TreasureHunt);
        CleanTHAwardInfo();
    }

    return true;
}

//寻宝开始/结束通知
bool CTreasureHunt::THNotify(ETHNotify eTHNotify)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwKillNum = rCGameVar.GetVar(NVarDefine::ePlayerTHKillNum);
    UINT64 qwBuffA = rCGameVar.GetVar(NVarDefine::ePlayerTGSL);
    UINT64 qwBuffB = rCGameVar.GetVar(NVarDefine::ePlayerBJGX);
    UINT64 qwBuffC = rCGameVar.GetVar(NVarDefine::ePlayerTLHZ);

    TVecTHBuffInfo vecTHBuffInfo;

    STHBuffInfo sTHBuffInfoA;
    sTHBuffInfoA.byBuffID = BUFF_TGSL;
    sTHBuffInfoA.byBuffNum = GET_BIT_32(qwBuffA, BIT_MARKA);
    sTHBuffInfoA.dwBuffCDTime = GET_BIT_32(qwBuffA, BIT_MARKB);
    vecTHBuffInfo.push_back(sTHBuffInfoA);

    STHBuffInfo sTHBuffInfoB;
    sTHBuffInfoB.byBuffID = BUFF_BJGX;
    sTHBuffInfoB.byBuffNum = GET_BIT_32(qwBuffB, BIT_MARKA);
    sTHBuffInfoB.dwBuffCDTime = GET_BIT_32(qwBuffB, BIT_MARKB);
    vecTHBuffInfo.push_back(sTHBuffInfoB);

    STHBuffInfo sTHBuffInfoC;
    sTHBuffInfoC.byBuffID = BUFF_TLHZ;
    sTHBuffInfoC.byBuffNum = GET_BIT_32(qwBuffC, BIT_MARKA);
    sTHBuffInfoC.dwBuffCDTime = GET_BIT_32(qwBuffC, BIT_MARKB);
    vecTHBuffInfo.push_back(sTHBuffInfoC);

    _rPlayer.SendPkg(g_TreasureHuntProtS.BuildPkg_THNotify(eTHNotify, qwKillNum, vecTHBuffInfo));

    return true;
}

/********************离线特殊处理Begin****************/
//获取战斗准备信息
bool CTreasureHunt::GetTHBattlePrepareInfo(
        UINT8& byKillNum, 
        UINT32& dwCurBossHP, 
        UINT32& dwTotalTimes, 
        TVecTHAwardInfo& vecTHAwardInfo, 
        TVecTHBuffInfo& vecTHBuffInfo
        )
{
    UINT32 dwTempTime = 0;
    UINT32 dwNow = time(NULL); 
    if (dwNow > GetTHLastTime())
        dwTempTime = dwNow - GetTHLastTime();

    UINT32 dwNum = dwTempTime / TH_TIMER;
    for (UINT32 i=0; i<dwNum; i++)
    {
        if (eTHProgress != GetTHStatus())
            break;

        OffLineTHBattlePrepare();
    }
    SetTHLastTime(dwNow);
    _bOffLineHandleMark = false;
    Update2DB(eOpUpdate);

    //byKillNum
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwKillNum = rCGameVar.GetVar(NVarDefine::ePlayerTHKillNum);
    if (MAX_KILLNUM > qwKillNum)
         byKillNum = MAX_KILLNUM - qwKillNum;

    //dwCurBossHP
    UINT8 bySize = _TVecBattleFighterVec.size();
    if (bySize > 0)
    {
        TVecBattleFighterPtr& vecBattleBoss = _TVecBattleFighterVec[bySize-1];
        if (vecBattleBoss[0])
            dwCurBossHP = vecBattleBoss[0]->GetHP();
    }

    //dwTotalTimes
    dwTotalTimes = GetTHTotalTime();

    //vecTHAwardInfo
    MapTHAward::iterator iter = _MapTHAward.begin();
    for (; iter!=_MapTHAward.end(); iter++)
    {
        vecTHAwardInfo.push_back(iter->second);
    }

    //vecTHBuffInfo
    {
        UINT64 qwBuffA = rCGameVar.GetVar(NVarDefine::ePlayerTGSL);
        UINT64 qwBuffB = rCGameVar.GetVar(NVarDefine::ePlayerBJGX);
        UINT64 qwBuffC = rCGameVar.GetVar(NVarDefine::ePlayerTLHZ);

        STHBuffInfo sTHBuffInfoA;
        sTHBuffInfoA.byBuffID = BUFF_TGSL;
        sTHBuffInfoA.byBuffNum = GET_BIT_32(qwBuffA, BIT_MARKA);
        sTHBuffInfoA.dwBuffCDTime = GET_BIT_32(qwBuffA, BIT_MARKB);
        vecTHBuffInfo.push_back(sTHBuffInfoA);

        STHBuffInfo sTHBuffInfoB;
        sTHBuffInfoB.byBuffID = BUFF_BJGX;
        sTHBuffInfoB.byBuffNum = GET_BIT_32(qwBuffB, BIT_MARKA);
        sTHBuffInfoB.dwBuffCDTime = GET_BIT_32(qwBuffB, BIT_MARKB);
        vecTHBuffInfo.push_back(sTHBuffInfoB);

        STHBuffInfo sTHBuffInfoC;
        sTHBuffInfoC.byBuffID = BUFF_TLHZ;
        sTHBuffInfoC.byBuffNum = GET_BIT_32(qwBuffC, BIT_MARKA);
        sTHBuffInfoC.dwBuffCDTime = GET_BIT_32(qwBuffC, BIT_MARKB);
        vecTHBuffInfo.push_back(sTHBuffInfoC);
    }

    return true;
}

//离线寻宝处理
bool CTreasureHunt::OffLineTH(UINT32 dwBossCurHP)
{
    UINT8 byCopyID = GetTHCopyID();
    if (0 == byCopyID)
        return false;
    
    SSearchMapCFG* pSearchMapCFG = CTreasureHuntMgr::Instance().GetSearchMapCFG(byCopyID);
    if (!pSearchMapCFG)
        return false;
    
    if (_rPlayer.GetLevel() < pSearchMapCFG->_Level)
        return false;

    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT8 byCond = rCGameVar.GetVar(NVarDefine::ePlayerTHCond);
    if ((byCond + 1) < byCopyID)
        return false;

    UINT64 qwKillNum = rCGameVar.GetVar(NVarDefine::ePlayerTHKillNum);
    if (qwKillNum >= MAX_KILLNUM)
        return eTHMaxKillNumDay;

    Tokenizer tk(pSearchMapCFG->_MonsterGroup, ";");
    for (size_t i=0; i<tk.size(); i++)
    {
        UINT32 dwMonsterGroupID = atoi(tk[i].c_str());
        if (0 == dwMonsterGroupID)
            return false;

        TVecBattleFighterPtr vecBattleFighter;
        vector<TVecBattleFighterPtr> vecvecBattleFighter2;
        UINT64 qwDefenseID = GET_GUID(GUID_MONSTER);
        UINT64 qwMainMonsterID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, dwMonsterGroupID, qwDefenseID, vecBattleFighter);
        if(!qwMainMonsterID)
        {
            LOG_CRI << "Can't find Monster! GroupID: " << dwMonsterGroupID;
            return false;
        }

        if (0 == vecvecBattleFighter2[0].size())
            return false;

        _TVecBattleFighterVec.push_back(vecvecBattleFighter2[0]);
        _vecMonsterGroupID.push_back(dwMonsterGroupID);
        _vecMonsterID.push_back(qwMainMonsterID);
        _vecDefenseID.push_back(qwDefenseID);
    }

    UINT8 bySize = _TVecBattleFighterVec.size();
    if (0 == bySize)
        return false;

    //Boss
    TVecBattleFighterPtr& vecBattleBoss = _TVecBattleFighterVec[bySize-1];
    if (vecBattleBoss[0])
    {
        //设置Boss最大血量
        SetTHBossMaxHP(vecBattleBoss[0]->GetHP());
        //设置Boss当前血量
        vecBattleBoss[0]->SetHP(dwBossCurHP);
    }

    return true;
}

//离线寻宝战斗准备
bool CTreasureHunt::OffLineTHBattlePrepare()
{
    UINT32 byTotalNum = GetTHTotalNum();
    if(_vecMonsterGroupID.empty())
    {
        LOG_CRI << "_vecMonsterGroupID.empty()";
        return false;
    }
    UINT8 byCurIndex = byTotalNum % _vecMonsterGroupID.size();

    UINT8 byLen = byCurIndex + 1;
    if (byLen > _vecMonsterGroupID.size()
            || byLen > _vecMonsterID.size()
            || byLen > _vecDefenseID.size()
            || byLen > _TVecBattleFighterVec.size())
        return false;

    UINT32 dwMonsterGroupID = _vecMonsterGroupID[byCurIndex];
    UINT64 qwMainMonsterID = _vecMonsterID[byCurIndex];
    UINT64 qwDefenseID = _vecDefenseID.size();
    TVecBattleFighterPtr& vecBattleFighter2 = _TVecBattleFighterVec[byCurIndex];

    OffLineTHBattle(dwMonsterGroupID, qwMainMonsterID, qwDefenseID, vecBattleFighter2, byCurIndex);

    return true;
}

//离线寻宝战斗
bool CTreasureHunt::OffLineTHBattle(UINT32 dwMonsterGroupID, UINT64 qwMainMonsterID, UINT64 qwDefenseID, TVecBattleFighterPtr& vecBattleFighter2, UINT8 byCurIndex)
{
    if (0 == vecBattleFighter2.size())
        return false;

    UINT8 bySize = _TVecBattleFighterVec.size();
    if (0 == bySize)
        return false;

    bool bBossMark = false;
    if (bySize == byCurIndex + 1)
        bBossMark = true;

    //设置战斗类型
    _rPlayer.SetBattleType(ETreasureHunt);

    //战斗前的Monster血量
    UINT32 dwOldMonsterHP = 0;
    TVecBattleFighterPtr& vecBattleMonster = _TVecBattleFighterVec[byCurIndex];
    for (size_t i=0; i<vecBattleMonster.size(); i++)
    {
        if (vecBattleMonster[i])
            dwOldMonsterHP += vecBattleMonster[i]->GetHP();
    }

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    TVecBattleFighterPtr vecBattleFighter;
    _rPlayer.GetBattleFighterList(vecBattleFighter);

    IBattleFighterPtr pScene;
    pScene = CMonster::GetSceneFighter(dwMonsterGroupID);
    if (!pScene)
        pScene = _rPlayer.GetSceneFighter();

    pBS->PutFighters(0, _rPlayer.GetMainFighter()->GetInstID(), _rPlayer.GetLevel(), vecBattleFighter, _rPlayer.GetRoleID());
    pBS->PutFighters(1, qwMainMonsterID, CMonster::GetMonsterLevelByGroupID(dwMonsterGroupID), vecBattleFighter2, qwDefenseID, false);
    pBS->PutScene(pScene);
    pBS->Start(EBTMonster);
    _rPlayer.SetBattleType(EBTINVALID);

    bool bWinMark = false;
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    if(pBS->GetFinalWinner() == EBResultAttackWin)
    {
        CMonster::DropToPlayer(dwMonsterGroupID, vecItems, vecRes);

        if (bBossMark)
        {
            SSearchMapCFG* pSearchMapCFG = CTreasureHuntMgr::Instance().GetSearchMapCFG(_byCopyID);
            if (!pSearchMapCFG)
                return false;

            //通关奖励
            if (_dwTotalTime <= pSearchMapCFG->_ClearTime)
            {
                UINT32 dwDropId = pSearchMapCFG->_TimeAward;
                LOOT.Roll(dwDropId, vecItems, vecRes);
            }

            bWinMark = true;
        }
        else
        {
            for (size_t i=0; i<vecBattleMonster.size(); i++)
            {
                if (vecBattleMonster[i])
                    vecBattleMonster[i]->SetHP(dwOldMonsterHP);
            }
        }
    }
    else
        _rPlayer.RegenAllHP();

    for (size_t i=0; i<vecItems.size(); i++)
    {
        STHAwardInfo sTHAwardInfo;
        sTHAwardInfo.wItemID = vecItems[i].wItemID;
        sTHAwardInfo.dwCount = vecItems[i].dwCount;
        AddTHAward(sTHAwardInfo);
    }

    for (size_t i=0; i<vecRes.size(); i++)
    {
        STHAwardInfo sTHAwardInfo;
        sTHAwardInfo.wItemID = vecRes[i]._eRes;
        sTHAwardInfo.dwCount = vecRes[i]._dwValue;
        AddTHAward(sTHAwardInfo);
    }

    AddTHTotalNum(1);
    AddTHTotalTime(5);

    //寻宝结束
    if (bWinMark)
    {
        THNotify(eTHEnd);
        SetTHStatus(eTHWaitGetAward);
        CleanTHBaseInfo();
        
        CUser& rUser = _rPlayer.GetUser();
        CGameVar& rCGameVar = rUser.GetVars();
        rCGameVar.AddVar(NVarDefine::ePlayerTHKillNum, 1);

        if (GetTHCopyID() > rCGameVar.GetVar(NVarDefine::ePlayerTHCond))
            rCGameVar.AddVar(NVarDefine::ePlayerTHCond, 1);
        
        //事件
        {
            TVecINT32 vecParam;
            vecParam.push_back(_byCopyID);
            vecParam.push_back(1);

            CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
            if(pEventMgr)
                pEventMgr->OnEvent(eEventType_TreasureSuccess, vecParam);
        }

        rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_FinishTreasureHunt);
    }

    return true;
}
/********************离线特殊处理End****************/

//玩家离开设置寻宝状态
bool CTreasureHunt::PlayerLeaveSetTHStatus()
{
   if (eTHProgress == GetTHStatus())
       _bOffLineHandleMark = true;

   return true;
}

//玩家离开清除寻宝信息
bool CTreasureHunt::PlayerLeaveCleanTHInfo()
{
    if (eTHProgress == GetTHStatus())
        CleanTHAwardInfo();

    CleanTHBaseInfo();

    return true;
}

//清除寻宝基本信息
bool CTreasureHunt::CleanTHBaseInfo()
{
    SetTHTotalNum(0);
    SetTHLastTime(0);
    SetTHBossMaxHP(0);
    _bOffLineHandleMark = false;

    _vecMonsterGroupID.clear();
    _vecMonsterID.clear();
    _vecDefenseID.clear();
    _TVecBattleFighterVec.clear();

    return true;
}

//清除寻宝奖励信息
bool CTreasureHunt::CleanTHAwardInfo()
{
    Update2DB(eOpDel);

    SetTHCopyID(0);
    SetTHStatus(0);
    SetTHTotalTime(0);

    _MapTHAward.clear();

    return true;
}

//更新DB
bool CTreasureHunt::Update2DB(EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    STHDBInfo oTHDBInfo;
    oTHDBInfo.qwRoleID = _rPlayer.GetRoleID();
    oTHDBInfo.byCopyID = GetTHCopyID();
    oTHDBInfo.byStatus = GetTHStatus();
    UINT32 dwCurBossHP = 0;
    UINT8 bySize = _TVecBattleFighterVec.size();
    if (bySize > 0)
    {
        TVecBattleFighterPtr& vecBattleBoss = _TVecBattleFighterVec[bySize-1];
        if (vecBattleBoss[0])
            dwCurBossHP = vecBattleBoss[0]->GetHP();
    }
    oTHDBInfo.dwBossCurHP = dwCurBossHP;
    oTHDBInfo.dwLastTime = GetTHLastTime();
    oTHDBInfo.dwTime = GetTHTotalTime();
    oTHDBInfo.dwNum = GetTHTotalNum();

    string& strAward = oTHDBInfo.strAward;
    MapTHAward::iterator iter = _MapTHAward.begin();
    for (; iter!=_MapTHAward.end(); iter++)
    {
        char strTmp[255];
        sprintf_s(strTmp,"%d,%d|", iter->second.wItemID, iter->second.dwCount);
        strAward = strAward + string(strTmp);
    }

    iar << oTHDBInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypeTH, eDataChange, strData);

    return true;
}

