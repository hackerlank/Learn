/********************************************************************
//	Game Server Source File.
//	File name:	NetMgr.h
//	Created:	2011/05/30	10:00
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

#ifndef GAME_NET_MGR_H
#define GAME_NET_MGR_H

#pragma once

#include "stdafx.h"

#include "NetMgr.h"

class CGameSvrHandler : public CSvrHandler
{
public:
	CGameSvrHandler(bool bIsC2S, CSessionMgr& rSessionMgr) : CSvrHandler(eHostGame, false, rSessionMgr), _bIsC2S(bIsC2S), _wSrcGroup(0), _bySrcIndex(0) { }
	virtual bool Send(const char* pBuf, UINT32 dwLen) override;
	virtual bool SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen) override;
	virtual UINT32 GetCurSvrID() const override;
	void SetSrcGroup(UINT16 wSrcGroup) { _wSrcGroup = wSrcGroup; }
	void SetSrcIndex(UINT8 bySrcIndex) { _bySrcIndex = bySrcIndex; }
protected:
	bool _bIsC2S;
	UINT16 _wSrcGroup;
	UINT8 _bySrcIndex;
};

extern CGameSvrHandler g_GameSvrHandlerC2S;
extern CGameSvrHandler g_GameSvrHandlerS2C;

class CGameNetMgr : public CNetMgr
{
public:
	static CGameNetMgr& Instance();
	bool GetCurUser(CUserPtr* ppUser = NULL, CPlayerPtr* ppPlayer = NULL, CGameMapPtr* ppMap = NULL);
	virtual void TimerCheck() override;
protected:
    virtual void OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID) override;
	virtual bool OnUserLogic() override;
	virtual void InitProtocol() override;
	virtual bool OnException(EExceptType eExceptType) override;
    virtual void OnGateClosed( ISocket& rSocket ) override;
    virtual void OnCenterClosed( ISocket& rSocket ) override;
    virtual void OnDBClosed( ISocket& rSocket ) override;
    virtual void OnLoggerClosed( ISocket& rSocket ) override;
    virtual void OnLoginClosed( ISocket& rSocket ) override;
};

#define NetMgr CGameNetMgr::Instance()

#endif // #ifndef GAME_NET_MGR_H
