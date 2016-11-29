/********************************************************************
//	Server Common Library Source File.
//	File name:	UsrSessMgr.h
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

#pragma once
#include <map>
#include <memory>
#include <functional>
#include "Platform.h"
#include "Singleton.h"

using namespace std;

typedef shared_ptr<void> VoidPtr;
typedef function<void (UINT32 dwSessionID)> FnTimeOutCallback;

class CUsrSessMgr : public StaticSingleton<CUsrSessMgr>
{
	struct SSession
	{
		VoidPtr pData;
		time_t tStartTime;
		FnTimeOutCallback fnOnTimeOut;

		SSession() : tStartTime(0) { }
	};
public:
	CUsrSessMgr() : _dwNextSessionID(1) { }
	UINT32 GetNewSession();
	void DelSession(UINT32 dwSessionID);

	bool StoreData(UINT32 dwSessionID, VoidPtr pData, FnTimeOutCallback fnOnTimeOut = nullptr);
	VoidPtr GetData(UINT32 dwSessionID);
	void TimerCheck(time_t tNow);
protected:
	
	UINT32 _dwNextSessionID;
	map<UINT32, SSession> _mapID2Session;
};
