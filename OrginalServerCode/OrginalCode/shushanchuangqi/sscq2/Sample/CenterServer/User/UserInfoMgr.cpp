#include "stdafx.h"
#include "UserInfoMgr.h"
#include "Protocols.h"

TMapID2UsrInfo CUsrInfoMgr::_mapID2User;
TMapName2ID    CUsrInfoMgr::_mapName2ID;

void CUsrInfoMgr::Destroy()
{
	_mapID2User.clear();
	_mapName2ID.clear();
}

void CUsrInfoMgr::AddUser(SUsrInfo& rInfo)
{
	if(rInfo._qwUsrID != 0 && !rInfo._strUsrName.empty())
	{
		if(NULL == GetUsrInfo(rInfo._qwUsrID))
		{
			_mapID2User[rInfo._qwUsrID] = rInfo;
			_mapName2ID[rInfo._strUsrName] = rInfo._qwUsrID;
		}
	}
}

UINT64 CUsrInfoMgr::GetUsrIDByName(string strName)
{
	auto p = _mapName2ID.find(strName);
	if(p != _mapName2ID.end())
		return p->second;
	return 0;
}

UINT32 CUsrInfoMgr::GetUsrCount()
{
	return (UINT32)(_mapID2User.size());
}

/*
bool CUsrInfoMgr::LoadAllUser()
{
}
*/

SUsrInfo* CUsrInfoMgr::GetUsrInfo(UINT64 qwUsrID)
{
	auto p = _mapID2User.find(qwUsrID);
	if(p != _mapID2User.end())
		return &(p->second);
	return NULL;
}

