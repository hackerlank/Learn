/********************************************************************
//	Login Server Source File.
//	File name:	Config.cpp
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

#include "stdafx.h"
#ifdef _WIN32
#include "resource.h"
#include "LoginServerDlg.h"
#endif
#include "tinyxml.h"

CLoginConfig& CLoginConfig::Instance()
{
	static CLoginConfig config(NetMgr);
	return config;
}

bool CLoginConfig::InitServer()
{
	if(!CTimerMgr::Instance().OpenAllTimer())
	{
		LOG_CRI << "CTimerMgr::OpenAllTimer fails!";
		return false;
	}
	return true;
}

void CLoginConfig::UnInitServer()
{
}

bool CLoginConfig::OnAccept(ISocket& rSocket)
{
	EHostType ePeerType = rSocket.GetPeerType();
	if(ePeerType == eHostClient)
	{
		if(!_bShowClient)
			return true;
#ifdef _WIN32
		if(_pServerDlg != NULL)
			_pServerDlg->AddToList(rSocket);
#else
		_setCltSocket.insert(&rSocket);
#endif
	}
	else
	{
		if(!CConfig::OnAccept(rSocket))
			return false;
	}
	return true;
}

void CLoginConfig::OnClose(ISocket& rSocket)
{
	if(rSocket.GetPeerType() == eHostClient)
	{
		if(!_bShowClient)
			return;
#ifdef _WIN32
		if(_pServerDlg != NULL)
			_pServerDlg->DelFromList(rSocket);
#else
		_setCltSocket.erase(&rSocket);
#endif
	}
	else
	{
		CConfig::OnClose(rSocket);
	}
}

void CLoginConfig::GetExtraInfo(string& strInfo)
{
	if(_setCltSocket.empty())
		return;
	ostringstream os;
	os << "Accept Client:\n";
	for(auto it = _setCltSocket.begin(); it != _setCltSocket.end(); ++it)
	{
		ISocket& rSocket = **it;
		os << "\tAddress: " << rSocket.GetPeerAddrStr() << ", Port: " << rSocket.GetPeerPort() << "\n";
	}
	strInfo += os.str();
}
