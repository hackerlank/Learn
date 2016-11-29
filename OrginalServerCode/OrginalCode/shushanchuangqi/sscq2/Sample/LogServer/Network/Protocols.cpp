#include "stdafx.h"
#include "Protocols.h"

CLogEventS g_LogEventS4CT;
CLogEventS g_LogEventS4GS;
CLogEventS g_LogEventS4DB;
/*CLogEventS g_LogEventS4GT;*/

CDBProtS g_DBProtS4CT;
CDBProtS g_DBProtS4GS;

void CLogNetMgr::InitProtocol()
{
	CSvrHandler* pCenterHandler = GetSvrHandler(eHostCenter);
	CSvrHandler* pGameHandler = GetSvrHandler(eHostGame);
	CSvrHandler* pDBHandler = GetSvrHandler(eHostDB);
    //CSvrHandler* pGateHandler = GetSvrHandler(eHostGate);

	//CenterServer
	if(pCenterHandler != NULL)
	{
		pCenterHandler->RegisterProtocol(g_LogEventS4CT);
		pCenterHandler->RegisterProtocol(g_DBProtS4CT);
	}
	//GameServer
	if(pGameHandler != NULL)
	{
		pGameHandler->RegisterProtocol(g_LogEventS4GS);
		pGameHandler->RegisterProtocol(g_DBProtS4GS);
	}
	//DBServer
	if(pDBHandler != NULL)
		pDBHandler->RegisterProtocol(g_LogEventS4DB);
    //GateServer
	/*if(pGateHandler != NULL)
		pGateHandler->RegisterProtocol(g_LogEventS4GT);*/


}
