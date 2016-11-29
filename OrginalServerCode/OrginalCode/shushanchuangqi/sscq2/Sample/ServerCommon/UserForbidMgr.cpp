#include "stdafx.h"
#include "UserForbidMgr.h"

map<UINT64,SForbidData> CUsrForbidMgr::_mapUsr2ForbidData;
bool CUsrForbidMgr::Init()
{

	return true;
}
void CUsrForbidMgr::Destroy()
{
	_mapUsr2ForbidData.clear();
}
void CUsrForbidMgr::LoadDataFromDB(const SRow& rRow)
{
	UINT64 qwUsrID = 0;
	UINT32 dwLoginSetTime = 0;
	UINT32 dwLoginExpiredTime = 0;
	UINT32 dwTalkSetTime = 0;
	UINT32 dwTalkExpiredTime = 0;
	rRow[0] >> qwUsrID;
	rRow[1] >> dwLoginSetTime;
	rRow[2] >> dwLoginExpiredTime;
	rRow[3] >> dwTalkSetTime;
	rRow[4] >> dwTalkExpiredTime;

	if(qwUsrID > 0 && (dwLoginExpiredTime > time(NULL) || dwTalkExpiredTime > time(NULL)))
	{
		SForbidData sData(dwLoginExpiredTime, dwTalkExpiredTime);
		_mapUsr2ForbidData[qwUsrID] = sData;
	} 
}
SForbidData* CUsrForbidMgr::GetForbidDataByID(UINT64 qwUsrID)
{
	auto p = _mapUsr2ForbidData.find(qwUsrID);
	if(p != _mapUsr2ForbidData.end())
		return &(p->second);
	return NULL;
}
void CUsrForbidMgr::AddForbidData(UINT64 qwUsrID, UINT32 dwLoginSeconds, UINT32 dwTalkSeconds, bool bToDB)
{
	if(qwUsrID == 0)
		return;
	UINT32 tNow = (UINT32)time(NULL);
	SForbidData sData;
	if(dwLoginSeconds > 0)
		sData._dwLoginExpiredTime = tNow + dwLoginSeconds;
	if(dwTalkSeconds > 0)
		sData._dwTalkExpiredTime = tNow + dwTalkSeconds;

	_mapUsr2ForbidData[qwUsrID] = sData;

	if (bToDB)
		CForbidDB::UpdateData(qwUsrID, sData);

}
void CUsrForbidMgr::UnForbidLogin(UINT64 qwUsrID, bool bToDB)
{
	auto p = _mapUsr2ForbidData.find(qwUsrID);
	if(p != _mapUsr2ForbidData.end())
	{
		p->second._dwLoginExpiredTime = 0;
		if (bToDB)
			CForbidDB::UpdateData(qwUsrID, p->second);
	}
}
void CUsrForbidMgr::UnForbidTalk(UINT64 qwUsrID, bool bToDB)
{
	auto p = _mapUsr2ForbidData.find(qwUsrID);
	if(p != _mapUsr2ForbidData.end())
	{
		p->second._dwTalkExpiredTime = 0;
		if (bToDB)
			CForbidDB::UpdateData(qwUsrID, p->second);
	}
}
bool CUsrForbidMgr::IsForbidLogin(UINT64 qwUsrID)
{
	auto p = _mapUsr2ForbidData.find(qwUsrID);
	if(p != _mapUsr2ForbidData.end())
		return (p->second._dwLoginExpiredTime > (UINT32)time(NULL));
	return false;
}
bool CUsrForbidMgr::IsForbidTalk(UINT64 qwUsrID)
{
	auto p = _mapUsr2ForbidData.find(qwUsrID);
	if(p != _mapUsr2ForbidData.end())
		return (p->second._dwTalkExpiredTime > (UINT32)time(NULL));
	return false;
}
static void OnLoadAllForbidData(const TVecTable& rVecTable)
{
	if(rVecTable.empty())
		return;

	const STable& rTable = rVecTable[0];
	for(size_t idx = 0; idx < rTable.Size(); ++idx)
	{
		CUsrForbidMgr::LoadDataFromDB(rTable[idx]);
	}
}

void CForbidDB::OnResult(INT8 byRet, UINT32 dwAffectRow)
{
	if(byRet)
	{
		LOG_CRI << "Operate id=" << _eOperate << ", desc=" << GetOperateDesc(_eOperate) << ", ret=" << byRet;
		return;
	}
}

void CForbidDB::OnResultData(INT32 byRet, const TVecTable& rVecTable)
{
	if(byRet)
	{
		LOG_CRI << "Operate id="<< _eOperate << ", desc=" << GetOperateDesc(_eOperate) << ", ret=" << byRet;
		return;
	}

	switch(_eOperate)
	{
	case eOperateLoadAllForbidData:
		OnLoadAllForbidData(rVecTable);
		break;
	default:
		{
			LOG_CRI << "Unknown Operate id=" << _eOperate;
		}
	}
}

bool CForbidDB::LoadAllData()
{
	CForbidDBPtr pDB(new CForbidDB);
	if(pDB == NULL)
	{
		LOG_CRI << "CForbidDB Alloc Failed!";
		return false;
	}
	return pDB->LoadAllDataImpl();
}

bool CForbidDB::LoadAllDataImpl()
{
	_eOperate = eOperateLoadAllForbidData;
	SetHasResult(true);
	AddSQL("select UsrID,UNIX_TIMESTAMP(LoginSetTime),UNIX_TIMESTAMP(LoginExpiredTime),UNIX_TIMESTAMP(TalkSetTime),UNIX_TIMESTAMP(TalkExpiredTime) from tblforbid;");
	return g_DBQueryMgr.DoQuery(*this);
}

bool CForbidDB::UpdateData(UINT64 qwUsrID, SForbidData& oData)
{
	CForbidDBPtr pDB(new CForbidDB);
	if(pDB == NULL)
	{
		LOG_CRI << "CForbidDB Alloc Failed!";
		return false;
	}
	return pDB->UpdateDataImpl(qwUsrID, oData);
}
bool CForbidDB::UpdateDataImpl(UINT64 qwUsrID, SForbidData& oData)
{
	_eOperate = eOperateUpdateForbidData;
	UINT32 dwLoginSetTime = 0;
	UINT32 dwTalkSetTime = 0;
	if(oData._dwLoginExpiredTime > time(NULL))
		dwLoginSetTime = (UINT32)time(NULL);
	if(oData._dwTalkExpiredTime > time(NULL))
		dwTalkSetTime = (UINT32)time(NULL);

	AddSQL("replace INTO tblforbid(UsrID, LoginSetTime, LoginExpiredTime, TalkSetTime, TalkExpiredTime) VALUES(%1,FROM_UNIXTIME(%2),FROM_UNIXTIME(%3),FROM_UNIXTIME(%4),FROM_UNIXTIME(%5))");

	AddParam<eTypeUINT64>(qwUsrID);
	AddParam<eTypeUINT32>(dwLoginSetTime);
	AddParam<eTypeUINT32>(oData._dwLoginExpiredTime);
	AddParam<eTypeUINT32>(dwTalkSetTime);
	AddParam<eTypeUINT32>(oData._dwTalkExpiredTime);
	return g_DBQueryMgr.DoQuery(*this);
}
