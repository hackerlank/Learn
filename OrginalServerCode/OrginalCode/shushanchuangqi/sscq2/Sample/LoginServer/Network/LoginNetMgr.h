/********************************************************************
//	Login Server Source File.
//	File name:	NetMgr.h
//	Created:	2011/06/10	14:00
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

class CLoginAuthHandler : public CAuthHandler
{
public:
	CLoginAuthHandler(CAcceptHandler& rAcceptHandler, CSessionMgr& rSessionMgr) : CAuthHandler(rAcceptHandler, rSessionMgr) { }
	bool Send(ISocket& rSocket, const char* pBuf, UINT32 dwLen);
	virtual bool Send(const char* pBuf, UINT32 dwLen) override;
	virtual bool OnRecv(const char* pBuf, UINT32 dwLen) override;
};

class CLoginNetMgr : public CNetMgr
{
public:
	static CLoginNetMgr& Instance();
	virtual void TimerCheck() override;
protected:
	virtual void InitProtocol() override;
	virtual CAuthHandler* CreateAuthHandler() override;
};

#define NetMgr CLoginNetMgr::Instance()
