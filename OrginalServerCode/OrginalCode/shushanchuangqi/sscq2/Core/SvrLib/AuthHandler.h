/********************************************************************
//	Server Common Library Source File.
//	File name:	AuthHandler.h
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
#include "ConnHandler.h"

class CAcceptHandler;

//连接验证
class CAuthHandler : public CConnHandler
{
public:
	CAuthHandler(CAcceptHandler& rAcceptHandler, CSessionMgr& rSessionMgr)
		: CConnHandler(rSessionMgr, true), _rAcceptHandler(rAcceptHandler), _dwNextNewSocketID(1) { }
	virtual EHostType GetPeerType() const override { return eHostNone; }
	virtual bool OnEstablish(ISocket& rSocket, bool bAccept) override;
	virtual bool OnRecv(const char* pBuf, UINT32 dwLen) override;
	virtual UINT32 GetStaleCount() const override { return 10; }	//连接检查时的失效次数
protected:
	CAcceptHandler& _rAcceptHandler;	//Accept处理器
	UINT32 _dwNextNewSocketID;			//分配临时的ID
};
