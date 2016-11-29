/********************************************************************
//	Unique Server Source File.
//	File name:	Config.h
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

#pragma once
#include "Config.h"
#ifdef _WIN32
class CLogServerDlg;
#endif

class CNetMgr;
class TiXmlElement;

class CLogConfig : public CConfig
{
	friend class CRequestHandler;
public:
	static CLogConfig& Instance();
	CLogConfig(CNetMgr& rNetMgr) : CConfig(rNetMgr) { }

private:
	virtual bool InitServer();
	virtual void UnInitServer();
};

#define Config CLogConfig::Instance()
