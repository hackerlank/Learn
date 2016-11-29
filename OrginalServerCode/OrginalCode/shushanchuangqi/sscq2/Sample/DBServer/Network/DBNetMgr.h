/********************************************************************
//	Database Server Source File.
//	File name:	NetMgr.h
//	Created:	2011/06/03	15:00
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

class CDBNetMgr : public CNetMgr, public StaticSingleton<CDBNetMgr>
{
public:
	virtual void TimerCheck() override;

protected:
	virtual void InitProtocol() override;
	virtual bool OnUserLogic() override;
    virtual void OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID) override;
    virtual void OnUserLogicExit() override;
    
    virtual void OnGateClosed( ISocket& rSocket ) override;
    virtual void OnCenterClosed( ISocket& rSocket ) override;
    virtual void OnGameClosed( ISocket& rSocket ) override;
    virtual void OnLoggerClosed( ISocket& rSocket ) override;
    virtual void OnLoginClosed( ISocket& rSocket ) override;
};

#define NetMgr CDBNetMgr::Instance()
