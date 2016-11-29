#include "stdafx.h"
#include "Protocols.h"

#include "Center2DBGuildS.h"

CDBProtS g_DBProtS4CT;
CDBProtS g_DBProtS4GS;
CGate2DBCommS g_Gate2DBCommS;
CCenter2DBCommS g_Center2DBCommS;
CGame2DBCommS g_Game2DBCommS;
NLogEvent::CLogEventClt g_LogEvent;
CRoleEnterGameProtSvrS g_RoleEnterGameProtSvrS;
void CDBNetMgr::InitProtocol()
{
	CGateHandler* pGateHandler = GetGateHandler();
	CSvrHandler* pCenterHandler = GetSvrHandler(eHostCenter);
	CSvrHandler* pGameHandler = GetSvrHandler(eHostGame);
	CSvrHandler* pLogHandler = GetSvrHandler(eHostLog);
	//GateServer
	if(pGateHandler != NULL)
	{
		pGateHandler->RegisterProtocol(g_Gate2DBCommS);
        pGateHandler->RegisterProtocol(g_RoleEnterGameProtSvrS);
	}
	//CenterServer
	if(pCenterHandler != NULL)
	{
		pCenterHandler->RegisterProtocol(g_DBProtS4CT);
		pCenterHandler->RegisterProtocol(g_Center2DBCommS);
		pCenterHandler->RegisterProtocol(g_Center2DBGuildS);
	}
	//GameServer
	if(pGameHandler != NULL)
	{
		pGameHandler->RegisterProtocol(g_DBProtS4GS);
		pGameHandler->RegisterProtocol(g_Game2DBCommS);
	}
	//LogServer
	if(pLogHandler != NULL)
		pLogHandler->RegisterProtocol(g_LogEvent);
}
