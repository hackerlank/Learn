// Login Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "LoginService.h"
#include "ace\OS_main.h"
#include "ace\ACE.h"

#include "..\GameBase\Common\MyDump.h"



int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//设置回调函数
	

	//Service ts;

	//ts.Startup(CLUSTER_MANAGER_ID, SERVICE_MGR_LISTEN_PORT, 1);

	LoginService ls;

	//ls.Startup(TEST_LOGIN_SERVER_ID, TEST_LOGIN_SERVER_PORT, 0);
	ls.Startup("Test Login Server");

	return 0;
}
