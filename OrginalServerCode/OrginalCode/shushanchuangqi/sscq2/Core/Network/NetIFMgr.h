/********************************************************************
// Server Network Library Source File.
// File name:  NetIFMgr.h
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
#include <set>
#include <iostream>
#include "LockFree.h"
#include "LoopBuffer.h"
#include "Lock.h"
#include "Singleton.h"
#include "Event.h"
#include "Thread.h"
#include "Interface.h"

using namespace std;
using namespace NetInterface;

class CBaseSocket;
class CBaseConnector;
class CBaseListener;
class CBaseAcceptor;

//网络线程抛到逻辑线程处理的事件类型
enum EEvtType
{
	eEvtNone,
	eConnect,
	eAccept,
	eRecv,
	eSend,
	eTimer,
	eClose,
	eError,
	eFunc
};

//Recv事件
struct SRecv
{
	CBaseSocket* pSocket;
	int len;
};

//Send事件
struct SSend
{
	CBaseSocket* pSocket;
};

//Connect事件
struct SConnect
{
	CBaseSocket* pSocket;
	bool bSucceed;
};

//Accept事件
struct SAccept
{
	CBaseSocket* pSocket;
};

//定时器事件
struct STimer
{
	ITimer* pTimer;
};

//关闭Socket事件
struct SClose
{
	CBaseSocket* pSocket;
	UINT32 dwError;
};

//执行函数的事件
struct SFunc
{
	FnUserLogicExit pFunc;
};

//网络线程事件包装器
struct SNetEvent
{
	EEvtType eType;
	union
	{
		SRecv recv;
		SSend send;
		SConnect connect;
		SAccept accept;
		STimer timer;
		SClose close;
		SFunc func;
	};

	SNetEvent()
	{
		memset(this, 0, sizeof *this);
	}
};

struct SIPAndPort
{
	string strIP;
	UINT16 wPort;
};

namespace std
{
	template<> struct less<SIPAndPort> : public binary_function<SIPAndPort, SIPAndPort, bool>
	{
		bool operator()(const SIPAndPort& left, const SIPAndPort& right) const
		{
			int ret = left.strIP.compare(right.strIP);
			if(ret < 0)
				return true;
			if(ret > 0)
				return false;
			if(left.wPort < right.wPort)
				return true;
			if(left.wPort > right.wPort)
				return false;
			return false;
		}
	};
}

//网络接口管理器
class CNetIFMgr
{
	friend class CException;
public:
	CNetIFMgr();
	virtual ~CNetIFMgr();

	static CNetIFMgr& Instance() { return *_pNetIFMgr; }

	bool IsRun() const { return _bRun; }

	virtual bool Init(UINT32 dwSvrID, UINT32 dwClientBufSize, UINT32 dwServerBufSize,UINT8 byIndex);
	void Shutdown();

	void WaitForShutdown();
	void OnInitFinish();

	virtual void AddListener(UINT16 wPort, CBaseListener* pListener);
	virtual void DelListener(UINT16 wPort);
	CBaseListener* GetListener(UINT16 wPort);
	void GetListeners(map<UINT16, CBaseListener*>& rMapListener);

	virtual CBaseSocket* CreateSocket(SOCKET sock = INVALID_SOCKET) = 0;
	virtual CBaseListener* CreateListener(bool bIsClient) = 0;

	void AddConnector(SIPAndPort& rIPAndPort, CBaseSocket* pSocket);
	void DelConnector(CBaseSocket* pSocket);
	bool IsConnecting(SIPAndPort& rIPAndPort);

	virtual bool CheckDel();

	static void LogicThread(CNetIFMgr* pThis);
	static void ManageThread(CNetIFMgr* pThis);

	virtual bool ProcessNetEvent(SNetEvent& rNetEvt);
	void TrimNetEvent();
	bool PushNetEvent(SNetEvent& rNetEvt);
	bool PopNetEvent();

	virtual bool ProcessUserLogic(UINT64 dwMaxTickCount);

	void AddSockToDel(CBaseSocket* pSocket);
	bool CheckDelSock(bool bForce);

	EHostType GetServerType() const { return _eSvrType; }
	UINT32 GetClientBufSize() const { return _dwClientBufSize; }
	UINT32 GetServerBufSize() const { return _dwServerBufSize; }

	static void SetUserLogicFunc(FnUserLogic fnUserLogic);
	static void SetExceptionCallbackFunc(FnExceptionCallback fnExceptionCallback);
	static void OnExceptionCallback(EExceptType eExceptType);
	static void SetUserLogicExit(FnUserLogicExit fnUserLogicExit);
	static void SetPreShutdown(FnUserLogicExit fnPreShutdown);

	virtual UINT32 GetProcessorCount() = 0;
	virtual UINT32 GetSysPageSize() = 0;

protected:
	void ShutdownListener();
	void ShutdownNotify();
	void ShutdownWaitSending();
	void ShutdownLogicThread();
	void ShutdownNetworkThread();
	void ShutdownManageThread();
    void ShutdownListenThread();

protected:
	EHostType _eSvrType;		//主机类型
	UINT32 _dwClientBufSize;	//客户端缓冲区大小
	UINT32 _dwServerBufSize;	//服务器缓冲区大小

	bool _bRun;			//网络层是否在运行
	bool _bLogicRun;	//逻辑线程是否在运行
	bool _bNetRun;		//网络线程是否在运行
	bool _bManRun;		//管理线程是否在运行
	bool _bListenRun;	//监听线程是否在运行

	CLockFreeQueue<SNetEvent> _queEvent;	//网络线程和定时器线程投递的事件队列
	deque<SNetEvent> _deqNetEvt;			//逻辑线程一次处理的事件队列
	deque<SNetEvent>::iterator _itEvt;		//当前的迭代器

	UINT64 _qwLogicStartTick;		//逻辑线程一次处理的开始时间

	CThread _tLogicThread;		//逻辑线程
	CThread _tManageThread;		//管理线程
	vector<CThread> _vecNetworkThreads;		//网络线程
	CThread _tListenThread;		//Listen线程

	CEvent _evtInit;			//初始化同步事件
	CEvent _evtShutdown;		//关闭时的同步事件
	CEvent _evtPreShutdown;		//关闭前的同步事件

	map<UINT16, CBaseListener*> _mapListener;	//端口到监听器的映射
	CSpinLock _spLsn;

	map<SIPAndPort, CBaseSocket*> _mapConnector;	//(地址, 端口)到连接正在连接中Socket的映射
	CSpinLock _spCon;

	set<CBaseSocket*> _setDelSocket;	//将要被释放的Socket的集合
	CSpinLock _spDel;

	static FnUserLogic _fnUserLogic;	//逻辑层在协议处理函数和时钟处理函数外需要执行的函数
	static FnExceptionCallback _fnExceptionCallback;	//进程发生异常时的处理函数
	static FnUserLogicExit _fnPreShutdown;		//在进程关闭前需要运行的函数
	static FnUserLogicExit _fnUserLogicExit;	//在逻辑线程退出前需要运行的函数

	static void DoPreShutdown();
	static CNetIFMgr* _pNetIFMgr;
};
