/********************************************************************
// Server Network Library Source File.
// File name:  BaseListener.h
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
#include <string>
#include "Interface.h"
#include "Event.h"

using namespace std;

class CBaseSocket;

//监听器基础类
class CBaseListener
{
public:
	CBaseListener(bool bIsClient);
	virtual ~CBaseListener();

	virtual bool Listen(UINT16 wPort, UINT32 dwBackLog, IAcceptHandler& rHandler);
	virtual bool ActiveListen() { return true; }
	virtual bool StopListen();
	virtual bool WaitStop(UINT32 dwTimeout);

protected:
	SOCKET CreateAndBind(UINT16 wPort);
	IAcceptHandler* GetAcceptHandler() { return _pAcceptHandler; }

protected:
	SOCKET _socket;
	IAcceptHandler* _pAcceptHandler;	//Accpet处理器
	CEvent _evtStop;		//停止监听事件
	UINT32 _dwBufferSize;	//Accept到的Socket需要分配的缓冲区大小
	bool _bIsClient;		//监听对方是否为客户端(前端)
};
