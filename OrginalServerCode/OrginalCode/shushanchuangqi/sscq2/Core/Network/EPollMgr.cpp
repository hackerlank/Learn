/********************************************************************
// Server Network Library Source File.
// File name:  EPollMgr.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/epoll.h>
#include "Linux.h"
#include "Directory.h"
#include "Exception.h"
#include "EPollMgr.h"
#include "EPollListener.h"

#define gettid() syscall(__NR_gettid)

#define MAXEVENTS 64

bool EPollInCtl(int op, uint32_t events, SIOEvent& rEvent, int fd)
{
	epoll_event event;
	event.data.ptr = &rEvent;
	event.events = events;
	int rc = epoll_ctl(CEPollMgr::Instance().GetEPollInFD(), op, fd, &event);
	if(rc < 0)
	{
		LOG_CRI<< "epoll_ctl fails: " << ERRDESC;
		return false;
	}
	return true;
}

bool EPollOutCtl(int op, uint32_t events, SIOEvent& rEvent, int fd)
{
	epoll_event event;
	event.data.ptr = &rEvent;
	event.events = events;
	int rc = epoll_ctl(CEPollMgr::Instance().GetEPollOutFD(), op, fd, &event);
	if(rc < 0)
	{
		LOG_CRI<< "epoll_ctl fails: " << ERRDESC;
		return false;
	}
	return true;
}

bool EPollListenCtl(int op, uint32_t events, SIOEvent& rEvent, int fd)
{
	epoll_event event;
	event.data.ptr = &rEvent;
	event.events = events;
	int rc = epoll_ctl(CEPollMgr::Instance().GetEPollListenFD(), op, fd, &event);
	if(rc < 0)
	{
		LOG_CRI<< "epoll_ctl fails: " << ERRDESC;
		return false;
	}
	return true;
}

bool EPollInDel(int fd)
{
	int rc = epoll_ctl(CEPollMgr::Instance().GetEPollInFD(), EPOLL_CTL_DEL, fd, NULL);
	if(rc < 0)
	{
		LOG_WRN << "epoll_ctl fails: " << ERRDESC;
		return false;
	}
	return true;
}

bool EPollOutDel(int fd)
{
	int rc = epoll_ctl(CEPollMgr::Instance().GetEPollOutFD(), EPOLL_CTL_DEL, fd, NULL);
	if(rc < 0)
	{
		LOG_WRN << "epoll_ctl fails: " << ERRDESC;
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////

CEPollMgr::CEPollMgr()
	: _fdEpollIn(0)
	, _fdEpollOut(0)
	, _fdEpollListen(0)
{
}

UINT32 CEPollMgr::GetProcessorCount()
{
	return sysconf(_SC_NPROCESSORS_ONLN);
}

UINT32 CEPollMgr::GetSysPageSize()
{
	return sysconf(_SC_PAGESIZE);
}

CBaseSocket* CEPollMgr::CreateSocket(SOCKET sock)
{
	return new CEPollSocket(sock);
}

CBaseListener* CEPollMgr::CreateListener(bool bIsClient)
{
	return new CEPollListener(bIsClient);
}

bool CEPollMgr::Init(UINT32 dwSvrID, UINT32 dwClientBufSize, UINT32 dwServerBufSize,UINT8 byIndex)
{
	if(!CNetIFMgr::Init(dwSvrID, dwClientBufSize, dwServerBufSize, byIndex))
		return false;

	UINT32 dwCoreCount = GetProcessorCount();
	if(dwCoreCount < 2)
		dwCoreCount = 2;
    if(dwCoreCount > 4)
        dwCoreCount = 4;

	if(!CException::Init())
	{
		LOG_CRI << "CException::Init fails!";
		return false;
	}

	_fdEpollIn = epoll_create1(0);
	if(_fdEpollIn == -1)
	{
		LOG_CRI<< "epoll_create fails: " << ERRDESC;
		return false;
	}

	_fdEpollOut = epoll_create1(0);
	if(_fdEpollOut == -1)
	{
		LOG_CRI<< "epoll_create fails: " << ERRDESC;
		return false;
	}

	_fdEpollListen = epoll_create1(0);
	if(_fdEpollListen == -1)
	{
		LOG_CRI<< "epoll_create fails: " << ERRDESC;
		return false;
	}

	for(UINT32 i = 0; i < dwCoreCount; ++i)
	{
		CThread thrd;
		if(!thrd.Start(NetworkInThread, this))
			return false;
		_vecNetworkThreads.emplace_back(move(thrd));
	}
	for(UINT32 i = 0; i < dwCoreCount; ++i)
	{
		CThread thrd;
		if(!thrd.Start(NetworkOutThread, this))
			return false;
		_vecNetworkThreads.emplace_back(move(thrd));
	}
    if(!_tListenThread.Start(NetworkListenThread, this))
        return false;
	if(!_tLogicThread.Start(LogicThread, this))
		return false;
	if(!_tManageThread.Start(ManageThread, this))
		return false;
	return true;
}

void CEPollMgr::NetworkListenThread(CEPollMgr* pThis)
{
	epoll_event events[MAXEVENTS]; // = 60
	int n = 0;
	while(pThis->_bRun)
	{
		n = epoll_wait(pThis->_fdEpollListen, events, MAXEVENTS, 100);
		for(int i = 0; i < n; ++i)
		{
			epoll_event event = events[i];
			SIOEvent* pEvent = (SIOEvent*)event.data.ptr;
			if((event.events & EPOLLERR) || (event.events & EPOLLHUP))
			{
				LOG_DBG << "epoll_wait error: " << ERRDESC << ", type:" << pEvent->eIOType;
				continue;
			}
			switch(pEvent->eIOType)
			{
			case SIOEvent::eIOAccept:
				{
					CEPollListener* pListener = (CEPollListener*)pEvent->pData;
					pListener->OnAccept();
				}
				break;
                /*
			case SIOEvent::eIORecv:
				{
					CEPollSocket* pSocket = (CEPollSocket*)pEvent->pData;
					pSocket->OnRecv();
				}
				break;
                */
			default:
				LOG_CRI << "Epoll Error! Type: " << pEvent->eIOType;
				break;
			}
		}
	}
}


void CEPollMgr::NetworkInThread(CEPollMgr* pThis)
{
	epoll_event events[MAXEVENTS];
	int n = 0;
	while(pThis->_bRun)
	{
		n = epoll_wait(pThis->_fdEpollIn, events, MAXEVENTS, 100);
		for(int i = 0; i < n; ++i)
		{
			epoll_event event = events[i];
			SIOEvent* pEvent = (SIOEvent*)event.data.ptr;
			if((event.events & EPOLLERR) || (event.events & EPOLLHUP))
			{
				LOG_DBG << "epoll_wait error: " << ERRDESC << ", type:" << pEvent->eIOType;
				continue;
			}
			switch(pEvent->eIOType)
			{
                /*
			case SIOEvent::eIOAccept:
				{
					CEPollListener* pListener = (CEPollListener*)pEvent->pData;
					pListener->OnAccept();
				}
				break;
                */
			case SIOEvent::eIORecv:
				{
					CEPollSocket* pSocket = (CEPollSocket*)pEvent->pData;
					pSocket->OnRecv();
				}
				break;
			default:
				LOG_CRI << "Epoll Error! Type: " << pEvent->eIOType;
				break;
			}
		}
	}
}

void CEPollMgr::NetworkOutThread(CEPollMgr* pThis)
{
	epoll_event events[MAXEVENTS];
	int n = 0;
	bool bError = false;
	while(pThis->_bRun)
	{
		n = epoll_wait(pThis->_fdEpollOut, events, MAXEVENTS, 100);
		for(int i = 0; i < n; ++i)
		{
			bError = false;
			epoll_event event = events[i];
			SIOEvent* pEvent = (SIOEvent*)event.data.ptr;
			if((event.events & EPOLLERR) || (event.events & EPOLLHUP))
			{
				LOG_DBG << "epoll_wait error:" << errno << ", type:" << pEvent->eIOType;
				bError = true;
			}
			switch(pEvent->eIOType)
			{
			case SIOEvent::eIOSend:
				{
					CEPollSocket* pSocket = (CEPollSocket*)pEvent->pData;
					if(pSocket->GetSocketState() == CBaseSocket::SOCK_STATE_CONNECTING)
						pSocket->OnConnected(!bError);
					else
						pSocket->OnSend();
				}
				break;
			default:
				LOG_CRI << "Epoll Error! Type: " << pEvent->eIOType;
				break;
			}
		}
	}
}
