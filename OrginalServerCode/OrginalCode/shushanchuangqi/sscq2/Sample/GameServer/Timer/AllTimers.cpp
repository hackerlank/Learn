/********************************************************************
//	Game Server Source File.
//	File name:	AllTimers.cpp
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

#include "AllTimers.h"

#include "stdafx.h"
#include "Walker.h"
#include "UserMgr.h"
#include "DungeonMgr.h"
#include "Protocols.h"
#include "TimePointMgr.h"
#include "GatherMgr.h"
#include "SwitcherMgr.h"
#include "BlockerMgr.h"
#include "ManagerMonsterAI.h"
#include "WorldBossMgr.h"
#include "ShushanBattleMgr.h"
#include "DayActivityMgr.h" 
#include "GuildBattleMgr.h"
#include "NewGuildBattleMgr.h"
#include "WondActMgr.h"
#include "DBQueryMgr.h"
#include "GameNetMgr.h"

static void DebugBreakHelper()
{
#ifdef _DEBUG
	DebugBreak();
#endif
}

#define TIMER_BEGIN \
	UINT64 qwStartTick = GetTickCount64(); \
	try { \

#define TIMER_END \
	} \
	catch(std::exception& ex) \
	{ \
		LOG_CRI << "Exception caught: " << ex.what() << " Timer Type: " << typeid(*this).name(); \
		DebugBreakHelper(); \
	} \
	catch(...) \
	{ \
		LOG_CRI << "Exception caught! " << " Timer Type: " << typeid(*this).name(); \
		DebugBreakHelper(); \
	} \
	UINT64 qwDiffTick = GetTickCount64() - qwStartTick; \
	if(qwDiffTick > FRAME_OVERTIME_LIMIT) \
		LNF_CRI << __FUNCTION__ << " Overtime: " << qwDiffTick;

void COneSecTimer::OnTimer()
{
	TIMER_BEGIN;
	Config.TimerCheckInit();
	time_t tNow = time(NULL);
    CGatherMgr::TimerCheck(tNow);
    CGuildBattleMgr::Instance().TimerCheck(tNow);
    NNewGuildBattle::CBattleMgr::Instance().TimerCheck(tNow);
    g_DayActivityMgr.TimerCheck(tNow);
    CGameBuffMgr::Instance().TimerCheck(tNow);
	TIMER_END;
}

void CFiveSecTimer::OnTimer()
{
	TIMER_BEGIN;
	NetMgr.TimerCheck();
	time_t tNow = time(NULL);
    CWorldBossMgr::Instance().TimerCheck(tNow);
    ShushanBattleMgr.TimerCheck(tNow);
#ifdef _DEBUG
    CUserMgr::SyncLevelRank();
#endif
	TIMER_END;
}

void CTenSecTimer::OnTimer()
{
    
	TIMER_BEGIN;
	time_t tNow = time(NULL);
	NetMgr.GetSessionMgr().TimerCheck(tNow);
	g_DBQueryMgr.TimerCheck(tNow);
	CTimePointMgr::TimerCheck(tNow);
    g_WondActMgr.TimerCheck(tNow);
	TIMER_END;
}

void COneMinTimer::OnTimer()
{
	TIMER_BEGIN;
	time_t tNow = time(NULL);
    g_DayActivityMgr.OnMinuteCheck(tNow);
    g_WondActMgr.OneMinCheck(tNow);
    //CTimerMgr::Instance().CallMem();
	TIMER_END;
}
void CTimerMgr::CallMem()
{
    std::map<std::string,UINT64> Count;
    PoolRecord::GetUseCount(Count);
    LOG_CRI << "Check all Mem";
    for(auto it = Count.begin();it != Count.end();it++)
    {
        LOG_CRI << it->first << ": " << it->second;
    }
}
void CFifteenMinTimer::OnTimer()
{
    TIMER_BEGIN;
#ifndef _DEBUG
    CUserMgr::SyncLevelRank();
#endif
    CTimerMgr::Instance().CallMem();
	TIMER_END;
}

void CInitTimer::OnTimer()
{
	TIMER_BEGIN;
    g_Game2DBCommC.TimerCheck();
    g_Game2CenterCommC.TimerCheck();
	TIMER_END;
}

void CWalkTimer::OnTimer()
{
	TIMER_BEGIN;
	CWalkerMgr::TimerCheck(_dwIndex);
	TIMER_END;
}

void CUserTimer::OnTimer()
{
    TIMER_BEGIN;
    time_t tNow = time(NULL);
    CUserMgr::TimerCheck(tNow);
    TIMER_END;
}


void CDungeonTimer::OnTimer()
{
    TIMER_BEGIN;
    time_t tNow = time(NULL);
    CDungeonMgr::TimerCheck(tNow);
    TIMER_END;
}

void CSwitcherTimer::OnTimer()
{
    TIMER_BEGIN;
    CSwitcherMgr::TimerCheck();
    CBlockerMgr::TimerCheck();
    TIMER_END;
}
void CMstFastFuncTimer::OnTimer()
{
   TIMER_BEGIN;
    time_t tNow = time(NULL);
    g_MonsterAIManager.TimerCheckFast(_dwIndex, tNow);
    TIMER_END;
}

void CMstSlowFuncTimer::OnTimer()
{
   TIMER_BEGIN;
    time_t tNow = time(NULL);
    g_MonsterAIManager.TimerCheckSlow(_dwIndex, tNow);
    TIMER_END;
}

bool CTimerMgr::OpenAllTimer()
{
	if(!NetInterface::OpenTimer(_oOneSecTimer, 1000))
		return false;
	if(!NetInterface::OpenTimer(_oFiveSecTimer, 5 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oTenSecTimer, 10 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oOneMinTimer, 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oFifteenMinTimer, 15 * 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oInitTimer, 1000))
		return false;
	if(!NetInterface::OpenTimer(_oInitCenterTimer, 1000))
		return false;
    if(!NetInterface::OpenTimer(_oDungeonTimer, 1000))
        return false;
    if(!NetInterface::OpenTimer(_oUserTimer, 1000))
        return false;
     if(!NetInterface::OpenTimer(_oSwitcherTimer, 1000))
        return false;
	for(UINT32 dwIndex = 0; dwIndex < PLAYER_WALK_MAP_COUNT; ++dwIndex)
	{
		_arWalkTimer[dwIndex].SetIndex(dwIndex);
		if(!NetInterface::OpenTimer(_arWalkTimer[dwIndex], 100))
			return false;
	}
    for(UINT32 dwIndex = 0; dwIndex < FAST_MONSTER_MAP_COUNT; ++dwIndex)
	{
		_arMstFastFuncTimer[dwIndex].SetIndex(dwIndex);
		if(!NetInterface::OpenTimer(_arMstFastFuncTimer[dwIndex],FAST_MONSTER_TIMER_INTERVAL))
			return false;
	}
    for(UINT32 dwIndex = 0; dwIndex < SLOW_MONSTER_MAP_COUNT; ++dwIndex)
	{
		_arMstSlowFuncTimer[dwIndex].SetIndex(dwIndex);
		if(!NetInterface::OpenTimer(_arMstSlowFuncTimer[dwIndex],SLOW_MONSTER_TIMER_INTERVAL))
			return false;
	}
	return NetInterface::StartTimer();
}

