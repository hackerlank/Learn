/********************************************************************
 //	Login Server Source File.
 //	File name:	Config.h
 //	Created:	2011/06/10	14:00
 //	Organization:
 //	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
 // ------------------------------------------------------------------
 //	Author:		Jingyuan Wang
 //	E-Mail:		tyketom@hotmail.com
 //	Http://
 // ------------------------------------------------------------------
 //	Purpose:
 //	Version:	1.0
 //	Histroy:
 *********************************************************************/

#pragma once
#include "Config.h"
#ifdef _WIN32
class CLoginServerDlg;
#endif

class CNetMgr;
class TiXmlElement;

class CLoginConfig : public CConfig
{
	friend class CRequestHandler;
public:
	static CLoginConfig& Instance();
	CLoginConfig(CNetMgr& rNetMgr) : CConfig(rNetMgr) { }

	virtual bool OnAccept(ISocket& rSocket);
	virtual void OnClose(ISocket& rSocket);

	void GetExtraInfo(string& strInfo);

private:
	virtual bool InitServer();
	virtual void UnInitServer();

	set<ISocket*> _setCltSocket;
	map<ULONG, UINT8> _mapAddr2Type;
};

#define Config CLoginConfig::Instance()
