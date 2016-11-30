#pragma once

#include "ace\ACE.h"
#include "ace\Singleton.h"
#include "ace\Message_Queue.h"
#include "ace\Condition_Thread_Mutex.h"



class DBAccessMgr
{
public:
	DBAccessMgr();
	~DBAccessMgr();

	int init();
	void fini();

	int add_deal_msg(ACE_Message_Block *msg);

private:
	ACE_Message_Queue<ACE_MT_SYNCH> m_dealQueue;

	static ACE_THR_FUNC_RETURN do_db_query(void *opParam);

	int m_nThreadGroupID;

	//ACE_Thread_t m_handleList[MAX_DB_ACCESS_THREAD];
};

typedef ACE_Singleton<DBAccessMgr, ACE_Thread_Mutex> DB_ACCESS_MGR_INSTANCE;