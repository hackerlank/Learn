/********************************************************************
//	Server Common Library Source File.
//	File name:	UsrSessMgr.cpp
//	Created:	2012/08/21	10:00
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
#include "UsrSessMgr.h"

UINT32 CUsrSessMgr::GetNewSession()
{
	UINT32 dwSessionID = _dwNextSessionID++;
	if(_dwNextSessionID == 0)
		_dwNextSessionID = 1;
	SSession& rSession = _mapID2Session[dwSessionID];
	rSession.tStartTime = time(NULL);
	return dwSessionID;
}

void CUsrSessMgr::DelSession(UINT32 dwSessionID)
{
	_mapID2Session.erase(dwSessionID);
}

bool CUsrSessMgr::StoreData(UINT32 dwSessionID, VoidPtr pData, FnTimeOutCallback fnOnTimeOut /*= nullptr*/)
{
	auto it = _mapID2Session.find(dwSessionID);
	if(it == _mapID2Session.end())
		return false;
	SSession& rSession = it->second;
	rSession.pData = pData;
	rSession.fnOnTimeOut = fnOnTimeOut;
	return true;
}

VoidPtr CUsrSessMgr::GetData(UINT32 dwSessionID)
{
	auto it = _mapID2Session.find(dwSessionID);
	if(it == _mapID2Session.end())
		return NULL;
	SSession& rSession = it->second;
	return rSession.pData;
}

void CUsrSessMgr::TimerCheck(time_t tNow)
{
	for(auto it = _mapID2Session.begin(); it != _mapID2Session.end();)
	{
		UINT32 dwSessionID = it->first;
		SSession& rSession = it->second;
		if(tNow > rSession.tStartTime && tNow - rSession.tStartTime > 10)
		{
			if(rSession.fnOnTimeOut != nullptr)
				rSession.fnOnTimeOut(dwSessionID);
			it = _mapID2Session.erase(it);
		}
		else
		{
			++it;
		}
	}
}
