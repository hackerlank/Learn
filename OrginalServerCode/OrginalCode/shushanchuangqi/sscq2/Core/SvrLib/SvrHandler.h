/********************************************************************
//	Server Common Library Source File.
//	File name:	SvrHandler.h
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

class CSvrHandler : public CConnHandler
{
public:
	CSvrHandler(EHostType ePeerType, bool bAccept, CSessionMgr& rSessionMgr)
		: CConnHandler(rSessionMgr, bAccept), _ePeerType(ePeerType) { }
	virtual EHostType GetPeerType() const override { return _ePeerType; }
	virtual bool Send(const char* pBuf, UINT32 dwLen) override;
	virtual bool SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen) override;
	virtual bool ProxySend(const char* pBuf, UINT32 dwLen) override;	//协议数据包转发
	virtual bool ProxySend(UINT32 dwSvrID, const char* pBuf, UINT32 dwLen) override;	//协议数据包转发到指定的服务器
protected:
	UINT32 GetCurSvrID();
	bool GateSend(ISocket& rSocket, const char* pBuf, UINT32 dwLen);
	virtual UINT32 ParseHeader(const char* pBuf, UINT32 dwLen) override;	//解析协议头部，返回协议长度

	EHostType _ePeerType;	//对方的主机类型
};
