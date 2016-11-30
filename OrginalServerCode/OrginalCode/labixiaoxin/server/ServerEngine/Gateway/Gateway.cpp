// Gateway.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "GatewayService.h"
#include "ace\OS_main.h"
#include "ace\ACE.h"

#include "..\GameBase\Common\MyDump.h"




int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//设置回调函数
	


	GatewayService ts;

	//ts.Startup(TEST_GATEWAY_ID, TEST_GATEWAY_PORT, 0);
	ts.Startup("Test Gateway");

	return 0;
}