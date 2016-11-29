/********************************************************************
// Server Network Library Source File.
// File name:  EPollSocket.h
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
#include "GlobalDefine.h"
#include "Interface.h"
#include "LoopBuffer.h"
#include "BaseSocket.h"
#include "ObjPool.h"
#include "Lock.h"

using namespace std;

//EPoll的Socket类
class CEPollSocket : public CBaseSocket
{
public:
	DEF_NET_NEW_DELETE(CEPollSocket);
	CEPollSocket(SOCKET sock = INVALID_SOCKET);
	virtual ~CEPollSocket();

	virtual bool ActiveSend() override;
	virtual bool ActiveRecv() override;
	bool OnRecv();
	bool OnSend();

	void GracefulClose(); //优雅关闭

protected:

	bool _bOutCtlAdded;	//fd是否已关联到EPoll写FD
	bool _bInCtlAdded;	//fd是否已关联到EPoll读FD

	SIOEvent _oRecv;	//接收事件
	SIOEvent _oSend;	//发送事件
};
