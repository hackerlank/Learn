/********************************************************************
//	Unique Server Source File.
//	File name:	Config.cpp
//	Created:	2011/06/20	15:00
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

#include "stdafx.h"
#ifdef _WIN32
#include "resource.h"
#include "LogServerDlg.h"
#endif
#include "tinyxml.h"
#include "LogExt.h"

CLogConfig& CLogConfig::Instance()
{
	static CLogConfig config(CLogNetMgr::Instance());
	return config;
}

bool CLogConfig::InitServer()
{
	if(!CTimerMgr::Instance().OpenAllTimer())
	{
		LOG_CRI << "CTimerMgr::OpenAllTimer fails!";
		return false;
	}

	if (!CLogMgr::Instance().Init())
	{
		LOG_CRI << "CLogMgr::Init fails!";
		return false;
	}

	if (!CDBMgr::Instance().Init())
	{
		LOG_CRI << "CDBMgr::Init fails!";
		return false;
	}

	return true;
}

void CLogConfig::UnInitServer()
{
	CDBMgr::Instance().Stop();
}
