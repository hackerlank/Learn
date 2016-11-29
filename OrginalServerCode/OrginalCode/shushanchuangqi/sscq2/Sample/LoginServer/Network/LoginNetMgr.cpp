/********************************************************************
//	Login Server Source File.
//	File name:	NetMgr.cpp
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

#include "stdafx.h"
#include "Protocols.h"

bool CLoginAuthHandler::Send(ISocket& rSocket, const char* pBuf, UINT32 dwLen)
{
	static char arBuf[0x10000];
	UINT32 dwNewLen = sizeof arBuf;
	if(!CompressPacket(pBuf, dwLen, arBuf, dwNewLen))
	{
		LOG_CRI << "Compress fails!";
		return false;
	}
	XOR(arBuf, dwNewLen, rSocket.GetSessionKey());
	return rSocket.Send(arBuf, dwNewLen);
}

bool CLoginAuthHandler::Send(const char* pBuf, UINT32 dwLen)
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
		return false;
	return Send(*pSocket, pBuf, dwLen);
}

bool CLoginAuthHandler::OnRecv(const char* pBuf, UINT32 dwLen)
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
	{
		LOG_CRI << "Can't find current socket!";
		return false;
	}
	pSocket->SetSessionKey(pSocket->GetHostPort());
	assert(pSocket->IsCltSocket() && pSocket->GetSessionKey() != 0);
	XOR((char*)pBuf, dwLen, pSocket->GetSessionKey());
	return CConnHandler::OnRecv(pBuf, dwLen);
}

CLoginNetMgr& CLoginNetMgr::Instance()
{
	static CLoginNetMgr oNetMgr;
	return oNetMgr;
}

void CLoginNetMgr::TimerCheck()
{
	CNetMgr::TimerCheck();
	g_Login2CenterCommC.Send_KeepAlive();
}

CAuthHandler* CLoginNetMgr::CreateAuthHandler()
{
	if(_pAcceptHandler == NULL)
		return NULL;
	return new CLoginAuthHandler(*_pAcceptHandler, _oSessionMgr);
}