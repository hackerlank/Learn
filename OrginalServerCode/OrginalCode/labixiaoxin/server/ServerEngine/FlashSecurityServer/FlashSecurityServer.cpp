// FlashSecurityServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ace\ACE.h"
#include "ace\OS_main.h"
#include "SecurityService.h"

#define TEST_SERVICE_ADDRESS "192.168.1.12"

int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{
	//GameMgrService gs;

	//gs.Startup(GAME_SERVER_ID, SERVICE_MGR_LISTEN_PORT, 1);
	SecurityService ss;
	ss.activate(TEST_SERVICE_ADDRESS);

	return 0;
}

