/********************************************************************
// Server Network Library Source File.
// File name:  Timer.h
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
#pragma once
#include <list>
#include <vector>
#include <stdint.h>
#include "GlobalDefine.h"

using namespace std;

class ITimer;

//定时器实现，Windows采用TimerQueue，Linux采用时钟轮算法

#ifdef __GNUG__

class CTimeHandler
{
public:
	bool IsOpened() const { return _bOpened; }
	void SetOpen(bool bOpened) { _bOpened = bOpened; }
	UINT32 GetInterval() { return _dwInterval; }
	void SetInterval(UINT32 dwInterval) { _dwInterval = dwInterval; }
	void OnTimeOut();
	void Release();
	static CTimeHandler* Create(ITimer& rTimer);

private:
	DEF_NET_NEW_DELETE(CTimeHandler);
	CTimeHandler(ITimer& rTimer) : _rTimer(rTimer), _bOpened(false), _dwInterval(0) { }

	ITimer& _rTimer;
	bool _bOpened;
	UINT32 _dwInterval;
};

//时钟轮
class CTimingWheel
{
public:
	CTimingWheel();
	~CTimingWheel();

	void SetTimer(UINT32 dwInterval, CTimeHandler* pHandler);
	void Step();

private:
	struct SListNode
	{
		UINT32 dwInterval;
		CTimeHandler* pHandler;
		SListNode(UINT32 dwInterval_, CTimeHandler* pHandler_) :
			dwInterval(dwInterval_), pHandler(pHandler_) { }
	};

	static const int BUCKET_CNT = 5;
	UINT32 _newest[BUCKET_CNT];
	list<SListNode>* _buckets[BUCKET_CNT];
};

#endif

//定时器管理器
class CNetTimerMgr
{
public:
	static CNetTimerMgr& Instance();
#ifdef _WIN32
	CNetTimerMgr() : _hTimerQueue(NULL) { }
#else
	CNetTimerMgr() : _fdTimer(0), _bTimerRun(false) { }
#endif
	~CNetTimerMgr();

	bool Init();
	bool Start();
	void Stop();
	bool OpenTimer(ITimer& rTimer, UINT32 dwPeriod);
	bool CloseTimer(ITimer& rTimer);
#ifdef _WIN32
	static VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);	//定时器线程函数
#else
	static void TimerThread(CNetTimerMgr* pThis);	//定时器线程函数
#endif
	
protected:
#ifdef _WIN32
	HANDLE _hTimerQueue;
#else
	CTimingWheel _oTimingWheel;	//时钟轮
	static const INT32 STEP_MILLISECOND = 100; //时钟轮每步的毫秒数
	CThread _tTimerThread;	//时钟轮线程
	int _fdTimer;
	bool _bTimerRun;
#endif
};
