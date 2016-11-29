#include "stdafx.h"
#include "Protocols.h"

CExampleS g_ExampleS;
CLoginProtS g_LoginProtS;
CLogin2CenterCommC g_Login2CenterCommC;

void CLoginNetMgr::InitProtocol()
{
	IConnectionHandler* pClientHandler = GetConnectionHandler(eHostNone);
	CSvrHandler* pCenterHandler = GetSvrHandler(eHostCenter);
	//Client
	if(pClientHandler != NULL)
	{
		pClientHandler->RegisterProtocol(g_ExampleS);
		pClientHandler->RegisterProtocol(g_LoginProtS);
	}
	//CenterServer
	if(pCenterHandler != NULL)
		pCenterHandler->RegisterProtocol(g_Login2CenterCommC);
}
