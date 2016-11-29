/********************************************************************
// Server Network Library Source File.
// File name:  Interface.cpp
// Created:    2012/08/21  11:00
// Organization:
// Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
// Author:     Jingyuan Wang
// E-Mail:     tyketom@hotmail.com
// Http://
// ------------------------------------------------------------------
// Purpose:
// Version:    1.0
// Histroy:
*********************************************************************/

#include <stdlib.h>
#include <map>
#include <time.h>
#include "GlobalDefine.h"
#ifdef _WIN32
#include <IPHlpApi.h>
#include "IOCPMgr.h"
#else
#include <ifaddrs.h>
#include "EPollMgr.h"
#include "Exception.h"
#endif
#include "Interface.h"
#include "Timer.h"
#include "NetIFMgr.h"
#include "BaseSocket.h"
#include "BaseListener.h"
#include "UtilFunc.h"
#include "ServerID.h"

ISocket::ISocket()
	: _pConnHandler(NULL)
	, _dwPeerID(0)
	, _ePeerType(eHostNone)
	, _eActType(eActNone)
{
	memset(_arPeerMac, 0, sizeof _arPeerMac);
}

ISocket::~ISocket()
{
	_pConnHandler = NULL;
}

std::string ISocket::GetPeerName() const
{
	const char* pszSvrName = GetServerName(_ePeerType);
	if(pszSvrName != NULL)
		return pszSvrName;
	return "Unknown";
}

ISocket* IProtocol::GetCurSock() const
{
	if(_pConnHandler == NULL)
		return NULL;
	return _pConnHandler->GetCurSock();
}

EHostType IProtocol::GetPeerType() const
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
		return eHostNone;
	return pSocket->GetPeerType();
}

UINT32 IProtocol::GetCurSvrID()
{
	if(_pConnHandler == NULL)
		return 0;
	return _pConnHandler->GetCurSvrID();
}

UINT64 IProtocol::GetCurUsrID()
{
	if(_pConnHandler == NULL)
		return 0;
	return _pConnHandler->GetCurUsrID();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace NetInterface
{
#ifdef __GNUG__
	void OnExit()
	{
		CException::RecordExit(false);
	}
#endif

	bool InitNetwork(UINT32 dwSvrID, UINT32 dwClientBufSize, UINT32 dwServerBufSize,UINT8 byIndex)
	{
		if(!CNetTimerMgr::Instance().Init())
			return false;
#ifdef _WIN32
		return CIOCPMgr::Instance().Init(dwSvrID, dwClientBufSize, dwServerBufSize);
#else
		int rc = atexit(OnExit);
		if(rc < 0)
		{
			printf("atexit fails!");
			return false;
		}
		return CEPollMgr::Instance().Init(dwSvrID, dwClientBufSize, dwServerBufSize,byIndex); //启动监听，发送和接收进程
#endif
	}

	void ShutdownNetwork()
	{
		LOG_INF << LOGCTL_NO_CONSOLE << "Network shutdown!";
		CNetTimerMgr::Instance().Stop();
		CNetIFMgr::Instance().Shutdown();
		CNetIFMgr::Instance().WaitForShutdown();
	}

	void OnLogicInitFinish()
	{
		CNetIFMgr::Instance().OnInitFinish();
	}

	bool ListenOnPort(UINT16 wPort, bool bIsClient, UINT32 dwBackLog, IAcceptHandler& rAcceptHandler)
	{
		CNetIFMgr& rIFMgr = CNetIFMgr::Instance();
		if(!rIFMgr.IsRun())
			return false;
		CBaseListener* pListener = rIFMgr.GetListener(wPort);
		if(pListener != NULL)
			return false;
		pListener = rIFMgr.CreateListener(bIsClient);
		if(pListener == NULL)
			return false;
		if(!pListener->Listen(wPort, dwBackLog, rAcceptHandler))
		{
			delete pListener;
			return false;
		}
		rIFMgr.AddListener(wPort, pListener);
		return true;
	}

	bool Connect(const char* pszAddr, UINT16 wPort, EHostType ePeerType, UINT32 dwPeerID, IConnectHandler& rConnectHandler)
	{
		CNetIFMgr& rIFMgr = CNetIFMgr::Instance();
		if(!rIFMgr.IsRun())
			return false;
		SIPAndPort oIPAndPort = { pszAddr, wPort };
		if(rIFMgr.IsConnecting(oIPAndPort))
			return false;
		CBaseSocket* pSocket = rIFMgr.CreateSocket();
		return pSocket->Connect(ePeerType, dwPeerID, pszAddr, wPort, rConnectHandler);
	}

	void SetUserLogicFunc(FnUserLogic fnUserLogic)
	{
		CNetIFMgr::Instance().SetUserLogicFunc(fnUserLogic);
	}

	void SetExceptionCallbackFunc(FnExceptionCallback fnExceptionCallback)
	{
		CNetIFMgr::Instance().SetExceptionCallbackFunc(fnExceptionCallback);
	}

	void SetPreShutdown(FnUserLogicExit fnPreShutdown)
	{
		CNetIFMgr::Instance().SetPreShutdown(fnPreShutdown);
	}

	void SetUserLogicExit(FnUserLogicExit fnUserLogicExit)
	{
		CNetIFMgr::Instance().SetUserLogicExit(fnUserLogicExit);
	}

	bool OpenTimer(ITimer& rTimer, UINT32 dwPeriod)
	{
		return CNetTimerMgr::Instance().OpenTimer(rTimer, dwPeriod);
	}

	bool CloseTimer(ITimer& rTimer)
	{
		return CNetTimerMgr::Instance().CloseTimer(rTimer);
	}

	bool StartTimer()
	{
		return CNetTimerMgr::Instance().Start();
	}

	bool GetLocalAddress(std::vector<std::string>& vecAddr)
	{
#ifdef _WIN32
		ULONG size = 0;
		if(GetIpAddrTable(NULL, &size, FALSE) != ERROR_INSUFFICIENT_BUFFER)
			return false;

		BYTE* pBuf = new BYTE[size];
		if(pBuf == NULL)
			return false;
		MIB_IPADDRTABLE* pIPTable = (MIB_IPADDRTABLE*)pBuf;

		if(GetIpAddrTable(pIPTable, &size, TRUE) != NO_ERROR)
		{
			delete[] pBuf;
			return false;
		}

		for(DWORD i = 0; i < pIPTable->dwNumEntries; ++i)
		{
			DWORD dwAddr = pIPTable->table[i].dwAddr;
			IN_ADDR inAddr;
			inAddr.S_un.S_addr = dwAddr;
			vecAddr.push_back(inet_ntoa(inAddr));
		}
		delete[] pBuf;
#else
		ifaddrs *pAddrHead = NULL, *pAddr = NULL;
		if(getifaddrs(&pAddrHead) < 0)
			return false;
		pAddr = pAddrHead;
		while(pAddr != NULL)
		{
			if(pAddr->ifa_addr->sa_family == AF_INET)
			{
				in_addr* pInAddr = &((sockaddr_in*)pAddr->ifa_addr)->sin_addr;
				char szBuf[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, pInAddr, szBuf, INET_ADDRSTRLEN);
				vecAddr.push_back(szBuf);
			}
			pAddr = pAddr->ifa_next;
		}
		freeifaddrs(pAddrHead);
#endif
		return true;
	}
}
