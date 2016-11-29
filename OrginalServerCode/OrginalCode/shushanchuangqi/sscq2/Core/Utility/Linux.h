/********************************************************************
//	Server Utility Library Source File.
//	File name:	Linux.h
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

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>

typedef char INT8;
typedef short INT16;
typedef int INT32;
typedef long LONG;
typedef int64_t INT64;

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long ULONG;
typedef unsigned long long ULONGLONG;
typedef uint64_t UINT64;

typedef float FLOAT;
typedef double DOUBLE;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#ifndef UINT32_MAX

/* Limits of integral types.  */

/* Minimum of signed integral types.  */
# define INT8_MIN               (-128)
# define INT16_MIN              (-32767-1)
# define INT32_MIN              (-2147483647-1)
# define INT64_MIN              (-__INT64_C(9223372036854775807)-1)
/* Maximum of signed integral types.  */
# define INT8_MAX               (127)
# define INT16_MAX              (32767)
# define INT32_MAX              (2147483647)
# define INT64_MAX              (__INT64_C(9223372036854775807))

/* Maximum of unsigned integral types.  */
# define UINT8_MAX              (255)
# define UINT16_MAX             (65535)
# define UINT32_MAX             (4294967295U)
# define UINT64_MAX             (__UINT64_C(18446744073709551615))

#endif

typedef int SOCKET;
typedef void* HANDLE;
#define INVALID_SOCKET -1
#define closesocket(s) close(s)

#define CONTAINING_RECORD(address, type, field) ((type*)( \
	(char*)(address) - \
	(ULONG)(&((type*)0)->field)))

#define ARRAYSIZE(A) (sizeof(A)/sizeof((A)[0]))

#define DebugBreak() do{\
	PrintCallStack(), \
	printf("DebugBreak[%s:%u]\n", __PRETTY_FUNCTION__, __LINE__), \
	fflush(stdout), \
	__builtin_trap();\
    } while(0)

#define memcpy_s(dest, m, src, n) memcpy((dest), (src), ((m) < (n) ? (m) : (n)))
#define sprintf_s sprintf
#define strtok_s strtok_r
#define Sleep(seconds) usleep((seconds) * 1000)
#define localtime_s(_Tm, _Time) localtime_r((_Time), (_Tm))

//#pragma GCC diagnostic ignored "-Wswitch"
//#pragma GCC diagnostic ignored "-Winvalid-offsetof"
//#pragma GCC diagnostic ignored "-Wchar-subscripts"
//#pragma GCC diagnostic ignored "-Wunused-function"
