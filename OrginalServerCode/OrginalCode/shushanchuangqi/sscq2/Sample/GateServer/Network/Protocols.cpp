#include "stdafx.h"
#include "Protocols.h"

CGate2CenterCommC g_Gate2CenterCommC;
CGate2GameCommC g_Gate2GameCommC;
CGate2DBCommC g_Gate2DBCommC;
CGameSvrBasicS g_GameSvrBasicS;
/*NLogEvent::CLogEventClt g_LogEvent;*/

void CGateNetMgr::InitProtocol()
{
	CSvrHandler* pCenterHandler = GetSvrHandler(eHostCenter);
	CSvrHandler* pGameHandler = GetSvrHandler(eHostGame);
	CSvrHandler* pDBHandler = GetSvrHandler(eHostDB);
	/*CSvrHandler* pLogHandler = GetSvrHandler(eHostLog);

	//LogServer
	if(pLogHandler != NULL)
	{
		pLogHandler->RegisterProtocol(g_LogEvent);
	}*/

	//CenterServer
	if(pCenterHandler != NULL)
		pCenterHandler->RegisterProtocol(g_Gate2CenterCommC);
	//GameServer
	if(pGameHandler != NULL)
		pGameHandler->RegisterProtocol(g_Gate2GameCommC);
	//DBServer
	if(pDBHandler != NULL)
		pDBHandler->RegisterProtocol(g_Gate2DBCommC);
	//Client
	assert(_pClientMgr != NULL);
	_pClientMgr->RegisterPeekProtC2S(g_GameSvrBasicS);
}
