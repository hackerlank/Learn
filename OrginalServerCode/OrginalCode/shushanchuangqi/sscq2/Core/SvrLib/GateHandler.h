/********************************************************************
//	Server Common Library Source File.
//	File name:	GateHandler.h
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
#include <map>
#include <unordered_set>
#include <vector>
#include "Interface.h"
#include "SessionMgr.h"

#include "SvrHandler.h"

using namespace std;

class CGateHandler : public CConnHandler
{
public:
	CGateHandler(CSessionMgr& rSessionMgr) : CConnHandler(rSessionMgr, true) { }

	const map<UINT64, UINT32>& GetUserMap() const { return _mapUsr2Gate; }
	virtual EHostType GetPeerType() const override { return eHostGate; }
	virtual void RegisterProtocol(IProtocol& rProtocol) override;
	void OnUserLogin(UINT64 qwUsrID);	//User在登录后需要注册其在哪一个网关上
	void OnUserLogin(UINT64 qwUsrID, UINT32 dwSvrID);	//User在登录后需要注册其在哪一个网关上
	void OnUserLogout(UINT64 qwUsrID);	//User在登出时需要删除所在的网关信息
	UINT32 GetGateID(UINT64 qwUsrID);	//获取User所在的网关服务器ID
	virtual UINT64 GetCurUsrID() const override;	//获取协议当前处理的UserID
	virtual bool Send(const char* pBuf, UINT32 dwLen) override;
	virtual bool SendClt(const UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen) override;
	virtual bool SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen) override;
	virtual bool SendGate(UINT32 dwSvrID, UINT64* pUsrID, UINT16 wUsrCnt, const char* pBuf, UINT32 dwLen) override;

protected:
	virtual UINT32 ParseHeader(const char* pBuf, UINT32 dwLen) override;
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	map<UINT64, UINT32>	_mapUsr2Gate;	//UserID到网关服务器ID的映射
	unordered_set<UINT8> _setDirectProtID;	//不需要网关服务器转发的协议ID集合
	UINT64 _qwCurUsrID;		//当前协议处理对应的UserID
};
