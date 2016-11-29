/********************************************************************
// Server Network Library Source File.
// File name:  EPollSocket.cpp
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
#include "EPollSocket.h"
#include "EPollMgr.h"

CEPollSocket::CEPollSocket(SOCKET sock)
	: CBaseSocket(sock)
	, _bOutCtlAdded(false)
	, _bInCtlAdded(false)
	, _oRecv(SIOEvent::eIORecv, this)
	, _oSend(SIOEvent::eIOSend, this)
{
}

CEPollSocket::~CEPollSocket()
{
	if(_bOutCtlAdded)
		EPollOutDel(_socket);
	if(_bInCtlAdded)
		EPollInDel(_socket);
	GracefulClose();
}

bool CEPollSocket::ActiveSend()
{
	int op = EPOLL_CTL_MOD;
	bool doAdd = false;
	if(!_bOutCtlAdded)
	{
		op = EPOLL_CTL_ADD;
		doAdd = true;
		_bOutCtlAdded = true;
	}
	bool ret = EPollOutCtl(op, EPOLLOUT | EPOLLET | EPOLLONESHOT | EPOLLERR | EPOLLHUP, _oSend, _socket);
	if(!ret && doAdd)
		_bOutCtlAdded = false;
	return ret;
}

bool CEPollSocket::ActiveRecv()
{
	int op = EPOLL_CTL_MOD;
	bool doAdd = false;
	if(!_bInCtlAdded)
	{
		op = EPOLL_CTL_ADD;
		doAdd = true;
		_bInCtlAdded = true;
	}
	bool ret = EPollInCtl(op, EPOLLIN | EPOLLET | EPOLLONESHOT | EPOLLERR | EPOLLHUP, _oRecv, _socket);
	if(!ret && doAdd)
		_bInCtlAdded = false;
	return ret;
}

bool CEPollSocket::OnRecv()
{
	if(_eSockState != SOCK_STATE_ESTABLISH)
		return false;
	while(true)
	{
		SBuffer* pBuf = NULL;
		int count = 0;
		if(!_oRecvLoopBuffer.GetWriteVecBuf(pBuf, count))
		{
			LOG_CRI << "GetWriteVecBuf failed!";
			CloseEx(eSockRecvError);
			SetError();
			return false;
		}
		int rc = readv(_socket, (iovec*)pBuf, count);
		if(rc < 0)
		{
			if(errno == EWOULDBLOCK) // 对端socket没有数据可读
			{
				if(ActiveRecv())
					return true;
				LOG_CRI << "EPollInCtl fails: " << ERRDESC;
				CloseEx(eSockNetError, errno);
			}
			else if(errno == ECONNRESET)
			{
				CloseEx(eSockPeerClose);
			}
			else
			{
				LOG_CRI << "readv fails: " << ERRDESC;
				CloseEx(eSockRecvError, errno);
			}
			SetError();
			return false;
		}
		else if(rc == 0) //对端socket已经关闭
		{
			CloseEx(eSockPeerClose);
			SetError();
			return false;
		}
		else
		{
			//LOG_DBG << "[Type: " << _ePeerType << "], Data Received: " << rc;
			CBaseSocket::OnRecv(rc);
		}
	}
	return true;
}

bool CEPollSocket::OnSend()
{
	if(_eSockState != SOCK_STATE_ESTABLISH && _eSockState != SOCK_STATE_CLOSE)
	{
		LOG_CRI << "Invalid socket state: " << _eSockState << ", PeerType: " << _ePeerType << ", PeerAddr: " << GetPeerAddrStr();
		return false;
	}

	UINT32 dwToSend = _dwDataToSend.load(memory_order_relaxed);
	if(dwToSend == 0)
	{
		LOG_CRI << "Error! dwToSend == 0";
		CloseEx(eSockSendError, 1);
		SetError();
		return false;
	}

	while(true)
	{
		SBuffer* pBuf = NULL;
		int count = 0;
		if(!_oSendLoopBuffer.GetReadVecBuf(pBuf, count, dwToSend))
		{
			LOG_CRI << "GetReadVecBuf failed!";
			CloseEx(eSockSendError);
			SetError();
			return false;
		}

		int rc = writev(_socket, (iovec*)pBuf, count);
		if(rc <= 0)
		{
			if(errno == EWOULDBLOCK)
			{
				if(ActiveSend())
					return true;
				LOG_CRI << "EPollOutCtl fails: " << ERRDESC;
				CloseEx(eSockNetError);
			}
			else if(errno == ECONNRESET)
			{
				LOG_CRI << "EPollOutCtl fails: " << ERRDESC;
				CloseEx(eSockPeerClose);
			}
			else
			{
				LOG_CRI << "send fails: " << ERRDESC;
				CloseEx(eSockSendError, 2);
			}
			SetError();
			return false;
		}
		if(!_oSendLoopBuffer.ReadForward(rc))
		{
			LOG_CRI << "writev return " << rc << " larger than buffer!";
			CloseEx(eSockBufferError);
			SetError();
			return false;
		}
		UINT32 dwOldLen = _dwDataToSend.fetch_sub(rc, memory_order_relaxed);
		assert(dwOldLen >= static_cast<UINT32>(rc));
		if(dwOldLen == static_cast<UINT32>(rc))  //发送完退出
			return true;
		dwToSend = dwOldLen - rc;
	}
	return false;
}

void CEPollSocket::GracefulClose()
{
	if(shutdown(_socket, SHUT_WR) == 0)
	{
		char szBuf[64];
		recv(_socket, szBuf, sizeof szBuf, 0);
	}
	close(_socket);
}
