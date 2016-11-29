// test4LoadingLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <process.h>
#include <iostream>

#include "TaskConfMgr.h"
#include "TaskConf.h"

int _tmain(int argc, _TCHAR* argv[])
{
	const char dir[] = "d:\\task";
	if(!CTaskConfMgr::Instance().LoadTaskDirectory(dir))
	{
		std::cout << "failed to load tasks." << endl;
	}

	system("pause");
	return 0;
}

