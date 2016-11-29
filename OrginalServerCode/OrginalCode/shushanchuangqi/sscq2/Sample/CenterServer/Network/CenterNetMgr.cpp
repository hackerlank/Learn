/********************************************************************
//	Center Server Source File.
//	File name:	NetMgr.cpp
//	Created:	2011/06/06	10:00
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
#include "ServerDefine.h"
#include "Protocols.h"
#include "UserMgr.h"

CCenterNetMgr& CCenterNetMgr::Instance()
{
	static CCenterNetMgr oNetMgr;
	return oNetMgr;
}

void CCenterNetMgr::TimerCheck()
{
	CNetMgr::TimerCheck();
	g_Center2DBCommC.Send_KeepAlive();
	g_LogEvent.Send_KeepAlive();
}

void CCenterNetMgr::OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID)
{
	CNetMgr::OnRecvFail(qwUsrID, byProtID, byFuncID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(pUser != NULL)
		pUser->OnRecvFail();
}

bool CCenterNetMgr::OnException(EExceptType eExceptType)
{
	UINT64 qwUsrID = GetCurUsrID();
	if(qwUsrID != 0)
	{
		LOG_WRN << "Kick User: " << qwUsrID << " offline! eExceptType: " << eExceptType << LOGCTL_FLUSH;
		CUserMgr::AddExceptUser(qwUsrID);
		CUserMgr::KickUserOffLine(qwUsrID, true);
		CUserMgr::RemoveUser(qwUsrID);
	}
	return true;
}

bool CCenterNetMgr::GetCurUser(CUserPtr* ppUser)
{
    if (!ppUser)
        return false;
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if (!pUser)
        return false;
    *ppUser = pUser;
    return true;
}

void CCenterNetMgr::OnGateClosed( ISocket& rSocket ) 
{
}
void CCenterNetMgr::OnGameClosed( ISocket& rSocket ) 
{
}
void CCenterNetMgr::OnDBClosed( ISocket& rSocket ) 
{
}
void CCenterNetMgr::OnLoggerClosed( ISocket& rSocket )
{
}
void CCenterNetMgr::OnLoginClosed( ISocket& rSocket ) 
{
}

