/********************************************************************
//	Game Server Source File.
//	File name:	UserMgr.cpp
//	Created:	2011/05/30	10:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
 *********************************************************************/

#include "stdafx.h"
#include "Protocols.h"
#include "User.h"
#include "UserMgr.h"
#include "TimePointMgr.h"
#include "Player.h"
#include "Map.h"
#include "IconAppearManager.h"
#include "ServerID.h"
#include "GameNetMgr.h"
#include "EverydayRecharge.h"
#include "ActivityIDProt.h"
#include "FeedBackMgr.h"

TMapID2Usr CUserMgr::_mapID2Usr;
map<string, CUserPtr> CUserMgr::_mapName2Usr;
unordered_set<UINT64> CUserMgr::_setUserExcept;
SBornInfo CUserMgr::_oBornInfo;

map<UINT64, SRRLevelInfoPtr> CUserMgr::_mapRankLevel;
map<UINT32, bool> CUserMgr::_mapActID2State;

bool CUserMgr::Init()
{
    CTimePointMgr::AddCallback(eTimePointDaily19, DailyReset);
    CTimePointMgr::AddCallback(eTimePointDaily0, DailyReset);

    return true;
}

void CUserMgr::Destroy()
{
    _mapID2Usr.clear();
}

CUserPtr CUserMgr::CreateUser(UINT64 qwUsrID)
{
    CUserPtr pUser(new CUser(qwUsrID));
    if(pUser == NULL)
        return NULL;
    pUser->Init();
    if(!_mapID2Usr.insert(make_pair(qwUsrID, pUser)).second)
    {
        LOG_CRI << "User already exists! UsrID: " << qwUsrID;
        return NULL;
    }
    LOG_INF << "Create UsrID: " << qwUsrID;
    return pUser;
}

void CUserMgr::RemoveUser(UINT64 qwUsrID)
{
    auto it = _mapID2Usr.find(qwUsrID);
    RemoveUser(it);
}

void CUserMgr::RemoveUser(TMapID2Usr::iterator it)
{
    if(it == _mapID2Usr.end())
    {
        LOG_CRI << "Can't find User!";
        return;
    }
    CUserPtr pUser = it->second;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer != NULL)
    {
        CGameMapPtr pMap = pPlayer->GetMap();
        CWalkerMgr::DelWalker(pPlayer->GetWalker());
        if (pMap)
            pMap->PlayerDisappear(*pPlayer);
        pUser->SetPlayer(NULL);
    }
    UINT64 qwUsrID = pUser->GetUserID();
    LOG_DBG << "RemoveUser, UserID: " << qwUsrID;
    NetMgr.GetGateHandler()->OnUserLogout(qwUsrID);
    _mapID2Usr.erase(it);
}

CUserPtr CUserMgr::GetUserByUserID(UINT64 qwUsrID)
{
    auto it = _mapID2Usr.find(qwUsrID);
    if(it == _mapID2Usr.end())
        return NULL;
    return it->second;
}

bool CUserMgr::SendPkg(const TVecUINT64& vecUsrID, const string& strPkg)
{
    if(strPkg.empty())
        return false;
    if(vecUsrID.empty())
        return true;
    return NetMgr.GetGateHandler()->SendClt((UINT64*)&vecUsrID[0], (UINT16)vecUsrID.size(), strPkg.c_str(), (UINT32)strPkg.size());
}

bool CUserMgr::OnUserBorn(CUser& rUser)
{
    // TODO:
    return true;
}

bool CUserMgr::OnUserLeave(UINT64 qwUsrID, ELeaveType eLeaveType)
{
    CUserPtr pUser = GetUserByUserID(qwUsrID);
    if(pUser == NULL)
        return false;
    return OnUserLeave(*pUser, eLeaveType);
}

bool CUserMgr::OnUserLeave(CUser& rUser, ELeaveType eLeaveType)
{
    // TODO:
    // 这里把变化发给数据库，就可以删除了。。。。：yhs
    //RemoveUser(rUser.GetUserID());
    //if(eUserLeaveAway != rUser.GetUserState())
    //	LoginLog.LogLoginOut(rUser, eLeaveType);
    UINT64 qwUsrID = rUser.GetUserID();
    switch(eLeaveType)
    {
        case eLeaveAway:
            rUser.OnLeaveAway();
            break;
        case eLeaveJump:
            rUser.OnLeaveOff(eSaveJump);
            RemoveUser(qwUsrID);
            break;
        case eLeaveKick:
            rUser.OnLeaveOff(eSaveKick);
            RemoveUser(qwUsrID);
            break;
        case eLeaveExcept:
            rUser.OnLeaveOff(eSaveExcept);
            RemoveUser(qwUsrID);
            break;
        case eIndulgeKick:
        case eIndulgeTimeKick:
            {
                rUser.OnLeaveOff(eSaveKick);
                RemoveUser(qwUsrID);
            }
            break;
        default:
            LOG_CRI << "Invalid eLeaveType: " << GetDescription(eLeaveType);
    }

    return true;
}

bool CUserMgr::KickUserOffLine(UINT64 qwUsrID, bool bException /*= false*/)
{
    UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(qwUsrID);
    if(dwGateID == 0)
        return false;
    LOG_INF << "KickUserOffLine! UsrID: " << qwUsrID;
    ELeaveType eLeaveType = bException ? eLeaveExcept : eLeaveKick;
    return g_Gate2GameCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUsrID, eLeaveType);
}

bool CUserMgr::KickUserOffLineReason(UINT64 qwUsrID, ELeaveType eELeaveType)
{
    UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(qwUsrID);
    if(dwGateID == 0)
        return false;
    LOG_INF << "KickUserOffLine! UsrID: " << qwUsrID;
    return g_Gate2GameCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUsrID, eELeaveType);
}

bool CUserMgr::ForceKickUserOffLine(UINT64 qwUsrID, bool bException /*= false*/)
{
    LOG_INF << "ForceKickUserOffLine! UsrID: " << qwUsrID;
    ELeaveType eLeaveType = bException ? eLeaveExcept : eLeaveKick;
    UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(qwUsrID);
    if(dwGateID != 0)
        return g_Gate2GameCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUsrID, eLeaveType);
    return g_Gate2GameCommS.SendSvr_KickUserOffLine(NULL, 0, qwUsrID, eLeaveType);
}

void CUserMgr::TimerCheck(time_t tNow)
{
    bool bCheck = false;
    static time_t tLastPerMinute = tNow + PER_MINUTE_TO_S;
    if(tNow > tLastPerMinute)
    {
        bCheck = true;
        tLastPerMinute = tNow + PER_MINUTE_TO_S;
    }

    auto it = _mapID2Usr.begin(), itCur = it;
    while(it != _mapID2Usr.end())
    {
        UINT64 qwUsrID = it->first;
        CUserPtr pUser = it->second;
        itCur = it;
        ++it;

        switch(pUser->GetUserState())
        {
            case eUserInGame:
                {
                    if (pUser->GetPlayer() != NULL)
                    {
                        pUser->TimerCheck(tNow);
                        pUser->GetTaskPkg().TimerCheck(tNow);
                        if(bCheck) //one minute
                        {
                            pUser->GetPack().TimerCheck(tNow);
                            pUser->GetDepot().TimerCheck(tNow);
                            // TODO:
                        }
                    }

                    if(tNow > pUser->_tLastSaveTime)
                    {
                        time_t tDiffTime = tNow - pUser->_tLastSaveTime;
                        if((pUser->HasChange() && tDiffTime >= TIMER_SAVE_INTERVAL_NORMAL) ||
                                (tDiffTime >= TIMER_SAVE_INTERVAL_MAX))
                        {
                            pUser->_tLastSaveTime = tNow;
                            // TODO: 定时保存
                            //if(!g_Game2DBCommC.SaveDataReq(*pUser, eSaveData))
                            //	CUserMgr::KickUserOffLine(qwUsrID);
                            pUser->ClearChange();
                        }
                    }
                }
                break;
            case eUserLeaveAway:
                if(Config._bIsCrossServer)
                {
                    if(pUser->CanRemove())
                    {
                        pUser->OnLeaveOff(eSaveOff);
                        CUserMgr::RemoveUser(itCur);
                    }
                }
                else
                {
                    if(tNow > pUser->_tLastCheckTime 
                            && tNow - pUser->_tLastCheckTime >= MAX_LEAVE_INTERVAL
                            &&pUser->CanRemove())
                    {
                        pUser->OnLeaveOff(eSaveOff);
                        //LOG_CRI << "User ref :" << pUser.use_count();
                        CUserMgr::RemoveUser(itCur);
                        //LOG_CRI << "User ref :" << pUser.use_count();
                        //LOG_INF << "Player Leaver!";
                    }
                }
                break;
            case eUserReplace:
                if(tNow > pUser->_tLastCheckTime && tNow - pUser->_tLastCheckTime >= MAX_REPLACE_INTERVEL)
                {
                    LOG_CRI << "User in replace state too long! UsrID: " << qwUsrID;
                    pUser->OnLeaveOff(eSaveKick);
                    CUserMgr::RemoveUser(itCur);
                }
                break;
            default:
                break;
        }
    }
}

void CUserMgr::DailyReset(ETimePointType eType)
{
    if(eTimePointDaily0 == eType)
    {
        g_FeedBackMgr.OnMidNight();
    }

    for(auto itr = _mapID2Usr.begin(); itr != _mapID2Usr.end(); ++itr)
    {
        // TODO:
        CUserPtr pUser = itr->second;
        if(pUser)
        {
            pUser->OnDayReset(eType);
        }
    }
}

void CUserMgr::AddExceptUser(UINT64 qwUsrID)
{
    _setUserExcept.insert(qwUsrID);
}

bool CUserMgr::HasException(UINT64 qwUsrID)
{
    return _setUserExcept.find(qwUsrID) != _setUserExcept.end();
}

CPlayerPtr CUserMgr::CreatePlayer(UINT64 qwRoleID, const CUserPtr& pUser)
{
    if(pUser == NULL)
    {
        LOG_CRI << "pUser is NULL! qwRoleID: " << qwRoleID;
        return NULL;
    }
    if(pUser->GetPlayer() != NULL)
    {
        return pUser->GetPlayer();
    }
    CPlayerPtr pPlayer(new CPlayer(qwRoleID, pUser));
    if(pPlayer == NULL)
    {
        LOG_CRI << "pPlayer is NULL!";
        return NULL;
    }
    pPlayer->SetPlayerState(ePlayerBorn);
    pUser->_tLastSaveTime = time(NULL);
    pUser->SetPlayer(pPlayer);
    CWalkerMgr::AddWalker(pPlayer->GetWalker());
#ifdef _WIN32
    Config.ShowPlayerCount((UINT16)_mapRole2Player.size());
#endif
    return pPlayer;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */
void CUserMgr::LoadUser(UINT64 qwRoleID, FunLoadUser fun)
{
    CUserPtr pUser = GetUserByUserID(qwRoleID);
    if(NULL != pUser)
    {
        fun(pUser);
        return ;
    }
    g_Game2DBCommC.Send_LoadOffLineUserData(qwRoleID,[qwRoleID,fun](UINT8 byRet_, //0为成功，1为失败，2为超时
                UINT8 byRet, //(返回值)0表示成功
                const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
                )
            {
            if(byRet_ != 0 || byRet != 0)
            {
            fun(NULL);
            return ;
            }

            CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
            if (pUser != NULL)
            {
            fun(pUser); 
            return ;
            }
            bool bFind = false;
            do{
            pUser = CUserMgr::CreateUser(RoleData.qwRoleId);
            if (!pUser)
            {
                LOG_CRI << "CUserMgr::CreateUser(" << RoleData.qwRoleId << ") error.";
                break;
            }
            CPlayerPtr pPlayer = CUserMgr::CreatePlayer(RoleData.qwRoleId, pUser);
            if (pPlayer == NULL)
            {
                LOG_CRI << "CUserMgr::CreatePlayer(" << RoleData.qwRoleId << ") errorek";
                break;
            }
            if (!pPlayer->Init())
            {
                LOG_CRI << "CPlayer::Init(" << RoleData.qwRoleId << ") error.";
                break; 
            } 
            if (!pPlayer->LoadFromDB(RoleData))
            {
                LOG_CRI << "CPlayer::LoadFromDB(" << RoleData.qwRoleId << ") error.";
                break;
            }
            pUser->_tLastCheckTime = time(NULL);
            pUser->SetSvrGroup(GetServerGroup(g_Game2DBCommC.GetCurSvrID()));
            pPlayer->SetPlayerState(ePlayerLeave);
            pUser->SetUserState(eUserLeaveAway);
            pUser->SetVIPLevel(pUser->CalcVIPLevel());
            if(pPlayer->GetBaseInfo().qwDgnId == 0)
            {
                pPlayer->SetCurMapID(pPlayer->GetBaseInfo().wMapID); 
                pPlayer->SetPoint(SPoint(pPlayer->GetBaseInfo().fX,pPlayer->GetBaseInfo().fY));
            }
            pPlayer->RegenAllHP();
            fun(pUser);
            pPlayer->DoCheckErrItem();
            bFind = true;
            }while(0);
    if(!bFind)
    {
        CUserMgr::KickUserOffLine(qwRoleID);
        CUserMgr::OnUserLeave(qwRoleID, eLeaveKick);
        LOG_CRI << "LoadData Fails! UsrID: " << qwRoleID;
        fun(NULL);
    }
            });

}

void CUserMgr::InsertLevelRank(UINT64 qwRoleID, SRRLevelInfoPtr pInfo)
{
    _mapRankLevel[qwRoleID] = pInfo;
}

void CUserMgr::EraseLevelRank(UINT64 qwRoleID)
{
    auto it = _mapRankLevel.find(qwRoleID);
    if (it != _mapRankLevel.end())
        _mapRankLevel.erase(it);
}

void CUserMgr::SyncLevelRank()
{
    TVecUINT64 vecRoleID;
    TVecRankInfo vecRankInfo;
    for (auto& rPair:_mapRankLevel)
    {
        vecRoleID.push_back(rPair.first);
        vecRankInfo.push_back(dynamic_pointer_cast<SRankInfo>(rPair.second));
    }
    g_Game2CenterRankC.Send_UpdateAllLevelInfo(vecRoleID, vecRankInfo);
    _mapRankLevel.clear();
}

void CUserMgr::PrintUserSize()
{

    UINT32 dwTotalSize = 0;
    for(auto itr = _mapID2Usr.begin();itr != _mapID2Usr.end(); itr++)
    {
        CUserPtr pUser = itr->second;
        if(pUser)
        {
            UINT32 dwSize = pUser->ToSize();
            LOG_INF<<"UserID:"<<pUser->GetUserID()<<" size:"<<dwSize;
            dwTotalSize += dwSize;
        }
    }

    LOG_INF<<"UserSize:"<<dwTotalSize<<" usercount:"<<_mapID2Usr.size();
}

void CUserMgr::OpenIcon(UINT32 dwActID,bool bNotify)
{
    bool &bState = _mapActID2State[dwActID];
    bState = true;
    /* //策划需求，活动开启和Icon显示 两码事
    if(bNotify)
        CIconAppearMgr::Instance().IconControlBySelf(dwActID);
    */
    if(dwActID ==  NActivityIDProt::eDragonBallAct)
    {
        g_EveryDayRechargeMgr.SetDragonState(true);
    }
    if(bNotify)
    {
        UINT16 wIcon = CIconAppearMgr::Instance().GetIconByActiveID(dwActID);
        if(!wIcon)
        {
            LOG_INF<<"Icon is 0.";
            return;
        }
        TVecUINT16 vecIcon;
        vecIcon.push_back(wIcon);
        
        TMapID2Usr mapUsr;
        GetOnlineUser(mapUsr);
        for(auto & it : mapUsr)
        {
            CUserPtr pUser = it.second;
            if(CIconAppearMgr::Instance().IsActivityOpen(*pUser,dwActID))
            {
                CIconAppearMgr::Instance().OpenActionToClient(*pUser,vecIcon);
                 
            }
        }
    }
}

void CUserMgr::CloseIcon(UINT32 dwActID,bool bNotify)
{
    bool &bState = _mapActID2State[dwActID];
    bState = false;
    if(dwActID == NActivityIDProt::eDragonBallAct)
    {
        g_EveryDayRechargeMgr.SetDragonState(false);
    }
    if(bNotify)
    {
        UINT16 wIcon = CIconAppearMgr::Instance().GetIconByActiveID(dwActID);
        if(wIcon > 0)
        CIconAppearMgr::Instance().CloseActionToClientForAll(wIcon);
    }
}

bool CUserMgr::CheckIcon(UINT32 dwActID)
{
    bool bState = false;
    auto it = _mapActID2State.find(dwActID);
    if( it != _mapActID2State.end())
        bState = it->second;
    return bState;
}

void CUserMgr::AddIcon(UINT32 dwActID,bool bOpen,bool bNotify)
{
    if(bOpen)
        OpenIcon(dwActID,bNotify);
    else 
        CloseIcon(dwActID,bNotify);
}

void CUserMgr::GetOnlineUser(TMapID2Usr& mapID2Usr)
{
    auto it = _mapID2Usr.begin();
    while(it != _mapID2Usr.end())
    {
        UINT64 qwUsrID = it->first;
        CUserPtr pUser = it->second;
        if(pUser->GetUserState() == eUserInGame)
            mapID2Usr[qwUsrID] = pUser;
        
        ++it;
    }
}

