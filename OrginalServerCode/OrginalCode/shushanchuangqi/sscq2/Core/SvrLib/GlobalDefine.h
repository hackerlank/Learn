/********************************************************************
//	Server Common Library Source File.
//	File name:	GlobalDefine.h
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
#include "ServerDefine.h"

#ifdef _DEBUG
#define KEEP_ALIVE_MAX_STALE_COUNT 500
#else
#define KEEP_ALIVE_MAX_STALE_COUNT 10
#endif

#define LISTEN_BACKLOG 1000

#ifdef _DEBUG
#define SERVER_BUFFER_SIZE 2 * 1024 * 1024
#else
#define SERVER_BUFFER_SIZE 4 * 1024 * 1024
#endif

#ifdef _DEBUG
#define CLIENT_BUFFER_SIZE 512 * 1024
#else
#define CLIENT_BUFFER_SIZE 128 * 1024
#endif

#define TIMER_SAVE_INTERVAL 5
#define LEAVE_WAIT_INTERVAL 3 * 60

#define STRICT_SCRIPT_CHECK 0

#define MEMORY_LEAK_CHECK