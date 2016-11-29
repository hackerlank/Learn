/********************************************************************
//	Server Utility Library Source File.
//	File name:	CallStack.h
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

#ifdef _WIN32
#include <Windows.h>
#else
#include "Linux.h"
#endif
#include <stdio.h>
#define CALLSTACK_BUF_SIZE 0x1000

#ifdef _WIN32
void GetCallStack(CONTEXT& rContext, char* pBuf, size_t size, UINT16 wDepth = 0);
#define GET_CALL_STACK(buf, size) \
	CONTEXT c; \
	RtlCaptureContext(&c); \
	GetCallStack(c, buf, size);
#else
void* GetCurrentAddress();
void GetCallStack(void* pAddr, char* pBuf, size_t size);
#define GET_CALL_STACK(buf, size) \
	GetCallStack(GetCurrentAddress(), buf, size);
#endif

#define PRINT_CALL_STACK \
	static char szBuf[CALLSTACK_BUF_SIZE]; \
	GET_CALL_STACK(szBuf, sizeof szBuf); \
	LNF_CRI << "++++++++++++++++++++++++Call Stack++++++++++++++++++++++++"; \
	LOG_RAW << szBuf << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

#ifdef _DEBUG
#define PRINT_CALL_STACK_DEBUG PRINT_CALL_STACK
#else
#define PRINT_CALL_STACK_DEBUG
#endif

inline void PrintCallStack()
{
	static char szBuf[CALLSTACK_BUF_SIZE];
	GET_CALL_STACK(szBuf, sizeof szBuf);
	printf("++++++++++++++++++++++++Call Stack++++++++++++++++++++++++\n%s"
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n", szBuf);
}
