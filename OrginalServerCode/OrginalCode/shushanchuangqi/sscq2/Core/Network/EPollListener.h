/********************************************************************
// Server Network Library Source File.
// File name:  EPollListener.h
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
#include "GlobalDefine.h"
#include "BaseListener.h"
#include "BaseSocket.h"

//EPoll监听器
class CEPollListener: public CBaseListener
{
public:
	DEF_NET_NEW_DELETE(CEPollListener);
	CEPollListener(bool bIsClient);
	virtual bool Listen(UINT16 wPort, UINT32 dwBackLog, IAcceptHandler& rHandler);
	bool OnAccept();

	SIOEvent _oIOEvent; //IO事件
};
