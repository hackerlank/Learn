// PhpProxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ace\OS_main.h"
#include "ace\ACE.h"
#include "PhpProxyService.h"

#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif


#include "..\GameBase\Common\MyDump.h"


int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//设置回调函数

	//Service ts;

	//ts.Startup(CLUSTER_MANAGER_ID, SERVICE_MGR_LISTEN_PORT, 1);

	//MapService *ls = new MapService();

	//ls->Startup(TEST_MAP_SERVICE_ID, TEST_MAP_SERVER_PORT, 0);

	//delete ls;

	PhpProxyService *ls = new PhpProxyService();
	//ls->Startup(TEST_PHP_PROXY_SERVICE_ID, TEST_PHP_PROXY_SERVER_PORT, 0);
	ls->Startup("Test Php Proxy");

	delete ls;

	return 0;
}