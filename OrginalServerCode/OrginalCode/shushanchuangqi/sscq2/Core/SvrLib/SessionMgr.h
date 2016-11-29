/********************************************************************
//	Server Common Library Source File.
//	File name:	SessionMgr.h
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

#pragma once
#include <map>
#include <memory>
#include "Interface.h"

using namespace std;

typedef shared_ptr<void> VoidPtr;

class CSessionMgr
{
	struct SSession
	{
		SSession() : _pProtocol(NULL), _byFuncID(0), _tStartTime(0) { } 
		IProtocol* _pProtocol;
		UINT8 _byFuncID;
		VoidPtr _pData;
		time_t _tStartTime;
	};
public:
	CSessionMgr() : _dwNextSessionID(1) { }
	UINT32 GetNewSession(IProtocol& rProtocol, UINT8 byFuncID);
	void DelSession(UINT32 dwSessionID);
	bool StoreData(UINT32 dwSessionID, VoidPtr pData);
	VoidPtr GetData(UINT32 dwSessionID);
	void TimerCheck(time_t tNow);
protected:
	UINT32 _dwNextSessionID;
	map<UINT32, SSession> _mapID2Session;
};
