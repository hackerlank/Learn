// DB Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DBService.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"   
#include "cppconn/prepared_statement.h"   
#include "cppconn/metadata.h"   
#include "cppconn/exception.h"

#include "ConnectionPool.h"

using namespace sql;


#include "..\GameBase\Common\MyDump.h"

int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//设置回调函数
	
	DBService ts;

	//ts.Startup(SERVICE_DB_ID, TEST_DB_PORT, 0);
	ts.Startup("Test DB Server");

	return 0;
}

