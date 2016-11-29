/********************************************************************
//	Log Server Source File.
//	File name:	NetMgr.h
//	Created:	2011/12/26	14:00
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
#include "NetMgr.h"
#include "Singleton.h"

class CLogNetMgr : public CNetMgr, public StaticSingleton<CLogNetMgr>
{
public:
	virtual void InitProtocol();
	virtual bool OnUserLogic();
};

#define NetMgr CLogNetMgr::Instance()
