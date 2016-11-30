// World Manager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\GameBase\Common\GameService.h"

int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{
	GameService ts;

	ts.Startup(TEST_WORLD_MANAGER_ID, TEST_WORLD_MANAGER_PORT, 0);

	return 0;
}

