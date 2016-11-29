#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "VIPMgr.h"
#include "Tokenizer.h"
#include "ItemProt.h"
#include "Loot.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "Monster.h"
#include "FighterManager.h"
#include "GuardEMei.h"
#include "GuardEMeiMgr.h"
#include "GuardEMeiProtS.h"
#include "FightHeroInfoMgr.h"
#include "FightFormationMgr.h"
#include "HeroFighter.h"
#include "Random.h"
#include "GUIDMgr.h"

//加载DB
void CGuardEMei::LoadFromDB(const SGEMDBInfo& sGEMDBInfo)
{
    SetMissionID(sGEMDBInfo.wMissionID);
    SetGEMType(sGEMDBInfo.byGEMType);
    SetCurProgress(sGEMDBInfo.wCurProgress);
    SetGuardProgress(sGEMDBInfo.wGuardProgress);
    SetGuardMonsterGroupID(sGEMDBInfo.dwGuardMonsterGroupID);
    SetSweepEndTime(sGEMDBInfo.dwSweepEndTime);
    
    Tokenizer tk1(sGEMDBInfo.strBuff, "|");
    for (size_t i=0; i<tk1.size(); i++)
    {
        string strAwardA = tk1[i].c_str();
        
        Tokenizer tkA(strAwardA, ',');
        if (2 != tkA.size())
            continue;

        SGEMBuffInfo sGEMBuffInfo;
        sGEMBuffInfo.dwBuffID = atoi(tkA[0].c_str());
        sGEMBuffInfo.dwBuffNum = atoi(tkA[1].c_str());
          
        AddGEMGuardBuff(sGEMBuffInfo); 
    }

    SetGuardMark(1);

    return;
}

//请求守卫峨眉信息
bool CGuardEMei::ReqGEMInfo(TVecGEMMissionInfo& vecGEMMissionInfo)
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwEntryNumDay = rCGameVar.GetVar(NVarDefine::ePlayerGEMEntryNum);
    UINT64 qwIsGuardSucc = rCGameVar.GetVar(NVarDefine::ePlayerGEMMissionStatus);
    UINT64 qwBuyEntryNum = rCGameVar.GetVar(NVarDefine::ePlayerGEMBuyEntryNum);
    UINT16 wFreeEntryNumDay = GET_BIT_32(qwEntryNumDay, BIT_MARKA);
    UINT16 wBuyEntryNumDay = GET_BIT_32(qwEntryNumDay, BIT_MARKB);
    
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
    if(NULL == pCfgVip)
        return false;

    if (wFreeEntryNumDay >= pCfgVip->_GuardEMeiTimes)
        wFreeEntryNumDay = 0;
    else
        wFreeEntryNumDay =  pCfgVip->_GuardEMeiTimes - wFreeEntryNumDay;

    SGEMMissionInfo sGEMMissionInfo;
    sGEMMissionInfo.wFreeEntryNumDay = wFreeEntryNumDay;
    sGEMMissionInfo.wBuyEntryNumDay = wBuyEntryNumDay;
    sGEMMissionInfo.wBuyEntryTotalNum = qwBuyEntryNum;
    sGEMMissionInfo.qwIsGuardSucc = qwIsGuardSucc;
    sGEMMissionInfo.wCurMissionID = GetMissionID();
    sGEMMissionInfo.byGEMType = GetGEMType();
    sGEMMissionInfo.wCurProgress = GetCurProgress();

    vecGEMMissionInfo.push_back(sGEMMissionInfo);

    return true;
}

//请求购买守卫峨眉进入次数
bool CGuardEMei::BuyGEMEntryNum()
{
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwEntryNumDay = rCGameVar.GetVar(NVarDefine::ePlayerGEMEntryNum);
    UINT64 qwBuyEntryNumDay = GET_BIT_32(qwEntryNumDay, BIT_MARKB);
    
    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
    if(pCfgVip == NULL)
        return false;

    if (qwBuyEntryNumDay >= pCfgVip->_GuardEMeiBuyingTimes)
        return false;
    
    UINT32 dwNeedMoney = 0;
    switch(qwBuyEntryNumDay)
    {
        case 0:
            {
                dwNeedMoney = SParamConfig::wGuardEMeiBuyingTimesPrice1;
            }
            break;
        case 1:
            {
                dwNeedMoney = SParamConfig::wGuardEMeiBuyingTimesPrice2;
            }
            break;
        case 2:
            {
                dwNeedMoney = SParamConfig::wGuardEMeiBuyingTimesPrice3;
            }
            break;
        case 3:
            {
                dwNeedMoney = SParamConfig::wGuardEMeiBuyingTimesPrice4;
            }
            break;
        default:
            {
                dwNeedMoney = SParamConfig::wGuardEMeiBuyingTimesPrice5;
            }
            break;
    }

    if (!rUser.CanSubMoney(EMONEY_GOLD, dwNeedMoney))
        return false;

    rUser.SubMoney(EMONEY_GOLD, dwNeedMoney, NLogDataDefine::ItemTo_BuyEntryNum);

    rCGameVar.AddVar(NVarDefine::ePlayerGEMBuyEntryNum, 1);

    qwBuyEntryNumDay++;
    qwEntryNumDay = SET_BIT_32(qwEntryNumDay, BIT_MARKB, qwBuyEntryNumDay);
    rCGameVar.SetVar(NVarDefine::ePlayerGEMEntryNum, qwEntryNumDay);

    return true;
}

//请求使用守卫峨眉守卫Buff
bool CGuardEMei::ReqUseGEMGuardBuff(UINT32 dwBuffID, TVecGEMBattleFighterInfo& vecGEMBattleFighterInfo, TVecGEMBuffInfo& vecGEMBuffInfo)
{
    TVecBattleFighterPtr vecBattleFighter;
    bool bRet = _rPlayer.GetBattleFighterList(vecBattleFighter, EGuardEMei);
    if (!bRet)
        return false;

    SEffectCFG* pEffectCFG = CGuardEMeiMgr::Instance().GetEffectCFG(dwBuffID);
    if (!pEffectCFG)
        return false;
    
    if (FindGEMGuardBuff(dwBuffID) && (1 != pEffectCFG->_EffectType))
    {
        switch(pEffectCFG->_EffectType)
        {
            case 2:
                {
                    for(size_t i=0; i < vecBattleFighter.size(); i++)
                    {
                        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
                        if (0 == pBattleFighter->GetInstID())
                            continue;

                        if (0 == pBattleFighter->GetHP())
                            continue;

                        UINT32 dwFighterCurHP = pBattleFighter->GetHP();
                        UINT32 dwFighterMaxHP = pBattleFighter->GetMaxHP();
                        if ((dwFighterCurHP + pEffectCFG->_Effect) > dwFighterMaxHP)
                            pBattleFighter->SetHP(dwFighterMaxHP);
                        else
                            pBattleFighter->SetHP(dwFighterCurHP + pEffectCFG->_Effect);
                    }
                }
                break;
            case 3:
                {
                    for(size_t i=0; i < vecBattleFighter.size(); i++)
                    {
                        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
                        if (0 == pBattleFighter->GetInstID())
                            continue;

                        if (0 == pBattleFighter->GetHP())
                            continue;

                        UINT32 dwFighterCurHP = pBattleFighter->GetHP();
                        UINT32 dwFighterMaxHP = pBattleFighter->GetMaxHP();
                        UINT32 dwTempHp = dwFighterMaxHP * pEffectCFG->_Effect / 10000;
                        if ((dwFighterCurHP + dwTempHp) > dwFighterMaxHP)
                            pBattleFighter->SetHP(dwFighterMaxHP);
                        else
                            pBattleFighter->SetHP(dwFighterCurHP + dwTempHp);
                    }
                }
                break;
            case 4:
                {
                    for(size_t i=0; i < vecBattleFighter.size(); i++)
                    {
                        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
                        if (0 == pBattleFighter->GetInstID())
                            continue;

                        if (0 == pBattleFighter->GetHP())
                            continue;

                        UINT32 dwFighterCurAnima =  pBattleFighter->GetAura();
                        UINT32 dwFighterMaxAnima = pBattleFighter->GetMaxAura();
                        if ((dwFighterCurAnima + pEffectCFG->_Effect) > dwFighterMaxAnima)
                            pBattleFighter->SetAura(dwFighterMaxAnima);
                        else
                            pBattleFighter->SetAura(dwFighterCurAnima + pEffectCFG->_Effect);
                    }
                }
                break;
        }

        _rPlayer.SaveBattleFighterInfo(EGuardEMei, vecBattleFighter);
        
        SubGEMGuardBuff(dwBuffID);

        Update2DB(eOpUpdate);
    }

    for(size_t i=0; i < vecBattleFighter.size(); i++)
    {
        SGEMBattleFighterInfo oGEMBattleFighterInfo;

        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
        if (0 == pBattleFighter->GetInstID())
            continue;

        oGEMBattleFighterInfo.dwFighterID = pBattleFighter->GetID();
        oGEMBattleFighterInfo.byFighterLevel = pBattleFighter->GetLevel();
        oGEMBattleFighterInfo.byFighterColour = pBattleFighter->GetColour();
        oGEMBattleFighterInfo.dwFighterCurHP = pBattleFighter->GetHP();
        oGEMBattleFighterInfo.dwFighterMaxHP = pBattleFighter->GetMaxHP();
        oGEMBattleFighterInfo.dwFighterCurAnima =  pBattleFighter->GetAura();
        oGEMBattleFighterInfo.dwFighterMaxAnima = pBattleFighter->GetMaxAura();

        vecGEMBattleFighterInfo.push_back(oGEMBattleFighterInfo);
    }
    
    MapGEMBuff::iterator iterA = _mapGEMBuff.begin();
    for (; iterA!=_mapGEMBuff.end(); iterA++)
    {
        vecGEMBuffInfo.push_back(iterA->second);
    }

    return true;
}

//请求守卫峨眉守卫准备战斗信息
bool CGuardEMei::ReqGEMGuardPrepareBattleInfo(UINT16 wMissionID, SGEMPrepareBattleInfo& sGEMPrepareBattleInfo)
{
    if (0 == wMissionID)
        return false;

    if (GetCurProgress() && wMissionID != GetMissionID())
        return false;

    //检测前一个关卡是否已经完成
    if (wMissionID > 1)
    {
        CUser& rUser = _rPlayer.GetUser();
        CGameVar& rCGameVar = rUser.GetVars();
        UINT64 qwIsGuardSucc = rCGameVar.GetVar(NVarDefine::ePlayerGEMMissionStatus);
        UINT64 qwPos = wMissionID - 2;
        UINT8 qwSuccMark = GET_BIT(qwIsGuardSucc, qwPos);
        if (0 == qwSuccMark)
            return false;
    }

    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(wMissionID);
    if (!pGuardEMeiCFG)
        return false;

    if (_rPlayer.GetLevel() < pGuardEMeiCFG->_RequiredLevel)
        return false;

    if (GEM_SWEEP == GetGEMType())
        return false;
   
    if (0 == GetGuardMonsterGroupID())
    {
        UINT16 wProgress = GetGuardProgress() + 1;
        SGuardEMeiLevelCFG* pGuardEMeiLevelCFG = CGuardEMeiMgr::Instance().GetGuardEMeiLevelCFG(wMissionID, wProgress);
        if (!pGuardEMeiLevelCFG)
            return false;
      
        UINT16 wTemp = 0;
        UINT16 wRand = CRandom::RandInt(0, GEM_MAX_RANDNUM);
        Tokenizer tk(pGuardEMeiLevelCFG->_MonsterGroup, "|");
        for (size_t i=0; i<tk.size(); i++)
        {
            Tokenizer tkA(tk[i].c_str(), ",");
            if (2 != tkA.size())
                return false;
            
            UINT16 wValue = atoi(tkA[1].c_str());
            if (wRand >= wTemp && wRand < wValue)
            {
                UINT32 dwMonstrGroupID = atoi(tkA[0].c_str());
                SetGuardMonsterGroupID(dwMonstrGroupID);
                break;
            }
            else
                wTemp = wValue;
        }
    }

    EDataChange eDataChange;
    if (0 == GetGuardMark())
    {
        CUser& rUser = _rPlayer.GetUser();
        CGameVar& rCGameVar = rUser.GetVars();
        UINT64 qwBuyEntryNumDay = rCGameVar.GetVar(NVarDefine::ePlayerGEMBuyEntryNum);
        UINT64 qwEntryNumDay = rCGameVar.GetVar(NVarDefine::ePlayerGEMEntryNum);
        UINT64 qwFreeEntryNumDay = GET_BIT_32(qwEntryNumDay, BIT_MARKA);
            
        SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
        if(NULL == pCfgVip)
            return false;

        if (qwFreeEntryNumDay < pCfgVip->_GuardEMeiTimes)
        {
            //优先扣除当天免费赠送进入次数 
            qwFreeEntryNumDay++;
            qwEntryNumDay = SET_BIT_32(qwEntryNumDay, BIT_MARKA, qwFreeEntryNumDay);
            rCGameVar.SetVar(NVarDefine::ePlayerGEMEntryNum, qwEntryNumDay);
        }
        else if (qwBuyEntryNumDay > 0)
        {
            //当天免费赠送进入次数用完，扣除仙石购买进入次数
            qwBuyEntryNumDay--;
            rCGameVar.SetVar(NVarDefine::ePlayerGEMBuyEntryNum, qwBuyEntryNumDay);
        }
        else
            return false;

        if (0 == wMissionID)
            return false;

        if (_rPlayer.GetFightHeroInfoMgr())
            _rPlayer.GetFightHeroInfoMgr()->ClearByBattleType(EGuardEMei);
        
        SetMissionID(wMissionID);
        SetGuardMark(1);
        eDataChange = eOpAdd;
    }
    else
        eDataChange = eOpUpdate;
       
    //设置守卫类型
    SetGEMType(GEM_GUARD);
    //放弃扫荡，将当前进度设置为和扫荡前的守卫进度一致
    SetCurProgress(GetGuardProgress());

    sGEMPrepareBattleInfo.wCurProgress = GetCurProgress();
    sGEMPrepareBattleInfo.dwMonsterID = GetGuardMonsterGroupID();
    CFightFormationMgrPtr pFightFormationMgr = _rPlayer.GetFightFormationMgr();
    if(pFightFormationMgr)
        sGEMPrepareBattleInfo.dwBattlePoint = pFightFormationMgr->GetBattlePoint(EGuardEMei);
    
    MapGEMBuff::iterator iter = _mapGEMBuff.begin();
    for (; iter!=_mapGEMBuff.end(); iter++)
    {
        sGEMPrepareBattleInfo.vecGEMBuffInfo.push_back(iter->second);
    }

    TVecBattleFighterPtr vecBattleFighter;
    _rPlayer.GetBattleFighterList(vecBattleFighter, EGuardEMei);
    for(size_t i=0; i < vecBattleFighter.size(); i++)
    {
        SGEMBattleFighterInfo oGEMBattleFighterInfo;

        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
        if (0 == pBattleFighter->GetInstID())
            continue;

        oGEMBattleFighterInfo.dwFighterID = pBattleFighter->GetID();
        oGEMBattleFighterInfo.byFighterLevel = pBattleFighter->GetLevel();
        oGEMBattleFighterInfo.byFighterColour = pBattleFighter->GetColour();
        oGEMBattleFighterInfo.dwFighterCurHP = pBattleFighter->GetHP();
        oGEMBattleFighterInfo.dwFighterMaxHP = pBattleFighter->GetMaxHP();
        oGEMBattleFighterInfo.dwFighterCurAnima =  pBattleFighter->GetAura();
        oGEMBattleFighterInfo.dwFighterMaxAnima = pBattleFighter->GetMaxAura();

        sGEMPrepareBattleInfo.vecGEMBattleFighterInfo.push_back(oGEMBattleFighterInfo);
    }
    
    Update2DB(eDataChange);

    return true;
}

//守卫峨眉守卫结束战斗信息
bool CGuardEMei::GEMGuardEndBattleInfo(SGEMPrepareBattleInfo& sGEMPrepareBattleInfo)
{
    sGEMPrepareBattleInfo.wCurProgress = GetCurProgress();
    sGEMPrepareBattleInfo.dwMonsterID = GetGuardMonsterGroupID();
    CFightFormationMgrPtr pFightFormationMgr = _rPlayer.GetFightFormationMgr();
    if(pFightFormationMgr)
        sGEMPrepareBattleInfo.dwBattlePoint = pFightFormationMgr->GetBattlePoint(EGuardEMei);
    
    MapGEMBuff::iterator iter = _mapGEMBuff.begin();
    for (; iter!=_mapGEMBuff.end(); iter++)
    {
        sGEMPrepareBattleInfo.vecGEMBuffInfo.push_back(iter->second);
    }

    TVecBattleFighterPtr vecBattleFighter;
    _rPlayer.GetBattleFighterList(vecBattleFighter, EGuardEMei);
    for(size_t i=0; i < vecBattleFighter.size(); i++)
    {
        SGEMBattleFighterInfo oGEMBattleFighterInfo;

        IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
        if (0 == pBattleFighter->GetInstID())
            continue;

        oGEMBattleFighterInfo.dwFighterID = pBattleFighter->GetID();
        oGEMBattleFighterInfo.byFighterLevel = pBattleFighter->GetLevel();
        oGEMBattleFighterInfo.byFighterColour = pBattleFighter->GetColour();
        oGEMBattleFighterInfo.dwFighterCurHP = pBattleFighter->GetHP();
        oGEMBattleFighterInfo.dwFighterMaxHP = pBattleFighter->GetMaxHP();
        oGEMBattleFighterInfo.dwFighterCurAnima =  pBattleFighter->GetAura();
        oGEMBattleFighterInfo.dwFighterMaxAnima = pBattleFighter->GetMaxAura();

        sGEMPrepareBattleInfo.vecGEMBattleFighterInfo.push_back(oGEMBattleFighterInfo);
    }

    return true;
}

//请求守卫峨眉守卫战斗
bool CGuardEMei::ReqGEMGuardBattle(UINT16 wMissionID, UINT32 dwBuffID, EGEMBattleType eGEMBattleType, EGEMBattleRet& eGEMBattleRet, SGEMPrepareBattleInfo& sGEMPrepareBattleInfo)
{
    if (GEM_GUARD != GetGEMType())
        return false;

    if (wMissionID != GetMissionID())
        return false;

    if (eGEMBattleTypeA!=eGEMBattleType && eGEMBattleTypeB!=eGEMBattleType)
        return false;

    //检测前一个关卡是否已经完成
    if (wMissionID > 1)
    {
        CUser& rUser = _rPlayer.GetUser();
        CGameVar& rCGameVar = rUser.GetVars();
        UINT64 qwIsGuardSucc = rCGameVar.GetVar(NVarDefine::ePlayerGEMMissionStatus);
        UINT64 qwPos = wMissionID - 2;
        UINT8 qwSuccMark = GET_BIT(qwIsGuardSucc, qwPos);
        if (0 == qwSuccMark)
            return false;
    }

    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(GetMissionID());
    if (!pGuardEMeiCFG)
        return false;

    if (_rPlayer.GetLevel() < pGuardEMeiCFG->_RequiredLevel)
        return false;

    LOG_CRI << "GUARD Progress:" << GetGuardProgress();
    if (GetGuardProgress() >= pGuardEMeiCFG->_MaxNum)
        return false;
    
    UINT16 wProgress = GetGuardProgress() + 1;
    SGuardEMeiLevelCFG* pGuardEMeiLevelCFG = CGuardEMeiMgr::Instance().GetGuardEMeiLevelCFG(GetMissionID(), wProgress);
    if (!pGuardEMeiLevelCFG)
        return false;

    //提前掉落，只为背包检测
    bool bPassMark = false;
    UINT64 qwExp = 0;
    TVecItemGenInfo vecAwards;
    {
        if (wProgress == pGuardEMeiCFG->_MaxNum)
        {
            GetGEMGuardSuccAward(vecAwards);
            
            TVecItemGenInfo::iterator iter = vecAwards.begin();
            for ( ; iter!=vecAwards.end(); )
            {
                if (EMONEY_EXP == (*iter).wItemID)
                {
                    qwExp += (*iter).dwCount;
                    iter = vecAwards.erase(iter);
                }
                else
                    iter++;
            }

            bPassMark = true;
        }

        TVecItemGenInfo vecItems;
        TVecResource vecRes;
        LOOT.Roll(pGuardEMeiLevelCFG->_LootId, vecItems, vecRes);
       
        for (size_t i=0; i<vecItems.size(); i++)
        {
            SItemGenInfo sItemGenInfo;
            sItemGenInfo.wItemID = vecItems[i].wItemID;
            sItemGenInfo.dwCount = vecItems[i].dwCount;
            sItemGenInfo.eBindType = eBindGet;
            vecAwards.push_back(sItemGenInfo);
            
            //背包检测
            CPack& oPack = _rPlayer.GetUser().GetPack();
            if(!oPack.CanAddItem(vecAwards))
            {
                _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
                return false;
            }
        }
        
        for (size_t i=0; i<vecRes.size(); i++)
        {
            if (EMONEY_EXP == vecRes[i]._eRes)
                qwExp += vecRes[i]._dwValue;
            else
            {
                SItemGenInfo sItemGenInfo;
                sItemGenInfo.wItemID = vecRes[i]._eRes;
                sItemGenInfo.dwCount = vecRes[i]._dwValue;
                sItemGenInfo.eBindType = eBindGet;
                vecAwards.push_back(sItemGenInfo);
            }
        }
    }

    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    TVecBattleFighterPtr vecBattleFighter;
    vector<TVecBattleFighterPtr> vecvecBattleFighter2;
    bool bRet = _rPlayer.GetBattleFighterList(vecBattleFighter, EGuardEMei);
    if (!bRet)
        return false;
    
    TVecUINT16 vecFighterID;
    for (size_t i=0;i < vecBattleFighter.size(); i++)
    {
        //死的不加载技能
        if(vecBattleFighter[i]->GetHP())
        {
            CFighterPtr pFigter = _rPlayer.GetFighterByInstID(vecBattleFighter[i]->GetInstID()); 
            if(pFigter)
                vecFighterID.push_back(pFigter->GetID());
        }
    }
    _rPlayer.GetFighterManager()->ResetCombinationSkill(vecFighterID, eCombEquipToEMei);

    //TODO
    vecBattleFighter.clear();
    _rPlayer.GetBattleFighterList(vecBattleFighter, EGuardEMei);

    UINT64 qwDefenseID = GET_GUID(GUID_MONSTER);
    UINT64 qwMainMonsterID = CMonster::GetBattleFighterListByGroupID(vecvecBattleFighter2, GetGuardMonsterGroupID(), qwDefenseID, vecBattleFighter);
    if(!qwMainMonsterID)
    {
        LOG_CRI << "GuardEMei Can't find Monster! GroupID: " << GetGuardMonsterGroupID();
        return false;
    }

    //添加增益Buff
    if (FindGEMGuardBuff(dwBuffID))
        _rPlayer.AddBuff(dwBuffID);

    IBattleFighterPtr pScene;
    pScene = CMonster::GetSceneFighter(GetGuardMonsterGroupID());
    if (!pScene)
        pScene = _rPlayer.GetSceneFighter();

    pBS->PutFighters(0, _rPlayer.GetMainFighter()->GetInstID(), _rPlayer.GetLevel(), vecBattleFighter, _rPlayer.GetRoleID(), false, _rPlayer.GetAppearFeature());
    pBS->PutFighters(1, qwMainMonsterID, CMonster::GetMonsterLevelByGroupID(GetGuardMonsterGroupID()), vecvecBattleFighter2[0], qwDefenseID);
    pBS->PutScene(pScene);
    pBS->Start(EBTMonster);
  
    //发送战报
    if (eGEMBattleTypeA == eGEMBattleType)
    {
        std::string strReport;
        pBS->GetReport(strReport);
        std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, _rPlayer.GetRoleID(), _rPlayer.GetMainFighter()->GetID());
        _rPlayer.SendPkg(strData);
    }

    //恢复连携技能
    _rPlayer.GetFighterManager()->ResetCombinationSkill();

    //移除增益Buff
    if (FindGEMGuardBuff(dwBuffID))
    {
        _rPlayer.RemoveBuff(dwBuffID);

        SubGEMGuardBuff(dwBuffID);
    }

    //保存散仙信息
    _rPlayer.SaveBattleFighterInfo(EGuardEMei, vecBattleFighter);

    bool bWinMark = false;
    if(pBS->GetFinalWinner() == EBResultAttackWin)
    {
        //胜利获得Buff
        UINT16 wTemp = 0;
        UINT16 wRand = CRandom::RandInt(0, GEM_MAX_RANDNUM);
        Tokenizer tk(pGuardEMeiLevelCFG->_LootBuff, "|");
        for (size_t i=0; i<tk.size(); i++)
        {
            Tokenizer tkA(tk[i].c_str(), ",");
            if (2 != tkA.size())
                continue;
            
            UINT16 wValue = atoi(tkA[1].c_str());
            if (wRand >= wTemp && wRand < wValue)
            {
                SGEMBuffInfo sGEMBuffInfo;
                sGEMBuffInfo.dwBuffID = atoi(tkA[0].c_str());
                sGEMBuffInfo.dwBuffNum = 1;
                AddGEMGuardBuff(sGEMBuffInfo);
                break;
            }
            else
                wTemp = wValue;
        }

        //胜利获得奖品
        GetAward(vecAwards);
        
        //经验只发放当前阵型上的散仙
        if (qwExp > 0)
        {
            CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
            if(NULL == pFighterManager)
                return false;

            for(size_t i=0; i < vecBattleFighter.size(); i++)
            {
                IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
                if (0 == pBattleFighter->GetInstID())
                    continue;
                
                CFighterPtr pFighter = pFighterManager->GetFighterByInstID(pBattleFighter->GetInstID());
                if(NULL == pFighter)
                    continue;

                pFighter->AddExp(qwExp);
            }
        }

        bWinMark = true;
    }
    else
    {
        if (!_rPlayer.GetFightHeroInfoMgr())
            return false;

        GEMGuardEndBattleInfo(sGEMPrepareBattleInfo);

        //策划需求，玩家在锁仙台中只要战斗失败，则即为挑战失败（先前是全队团灭）
        _rPlayer.SendPkg(g_GuardEMeiProtS.BuildPkg_MissionPassFailedtify());
        CleanGEMData();
        
        //如果所有散仙血量不为0，替换散仙可以继续守卫，否则守卫失败
        /*if (!_rPlayer.GetFightHeroInfoMgr()->CheckAllFighterHPByBattleType(EGuardEMei))
        {
            _rPlayer.SendPkg(g_GuardEMeiProtS.BuildPkg_MissionPassFailedtify());
            CleanGEMData();
        }*/
    }

    if (bWinMark)
    {
        //设置守卫通关标记
        if (bPassMark)
        {
            eGEMBattleRet = eGEMBattleSucc;
            GEMGuardEndBattleInfo(sGEMPrepareBattleInfo);

            CUser& rUser = _rPlayer.GetUser();
            CGameVar& rCGameVar = rUser.GetVars();
            UINT64 qwIsGuardSucc = rCGameVar.GetVar(NVarDefine::ePlayerGEMMissionStatus);
            UINT64 qwSuccMark = GET_BIT(qwIsGuardSucc, (GetMissionID()-1));
            if (0 == qwSuccMark)
            {
                qwIsGuardSucc = SET_BIT(qwIsGuardSucc, (GetMissionID()-1));
                rCGameVar.SetVar(NVarDefine::ePlayerGEMMissionStatus, qwIsGuardSucc);
            }
            
            _rPlayer.SendPkg(g_GuardEMeiProtS.BuildPkg_MissionPassSuccNotify());
            
            //事件
            {
                TVecINT32 vecParam;
                vecParam.push_back(GetMissionID());

                CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
                if(pEventMgr)
                {
                    pEventMgr->OnEvent(eEventType_GuardEmeiFinish, vecParam);
                    vecParam.push_back(_rPlayer.GetBattlePoint());
                    pEventMgr->OnEvent(eEventType_GuardEmeiFinishMore, vecParam);
                }
            }

            rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_DefenseShushanSuc); 
            
            CleanGEMData();

        }
        else
        {
            SetCurProgress(wProgress);
            SetGuardProgress(wProgress);
            SetGuardMonsterGroupID(0);

            eGEMBattleRet = eGEMBattleFailed;
            //下一波战斗准备信息
            ReqGEMGuardPrepareBattleInfo(GetMissionID(), sGEMPrepareBattleInfo);
        }
    }

    return true;
}

//请求重置守卫峨眉守卫关卡
bool CGuardEMei::ReqResetGEMGuardMission(UINT16 wMissionID)
{
    if (wMissionID != GetMissionID())
        return false;
    
    CleanGEMData();

    return true;
}

//查找守卫峨眉守卫Buff
bool CGuardEMei::FindGEMGuardBuff(UINT32 dwBuffID)
{
    MapGEMBuff::iterator iter = _mapGEMBuff.find(dwBuffID);
    if (iter == _mapGEMBuff.end())
        return false;

    return true;
}

//添加守卫峨眉守卫Buff
bool CGuardEMei::AddGEMGuardBuff(SGEMBuffInfo& sGEMBuffInfo)
{
    MapGEMBuff::iterator iter = _mapGEMBuff.find(sGEMBuffInfo.dwBuffID);
    if (iter != _mapGEMBuff.end())
        iter->second.dwBuffNum += sGEMBuffInfo.dwBuffNum;
    else
        _mapGEMBuff.insert(std::make_pair(sGEMBuffInfo.dwBuffID, sGEMBuffInfo)); 
    
    return true;
}

//扣除守卫峨眉守卫Buff
bool CGuardEMei::SubGEMGuardBuff(UINT32 dwBuffID)
{
    MapGEMBuff::iterator iter = _mapGEMBuff.find(dwBuffID);
    if (iter != _mapGEMBuff.end())
        if (iter->second.dwBuffNum > 0)
            iter->second.dwBuffNum -= 1;
    
    if (0 == iter->second.dwBuffNum)
        _mapGEMBuff.erase(iter);

    return true;
}

//获取守卫峨眉通关奖励
bool CGuardEMei::GetGEMGuardSuccAward(TVecItemGenInfo& vecAwards)
{
    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(GetMissionID());
    if (!pGuardEMeiCFG)
        return false;
    
    if (GetCurProgress()+1 < pGuardEMeiCFG->_MaxNum)
        return false;

    Tokenizer tk(pGuardEMeiCFG->_FinishReward, "|");
    for (size_t i=0; i<tk.size(); i++)
    {
        Tokenizer tkA(tk[i].c_str(), ",");
        if (2 != tkA.size())
            return false;
        
        SItemGenInfo sItemGenInfo;
        sItemGenInfo.wItemID = atoi(tkA[0].c_str());
        sItemGenInfo.dwCount = atoi(tkA[1].c_str());
        sItemGenInfo.eBindType = eBindGet;
        vecAwards.push_back(sItemGenInfo);
    }

    return true;
}

//请求守卫峨眉扫荡开始
bool CGuardEMei::ReqGEMSweepBegin(UINT16 wMissionID)
{
    if (0 == wMissionID)
        return false;

    //守卫成功，方可扫荡
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwIsGuardSucc = rCGameVar.GetVar(NVarDefine::ePlayerGEMMissionStatus);
    UINT64 qwPos = wMissionID - 1;
    UINT8 qwSuccMark = GET_BIT(qwIsGuardSucc, qwPos);
    if (0 == qwSuccMark)
        return false;
    
    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(wMissionID);
    if (!pGuardEMeiCFG)
        return false;

    if (_rPlayer.GetLevel() < pGuardEMeiCFG->_RequiredLevel)
        return false;

    if (GetCurProgress() >= pGuardEMeiCFG->_MaxNum)
        return false;

    EDataChange eDataChange;
    if (0 == GetGuardMark())
    {
        CUser& rUser = _rPlayer.GetUser();
        CGameVar& rCGameVar = rUser.GetVars();
        UINT64 qwBuyEntryNumDay = rCGameVar.GetVar(NVarDefine::ePlayerGEMBuyEntryNum);
        UINT64 qwEntryNumDay = rCGameVar.GetVar(NVarDefine::ePlayerGEMEntryNum);
        UINT64 qwFreeEntryNumDay = GET_BIT_32(qwEntryNumDay, BIT_MARKA);

        SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
        if(NULL == pCfgVip)
            return false;

        if (qwFreeEntryNumDay < pCfgVip->_GuardEMeiTimes)
        {
            //优先扣除当天免费赠送进入次数 
            qwFreeEntryNumDay++;
            qwEntryNumDay = SET_BIT_32(qwEntryNumDay, BIT_MARKA, qwFreeEntryNumDay);
            rCGameVar.SetVar(NVarDefine::ePlayerGEMEntryNum, qwEntryNumDay);
        }
        else if (qwBuyEntryNumDay > 0)
        {
            //当天免费赠送进入次数用完，扣除仙石购买进入次数
            qwBuyEntryNumDay--;
            rCGameVar.SetVar(NVarDefine::ePlayerGEMBuyEntryNum, qwBuyEntryNumDay);
        }
        else
            return false;
        
        if (0 == wMissionID)
            return false;

        if (_rPlayer.GetFightHeroInfoMgr())
            _rPlayer.GetFightHeroInfoMgr()->ClearByBattleType(EGuardEMei);
        
        SetMissionID(wMissionID);
        SetGuardMark(1);
        eDataChange = eOpAdd;
    }
    else
        eDataChange = eOpUpdate;

    SVIPLevelCFGEx* pCfgVip =  VIPMgr.GetVIPLevelCfg(rUser.GetVIPLevel());
    if(NULL == pCfgVip)
        return false;

    UINT16 wSweepNum = pGuardEMeiCFG->_MaxNum - GetCurProgress();
    if (0 == pCfgVip->_GuardEMeiAutoNoCd)
    {
        UINT32 dwNow = time(NULL);
        UINT32 dwSweepEndTime = dwNow + wSweepNum * (SParamConfig::wGuardEMeiBuyingAutoFightTime);
        SetSweepLastTime(dwNow);
        SetSweepEndTime(dwSweepEndTime);

        wSweepNum = 0;
    }

    SetGEMType(GEM_SWEEP);

    Update2DB(eDataChange);

    for (size_t i=0; i<wSweepNum; i++)
    {
        GEMSweepResult();
    }

    return true;
}

//守卫峨眉扫荡定时器
bool CGuardEMei::GEMSweepTimerCheck(UINT32 dwNow)
{
    if (GEM_SWEEP != GetGEMType())
        return false;
    
    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(GetMissionID());
    if (!pGuardEMeiCFG)
        return false;

    if (GetCurProgress() >= pGuardEMeiCFG->_MaxNum)
        return false;

    UINT32 dwTempTime = 0;
    if (dwNow > GetSweepLastTime())
        dwTempTime = dwNow - GetSweepLastTime();

    if (dwTempTime >= SParamConfig::wGuardEMeiBuyingAutoFightTime)
    {
        GEMSweepResult();
        SetSweepLastTime(dwNow);
    }

    return true;
}

//守卫峨眉特殊扫荡
bool CGuardEMei::GEMSpecialSweep()
{
    if (GEM_SWEEP != GetGEMType())
        return false;
    
    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(GetMissionID());
    if (!pGuardEMeiCFG)
        return false;

    if (GetCurProgress() >= pGuardEMeiCFG->_MaxNum)
        return false;

    UINT16 wCount = 0;
    UINT32 dwNowTime = time(NULL);
    if (dwNowTime >= GetSweepEndTime())
        wCount = pGuardEMeiCFG->_MaxNum - GetCurProgress();
    else
    {
        UINT16 wtemp = (GetSweepEndTime() - dwNowTime) / (SParamConfig::wGuardEMeiBuyingAutoFightTime) + GetCurProgress();
        if (pGuardEMeiCFG->_MaxNum >= wtemp)
            wCount = pGuardEMeiCFG->_MaxNum - wtemp;
    }

    for (size_t i=0; i<wCount; i++)
    {
        GEMSweepResult();
    }

    return true;
}

//守卫峨眉扫荡结果
bool CGuardEMei::GEMSweepResult()
{
    if (GEM_SWEEP != GetGEMType())
        return false;
    
    //守卫成功，方可扫荡
    CUser& rUser = _rPlayer.GetUser();
    CGameVar& rCGameVar = rUser.GetVars();
    UINT64 qwIsGuardSucc = rCGameVar.GetVar(NVarDefine::ePlayerGEMMissionStatus);
    UINT64 qwPos = GetMissionID() - 1;
    UINT8 qwSuccMark = GET_BIT(qwIsGuardSucc, qwPos);
    if (0 == qwSuccMark)
        return false;

    SGuardEMeiCFG* pGuardEMeiCFG = CGuardEMeiMgr::Instance().GetGuardEMeiCFG(GetMissionID());
    if (!pGuardEMeiCFG)
        return false;

    if (GetCurProgress() >= pGuardEMeiCFG->_MaxNum)
        return false;

    if (_rPlayer.GetLevel() < pGuardEMeiCFG->_RequiredLevel)
        return false;

    UINT16 wCurProgress = GetCurProgress()+1; 
    SGuardEMeiLevelCFG* pGuardEMeiLevelCFG = CGuardEMeiMgr::Instance().GetGuardEMeiLevelCFG(GetMissionID(), wCurProgress);
    if (!pGuardEMeiLevelCFG)
        return false;

    bool bPassMark = false;
    UINT64 qwExp = 0;
    TVecGEMAwardInfo vecGEMAwardInfo;
    TVecItemGenInfo vecAwards;
    {
        if (wCurProgress == pGuardEMeiCFG->_MaxNum)
        {
            bPassMark = true;
            GetGEMGuardSuccAward(vecAwards);

            TVecItemGenInfo::iterator iter = vecAwards.begin();
            for ( ; iter!=vecAwards.end(); )
            {
                SGEMAwardInfo sGEMAwardInfo;
                sGEMAwardInfo.wItemID = (*iter).wItemID;
                sGEMAwardInfo.dwCount = (*iter).dwCount;
                vecGEMAwardInfo.push_back(sGEMAwardInfo);
                
                if (EMONEY_EXP == (*iter).wItemID)
                {
                    qwExp += (*iter).dwCount;
                    iter = vecAwards.erase(iter);
                }
                else
                    iter++;
            }
        }

        TVecItemGenInfo vecItems;
        TVecResource vecRes;
        LOOT.Roll(pGuardEMeiLevelCFG->_LootId, vecItems, vecRes);
       
        for (size_t i=0; i<vecItems.size(); i++)
        {
            SGEMAwardInfo sGEMAwardInfo;
            sGEMAwardInfo.wItemID = vecItems[i].wItemID;
            sGEMAwardInfo.dwCount = vecItems[i].dwCount;
            vecGEMAwardInfo.push_back(sGEMAwardInfo);

            SItemGenInfo sItemGenInfo;
            sItemGenInfo.wItemID = vecItems[i].wItemID;
            sItemGenInfo.dwCount = vecItems[i].dwCount;
            sItemGenInfo.eBindType = eBindGet;
            vecAwards.push_back(sItemGenInfo);
            
            //背包检测
            CPack& oPack = _rPlayer.GetUser().GetPack();
            if(!oPack.CanAddItem(vecAwards))
            {
                _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
                return false;
            }
        }
        
        for (size_t i=0; i<vecRes.size(); i++)
        {
            SGEMAwardInfo sGEMAwardInfo;
            sGEMAwardInfo.wItemID = vecRes[i]._eRes;
            sGEMAwardInfo.dwCount = vecRes[i]._dwValue;
            vecGEMAwardInfo.push_back(sGEMAwardInfo);

            if (EMONEY_EXP == vecRes[i]._eRes)
                qwExp += vecRes[i]._dwValue;
            else
            {
                SItemGenInfo sItemGenInfo;
                sItemGenInfo.wItemID = vecRes[i]._eRes;
                sItemGenInfo.dwCount = vecRes[i]._dwValue;
                sItemGenInfo.eBindType = eBindGet;
                vecAwards.push_back(sItemGenInfo);
            }
        }
    }

    //发放奖品
    GetAward(vecAwards);

    //经验只发放当前阵型上的散仙
    if (qwExp > 0)
    {
        CFighterManagerPtr pFighterManager = _rPlayer.GetFighterManager();
        if(NULL == pFighterManager)
            return false;

        TVecBattleFighterPtr vecBattleFighter;
        _rPlayer.GetBattleFighterList(vecBattleFighter, EGuardEMei);
        for(size_t i=0; i < vecBattleFighter.size(); i++)
        {
            IBattleFighterPtr pBattleFighter=vecBattleFighter[i];
            if (0 == pBattleFighter->GetInstID())
                continue;
            
            CFighterPtr pFighter = pFighterManager->GetFighterByInstID(pBattleFighter->GetInstID());
            if(NULL == pFighter)
                continue;

            pFighter->AddExp(qwExp);
        }
    }

    //设置扫荡进度
    SetCurProgress(wCurProgress);
    
    //发放奖品日志
    _rPlayer.SendPkg(g_GuardEMeiProtS.BuildPkg_SweepInfoNotify(GetCurProgress(), vecGEMAwardInfo));

    //扫荡通关
    if (bPassMark)
    {
        _rPlayer.SendPkg(g_GuardEMeiProtS.BuildPkg_MissionPassSuccNotify());
        
        CUser& rUser = _rPlayer.GetUser();
        rUser.GetTaskPkg().OnAction(_rPlayer, eProcessAction_DefenseShushanSuc);
        
        //事件
        {
            TVecINT32 vecParam;
            vecParam.push_back(GetMissionID());

            CEventMgrPtr pEventMgr = _rPlayer.GetEventMgr();
            if(pEventMgr)
            {
                pEventMgr->OnEvent(eEventType_GuardEmeiFinish, vecParam);
                
                vecParam.push_back(_rPlayer.GetBattlePoint());
                pEventMgr->OnEvent(eEventType_GuardEmeiFinishMore, vecParam);

            }
        }

        CleanGEMData();
    }
    else
        Update2DB(eOpUpdate);

    return true;
}

//请求获取守卫峨眉扫荡结束(放弃扫荡)
UINT16 CGuardEMei::ReqGEMSweepEnd(UINT16 wMissionID)
{
    if (wMissionID != GetMissionID())
        return false;

    if (GEM_SWEEP != GetGEMType())
        return false;
   
    SetGEMType(0);

    SetCurProgress(GetGuardProgress());

    CleanGEMSweepData();

    Update2DB(eOpUpdate);

    return GetCurProgress();
}

//获取奖励
bool CGuardEMei::GetAward(TVecItemGenInfo& vecAwards)
{
    if (0 == vecAwards.size())
        return false;

    CPack& oPack = _rPlayer.GetUser().GetPack();
    if(!oPack.CanAddItem(vecAwards))
    {
        _rPlayer.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgMonsterDropPackFull));
        return false;
    }
    else
        oPack.AddItem(vecAwards, NLogDataDefine::ItemFrom_GuardEMei);

    return true;
}

//清除守卫峨眉信息
bool CGuardEMei::CleanGEMData()
{
    Update2DB(eOpDel);

    SetGuardMark(0);
    SetGEMType(0);
    SetMissionID(0);
    SetCurProgress(0);

    CleanGEMGuardData();
    CleanGEMSweepData();

    CFightFormationMgrPtr pFightFormationMgr = _rPlayer.GetFightFormationMgr();
    if(pFightFormationMgr)
    {
        pFightFormationMgr->ClearFormation(EGuardEMei);
    }

    return true;
}

//清除守卫峨眉守卫信息
bool CGuardEMei::CleanGEMGuardData()
{
    SetGuardProgress(0);
    SetGuardMonsterGroupID(0);

    _mapGEMBuff.clear();

    return true;
}

//清除守卫峨眉扫荡信息
bool CGuardEMei::CleanGEMSweepData()
{
    SetSweepLastTime(0);
    SetSweepEndTime(0);
    
    return true;
}

//更新DB
bool CGuardEMei::Update2DB(EDataChange eDataChange)
{
    string strData;
    COutArchive iar(strData);
    SGEMDBInfo oGEMDBInfo;
    oGEMDBInfo.qwRoleID = _rPlayer.GetRoleID();
    oGEMDBInfo.wMissionID = GetMissionID();
    oGEMDBInfo.byGEMType = GetGEMType();
    oGEMDBInfo.wCurProgress = GetCurProgress();
    oGEMDBInfo.wGuardProgress = GetGuardProgress();
    oGEMDBInfo.dwSweepEndTime = GetSweepEndTime();

    string& strBuff = oGEMDBInfo.strBuff;
    MapGEMBuff::iterator iterA = _mapGEMBuff.begin();
    for (; iterA!=_mapGEMBuff.end(); iterA++)
    {
        char strTmp[255];
        sprintf_s(strTmp,"%d,%d|", iterA->second.dwBuffID, iterA->second.dwBuffNum);
        strBuff = strBuff + string(strTmp);
    }

    iar << oGEMDBInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(_rPlayer.GetUserID(), eTypeGuardEMei, eDataChange, strData);

    return true;
}


