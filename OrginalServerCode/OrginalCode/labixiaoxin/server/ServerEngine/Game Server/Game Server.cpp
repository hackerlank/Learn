// Game Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ace\ACE.h"
#include "ace\OS_main.h"
#include "GameMgrService.h"
#include "ace\Containers.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"

#include "..\Base\TimerMgr\TimerMgr.h"

typedef struct tagTestInfo
{
	int v;
}TestInfo;

typedef ACE_DLList<TestInfo> TEST_DL_LIST;
typedef ACE_DLList_Iterator<TestInfo> TEST_DL_LIST_ITERATOR;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, TestInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> TEST_OBJ_MAP;
typedef TEST_OBJ_MAP::ITERATOR TEST_OBJ_MAP_ITERATOR;



#include "..\GameBase\Common\MyDump.h"

int ACE_TMAIN(int argc, ACE_TCHAR **argv)
{

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);//设置回调函数

	
#if 0
	int i;

	TestInfo *info;

	TEST_DL_LIST testList;

	for(i = 0;i < 100;i ++)
	{
		info = new TestInfo();
		info->v = i;

		testList.insert_tail(info);
	}

	printf("list size = %d\n", testList.size());

	TEST_DL_LIST_ITERATOR iter(testList);

	while(!iter.done())
	{
		info = iter.next();

		printf("info = %d\n", info->v);

		//iter.remove();
		//iter.advance_and_remove(true);
		iter.advance();

		delete info;
		//delete info;
	}

	testList.reset();

	printf("list size = %d\n", testList.size());
#endif
	/*
	TEST_OBJ_MAP testMap;

	TestInfo *info = new TestInfo();

	testMap.bind(1, info);

	testMap.unbind(1);

	delete info;
	*/

	GameMgrService gs;

	//gs.Startup(GAME_SERVER_ID, SERVICE_MGR_LISTEN_PORT, 1);
	gs.Startup("Game Server");

	return 0;
}
