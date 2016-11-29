/********************************************************************
//	Gate Server Source File.
//	File name:	NetMgr.cpp
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
#include "Protocols.h"
#include "Encode.h"

bool CGateSvrHandler::OnRecv(const char* pBuf, UINT32 dwLen)
{
	ISocket* pSocket = GetCurSock();
	if(pSocket == NULL)
	{
		LOG_CRI << "pSocket is NULL!";
		return false;
	}
	EHostType ePeerType = pSocket->GetPeerType();
	assert(ePeerType != eHostNone && ePeerType != eHostClient);
	UINT16 wUsrCnt = *(UINT16*)pBuf;
	UINT64* pUsrID = NULL;
	if(wUsrCnt != 0)
		pUsrID = (UINT64*)(pBuf + sizeof(UINT16));
	UINT32 dwIDLen = sizeof(UINT16) + sizeof(UINT64) * wUsrCnt;
	if(dwIDLen > dwLen)
	{
		LOG_CRI << "dwIDLen: " << dwIDLen << ", dwLen: " << dwLen;
		return false;
	}
	pBuf += dwIDLen;
	dwLen -= dwIDLen;
	UINT8 byProtID = *(UINT8*)pBuf;
	auto it = _mapID2Prot.find(byProtID);
	if(it == _mapID2Prot.end())
		return NetMgr.GetClientMgr().SendClt(pUsrID, wUsrCnt, pBuf, dwLen);
	return CSvrHandler::OnRecv(pBuf, dwLen);
}

CGateNetMgr& CGateNetMgr::Instance()
{
	static CGateNetMgr oNetMgr;
	return oNetMgr;
}

void CGateNetMgr::TimerCheck()
{
	CNetMgr::TimerCheck();
	g_Gate2CenterCommC.KeepAlive();
	g_Gate2GameCommC.SendSvr_KeepAlive(NULL, 0);
	g_Gate2DBCommC.Send_KeepAlive();
}

bool CGateNetMgr::InitNetMgr()
{
	_pClientMgr = new CClientMgr;
	if(_pClientMgr == NULL)
		return false;
	return AddSvrHandler(eHostClient, *_pClientMgr);
}

CGateSvrHandler* CGateNetMgr::CreateSvrHandler(EHostType ePeerType, bool bAccept)
{
	return new CGateSvrHandler(ePeerType, _oSessionMgr);
}
