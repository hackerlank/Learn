#include "ShushanBattleMgr.h"
#include "ShushanBattle.h"
#include "UserMgr.h"
#include "User.h"
#include "Player.h"
#include "Random.h"
#include "Protocols.h"
#include "FighterManager.h"
#include "GameServerSysMail.h"
#include "HeroFighter.h"
#include "Loot.h"
#include "Battle.h"
#include "GUIDMgr.h"

//蜀山论剑的每场战斗时间
const static UINT32 NCBATTLE_TIME = 45;
//蜀山论剑每个玩家霸气怒气上限值
const static UINT32 MAX_BANUQI = 100;

UINT32 CShushanBattle::_dwPairID = 0;

#define COUNT_LOSEACHIEVE(a,b) (4 + (a + b) / 2)
#define COUNT_WINACHIEVE(a,b,c,d) (4 + a + b + (c + d) * 2)

void SSBPlayerData::SetAllTaskInfo()
{
    //取5个蜀山论剑任务
	ShushanBattleMgr.GetBattleTaskCfg(_vecTaskInfo);
}

UINT8 SSBPlayerData::UpdateTaskInfo(UINT8 byTaskID)
{
    UINT8 byScore = 0;
    UINT8 byTaskCnt = 0;
    if(byTaskID == 0)
        return byScore;
    TVecTaskData::iterator iter = _vecTaskInfo.begin();
    while (iter != _vecTaskInfo.end())
    {
        if (iter->byTaskID == byTaskID)
        {
            if ((*iter).byComplete)
                return byScore;
            iter->byComplete = 1;
            byScore = iter->byAward;
            ++ byTaskCnt;
        }
        ++ iter;
        if (iter->byComplete)
            ++ byTaskCnt;
    }
    if (byScore > 0)
    {   //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(byTaskCnt);
        vecParam.push_back(byTaskID);
        if (GetPlayer())
            GetPlayer()->OnEvent(eEventType_ShushanBattleTaskFinish, vecParam);
    }
    return byScore;
}

bool SSBPlayerData::CanAddSkillFlag(UINT8 bySkillID)
{
    if(bySkillID == 0 || bySkillID > 8)
        return false;
    if((_wSkillFlags & (1 << (bySkillID-1))) != 0)
        return false;
    return true;
}

bool SSBPlayerData::AddAngerDomineer(UINT8 byFlag, UINT8 byValue)
{
    if(byFlag)
    {
        if(_byAnger >= MAX_BANUQI)
            return false;
        _byAnger += byValue;
        if(_byAnger > MAX_BANUQI)
            _byAnger = MAX_BANUQI;
    }
    else
    {
        if(_byDomineer >= MAX_BANUQI)
            return false;
        _byDomineer += byValue;
        if(_byDomineer > MAX_BANUQI)
            _byDomineer = MAX_BANUQI;
    }
    return true;
}

void SSBPlayerData::SetHonorLevel(UINT16 wHonor)
{
    UINT8 byOldLvl = _byHonorLvl;
    _wHonor += wHonor;
    _byHonorLvl = ShushanBattleMgr.CalcHonorLevel(_wHonor);

    if (GetPlayer() && _byHonorLvl > byOldLvl)
    {
        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(_byHonorLvl);
        GetPlayer()->OnEvent(eEventType_ShushanBattleBadgeUpgrade, vecParam);
    }
}

void SSBPlayerData::SendBattleReport()
{
    if (!GetPlayer()) return;
    //暂定发送5个
    TVecSSBattleReport vecBR;
    UINT8 bySize = _vecBattleReport.size();
    if (bySize > 0)
        vecBR.push_back(_vecBattleReport[bySize-1]);
    GetPlayer()->SendPkg(g_ShushanBattleProtS.BuildPkg_BattleReportInfo(0, vecBR));
}

CShushanBattle::CShushanBattle()
{
    _pMap = CMapMgr::CreateMap(ENTER_MAPID);
    _qwJoinByeRoleID = 0;
    _dwExpTime = 0;
    _dwTickTime = 0;
    _qwTopKiller = 0;
    _byTopStreak = 0;
    _qwHonorKing = 0;
    _wMaxHonor = 0;
}

CPlayerPtr CShushanBattle::GetPlayerByRoleID(UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if (!pUser)
        return NULL;
    return pUser->GetPlayer();
}

ESSBattleResult CShushanBattle::PlayerEnter(CPlayerPtr pPlayer)
{
	if (!ShushanBattleMgr.IsRunning())
		return eSSBattle_NotRuning;
	if (!pPlayer || pPlayer->GetLevel() < 30)
		return eSSBattle_LevelLimit;
    SBuffInfo stBuffInfo;
    if (pPlayer->GetBuffData(6, stBuffInfo) == eBORSuccess)
        return eSSBattle_CDTime;
    UINT64 qwRoleID = pPlayer->GetRoleID();
    
    //任务集市需求
    UINT64 qwVar = pPlayer->GetUser().GetVars().GetVar(ePlayerTaskMarket);
    if(!(qwVar & 1))
    {
        qwVar = qwVar | 1;
        pPlayer->GetUser().GetVars().SetVar(ePlayerTaskMarket,qwVar);
    }

    SSBPlayerDataPtr pPlayerData = NULL;
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
    if (iter == _mapSSBPlayerData.end())
    {
        pPlayerData = SSBPlayerDataPtr(new SSBPlayerData);
        pPlayerData->_qwRoleID = qwRoleID;
        pPlayerData->SetAllTaskInfo();

        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(1);
        pPlayer->OnEvent(eEventType_ShushanBattleJoin, vecParam);
    }
    else
        pPlayerData = iter->second;
    pPlayerData->_byType = eSSBattle_ENTER;
    pPlayerData->SetHonorLevel();
    _mapSSBPlayerData[qwRoleID] = pPlayerData;
    
    PlayerEnterInSpecialTime(pPlayer);
    SendSelfInfo(pPlayer);
    return eSSBattle_Suc;
}

void CShushanBattle::PlayerEnterInSpecialTime(CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return;
    CGameMapPtr pFightMap = NULL;
    UINT64 qwOtherID = 0;
    UINT64 qwRoleID = pPlayer->GetRoleID();
    UINT32 dwCurtime = time(NULL);
    UINT32 dwStartTime = ShushanBattleMgr.GetStartTime();
    bool bNeedPair = false;
    if (dwCurtime > dwStartTime && dwCurtime < _dwTickTime)
    {   //处理在一个轮回内新加入的玩家
        PairPlayerInfo * pPairInfo = FindPairInfoByRoleID(qwRoleID);
        if (!pPairInfo)
            bNeedPair = true;
        else
            pFightMap = pPairInfo->_pFightMap;
    }
    else
        pFightMap = _pMap;
    if (bNeedPair)
    {   //配对or轮空
        if (_qwJoinByeRoleID == 0)
        {
            SetJoinByeRoleID(qwRoleID);
            pFightMap = CMapMgr::CreateMap(FIGHT_MAPID);
        }
        else
        {
            if (qwRoleID != _qwJoinByeRoleID)
            {
                qwOtherID = _qwJoinByeRoleID;
                SetJoinByeRoleID(0);
                UINT32 dwPairID = GetPairID();
                PairPlayerInfo * pPairInfo = FindPairInfoByPairID(dwPairID);
                if (pPairInfo)
                {
                    pPairInfo->SetRoleID(qwRoleID, qwOtherID);
                    pFightMap = pPairInfo->_pFightMap;
                }
                else
                {
                    PairPlayerInfo oPairPlayerInfo(qwRoleID, qwOtherID);
                    _mapPairPlayerInfo.insert(std::make_pair(dwPairID, oPairPlayerInfo));
                    pFightMap = oPairPlayerInfo._pFightMap;
                }
                SendSelfInfo(GetPlayerByRoleID(qwOtherID));
            }
            else
                pFightMap = CMapMgr::CreateMap(FIGHT_MAPID);
        }
    }
    if (pFightMap)
    {   //玩家跳地图场景
        SPoint oPoint;
        SPoint oRealPoint = pFightMap->GetRealivePoint();
        pFightMap->GetMovablePoint(oRealPoint, oPoint);
        if(!pPlayer->JumpMap(pFightMap, oPoint))
            LOG_CRI << "player jump map error in enter shushanBattle! qwRoleID:" << qwRoleID << ", MapID:" << pFightMap->GetMapID();
        if (qwOtherID)
        {
            CUserMgr::LoadUser(qwOtherID,[this, pFightMap, oRealPoint](CUserPtr pUser) mutable{
                    if (pUser && pUser->GetPlayer() && pFightMap)
                    {
                        SPoint oPoint;
                        pFightMap->GetMovablePoint(oRealPoint, oPoint);
                        pUser->GetPlayer()->JumpMap(pFightMap, oPoint);
                    }
                    });
        }
    }
}

ESSBattleResult CShushanBattle::PlayerLeave(CPlayerPtr pPlayer)
{
	if (!pPlayer || !ShushanBattleMgr.IsRunning())
		return eSSBattle_NotRuning;
    UINT32 dwCurtime = time(NULL);
    UINT64 qwRoleID = pPlayer->GetRoleID();
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
    if(iter == _mapSSBPlayerData.end())
        return eSSBattle_NotEnter;
    SSBPlayerDataPtr pPlayerData = iter->second;
    if(pPlayerData->IsQuit() || pPlayerData->_byType == 0xFF)
        return eSSBattle_NotEnter;
    pPlayerData->_byType = eSSBattle_QUIT;
    pPlayerData->_wSkillFlags = 0;
    pPlayerData->SetHonorLevel();
    pPlayer->RegenAllHP();
    if (_qwJoinByeRoleID == qwRoleID)
        SetJoinByeRoleID(0);
    if (dwCurtime >= ShushanBattleMgr.GetStartTime() && dwCurtime < ShushanBattleMgr.GetEndedTime())
        pPlayer->AddBuff(6);
    pPlayer->GetFighterManager()->SetDirty(eAttrGpShushanBattle);

    CGameMapPtr pInitMap = CMapMgr::GetMap(INIT_MAPID);
    if (pInitMap)
    {
        SPoint oPoint = pInitMap->GetRealivePoint();
        pPlayer->JumpMap(pInitMap, oPoint);
    }
    return eSSBattle_Suc;
}

ESSBattleResult CShushanBattle::UseSkill(CPlayerPtr pPlayer, UINT8 bySkillID)
{
    if (!pPlayer || !ShushanBattleMgr.IsRunning())
        return eSSBattle_NotRuning;
    UINT64 qwRoleID = pPlayer->GetRoleID();
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
    if (iter == _mapSSBPlayerData.end())
        return eSSBattle_NotEnter;
    SSBPlayerDataPtr pPlayerData = iter->second;
    if (!pPlayerData->CanAddSkillFlag(bySkillID))
        return eSSBattle_Used;
    SBattleSkillCFGEx* pBattleSkillCfg = ShushanBattleMgr.GetBattleSkillCfg(bySkillID);
    if (!pBattleSkillCfg)
        return eSSBattle_OtherErr;
    UINT8 byPrice = pBattleSkillCfg->_Cost;
    if (!pBattleSkillCfg->_CostType)
    {
        if(pPlayerData->_byDomineer < byPrice)
            return eSSBattle_NotEnough;
        pPlayerData->_byDomineer -= byPrice;
    }
    else
    {
        if(pPlayerData->_byAnger < byPrice)
            return eSSBattle_NotEnough;
        pPlayerData->_byAnger -= byPrice;
    }
    pPlayerData->SetSkillFlag(bySkillID);
    pPlayer->GetFighterManager()->SetDirty(eAttrGpShushanBattle);
    if (bySkillID == 4)     //春风花雨 加散仙当前血量
        pPlayer->AddCurrHPPer(pBattleSkillCfg->_vecAddAttr[EFIGHTATTR_MAXHP_PER]);

    UINT16 wAward = pPlayerData->UpdateTaskInfo(pBattleSkillCfg->_TaskId);
    if (wAward)
        pPlayerData->SetHonorLevel(wAward);
    SendSelfInfo(pPlayer, pPlayerData);

    SSSBattleUseSkill stUseSkill;
    stUseSkill.qwRoleID = qwRoleID;
    stUseSkill.wHonor = pPlayerData->_wHonor;
    stUseSkill.wSkillFlags = pPlayerData->_wSkillFlags;
    stUseSkill.dwCurHp = pPlayer->GetCurrHP();
    string strData = g_ShushanBattleProtS.BuildPkg_UseSkillInfo(stUseSkill);
    //pPlayer->SendPkg(strData);
    CPlayerPtr pPlayerOther = GetPlayerByRoleID(FindPairPlayer(qwRoleID));
    if (pPlayerOther)
        pPlayerOther->SendPkg(strData);

    //Event事件
    TVecINT32 vecParam;
    vecParam.push_back(bySkillID);
    pPlayer->OnEvent(eEventType_ShushanBattleSkillUsing, vecParam);
    return eSSBattle_Suc;
}

ESSBattleResult CShushanBattle::BuySkill(CPlayerPtr pPlayer, UINT8 byFlag)
{
    if (!pPlayer || (byFlag != 0 && byFlag != 1))
        return eSSBattle_OtherErr;
    if (!ShushanBattleMgr.IsRunning())
        return eSSBattle_NotRuning;
    UINT64 qwRoleID = pPlayer->GetRoleID();
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
    if (iter == _mapSSBPlayerData.end())
        return eSSBattle_NotEnter;
    if (!pPlayer->GetUserPtr()->CanSubMoney(EMONEY_GOLD, 5))
        return eSSBattle_LackMoney;
    SSBPlayerDataPtr pPlayerData = iter->second;
    if (!pPlayerData)
        return eSSBattle_OtherErr;
    if (!pPlayerData->AddAngerDomineer(byFlag, 50))
        return eSSBattle_Full;
    pPlayer->GetUserPtr()->SubMoney(EMONEY_GOLD, 5,NLogDataDefine::ItemTo_BattleBuySkill);
    return eSSBattle_Suc;
}

void CShushanBattle::CheckAddExp(UINT32 dwCurtime)
{
    if (_dwExpTime > dwCurtime)
        return;
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin();
    while (iter != _mapSSBPlayerData.end())
    {
        //计算经验
        if (!iter->second->IsQuit() && iter->second->_qwRoleID)
        {
            CUserMgr::LoadUser(iter->second->_qwRoleID,[this](CUserPtr pUser){
                    if (!pUser || !pUser->GetPlayer())
                        return;
                    /*
                    UINT8 bylvl = pUser->GetLevel();
                    UINT32 dwExp = 16 * ((bylvl - 10) * ((bylvl > 99 ? 99 : bylvl) / 10) * 5 + 25);
                    pUser->GetPlayer()->AddExp(dwExp);
                    */
                    SBattleExpCFGEx* pBattleExpCfg = ShushanBattleMgr.GetBattleExpCfg(pUser->GetLevel());
                    if (pBattleExpCfg)
                        pUser->GetPlayer()->AddExp(pBattleExpCfg->_ExpAward*4);
                    });
        }
        ++ iter;
    }
    _dwExpTime += 60;
}

void CShushanBattle::AllotPlayers()
{
    for(UINT8 bylvl = MAX_ACHLEVEL; bylvl > 0; --bylvl)
    {
        _vecAllPlayers[bylvl-1].clear();
    }
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin();
    while(iter != _mapSSBPlayerData.end())
    {
        for(UINT8 bylvl = MAX_ACHLEVEL; bylvl > 0; --bylvl)
        {
            SSBPlayerDataPtr pPlayerData = iter->second;
            if (pPlayerData->_byHonorLvl == bylvl && !pPlayerData->IsQuit())
            {
                _vecAllPlayers[bylvl-1].push_back(iter->first);
                break;
            }
        }
        ++ iter;
    }
}

void CShushanBattle::MakePairPlayers()
{
    SetJoinByeRoleID(0);
    for(UINT8 bylvl = MAX_ACHLEVEL; bylvl > 0; --bylvl)
    {
        UINT64 qwRoleID1 = 0;
        UINT64 qwRoleID2 = 0;
        while(_vecAllPlayers[bylvl-1].size())
        {
            UINT32 dwCount = _vecAllPlayers[bylvl-1].size();
            if (dwCount <= 0) break;
            if (dwCount == 1)
            {
                qwRoleID1 = _vecAllPlayers[bylvl-1][0];
                _vecAllPlayers[bylvl-1].clear();
                if(bylvl > 1)
                    _vecAllPlayers[bylvl-2].push_back(qwRoleID1);
                else
                    SetJoinByeRoleID(qwRoleID1);
                break;
            }
            UINT32 dwRand = CRandom::RandInt(0, dwCount-1);
            qwRoleID1 = _vecAllPlayers[bylvl-1][dwRand];
            _vecAllPlayers[bylvl-1].erase(_vecAllPlayers[bylvl-1].begin() + dwRand);
            
            dwCount = _vecAllPlayers[bylvl-1].size();
            dwRand = CRandom::RandInt(0, dwCount-1);
            qwRoleID2 = _vecAllPlayers[bylvl-1][dwRand];
            _vecAllPlayers[bylvl-1].erase(_vecAllPlayers[bylvl-1].begin() + dwRand);

            UINT32 dwPairID = GetPairID();
            PairPlayerInfo * pPairInfo = FindPairInfoByPairID(dwPairID);
            if (pPairInfo)
                pPairInfo->SetRoleID(qwRoleID1, qwRoleID2);
            else
            {
                PairPlayerInfo oPairPlayerInfo(qwRoleID1, qwRoleID2);
                _mapPairPlayerInfo.insert(std::make_pair(dwPairID, oPairPlayerInfo));
            }
        }
    }
    for(TMapPairPlayerInfo::iterator iter = _mapPairPlayerInfo.begin(); iter != _mapPairPlayerInfo.end(); ++iter)
    {
        UINT64 qwAtkerID = iter->second._qwAtkerRoleID;
        UINT64 qwDeferID = iter->second._qwDeferRoleID;
        CGameMapPtr pFightMap = iter->second._pFightMap;
        if (!pFightMap || !qwAtkerID || !qwDeferID)
            continue;
        CUserMgr::LoadUser(qwAtkerID,[this, pFightMap](CUserPtr pAtkUser) mutable{
                if (pAtkUser && pAtkUser->GetPlayer() && pFightMap)
                {
                    //玩家跳地图场景
                    SPoint oPoint = pFightMap->GetRealivePoint();
                    if(!pAtkUser->GetPlayer()->JumpMap(pFightMap, oPoint))
                        LOG_CRI << "player jump map error in shushanBattle! qwRoleID:" << pAtkUser->GetUserID() << ", MapID:" << pFightMap->GetMapID();
                }
                });

        CUserMgr::LoadUser(qwDeferID,[this, pFightMap](CUserPtr pDefUser) mutable{
                if (pDefUser && pDefUser->GetPlayer() && pFightMap)
                {
                    //玩家跳地图场景
                    SPoint oPoint;
                    SPoint oRealPoint = pFightMap->GetRealivePoint();
                    pFightMap->GetMovablePoint(oRealPoint, oPoint);
                    if(!pDefUser->GetPlayer()->JumpMap(pFightMap, oPoint))
                        LOG_CRI << "player jump map error in shushanBattle! qwRoleID:" << pDefUser->GetUserID() << ", MapID:" << pFightMap->GetMapID();
                }
                });

    }
    if (_qwJoinByeRoleID)
    {
        CUserMgr::LoadUser(_qwJoinByeRoleID,[this](CUserPtr pUser){
                if (pUser && pUser->GetPlayer())
                {
                    //玩家跳地图场景
                    CGameMapPtr pFightMap = CMapMgr::CreateMap(FIGHT_MAPID);
                    if (!pFightMap) return;
                    SPoint oPoint = pFightMap->GetRealivePoint();
                    if(!pUser->GetPlayer()->JumpMap(pFightMap, oPoint))
                        LOG_CRI << "player jump map error in shushanBattle! qwRoleID:" << pUser->GetUserID() << ", MapID:" << pFightMap->GetMapID();
                }
                });
    }
}

UINT64 CShushanBattle::FindPairPlayer(UINT64 qwRoleID)
{
    UINT64 qwOtherID = 0;
    TMapPairPlayerInfo::iterator iter = _mapPairPlayerInfo.begin();
    while(iter != _mapPairPlayerInfo.end())
    {
        if (iter->second._qwAtkerRoleID == qwRoleID) 
        {
            qwOtherID = iter->second._qwDeferRoleID;
            break;
        }
        else if (iter->second._qwDeferRoleID == qwRoleID) 
        {
            qwOtherID = iter->second._qwAtkerRoleID;
            break;
        }
        ++iter;
    }
    return qwOtherID;
}

PairPlayerInfo * CShushanBattle::FindPairInfoByRoleID(UINT64 qwRoleID)
{
    TMapPairPlayerInfo::iterator iter = _mapPairPlayerInfo.begin();
    while(iter != _mapPairPlayerInfo.end())
    {
        if (iter->second._qwAtkerRoleID == qwRoleID)
            return &(iter->second);
        else if (iter->second._qwDeferRoleID == qwRoleID)
            return &(iter->second);
        ++iter;
    }
    return NULL;
}

PairPlayerInfo * CShushanBattle::FindPairInfoByPairID(UINT32 dwPairID)
{
    TMapPairPlayerInfo::iterator iter = _mapPairPlayerInfo.find(dwPairID);
    if (iter != _mapPairPlayerInfo.end())
        return &(iter->second);
    return NULL;
}

void CShushanBattle::JoinBye()
{   //轮空
    if (!_qwJoinByeRoleID)
        return;
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(_qwJoinByeRoleID);
    if (iter == _mapSSBPlayerData.end())
        return;
    SSBPlayerDataPtr pPlayerData = iter->second;
    pPlayerData->_byType = eSSBattle_JOINBYE;
    pPlayerData->SetHonorLevel(8);

    CUserMgr::LoadUser(_qwJoinByeRoleID,[this,pPlayerData](CUserPtr pUser){
            if (!pPlayerData || !pUser || !pUser->GetPlayer())
                return;

            pPlayerData->_pPlayer = pUser->GetPlayer();
            CompleteTask1(pPlayerData);
            SSSBattleReport stBR;
            stBR.byRound    = GetRound() > 1 ? GetRound()-1 : 0;
            stBR.strNameA   = pUser->GetPlayer()->GetName();
            stBR.qwRoleA    = pUser->GetUserID();
            stBR.strNameB   = "";
            stBR.qwRoleB    = 0;
            stBR.byResult   = 4;
            stBR.qwBattleID = 0;
            stBR.byCurrKill = pPlayerData->_byCurrKill;
            stBR.wHonor     = 8;
            pPlayerData->_vecBattleReport.push_back(stBR);
            pPlayerData->SendBattleReport();
            this->_vecSSBattleReport.push_back(stBR);
            });
}

void CShushanBattle::Process(UINT32 dwCurtime)
{
    UINT32 dwStartTime = ShushanBattleMgr.GetStartTime();
    if (dwStartTime == 0)
        return;
    if (_dwExpTime)
        CheckAddExp(dwCurtime);
    UINT8 byCorr = (dwCurtime - dwStartTime) / NCBATTLE_TIME;
    if (!_dwExpTime)
        _dwExpTime = dwStartTime + byCorr * NCBATTLE_TIME + 60;
    if (!_dwTickTime)
    {   
        _dwTickTime = dwStartTime + (byCorr + 1) * NCBATTLE_TIME;
        //开始时配对
        AllotPlayers();
        MakePairPlayers();
        SendAllInfo();
    }
    if (dwCurtime < _dwTickTime)
        return;
    _dwTickTime += NCBATTLE_TIME;

    HandleBattle();     //战斗
    if (dwCurtime >= ShushanBattleMgr.GetEndedTime())
    {
        UpdateFirst();
        SendAllInfo();
        End();
        return;
    }
    AllotPlayers();     //重新分配玩家
    MakePairPlayers();  //配对玩家
    UpdateFirst();      //广播荣誉王连胜王
    SendAllInfo();      //发送所有玩家的个人数据
}

void CShushanBattle::Prepare()
{
    _dwExpTime = 0;
    _dwTickTime = 0;
    _qwTopKiller = 0;
    _byTopStreak = 0;
    _qwHonorKing = 0;
    _wMaxHonor = 0;
    _qwJoinByeRoleID = 0;
    for(UINT8 bylvl = MAX_ACHLEVEL; bylvl > 0; --bylvl)
    {
        _vecAllPlayers[bylvl-1].clear();
    }
    /*
    for(TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin(); iter != _mapSSBPlayerData.end(); ++ iter)
    {
        delete iter->second;
    }
    */
    _mapSSBPlayerData.clear();
}

void CShushanBattle::End()
{
    SPoint oRealPoint;
    CGameMapPtr pInitMap = CMapMgr::GetMap(INIT_MAPID);
    if (pInitMap)
    {
        oRealPoint = pInitMap->GetRealivePoint();
    }
    for(TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin(); iter != _mapSSBPlayerData.end(); ++ iter)
    {
        SSBPlayerDataPtr pPlayerData = iter->second;
        if (!pPlayerData)
            continue;
        SBattleAwardCFGEx* pBattleAwardCfg = ShushanBattleMgr.GetBattleAwardCfg(pPlayerData->_byHonorLvl);
        if (!pBattleAwardCfg)
            continue;
        UINT8 byCount = 0;
        TVecTaskData::iterator it = pPlayerData->_vecTaskInfo.begin();
        while(it != pPlayerData->_vecTaskInfo.end())
        {
            if ((*it).byComplete)
                ++ byCount;
            ++ it;
        }
        UINT16 wHonor = 0;
        TVecItemGenInfo vecItems = pBattleAwardCfg->_vecItemGenInfo;
        for (size_t i = 0; i < vecItems.size(); ++ i)
        {
            if (vecItems[i].wItemID == 6)  //XXX 改为奖励声望，非荣誉！！
            {
                vecItems[i].dwCount += pPlayerData->_wHonor;
                wHonor = vecItems[i].dwCount;
                break;
            }
        }
        if (0 == wHonor)     //XXX 防止策划把声望奖励配错！！
        {
            wHonor = pPlayerData->_wHonor;
            SItemGenInfo stItemGen;
            stItemGen.wItemID = 6;
            stItemGen.dwCount = pPlayerData->_wHonor;
            stItemGen.eBindType = eBindGet;
            vecItems.push_back(stItemGen);
        }
        //发送邮件
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_SHUSHANBATTLE;
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byTotalWin));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byTotalLose));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byMaxKill));
        stBody.vecParam.push_back(NumberToString(byCount));
        stBody.vecParam.push_back(NumberToString(wHonor));
        stBody.vecParam.push_back(NumberToString(pPlayerData->_byHonorLvl));
        TVecUINT64 vecTargets;
        vecTargets.push_back(iter->first);
        GameServerSysMail::SendSysMail(SEND_SHUSHANBATTLE, TITLE_SHUSHANBATTLE, stBody, vecTargets, &vecItems);

        if (!pPlayerData->IsQuit())
        {
            CUserMgr::LoadUser(iter->first,[this, pInitMap, oRealPoint](CUserPtr pUser) mutable{
                    if (!pUser || !pUser->GetPlayer() || !pInitMap)
                        return;
                    SPoint oPoint;
                    pInitMap->GetMovablePoint(oRealPoint, oPoint);
                    pUser->GetPlayer()->JumpMap(pInitMap, oPoint);
                    pUser->GetPlayer()->RegenAllHP();
                    pUser->GetPlayer()->SendPkg(g_ShushanBattleProtS.BuildPkg_BattleStartInfo(2, 0));
                    });
        }
        
        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(1);

        if (pPlayerData->GetPlayer())
        {
            pPlayerData->GetPlayer()->OnEvent(eEventType_ShushanBattleGetPrize, vecParam);
        }
        else
        {
            string strParam;
            CPlayer::AddOffLineEvent(iter->first,eEventType_ShushanBattleGetPrize,vecParam,strParam);
        }

    }
    SendFirstAward();
}

void CShushanBattle::SendFirstAward()
{
    //连杀王奖励
    if (_qwTopKiller)
    {
        TVecResource vecRes;
        TVecItemGenInfo vecItems;
        LOOT.Roll(SParamConfig::wShushanBattleAward1, vecItems, vecRes);
        for (size_t i = 0; i < vecRes.size(); ++ i)
        {
            SItemGenInfo stItemGen;
            stItemGen.wItemID = vecRes[i]._eRes;
            stItemGen.dwCount = vecRes[i]._dwValue;
            stItemGen.eBindType = eBindGet;
            vecItems.push_back(stItemGen);
        }

        //发送邮件
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_SSBTOPKILLER;
        TVecUINT64 vecTargets;
        vecTargets.push_back(_qwTopKiller);
        GameServerSysMail::SendSysMail(SEND_SSBTOPKILLER, TITLE_SSBTOPKILLER, stBody, vecTargets, &vecItems);
      
        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(2);

        CPlayerPtr pPlayer = GetPlayerByRoleID(_qwTopKiller);
        if (pPlayer)
        {
            pPlayer->OnEvent(eEventType_ShushanBattleGetPrize, vecParam);
            //世界广播
            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgShushanLunjianKiller,vecstring);
        }
        else
        {
            string strParam;
            CPlayer::AddOffLineEvent(_qwTopKiller,eEventType_ShushanBattleGetPrize,vecParam,strParam);
        }
    }
    //荣誉王奖励
    if (_qwHonorKing)
    {
        TVecResource vecRes;
        TVecItemGenInfo vecItems;
        LOOT.Roll(SParamConfig::wShushanBattleAward2, vecItems, vecRes);
        for (size_t i = 0; i < vecRes.size(); ++ i)
        {
            SItemGenInfo stItemGen;
            stItemGen.wItemID = vecRes[i]._eRes;
            stItemGen.dwCount = vecRes[i]._dwValue;
            stItemGen.eBindType = eBindGet;
            vecItems.push_back(stItemGen);
        }

        //发送邮件
        NMailProt::SysMailSendTxt stBody;
        stBody.dwstrMsgID = BODY_SSBHONORKING;
        TVecUINT64 vecTargets;
        vecTargets.push_back(_qwHonorKing);
        GameServerSysMail::SendSysMail(SEND_SSBHONORKING, TITLE_SSBHONORKING, stBody, vecTargets, &vecItems);
            
        //Event事件
        TVecINT32 vecParam;
        vecParam.push_back(3);
 
        CPlayerPtr pPlayer = GetPlayerByRoleID(_qwHonorKing);
        if (pPlayer)
        {
           pPlayer->OnEvent(eEventType_ShushanBattleGetPrize, vecParam);
            //世界广播
            TVecString vecstring;
            vecstring.push_back(NumberToString(pPlayer->GetColor()));
            vecstring.push_back(pPlayer->GetName());
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgShushanLunjianHonor,vecstring);
        }
        else
        {
            string strParam;
            CPlayer::AddOffLineEvent(_qwHonorKing,eEventType_ShushanBattleGetPrize,vecParam,strParam);
        }
    }
}

void CShushanBattle::SendAllInfo()
{
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin();
    while(iter != _mapSSBPlayerData.end())
    {
        SendSelfInfo(GetPlayerByRoleID(iter->first), iter->second);
        ++ iter;
    }
}

void CShushanBattle::SendSelfInfo(CPlayerPtr pPlayer)
{
    if (!pPlayer)
        return;
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(pPlayer->GetRoleID());
    if (iter != _mapSSBPlayerData.end() && !iter->second->IsQuit())
        SendSelfInfo(pPlayer, iter->second);
    else
    {   //与客户端约定的
    }
}

void CShushanBattle::SendSelfInfo(CPlayerPtr pPlayer, SSBPlayerDataPtr pPlayerData)
{   //更新个人数据(下一轮)
    if (!pPlayer || !pPlayerData || pPlayerData->IsQuit()) //已退出玩家
        return;
    UINT8 byRound = 0;
    UINT16 wTimeLeft = 0;
    UINT32 dwCurtime = time(NULL);
    UINT32 dwStartTime = ShushanBattleMgr.GetStartTime();
    if (_dwTickTime)
    {
        byRound   = (_dwTickTime - dwStartTime) / NCBATTLE_TIME;
        wTimeLeft = _dwTickTime - dwCurtime;
    }
    else
    {
        if (dwCurtime > dwStartTime)  //预防宕机,纠正时间
        {
            byRound   = (dwCurtime - dwStartTime) / NCBATTLE_TIME;
            wTimeLeft = (byRound + 1) * NCBATTLE_TIME + dwStartTime - dwCurtime; 
        }
        else
            wTimeLeft = dwStartTime - dwCurtime;
    }

    SSSBattlePairInfo stPairInfo;
    stPairInfo.byRound       = byRound;
    stPairInfo.wTimeLeft     = wTimeLeft;
    stPairInfo.byCurrKill    = pPlayerData->_byCurrKill;
    stPairInfo.byMaxKill     = pPlayerData->_byMaxKill;
    stPairInfo.byTotalWin    = pPlayerData->_byTotalWin;
    stPairInfo.byTotalLose   = pPlayerData->_byTotalLose;
    stPairInfo.wHonor        = pPlayerData->_wHonor;
    stPairInfo.byDomineer    = pPlayerData->_byDomineer;
    stPairInfo.byAnger       = pPlayerData->_byAnger;
    stPairInfo.wSkillFlags   = pPlayerData->_wSkillFlags;
    stPairInfo.vecTaskData   = pPlayerData->_vecTaskInfo;
    stPairInfo.dwMaxHp       = pPlayer->GetMaxHP2();
    stPairInfo.dwCurHp       = pPlayer->GetCurrHP();
    stPairInfo.dwBattlePower = pPlayer->GetBattlePoint();

    UINT64 qwOtherID = FindPairPlayer(pPlayer->GetRoleID());
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwOtherID);
    if (iter == _mapSSBPlayerData.end() || iter->second->IsQuit() || !qwOtherID)
    {   //轮空
        pPlayer->SendPkg(g_ShushanBattleProtS.BuildPkg_PlayerPairInfo(stPairInfo));
        return;
    }
    SSBPlayerDataPtr pPDDefer = iter->second;
    CUserMgr::LoadUser(qwOtherID,[this, pPlayer, pPDDefer, stPairInfo](CUserPtr pUser) mutable {
            if (pUser && pUser->GetPlayer() && pPDDefer && pPDDefer)
            {
                SOtherPlayer stOtherPlayer;
                SPlayerAppear appear;
                pUser->GetPlayer()->GetPlayerAppear(appear);
                stOtherPlayer.rPlayerAppear      = appear;
                stOtherPlayer.qwRoleIDOther      = pUser->GetPlayer()->GetRoleID();
                stOtherPlayer.dwMaxHpOther       = pUser->GetPlayer()->GetMaxHP2();
                stOtherPlayer.dwCurHpOther       = pUser->GetPlayer()->GetCurrHP();
                stOtherPlayer.byCurrKillOther    = pPDDefer->_byCurrKill;
                stOtherPlayer.wHonorOther        = pPDDefer->_wHonor;
                stOtherPlayer.wSkillFlagsOther   = pPDDefer->_wSkillFlags;
                stOtherPlayer.dwBattlePowerOther = pUser->GetPlayer()->GetBattlePoint();
                stPairInfo.vecOtherPlayer.push_back(stOtherPlayer);
            }
            if (pPlayer)
                pPlayer->SendPkg(g_ShushanBattleProtS.BuildPkg_PlayerPairInfo(stPairInfo));
            });
}

void CShushanBattle::UpdateFirst()
{   //广播连胜王与荣誉王
    bool bBroadTop = false;
    bool bBroadHonor = false;
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin();
    for(; iter != _mapSSBPlayerData.end(); ++ iter)
    {
        if (iter->second->_byCurrKill > _byTopStreak)
        {
            _qwTopKiller = iter->first;
            _byTopStreak = iter->second->_byCurrKill;
            bBroadTop = true;
        }
        if (iter->second->_wHonor > _wMaxHonor)
        {
            _qwHonorKing = iter->first;
            _wMaxHonor = iter->second->_wHonor;
            bBroadHonor = true;
        }
    }
    if (bBroadTop && _qwTopKiller)
    {   //广播连胜王
        CUserMgr::LoadUser(_qwTopKiller,[this](CUserPtr pUser){
                if (!pUser || !pUser->GetPlayer())
                    return;

                string strData = g_ShushanBattleProtS.BuildPkg_TopKiller(pUser->GetPlayer()->GetName(), _byTopStreak);
                TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin();
                for(; iter != _mapSSBPlayerData.end(); ++ iter)
                {
                    CPlayerPtr pPlayer = GetPlayerByRoleID(iter->first);
                    if (pPlayer && !iter->second->IsQuit())
                        pPlayer->SendPkg(strData);
                }
                });
    }

    if (bBroadHonor && _qwHonorKing)
    {   //广播荣誉王
        CUserMgr::LoadUser(_qwHonorKing,[this](CUserPtr pUser){
                if (!pUser || !pUser->GetPlayer())
                    return;

                string strData = g_ShushanBattleProtS.BuildPkg_HonorKinger(pUser->GetPlayer()->GetName(), _wMaxHonor);
                TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.begin();
                for(; iter != _mapSSBPlayerData.end(); ++ iter)
                {
                    CPlayerPtr pPlayer = GetPlayerByRoleID(iter->first);
                    if (pPlayer && !iter->second->IsQuit())
                        pPlayer->SendPkg(strData);
                }
                });
    }
}

void CShushanBattle::GetFirstPlayer(CPlayerPtr pPlayer)
{   //获取连胜王与荣誉王
    if (!pPlayer || !ShushanBattleMgr.IsRunning())
        return;
    if (_qwTopKiller)
    {
        CUserMgr::LoadUser(_qwTopKiller,[this, pPlayer](CUserPtr pUser){
                string strName;
                if (pUser && pUser->GetPlayer())
                    strName = pUser->GetPlayer()->GetName();

                string strData = g_ShushanBattleProtS.BuildPkg_TopKiller(strName, _byTopStreak);
                if (pPlayer)
                    pPlayer->SendPkg(strData);
                });
    }

    if (_qwHonorKing)
    {
        CUserMgr::LoadUser(_qwHonorKing,[this, pPlayer](CUserPtr pUser){
                string strName;
                if (pUser && pUser->GetPlayer())
                    strName = pUser->GetPlayer()->GetName();

                string strData = g_ShushanBattleProtS.BuildPkg_HonorKinger(strName, _wMaxHonor);
                if (pPlayer)
                    pPlayer->SendPkg(strData);
                });
    }
}

bool CShushanBattle::IsRunAway(SSBPlayerDataPtr pPDAtker, SSBPlayerDataPtr pPDDefer)
{
    if (pPDAtker->IsQuit() && pPDDefer->IsQuit())
        return true;
    SSSBattleReport stBR;
    stBR.strNameA   = pPDAtker->GetPlayer()->GetName();
    stBR.qwRoleA    = pPDAtker->GetPlayer()->GetRoleID();
    stBR.strNameB   = pPDDefer->GetPlayer()->GetName();
    stBR.qwRoleB    = pPDDefer->GetPlayer()->GetRoleID();
    stBR.qwBattleID = 0;
    stBR.byRound    = GetRound() > 1 ? GetRound()-1 : 0;

    UINT8 byHonorLvl1 = pPDAtker->_byHonorLvl;
    UINT8 byKill1 = pPDAtker->_byCurrKill;
    UINT8 byHonorLvl2 = pPDDefer->_byHonorLvl;
    UINT8 byKill2 = pPDDefer->_byCurrKill;
    UINT16 wWinHonor = 0;
    if (pPDAtker->IsQuit())
    {   //玩家1逃跑,玩家2胜利
        pPDDefer->_byCurrKill ++;
        pPDDefer->_byTotalWin ++;
        if (pPDDefer->_byCurrKill > pPDDefer->_byMaxKill)
            pPDDefer->_byMaxKill = pPDDefer->_byCurrKill;
        byKill2 = pPDDefer->_byCurrKill > 10 ? 10 : pPDDefer->_byCurrKill;
        wWinHonor = COUNT_WINACHIEVE(byKill1, byKill2, byHonorLvl1, byHonorLvl2);
        pPDDefer->SetHonorLevel(wWinHonor);
        pPDDefer->AddAngerDomineer(0, 5);
        //Event事件
        if (pPDDefer->GetPlayer())
        {
            TVecINT32 vecParam;
            vecParam.push_back(pPDDefer->_byCurrKill);
            pPDDefer->GetPlayer()->OnEvent(eEventType_ShushanBattleWinStreak, vecParam);

            vecParam.clear();
            vecParam.push_back(pPDDefer->_byTotalWin);
            for (int i = 1; i <= 8; ++ i)
            {
                if ((pPDDefer->_wSkillFlags >> (i-1)) & 1)
                    vecParam.push_back(i);
            }
            pPDDefer->GetPlayer()->OnEvent(eEventType_ShushanBattleVictory, vecParam);
        }
        pPDDefer->_wSkillFlags = 0;
        CompleteTask(pPDDefer, pPDAtker);

        stBR.byResult   = 2;
        stBR.byCurrKill = pPDDefer->_byCurrKill;
        stBR.wHonor     = wWinHonor;
        pPDDefer->_vecBattleReport.push_back(stBR);
        pPDDefer->SendBattleReport();
        this->_vecSSBattleReport.push_back(stBR);
        return true;
    }
    if (pPDDefer->IsQuit())
    {   //玩家2逃跑,玩家1胜利
        pPDAtker->_byCurrKill ++;
        pPDAtker->_byTotalWin ++;
        if (pPDAtker->_byCurrKill > pPDAtker->_byMaxKill)
            pPDAtker->_byMaxKill = pPDAtker->_byCurrKill;
        byKill1 = pPDAtker->_byCurrKill > 10 ? 10 : pPDAtker->_byCurrKill;
        wWinHonor = COUNT_WINACHIEVE(byKill1, byKill2, byHonorLvl1, byHonorLvl2);
        pPDAtker->SetHonorLevel(wWinHonor);
        pPDAtker->AddAngerDomineer(0, 5);
        //Event事件
        if (pPDAtker->GetPlayer())
        {
            TVecINT32 vecParam;
            vecParam.push_back(pPDAtker->_byCurrKill);
            pPDAtker->GetPlayer()->OnEvent(eEventType_ShushanBattleWinStreak, vecParam);

            vecParam.clear();
            vecParam.push_back(pPDAtker->_byTotalWin);
            for (int i = 1; i <= 8; ++ i)
            {
                if ((pPDAtker->_wSkillFlags >> (i-1)) & 1)
                    vecParam.push_back(i);
            }
            pPDAtker->GetPlayer()->OnEvent(eEventType_ShushanBattleVictory, vecParam);
        }
        pPDAtker->_wSkillFlags = 0;
        CompleteTask(pPDAtker, pPDDefer);

        stBR.byResult   = 3;
        stBR.byCurrKill = pPDAtker->_byCurrKill;
        stBR.wHonor     = wWinHonor;
        pPDAtker->_vecBattleReport.push_back(stBR);
        pPDAtker->SendBattleReport();
        this->_vecSSBattleReport.push_back(stBR);
        return true;
    }
    return false;
}

bool CShushanBattle::Challenge(CPlayerPtr pPlayer1, CPlayerPtr pPlayer2, SSSBattleReport& stBR)
{
    if (!pPlayer1 || !pPlayer2)
        return false;
    IBattleSimulatorPtr pBS = CreateBattleSimulator(GET_GUID(GUID_BATTLE));
    TVecBattleFighterPtr vecBattleFighter;
    pPlayer1->GetBattleFighterList(vecBattleFighter);

    TVecBattleFighterPtr vecBattleFighter2;
    pPlayer2->GetBattleFighterList(vecBattleFighter2);
    pBS->PutFighters(0, pPlayer1->GetMainFighter()->GetInstID(), pPlayer1->GetLevel(), vecBattleFighter, pPlayer1->GetRoleID(), false);
    pBS->PutFighters(1, pPlayer2->GetMainFighter()->GetInstID(), pPlayer2->GetLevel(), vecBattleFighter2, pPlayer2->GetRoleID(), false);
    pBS->PutScene(pPlayer1->GetSceneFighter());
    pBS->Start(EBShushan);

    bool bResult = pBS->GetFinalWinner() == EBResultAttackWin;
    vecBattleFighter.clear();   // XXX: 需要恢复攻方玩家血量
    vecBattleFighter2.clear();  // XXX: 需要恢复守方玩家血量
    pBS->GetFighterList(0, vecBattleFighter);
    pBS->GetFighterList(1, vecBattleFighter2);
    if (bResult)
    {
        pPlayer1->RecoverFighters(vecBattleFighter);
        pPlayer2->RegenAllHP();
    }
    else
    {
        pPlayer1->RegenAllHP();
        pPlayer2->RecoverFighters(vecBattleFighter2);
    }

    stBR.strNameA   = pPlayer1->GetName();
    stBR.qwRoleA    = pPlayer1->GetRoleID();
    stBR.strNameB   = pPlayer2->GetName();
    stBR.qwRoleB    = pPlayer2->GetRoleID();
    stBR.byResult   = bResult ? 0 : 1;
    stBR.qwBattleID = pBS->GetBattleID();

    std::string strReport;
    pBS->GetReport(strReport);
    std::string strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer1->GetRoleID(), pPlayer1->GetMainFighter()->GetID());
    pPlayer1->SendPkg(strData);
    strData = g_BattleGSS.BuildPkg_BattleReportData(strReport, pPlayer2->GetRoleID(), pPlayer2->GetMainFighter()->GetID());
    pPlayer2->SendPkg(strData);
    return bResult;
}

void CShushanBattle::HandleBattle()
{
    JoinBye();  //轮空
    UINT32 dwIndex = 0;
    UINT32 dwPairSize = _mapPairPlayerInfo.size();
    for(TMapPairPlayerInfo::iterator iter = _mapPairPlayerInfo.begin(); iter != _mapPairPlayerInfo.end(); ++iter, ++ dwIndex)
    {
        UINT64 qwAtkerID = iter->second._qwAtkerRoleID;
        UINT64 qwDeferID = iter->second._qwDeferRoleID;
        //清除配对信息
        InsertPairID(iter->first);
        iter->second.Reset();

        if (!qwAtkerID || !qwDeferID)
            continue;
        SSBPlayerDataPtr pPDAtker = NULL;
        SSBPlayerDataPtr pPDDefer = NULL;
        TMapSSBPlayerData::iterator iter1 = _mapSSBPlayerData.find(qwAtkerID);
        if (iter1 != _mapSSBPlayerData.end())
            pPDAtker = iter1->second;
        TMapSSBPlayerData::iterator iter2 = _mapSSBPlayerData.find(qwDeferID);
        if (iter2 != _mapSSBPlayerData.end())
            pPDDefer = iter2->second;
        CGameMapPtr pFightMap = iter->second._pFightMap;
        if (!pPDAtker || !pPDDefer || !pFightMap)
            continue;
        CUserMgr::LoadUser(qwAtkerID,[this, pPDAtker, pPDDefer, pFightMap, dwIndex, dwPairSize](CUserPtr pAtkUser){
                if (!pPDAtker || !pPDDefer || !pFightMap || !pAtkUser || !pAtkUser->GetPlayer())
                    return;
                UINT64 qwDeferID = pPDDefer->_qwRoleID;
                pPDAtker->_pPlayer = pAtkUser->GetPlayer();

                CUserMgr::LoadUser(qwDeferID,[this, pPDAtker, pPDDefer, pFightMap, dwIndex, dwPairSize](CUserPtr pDefUser){
                        if (!pPDAtker || !pPDDefer || !pFightMap || !pDefUser || !pDefUser->GetPlayer())
                            return;
                        SSSBattleReport stBR;
                        stBR.byRound       = GetRound() > 1 ? GetRound()-1 : 0;
                        CPlayerPtr pDefer  = pDefUser->GetPlayer();
                        pPDDefer->_pPlayer = pDefer;
                        if (IsRunAway(pPDAtker, pPDDefer))  //处理中途逃跑的玩家
                            return;
                        bool bResult = Challenge(pPDAtker->GetPlayer(), pDefer, stBR);

                        UINT32 currHp1 = pPDAtker->GetPlayer()->GetCurrHP();
                        UINT32 currHp2 = pDefer->GetCurrHP();
                        if (bResult && currHp1 < currHp2)
                        {   //击败一位生命高于自己的对手
                            if (UINT16 wAward = pPDAtker->UpdateTaskInfo(6))
                                pPDAtker->SetHonorLevel(wAward);
                        }
                        if (!bResult && currHp1 > currHp2)
                        {   //击败一位生命高于自己的对手
                            if (UINT16 wAward = pPDDefer->UpdateTaskInfo(6))
                                pPDDefer->SetHonorLevel(wAward);
                        }

                        if (bResult)
                            ChallengeResult(pPDAtker, pPDDefer, stBR);
                        else
                            ChallengeResult(pPDDefer, pPDAtker, stBR);

                        pPDAtker->GetPlayer()->GetFighterManager()->SetDirty(eAttrGpShushanBattle);
                        pDefer->GetFighterManager()->SetDirty(eAttrGpShushanBattle);

                        pFightMap->PlayerDisappear(*pPDAtker->GetPlayer());
                        pFightMap->PlayerDisappear(*pDefer);
                        TVecUINT64 vecUsrID;
                        vecUsrID.push_back(pPDAtker->GetPlayer()->GetRoleID());
                        g_MapProtS.NotifyCreatureDisappear(vecUsrID, *pDefer, false);
                        /*
                        if (_pMap)
                        {
                            SPoint oPoint = _pMap->GetRealivePoint();
                            pDefer->JumpMap(_pMap, oPoint);
                            pPDAtker->GetPlayer()->JumpMap(_pMap, oPoint);
                        }
                        */
                        if (dwIndex == dwPairSize - 1)    //最后一个 广播战报
                        {
                            for(auto itr = _mapSSBPlayerData.begin(); itr != _mapSSBPlayerData.end(); ++ itr)
                            {
                                CPlayerPtr pPlayer = GetPlayerByRoleID(itr->first);
                                if (pPlayer && !itr->second->IsQuit())
                                    pPlayer->SendPkg(g_ShushanBattleProtS.BuildPkg_BattleReportInfo(1, this->_vecSSBattleReport));
                            }
                            this->_vecSSBattleReport.clear();
                        }
                        });
                });
    }
}

void CShushanBattle::ChallengeResult(SSBPlayerDataPtr pPDAtker, SSBPlayerDataPtr pPDDefer, SSSBattleReport& stBR)
{
    pPDAtker->_byCurrKill ++;
    pPDAtker->_byTotalWin ++;
    UINT8 byKill = pPDAtker->_byCurrKill > 10 ? 10 : pPDAtker->_byCurrKill;
    UINT16 wWinHonor  = COUNT_WINACHIEVE(byKill, pPDDefer->_byCurrKill, pPDAtker->_byHonorLvl, pPDDefer->_byHonorLvl);
    UINT16 wLoseHonor = COUNT_LOSEACHIEVE(pPDAtker->_byHonorLvl, pPDDefer->_byHonorLvl);
    pPDAtker->SetHonorLevel(wWinHonor);
    if (!pPDAtker->IsQuit())
        pPDAtker->_byType = eSSBattle_FIGHTING;
    pPDAtker->AddAngerDomineer(0, 5);
    if (pPDAtker->_byCurrKill > pPDAtker->_byMaxKill)
        pPDAtker->_byMaxKill = pPDAtker->_byCurrKill;
    CompleteTask(pPDAtker, pPDDefer);
    //Event事件
    if (pPDAtker->GetPlayer())
    {
        TVecINT32 vecParam;
        vecParam.push_back(pPDAtker->_byCurrKill);
        pPDAtker->GetPlayer()->OnEvent(eEventType_ShushanBattleWinStreak, vecParam);

        vecParam.clear();
        vecParam.push_back(pPDAtker->_byTotalWin);
        for (int i = 1; i <= 8; ++ i)
        {
            if ((pPDAtker->_wSkillFlags >> (i-1)) & 1)
                vecParam.push_back(i);
        }
        pPDAtker->GetPlayer()->OnEvent(eEventType_ShushanBattleVictory, vecParam);
    }
    pPDAtker->_wSkillFlags = 0;

    pPDDefer->_byCurrKill = 0;
    pPDDefer->_byTotalLose ++;
    pPDDefer->SetHonorLevel(wLoseHonor);
    if (!pPDDefer->IsQuit())
        pPDDefer->_byType = eSSBattle_FIGHTING;
    pPDDefer->AddAngerDomineer(1, 5);
    pPDDefer->_wSkillFlags = 0;
    CompleteTask1(pPDDefer);

    //推送战斗战报
    stBR.byCurrKill = pPDAtker->_byCurrKill;
    stBR.wHonor     = wWinHonor;
    pPDAtker->_vecBattleReport.push_back(stBR);
    pPDAtker->SendBattleReport();
    //if (CRandom::RandInt(0, 10000) < 10000)     //XXX 战报太多 50%概率广播战报？？？
    this->_vecSSBattleReport.push_back(stBR);

    stBR.byCurrKill = pPDDefer->_byCurrKill;
    stBR.wHonor     = wLoseHonor;
    pPDDefer->_vecBattleReport.push_back(stBR);
    pPDDefer->SendBattleReport();
}

void CShushanBattle::CompleteTask(SSBPlayerDataPtr pPDAtker, SSBPlayerDataPtr pPDDefer)
{
    UINT16 wAward = 0;
    UINT8 byCurrKill = pPDAtker->_byCurrKill;
    if (byCurrKill >= 2)
    {
        wAward += pPDAtker->UpdateTaskInfo(1);
        if (byCurrKill >= 3)
            wAward += pPDAtker->UpdateTaskInfo(15);
        if (byCurrKill >= 4)
            wAward += pPDAtker->UpdateTaskInfo(19);
        if (byCurrKill >= 6)
            wAward += pPDAtker->UpdateTaskInfo(23);
        if (byCurrKill >= 10)
            wAward += pPDAtker->UpdateTaskInfo(26);
    }
    UINT8 byTotalWin = pPDAtker->_byTotalWin;
    if (byTotalWin >= 3)
    {
        wAward += pPDAtker->UpdateTaskInfo(3);
        if (byTotalWin >= 10)
            wAward += pPDAtker->UpdateTaskInfo(17);
        if (byTotalWin >= 15)
            wAward += pPDAtker->UpdateTaskInfo(21);
        if (byTotalWin >= 20)
            wAward += pPDAtker->UpdateTaskInfo(24);
        if (byTotalWin >= 25)
            wAward += pPDAtker->UpdateTaskInfo(27);
    }
    UINT8 byKillOther = pPDDefer->_byCurrKill;
    if (byKillOther >= 2)
    {
        wAward += pPDAtker->UpdateTaskInfo(2);   //终结2连杀
        if (byKillOther >= 3)
            wAward += pPDAtker->UpdateTaskInfo(16);  //终结3连杀
        if (byKillOther >= 4)
            wAward += pPDAtker->UpdateTaskInfo(20);  //终结4连杀
    }
    if (pPDAtker->GetPlayer() && pPDDefer->GetPlayer() && pPDAtker->GetPlayer()->GetBattlePoint() < pPDDefer->GetPlayer()->GetBattlePoint())
    {   //击败一位战力高于自己的对手
        wAward += pPDAtker->UpdateTaskInfo(5);
    }
    UINT8 byHonorLvl1 = pPDAtker->_byHonorLvl;
    if (byHonorLvl1 >= 2)
    {
        wAward += pPDAtker->UpdateTaskInfo(4);   //2级
        if (byHonorLvl1 >= 4)
            wAward += pPDAtker->UpdateTaskInfo(18);  //4级
        if (byHonorLvl1 >= 6)
            wAward += pPDAtker->UpdateTaskInfo(22);  //6级
        if (byHonorLvl1 >= 8)
            wAward += pPDAtker->UpdateTaskInfo(25);  //8级
        if (byHonorLvl1 >= 9)
            wAward += pPDAtker->UpdateTaskInfo(28);  //9级
    }
    if (wAward)
        pPDAtker->SetHonorLevel(wAward);
}

void CShushanBattle::CompleteTask1(SSBPlayerDataPtr pPlayerData)
{
    //一直失败或者轮空的玩家
    UINT8 byHonorLvl = pPlayerData->_byHonorLvl;
    if (byHonorLvl >= 2)
    {
        UINT16 wAward = 0;
        wAward += pPlayerData->UpdateTaskInfo(4);   //2级
        if (byHonorLvl >= 4)
            wAward += pPlayerData->UpdateTaskInfo(18);  //4级
        if (byHonorLvl >= 6)
            wAward += pPlayerData->UpdateTaskInfo(22);  //6级
        if (byHonorLvl >= 8)
            wAward += pPlayerData->UpdateTaskInfo(25);  //8级
        if (byHonorLvl >= 9)
            wAward += pPlayerData->UpdateTaskInfo(28);  //9级
        if (wAward)
            pPlayerData->SetHonorLevel(wAward);
    }
}

void CShushanBattle::InsertPairID(UINT32 dwPairID)
{
    TVecUINT32::iterator it = std::find(_vecPairID.begin(), _vecPairID.end(), dwPairID);
    if (it != _vecPairID.end())
        return;
    _vecPairID.push_back(dwPairID);
}

UINT32 CShushanBattle::GetPairID()
{
    UINT32 dwSize = _vecPairID.size();
    if (dwSize == 0)
        return _dwPairID ++;
    UINT32 dwRand = CRandom::RandInt(0, dwSize-1);
    TVecUINT32::iterator it = _vecPairID.begin();
    std::advance(it, dwRand);
    UINT32 dwPairID = *it;
    _vecPairID.erase(it);
    return dwPairID;
}

void CShushanBattle::GetAddAttr(TVecFloat& rvecAttr, UINT64 qwRoleID)
{
    if (!ShushanBattleMgr.IsRunning())
        return;
    TMapSSBPlayerData::iterator iter = _mapSSBPlayerData.find(qwRoleID);
    if (iter == _mapSSBPlayerData.end())
        return;
    if (iter->second->IsQuit())
        return;
    for (int i = 1; i <= 8; ++ i)
    {
        if ((iter->second->_wSkillFlags >> (i-1)) & 1)
        {
            SBattleSkillCFGEx* pBattleSkillCfg = ShushanBattleMgr.GetBattleSkillCfg(i);
            if (pBattleSkillCfg)
            {
                if ( i != 4)
                    rvecAttr += pBattleSkillCfg->_vecAddAttr;
                /*
                else
                {
                    CPlayerPtr pPlayer = GetPlayerByRoleID(qwRoleID);
                    if (pPlayer)
                        pPlayer->AddCurrHPPer(pBattleSkillCfg->_vecAddAttr[EFIGHTATTR_MAXHP_PER]);
                }
                */
            }
        }
    }
}

UINT8 CShushanBattle::GetRound()
{
    UINT32 dwStartTime = ShushanBattleMgr.GetStartTime();
    if (_dwTickTime < dwStartTime)
        return 0;
    return (_dwTickTime - dwStartTime) / NCBATTLE_TIME;
}

