/********************************************************************
//	Center Server Source File.
//	File name:	UserMgr.h
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

#pragma once
#include "User.h"
#include "Game2CenterComm.h"


typedef map<UINT8, set<UINT64>> TMapLevel2User;
typedef map<UINT8, TMapLevel2User> TMapCamp2LevelUser;
typedef map<UINT32,UINT32> TMapID2Count; 

class CUserMgr
{
	friend class CUser;
public:
	static void Destroy();
	static CUserPtr CreateUser(UINT64 qwUsrID);
	static void RemoveUser(UINT64 qwUsrID);
	static void RegisterRoleID(UINT64 qwUsrID, UINT64 qwRoleID);
	static CUserPtr GetUserByUserID(UINT64 qwUsrID);
	static CUserPtr GetUserByName(const string& strName);
    static bool MapUserName2ID(const string& strName, UINT64 qwUserID);
	static UINT32 GetUserCount();
	static bool KickUserOffLine(UINT64 qwUsrID, bool bException = false);
    static bool KickUserOffLineReason(UINT64 qwUsrID,ELeaveType eELeaveType = eLeaveKick);
	static bool IsOnline(UINT64 qwUsrID);

	static UINT32 GenSessionKey();

	static void TimerCheck(time_t tNow);

	static map<UINT64, CUserPtr>& GetUsrMap() { return _mapID2Usr; }

	static UINT16 GetActiveUserCount() { return _wActiveUserCount; }
	static void IncActiveUserCount();
	static void DecActiveUserCount();

	static void OnUserPropChanged(CUser& rUser, NGame2CenterComm::EUserSyncPropField eField, const std::string& strVal);

	static void UpdateUserLevel(CUser& rUser, UINT8 byOldLevel = 0);
	static void RemoveUserLevel(CUser& rUser);
	static TMapLevel2User* GetUserLevelRange(UINT8 byNation);

	static void AddExceptUser(UINT64 qwUsrID);
	static bool HasException(UINT64 qwUsrID);

    static void InitPlatformParam(UINT32 dwCurSize, UINT32 dwTotalSize, const TVecUINT64& vecRoleID, const NProtoCommon::TVecPlatformParam& vecPlatform);
    static void UpdatePlatformParam(UINT64 qwRoleID, const NProtoCommon::TVecPlatformParam vecPlatform);
    static const TVecPlatformParam& GetPlatformParam(UINT64 qwRoleID);
    static void ChangeLevel(UINT64 qwRoleID,UINT8 byOldLv,UINT8 byNewLv);
    static UINT32 GetCount(const UINT8 byType,const UINT32 byLevel);
    static void   GetRoleIDs(const UINT8 byType,const UINT32 byLevel,TSetUINT64 &setRoleID);
    static void   SetRoleIDs(const UINT8 byType,const UINT32 byLevel,TSetUINT64 &setRoleID);
    static void   SetRoleInfos(const UINT32 byType,const TVecRoleLevel &vecRet);
    static void   ChangeRoleInfo(const UINT8 byType,const UINT32 dwID,const UINT64 qwRoleID);
protected:
	static void RemoveUser(map<UINT64, CUserPtr>::iterator it);
	static map<UINT64, CUserPtr> _mapID2Usr;
	static map<UINT64, UINT64> _mapRole2UsrID;
	static map<string, UINT64> _mapName2UsrID;
	static TMapCamp2LevelUser _mapNationLevel2UsrID;
	static unordered_set<UINT64> _setUserExcept;
	static UINT16 _wActiveUserCount;
    static map<UINT64, TVecPlatformParam> _mapPlatformParam;
    
    static map<UINT8,TMapID2Count> _mapmapType2Count;
    static map<UINT8,UINT32> _mapLevel2Count;
};
