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

#include "GlobalDefine.h"
#include "ServerDefine.h"

#if defined(_DEBUG) && defined(_WIN32) && defined(MEMORY_LEAK_CHECK)
#include <vld.h>
#endif

CLog g_oLog;
