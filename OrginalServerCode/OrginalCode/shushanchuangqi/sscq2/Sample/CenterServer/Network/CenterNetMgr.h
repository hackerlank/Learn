/********************************************************************
//	Center Server Source File.
//	File name:	NetMgr.h
//	Created:	2011/06/06	10:00
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

class CCenterNetMgr : public CNetMgr
{
public:
	static CCenterNetMgr& Instance();
	virtual void TimerCheck() override;
    bool GetCurUser(CUserPtr* ppUser);
protected:
	virtual void InitProtocol() override;
    virtual void OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID) override;
	virtual bool OnException(EExceptType eExceptType) override;
    virtual void OnGateClosed( ISocket& rSocket ) override;
    virtual void OnGameClosed( ISocket& rSocket ) override;
    virtual void OnDBClosed( ISocket& rSocket ) override;
    virtual void OnLoggerClosed( ISocket& rSocket ) override;
    virtual void OnLoginClosed( ISocket& rSocket ) override;

};

#define NetMgr CCenterNetMgr::Instance()
