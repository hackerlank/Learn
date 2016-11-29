/********************************************************************
//	Center Server Source File.
//	File name:	AllTimers.cpp
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

#include "AllTimers.h"

#include "stdafx.h"
#include "Protocols.h"
#include "TimePointMgr.h"
#include "ArenaManager.h"
#include "DemonTowerMgr.h"
#include "UserMgr.h"
#include "GuildMgr.h"
#include "RankMgr.h"
#include "WonderActivityMgr.h"
#include "TripodManager.h"
#include "UDPLog.h"
#include "Answer.h"
#include "ShipManager.h"
#include "DragonBallActMgr.h"
#include "GuildXiheManager.h"
#include "DayActivityMgr.h"
#include "ActivityMgr.h"
#include "SevenConsumeActMgr.h"
///////////////////////////////////////////////////////////////////////////////////
void COneSecTimer::OnTimer()
{
	time_t tNow = time(NULL);
	Config.TimerCheckInit();
    CArenaManager::CalRank();
    CUserMgr::TimerCheck(tNow);
    CGuildMgr::Instance().TimeCheck(tNow);
    AnswerMgr.TimerCheck(tNow);
    g_ShipManager.TimerCheck();
    CDragonBallActMgr::Instance().TimeCheck(tNow);
    GuildXiheManager.TimerCheck(tNow);
    g_DayActivityMgr.TimerCheck(tNow);
    g_WonderActivityMgr.TimerCheck(tNow);
}

void CTwoSecTimer::OnTimer()
{
}

void CFiveSecTimer::OnTimer()
{
	time_t tNow = time(NULL);
	NetMgr.TimerCheck();
    
    g_DemonTowerMgr.TimerCheck(tNow);
#ifdef _DEBUG
    CRankMgr::Instance().ClearSurplusRank();
#endif
    CRankMgr::Instance().TimeCheck(tNow);
    TripodManager.TimerCheck(tNow);
}

void CTenSecTimer::OnTimer()
{
	time_t tNow = time(NULL);
    g_ActivityMgr.TimerCheck();
	NetMgr.GetSessionMgr().TimerCheck(tNow);
    CSevenConsumeActMgr::Instance().TimerCheck();
}

void COneMinTimer::OnTimer()
{
	time_t tNow = time(NULL);
    g_WonderActivityMgr.OneMinCheck(tNow);
    g_DayActivityMgr.OnMinuteCheck(tNow);
	CTimePointMgr::TimerCheck(tNow);
}

void CFiveMinTimer::OnTimer()
{
	time_t tNow = time(NULL);
    CUDPLogMgr::TimerCheck(tNow);
}

void CTenMinTimer::OnTimer()
{
    g_PHPProtS.TimerCheck();
}

void CHalfHourTimer::OnTimer()
{
}

void COneHourTimer::OnTimer()
{
#ifndef _DEBUG
    CRankMgr::Instance().ClearSurplusRank();
#endif
}

void CInitTimer::OnTimer()
{
	g_Center2DBCommC.TimerCheck();
}

///////////////////////////////////////////////////////////////////////////////////

bool CTimerMgr::OpenAllTimer()
{
	if(!NetInterface::OpenTimer(_oOneSecTimer, 1000))
		return false;
	if(!NetInterface::OpenTimer(_oTwoSecTimer, 2 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oFiveSecTimer, 5 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oTenSecTimer, 10 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oOneMinTimer, 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oFiveMinTimer, 5 * 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oTenMinTimer, 10 * 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oHalfHourTimer, 30 * 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oOneHourTimer, 60 * 60 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oInitTimer, 1000))
		return false;
	return NetInterface::StartTimer();
}
