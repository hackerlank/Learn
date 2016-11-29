/********************************************************************
//	Server Common Library Source File.
//	File name:	SessionMgr.cpp
//	Created:	2012/08/21	11:00
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

#include <time.h>
#include "SessionMgr.h"

UINT32 CSessionMgr::GetNewSession(IProtocol& rProtocol, UINT8 byFuncID)
{
	UINT32 dwSessionID = _dwNextSessionID++;
	if(_dwNextSessionID == 0)
		_dwNextSessionID = 1;
	SSession& rSession = _mapID2Session[dwSessionID];
	rSession._pProtocol = &rProtocol;
	rSession._byFuncID = byFuncID;
	rSession._tStartTime = time(NULL);
	return dwSessionID;
}

void CSessionMgr::DelSession(UINT32 dwSessionID)
{
	_mapID2Session.erase(dwSessionID);
}

bool CSessionMgr::StoreData(UINT32 dwSessionID, VoidPtr pData)
{
	auto it = _mapID2Session.find(dwSessionID);
	if(it == _mapID2Session.end())
		return false;
	SSession& rSession = it->second;
	rSession._pData = pData;
	return true;
}

VoidPtr CSessionMgr::GetData(UINT32 dwSessionID)
{
	auto it = _mapID2Session.find(dwSessionID);
	if(it == _mapID2Session.end())
		return NULL;
	SSession& rSession = it->second;
	return rSession._pData;
}

void CSessionMgr::TimerCheck(time_t tNow)
{
#ifdef _WIN32
	INT32 dwMaxTime = 100;
	if(IsDebuggerPresent())
		dwMaxTime = 1000;
#else
	const INT32 dwMaxTime = 10;
#endif
	for(auto it = _mapID2Session.begin(); it != _mapID2Session.end();)
	{
		UINT32 dwSessionID = it->first;
		SSession& rSession = it->second;
		if(tNow > rSession._tStartTime && tNow - rSession._tStartTime > dwMaxTime)
		{
			rSession._pProtocol->OnTimeOut(rSession._byFuncID, dwSessionID);
			it = _mapID2Session.erase(it);
		}
		else
		{
			++it;
		}
	}
}
