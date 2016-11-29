/********************************************************************
// Server Network Library Source File.
// File name:  BaseListener.cpp
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

#include "GlobalDefine.h"
#include "BaseSocket.h"
#include "BaseListener.h"
#include "ServerID.h"
#include "NetIFMgr.h"

CBaseListener::CBaseListener(bool bIsClient)
	: _socket(INVALID_SOCKET)
	, _pAcceptHandler(NULL)
	, _bIsClient(bIsClient)
{
	if(bIsClient)
		_dwBufferSize = CNetIFMgr::Instance().GetClientBufSize();
	else
		_dwBufferSize = CNetIFMgr::Instance().GetServerBufSize();
}

CBaseListener::~CBaseListener()
{
	if(_socket != INVALID_SOCKET)
		closesocket(_socket);
}

SOCKET CBaseListener::CreateAndBind(UINT16 wPort)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		LOG_CRI << "Could not create socket: " << ERRDESC;
		return INVALID_SOCKET;
	}

	int optval = 1;
	if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof optval) < 0)
	{
		LOG_CRI << "setsockopt fails: " << ERRDESC;
		closesocket(s);
		return INVALID_SOCKET;
	}

	sockaddr_in saServer;
	memset(&saServer, 0, sizeof saServer);
	saServer.sin_port = htons(wPort);
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = htonl(INADDR_ANY);

	if(::bind(s, (sockaddr*)&saServer, sizeof saServer) < 0)
	{
		LOG_DBG << "bind fails:" << ERRDESC;
		closesocket(s);
		return INVALID_SOCKET;
	}
	return s;
}

bool CBaseListener::Listen(UINT16 wPort, UINT32 dwBackLog, IAcceptHandler& rHandler)
{
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(_socket == INVALID_SOCKET)
	{
		LOG_CRI << "Could not create socket: " << ERRDESC;
		return false;
	}

	int optval = 1;
	if(setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof optval) < 0)
	{
		LOG_CRI << "setsockopt fails: " << ERRDESC;
		return false;
	}

	if(!CBaseSocket::MakeNonBlocking(_socket))
		return false;

	_pAcceptHandler = &rHandler;

	sockaddr_in saServer;
	memset(&saServer, 0, sizeof saServer);
	saServer.sin_family = AF_INET;
	saServer.sin_port = htons(wPort);
	saServer.sin_addr.s_addr = htonl(INADDR_ANY);

	if(::bind(_socket, (sockaddr*)&saServer, sizeof saServer) < 0)
	{
		LOG_CRI << "bind fails:" << ERRDESC;
		return false;
	}

	int rc = listen(_socket, dwBackLog);
	if(rc == -1)
	{
		LOG_CRI << "listen fails: " << ERRDESC;
		return false;
	}

	return ActiveListen();
}

bool CBaseListener::StopListen()
{
	closesocket(_socket);
	_socket = INVALID_SOCKET;
	return true;
}

bool CBaseListener::WaitStop(UINT32 dwTimeout)
{
	return _evtStop.Wait(dwTimeout);
}
