/********************************************************************
//	Database Server Source File.
//	File name:	Config.h
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

#pragma once
#include "Config.h"
#ifdef _WIN32
class CDBServerDlg;
#endif
#define OPEN_SQL_LOG
#if defined(OPEN_SQL_LOG)
//#define LOG_SQL CLogObj(g_SQLLog)
 #define LOG_SQL CLogObj(g_SQLLog)<<THIS_FILE<<":"<< __LINE__ <<":"
#else
    #define LOG_SQL CNulLog::_sNulLog
#endif
extern CLog g_SQLLog;
class CNetMgr;
class TiXmlElement;
enum EPreLoad
{
    eLoadName ,//加载名字
    eLoadDemonTower,
    eLoadMallDiscount,
    eLoadWonderPrize,
    eLoadWonderPrizeLevel,
    eLoadWonderPrizeTrump,
    eLoadWonderPrizeFighter,
    eLoadWonderPrizeFormation,
    eLoadWonderPrizeDungon,
    eLoadWonderPrizeBeauty,
    eLoadWonderPrizeHorse,
    eLoadRetain,
    eLoadGodMonster,
    eLoadLimitPrize,
    eLoadActivity,
    eLoadBoss,
    eLoadCenterData,
    eLoadMax,//最大值
};

class CDBConfig : public CConfig
{
    friend class CRequestHandler;
    public:
    static CDBConfig& Instance();
    CDBConfig(CNetMgr& rNetMgr); 
    virtual void OnConnect(ISocket& rSocket, bool bSucceed);
    virtual void OnClose(ISocket& rSocket);
    virtual bool OnAccept(ISocket& rSocket);
    virtual bool InitServerConfig(TiXmlElement* pServer);
    UINT32 GetSvrIDByMapID(UINT16 wMapID);
    bool IsPreLoad();
    void SetPreLoad(EPreLoad eLoad);

    private:
    virtual bool InitServer();
    virtual void UnInitServer();
    private:
    map<UINT16, UINT8> _mapID2GameSvrIdx;
    private:
    set<EPreLoad> _preLoad;

};

#define Config CDBConfig::Instance()

