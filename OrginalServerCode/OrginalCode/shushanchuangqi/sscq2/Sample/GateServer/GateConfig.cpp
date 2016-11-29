/********************************************************************
//	Gate Server Source File.
//	File name:	Config.cpp
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

#include "stdafx.h"
#ifdef _WIN32
#include "resource.h"
#include "GateServerDlg.h"
#endif
#include "tinyxml.h"
#include "ProtProxy.h"

CGateConfig& CGateConfig::Instance()
{
	static CGateConfig config(NetMgr);
	return config;
}

bool CGateConfig::InitServer()
{
	if(!InitProtProxy())
	{
		LOG_CRI << "InitProtProxy fails!";
		return false;
	}
	if(!CTimerMgr::Instance().OpenAllTimer())
	{
		LOG_CRI << "CTimerMgr::OpenAllTimer fails!";
		return false;
	}
	return true;
}

bool CGateConfig::OnAccept(ISocket& rSocket)
{
	EHostType ePeerType = rSocket.GetPeerType();
	if(ePeerType != eHostClient)
		return false;
	++_wClientCount;
#ifdef _WIN32
	if(_pServerDlg != NULL)
	{
		if(_bShowClient)
			_pServerDlg->AddToList(rSocket);
		_pServerDlg->ShowClientCount(_wClientCount);
	}
#else
	if(_bShowClient)
		_setCltSocket.insert(&rSocket);
#endif
	return true;
}

void CGateConfig::OnClose(ISocket& rSocket)
{
    if(rSocket.GetPeerType() == eHostGame || rSocket.GetPeerType() == eHostCenter || rSocket.GetPeerType() == eHostDB)//踢掉所有玩家
    {
        NetMgr.GetClientMgr().KickAllClient(eLeaveExcept);
    }
	if(rSocket.GetPeerType() == eHostClient)
	{
		--_wClientCount;
#ifdef _WIN32
		if(_pServerDlg != NULL)
		{
			if(_bShowClient)
			{
				_setCltSocket.erase(&rSocket);
				_pServerDlg->DelFromList(rSocket);
			}
			_pServerDlg->ShowClientCount(_wClientCount);
		}
#else
		if(_bShowClient)
			_setCltSocket.erase(&rSocket);
#endif
	}
	else
	{
		CConfig::OnClose(rSocket);
	}
}

bool CGateConfig::InitProtProxy()
{
	UINT8 byGameServerMax = arProtGameServer[ARRAYSIZE(arProtGameServer) - 1];
	UINT8 byCenterServerMax = arProtCenterServer[ARRAYSIZE(arProtCenterServer) - 1];
	UINT8 byDBServerMax = arProtDBServer[ARRAYSIZE(arProtDBServer) - 1];
	UINT8 byCount = max(max(byGameServerMax, byCenterServerMax), byDBServerMax) + 1;
	_vecProxyInfo.resize(byCount);
	for(UINT8 byProtID : arProtGameServer)
		_vecProxyInfo[byProtID] = eHostGame;
	for(UINT8 byProtID : arProtCenterServer)
		_vecProxyInfo[byProtID] = eHostCenter;
	for(UINT8 byProtID : arProtDBServer)
		_vecProxyInfo[byProtID] = eHostDB;
	return true;
}

EHostType CGateConfig::GetProxyByProt(UINT8 byProtID)
{
	if(byProtID >= _vecProxyInfo.size())
	{
#ifdef _DEBUG
		LOG_CRI << "byProtID invalid: " << byProtID;
#endif
		return eHostNone;
	}
	return _vecProxyInfo[byProtID];
}

void CGateConfig::GetExtraInfo(string& strInfo)
{
	if(_setCltSocket.empty())
		return;
	UINT32 dwCount = 0;
	ostringstream os;
	os << "Accept Client: " << _setCltSocket.size() << "\n";
	for(auto it = _setCltSocket.begin(); it != _setCltSocket.end(); ++it)
	{
		ISocket& rSocket = **it;
		++dwCount;
		if(dwCount > 10)
			break;
		os << "\tAddress: " << rSocket.GetPeerAddrStr() << ", Port: " << rSocket.GetPeerPort() << ", UsrID: " << rSocket.GetPeerID() << "\n";
	}
	strInfo += os.str();
}
