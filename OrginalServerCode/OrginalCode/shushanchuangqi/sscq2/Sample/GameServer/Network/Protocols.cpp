#include "stdafx.h"

#include "Protocols.h"

#include "GameNetMgr.h"
#include "DemonTowerSvrS.h"
#include "Game2CenterDemonTowerC.h"
#include "Game2CenterTeamC.h"
#include "HorseSvrS.h"
#include "BossProtS.h" 
#include "MiscProtS.h"
#include "DayActProtS.h"
#include "AchievementProtS.h"
#include "CollectionProtS.h"
#include "LangHuanBlessProtS.h"
#include "ExchangeShopSvrS.h"
#include "YelloDiamondProtS.h"
#include "ViewInfoProtS.h"
#include "WondActMgr.h"
#include "DayTargetS.h"
#include "LoginPkgProtS.h"
#include "TreasureHuntProtS.h"
#include "GuardEMeiProtS.h"
#include "MoneyTreeProtS.h"
#include "RegisterSevenDaysProtS.h"
#include "BattleArrayS.h" 
#include "BeautyS.h"
#include "ShushanweiweiProtS.h"
#include "FightFormationS.h"
#include "LingShanProtS.h"
#include "NewGuildBattleProtS.h"
#include "ShengLingProtS.h"
#include "EquipTrumpProtS.h"
#include "FeedBackProtS.h"

CGate2GameCommS g_Gate2GameCommS;
CGame2DBCommC g_Game2DBCommC;
CGame2CenterCommC g_Game2CenterCommC;
CDBProtC g_DBProtC;
CDBProtC g_LogDBProtC;
CMapProtS g_MapProtS;
CGameSvrBasicS g_GameSvrBasicS;
CGameSvrCommC g_GameSvrCommC;
CGameSvrCommS g_GameSvrCommS;
NLogEvent::CLogEventClt g_LogEvent;
CChatProtS g_ChatProtS;
CRoleEventS g_RoleEventProtS;
CNpcProtS g_NpcProtS;
CDungeonProtS g_DungeonProtS;
CItemProtS g_ItemProtS;
CPropInfoS g_PropInfoS;
CBattleGSS g_BattleGSS;
CTaskProtS g_TaskProtS;
CMallProtS g_MallProtS;
CFighterProtS g_FighterProtS;
CGatherProtS g_GatherProtS;
CFormationProtS g_FormationProtS;
CShushanBattleProtS g_ShushanBattleProtS;
CVIPProtS g_VIPProtS;
CGroupTaskProtS g_GroupTaskProtS;
CYaMenTaskProtS g_YaMenTaskProtS;
CActivityProtS g_ActivityProtS;
CTitleProtS g_TitleProtS;
CGuildBattleProtS g_GuildBattleProtS;
CGame2CenterGuildBattleC g_Game2CenterGuildBattleC;
CCompareBattlePointS g_CompareBattlePointS;
CSittingProtS g_SittingProtS;
CGame2CenterLogC g_Game2CenterLog;
CGame2CenterRankC g_Game2CenterRankC;
CSignProtS g_SignProtS;
void CGameNetMgr::InitProtocol()
{
	CGateHandler* pGateHandler = GetGateHandler();
	CSvrHandler* pCenterHandler = GetSvrHandler(eHostCenter);
	CSvrHandler* pDBHandler = GetSvrHandler(eHostDB);
	CSvrHandler* pLogHandler = GetSvrHandler(eHostLog);

	//GateServers
	if(pGateHandler)
	{
		pGateHandler->RegisterProtocol(g_Gate2GameCommS);
		pGateHandler->RegisterProtocol(g_MapProtS);
		pGateHandler->RegisterProtocol(g_GameSvrBasicS);
		pGateHandler->RegisterProtocol(g_ChatProtS);
        pGateHandler->RegisterProtocol(g_RoleEventProtS);
        pGateHandler->RegisterProtocol(g_NpcProtS);
        pGateHandler->RegisterProtocol(g_DungeonProtS);
        pGateHandler->RegisterProtocol(g_ItemProtS);
        pGateHandler->RegisterProtocol(g_PropInfoS);
        pGateHandler->RegisterProtocol(g_BattleGSS);
        pGateHandler->RegisterProtocol(g_TaskProtS);
        pGateHandler->RegisterProtocol(g_FighterProtS);
        pGateHandler->RegisterProtocol(g_GatherProtS);
        pGateHandler->RegisterProtocol(g_FormationProtS);
        pGateHandler->RegisterProtocol(g_ShushanBattleProtS);
        pGateHandler->RegisterProtocol(g_VIPProtS);
        pGateHandler->RegisterProtocol(g_DemonTowerSvrS);
        pGateHandler->RegisterProtocol(g_BossProtS);
        pGateHandler->RegisterProtocol(g_MallProtS);
        pGateHandler->RegisterProtocol(g_GroupTaskProtS);
        pGateHandler->RegisterProtocol(g_HorseSvrS);
        pGateHandler->RegisterProtocol(g_YaMenTaskProtS);
        pGateHandler->RegisterProtocol(g_ActivityProtS);
        pGateHandler->RegisterProtocol(g_TitleProtS);
        pGateHandler->RegisterProtocol(g_MiscProtS);
        pGateHandler->RegisterProtocol(g_GuildBattleProtS);
        pGateHandler->RegisterProtocol(g_NewGuildBattleProtS);
        pGateHandler->RegisterProtocol(g_DayActProtS);
        pGateHandler->RegisterProtocol(g_CompareBattlePointS);
        pGateHandler->RegisterProtocol(g_AchievementProtS);
        pGateHandler->RegisterProtocol(g_CollectionProtS);
        pGateHandler->RegisterProtocol(g_SittingProtS);
        pGateHandler->RegisterProtocol(g_LangHuanBlessProtS);
        pGateHandler->RegisterProtocol(g_ExchangeShopProtSvrS);
        pGateHandler->RegisterProtocol(g_YelloDiamondProtS);
        pGateHandler->RegisterProtocol(g_ViewInfoProtS);
        pGateHandler->RegisterProtocol(g_LevelPrizeSvrS);
        pGateHandler->RegisterProtocol(g_CoinProtS);
        pGateHandler->RegisterProtocol(g_SignProtS);
        pGateHandler->RegisterProtocol(g_DayTargetS);
        pGateHandler->RegisterProtocol(g_LoginPkgProtS);
        pGateHandler->RegisterProtocol(g_TreasureHuntProtS);
        pGateHandler->RegisterProtocol(g_GuardEMeiProtS);
        pGateHandler->RegisterProtocol(g_MoneyTreeProtS);
        pGateHandler->RegisterProtocol(g_RegisterSevenDaysProtS);
        pGateHandler->RegisterProtocol(g_BattleArrayS);
        pGateHandler->RegisterProtocol(g_ShushanweiweiProtS);
        pGateHandler->RegisterProtocol(g_BeautyS);
        pGateHandler->RegisterProtocol(g_FightFormationS);
        pGateHandler->RegisterProtocol(g_LingShanProtS);
        pGateHandler->RegisterProtocol(g_ShengLingProtS);
        pGateHandler->RegisterProtocol(g_EquipTrumpProtS);
        pGateHandler->RegisterProtocol(g_FeedBackProtS);
	}

	//CenterServer
	if(pCenterHandler != NULL)
	{
		pCenterHandler->RegisterProtocol(g_Game2CenterCommC);
        pCenterHandler->RegisterProtocol(g_Game2CenterTeamC);
        pCenterHandler->RegisterProtocol(g_Game2CenterDemonTowerC);
        pCenterHandler->RegisterProtocol(g_Game2CenterGuildBattleC);
		pCenterHandler->RegisterProtocol(g_Game2CenterLog);
		pCenterHandler->RegisterProtocol(g_Game2CenterRankC);
	}

	//DBServer
	if(pDBHandler != NULL)
	{
		pDBHandler->RegisterProtocol(g_DBProtC);
		pDBHandler->RegisterProtocol(g_Game2DBCommC);
	}
	
	//LogServer
	if(pLogHandler != NULL)
	{
		pLogHandler->RegisterProtocol(g_LogEvent);
		pLogHandler->RegisterProtocol(g_LogDBProtC);
	}

	//GameServer
	g_GameSvrHandlerC2S.RegisterProtocol(g_GameSvrCommC);
	g_GameSvrHandlerS2C.RegisterProtocol(g_GameSvrCommS);
}
