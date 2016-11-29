/* ********************************************************************
//	Game Server Source File.
//	File name:	Config.cpp
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

#include "stdafx.h"
#ifdef _WIN32
#include "resource.h"
#include "GameServerDlg.h"
#endif
#include "tinyxml.h"
#include "Protocols.h"
#include "PathFinder.h"
#include "NameCheckMgr.h"
#include "AllTimers.h"
#include "DBQueryMgr.h"
#include "MapMgr.h"
#include "UserMgr.h"
#include "TimePointMgr.h"
#include "ServiceDateMgr.h"
#include "Parameter.h"
#include "MoneyParam.h"
#include "NPCMgr.h"
#include "DungeonMgr.h"
#include "ItemMgr.h"
#include "GetCondMgr.h"
#include "VIPMgr.h"
#include "FighterMgr.h"
#include "MonsterMgr.h"
#include "Skill.h"
#include "TaskMgr.h"
#include "ExpMgr.h"
#include "GameServerSysMail.h"
#include "Loot.h"
#include "CittaMgr.h"
#include "GatherMgr.h"
#include "ObjCondMgr.h"
#include "TrumpMgr.h"
#include "GameVar.h"
#include "DemonTowerMgr.h"
#include "PlayerDgn.h"
#include "IconAppearManager.h"
#include "DgnCondManager.h"
#include "BlockerMgr.h"
#include "WorldBossMgr.h"
#include "ShushanBattleMgr.h"
#include "MapAreaManager.h"
#include "PassiveSkill.h"
#include "SkillAttr.h"
#include "HorseMgr.h"
#include "GroupTaskManager.h"
#include "YaMenTaskManager.h"
#include "BubbleMgr.h"
#include "ActivityManager.h"
#include "GameBuffManager.h"
#include "BattlePoint.h"
#include "GuildBattleConfig.h"
#include "NewGuildBattleConfig.h"
#include "NewGuildBattleMgr.h"
#include "DayActivityMgr.h"
#include "FoundationMgr.h"
#include "TitleManager.h"
#include "AchievementMgr.h"
#include "CollectionMgr.h"
#include "EventMgr.h"
#include "ActionBase.h"
#include "LangHuanBlessMgr.h"
#include "Battle.h"
#include "ExchangeShopMgr.h"
#include "YelloDiamondMgr.h"
#include "EnergyMgr.h"
#include "TripodMgr.h"
#include "WondActMgr.h"
#include "Mall.h"
#include "SignInManager.h"
#include "DayTargetMgr.h"
#include "TreasureHuntMgr.h"
#include "GuardEMeiMgr.h"
#include "CommonMgr.h"
#include "BattleArrayMgr.h"
#include "BeautyMgr.h"
#include "BoostMgr.h"
#include "TaskMarket.h"
#include "GatherMgr.h"
#include "HeroFighterTavern.h"
#include "DrawMgr.h"
#include "ZhanQiMgr.h"
#include "Lottery.h"
#include "ServerID.h"
#include "GUIDMgr.h"
#include "ManagerMonsterAI.h"
#include "AllTimers.h"
#include "GameNetMgr.h"
#include "ShengLingMgr.h"
#include "TimerPriceMgr.h"
#include "EquipTrumpMgr.h"
#include "EverydayRecharge.h"
#include "FeedBackMgr.h"

CGUIDMgr g_GUIDMgr;

CGameConfig& CGameConfig::Instance()
{
    static CGameConfig config(CGameNetMgr::Instance());
    return config;
}

// XXX: 这个函数在加载配置和网络初始化完成之后才执行
bool CGameConfig::InitServer()
{
    if (!InitScript())
    {
        LOG_CRI << "CGameConfig::InitScript fails!";
        return false;
    }


    if(!CTimerMgr::Instance().OpenAllTimer())
    {
        LOG_CRI << "CTimerMgr::OpenAllTimer fails!";
        return false;
    }
    g_DBQueryMgr.Init(g_DBProtC);
    g_LogQueryMgr.Init(g_LogDBProtC);
    if(!InitGame())
    {
        LOG_CRI << "InitGame fails!";
        return false;
    }
    if(!CPathFindMgr::Instance().Start())
    {
        LOG_CRI << "CPathFindMgr::Instance().Start() fails!";
        return false;
    }
    CTimePointMgr::Start();
    CGameVar::Register();
    return true;
}

bool CGameConfig::InitScript(int flag)
{
    if (!flag)
        flag = SCRIPT_TYPE_ALL;
    if (!_oScript.LoadMainFile(_strScripts+"/"+_strScriptMain, GetServerType(GetServerID()), flag))
    {
        LOG_CRI << "_oScript.LoadMainFile fails!";
        return false;
    }
    return true;
}

void CGameConfig::UnInitServer()
{
    UnInitGame();
    CPathFindMgr::Instance().Stop();
}

/*
   void CGameConfig::OnClose(ISocket& rSocket)
   {
   switch(rSocket.GetPeerType())
   {
   case eHostGate:
   if(Config._bIsCrossServer)
   {
   CGateHandler* pGateHandler = NetMgr.GetGateHandler();
   if(pGateHandler == NULL)
   break;
   auto& rMapUsr2Gate = pGateHandler->GetUserMap();
   for(auto it = rMapUsr2Gate.begin(); it != rMapUsr2Gate.end();)
   {
//UINT64 qwUsrID = it->first;
//UINT32 dwSvrID = it->second;
++it;
///if(rSocket.GetPeerID() == dwSvrID)
//CUserMgr::RemoveUser(qwUsrID);
}
}
break;
default:
break;
}
}
*/

static void OnGUIDLoaded()
{
    Config.SetInited(eDBInitGUID);
}

void CGameConfig::SetInited(EDBInitType eType)
{
    LOG_INF << "SetInited: " << static_cast<UINT32>(eType) << ".";
    _setDBToBeInited.erase(eType);
    if (_setDBToBeInited.empty())
    {
        if(!_bDBDataInited)
        {
            _bDBDataInited = true;
            if(_bAllConnect &&  _bInited )
            {
                LOG_INF << "Send _GameSvrInitNft()";
                g_Game2CenterCommC.Send_GameSvrInitNft(); 
            }
        }
    }
}

bool CGameConfig::InitGame()
{
    _setDBToBeInited.clear();
    for  (UINT8 byIndex = eDBInitNone; byIndex < eDBInitMax; ++byIndex)
    {
        _setDBToBeInited.insert(static_cast<EDBInitType>(byIndex));
    }
    _setDBToBeInited.erase(eDBInitNone);
    _setDBToBeInited.erase(eDBInitNewGuildBattle);

    CGUIDMgr::Instance().Init(_wGroup, _byIndex, OnGUIDLoaded);
    vector<EGUIDType> vecType;
    vecType.push_back(GUID_HERO);
    vecType.push_back(GUID_ITEM);
    vecType.push_back(GUID_EQUIP);
    vecType.push_back(GUID_MONSTER);
    vecType.push_back(GUID_NPC);
    vecType.push_back(GUID_DGN);
    vecType.push_back(GUID_BATTLE);

    if(!g_SkillAttrMgr.SkillAttrInit())
    {
        LOG_CRI<<"g_SkillAttr.SkillAttInit fails";
        return false;
    }

    if(!CExchangeShopMgr::ExchangeInit())
    {
        LOG_CRI<<"CExchangeShopMgr ExchangeInit fails!!";
        return false;
    }


    if(!CGUIDMgr::Instance().InitType(vecType, true))
    {
        LOG_CRI << "CGUIDMgr::Instance().InitType fails!";
        return false;
    }

    vecType.clear();
    if (!CSkillMgr::Instance().Init(_strConfigDir))
    {
        LOG_CRI << "CSkillMgr::Init fails!";
        return false;
    }
    LOG_INF << "CSkillMgr::Init OK!";

    if (!CPassiveSkillMgr::Instance().LoadConfig(_strConfigDir))
    {
        LOG_CRI << "CPassiveSkillMgr::Init fails!";
        return false;
    }
    LOG_INF << "CPassiveSkillMgr::Init OK!";

    if(!CGUIDMgr::Instance().InitType(vecType, false))
    {
        LOG_CRI << "CGUIDMgr::Instance().InitType fails!";
        return false;
    }
    LOG_INF << "CGUIDMgr::Instance().InitType OK!";
    if(!CServiceDateMgr::Init())
    {
        LOG_CRI << "ServiceDateMgr::Init fails!";
        return false;
    }
    LOG_INF << "ServiceDateMgr::Init OK!";
    if(!CNameCheckMgr::Init())
    {
        LOG_CRI << "CNameCheckMgr::Init fails!";
        return false;
    }
    LOG_INF << "CNameCheckMgr::Init OK!";
    if(!CTimePointMgr::Init())
    {
        LOG_CRI << "CTimePointMgr::Init fails!";
        return false;
    }
    LOG_INF << "CTimePointMgr::Init OK!";
    if(!CParamMgr::Init())
    {
        LOG_CRI << "CParameter::Init fails!";
        return false;
    }
    LOG_INF << "CParameter::Init OK!";
    if(!CMoneyParamMgr::Init())
    {
        LOG_CRI << "CMoneyParamMgr::Init fails!";
        return false;
    }
    LOG_INF << "CMoneyParamMgr::Init OK!";
    if(!CExpMgr::Init())
    {
        LOG_CRI << "CExpMgr::Init fails!";
        return false;
    }
    LOG_INF << "CExpMgr::Init OK!";
    if(!CUserMgr::Init())
    {
        LOG_CRI << "CUserMgr::Init fails!";
        return false;
    }
    LOG_INF << "CUserMgr::Init OK!";
    if(!CNpcMgr::Init())
    {
        LOG_CRI << "CNpcMgr::Init fails!";
        return false;
    }
    LOG_INF << "CNpcMgr::Init OK!";
    if (!CGatherMgr::Init())
    {
        LOG_INF << "CGatherMgr::Init fails!";
        return false;
    }
    LOG_INF << "CGatherMgr:: Init OK!";
    if (!CTaskMgr::Init())
    {
        LOG_CRI << "CTaskMgr::Init fails!";
        return false;
    }
    LOG_INF << "CTaskMgr::Init OK!";

    if (!CBlockerMgr::Init())
    {
        LOG_CRI << "CBlockerMgr::Init() fails!";
        return false;
    }
    LOG_INF << "CBlockerMgr::Init() OK!";

    if(!CMapMgr::Init())
    {
        LOG_CRI << "CMapMgr::Init fails!";
        return false;
    }
    LOG_INF << "CMapMgr::Init OK!";
    if(!CDungeonMgr::Init())
    {
        LOG_CRI << "CDungeonMgr::Init fails!";
        return false;
    }
    LOG_INF << "CDungeonMgr::Init OK!";
    if (!CItemMgr::Init())
    {
        LOG_CRI << "CItemMgr::Init fails!";
        return false;
    }
    LOG_INF << "CItemMgr::Init OK!";
    if (!CFighterMgr::Init())
    {
        LOG_CRI << "CFighterMgr::Init fails!";
        return false;
    }
    LOG_INF << "CFighterMgr::Init OK!";
    if (!CMonsterMgr::Init())
    {
        LOG_CRI << "CMonsterMgr::Init fails!";
        return false;
    }
    if (!g_WondActMgr.Init())
    {
        LOG_CRI << "CWondActMgr::Init fails!";
        return false;
    }
    LOG_INF << "CWondActMgr::Init OK!";
    if (!GameServerSysMail::Init())
    {
        LOG_CRI << "GameServerSysMail::Init fails!";
        return false;
    }
    LOG_INF << "GameServerSysMail::Init OK!";
    if(!LOOT.Init())
    {
        LOG_INF << "LOOT::Init fails!";
        return false;
    }
    LOG_INF << "LOOT::Init OK!";
    if (!CCittaMgr::Instance().Init())
    {
        LOG_INF << "CCittaMgr::Init fails!";
        return false;
    }
    LOG_INF << "CCittaMgr:: Init OK!";

    if (!CObjCondMgr::Init())
    {
        LOG_INF << "CObjCondMgr::Init fails!";
        return false;
    }
    LOG_INF << "CObjCondMgr:: Init OK!";

    if (!CTrumpMgr::Instance().Init())
    {
        LOG_INF << "CTrumpMgr::Init fails!";
        return false;
    }
    LOG_INF << "CTrumpMgr:: Init OK!";

    if (!CVIPMgr::Instance().Init())
    {
        LOG_CRI << "CVIPMgr::Init fails!";
        return false;
    }
    LOG_INF << "CVIPMgr::Init OK!";

    if (!CTreasureHuntMgr::Instance().Init())
    {
        LOG_CRI << "CTreasureHuntMgr::Init fails!";
        return false;
    }
    LOG_INF << "CTreasureHuntMgr::Init OK!";

    if (!CCommonMgr::Instance().Init())
    {
        LOG_CRI << "CCommonMgr::Init fails!";
        return false;
    }
    LOG_INF << "CCommonMgr::Init OK!";

    if (!g_DemonTowerMgr.Init())
    {
        LOG_CRI << "CDemonTowerMgr::Init fails!";
        return false;
    }
    LOG_INF << "CDemonTowerMgr::Init OK!";

    if (!CIconAppearMgr::Instance().Init())
    {
        LOG_CRI << "CIconAppearMgr::Instance().Init() fails!";
        return false;
    }
    LOG_INF << "CIconAppearMgr::Instance().Init() OK!";

    if (!g_CDgnCondManager.Init())
    {
        LOG_CRI << "g_CDgnCondManager.Init() fails!";
        return false;
    }
    LOG_INF << "g_CDgnCondManager.Init() OK!";

    if (!CWorldBossMgr::Instance().Init())
    {
        LOG_CRI << "CWorldBossMgr::Init() fails!";
        return false;
    }
    LOG_INF << "CWorldBossMgr::Init() OK!";
    if(!CLangHuanBlessMgr::Instance().Init())
    {
        LOG_INF << "CLangHuanBlessMgr::Init() fails";
        return false;
    }
    LOG_INF << "CLangHuanBlessMgr::Init() OK!";

    if(!TaskMarketMgr.Init())
    {
        LOG_INF << "CTaskMarketMgr::Init() fails";
        return false;
    }
    LOG_INF << "CTaskMarketMgr::Init() OK!";

    if(!CYelloDiamondMgr::Instance().Init())
    {
        LOG_INF << "CYelloDiamondMgr::Init() fails";
        return false;
    }
    LOG_INF << "CYelloDiamondMgr::Init() OK!";
    if (!CShushanBattleMgr::Instance().Init())
    {
        LOG_CRI << "CShushanBattleMgr::Init() fails!";
        return false;
    }
    LOG_INF << "CShushanBattleMgr::Init() OK!";

    if (!g_AreaManager.Init())
    {
        LOG_CRI << "g_AreaManager.Init() fails!";
        return false;
    }

    if(!CHorseMgr::HorseMgrInit())
    {
        LOG_CRI<<"CHorseMgr::HorseMgrInit() fails";
        return false;
    }
    if (!g_CGroupTaskManager.Init())
    {
        LOG_CRI << "g_CGroupTaskManager.Init() fails!";
        return false;
    }
    if (!g_CYaMenTaskManager.Init())
    {
        LOG_CRI << "g_CYaMenTaskManager.Init() fails!";
        return false;
    }
    if (!CBubbleMgr::Instance().Init())
    {
        LOG_CRI << "CBubbleMgr Init fails!";
        return false;
    }
    if (!g_CActivityManager.Init())
    {
        LOG_CRI << "g_CActivityManager Init fails!";
        return false;
    }
    if (!CGameBuffMgr::Instance().Init(_strConfigDir))
    {
        LOG_CRI << "CGameBuffMgr Init fails!";
        return false;
    }

    if (!BattlePointCalucator.Init())
    {
        LOG_CRI << "CBattlePointCalucator Init fails!";
        return false;
    }

    if (!g_CTitleManager.Init())
    {
        LOG_CRI << "!g_CTitleManager.Init() fails!";
        return false;
    }

    if (!g_Lottery.Init())
    {
        LOG_CRI << "!g_Lottery.Init() fails!";
        return false;
    }
    if(!CEventMgr::EventInit())
    {
        LOG_CRI<<"g_EventMgr.EventInit fails!";
        return false;
    }

    if(!CAchievementMgr::AchievementInit())
    {
        LOG_CRI<<"CAchievementMgr::AchievementInit()  fails!";
        return false;
    }

    if(!CCollectionMgr::CollectionInit())
    {
        LOG_CRI<<"CCollectionMgr::CollectionInit()  fails!";
        return false;
    }

    if(!CActionManager::Init())
    {
        LOG_CRI<<"CActionManager::Init() fails!";
        return false;
    }

    if(!CEnergyMgr::CEnergyMgr_Init())
    {
        LOG_CRI<<"CEnergyMgr::Init() fails!";
        return false;
    }

    if(!CDayTargetMgr::DayTargetInit())
    {
        return false;
    }

    if(!CTripodMgr::Init())
    {
        LOG_CRI<<"CTripodMgr::Init() fails!";
        return false;
    }
    LOG_INF << "CTripodMgr::Init OK!";

    if (!CGuardEMeiMgr::Instance().Init())
    {
        LOG_CRI << "CGuardEMeiMgr::Init fails!";
        return false;
    }
    LOG_INF << "CGuardEMeiMgr::Init OK!";


    //XXX keep this end
    if(!g_DayActivityMgr.Init())
    {
        LOG_CRI<<"g_DayActivityMgr.Init fail!";
        return false;
    }

    if (!CGuildBattleConfigMgr::Instance().Init())
    {
        LOG_CRI << "CGuildBattleConfigMgr Init fails!";
        return false;
    }
    if (!NNewGuildBattle::CConfigMgr::Instance().Init())
    {
        LOG_CRI << "CNewGuildBattleConfigMgr Init fails!";
        return false;
    }

    if(!CFoundationMgr::Instance().Init())
    {
        LOG_CRI << "CFoundationMgr Init fail!";
        return false;
    }

    if(!CEquipTrumpMgr::Instance().Init())
    {
        LOG_CRI << "CEquipTrumpMgr Init fail!";
        return false;
    }


    if(!CBattleArrayMgr::BattleArrayInit())
    {
        LOG_CRI<<"CBattleArrayMgr init fail!";
        return false;
    }

    if(!CBeautyMgr::BeautyInit())
    {
        LOG_CRI<<"CBeautyMgr init fail!";
        return false;
    }

    // XXX: 在所有条件需要的配置之后加载
    if (!CGetCondMgr::Instance().Init())
    {
        LOG_CRI << "CGetCondMgr::Init fails!";
        return false;
    }
    LOG_INF << "CGetCondMgr::Init OK!";

    if (!BattleInit(_strBattleReportDir, _strConfigDir))
    {
        LOG_CRI << "BattleInit fails!";
        return false;
    }

    if(!g_CSignInManager.Init())
    {
        LOG_CRI << "g_CSignInManager.Init() fails!";
        return false;
    }

    if(!g_ZhanQiMgr.ZhanQiInit())
    {
        LOG_CRI<<"g_ZhanQiMgr ZhanQiInit Fails!";
        return false;
    }

    if(!g_FeedBackMgr.FeedBackMgrInit())
    {
        LOG_CRI<<"FeedBackMgrInit Fails";
        return false;
    }

    if(!CBoostMgr::Instance().Init())
    {
        LOG_CRI << "CBoostMgr Init fails!";
        return false;
    }

    if (!CTavernMgr::Instance().Init())
    {
        LOG_CRI << "CTavernMgr Init fails!";
        return false;
    }

    if (!CDrawMgr::Instance().Init())
    {
        LOG_CRI << "CDrawMgr Init fails!";
        return false;
    }
    if (!g_ShengLingMgr.Init())
    {
        LOG_CRI << "g_ShengLingMgr Init fails!";
        return false;
    }
    if (!g_TimesPriceManager.Init())
    {
        LOG_CRI << "g_TimesPriceManager Init fails!";
    }
    if(!g_EveryDayRechargeMgr.Init())
    {
        LOG_CRI << "g_EveryDayRechargeMgr.Init() Err";
        return false;
    }

    LOG_INF << "==============GameServer Init finish==============";
    return true;
}

template<typename T>
void CheckPtrLeak()
{
#ifdef _DEBUG
    UINT32 dwOutCount = CObjectPool<T>::Instance().GetOutCount();
    if(dwOutCount > 0)
    {
        LOG_CRI << typeid(T).name() << " has leak!";
        //DebugBreak();
    }
#endif
}

static void CheckLeak()
{
    CheckPtrLeak<CGameMap>();
    CheckPtrLeak<CNpc>();
    CheckPtrLeak<CPlayer>();
    CheckPtrLeak<CUser>();
    CheckPtrLeak<CPlayerDgn>();
}

void CGameConfig::UnInitGame()
{
    CMapMgr::Destroy();
    CUserMgr::Destroy();
    CNpcMgr::Destroy();
    CDungeonMgr::Destroy();
    CGatherMgr::Destroy();
    g_DayActivityMgr.Destroy();
    g_MonsterAIManager.Destroy();
    CMonsterMgr::Destroy();
    LOG_CRI << "CGameConfig::UnInitGame()";
    CTimerMgr::Instance().CallMem();

    //  CScriptMgr::Destroy();
    CheckLeak();
}

bool CGameConfig::CheckMapInServer(UINT32 dwMapId)
{
    UINT8 idx = DEFAULT_GAME_SVR;
    auto i = _mapID2GameSvrIdx.find(dwMapId);
    if (i == _mapID2GameSvrIdx.end())
    {
        LOG_CRI << "Can not find map" <<dwMapId;
        return false;
    }
    idx = i->second;
    return idx == _byIndex;
}
bool CGameConfig::InitServerConfig(TiXmlElement* pServer)
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

void CGameConfig::ReloadTable(const TVecString& vecTable)
{
    string sRet;
    for(auto it = vecTable.begin();it != vecTable.end();it++)
    {
        LOG_CRI << "接收到的XML文件名字为：" << *it;
        bool  bUpdate = false;
        if(((*it).find("Task") != string::npos) && (string::npos != (*it).find_first_of("0123456789")))
        {
            bUpdate = CTaskMgr::ReloadConfig(*it);
        }else if("Parameter.xml" == *it)
        {
            bUpdate =  CParamMgr::Init(); 

        }else if("AchievementLevel.xml" == *it)
        {
            bUpdate = CAchievementMgr::ReLoadConfig(*it);

        }else if("Achievement.xml" == *it)
        {
            bUpdate = CAchievementMgr::ReLoadConfig(*it);
        }else if("ActivityPoint.xml" == *it)
        {
            bUpdate = g_CActivityManager.ReLoadConfig(*it);
        }else if("Daily_shimen.xml" == *it)
        {
            bUpdate = g_CGroupTaskManager.ReLoadConfig(*it);

        }else if("Daily_shimentask.xml" == *it)
        {
            bUpdate = g_CGroupTaskManager.ReLoadConfig(*it);
        }else if("Daily_shimentaskColor.xls" == *it)
        {
            bUpdate = g_CGroupTaskManager.ReLoadConfig(*it);
        }else if("StoveAttr.xls" == *it)
        {
            bUpdate = CTripodMgr::ReLoadConfig(*it);
        }else if("Collection.xml" == *it)
        {
            bUpdate = CCollectionMgr::ReLoadConfig(*it);

        }else if("CollectionLevel.xml" == *it)
        {
            bUpdate = CCollectionMgr::ReLoadConfig(*it);
        }else if("Citta.xml" == *it)
        {
            bUpdate = CCittaMgr::Instance().LoadConfig(*it);
        }else if("CittaSignet.xml" == *it)
        {
            bUpdate = CCittaMgr::Instance().LoadConfig(*it);

        }else if("CittaSignetSuit.xml" == *it)
        {
            bUpdate = CCittaMgr::Instance().LoadConfig(*it);

        }else if("CittaMerge.xml" == *it)
        {
            bUpdate = CCittaMgr::Instance().LoadConfig(*it);

        }else if("Bubble.xml" == *it)
        {
            bUpdate = CBubbleMgr::Instance().Init();

        }else if("Beast.xml" == *it                ||
                "Formation.xml" == *it             ||
                "FighterZuHe.xml" == *it           ||
                "FighterTaoism.xml" == *it         ||
                "FighterTalent.xml" == *it         ||
                "FighterTalentUpgrade.xml" == *it  ||
                "FighterStar.xml" == *it           ||
                "FighterStarGrowth.xml" == *it     ||
                "FighterRecruit.xml" == *it        ||
                "FighterProp.xml" == *it           ||
                "FighterLvAttr.xml" == *it         ||
                "FighterLevelUP.xml" == *it        ||
                "FighterInstinct.xml" == *it       ||
                "FighterFind.xml" == *it           ||
                "FighterCuiTi.xml" == *it          ||
                "DujieTemplate.xml" == *it         ||
                "PetLevel.xml" == *it              ||
                "Pet.xml" == *it                   
                )
        {
            bUpdate = CFighterMgr::LoadConfig(true);

        }else if("Barrier.xml" == *it)
        {
            bUpdate = CObjCondMgr::Init();

        }else if("BagCost.xml" == *it              || 
                "AttachSpirit.xml" == *it          ||
                "AttachSpiritLevelUp.xml" == *it   ||
                "ArmorUpgrade.xml" == *it          ||
                "Fashion.xml" == *it               ||
                "FashionAttr.xml" == *it           ||
                "DepotCost.xml" == *it             ||
                "Mall.xml" == *it                  ||
                "ChongZhi.xml" == *it              ||
                "Item.xml" == *it                  ||
                "ItemTime.xml" == *it              ||
                "ItemAttr.xml" == *it              ||
                "Intensify.xml" == *it              ||
                "ZodTrumpUP.xml" == *it)            
        {
            bUpdate = CItemMgr::LoadConfig(true);

        }else if("AttrShow.xml" == *it)
        {
            bUpdate = BattlePointCalucator.Init();

        }else if("Area.xml" == *it)
        {
            bUpdate = g_AreaManager.Init();

        }else if("AI.xml" == *it)
        {
            bUpdate = CMonsterMgr::LoadConfig(*it);
        }else if("Activity.xml" == *it)
        {
            bUpdate = g_CActivityManager.ReLoadConfig(*it);
        }else if("ActivityPool.xml" == *it)
        {
            bUpdate = g_CActivityManager.ReLoadConfig(*it);
            //The First End====================================
        }else if("HorseUpgrade.xml" == *it)
        {
            bUpdate = CHorseMgr::ReLoadConfig(*it);

        }else if("HorseBase.xml" == *it)
        {
            bUpdate = CHorseMgr::ReLoadConfig(*it);

        }else if("GuildBattleConfig.xml" == *it)
        {
            bUpdate = CGuildBattleConfigMgr::Instance().ReLoadConfig(*it);

        }else if("GuildSpot.xml" == *it)
        {
            bUpdate = CGuildBattleConfigMgr::Instance().ReLoadConfig(*it);

        }else if("GuildBattleSkill.xml" == *it)
        {
            bUpdate = CGuildBattleConfigMgr::Instance().ReLoadConfig(*it);
        }else if("GuildBattlePos.xml" == *it)
        {
            bUpdate = CGuildBattleConfigMgr::Instance().ReLoadConfig(*it);

        }else if("GetCond.xml" == *it)
        {
            bUpdate = CGetCondMgr::Instance().Init();
        }else if("Gather.xml" == *it)
        {
            bUpdate = CGatherMgr::ReloadConfig(true);

        }else if("Exp.xml" == *it)
        {
            bUpdate = CExpMgr::Init();

        }else if("Exclusion.xml" == *it)
        {
            bUpdate = CActionManager::Init();

        }else if("ExchangeMall.xml" == *it)
        {
            bUpdate = CExchangeShopMgr::ExchangeInit();

        }else if("Event.xml" == *it)
        {
            bUpdate = CEventMgr::EventInit();
        }else if("EnergyPrice.xml" == *it)
        {
            bUpdate = CEnergyMgr::CEnergyMgr_Init();

        }else if("Dungeon.xml" == *it)
        {
            bUpdate = CDungeonMgr::Init();

        }else if("DungeonAssess.xml" == *it)
        {
            bUpdate = g_CDgnCondManager.Init();

        }else if("DemonTower.xml" == *it)
        {
            bUpdate = g_DemonTowerMgr.ReLoadConfig(*it);

        }else if("DayAct.xml" == *it)
        {
            bUpdate = g_DayActivityMgr.Init();

        }else if("Daily_yamen.xml" == *it)
        {
            bUpdate = g_CYaMenTaskManager.ReLoadConfig(*it);
        }else if("Daily_yamentaskColor.xml" == *it)
        {
            bUpdate = g_CYaMenTaskManager.ReLoadConfig(*it);
        }else if("Daily_yamentask.xml" == *it)
        {
            bUpdate = g_CYaMenTaskManager.ReLoadConfig(*it);
            //The second End================================
        }else if("NpcProp.xml" == *it)
        {
            bUpdate = CNpcMgr::ReloadConfig(true);

        }else if("MonsterGroup.xml" == *it)
        {
            bUpdate = CMonsterMgr::LoadConfig(*it);
        }else if("MessageSysMailBody.xml" == *it)
        {
            bUpdate = GameServerSysMail::Init();

        }else if("Loots.xml" == *it)
        {
            bUpdate = CLootMgr::Instance().Init();

        }else if("LanghuanfudiSkill.xml" == *it)
        {
            bUpdate = CLangHuanBlessMgr::Instance().ReLoadConfig(*it);

        }else if("LanghuanfudiAward.xml" == *it)
        {
            bUpdate = CLangHuanBlessMgr::Instance().ReLoadConfig(*it);

        }else if("IconAppear.xml" == *it)
        {
            bUpdate = CIconAppearMgr::Instance().Init();
            //The third End
        }else if("TrumpGetCond.xml" == *it)
        {
            bUpdate = CTrumpMgr::Instance().LoadConfig(*it);
        }else if("Title.xml" == *it)
        {
            bUpdate = g_CTitleManager.Init();

        }else if("TaskDrop.xml" == *it)
        {
            bUpdate = CMonsterMgr::LoadConfig(*it);

        }else if("SoulSpace.xml" == *it)
        {
            bUpdate = g_DemonTowerMgr.ReLoadConfig(*it);

        }else if("SkillEffect.xml" == *it)
        {
            bUpdate = CSkillMgr::Instance().ReLoadConfig(*it) && BattleSkillEffectReload(_strConfigDir, *it);
        }else if("SkillBase.xml" == *it)
        {
            bUpdate = CSkillMgr::Instance().ReLoadConfig(*it) && BattleSkillBaseReload(_strConfigDir, *it);
        }else if("SkillAttr.xml" == *it)
        {
            bUpdate = g_SkillAttrMgr.SkillAttrInit();

        }else if("SkillArea.xml" == *it)
        {
            bUpdate = BattleAreaReload(_strConfigDir, *it);

        }else if("ShuShanLunJianExp.xml" == *it || 
                "ShushanBattleTask.xml" == *it  || 
                "ShushanBattleSkill.xml" == *it ||
                "ShushanBattleAward.xml" == *it 
                )
        {
            bUpdate = CShushanBattleMgr::LoadConfig(true);

        }else if("Resist.xml" == *it)
        {
            bUpdate = CBlockerMgr::Init();

        }else if("YelloDiamond.xml" == *it)
        {
            //TODO
        }else if("WorldBoss.xml" == *it)
        {
            bUpdate = CMonsterMgr::LoadConfig(*it);

        }else if("WorldBossPrize.xml" == *it)
        {
            bUpdate = CWorldBossMgr::Instance().Init();

        }else if("VIPLevel.xml" == *it)
        {
            bUpdate = CVIPMgr::Instance().LoadConfig(*it);
        }else if("VIPBase.xml" == *it)
        {
            bUpdate = CVIPMgr::Instance().LoadConfig(*it);
        }else if("TrumpIntensify.xml" == *it)
        {
            bUpdate = CTrumpMgr::Instance().LoadConfig(*it);
        }else if("SignIn.xml" == *it)
        {
            bUpdate = g_CSignInManager.Init();
        }else if("SearchBuff.xml" == *it || 
                "SearchMap.xml" == *it)
        {
            bUpdate = CTreasureHuntMgr::Instance().LoadConfig(*it);
        }else if("GuardEMei.xml" ==  *it || 
                "GuardEMeiLevel.xml" ==  *it ||
                "Effect.xml" ==  *it)
        {
            bUpdate = CGuardEMeiMgr::Instance().LoadConfig(*it);
        }else if("SevDiscount.xml" == *it)
        {
            bUpdate = CCommonMgr::Instance().LoadConfig(*it);
        }

        if(bUpdate)
        {
            sRet.append("Reload Table [" + *it + "] Success!!\n");
            LOG_CRI << "Reload table " <<*it<<" Suc";
        }
        else
        {
            sRet.append("Reload Table [" + *it + "] Error!!\n");
            LOG_CRI << "Reload table " <<*it<<" Error";
        }
    }
    g_ChatProtS.SendClt_SystemMsgNotify(NULL,0,eChannelSys,sRet,eSubNone);
}

void CGameConfig::OnDBInited()
{
    if(!CGUIDMgr::Instance().LoadGUID())
        LOG_CRI << "LoadGUIDForGameServer fails!";
    CMall::Instance().LoadMallDiscount();
}
void CGameConfig::OnCenterInited()
{
    _bAllConnect = true;
    if(_bInited && IsDBInited() && g_Game2CenterCommC.IsCenterInited())
    {
        g_Game2CenterCommC.Send_GameSvrInitNft();
        LOG_INF << "Send _GameSvrInitNft()";
    }
}
