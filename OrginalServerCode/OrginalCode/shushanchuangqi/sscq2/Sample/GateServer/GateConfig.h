/********************************************************************
 //	Gate Server Source File.
 //	File name:	Config.h
 //	Created:	2011/06/03	10:00
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
class CGateServerDlg;
#endif

class CNetMgr;
class TiXmlElement;

class CGateConfig : public CConfig
{
	friend class CRequestHandler;
public:
	static CGateConfig& Instance();
	CGateConfig(CNetMgr& rNetMgr) : CConfig(rNetMgr), _wClientCount(0) { }

	virtual bool OnAccept(ISocket& rSocket);
	virtual void OnClose(ISocket& rSocket);

	virtual void GetExtraInfo(string& strInfo) override;
	EHostType GetProxyByProt(UINT8 byProtID);

private:
	bool InitProtProxy();
	virtual bool InitServer();

public:
	vector<EHostType> _vecProxyInfo;
	UINT16 _wClientCount;
	set<ISocket*> _setCltSocket;
};

#define Config CGateConfig::Instance()
