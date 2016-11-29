/********************************************************************
//	Server Common Library Source File.
//	File name:	SvrHandler.cpp
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
#include "SvrHandler.h"
#include "ServerID.h"
#include "NetMgr.h"
#include "Config.h"
#include "Encode.h"

bool CSvrHandler::GateSend(ISocket& rSocket, const char* pBuf, UINT32 dwLen)
{
	if(_pSendBuf == NULL || _dwBufSize == 0 || pBuf == NULL || dwLen == 0)
		return false;
	UINT64 qwUsrID = 0;
	UINT32 dwNewLen = 0;
	memcpy_s(_pSendBuf, _dwBufSize, &qwUsrID, sizeof qwUsrID);
	dwNewLen += sizeof qwUsrID;
	memcpy_s(_pSendBuf + dwNewLen, _dwBufSize - dwNewLen, pBuf, dwLen);
	dwNewLen += dwLen;
	return rSocket.Send(_pSendBuf, dwNewLen);
}

bool CSvrHandler::Send(const char* pBuf, UINT32 dwLen)
{
	if(!CConnHandler::Send(pBuf, dwLen)) //解析出发送协议ID, 发送函数ID
		return false;
	UINT32 dwCurSvrID = GetCurSvrID();
	if(dwCurSvrID == 0)
		return false;
	auto it = _mapID2Svr.find(dwCurSvrID);
	if(it == _mapID2Svr.end())
	{
		LOG_CANNOT_FIND_SEVER(dwCurSvrID);
		return false;
	}
	ISocket* pSocket = it->second.pSocket;
	if(CNetMgr::GetNetMgr()->GetHostType() == eHostGate)
		return GateSend(*pSocket, pBuf, dwLen); // 发送时 先加8个字节的UserID 然后pSocket Send
	else
		return pSocket->Send(pBuf, dwLen); // 发送时 + 4个字节的包长
}

bool CSvrHandler::SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	EHostType eSvrType = CNetMgr::GetNetMgr()->GetHostType();
	bool bRet = true;
	if(pSvrID == NULL)
	{
		if(bySvrCnt != 0)
		{
			LOG_CRI << "bySvrCnt != 0";
			return false;
		}
		if(_mapID2Svr.empty())
			return false;
		for(auto it = _mapID2Svr.begin(); it != _mapID2Svr.end(); ++it)
		{
			ISocket* pSocket = it->second.pSocket;
			if(pSocket == NULL)
				continue;
			if(eSvrType == eHostGate)
				bRet = GateSend(*pSocket, pBuf, dwLen) && bRet;
			else
				bRet = pSocket->Send(pBuf, dwLen) && bRet;
		}
	}
	else
	{
		for(UINT8 i = 0; i < bySvrCnt; ++i)
		{
			UINT32 dwSvrID = pSvrID[i];
			auto it = _mapID2Svr.find(dwSvrID);
			if(it == _mapID2Svr.end())
			{
				LOG_CANNOT_FIND_SEVER(dwSvrID);
				return false;
			}
			ISocket* pSocket = it->second.pSocket;
			if(pSocket == NULL)
				continue;
			if(eSvrType == eHostGate)
				bRet = GateSend(*pSocket, pBuf, dwLen) && bRet;
			else
				bRet = pSocket->Send(pBuf, dwLen) && bRet;
		}
	}
	return bRet;
}
//代理发送，并不判断是否为GateServer
bool CSvrHandler::ProxySend(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	UINT32 dwCurSvrID = GetCurSvrID();
	if(dwCurSvrID == 0)
		return false;
	auto it = _mapID2Svr.find(dwCurSvrID);
	if(it == _mapID2Svr.end())
	{
		LOG_CANNOT_FIND_SEVER(dwCurSvrID);
		return false;
	}
	ISocket* pSocket = it->second.pSocket;   
	if(pSocket == NULL)
		return false;
	return pSocket->Send(pBuf, dwLen);
}

bool CSvrHandler::ProxySend(UINT32 dwSvrID, const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	auto it = _mapID2Svr.find(dwSvrID);
	if(it == _mapID2Svr.end())
	{
		LOG_CANNOT_FIND_SEVER(dwSvrID);
		return false;
	}
	ISocket* pSocket = it->second.pSocket;
	if(pSocket == NULL)
		return false;
	return pSocket->Send(pBuf, dwLen);
}

UINT32 CSvrHandler::ParseHeader(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return 0;
	_byCurProt = *(UINT8*)pBuf;
	if(dwLen >= sizeof(UINT8) * 2)
		_byCurFunc = *(UINT8*)(pBuf + sizeof(UINT8));
	else
		_byCurFunc = 0;
	return 0;
}

UINT32 CSvrHandler::GetCurSvrID()
{
	switch(_ePeerType)
	{
	case eHostCenter:
	case eHostDB:
	case eHostLogin:
	case eHostLog:
		if(_mapID2Svr.size() == 1) //记录和本机相连接的所有的ISocket
			return _mapID2Svr.begin()->first;
		else if(_mapID2Svr.size() > 1)
			LOG_CRI << "More than 1 peer exist! PeerType: " << GetServerName(_ePeerType) << ", Prot: " << _bySendProt << ", Func: " << _bySendFunc;
		break;
	case eHostGame:
	case eHostControl:
		{
			ISocket* pSocket = GetCurSock();
			if(pSocket != NULL && pSocket->GetPeerType() == _ePeerType)
				return pSocket->GetPeerID();
		}
		break;
	default:
		break;
	}
	return 0;
}
