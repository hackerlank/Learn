/********************************************************************
//	Game Server Source File.
//	File name:	NetMgr.cpp
//	Created:	2011/05/30	10:00
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

#include "GameNetMgr.h"

#include "stdafx.h"
#include "Protocols.h"
#include "PathFinder.h"
#include "UserMgr.h"
#include "Player.h"
#include "Battle.h"
#include "ServerID.h"

CGameSvrHandler g_GameSvrHandlerC2S(true, NetMgr.GetSessionMgr());
CGameSvrHandler g_GameSvrHandlerS2C(false, NetMgr.GetSessionMgr());

bool CGameSvrHandler::Send(const char* pBuf, UINT32 dwLen)
{
	ESyncKey eSyncKey = eSyncNone;
	if(_bIsC2S)
		eSyncKey = eSyncGameSvrC2S;
	else
		eSyncKey = eSyncGameSvrS2C;
	string strPkg(pBuf, dwLen);
	if(Config._bIsCrossServer)
	{
		ISocket* pSocket = GetCurSock();
		assert(pSocket != NULL && pSocket->GetPeerType() == eHostCenter);
		return pSocket->Send(g_Game2CenterCommC.BuildPkg_GameSvrDataSyncReq(eSyncKey, _wSrcGroup, _bySrcIndex, TVecINT32(), strPkg));
	}
	else
	{
		return g_Game2CenterCommC.Send_GameSvrDataSyncReq(eSyncKey, _wSrcGroup, _bySrcIndex, TVecINT32(), strPkg);
	}
}

bool CGameSvrHandler::SendSvr(const UINT32* pSvrID, UINT8 bySvrCnt, const char* pBuf, UINT32 dwLen)
{
	bool bRet = true;
	for(UINT8 i = 0; i < bySvrCnt; ++i)
	{
		UINT32 dwSvrID = pSvrID[i];
		ESyncKey eSyncKey = eSyncNone;
		if(_bIsC2S)
			eSyncKey = eSyncGameSvrC2S;
		else
			eSyncKey = eSyncGameSvrS2C;
		string strPkg(pBuf, dwLen);
		UINT16 wGroup = GetServerGroup(dwSvrID);
		UINT8 byGameSvrIndex = GetServerIndex(dwSvrID);
		if(Config._bIsCrossServer)
		{
			UINT32 dwCenterSvrID = GetServerID(wGroup, eHostCenter, 1);
			bRet = g_Game2CenterCommC.SendSvr_GameSvrDataSyncReq(&dwCenterSvrID, 1, eSyncKey, wGroup, byGameSvrIndex, TVecINT32(), strPkg) && bRet;
		}
		else
		{
			bRet = g_Game2CenterCommC.Send_GameSvrDataSyncReq(eSyncKey, wGroup, byGameSvrIndex, TVecINT32(), strPkg) && bRet;
		}
	}
	return bRet;
}

UINT32 CGameSvrHandler::GetCurSvrID() const
{
	assert(_bySrcIndex != 0);
	return GetServerID(_wSrcGroup, eHostGame, _bySrcIndex);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

CGameNetMgr& CGameNetMgr::Instance()
{
	static CGameNetMgr oNetMgr;
	return oNetMgr;
}

void CGameNetMgr::TimerCheck()
{
	CNetMgr::TimerCheck();
	g_Game2CenterCommC.SendSvr_KeepAlive(NULL, 0);
	g_Game2DBCommC.SendSvr_KeepAlive(NULL, 0);
	g_LogEvent.Send_KeepAlive();
}

void CGameNetMgr::OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID)
{
	CNetMgr::OnRecvFail(qwUsrID, byProtID, byFuncID);
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(pUser != NULL)
		pUser->OnRecvFail();
}

bool CGameNetMgr::OnUserLogic()
{
	UINT32 dwStartTick = GetTickCount();
	bool bBusy = CPathFindMgr::Instance().ProcessResult();
    ProcessBattleReportResult();
	UINT32 dwDiffTick = GetTickCount() - dwStartTick;
	if(dwDiffTick > FRAME_OVERTIME_LIMIT)
		LNF_CRI << "UserLogicFunc Overtime: " << dwDiffTick;
	return bBusy;
}

bool CGameNetMgr::GetCurUser(CUserPtr* ppUser /*= NULL*/, CPlayerPtr* ppPlayer /*= NULL*/, CGameMapPtr* ppMap /*= NULL*/)
{
	UINT64 qwUsrID = GetCurUsrID(); // XXX: 网关过来的消息，能知道是哪一个玩家的
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(pUser == NULL)
	{
		LOG_CRI << "Can't find user! UserID: " << qwUsrID;
		PRINT_CALL_STACK_DEBUG;
		return false;
	}
	CPlayerPtr pPlayer = pUser->GetPlayer();
	if(pPlayer == NULL)
	{
		LOG_DBG << "User has no active player! UserID: " << qwUsrID;
		PRINT_CALL_STACK_DEBUG;
		return false;
	}
	if(ppUser != NULL)
		*ppUser = pUser;
	if(ppPlayer != NULL)
		*ppPlayer = pPlayer;
	if(ppMap != NULL)
	{
		CGameMapPtr pMap = pPlayer->GetMap();
		if(pMap == NULL)
		{
			LOG_CRI << "Player is not on map! RoleID: " << pPlayer->GetRoleID();
			PRINT_CALL_STACK_DEBUG;
			return false;
		}
		*ppMap = pMap;
	}
	return true;
}

bool CGameNetMgr::OnException(EExceptType eExceptType)
{
	UINT64 qwUsrID = GetCurUsrID();
	if(qwUsrID != 0)
	{
		CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
		CPlayerPtr pPlayer;
		if(pUser != NULL && (pPlayer = pUser->GetPlayer()) != NULL)
			LOG_WRN << "Kick User: " << qwUsrID << ", Player: " << pPlayer->GetLocaleName() << " offline! eExceptType: " << eExceptType << LOGCTL_FLUSH;
		else
			LOG_WRN << "Kick User: " << qwUsrID << " offline! eExceptType: " << eExceptType << LOGCTL_FLUSH;
		CUserMgr::AddExceptUser(qwUsrID);
		CUserMgr::KickUserOffLine(qwUsrID, true);
		CUserMgr::OnUserLeave(qwUsrID, eLeaveKick);
	}
	return true;
}
void CGameNetMgr::OnGateClosed( ISocket& rSocket ) 
{
}
void CGameNetMgr::OnCenterClosed( ISocket& rSocket ) 
{
}
void CGameNetMgr::OnDBClosed( ISocket& rSocket ) 
{
}
void CGameNetMgr::OnLoggerClosed( ISocket& rSocket ) 
{
}
void CGameNetMgr::OnLoginClosed( ISocket& rSocket ) 
{
}

