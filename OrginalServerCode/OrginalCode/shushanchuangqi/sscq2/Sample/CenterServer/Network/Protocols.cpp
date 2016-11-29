#include "stdafx.h"
#include "Protocols.h"
#include "DemonTowerSvrS.h"
#include "Game2CenterDemonTowerS.h"
#include "Game2CenterLogS.h"
#include "TeamGSS.h"
#include "Game2CenterTeamS.h"
#include "PHPProtS.h"
#include "BeautyLogSvrS.h"
#include "AnswerProtS.h"
#include "InviteGSSvrS.h"
#include "GodMonsterProtS.h"
#include "Center2DBGuildC.h"

CDBProtC g_DBProtC;
CDBProtC g_LogDBProtC;
CLogin2CenterCommS g_Login2CenterCommS;
CGate2CenterCommS g_Gate2CenterCommS;
CCenter2DBCommC g_Center2DBCommC;
CGame2CenterCommS g_Game2CenterCommS;
NLogEvent::CLogEventClt g_LogEvent;
CGlobalChatProtS g_GlobalChatProtS;
CFriendProtS g_FriendProtS;
CMailProtS g_MailProtS;
CArenaGSS g_ArenaGSS;
CGuildProtS g_GuildProtS;
CRankProtS g_RankProtS;
CGame2CenterGuildBattleS g_Game2CenterGuildBattleS;
CGame2CenterLogS g_Game2CenterLogS;
CGame2CenterRankS g_Game2CenterRankS;
CTripodProtS g_TripodProtS;
CShipProtS g_ShipProtS;
void CCenterNetMgr::InitProtocol()
{
	CGateHandler* pGateHandler = GetGateHandler();
	CSvrHandler* pLoginHandler = GetSvrHandler(eHostLogin);
	CSvrHandler* pGameHandler = GetSvrHandler(eHostGame);
	CSvrHandler* pDBHandler = GetSvrHandler(eHostDB);
	CSvrHandler* pLogHandler = GetSvrHandler(eHostLog);
	CSvrHandler* pControlHandler = GetSvrHandler(eHostControl);

	//GateServers
	if(pGateHandler != NULL)
	{
		pGateHandler->RegisterProtocol(g_Gate2CenterCommS);
		pGateHandler->RegisterProtocol(g_GlobalChatProtS);
		pGateHandler->RegisterProtocol(g_FriendProtS);
        pGateHandler->RegisterProtocol(g_MailProtS);
        pGateHandler->RegisterProtocol(g_ArenaGSS);
        pGateHandler->RegisterProtocol(g_CTeamGSS);
        pGateHandler->RegisterProtocol(g_GuildProtS);
        pGateHandler->RegisterProtocol(g_DemonTowerSvrS);
        pGateHandler->RegisterProtocol(g_RankProtS);
        pGateHandler->RegisterProtocol(g_TripodProtS);
        pGateHandler->RegisterProtocol(g_WonderActivityProtS);
        pGateHandler->RegisterProtocol(g_AnswerProtS);
        pGateHandler->RegisterProtocol(g_ShipProtS);
        pGateHandler->RegisterProtocol(g_BeautyLogSvrS);
        pGateHandler->RegisterProtocol(g_InviteSvrS);
        pGateHandler->RegisterProtocol(g_GodMonsterProtS);

	}
	//LoginServer
	if(pLoginHandler != NULL)
		pLoginHandler->RegisterProtocol(g_Login2CenterCommS);
	//GameServer
	if(pGameHandler != NULL)
	{
		pGameHandler->RegisterProtocol(g_Game2CenterCommS);
        pGameHandler->RegisterProtocol(g_Game2CenterTeamS);
        pGameHandler->RegisterProtocol(g_Game2CenterDemonTowerS);
        pGameHandler->RegisterProtocol(g_Game2CenterGuildBattleS);
        pGameHandler->RegisterProtocol(g_Game2CenterLogS);
        pGameHandler->RegisterProtocol(g_Game2CenterRankS);
	}
	//DBServer
	if(pDBHandler != NULL)
	{
		pDBHandler->RegisterProtocol(g_Center2DBCommC);
		pDBHandler->RegisterProtocol(g_Center2DBGuildC);
		pDBHandler->RegisterProtocol(g_DBProtC);
	}
	//LogServer
	if(pLogHandler != NULL)
	{
        pLogHandler->RegisterProtocol(g_LogEvent);
		pLogHandler->RegisterProtocol(g_LogDBProtC);
	}
	//ControlClient
	if(pControlHandler != NULL)
	{
		pControlHandler->RegisterProtocol(g_PHPProtS);
	}
}
