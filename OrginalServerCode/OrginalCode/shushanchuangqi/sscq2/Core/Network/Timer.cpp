/********************************************************************
// Server Network Library Source File.
// File name:  Timer.cpp
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

#ifdef __GNUG__
#include <sys/timerfd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#endif
#include "Timer.h"
#include "NetIFMgr.h"

#ifdef __GNUG__
void CTimeHandler::OnTimeOut()
{
	SNetEvent oEvt;
	oEvt.eType = eTimer;
	oEvt.timer.pTimer = &_rTimer;
	CNetIFMgr::Instance().PushNetEvent(oEvt);
}

void CTimeHandler::Release()
{
	_rTimer.SetHandle(NULL);
	delete this;
}

CTimeHandler* CTimeHandler::Create(ITimer& rTimer)
{
	CTimeHandler* pHandler = new CTimeHandler(rTimer);
	if(pHandler != NULL)
		rTimer.SetHandle(pHandler);
	return pHandler;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//时钟轮实现

static const UINT32 ELEMENT_CNT_PER_BUCKET[] = { 256, 64, 64, 64, 64 };
static const UINT32 RIGHT_SHIFT_PER_BUCKET[] = { 8, 6, 6, 6, 6 };
static const UINT32 BASE_PER_BUCKET[] = { 1, 256, 256 * 64, 256 * 64 * 64, 256 * 64 * 64 * 64 };

CTimingWheel::CTimingWheel()
{
	for(int bucketNo = 0; bucketNo < BUCKET_CNT; bucketNo++)
	{
		_newest[bucketNo] = 0;
		_buckets[bucketNo] = new std::list<SListNode>[ELEMENT_CNT_PER_BUCKET[bucketNo]];
	}
}

CTimingWheel::~CTimingWheel()
{
	for(int bucketNo = 0; bucketNo < BUCKET_CNT; bucketNo++)
	{
		for(UINT32 n=0; n<ELEMENT_CNT_PER_BUCKET[bucketNo]; ++n)
		{
			std::list<SListNode>& listNode = _buckets[bucketNo][n];
			for(auto it = listNode.begin(); it != listNode.end(); ++it)
				it->pHandler->Release();
		}
		delete[] _buckets[bucketNo];
	}
}

void CTimingWheel::SetTimer(UINT32 dwInterval, CTimeHandler* pHandler)
{
	assert(dwInterval > 0);
	UINT32 bucketNo = 0;
	UINT32 offset = dwInterval;
	UINT32 left = dwInterval;
	while(offset >= ELEMENT_CNT_PER_BUCKET[bucketNo])
	{
		offset >>= RIGHT_SHIFT_PER_BUCKET[bucketNo];
		left -= BASE_PER_BUCKET[bucketNo] * (ELEMENT_CNT_PER_BUCKET[bucketNo] - _newest[bucketNo] - (bucketNo == 0 ? 0 : 1));
		++bucketNo;
	}
	assert(offset >= 1);
	assert(dwInterval >= BASE_PER_BUCKET[bucketNo] * offset);
	left -= BASE_PER_BUCKET[bucketNo] * (offset - 1);
	UINT32 pos = (_newest[bucketNo] + offset) % ELEMENT_CNT_PER_BUCKET[bucketNo];
	_buckets[bucketNo][pos].push_back(SListNode(left, pHandler));
}

void CTimingWheel::Step()
{
	std::vector<CTimeHandler*> vecHandler;
	for(int bucketNo = 0; bucketNo < BUCKET_CNT; bucketNo++)
	{
		_newest[bucketNo] = (_newest[bucketNo] + 1) % ELEMENT_CNT_PER_BUCKET[bucketNo];
		std::list<SListNode>& curList = _buckets[bucketNo][_newest[bucketNo]];
		while(!curList.empty())
		{
			if(bucketNo == 0 || curList.front().dwInterval == 0)
				vecHandler.push_back(curList.front().pHandler);
			else
				SetTimer(curList.front().dwInterval, curList.front().pHandler);
			curList.pop_front();
		}
		if(_newest[bucketNo] != 0)
			break;
	}
	for(std::size_t i = 0; i < vecHandler.size(); i++)
	{
		vecHandler[i]->OnTimeOut();
		SetTimer(vecHandler[i]->GetInterval(), vecHandler[i]);
	}
}

#endif

CNetTimerMgr& CNetTimerMgr::Instance()
{
	static CNetTimerMgr oTimer;
	return oTimer;
}

CNetTimerMgr::~CNetTimerMgr()
{
	Stop();
}

bool CNetTimerMgr::Init()
{
#ifdef _WIN32
	_hTimerQueue = CreateTimerQueue();
	return _hTimerQueue != NULL;
#else
	timespec tp = { 0, STEP_MILLISECOND * 1000000 };
	itimerspec ts;
	ts.it_value = tp;
	ts.it_interval = tp;
	_fdTimer = timerfd_create(CLOCK_REALTIME, 0);
	if(_fdTimer == -1)
		return false;
	if(timerfd_settime(_fdTimer, 0, &ts, NULL) == -1)
		return false;
#endif
	return true;
}

bool CNetTimerMgr::Start()
{
#ifdef __GNUG__
	_bTimerRun = true;
	if(!_tTimerThread.Start(TimerThread, this))
		return false;
#endif
	return true;
}

void CNetTimerMgr::Stop()
{
#ifdef _WIN32
	if(_hTimerQueue != NULL && DeleteTimerQueueEx(_hTimerQueue, NULL))
		_hTimerQueue = NULL;
#else
	_bTimerRun = false;
	_tTimerThread.Join();
#endif
}

bool CNetTimerMgr::OpenTimer(ITimer& rTimer, UINT32 dwPeriod)
{
#ifdef _WIN32
	HANDLE hTimer = NULL;
	UINT32 dwDueTime = rand() % dwPeriod;
	if(!CreateTimerQueueTimer(&hTimer, _hTimerQueue, (WAITORTIMERCALLBACK)TimerRoutine, &rTimer, dwDueTime, dwPeriod, 0))
		return false;
	rTimer.SetHandle(hTimer);
#else
	CTimeHandler* pTimerHandler = CTimeHandler::Create(rTimer);
	if(pTimerHandler == NULL)
		return false;
	pTimerHandler->SetOpen(true);
	UINT32 dwInterval = dwPeriod / STEP_MILLISECOND;
	pTimerHandler->SetInterval(dwInterval);
	_oTimingWheel.SetTimer(dwInterval, pTimerHandler);
#endif
	return true;
}

bool CNetTimerMgr::CloseTimer(ITimer& rTimer)
{
#ifdef _WIN32
	HANDLE hTimer = rTimer.GetHandle();
	if(hTimer == NULL)
		return true;
	if(!DeleteTimerQueueTimer(_hTimerQueue, hTimer, NULL))
		return false;
	rTimer.SetHandle(NULL);
#else
	CTimeHandler* pHandler = (CTimeHandler*)rTimer.GetHandle();
	if(pHandler != NULL)
		pHandler->SetOpen(false);
#endif
	return true;
}

#ifdef _WIN32
VOID CALLBACK CNetTimerMgr::TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
	if(lpParam != NULL)
	{
		SNetEvent oEvt;
		oEvt.eType = eTimer;
		oEvt.timer.pTimer = (ITimer*)lpParam;
		CNetIFMgr::Instance().PushNetEvent(oEvt);
	}
}
#else
void CNetTimerMgr::TimerThread(CNetTimerMgr* pThis)
{
	uint64_t qwNum = 0;
	while(true)
	{
		read(pThis->_fdTimer, &qwNum, sizeof(uint64_t));
		if(!pThis->_bTimerRun)
			break;
		pThis->_oTimingWheel.Step();
	}
}
#endif
