#pragma once
#include "User.h"

#define  MAX_VIP_LEVEL 9

struct SUsrInfo 
{
	SUsrInfo() : _qwUsrID(0), _byVIPLevel(0) { }

	SUsrInfo(UINT64 qwID, string strName,UINT8 byVIPLevel = 0):
		_qwUsrID(qwID),
		_strUsrName(strName),
		_byVIPLevel(byVIPLevel) { }

	UINT64 _qwUsrID;
	string _strUsrName;
	UINT8 _byVIPLevel;
};

typedef map<UINT64, SUsrInfo> TMapID2UsrInfo;
typedef map<string, UINT64> TMapName2ID;

class CUsrInfoMgr
{
public:
	static void Destroy();
	static void AddUser(SUsrInfo& rInfo);
	static UINT64 GetUsrIDByName(string strName);
	static SUsrInfo* GetUsrInfo(UINT64 qwUsrID);
	static UINT32 GetUsrCount();
	//static bool LoadAllUser();
	static TMapID2UsrInfo& GetAllUsrInfo() { return _mapID2User; }
private:
	static TMapID2UsrInfo _mapID2User;
	static TMapName2ID    _mapName2ID;
};
