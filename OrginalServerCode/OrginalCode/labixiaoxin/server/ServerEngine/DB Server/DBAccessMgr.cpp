#include "DBAccessMgr.h"
#include "ace\Thread_Manager.h"
#include "DBHandler.h"
#include "..\Base\Service\BaseService.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif
#include "../GameBase/Common/GameUtils.h"

//#define MAX_DB_HANDLER 100

#define MAX_DB_ACCESS_THREAD 50

DBAccessMgr::DBAccessMgr()
{
	m_nThreadGroupID = -1;

	m_dealQueue.high_water_mark(0xA00000);
	m_dealQueue.low_water_mark(0xA00000);
}

DBAccessMgr::~DBAccessMgr()
{
	
}

int DBAccessMgr::init()
{
	//m_threadGroupID = m_dbConnectorThread = ACE_Thread_Manager::instance()->spawn_n(NULL, MAX_DB_ACCESS_THREAD, do_db_query, NULL, 0);

	m_nThreadGroupID = ACE_Thread_Manager::instance()->spawn_n(MAX_DB_ACCESS_THREAD, do_db_query, this);//多个线程

	if(m_nThreadGroupID == -1)
	{
		return -1;
	}

	return 0;
}

void DBAccessMgr::fini()
{
	m_dealQueue.close();


	if(m_nThreadGroupID != -1)
	{
		ACE_Thread_Manager::instance()->wait_grp(m_nThreadGroupID);
		m_nThreadGroupID = -1;
	}
}

int DBAccessMgr::add_deal_msg(ACE_Message_Block *msg)
{
	if(m_dealQueue.enqueue(msg) == -1)
	{
		return -1;
	}

	return 0;
}

ACE_THR_FUNC_RETURN DBAccessMgr::do_db_query(void *opParam)
{
	ACE_Message_Block *msg;

	DBAccessMgr *mgr = (DBAccessMgr *)opParam;

	MessageInfo msgInfo;

	DBHandler *handler = NULL;

	char *send_buff = new char[81920];

	while(1)
	{
		if(mgr->m_dealQueue.dequeue(msg) == -1)
		{
			break;
		}
// 		__try
// 		{
			//do db query
			if(parseMsg(msgInfo, msg) == 0)
			{
				handler = (DBHandler *)BaseService::instance()->findServiceObj(msgInfo.s_head->desAdr);
				if(handler != NULL)
				{
					handler->do_db_msg(msgInfo, send_buff);
				}
			}

			msg->release();
//		}
// 		__except(puts("exception error"),1)
// 		{
// 			FILE *_fp;
// 			char file_name[64];
// 			char day_str[32];
// 			GameUtils::get_current_day_str(day_str);
// 			sprintf(file_name, "loginfo/error-%s.txt",day_str);
// 			_fp = fopen(file_name, "a");
// 			if (_fp)
// 			{
// 				GameUtils::get_current_time_str(day_str);
// 				fprintf(_fp, "Memory crash %s\n", day_str);
// 				fclose(_fp);
// 				_fp = NULL;
// 			}
// 
// 			printf("memory error !!!!!!!!!!!!!!!\n");
// 		}
		
	}

	delete send_buff;

	printf("do_db_query error\n");
	return static_cast<ACE_THR_FUNC_RETURN>(0);
}