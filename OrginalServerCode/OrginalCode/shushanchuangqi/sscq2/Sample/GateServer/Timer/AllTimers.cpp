/********************************************************************
//	Gate Server Source File.
//	File name:	AllTimers.cpp
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

#include "AllTimers.h"

#include "stdafx.h"

void COneSecTimer::OnTimer()
{
	Config.TimerCheckInit();
}

void CFiveSecTimer::OnTimer()
{
	NetMgr.TimerCheck();
}

void CTenSecTimer::OnTimer()
{
	time_t tNow = time(NULL);
	NetMgr.GetSessionMgr().TimerCheck(tNow);
}

///////////////////////////////////////////////////////////////////////////////////

bool CTimerMgr::OpenAllTimer()
{
	if(!NetInterface::OpenTimer(_oOneSecTimer, 1000))
		return false;
	if(!NetInterface::OpenTimer(_oFiveSecTimer, 5 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oTenSecTimer, 10 * 1000))
		return false;
	return NetInterface::StartTimer();
}
