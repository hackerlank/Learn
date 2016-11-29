/********************************************************************
//	Server Utility Library Source File.
//	File name:	Time.cpp
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

#include "LinuxTime.h"

/*
 *
 *bref  GetTickCount（）保存的是系统的毫秒数值

 *
 */
UINT32 GetTickCount()
{
	timeval ts;
	gettimeofday(&ts, NULL);
	return UINT32(ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

UINT64 GetTickCount64()
{
	timeval ts;
	gettimeofday(&ts, NULL);
	return UINT64(ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

CElapseTimer::CElapseTimer()
{
	gettimeofday(&_start, NULL);
}

UINT64 CElapseTimer::GetElapsedMicroSecond()
{
	timeval end;
	gettimeofday(&end, NULL);
	return (end.tv_sec - _start.tv_sec) * 1000000 + (end.tv_usec - _start.tv_usec);
}
