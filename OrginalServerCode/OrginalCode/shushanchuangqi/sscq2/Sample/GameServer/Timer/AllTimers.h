/********************************************************************
//	Game Server Source File.
//	File name:	AllTimers.h
//	Created:	2011/05/30	10:00
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

#include "stdafx.h"

#include "Interface.h"
#include "Singleton.h"

class IArTimer : public ITimer
{
public:
	IArTimer() : _dwIndex(0) { }
	void SetIndex(UINT32 dwIndex) { _dwIndex = dwIndex; } 

protected:
	UINT32 _dwIndex;
};

//100ms定时器
class COneMSecTimer : public ITimer
{
public:
	void OnTimer();
};

//500ms定时器
class CFiveMSecTimer : public ITimer
{
public:
	void OnTimer();
};

class COneSecTimer : public ITimer
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

class COneMinTimer : public ITimer
{
public:
	void OnTimer();
};

class CFifteenMinTimer : public ITimer
{
public:
	void OnTimer();
};

class CInitTimer : public ITimer
{
public:
	void OnTimer();
};

class CWalkTimer : public IArTimer
{
public:
	void OnTimer();
};

class CUserTimer : public ITimer
{
public:
    void OnTimer();
};

class CDungeonTimer : public ITimer
{
public:
    void OnTimer();
};

class CSwitcherTimer : public ITimer
{
public:
    void OnTimer();
};
class CMstFastFuncTimer : public IArTimer
{
    public:
        void OnTimer();
};
class CMstSlowFuncTimer : public IArTimer
{
    public:
        void OnTimer();
};
class CTimerMgr : public StaticSingleton<CTimerMgr>
{
public:
	bool OpenAllTimer();

	CInitTimer& GetInitTimer() { return _oInitTimer; }
	CInitTimer& GetInitTimerForCenter() { return _oInitCenterTimer; }
    void CallMem();
protected:
	COneSecTimer _oOneSecTimer;
	CFiveSecTimer _oFiveSecTimer;
	CTenSecTimer _oTenSecTimer;
	COneMinTimer _oOneMinTimer;
    CFifteenMinTimer _oFifteenMinTimer;
	CInitTimer _oInitTimer;
	CInitTimer _oInitCenterTimer;
	CWalkTimer _arWalkTimer[PLAYER_WALK_MAP_COUNT];
    CUserTimer _oUserTimer;
    CDungeonTimer _oDungeonTimer;
    CSwitcherTimer _oSwitcherTimer;
    CMstFastFuncTimer _arMstFastFuncTimer[FAST_MONSTER_MAP_COUNT];
    CMstSlowFuncTimer _arMstSlowFuncTimer[SLOW_MONSTER_MAP_COUNT];
};
