#pragma once

#include "DBQueryMgr.h"

struct SForbidData 
{
	SForbidData():
		_dwLoginExpiredTime(0),
		_dwTalkExpiredTime(0)
	{
	}
	SForbidData(UINT32 dwLoginExpiredTime, UINT32 dwTalkExpiredTime):
		_dwLoginExpiredTime(dwLoginExpiredTime),
		_dwTalkExpiredTime(dwTalkExpiredTime)
	{
	}
	UINT32 _dwLoginExpiredTime;
	UINT32 _dwTalkExpiredTime;
};
class CUsrForbidMgr
{
public:
	static bool Init();
	static void Destroy();
	static void LoadDataFromDB(const SRow& rRow);
	static SForbidData* GetForbidDataByID(UINT64);
	static void AddForbidData(UINT64 qwUsrID, UINT32 dwLoginSeconds, UINT32 dwTalkSeconds, bool bToDB=true);
	static void UnForbidLogin(UINT64 qwUsrID, bool bToDB=true);
	static void UnForbidTalk(UINT64 qwUsrID, bool bToDB=true);
	static bool IsForbidLogin(UINT64 qwUsrID);
	static bool IsForbidTalk(UINT64 qwUsrID);
private:
	static map<UINT64,SForbidData> _mapUsr2ForbidData;
};

class CForbidDB : public IDBQuery
{
public:

	enum EOperateType
	{
		eOperateNone,
		eOperateLoadAllForbidData,
		eOperateUpdateForbidData,
	};

	static const char* GetOperateDesc(EOperateType eOperate)
	{
		if(eOperate == eOperateNone)
			return "None";
		else if(eOperate == eOperateLoadAllForbidData)
			return "LoadAllForbidData";
		else if(eOperate == eOperateUpdateForbidData)
			return "UpdateForbidData";
		return "Unknown";
	}

	CForbidDB() : _eOperate(eOperateNone) { }
	DEF_NEW_DELETE(CForbidDB);

	static bool LoadAllData();
	bool LoadAllDataImpl();

	static bool UpdateData(UINT64 qwUsrID, SForbidData& oData);
	bool UpdateDataImpl(UINT64 qwUsrID, SForbidData& oData);

private:
	// IDBQuery impl
	virtual void OnResult(INT8 byRet, UINT32 dwAffectRow);
	virtual void OnResultData(INT32 byRet, const TVecTable& rVecTable);

private:
	EOperateType _eOperate;
};
