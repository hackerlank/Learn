/********************************************************************
//	Gate Server Source File.
//	File name:	AllTimers.h
//	Created:	2011/06/03	10:00
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
	COneSecTimer() : _bGateInfoSent(false) { }
	void OnTimer();
	void SetGateInfoSent(bool bSent) { _bGateInfoSent = bSent; }
protected:
	bool _bGateInfoSent;
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

class CTimerMgr : public StaticSingleton<CTimerMgr>
{
public:
	bool OpenAllTimer();

	COneSecTimer& GetOneSecTimer() { return _oOneSecTimer; }

protected:
	COneSecTimer _oOneSecTimer;
	CFiveSecTimer _oFiveSecTimer;
	CTenSecTimer _oTenSecTimer;
};
