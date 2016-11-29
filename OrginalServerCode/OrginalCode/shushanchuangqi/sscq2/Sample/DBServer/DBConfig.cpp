/********************************************************************
//	Database Server Source File.
//	File name:	Config.cpp
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
#ifdef _WIN32
#include "resource.h"
#include "DBServerDlg.h"
#endif
#include "tinyxml.h"
#include "InvalidUserMgr.h"
#include "DBRoleNameManager.h"
#include "DBDemonTower.h"
#include "Parameter.h"
#include "DBBossMgr.h"
#include "DBMallDiscount.h"
#include "DBWonderPrizeTable.h"
#include "DBWonderRetainTable.h"
#include "DBCenterDataTable.h"
#include "DBRoleGodMonsterTable.h"
#include "DBRoleLimitPrizeTable.h"
#include "DBActivityCenterDBTable.h"

#include "NameCheckMgr.h"
#ifndef DEFAULT_GAME_SVR
#define DEFAULT_GAME_SVR 1
#endif
#ifndef DEFAULT_MAP
#define DEFAULT_MAP 1
#endif

CLog g_SQLLog;
/*static CDBGUIDMgr g_GUIDMgr;*/

CDBConfig& CDBConfig::Instance()
{
    static CDBConfig config(CDBNetMgr::Instance());
    return config;
}

bool CDBConfig::InitServer()
{
    // XXX: 无效果，直接使用前端传过来的roleid
#if 0
    g_GUIDMgr.Init(_wGroup, 0);
    vector<EGUIDType> vecType;
    vecType.push_back(GUID_ROLE);
    if(!g_GUIDMgr.InitType(vecType, true))
    {
        LOG_CRI << "g_GUIDMgr.InitType fails!";
        return false;
    }
#endif

    if(!CTimerMgr::Instance().OpenAllTimer())
    {
        LOG_CRI << "CTimerMgr::OpenAllTimer fails!";
        return false;
    }

    if(!CDBMgr::Instance().Init())
    {
        LOG_CRI << "CDBMgr::Init fails!";
        return false;
    }

    
    // FIXME: 这里没获取是否合服
    if (!RoleNameManager::Instance().Init(false,[this](INT8 byRet,UINT32 resSize){
                if(byRet == 0)
                {
                SetPreLoad(eLoadName);
                }
                LOG_INF << "Load Name is :"<<resSize;
                }))
    {
        LOG_CRI << "RoleNameManager::Init fails!";
        return false;
    }
    if(!CParamMgr::Init())
    {
        LOG_CRI << "CParamMgr::Init fails!";
        return false;
    }
    if (!CNameCheckMgr::Init())
    {
        LOG_CRI << "CNameCheckMgr::Init() fails!";
        return false;
    }

    //加载镇妖塔数据
    CDBDemonTowerPlayerManager::Instance().QueryData();
    g_CDBMallDiscountManager.QueryData();

    //加载精彩活动数据
    CDBWonderPrizeTableManager::Instance().QueryData();
    CDBWonderPrizeTableManager::Instance().QueryLevelData();
    CDBWonderPrizeTableManager::Instance().QueryTrumpData();
    CDBWonderPrizeTableManager::Instance().QueryFighterData();
    CDBWonderPrizeTableManager::Instance().QueryFormationData();
    CDBWonderPrizeTableManager::Instance().QueryDungonData();
    CDBWonderPrizeTableManager::Instance().QueryBeautyData();
    CDBWonderPrizeTableManager::Instance().QueryHorseData();
    CDBWonderRetainTableManager::Instance().QueryData();

    //天元神兽数据
    CDBRoleGodMonsterTableManager::Instance().QueryData();
    CDBRoleLimitPrizeTableManager::Instance().QueryData();
    //加载活动中心数据
    CDBActivityCenterTableManager::Instance().QueryData();

    //世界boss加载数据
    CDBBossMgr::Instance().Init();
    //美女日志
    CDBCenterDataDBTableManager::Instance().QueryData();

    //  while (m_bGetName == 0 );  
    // if (m_bGetName == 2)
    // {
    //  return false;
    //  }
    string strLogPath = Config._strCurDir + "/DBSQLLog";
    if(!CreateDirectory(strLogPath))
        return false;
    g_SQLLog.OpenConsole();
    if(!g_SQLLog.OpenLog(strLogPath.c_str(), "SQLLog"))
    {
        LOG_CRI << "OpenSQLLog fails! Path: " << strLogPath;
        return false;
    }
    return g_SQLLog.Start();
}

void CDBConfig::UnInitServer()
{
    g_SQLLog.Stop();
    /* CDBMgr::Instance().Stop();*/
}
/*
   static void OnDBSaveGUID(UINT16 wGroup, UINT8 byIndex, EGUIDType eType, UINT64 qwCounter)
   {
   mysqlpp::SQLQueryParms sqp;
   sqp << (mysqlpp::sql_smallint_unsigned)wGroup << (mysqlpp::sql_tinyint_unsigned)byIndex << (mysqlpp::sql_tinyint_unsigned)eType
   << (mysqlpp::sql_bigint_unsigned)qwCounter << (mysqlpp::sql_bigint_unsigned)qwCounter;
   CBaseDBMgr::Instance().DoModifyQuery("INSERT INTO tblmaxid VALUES(%0, %1, %2, %3) ON DUPLICATE KEY UPDATE Counter = %4;",
   &sqp, [eType](INT8 byRet, mysqlpp::SimpleResult& rSimpResult){
   if(byRet != 0)
   g_GUIDMgr.OnSaveFail(eType);
   });
   }

   bool CDBGUIDMgr::InitType(const vector<EGUIDType>& vecType, bool bSave)
   {
   if(!CGUIDMgr::InitType(vecType, bSave))
   return false;
   for(EGUIDType eType : vecType)
   {
   SGUIDInfoPtr& pGUIDInfo = _arGUIDInfo[eType];
   assert(pGUIDInfo != NULL);
   if(bSave)
   pGUIDInfo->fnSaveGUID = OnDBSaveGUID;
   }
   return true;
   }

   void CDBGUIDMgr::LoadGUID(mysqlpp::Query& query)
   {
   query << "SELECT Type, Counter FROM tblmaxid WHERE Grp = " << _wGroup << " AND Idx = 0;";
   mysqlpp::StoreQueryResult dataRes = query.store();
   for(size_t i = 0; i < dataRes.num_rows(); ++i)
   {
   mysqlpp::Row& rRow = dataRes[i];
   EGUIDType eType = (EGUIDType)(UINT8)rRow["Type"];
   UINT64 qwCounter = rRow["Counter"];
   if(eType == GUID_ROLE)
   InitCounter(eType, qwCounter);
   }
   _bLoaded = true;
   }

   void CDBMgr::InitData(mysqlpp::Query& query)
   {
   g_GUIDMgr.LoadGUID(query);
   }
   */
void CDBConfig::OnConnect(ISocket& rSocket, bool bSucceed)
{
    CConfig::OnConnect(rSocket,bSucceed);
    UINT32 dwConnectID = static_cast<UINT32>(rSocket.GetPeerID());
    UINT8  byResult = bSucceed ? 1: 0;
    switch (rSocket.GetPeerType())
    {
        case eHostGame:
            LOG_INF <<"GameServer Connect:"<<dwConnectID<<":"<< byResult;
            break;
        default:
            break;
    }
}
void CDBConfig::OnClose(ISocket& rSocket)
{
    CConfig::OnClose(rSocket);
    UINT32 dwConnectID = static_cast<UINT32>(rSocket.GetPeerID());
    switch (rSocket.GetPeerType())
    {
        case eHostGame:
            LOG_INF <<"GameServer OnClose:"<<dwConnectID;
            break;
        default:
            break;
    }
}
bool CDBConfig::OnAccept(ISocket& rSocket)
{

    UINT32 dwConnectID = static_cast<UINT32>(rSocket.GetPeerID());
    switch (rSocket.GetPeerType())
    {
        case eHostGame:
            LOG_INF <<"GameServer OnAccept:"<<dwConnectID;
            break;
        default:
            break;
    }
    return  CConfig::OnAccept(rSocket);

}

bool CDBConfig::InitServerConfig(TiXmlElement* pServer)
{
    if (!pServer)
        return true;

    TiXmlElement* pElemMapConfig = pServer->FirstChildElement("MapConfig");
    if (!pElemMapConfig) // XXX: 全部放在DEFAULT_GAME_SVR上
        return true;

    const char* pConfig = pElemMapConfig->Attribute("config");
    if (!pConfig) // 全部放在DEFAULT_GAME_SVR上
        return true;

    TiXmlDocument doc;
    if(!doc.LoadFile(pConfig, TIXML_ENCODING_UTF8))
        return true;

    TiXmlElement* pElemRoot = doc.RootElement();
    if(!pElemRoot)
        return true;

    TiXmlElement* pGameServer = pElemRoot->FirstChildElement("GameServer");
    if (!pGameServer)
        return false;
    while (pGameServer)
    {
        UINT16 mapId = DEFAULT_MAP;
        UINT8 svrIdx = DEFAULT_GAME_SVR;

        const char* pIdx = pGameServer->Attribute("index");
        if (!pIdx)
            return false;

        svrIdx = (INT8)atoi(pIdx);
        if (!svrIdx)
            return false;

        TiXmlElement* pMap = pGameServer->FirstChildElement("Map");
        if (!pMap) // XXX: 全部在1上
            return true;

        while (pMap)
        {
            const char* pMapId = pMap->Attribute("id");
            if (!pMapId)
                return false;

            mapId = (UINT16)atoi(pMapId);
            if (!mapId)
                return false;

            _mapID2GameSvrIdx[mapId] = svrIdx;
            pMap = pMap->NextSiblingElement("Map");
        }

        pGameServer = pGameServer->NextSiblingElement("GameServer");
    }

    for(auto i : _mapID2GameSvrIdx)
    {
        LOG_CRI << "mapid: " << i.first << " svrid: " << i.second;
    }

    return true;
}

UINT32 CDBConfig::GetSvrIDByMapID(UINT16 wMapID)
{
    UINT8 idx = DEFAULT_GAME_SVR;
    auto i = _mapID2GameSvrIdx.find(wMapID);
    if (i != _mapID2GameSvrIdx.end())
        idx = i->second;
    return ::GetServerID(_wGroup, eHostGame, idx);
}

bool CDBConfig::IsPreLoad()
{
    return _preLoad.empty();
}
void CDBConfig::SetPreLoad(EPreLoad eLoad)
{
    LOG_INF << "Load " << int(eLoad) << "Suc";
    _preLoad.erase(eLoad);
    LOG_INF << "_preLoad " << _preLoad.size() << "Suc";
}

CDBConfig::CDBConfig(CNetMgr& rNetMgr) : CConfig(rNetMgr)
{
    for( size_t pos = 0; pos != eLoadMax;pos ++)
    {
        _preLoad.insert(static_cast<EPreLoad>(pos));
    }

}

