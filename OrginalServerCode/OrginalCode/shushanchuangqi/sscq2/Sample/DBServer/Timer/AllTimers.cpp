/********************************************************************
//	Database Server Source File.
//	File name:	AllTimers.cpp
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

#include "AllTimers.h"

#include "stdafx.h"
#include "../DBRoleMgr.h"
#include "../DBRoleData.h"
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

void COneSecTimer::OnTimer()
{
	time_t tNow = time(NULL);
	Config.TimerCheckInit();
    CDBRoleMgr::Instance().TimerCheck(tNow);
    g_CDBTotalArenaManager.DumpToDB();
    g_CDBTotalShipManager.DumpToDB();
    g_CDBTotalGameVarsManager.DumpToDB();
    g_CDBTripodTableManager.DumpToDB();
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
    g_CDBTotalLadderRobotManager.DumpToDB();
}

void CFiveSecTimer::OnTimer()
{
	NetMgr.TimerCheck();
    /*CDBRoleMgr::Instance().CreateRole(10000,"test",[this](SDBRoleData* pData, ERoleResult result)
            {
            printf("create role is ok");
            
            });*/
            /*RoleBaseInfo info;
            info.qwRoleId =10000;
            info.strName ="test";
            info.byLevel = 2;
            string strData;
            COutArchive iar(strData);
            iar << info;
            CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(10000,eTypeRoleBaseInfo,eOpUpdate,strData);
           RoleItemInfo info;
           info.qwRoleId =10000;
           info.qwItemId =20000;
           info.dwItemType =100;
           string strData;
           COutArchive iar(strData);
           iar << info;
           CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(10000,eTypeItemInfo,eOpAdd,strData);
           
           RoleItemInfo info;
           info.qwRoleId =10000;
           info.qwItemId =20000;
           info.dwItemType =101;
           string strData;
           COutArchive iar(strData);
           iar << info;
           CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(10000,eTypeItemInfo,eOpUpdate,strData);
         
           RoleItemInfo info;

           info.qwRoleId =10000;
           info.qwItemId =20000;
           info.dwItemType =101;
           string strData;
           COutArchive iar(strData);
           iar << info;
           CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(10000,eTypeItemInfo,eOpDel,strData);*/
           /*CDBRoleMgr::Instance().OnRecv_LoadRoleData(10000)*/;
          /* CDBRoleMgr::Instance().CreateRole(20000,"xtest",[this](SDBRoleData* pData, ERoleResult result)
            {
            printf("create role is ok");
            
            });*/
           /* RoleBaseInfo info;
            info.qwRoleId =20000;
            info.strName ="xtest";
            info.byLevel = 2;
            string strData;
            COutArchive iar(strData);
            iar << info;
            CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(20000,eTypeRoleBaseInfo,eOpUpdate,strData);
            
           RoleItemInfo info;
           info.qwRoleId =20000;
           info.qwItemId =20000;
           info.dwItemType =100;
           string strData;
           COutArchive iar(strData);
           iar << info;
           CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(20000,eTypeItemInfo,eOpAdd,strData);
          
           RoleItemInfo info;
           info.qwRoleId =20000;
           info.qwItemId =20000;
           info.dwItemType =101;
           string strData;
           COutArchive iar(strData);
           iar << info;
           CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(20000,eTypeItemInfo,eOpUpdate,strData);
                     
           RoleItemInfo info;

           info.qwRoleId =20000;
           info.qwItemId =20000;
           info.dwItemType =101;
           string strData;
           COutArchive iar(strData);
           iar << info;
           CDBRoleMgr::Instance().OnRecv_RoleDataUpdate(20000,eTypeItemInfo,eOpDel,strData);
           CDBRoleMgr::Instance().OnRecv_LoadRoleData(20000);*/
/*           
NameVector tempvector ;
TableNamePair temppair;
temppair.SelfName ="byLevel";
temppair.DBName ="Level";
temppair.DataType="UINT16";
tempvector.push_back(temppair);
struct Data
{
    UINT16 byLevel;

} ;
Data testData;
testData.byLevel =5;
CreateInsertString("TestTable",tempvector,testData);*/
}

void CTenSecTimer::OnTimer()
{
	time_t tNow = time(NULL);
	NetMgr.GetSessionMgr().TimerCheck(tNow);
	CUsrSessMgr::Instance().TimerCheck(tNow);
    CDBMgr::Instance().PrintListLength();
}

///////////////////////////////////////////////////////////////////////////////////

bool CTimerMgr::OpenAllTimer()
{
	if(!NetInterface::OpenTimer(_oOneSecTimer, 1000))
		return false;
	if(!NetInterface::OpenTimer(_oFiveSecTimer, 5 * 1000))
		return false;
	if(!NetInterface::OpenTimer(_oTenSecTimer, 10 * 1000))
		return false;
	return NetInterface::StartTimer();
}

