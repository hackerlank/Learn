/********************************************************************
//	Server Utility Library Source File.
//	File name:	Time.h
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
#include <sys/time.h>
#include "Linux.h"

UINT32 GetTickCount();
UINT64 GetTickCount64();

class CElapseTimer
{
public:
	CElapseTimer();
	UINT64 GetElapsedMicroSecond();
protected:
	timeval _start;
};
