/********************************************************************
//	Game Server Source File.
//	File name:	UserMgr.h
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

#pragma once
#include "User.h"
#include "Point.h"

#include "ServerCommon.h"
#include "RankProt.h"

using namespace NServerCommon;
using namespace NRankProt;

typedef map<UINT64, CUserPtr> TMapID2Usr;

struct SBornCampInfo
{
    UINT16 wMapID;
    SPoint oPoint;
};

struct SBornItemInfo
{
    UINT16 wItemID;
    UINT8 byQuality;
    UINT16 wCount;
};

struct SBornInfo
{
    map<UINT8, SBornCampInfo> mapCamp2Info;
    map<UINT8, vector<SBornItemInfo>> mapJob2ItemList;
    map<UINT8, UINT32> mapJob2Skill;
};
typedef function<void(CUserPtr pUser)> FunLoadUser;
class CUserMgr
{
    public:
        static bool Init();
        static void Destroy();
        static CUserPtr CreateUser(UINT64 qwUsrID);
        static void RemoveUser(UINT64 qwUsrID);
        static void RemoveUser(TMapID2Usr::iterator it);
        static CUserPtr GetUserByUserID(UINT64 qwUsrID);

        static bool SendPkg(const TVecUINT64& vecUsrID, const string& strPkg);

        static bool OnUserBorn(CUser& rUser);
        static bool OnUserLeave(UINT64 qwUsrID, ELeaveType eLeaveType);
        static bool OnUserLeave(CUser& rUser, ELeaveType eLeaveType);
        static bool KickUserOffLine(UINT64 qwUsrID, bool bException = false);
        static bool KickUserOffLineReason(UINT64 qwUsrID, ELeaveType eELeaveType);
        static bool ForceKickUserOffLine(UINT64 qwUsrID, bool bException = false);

        static void TimerCheck(time_t tNow);
        static void DailyReset(ETimePointType eType);

        static void AddExceptUser(UINT64 qwUsrID);
        static bool HasException(UINT64 qwUsrID);
        static SBornInfo& GetBornInfo() { return _oBornInfo; }

        static CPlayerPtr CreatePlayer(UINT64 qwRoleID, const CUserPtr& pUser);
        static void LoadUser(UINT64 qwRoleID, FunLoadUser fun);

        static void InsertLevelRank(UINT64 qwRoleID, SRRLevelInfoPtr pInfo);
        static void EraseLevelRank(UINT64 qwRoleID);
        static void SyncLevelRank();
        //测试用
        static TMapID2Usr& GetUsrMap() { return _mapID2Usr; }

        static void PrintUserSize();
        static void OpenIcon(UINT32 dwActID,bool bNotify=true);
        static void CloseIcon(UINT32 dwActID,bool bNotify = true);
        static bool CheckIcon(UINT32 dwActID);
        static void AddIcon(UINT32 dwActID,bool bOpen,bool bNotify=true);
        static void GetOnlineUser(TMapID2Usr& mapID2Usr);

    protected:
        static TMapID2Usr _mapID2Usr;
        static map<string, CUserPtr> _mapName2Usr;
        static unordered_set<UINT64> _setUserExcept;

        static SBornInfo _oBornInfo;

        static map<UINT64, SRRLevelInfoPtr> _mapRankLevel;
        static map<UINT32, bool> _mapActID2State;
};

