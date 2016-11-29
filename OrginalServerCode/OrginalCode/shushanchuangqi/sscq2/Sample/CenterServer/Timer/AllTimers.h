/********************************************************************
//	Center Server Source File.
//	File name:	AllTimers.h
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

#include "Interface.h"

#include "Singleton.h"

class COneSecTimer : public ITimer
{
public:
	void OnTimer();
};

class CTwoSecTimer : public ITimer
{
public:
	void OnTimer();
};

class CFiveSecTimer : public ITimer
{
public:
	void OnTimer();
};

class CTenSecTimer : public ITimer
{
public:
	void OnTimer();
};

class COneMinTimer: public ITimer
{
public:
	void OnTimer();
};

class CFiveMinTimer: public ITimer
{
public:
	void OnTimer();
};

class CTenMinTimer: public ITimer
{
public:
	void OnTimer();
};

class CHalfHourTimer: public ITimer
{
public:
	void OnTimer();
};

class COneHourTimer: public ITimer
{
public:
	void OnTimer();
};

class CInitTimer : public ITimer
{
public:
	void OnTimer();
};

class CTimerMgr : public StaticSingleton<CTimerMgr>
{
public:
	bool OpenAllTimer();

	CInitTimer& GetInitTimer() { return _oInitTimer; }
protected:
	COneSecTimer _oOneSecTimer;
	CTwoSecTimer _oTwoSecTimer;
	CFiveSecTimer _oFiveSecTimer;
	CTenSecTimer _oTenSecTimer;
	COneMinTimer _oOneMinTimer;
	CFiveMinTimer _oFiveMinTimer;
	CTenMinTimer _oTenMinTimer;
    CHalfHourTimer _oHalfHourTimer;
    COneHourTimer _oOneHourTimer;
	CInitTimer _oInitTimer;
};
