/********************************************************************
// Server Network Library Source File.
// File name:  EPollListener.cpp
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

#include <sys/epoll.h>
#include "ServerID.h"
#include "EPollListener.h"
#include "EPollSocket.h"
#include "EPollMgr.h"

CEPollListener::CEPollListener(bool bIsClient)
	: CBaseListener(bIsClient)
	, _oIOEvent(SIOEvent::eIOAccept, this)
{
}

bool CEPollListener::Listen(UINT16 wPort, UINT32 dwBackLog, IAcceptHandler& rHandler)
{
	if(!CBaseListener::Listen(wPort, dwBackLog, rHandler))
		return false;
	if(!EPollListenCtl(EPOLL_CTL_ADD, EPOLLIN | EPOLLET | EPOLLERR | EPOLLHUP, _oIOEvent, _socket))
	{
		LOG_CRI << "EPollInCtl fails: " << ERRDESC;
		return false;
	}
	return true;
}

bool CEPollListener::OnAccept()
{
	if(_socket == INVALID_SOCKET)
	{
		_evtStop.Set();
		return false;
	}
	while(true)
	{
		sockaddr_in inAddr;
		socklen_t inLen = sizeof inAddr;
		SOCKET infd = accept(_socket, (sockaddr*)&inAddr, &inLen);
		if(infd < 0)
		{
			if(errno == EAGAIN)
                break;
			LOG_CRI << "accept fails: " << ERRDESC;
			break;
		}
		sockaddr_in hostAddr;
		socklen_t hostLen = sizeof inAddr;
		getsockname(infd, (sockaddr*)&hostAddr, &hostLen);

		CEPollSocket* pSocket = NULL;
		if(_bIsClient)
			pSocket = new CCltSocket<CEPollSocket>(infd);
		else
			pSocket = new CEPollSocket(infd);
		if(pSocket == NULL || pSocket->GetSocketState() == CBaseSocket::SOCK_STATE_ERROR)
		{
			LOG_CRI << "Create socket fails!";
			continue;
		}
		pSocket->SetPeerType(eHostNone);
		pSocket->SetPeerID(0);
		pSocket->SetHostAddrPort(hostAddr.sin_addr.s_addr, ntohs(hostAddr.sin_port));
		pSocket->SetPeerAddrPort(inAddr.sin_addr.s_addr, ntohs(inAddr.sin_port));
		pSocket->AllocLoopBuf(_dwBufferSize);
		pSocket->SetSockHandler(_pAcceptHandler);
		pSocket->OnAccepted();
	}

	return true;
}
