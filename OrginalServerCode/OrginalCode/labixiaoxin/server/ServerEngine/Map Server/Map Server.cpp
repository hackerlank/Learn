// Map Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MapService.h"
#include "ace\OS_main.h"
#include "ace\ACE.h"

#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif

#include "..\GameBase\Common\MyDump.h"
#include "..\GameBase\Common\GameUtils.h"

int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//设置回调函数

	//Service ts;

	//ts.Startup(CLUSTER_MANAGER_ID, SERVICE_MGR_LISTEN_PORT, 1);

	MapService *ls = new MapService();

	//ls->Startup(TEST_MAP_SERVICE_ID, TEST_MAP_SERVER_PORT, 0);
	ls->Startup("Test Map Server");

	delete ls;

	return 0;
}