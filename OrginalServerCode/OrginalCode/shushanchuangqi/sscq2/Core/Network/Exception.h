/********************************************************************
//  Server Network Library Source File.
//  File name:  Exception.h
//  Created:    2012/08/24  11:00
//  Organization:
//  Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//  Author:     Jingyuan Wang
//  E-Mail:     tyketom@hotmail.com
//  Http://
// ------------------------------------------------------------------
//  Purpose:
//  Version:    1.0
//  Histroy:
*********************************************************************/
#pragma once
#include <signal.h>
#include <setjmp.h>

//Linux异常处理
//使用信号处理程序来处理异常，在异常处理后，进程可以继续执行

class CException
{
	friend class CEPollMgr;
	friend class CNetIFMgr;
public:
	static bool Init();
	static void HandleTerm(int sig, siginfo_t* pInfo, void* context);
	static void HandleException(int sig, siginfo_t* pInfo, void* context);
	static pid_t DumpCore();
	static void RecordExit(bool bKill);
private:
	static sigjmp_buf _env;
};
