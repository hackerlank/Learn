/********************************************************************
//	Database Server Source File.
//	File name:	NetMgr.cpp
//	Created:	2011/06/03	15:00
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
#include "DBArenaManger.h"
#include "DBShipManger.h"
#include "DBGameVarsMananger.h"
#include "DBDemonTower.h"
#include "DBGuildMgr.h"
#include "DBPubGuildMgr.h"
#include "DBRoleRankMgr.h"
#include "DBTripodTable.h"
#include "DBTripodHelpTable.h"
#include "DBTripodLogTable.h"
#include "DBMallDiscount.h"
#include "DBWonderPrizeTable.h"
#include "DBWonderRetainTable.h"
#include "DBShipManger.h"
#include "DBCenterDataTable.h"
#include "DBGuildXiheTable.h"
#include "DBRoleGodMonsterTable.h"
#include "DBRoleLimitPrizeTable.h"
#include "DBActivityCenterDBTable.h"
#include "DBLadderRobotManger.h"
#include "DBRoleMgr.h"

void CDBNetMgr::TimerCheck()
{
	CNetMgr::TimerCheck();
	g_LogEvent.Send_KeepAlive();
}

bool CDBNetMgr::OnUserLogic()
{
	bool bBusy = CDBMgr::Instance().ProcessResult();
	return bBusy;
}

void CDBNetMgr::OnRecvFail(UINT64 qwUsrID, UINT8 byProtID, UINT8 byFuncID)
{
	CNetMgr::OnRecvFail(qwUsrID, byProtID, byFuncID);
}

void CDBNetMgr::OnUserLogicExit()
{
    CDBRoleMgr::Instance().SavePlayer(true);
    g_CDBTotalArenaManager.DumpToDB(true);
    g_CDBTotalShipManager.DumpToDB();
    g_CDBTotalGameVarsManager.DumpToDB();
    g_CDBTripodTableManager.DumpToDB(true);
    g_CDBTripodHelpTableManager.DumpToDB();
    g_CDBTripodLogTableManager.DumpToDB();
    g_CDBMallDiscountManager.DumpToDB();
    g_CDBGuildXiheManager.DumpToDB();
    CDBDemonTowerPlayerManager::Instance().DumpToDB();
    CDBWonderPrizeTableManager::Instance().DumpToDB();
    CDBWonderRetainTableManager::Instance().DumpToDB();
    CDBRoleGodMonsterTableManager::Instance().DumpToDB();
    CDBRoleLimitPrizeTableManager::Instance().DumpToDB();
    CDBActivityCenterTableManager::Instance().DumpToDB();
    CDBCenterDataDBTableManager::Instance().DumpToDB();
    CDBGuildMgr::Instance().SaveGuild(true);
    CDBPubGuildMgr::Instance().SavePubGuild(true);
    CDBRoleRankMgr::Instance().SaveRank(true);
    CDBRoleRankMgr::Instance().SaveAdore(true);
    g_CDBTotalLadderRobotManager.DumpToDB(true);
    
    LOG_CRI << "CDBNetMgr::OnUserLogicExit()";
}

void CDBNetMgr::OnGateClosed( ISocket& rSocket )
{
    UINT32 dwGateID = static_cast<UINT32>(rSocket.GetPeerID());
    CDBRoleMgr::Instance().GateOff(dwGateID);
}

void CDBNetMgr::OnCenterClosed( ISocket& rSocket )
{
}

void CDBNetMgr::OnGameClosed( ISocket& rSocket )
{
}

void CDBNetMgr::OnLoggerClosed( ISocket& rSocket )
{
}

void CDBNetMgr::OnLoginClosed( ISocket& rSocket )
{
}

