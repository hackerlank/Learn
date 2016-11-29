/********************************************************************
// Server Network Library Source File.
// File name:  EPollMgr.h
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
#include <deque>
#include <iostream>
#include "LoopBuffer.h"
#include "NetIFMgr.h"
#include "LinuxTime.h"
#include "Event.h"
#include "Singleton.h"
#include "EPollSocket.h"

using namespace std;
using namespace NetInterface;

//设置fd为非阻塞
int MakeNonBlocking(SOCKET sock);

//在EPoll读FD上注册fd的相关事件
bool EPollInCtl(int op, uint32_t events, SIOEvent& rEvent, int fd);

//EPoll写FD上注册fd的相关事件
bool EPollOutCtl(int op, uint32_t events, SIOEvent& rEvent, int fd);

//EPoll监听FD上注册fd的相关事件
bool EPollListenCtl(int op, uint32_t events, SIOEvent& rEvent, int fd);

//删除与EPoll读FD关联的fd
bool EPollInDel(int fd);

//删除与EPoll写FD关联的fd
bool EPollOutDel(int fd);

//EPoll接口管理器
class CEPollMgr : public StaticSingleton<CEPollMgr>, public CNetIFMgr
{
	friend class CException;
public:
	using StaticSingleton<CEPollMgr>::Instance;

	CEPollMgr();

	bool Init(UINT32 dwSvrID, UINT32 dwClientBufSize, UINT32 dwServerBufSize,UINT8 byIndex);

	static void NetworkInThread(CEPollMgr* pThis);
	static void NetworkOutThread(CEPollMgr* pThis);
	static void NetworkListenThread(CEPollMgr* pThis);

	int GetEPollInFD() const { return _fdEpollIn; }
	int GetEPollOutFD() const { return _fdEpollOut; }
	int GetEPollListenFD() const { return _fdEpollListen; }

	virtual CBaseSocket* CreateSocket(SOCKET sock);
	virtual CBaseListener* CreateListener(bool bIsClient);

	virtual UINT32 GetProcessorCount() override;
	virtual UINT32 GetSysPageSize() override;

protected:
	int _fdEpollIn;		//EPoll读FD
	int _fdEpollOut;	//EPoll写FD
	int _fdEpollListen; //EPoll监听FD
};
