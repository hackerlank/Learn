/********************************************************************
//	Server Utility Library Source File.
//	File name:	Event.h
//	Created:	2012/08/24	11:00
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
#ifdef _WIN32
#include <Windows.h>
#else
#include <Linux.h>
#endif

class CEvent
{
public:
	CEvent(bool bAutoReset = false);
	~CEvent();
	bool Set();
	bool Reset();
	bool Wait();
	bool Wait(UINT32 dwMilliSeconds);
private:
#ifdef _WIN32
	HANDLE _event;
#else
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
	bool _bSignaled;
#endif
	bool _bAutoReset;
};
