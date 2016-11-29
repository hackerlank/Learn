/********************************************************************
//	Center Server Source File.
//	File name:	Config.cpp
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
#ifdef _WIN32
#include "resource.h"
#include "CenterServerDlg.h"
#endif
#include "tinyxml.h"
#include "SvrInfo.h"
#include "Protocols.h"
#include "Parameter.h"
#include "TimePointMgr.h"
#include "SystemMail.h"
#include "ResidentDataMgr.h"
#include "ArenaManager.h"
#include "CenterGameVar.h"
#include "GuildMgr.h"
#include "TeamMananger.h"
#include "DemonTowerMgr.h"
#include "UDPLog.h"
#include "RankMgr.h"
#include "TripodMgr.h"
#include "TripodManager.h"
#include "ExpMgr.h"
#include "VIPMgr.h"
#include "WonderActivityMgr.h"
#include "RetainMgr.h"
#include "Memcached.h"
#include "PrepaidManager.h"
#include "DCWorker.h"
#include "Answer.h"
#include "ShipManager.h"
#include "DragonBallActMgr.h"
#include "CenterDataMgr.h"
#include "InvitedFriendMgr.h"
#include "GuildXiheManager.h"
#include "TimerPriceManager.h"
#include "DayActivityMgr.h"
#include "GodMonsterMgr.h"
#include "ActivityMgr.h"
#include "SevenConsumeActMgr.h"
#include "NameCheckMgr.h"

static CGUIDMgr g_GUIDMgr;

void FunLoadGuidSuc()
{
    Config.SetInited(eDBInitGUID);
}
CCenterConfig& CCenterConfig::Instance()
{
    static CCenterConfig config(CCenterNetMgr::Instance());
    return config;
}

void CCenterConfig::OnDBInited()
{
    if(!g_GUIDMgr.LoadGUID())
    {
        LOG_CRI << "LoadGUIDForCenterServer fails!";
        return;
    }
    //请求斗剑信息
    CArenaManager::LoadFromDB();
    g_CenterGameVar.LoadFromDB();
    //请求所有九疑鼎信息
    TripodManager.LoadTripodFromDB();
    //请求所有玩家ID和名字
    g_PHPProtS.LoadFromDB();
    //请求所有公告
    g_PHPProtS.LoadNoticeFromDB();
    //请求玩家等级信息
    g_WonderActivityMgr.LoadRoleLevelData();
    //请求天元神兽玩家信息
    g_GodMonsterMgr.LoadFromDB();
    //精彩活动奖励信息
    g_WonderActivityMgr.LoadFromDB();
    //精彩活动保留玩家信息
    g_RetainMgr.LoadFromDB();
    //活动中心活动信息
    g_ActivityMgr.LoadFromDB();

    CGuildMgr::Instance().LoadFromDB();
    g_DemonTowerMgr.LoadFromDB();
    CRankMgr::Instance().LoadFromDB();
    g_Center2DBCommC.Send_GetPlatformParam();
    CPrepaidManager::Instance().LoadPrepaidFromDB();
    g_ShipManager.LoadFromDB();
    //请求所有羲和神车信息
    GuildXiheManager.LoadXiheFromDB();

    g_CenterDataMgr.InitDB();
}

string CCenterConfig::GetServerName(const string& name)
{
    return name + ".s" + NumberToString(_wGroup);
}

void CCenterConfig::SetInited(EDBInitType eType)
{
    LOG_INF << "SetInited: " << static_cast<UINT32>(eType) << ".";
    _setDBToBeInited.erase(eType);
    if (_setDBToBeInited.empty())
        _bDBDataInited = true;
    CheckServerIsReady();
}

bool CCenterConfig::IsSomeInited(EDBInitType eType) const
{
    auto it = _setDBToBeInited.find(eType);
    if (it == _setDBToBeInited.end())
        return true;
    else
        return false;

}

bool CCenterConfig::InitServer()
{
    if(!CTimerMgr::Instance().OpenAllTimer())
    {
        LOG_CRI << "CTimerMgr::OpenAllTimer fails!";
        return false;
    }
    g_DBQueryMgr.Init(g_DBProtC);
    g_LogQueryMgr.Init(g_LogDBProtC);
    if(!InitGateSvrInfo())
    {
        LOG_CRI << "InitGateSvrInfo fails!";
        return false;
    }
    if(!InitGame())
    {
        LOG_CRI << "InitGame fails!";
        return false;
    }

    if(!g_DayActivityMgr.Init())
    {
        LOG_CRI << "DayActivityMgr.Init fail!";
        return false;
    }

    CTimePointMgr::Start();

    initMemcache();
    return true;
}

void CCenterConfig::UnInitServer()
{
    UnInitGame();
}

/*void FinishLoadGuiD(UINT16 wGroup, UINT8 byIndex, EGUIDType eType, UINT64 qwCounter)
  {
  Config.SetInited(eDBInitGUID);
  }*/

bool CCenterConfig::InitGame()
{
    _setDBToBeInited.clear();
    for  (UINT8 byIndex = eDBInitNone; byIndex < eDBInitMax; ++byIndex)
    {
        _setDBToBeInited.insert(static_cast<EDBInitType>(byIndex));
    }
    _setDBToBeInited.erase(eDBInitNone);

    vector<EGUIDType> vecType;
    vecType.push_back(GUID_GUILD);
    vecType.push_back(GUID_MAIL);
    vecType.push_back(GUID_SHIP);
    g_GUIDMgr.Init(_wGroup, 0,FunLoadGuidSuc);
    if(!g_GUIDMgr.InitType(vecType, true))
    {
        LOG_CRI << "g_GUIDMgr.InitType fails!";
        return false;
    }
    if(!CSystemMail::Init())
    {
        LOG_CRI << "CSystemMail::Init() fails!";  
        return false;
    }
    if(!g_TeamManager.Init())
    {
        LOG_CRI << "g_TeamManager.Init() fails!";
        return false;
    }
    if (!g_ActivityMgr.Init())
    {
        LOG_CRI << "g_ActivityMgr Init fails!";
        return false;
    }
    if(!g_DemonTowerMgr.Init())
    {
        LOG_CRI << "g_DemonTowerMgr.Init() fails!"; 
        return false;
    }
    if(!CUDPLogMgr::Init())
    {
        LOG_CRI << "CUDPLogMgr::Init fails!";
        return false;
    }
    if(!CParamMgr::Init())
    {
        LOG_CRI << "CParamMgr::Init fails!";
        return false;
    }

    if (!CResidentDataMgr::Instance().Init())
    {
        LOG_CRI << "CResidentDataMgr::Init fails!";
        return false;
    }
    if (!AnswerMgr.Init())
    {
        LOG_CRI << "CAnswerMgr::Init fails!";
        return false;
    }
    LOG_CRI << "AnswerMgr::Init Suc!";
    if(!CTimePointMgr::Init())
    {
        LOG_CRI << "CTimePointMgr::Init fails!";
        return false;
    }
    if(!CArenaManager::Init())
    {
        LOG_CRI << "CArenaManager::Init fails!";
        return false;
    }
    if (!CGuildMgr::Instance().Init())
    {
        LOG_CRI << "CGuildMgr::Init fails!";
        return false;
    }
    if (!CRankMgr::Instance().Init())
    {
        LOG_CRI << "CGuildMgr::Init fails!";
        return false;
    }
    if (!g_GodMonsterMgr.Init())
    {
        LOG_CRI << "g_GodMonsterMgr Init fails!";
        return false;
    }
    if (!g_WonderActivityMgr.Init())
    {
        LOG_CRI << "g_WonderActivityMgr.Init fails!";
        return false;
    }
    if (!CTripodMgr::Init())
    {
        LOG_CRI << "CTripodMgr::Init fails!";
        return false;
    }
    LOG_INF << "CTripodMgr::Init OK!";
    if(!CExpMgr::Init())
    {
        LOG_CRI << "CExpMgr::Init fails!";
        return false;
    }
    LOG_INF << "CExpMgr::Init OK!";
    if(!VIPMgr.Init())
    {
        LOG_CRI << "CVIPMgr::Init fails!";
        return false;
    }
    LOG_INF << "CVIPMgr::Init OK!";
    if (!CDragonBallActMgr::Instance().Init())
    {
        LOG_CRI << "CDragonBallActMgr::Init fails!";
        return false;
    }

    if (!DC().Init())
    {
        LOG_CRI << "DCWorker Init Failed!";
        return false;
    }
    if(!g_ShipManager.Init())
    {
        LOG_CRI << "g_ShipManager Init Failed!";
        return false;
    }
    LOG_INF << "DCWorker Init OK!";

    if(!g_InvitedFriendMgr.InvitedFriendMgr_Init())
    {
        LOG_CRI <<"g_InvitedFriendMgr Init Failed!!";
        return false;
    }
    if(!g_TimesPriceManager.Init())
    {
        LOG_CRI <<"g_TimesPriceManager Init Failed!!";
        return false;
    }
    if(!CSevenConsumeActMgr::Instance().Init())
    {
        LOG_CRI <<"SevenConsumeActMgr Init Failed!!";
        return false;
    }
    if (!CNameCheckMgr::Init())
    {
        LOG_CRI << "CNameCheckMgr::Init() fails!";
        return false;
    }

    CGameVar::Register();
    return true;
}

void CCenterConfig::UnInitGame()
{
}

bool CCenterConfig::InitGateSvrInfo()
{
    auto itSvr = _oConfigInfo.mapSvr2Conf.find(eHostGate);
    if(itSvr == _oConfigInfo.mapSvr2Conf.end())
    {
        LOG_CRI << "Can't find GateServer Config!";
        return false;
    }
    auto& rMapConf = itSvr->second;
    for(auto itConf = rMapConf.begin(); itConf != rMapConf.end(); ++itConf)
    {
        UINT8 byIndex = itConf->first;
        SServerConfig& rConfig = itConf->second;
        SSvrInfo oSvrInfo;
        oSvrInfo.dwSvrID = ::GetServerID(_wGroup, eHostGate, byIndex);
        oSvrInfo.eHostType = eHostGate;
        oSvrInfo.wPort = rConfig.wListenPort;
        oSvrInfo.dwUsrCnt = 0;
        auto itHost = Config._oConfigInfo.mapHost2TypeAddr.find(rConfig.strHostName);
        auto& rMapType2Addr = itHost->second;
        for(auto itType = rMapType2Addr.begin(); itType != rMapType2Addr.end(); ++itType)
        {
            UINT8 byType = itType->first;
            string& strAddr = itType->second;
            oSvrInfo.mapType2Addr.insert(make_pair(byType, strAddr));
        }
        CSvrInfoMgr::AddSvrInfo(oSvrInfo);
    }
    return true;
}

void CCenterConfig::ReloadTable(const TVecString& vecTable)
{
    for(auto it = vecTable.begin();it != vecTable.end();it++)
    {
        bool bUpdate = true;
        if("DemonTower.xml" == *it)
        {
            bUpdate = g_DemonTowerMgr.ReloadTable();
        }
        else if("MessageSysMailBody.xml" == *it)
        {
            bUpdate =  CSystemMail::Init();
        }
        else if("Dungeon.xml"  == *it)
        {
            bUpdate =  g_TeamManager.Init();
        }
        else if("Arena.xml" == *it)
        {
            bUpdate =CArenaManager::ReloadTable(*it);
        }
        else if("ArenaConfig.xml" == *it)
        {
            bUpdate =CArenaManager::ReloadTable(*it);   
        }
        else if("Ladder.xml" == *it)
        {
            bUpdate =CArenaManager::ReloadTable(*it);
        }
        else if("GuildLevel.xml" == *it)
        {
            bUpdate = CGuildMgr::Instance().ReloadTable(*it);
        }
        else if("GuildBuilding.xml" == *it)
        {
            bUpdate = CGuildMgr::Instance().ReloadTable(*it);
        }
        else if("GuildTech.xml" == *it)
        {
            bUpdate = CGuildMgr::Instance().ReloadTable(*it);
        }
        else if("Parameter.xml" == *it)
        {
            bUpdate =  CParamMgr::Init();
        }
        else if("StoveFire.xml" == *it)
        {
            bUpdate = CTripodMgr::ReLoadConfig(*it);
        }
        else if("StoveFireLevel.xml" == *it)
        {
            bUpdate = CTripodMgr::ReLoadConfig(*it);
        }
        else if("StoveProp.xml" == *it)
        {
            bUpdate = CTripodMgr::ReLoadConfig(*it);
        }
        else if("StoveAttr.xml" == *it)
        {
            bUpdate = CTripodMgr::ReLoadConfig(*it);
        }
        else if("Exp.xml" == *it)
        {
            bUpdate = CExpMgr::ReLoadConfig(*it);
        }
        else if("VIPMgr.xml" == *it)
        {
            bUpdate = VIPMgr.ReLoadConfig(*it);
        }
        else if("ActivityOperating.xml" == *it)
        {
            bUpdate = g_WonderActivityMgr.ReLoadConfig(*it);
        }
        else if("ActivityOperatingConfig.xml" == *it)
        {
            bUpdate = g_WonderActivityMgr.ReLoadConfig(*it);
        }
        else if("DragonBall.xml" == *it)
        {
            bUpdate = CDragonBallActMgr::Instance().ReLoadConfig(*it);
        }
        else if("SevenConsume.xml" == *it)
        {
            bUpdate = CSevenConsumeActMgr::Instance().ReLoadConfig(*it);
        }
        else
        {
            bUpdate = false;
        }

        if(bUpdate)
            LOG_CRI << "Reload table " <<*it<<" Suc";
        else
            LOG_CRI << "Reload table " <<*it<<" Error";
    }
}

UINT32 CCenterConfig::GetSvrID()
{
    UINT8 idx = DEFAULT_GAME_SVR;
    return ::GetServerID(_wGroup, eHostGame, idx);
}
bool CCenterConfig::AllServerIsReady()
{
    return _bAllGameSvrInited && _bDBDataInited && _bInited;
}
void CCenterConfig::CheckServerIsReady()
{
    if(AllServerIsReady())
    {
        LOG_INF << "All Server is Ready";
        if (!_bLastInited)
        {
            _bLastInited = true;
            OnAllServerReady();
        }
    }
}

void CCenterConfig::OnAllServerReady()
{
    UINT32 dwID = GetSvrID();
    g_Game2CenterGuildBattleS.SendSvr_ReadyToSendNewGuildBattle(&dwID, 1);
}

