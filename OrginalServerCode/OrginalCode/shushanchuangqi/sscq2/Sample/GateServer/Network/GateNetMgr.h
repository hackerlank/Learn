/********************************************************************
//	Gate Server Source File.
//	File name:	NetMgr.h
//	Created:	2011/06/03	10:00
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

class CGateSvrHandler : public CSvrHandler
{
public:
	CGateSvrHandler(EHostType ePeerType, CSessionMgr& rSessionMgr)
		: CSvrHandler(ePeerType, false, rSessionMgr) { }

	virtual bool OnRecv(const char* pBuf, UINT32 dwLen) override;
};

class CGTAcceptHandler : public CAcceptHandler
{
public:
	virtual bool OnAccept(ISocket& rSocket);
};

class CGateNetMgr : public CNetMgr
{
public:
	static CGateNetMgr& Instance();
	virtual void InitProtocol() override;
	virtual void TimerCheck() override;
	CClientMgr& GetClientMgr() { return *_pClientMgr; }

protected:
	virtual bool InitNetMgr() override;
	virtual CGateSvrHandler* CreateSvrHandler(EHostType ePeerType, bool bAccept) override;

private:
	CClientMgr* _pClientMgr;
};

#define NetMgr CGateNetMgr::Instance()
