/********************************************************************
//	Server Common Library Source File.
//	File name:	AuthHandler.cpp
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

#include "GlobalDefine.h"
#include "AuthHandler.h"
#include "NetMgr.h"
#include "Config.h"
#include "Encode.h"
#include "UtilFunc.h"

bool CAuthHandler::OnEstablish(ISocket& rSocket, bool bAccept)
{
	UINT32 dwNextSocketID = _dwNextNewSocketID++;
	if(_dwNextNewSocketID == 0)
		_dwNextNewSocketID = 1;
	rSocket.SetPeerID(dwNextSocketID);
	return CConnHandler::OnEstablish(rSocket, bAccept);
}

bool CAuthHandler::OnRecv(const char* pBuf, UINT32 dwLen)
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
	{
		LOG_CRI << "Can't find current socket!";
		return false;
	}
	EHostType eSvrType = CConfig::GetConfig()->_eSvrType;
	if(pBuf == NULL || dwLen < sizeof(UINT8))
	{
		pSocket->Close();
		return false;
	}
	OnClose(*pSocket);
	UINT32 dwOffset = 0;
	UINT8 byType = *(UINT8*)(pBuf + dwOffset);	//获得对方的主机类型
	dwOffset += sizeof(UINT8);
	EHostType ePeerType = (EHostType)byType;
	pSocket->SetPeerType(ePeerType);
	if(pSocket->IsCltSocket()) //如果对方是客户端
	{
		if(ePeerType != eHostClient)
		{
			LOG_CRI << "Socket is not for Client! Type: " << byType << ", PeerAddr: " << pSocket->GetPeerAddrStr() << ", Content: " << GetBufContent(pBuf, dwLen);
			return false;
		}
		if(eSvrType != eHostGate) //只有GateServer才会处理这种情况
		{
			LOG_CRI << "Invalid Server Type: " << eSvrType;
			return false;
		}
		if(dwLen < dwOffset + sizeof(UINT64))
		{
			LOG_INF << "Invalid Client Identity!";
			pSocket->Close();
			return false;
		}
		UINT64 qwUsrID = *(UINT64*)(pBuf + dwOffset);	//获得客户端的UserID
		dwOffset += sizeof(UINT64);
		pSocket->SetUserID(qwUsrID);
		pSocket->SetPeerID((UINT32)qwUsrID);
	}
	else
	{
		if(dwLen < dwOffset + sizeof(UINT32))
		{
			LOG_CRI << "Invalid Server Identity!";
			pSocket->Close();
			return false;
		}
		UINT32 dwPeerID = *(UINT32*)(pBuf + dwOffset);	//获得对方的服务器ID
		dwOffset += sizeof(UINT32);
        if (!(ePeerType == eHostControl && pSocket->GetPeerID()))
		    pSocket->SetPeerID(dwPeerID);
	}
	if(dwLen < dwOffset + sizeof(UINT32))
	{
		LOG_INF << "Invalid Session Key!";
		pSocket->Close();
		return false;
	}
	UINT32 dwSessionKey = *(UINT32*)(pBuf + dwOffset);	//获得对方的连接密码
	pSocket->SetSessionKey(dwSessionKey);
	CAcceptHandler* pAcceptHandler = CNetMgr::GetNetMgr()->GetAcceptHandler();
	if(pAcceptHandler == NULL || !pAcceptHandler->OnAccept(*pSocket))	//让Accept处理器来处理新进连接
	{
		pSocket->Close();
		return false;
	}
	return true;
}
