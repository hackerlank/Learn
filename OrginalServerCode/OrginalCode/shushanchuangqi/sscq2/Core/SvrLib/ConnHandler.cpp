/********************************************************************
//	Server Common Library Source File.
//	File name:	ConnHandler.cpp
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

CConnHandler::~CConnHandler()
{
	for(auto it = _mapID2Svr.begin(); it != _mapID2Svr.end(); ++it)
	{
		SPeerInfo& rPeerInfo = it->second;
		rPeerInfo.pSocket->Release();
	}
	_mapID2Svr.clear();
	if(_pSendBuf)
#ifdef _WIN32
		VirtualFree(_pSendBuf, 0, MEM_RELEASE);
#else
		free(_pSendBuf);
#endif
	_pSendBuf = NULL;
}

bool CConnHandler::AllocBuf(UINT32 dwBufSize)
{
	if(dwBufSize == 0)
		return false;
#ifdef _WIN32
	_pSendBuf = (char*)VirtualAlloc(NULL, dwBufSize, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);
#else
	_pSendBuf = (char*)malloc(dwBufSize);
#endif
	if(_pSendBuf == NULL)
		return false;
	_dwBufSize = dwBufSize;
	return true;
}

bool CConnHandler::HasConnection(UINT8 byIndex) const
{
	UINT32 dwSvrID = GetServerID(CConfig::GetConfig()->_wGroup, GetPeerType(), byIndex);
	return _mapID2Svr.find(dwSvrID) != _mapID2Svr.end();
}

bool CConnHandler::OnEstablish(ISocket& rSocket, bool bAccept)
{
	EHostType ePeerType = rSocket.GetPeerType();
	UINT32 dwPeerID = rSocket.GetPeerID();
	if(bAccept && ePeerType != eHostNone && !CConfig::GetConfig()->OnAccept(rSocket))
	{
		LOG_CRI << "OnAccept fails! ePeerType: " << ePeerType << ", PeerID: " << rSocket.GetPeerID();
		return false;
	}
	auto pairRet = _mapID2Svr.insert(make_pair(dwPeerID, SPeerInfo(&rSocket, 0)));
	if(!pairRet.second)
	{
		LOG_CRI << "Connection has already been established! Peer Server: " << GetServerInfo(dwPeerID);
		return false;
	}
	CConfig* pConfig = CConfig::GetConfig();
	if(pConfig->_wGroup == GetServerGroup(dwPeerID) && _bAccept != bAccept)
		DebugBreak();
	SetCurSock(&rSocket);
	rSocket.SetConnectionHandler(this); //重新设置Handler
	if(!bAccept)
	{
		char buf[sizeof(UINT32) * 2 + sizeof(UINT8)];
		*(UINT8*)buf = (UINT8)pConfig->_eSvrType;
		*(UINT32*)(buf + sizeof(UINT8)) = pConfig->GetServerID();
		if(GetServerGroup(dwPeerID) == pConfig->_wCrossGroup)
			*(UINT32*)(buf + sizeof(UINT8) + sizeof(UINT32)) = pConfig->_dwCrossGroupKey;
		else
			*(UINT32*)(buf + sizeof(UINT8) + sizeof(UINT32)) = pConfig->_dwGroupKey;
		return rSocket.Send(buf, sizeof buf);
	}
	return true;
}

void CConnHandler::OnClose(ISocket& rSocket)
{
	EHostType ePeerType = GetPeerType();
	if(ePeerType != eHostNone)
	{
		CNetMgr::GetNetMgr()->OnClose(rSocket);
		CConfig::GetConfig()->OnClose(rSocket);
	}
	UINT32 dwPeerID = rSocket.GetPeerID();
	rSocket.SetConnectionHandler(NULL);
	if(_mapID2Svr.erase(dwPeerID) == 0)
		LOG_CRI << "Can't find SrvID: " << GetServerInfo(dwPeerID);
}

ISocket* CConnHandler::GetSocket(UINT32 dwSvrID)
{
	auto it = _mapID2Svr.find(dwSvrID);
	if(it == _mapID2Svr.end())
	{
		LOG_CANNOT_FIND_SEVER(dwSvrID);
		return NULL;
	}
	return it->second.pSocket;
}

void CConnHandler::ForeachSocket(std::function<void(ISocket&)> func)
{
	if(!func)
		return;
	for(auto it = _mapID2Svr.begin(); it != _mapID2Svr.end();)
	{
		SPeerInfo& rPeerInfo = it->second;
		++it;
		func(*rPeerInfo.pSocket);
	}
}

void CConnHandler::RegisterProtocol(IProtocol& rProtocol)
{
	rProtocol.SetSessionMgr(&_rSessionMgr);
	rProtocol.SetConnectionHandler(this);
	if(!_mapID2Prot.insert(make_pair(rProtocol.GetProtID(), &rProtocol)).second)
		LOG_CRI << "Duplicate ProtID: " << rProtocol.GetProtID();
}

void CConnHandler::OnKeepAlive(UINT32 dwSvrID)
{
	auto it = _mapID2Svr.find(dwSvrID);
	if(it != _mapID2Svr.end())
	{
		SPeerInfo& rPeerInfo = it->second;
		rPeerInfo.dwStaleCount = 0;
	}
	else
	{
		LOG_CANNOT_FIND_SEVER(dwSvrID);
	}
}

bool CConnHandler::OnRecv(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return true;
	UINT32 dwHeadLen = ParseHeader(pBuf, dwLen);
	if(dwLen < dwHeadLen + sizeof(UINT8))
		return false;
	CNetMgr::GetNetMgr()->SetCurConnHandler(this);
	CNetMgr::GetNetMgr()->SetCurUsrID(0);
	UINT64 qwStartTick = GetTickCount64();
	UINT8 byFuncID = *(UINT8*)(pBuf + dwHeadLen + sizeof(UINT8));
	bool bRet = false;
    // XXX: Debug也开启异常
//#if defined(_WIN32) || defined(_DEBUG) 
	//bRet = HandleMessage(pBuf + dwHeadLen, dwLen - dwHeadLen);
//#else
	try
	{
		bRet = HandleMessage(pBuf + dwHeadLen, dwLen - dwHeadLen);
	}
	catch(std::exception& ex)
	{
		char szBuf[0x100];
		sprintf_s(szBuf, "Exception caught! [%s] %s, eHostType: %s, ePeerType: %s, Protocol ID: %d, FuncID: %d",
			typeid(ex).name(), ex.what(), GetServerName(CConfig::GetConfig()->_eSvrType), GetServerName(GetPeerType()), _byCurProt, byFuncID);
		LOG_CRI << szBuf;
		cout << szBuf << endl;
	}
	catch(const char* szExcept)
	{
		char szBuf[0x100];
		sprintf_s(szBuf, "Exception caught! eHostType: %s, ePeerType: %s, Protocol ID: %d, FuncID: %d. %s",
			GetServerName(CConfig::GetConfig()->_eSvrType), GetServerName(GetPeerType()), _byCurProt, byFuncID, szExcept);
		LOG_CRI << szBuf;
		return false;
	}
	catch(...)
	{
		char szBuf[0x100];
		sprintf_s(szBuf, "Exception caught! eHostType: %s, ePeerType: %s, Protocol ID: %d, FuncID: %d",
			GetServerName(CConfig::GetConfig()->_eSvrType), GetServerName(GetPeerType()), _byCurProt, byFuncID);
		LOG_CRI << szBuf;
		cout << szBuf << endl;
	}
//#endif
	UINT64 qwDiffTick = GetTickCount64() - qwStartTick;
	if(qwDiffTick > FRAME_OVERTIME_LIMIT)
		LNF_CRI << "Protocol ID: " << _byCurProt << ", FuncID: " << byFuncID << ", Overtime: " << qwDiffTick;
	_byCurProt = 0;
	CNetMgr::GetNetMgr()->SetCurUsrID(0);
	return bRet;
}

bool CConnHandler::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return true;
	UINT8 byProtID = *(UINT8*)pBuf;
	auto it = _mapID2Prot.find(byProtID);
	if(it == _mapID2Prot.end())
	{
		INT8 byFuncID = 0;
		if(dwLen >= sizeof(UINT8) * 2)
			byFuncID = *(UINT8*)(pBuf + sizeof(UINT8));
		LOG_CRI << "Can't find protocol! byProtID: " << byProtID << ", byFuncID: " << byFuncID << ", Peer: " << GetServerDesc(GetCurSvrID());
		return false;
	}
	IProtocol* pProtocol = it->second;
	return pProtocol->HandleMessage(pBuf + sizeof(UINT8), dwLen - sizeof(UINT8));
}

bool CConnHandler::Send(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	_bySendProt = *(UINT8*)pBuf;
	if(dwLen >= sizeof(UINT8) * 2)
		_bySendFunc = *(UINT8*)(pBuf + sizeof(UINT8));
	else
		_bySendFunc = 0;
	return true;
}

UINT32 CConnHandler::GetCurSvrID() const
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
		return 0;
	return pSocket->GetPeerID();
}

UINT32 CConnHandler::GetStaleCount() const
{
	return KEEP_ALIVE_MAX_STALE_COUNT;
}

void CConnHandler::TimerCheck()
{
	for(auto it = _mapID2Svr.begin(); it != _mapID2Svr.end(); ++it)
	{
		SPeerInfo& rPeerInfo = it->second;
		++rPeerInfo.dwStaleCount;
		if(rPeerInfo.dwStaleCount >= GetStaleCount())
		{
			ISocket& rScoket = *rPeerInfo.pSocket;
			if(GetPeerType() == eHostNone)
			{
				LOG_INF << "New Client Authentication Overtime! StaleCount: " << GetStaleCount() << ", Peer Address: " << rScoket.GetPeerAddrStr();
			}
			else
			{
				LOG_CRI << "Peer Keep Alive Timeout! StaleCount: " << GetStaleCount() << ",PeerName: " << rScoket.GetPeerName() << ", Peer Group: "
					<< GetServerGroup(rScoket.GetPeerID()) << ", Peer Index: " << GetServerIndex(rScoket.GetPeerID());
			}
			rScoket.Close();
		}
	}
}
