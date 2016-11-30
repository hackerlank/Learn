#pragma once

#include "ace\ACE.h"
#include "ace\Singleton.h"
#include "ace\Containers.h"
#include "ace\Semaphore.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"   
#include "cppconn/prepared_statement.h"   
#include "cppconn/metadata.h"   
#include "cppconn/exception.h" 
//#include "ace\Thread.h"
//#include "ace\Synch.h"
//#include "ace\Condition_Thread_Mutex.h"

using namespace sql;

//创建连接池
//使用信号量唤醒等待的线程

#define MAX_DB_CONNECTION 200

class ConnectionPool
{
	friend class DBLogMgr;//xxj 2015/04/26 17:00:37 用于日志文件
public:
	ConnectionPool();
	~ConnectionPool();

	Connection *acquire_connection();
	void release_connection(Connection *conn);

	
private:
	Connection *create_connection();
	Connection *create_Log_connection();//xxj 2015/04/26 16:18:29 创建一个日志数据库连接
	void destroy_connection(Connection *conn);

	void destroy_all();

	ACE_Unbounded_Queue<Connection *> m_freeConnectionQueue;

	ACE_UINT32 m_unCurrentSize;
	ACE_Recursive_Thread_Mutex m_mutex;
	ACE_Semaphore m_semaphore;
};

typedef ACE_Singleton<ConnectionPool, ACE_Thread_Mutex> CONNECTION_POOL_INSTANCE;