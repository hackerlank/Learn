/********************************************************************
//  Server Network Library Source File.
//  File name:  GlobalDefine.h
//  Created:    2012/08/21  11:00
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
#ifdef __GNUG__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <Linux.h>
#else
#include <WinSock2.h>
#include <MSWSock.h>
#include <Windows.h>
#endif
#include <string>

using std::string;

#define USE_LOG 1

#ifdef _DEBUG
#define DEF_NET_NEW_DELETE DEF_NEW_DELETE_MT_WRAP
#else
#define DEF_NET_NEW_DELETE DEF_NEW_DELETE_MT
#endif

#ifndef _DEBUG
#define ROBUST_USER_LOGIC
#endif

#define SERVER_LOGIC_MAX_MILLISECOND 100
#define USER_LOGIC_MAX_MILLISECOND 50
#define MAX_COMPLETION_THREAD_COUNT 32

#if USE_LOG
#define OPEN_CRI
#define OPEN_WRN
#define OPEN_INF
//#define OPEN_DBG
#endif
#include "Log.h"

extern CLog g_oNetLog;
#define LOG_OBJ g_oNetLog
#include "LogDefine.h"
inline const string GetStringErr()
{
	char szbuf[1024];
	const char* pszMsg = szbuf;
#ifdef _WIN32
	sprintf_s(szbuf, "%d", WSAGetLastError());
#else
	pszMsg = strerror_r(errno, szbuf, sizeof szbuf);
#endif
	return string(pszMsg);
}
#define ERRDESC GetStringErr()

#ifdef _WIN32
typedef int socklen_t;
#endif
