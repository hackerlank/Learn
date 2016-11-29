/********************************************************************
//	Center Server Source File.
//	File name:	UserMgr.cpp
//	Created:	2011/06/06	10:00
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
#include "User.h"
#include "UserMgr.h"
#include "Protocols.h"
#include "ArenaManager.h"
#include "GuildUser.h"
#include "TripodManager.h"
#include "VarDefine.h"
#include "DragonBallActMgr.h"
#include "SevenConsumeActMgr.h"
#include "CenterGameVar.h"
#include "InvitedFriendMgr.h"
#include "TeamMananger.h"

extern CCenterGameVar g_CenterGameVar;

map<UINT64, CUserPtr> CUserMgr::_mapID2Usr;
map<string, UINT64> CUserMgr::_mapName2UsrID;
TMapCamp2LevelUser CUserMgr::_mapNationLevel2UsrID;
unordered_set<UINT64> CUserMgr::_setUserExcept;
UINT16 CUserMgr::_wActiveUserCount;
map<UINT64, TVecPlatformParam> CUserMgr::_mapPlatformParam;
map<UINT8,UINT32> CUserMgr::_mapLevel2Count;

map<UINT8,TMapID2Count> CUserMgr::_mapmapType2Count;

void CUserMgr::Destroy()
{
	_mapID2Usr.clear();
}

CUserPtr CUserMgr::CreateUser(UINT64 qwUsrID)
{
	CUserPtr pUser(new CUser(qwUsrID));
	if(pUser == NULL || !_mapID2Usr.insert(make_pair(qwUsrID, pUser)).second)
		return NULL;
	return pUser;
}

void CUserMgr::RemoveUser(map<UINT64, CUserPtr>::iterator it)
{
	if(it == _mapID2Usr.end())
		return;
	CUserPtr pUser = it->second;
	LOG_DBG << "RemoveUser, UserID: " << pUser->GetUserID();
	_mapID2Usr.erase(it);
	_mapName2UsrID.erase(pUser->GetUserName());
	RemoveUserLevel(*pUser);
}

void CUserMgr::RemoveUser(UINT64 qwUsrID)
{
	RemoveUser(_mapID2Usr.find(qwUsrID));
    g_TeamManager.PlayerOffLine(qwUsrID);
}

CUserPtr CUserMgr::GetUserByUserID(UINT64 qwUsrID)
{
	auto it = _mapID2Usr.find(qwUsrID);
	if(it == _mapID2Usr.end())
		return NULL;
	return it->second;
}

CUserPtr CUserMgr::GetUserByName(const string& strName)
{
	auto it = _mapName2UsrID.find(strName);
	if(it == _mapName2UsrID.end())
		return NULL;
	return GetUserByUserID(it->second);
}

bool CUserMgr::MapUserName2ID(const string& strName, UINT64 qwUserID)
{
	//_mapName2UsrID.erase(strName);
    return _mapName2UsrID.insert(std::make_pair(strName, qwUserID)).second;
}

UINT32 CUserMgr::GetUserCount()
{
	return (UINT32)_mapID2Usr.size();
}

UINT32 CUserMgr::GenSessionKey()
{
	UINT32 dwSessionKey = (UINT32)CRandom::RandInt();
	if(dwSessionKey == 0)
		dwSessionKey = UINT16_MAX;
	return dwSessionKey;
}

bool CUserMgr::KickUserOffLine(UINT64 qwUsrID, bool bException /*= false*/)
{
	UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(qwUsrID);
	if(dwGateID == 0)
		return false;
	LOG_INF << "KickUserOffLine! UsrID: " << qwUsrID;
	return g_Gate2CenterCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUsrID, bException ? eLeaveExcept : eLeaveKick);
}

bool CUserMgr::KickUserOffLineReason(UINT64 qwUsrID,ELeaveType eELeaveType)
{
	UINT32 dwGateID = NetMgr.GetGateHandler()->GetGateID(qwUsrID);
	if(dwGateID == 0)
		return false;
	LOG_INF << "KickUserOffLine! UsrID: " << qwUsrID;
	return g_Gate2CenterCommS.SendSvr_KickUserOffLine(&dwGateID, 1, qwUsrID, eELeaveType);

}

bool CUserMgr::IsOnline(UINT64 qwUsrID)
{
	auto it = _mapID2Usr.find(qwUsrID);
	if(it == _mapID2Usr.end())
		return false;

	CUserPtr pUser = it->second;
	if(pUser)
		return eUserInGame == pUser->GetState();

	return false;
}

void CUserMgr::TimerCheck(time_t tNow)
{
    //bool bZeroTime = false;
    if(g_CenterGameVar.IsLoad())
    {
        UINT32 dwTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVarZeroTime);
        if(time(NULL) > dwTime)
        {
            g_CenterGameVar.SetVar(NVarDefine::eSystemVarZeroTime,Time::TheDay(1));
            
            //OnMidTime
            g_InvitedFriendMgr.OnMiddNight();
        }

    }
	time_t tLastCheckTime = 0;
	auto it = _mapID2Usr.begin();
	auto itCur = it;
	while(it != _mapID2Usr.end())
	{
		CUserPtr pUser = it->second;
		itCur = it++;
		tLastCheckTime = pUser->GetCheckTime();
		switch(pUser->GetState())
		{
		case eUserWantLogin:
			if(tNow > tLastCheckTime && tNow - tLastCheckTime > ROLE_LOGIN_WAIT)
			{
				g_Gate2CenterCommS.SendSvr_KickUserOffLine(NULL, 0, pUser->GetUserID(), eLeaveKick);
				LOG_INF << "User wait to login too long, Kick offline, UsrID:" << pUser->GetUserID();
				RemoveUser(itCur);
			}
			break;
		case eUserReplace:
			if(tNow > tLastCheckTime && tNow - tLastCheckTime > ROLE_KICK_WAIT)
				pUser->SetState(eUserLeaveAway);
			break;
		case eUserLeaveAway:
			if(tNow > tLastCheckTime && tNow - tLastCheckTime > ROLE_LEAVE_WAIT)
            {
                LOG_INF << "User Leave long, Kick offline, UsrID:" << pUser->GetUserID();
				RemoveUser(itCur);
            }
			break;
       case eUserInGame:
            pUser->TimerCheck(tNow);
            break;
       default:
            break;
		}
	}
}

void CUserMgr::IncActiveUserCount()
{
	++_wActiveUserCount;
#ifdef _WIN32
	Config.ShowPlayerCount(_wActiveUserCount);
#endif
}

void CUserMgr::DecActiveUserCount()
{
	if(_wActiveUserCount > 0)
		--_wActiveUserCount;
#ifdef _WIN32
	Config.ShowPlayerCount(_wActiveUserCount);
#endif
}

void CUserMgr::OnUserPropChanged(CUser& rUser, NGame2CenterComm::EUserSyncPropField eField, const std::string& strVal)
{
	switch(eField)
	{
	case NGame2CenterComm::eSyncPropLevel:
		{
			UINT8 byLevel = static_cast<UINT8>(atoi(strVal.c_str()));
			UINT8 byOldLevel = rUser.GetLevel();
			if(byLevel != byOldLevel)
			{
				rUser.SetLevel(byLevel);
				UpdateUserLevel(rUser, byOldLevel);
                rUser.GetFriend().UserChangeNotify(g_FriendProtS.BuildPkg_LevelChangeNotify(rUser.GetUserID(), byLevel));
                CArenaManager::UpdatePlayerLevel(rUser.GetUserID(), byLevel);

                ChangeLevel(rUser.GetUserID(),byOldLevel,byLevel);
                g_InvitedFriendMgr.OnUserPropChanged(rUser,eField,byLevel);
			}
		}
		break;
	case NGame2CenterComm::eSyncPropNation:
		{
			UINT8 byNation = static_cast<UINT8>(atoi(strVal.c_str()));
			rUser.SetNation(byNation);
        }
        break;
       
    case NGame2CenterComm::eSyncPropGold:
		{
			UINT32 dwGold = static_cast<UINT32>(atoi(strVal.c_str()));
            UINT32 dwLastGold = rUser.GetGold();
            if (dwLastGold > dwGold)    //消耗仙石
            {
                UINT32 dwEndTime = g_CenterGameVar.GetVar(NVarDefine::eSystemVar_SevenConsumeActEndTime);
                UINT32 dwConsume = rUser.GetCenterVar().GetVar(NVarDefine::ePlayerVarSevenConsumeGold);
                rUser.GetCenterVar().SetVar(NVarDefine::ePlayerVarSevenConsumeGold, dwConsume+(dwLastGold-dwGold), 0, dwEndTime);
                CSevenConsumeActMgr::Instance().OnSevenConsumeAct(ToThisPtr(rUser));
            }

			rUser.SetGold(dwGold);
        }
        break;
    case NGame2CenterComm::eSyncPropSilver:
		{
			UINT32 dwSilver = static_cast<UINT32>(atoi(strVal.c_str()));
			rUser.SetSilver(dwSilver);
        }
        break;
    case NGame2CenterComm::eSyncPropCoupon:
		{
			UINT32 dwCoupon = static_cast<UINT32>(atoi(strVal.c_str()));
			rUser.SetCoupon(dwCoupon);
        }
        break;
    case NGame2CenterComm::eSyncPropVIPLevel:
		{
			UINT8 byVipLvl = static_cast<UINT8>(atoi(strVal.c_str()));
            if (rUser.GetVIPLevel() != byVipLvl)
            {
                bool bRes = TripodManager.SettleTripodFireSoul(rUser.GetUserID());  //XXX 必须在SetVIPLevel之前
                if (bRes)
                    TripodManager.Send_UpdateTripod(ToThisPtr(rUser));
            }

			rUser.SetVIPLevel(byVipLvl);
            rUser.GetFriend().UserChangeNotify(g_FriendProtS.BuildPkg_VIPChangeNotify(rUser.GetUserID(), byVipLvl));
            CArenaManager::UpdatePlayerVIPLevel(rUser.GetUserID(), byVipLvl);
            g_InvitedFriendMgr.OnUserPropChanged(rUser,eField,byVipLvl);
        }
        break;
    case NGame2CenterComm::eSyncPropQuality: //主将品质
        {
            UINT8 byQuality = static_cast<UINT8>(atoi(strVal.c_str()));
            if (rUser.GetQuality() != byQuality)
            {
                rUser.SetQuality(byQuality);
                CArenaManager::UpdatePlayerQuality(rUser.GetUserID(), byQuality);
            }

        }
        break;
    case NGame2CenterComm::eSyncPropPlayerFighterID: //主将ID
        break;
    case NGame2CenterComm::eSyncPropTotalRecharge:
        {
			UINT32 dwRecharge = static_cast<UINT32>(atoi(strVal.c_str()));
            rUser.GetCenterVar().AddVar(NVarDefine::ePlayerVarDayRechargeCenter, dwRecharge);
            rUser.AddTotalRecharge(dwRecharge);
            CDragonBallActMgr::Instance().OnDragonBallAct(ToThisPtr(rUser));
            g_InvitedFriendMgr.OnUserPropChanged(rUser,NGame2CenterComm::eSyncPropTotalRecharge,dwRecharge);
        }
        break;

        // TODO:
#if 0
    case NGame2CenterComm::eSyncPropYellowDiamond:
        {
            TVecUINT8 vecYellowDiamond;
            SplitToNumber(strVal, ",", vecYellowDiamond);
            if(2 == vecYellowDiamond.size())
            {
                UINT8 byLevel = vecYellowDiamond[0];
                bool bYearlyPay = vecYellowDiamond[1] > 0 ? true : false;
                if(byLevel != rUser.YellowDiamondLevel() || bYearlyPay != rUser.IsYearlyPay())
                {
                    rUser.SetYellowDiamond(byLevel, bYearlyPay);
                    rUser.GetFriend().UserChangeNotify(g_FriendProtS.BuildPkg_YellowDiamondNotify(rUser.GetUserID(), byLevel, bYearlyPay));
                }
            }
        }
        break;
    case NGame2CenterComm::eSyncPropUseTitle:
        {
            UINT16 wUseTitle = static_cast<UINT16>(atoi(strVal.c_str()));
            rUser.SetTitle(wUseTitle);
        }
        break;
#endif
	default:
		break;
	}
}

void CUserMgr::UpdateUserLevel(CUser& rUser, UINT8 byOldLevel /*= 0*/)
{
	UINT8 byNation = rUser.GetNation();
    // XXX: all 0

#if 0
	if(0 == byNation)
		return;
#endif
	auto it_nation = _mapNationLevel2UsrID.find(byNation);
	if(it_nation != _mapNationLevel2UsrID.end())
	{
		TMapLevel2User& rMap = it_nation->second;
		if(byOldLevel > 0)
		{
			auto it_old = rMap.find(byOldLevel);
			if(it_old != rMap.end())
				it_old->second.erase(rUser.GetUserID());
		}

		rMap[rUser.GetLevel()].insert(rUser.GetUserID());
	}
	else
	{
		_mapNationLevel2UsrID[byNation][rUser.GetLevel()].insert(rUser.GetUserID());
	}
    CGuildUserPtr pGuildUser = rUser.GetGuildUser();
    if (pGuildUser)
        pGuildUser->SetLevel(rUser.GetLevel());
}

void CUserMgr::RemoveUserLevel(CUser& rUser)
{
	UINT8 byNation = rUser.GetNation();
#if 0
	if(0 == byNation) // TODO:
		return;
#endif
	auto it_level = _mapNationLevel2UsrID[byNation].find(rUser.GetLevel());
	if(it_level != _mapNationLevel2UsrID[byNation].end())
		it_level->second.erase(rUser.GetUserID());
}

TMapLevel2User* CUserMgr::GetUserLevelRange(UINT8 byNation)
{
	auto it = _mapNationLevel2UsrID.find(byNation);
	if(it != _mapNationLevel2UsrID.end())
		return &it->second;

	return NULL;
}

void CUserMgr::AddExceptUser(UINT64 qwUsrID)
{
	_setUserExcept.insert(qwUsrID);
}

bool CUserMgr::HasException(UINT64 qwUsrID)
{
	return _setUserExcept.find(qwUsrID) != _setUserExcept.end();
}

void CUserMgr::InitPlatformParam(UINT32 dwCurSize, UINT32 dwTotalSize, const TVecUINT64& vecRoleID, const NProtoCommon::TVecPlatformParam& vecPlatform)
{
    auto it = vecRoleID.begin();
    auto it2 = vecPlatform.begin();
    for (; it != vecRoleID.end() && it2 != vecPlatform.end(); ++it, ++it2)
    {
        auto it3 = _mapPlatformParam.find(*it);
        if (it3 == _mapPlatformParam.end())
            _mapPlatformParam[*it].push_back(*it2);
        else
        {
            bool bFound = false;
            for (auto& rPlatformParam : it3->second)
            {
                if ((*it2).byPtType == rPlatformParam.byPtType
                        && (*it2).byQQPtType == rPlatformParam.byQQPtType)
                {
                    bFound = true;
                    rPlatformParam.byQQPtLv = (*it2).byQQPtLv;
                    rPlatformParam.bySPType = (*it2).bySPType;
                    break;
                }

            }
            if (!bFound)
                it3->second.push_back((*it2));
        }
    }
}

void CUserMgr::UpdatePlatformParam(UINT64 qwRoleID, const NProtoCommon::TVecPlatformParam vecPlatform)
{
    auto it = _mapPlatformParam.find(qwRoleID);
    if (it == _mapPlatformParam.end())
        _mapPlatformParam.insert(make_pair(qwRoleID, vecPlatform));
    else
    {
        for (auto& rNewPlatfomParam : vecPlatform)
        {
            bool bFound = false;
            for (auto& rPlatformParam : it->second)
            {
                if (rNewPlatfomParam.byPtType == rPlatformParam.byPtType
                        && rNewPlatfomParam.byQQPtType == rPlatformParam.byQQPtType)
                {
                    bFound = true;
                    if(rPlatformParam.byQQPtLv != rNewPlatfomParam.byQQPtLv
                            || rPlatformParam.bySPType != rNewPlatfomParam.bySPType)
                        rPlatformParam = rNewPlatfomParam;
                    break;
                }

            }
            if (!bFound)
            {
                it->second.push_back(rNewPlatfomParam);
            }
        }
    }
}

const TVecPlatformParam& CUserMgr::GetPlatformParam(UINT64 qwRoleID)
{
    return _mapPlatformParam[qwRoleID];
}

void CUserMgr::ChangeLevel(UINT64 qwRoleID,UINT8 byOldLv,UINT8 byNewLv)
{
    UINT32 dwCount = 1;
    auto it = _mapmapType2Count.find(eActLevel);
    if(it == _mapmapType2Count.end())
        return;
    auto OldIt = it->second.find((UINT32)byOldLv);
    if(OldIt != it->second.end())
        OldIt->second -= dwCount;
    auto NewIt = it->second.find((UINT32)byNewLv);
    if(NewIt != it->second.end())
        NewIt->second += dwCount;
    else
        it->second.insert(make_pair((UINT32)byNewLv,dwCount));
}

UINT32 CUserMgr::GetCount(const UINT8 byType,const UINT32 dwID)
{
    UINT32 dwCount = 0;
    auto it = _mapmapType2Count.find(byType);
    if(it == _mapmapType2Count.end())
        return dwCount;
    if(byType == eActLevel)
    {
        for(auto oIt : it->second)
            if(dwID <= oIt.first)
                dwCount += oIt.second;
    }else
    {
        auto oI = it->second.find(dwID);
        if(oI == it->second.end())
            return dwCount;
        dwCount = oI->second;
    }
    return dwCount;
}

void  CUserMgr::SetRoleInfos(const UINT32 byType,const TVecRoleLevel &vecRet)
{
     if(byType > NGame2CenterComm::eActEnd)
         return;
     TMapID2Count &oMapID2Count = _mapmapType2Count[byType];
     for(auto oIt : vecRet)
     {
         UINT32 &dwCount = oMapID2Count[oIt.dwID];
         dwCount = oIt.vecRole.size();
     }
}

void CUserMgr::ChangeRoleInfo(const UINT8 byType,const UINT32 dwID,const UINT64 qwRoleID)
{
    auto it = _mapmapType2Count.find(byType);
    if(it == _mapmapType2Count.end())
        return;
    UINT32 dwCount = 1;
    auto oIt = it->second.find(dwID);
    if(oIt == it->second.end())
        it->second.insert(make_pair(dwID,dwCount));
    else
        oIt->second += dwCount;
}
