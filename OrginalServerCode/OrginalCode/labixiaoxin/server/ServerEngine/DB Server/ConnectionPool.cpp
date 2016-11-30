#include "ConnectionPool.h"
#include "..\GameBase\Common\GameDefine.h"
#include "..\Base\Service\ServiceConfigMgr.h"

ConnectionPool::ConnectionPool()
{
	m_unCurrentSize = 0;

	m_semaphore.release(MAX_DB_CONNECTION - 1);
}

ConnectionPool::~ConnectionPool()
{
	destroy_all();
}

Connection *ConnectionPool::acquire_connection()
{
	m_semaphore.acquire();
	
	Connection *con = NULL;
	
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

		if(!m_freeConnectionQueue.is_empty())
		{
			if(m_freeConnectionQueue.dequeue_head(con) == -1)
			{
				con = NULL;
			}

			if(con->isClosed())
			{
				delete con;

				m_unCurrentSize --;

				con = create_connection();
			}

			return con;
		}

		if(m_unCurrentSize < MAX_DB_CONNECTION)
		{
			con = create_connection();
		}
	}

	return con;
}

void ConnectionPool::release_connection(Connection *conn)
{
	bool flag = true;
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

		if(m_freeConnectionQueue.enqueue_tail(conn) == -1)
		{
			destroy_connection(conn);
			flag = false;
		}
	}

	if(flag)
	{
		m_semaphore.release();
	}
}

Connection *ConnectionPool::create_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	//连接数据库
	Driver *driver;
	Connection *con = NULL;

	try
	{
		driver = get_driver_instance();

		if(driver == NULL)
		{
			return NULL;
		}

		DatabaseInfo *dbInfo = &SERVICE_CONFIG_MGR_INSTANCE::instance()->m_dbInfo;

		/* create a database connection using the Driver */  
		con = driver->connect(dbInfo->host, dbInfo->user, dbInfo->password);

		if(con == NULL)
		{
			return NULL;
		}

		/* turn off the autocommit */
		con -> setAutoCommit(0);
		con -> setSchema(dbInfo->name);
	}
	catch (SQLException &e)
	{
		if(con != NULL)
		{
			try
			{
				con->close();
			}
			catch (SQLException &e)
			{
				printf("fuck !\n");
			}

			delete con;
		}

		con = NULL;
	}
	
	if(con != NULL)
	{
		m_unCurrentSize ++;
	}

	return con;
}


Connection *ConnectionPool::create_Log_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	//连接数据库
	Driver *driver;
	Connection *con = NULL;
	try
	{
		driver = get_driver_instance();

		if(driver == NULL)
		{
			return NULL;
		}

		DatabaseInfo *dbInfo = &SERVICE_CONFIG_MGR_INSTANCE::instance()->m_dblogInfo;//日志文件信息

		/* create a database connection using the Driver */  
		con = driver->connect(dbInfo->host, dbInfo->user, dbInfo->password);

		if(con == NULL)
		{
			return NULL;
		}

		/* turn off the autocommit */
		con -> setAutoCommit(0);
		con -> setSchema(dbInfo->name);
	}
	catch (SQLException &e)
	{
		if(con != NULL)
		{
			try
			{
				con->close();
			}
			catch (SQLException &e)
			{
				printf("fuck!!\n");
			}

			delete con;
		}
		con = NULL;
	}

	return con;
}

void ConnectionPool::destroy_connection(Connection *conn)
{
	if(conn == NULL)
	{
		return;
	}
	try
	{
		conn->close();
	}
	catch (SQLException &e)
	{
		
	}

	delete conn;

	if(m_unCurrentSize > 0)
	{
		m_unCurrentSize --;
	}
}

void ConnectionPool::destroy_all()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	Connection *con;
	while(!m_freeConnectionQueue.is_empty())
	{
		if(m_freeConnectionQueue.dequeue_head(con) != -1)
		{
			destroy_connection(con);
		}
	}

	m_unCurrentSize = 0;
}