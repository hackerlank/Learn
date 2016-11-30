#include "DBLogMgr.h"
#include "ace\Thread_Manager.h"
#include "..\Base\Service\BaseService.h"
#include "ConnectionPool.h"
#include "..\GameBase\Protocol\DBProtocol.h"
#include <sstream>
#include <exception>

DBLogMgr::DBLogMgr()
{
	m_prep_stmt = NULL;
	m_con = NULL;
	m_nThreadGroupID = -1;
	ZeroVar(m_srcAdr);
	m_dbuserHandlerCallBack = NULL;
}

DBLogMgr::~DBLogMgr()
{

}

int DBLogMgr::init(void* pCall)
{
	m_nThreadGroupID = ACE_Thread_Manager::instance()->spawn_n(1, do_execute, this);

	if(m_nThreadGroupID == -1)
	{
		return -1;
	}
	
	m_dbuserHandlerCallBack = pCall;
	return 0;
}

void DBLogMgr::fini()
{
	if(m_nThreadGroupID != -1)
	{
		ACE_Thread_Manager::instance()->wait_grp(m_nThreadGroupID);
		m_nThreadGroupID = -1;
	}
}

int DBLogMgr::write_db_log(const LogItemInfo * msg,ACE_INT32 len)//数据库日志写入
{
	ACE_ASSERT(len <= MSG_DB_LOG_INFO_MAX_LEN);
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_DBLogLock);
	for (int i=0;i<len;i++)
	{
		ACE_ASSERT(msg[i].m_op_involve == 0);
		m_queueDBLog.push(msg[i]);
	}

	return 0;
}

int DBLogMgr::write_admin_db_log(MsgDBAdminLogInfoRequest * msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_DBLogLock);
	m_queueDBadminLog.push(*msg);
	return 0;
}

bool DBLogMgr::Read_db_log( LogItemInfo & msg )
{
	if (m_queueDBLog.empty())
	{
		return false;
	}
	else
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_DBLogLock);
		msg = m_queueDBLog.front();
		m_queueDBLog.pop();
		return true;
	}
}


bool DBLogMgr::Read_db_log( MsgDBAdminLogInfoRequest & msg )
{
	if (m_queueDBadminLog.empty())
	{
		return false;
	}
	else
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_DBLogLock);
		msg = m_queueDBadminLog.front();
		m_queueDBadminLog.pop();
		return true;
	}
}


/*
ACE_THR_FUNC_RETURN DBLogMgr::do_execute(void *opParam)
{
	DBLogMgr *mgr = (DBLogMgr *)opParam;
	Connection *con = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	if(con == NULL)
	{
		printf("critical db error, db connection is null\n");
		return static_cast<ACE_THR_FUNC_RETURN>(-1);
	}
	while(1)
	{
		if (mgr->m_queueDBLog.empty())
		{
			break;
		}
		std::string &strSql = mgr->m_queueDBLog.front();
		m_prep_stmt = con->prepareStatement(strSql.c_str());
		if(m_prep_stmt == NULL)
		{
			mgr->m_queueDBLog.pop();
			return static_cast<ACE_THR_FUNC_RETURN>(-2);
		}
		m_prep_stmt->execute();
		con->commit();
		mgr->m_queueDBLog.pop();
	}
	return static_cast<ACE_THR_FUNC_RETURN>(0);
}*/

ACE_THR_FUNC_RETURN DBLogMgr::do_execute(void *opParam)
{
	DBLogMgr *mgr = (DBLogMgr *)opParam;
	mgr->m_con = CONNECTION_POOL_INSTANCE::instance()->create_Log_connection();
	if(mgr->m_con == NULL)
	{
		printf("critical log db error, db log connection is null\n");
		return static_cast<ACE_THR_FUNC_RETURN>(-1);
	}
	else
		printf("critical log db succeed\n");

	LogItemInfo logTemp;
	MsgDBAdminLogInfoRequest logAdminTemp;
	ZeroVar(logTemp);

	while(1)
	{
		if (mgr->Read_db_log(logAdminTemp))//admin 命令
		{
			if (!mgr->read_db_message(mgr->m_con,logAdminTemp))
				return static_cast<ACE_THR_FUNC_RETURN>(-2);
		}
		else//写命令
		{
			if (!mgr->Read_db_log(logTemp))
			{
				Sleep(1000);
			}
			else
			{
				if (!mgr->insert_db_message(mgr->m_con,logTemp))
					return static_cast<ACE_THR_FUNC_RETURN>(-2);
			}
		}
			
		mgr->m_con->commit();
		ZeroVar(logTemp);
	}

	//断开数据库
	if(!mgr->m_con)
	{
		try
		{
			mgr->m_con->close();
			printf("delete log db succeed\n");
		}
		catch (SQLException &e)
		{
			printf("delete log db exception\n");
		}

		delete mgr->m_con;
		mgr->m_con = NULL;
	}

	return static_cast<ACE_THR_FUNC_RETURN>(0);
}

bool DBLogMgr::insert_db_message( Connection *db_conn, const LogItemInfo &msgInfo )
{
	try
	{
		m_prep_stmt = db_conn->prepareStatement
			("insert into log_tbl(user_id,name,level,channel_id,log_type,goods_id,operate_before,operate_after,operate_involve,operate_action,operate_way,operate_time) values(?,?,?,?,?,?,?,?,?,?,?,?)");
		if(m_prep_stmt == NULL)
		{
			return false;
		}

		m_prep_stmt->setInt(1,msgInfo.m_unUserID );
		m_prep_stmt->setString(2,msgInfo.m_name );
		m_prep_stmt->setInt(3, msgInfo.m_unLevel);
		m_prep_stmt->setInt(4, msgInfo.m_unChannel);
		m_prep_stmt->setInt(5, msgInfo.m_unType);
		m_prep_stmt->setInt(6, msgInfo.m_goodsID);
		m_prep_stmt->setInt(7, msgInfo.m_op_before);
		m_prep_stmt->setInt(8, msgInfo.m_op_after);
		m_prep_stmt->setInt(9, msgInfo.m_op_involve);
		m_prep_stmt->setInt(10, msgInfo.m_op_action);
		m_prep_stmt->setString(11, msgInfo.m_op_way);
		m_prep_stmt->setInt(12, msgInfo.m_op_time);

		m_prep_stmt->executeUpdate();

		//delete 
		//if(m_prep_stmt != NULL)
		{
			m_prep_stmt->close();
			delete m_prep_stmt;
			m_prep_stmt = NULL;
		}
		return true;
	}
	catch (SQLException& e)
	{
		printf("sql error:%s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
	return false;
}

// void DBLogMgr::destroy_db_res()
// {
// 	if(m_php_res != NULL)
// 	{
// 		try
// 		{
// 			m_php_res->close();
// 		}
// 		catch(SQLException& e) 
// 		{
// 		}
// 
// 		delete m_php_res;
// 		m_php_res = NULL;
// 	}
// }

/*
bool DBLogMgr::ReadLogItems( const MsgDBAdminLogInfoRequest * request,MsgDBAdminLogInfoResponse & response )
{
	response.m_unCount = 0;
	PreparedStatement *prep_stmt = NULL;
	try
	{
		Connection * db_con = CONNECTION_POOL_INSTANCE::instance()->create_Log_connection();
		if(db_con == NULL)
		{
			printf("critical php log db error, db log connection is null\n");
			return false;
		}

		bool isWhere = false;
		if (request->m_unType>0 || request->m_unUserID>0 || request->m_unLevel>0 || request->m_goodsID>0 || request->m_op_action>0 )
		{
			isWhere =true;
		}
		//SELECT user_id,name,level,channel_id,log_type,goods_id,operate_before,operate_after,operate_involve,operate_action,operate_time FROM log_tbl WHERE user_id = 447 and log_type = 12 ORDER BY operate_time DESC LIMIT 20,23
		std::string strSql = "SELECT user_id,name,level,channel_id,log_type,goods_id,operate_before,operate_after,operate_action,operate_way,operate_time FROM log_tbl ";//operate_involve
		if (isWhere)
			strSql.append("WHERE ");

		if (request->m_unType > 0)
			strSql.append("log_type = ").append(IntToString(request->m_unType));
		if (request->m_unUserID > 0)
			strSql.append("user_id = ").append(IntToString(request->m_unUserID));
		if (request->m_unLevel > 0)
			strSql.append("level = ").append(IntToString(request->m_unLevel));
		if (request->m_goodsID > 0)
			strSql.append("goods_id = ").append(IntToString(request->m_goodsID));
		if (request->m_op_action > 0)
			strSql.append("operate_action = ").append(IntToString(request->m_op_action));
		
		strSql.append("ORDER BY operate_time DESC LIMIT ").append(IntToString(request->m_pageNum * MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT)).append(",").append(IntToString(request->m_pageNum*MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT + MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT));
		
		char tmp_sql[1024];
		ZeroVar(tmp_sql);
		UINT32 iLen = strSql.size() > 1023 ? 1023 : strSql.size();
		ACE_OS::memcpy(tmp_sql, strSql.c_str(), iLen);


		prep_stmt = db_con->prepareStatement(tmp_sql);
		if(prep_stmt == NULL)
		{
			db_con->close();
			delete db_con;
			return false;
		}

		ResultSet * php_res = prep_stmt->executeQuery();
		if(php_res == NULL)
		{
			prep_stmt->close();
			delete prep_stmt;

			db_con->close();
			delete db_con;
			return false;
		}
		
		//delete 

		while(php_res->next())
		{
			response.m_logInfoItem[response.m_unCount].m_unUserID = php_res->getInt("user_id"); 
			set_name(php_res->getString("name"), response.m_logInfoItem[response.m_unCount].m_name, MAX_CHARACTER_LENGTH);
			response.m_logInfoItem[response.m_unCount].m_unLevel = php_res->getInt("level"); 
			response.m_logInfoItem[response.m_unCount].m_unChannel = php_res->getInt("channel_id"); 
			response.m_logInfoItem[response.m_unCount].m_unType = (enum_LOG_TYPE)php_res->getInt("log_type");
			response.m_logInfoItem[response.m_unCount].m_goodsID = php_res->getInt("goods_id"); 
			response.m_logInfoItem[response.m_unCount].m_op_before = php_res->getInt("operate_before"); 
			response.m_logInfoItem[response.m_unCount].m_op_after = php_res->getInt("operate_after"); 
			//response.m_logInfoItem[response.m_unCount].m_op_involve = php_res->getInt("operate_involve"); 
			response.m_logInfoItem[response.m_unCount].m_op_action= (enum_LOG_ACTION)php_res->getInt("operate_action");
			set_name(php_res->getString("operate_way"), response.m_logInfoItem[response.m_unCount].m_op_way, MAX_CHARACTER_LENGTH);
			response.m_logInfoItem[response.m_unCount].m_op_time= php_res->getInt("operate_time");
			
			if (response.m_unCount >= MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT - 1)
				break;
			else
				response.m_unCount ++;
		}

		php_res->close();
		delete php_res;

		prep_stmt->close();
		delete prep_stmt;

		db_con->close();
		delete db_con;

	}
	catch (SQLException& e)
	{
		printf("sql error:%s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
	catch (std::exception * e)
	{
		printf("------------------%s\n",e->what());
	}

	return true;
}
*/
std::string DBLogMgr::IntToString( int nv )
{
	// int 转 string
	std::stringstream ss;
	ss<<nv;
	return ss.str();
}

int DBLogMgr::set_name(SQLString str, char *dest, int len)
{
	const char *t = str.c_str();
	if(t == NULL)
	{
		dest[0] = '\0';
	}
	else
	{
		ACE_OS::strncpy(dest, t, len);
		dest[len] = '\0';
	}

	return 0;
}

bool DBLogMgr::read_db_message(Connection *db_conn, const MsgDBAdminLogInfoRequest &request)
{
	MsgDBAdminLogInfoResponse response;
	response.m_unCount = 0;
	PreparedStatement *prep_stmt = NULL;
	try
	{
		if(db_conn == NULL)
		{
			printf("critical php log db error, db log connection is null\n");
			return false;
		}

		bool isWhere = false;
		if (request.m_unType>0 || request.m_unUserID>0 || request.m_unLevel>0 || request.m_goodsID>0 || request.m_op_action>0 )
		{
			isWhere =true;
		}
		//SELECT user_id,name,level,channel_id,log_type,goods_id,operate_before,operate_after,operate_involve,operate_action,operate_time FROM log_tbl WHERE user_id = 447 and log_type = 12 ORDER BY operate_time DESC LIMIT 20,23
		std::string strSql = "SELECT user_id,name,level,channel_id,log_type,goods_id,operate_before,operate_after,operate_action,operate_way,operate_time FROM log_tbl ";//operate_involve
		if (isWhere)
			strSql.append("WHERE ");

		bool isIn = false;
		if (request.m_unType > 0)
		{
			isIn = true;
			strSql.append(" log_type = ").append(IntToString(request.m_unType));
		}
		if (request.m_unUserID > 0)
		{
			if (isIn)
				strSql.append(" and ");
			isIn = true;
			strSql.append(" user_id = ").append(IntToString(request.m_unUserID));
		}
		if (request.m_unLevel > 0)
		{
			if (isIn)
				strSql.append(" and ");
			isIn = true;
			strSql.append(" level = ").append(IntToString(request.m_unLevel));
		}
		if (request.m_goodsID > 0)
		{
			if (isIn)
				strSql.append(" and ");
			isIn = true;
			strSql.append(" goods_id = ").append(IntToString(request.m_goodsID));
		}
		if (request.m_op_action > 0)
		{
			if (isIn)
				strSql.append(" and ");
			isIn = true;
			strSql.append(" operate_action = ").append(IntToString(request.m_op_action));
		}

		strSql.append(" ORDER BY operate_time DESC LIMIT ").append(IntToString(request.m_pageNum * MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT)).append(",")
			.append(IntToString(request.m_pageNum*MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT + MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT));

		char tmp_sql[1024];
		ZeroVar(tmp_sql);
		UINT32 iLen = strSql.size() > 1023 ? 1023 : strSql.size();
		ACE_OS::memcpy(tmp_sql, strSql.c_str(), iLen);


		prep_stmt = db_conn->prepareStatement(tmp_sql);
		if(prep_stmt == NULL)
		{
			return false;
		}

		ResultSet * php_res = prep_stmt->executeQuery();
		if(php_res == NULL)
		{
			prep_stmt->close();
			delete m_prep_stmt;
			return false;
		}

		//delete 

		while(php_res->next())
		{
			response.m_logInfoItem[response.m_unCount].m_unUserID = php_res->getInt("user_id"); 
			set_name(php_res->getString("name"), response.m_logInfoItem[response.m_unCount].m_name, MAX_CHARACTER_LENGTH);
			response.m_logInfoItem[response.m_unCount].m_unLevel = php_res->getInt("level"); 
			response.m_logInfoItem[response.m_unCount].m_unChannel = php_res->getInt("channel_id"); 
			response.m_logInfoItem[response.m_unCount].m_unType = (enum_LOG_TYPE)php_res->getInt("log_type");
			response.m_logInfoItem[response.m_unCount].m_goodsID = php_res->getInt("goods_id"); 
			response.m_logInfoItem[response.m_unCount].m_op_before = php_res->getInt("operate_before"); 
			response.m_logInfoItem[response.m_unCount].m_op_after = php_res->getInt("operate_after"); 
			//response.m_logInfoItem[response.m_unCount].m_op_involve = php_res->getInt("operate_involve"); 
			response.m_logInfoItem[response.m_unCount].m_op_action= (enum_LOG_ACTION)php_res->getInt("operate_action");
			set_name(php_res->getString("operate_way"), response.m_logInfoItem[response.m_unCount].m_op_way, MAX_CHARACTER_LENGTH);
			response.m_logInfoItem[response.m_unCount].m_op_time= php_res->getInt("operate_time");

			if (response.m_unCount >= MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT - 1)
				break;
			else
				response.m_unCount ++;
		}


		php_res->close();
		delete php_res;

		prep_stmt->close();
		delete prep_stmt;

		if (m_dbuserHandlerCallBack)
			((DBUserHandler *)m_dbuserHandlerCallBack)->SendAdminLogItem(response,request.m_srcAdr);
	}
	catch (SQLException& e)
	{
		printf("sql error:%s:%d:%s\n", e.getSQLStateCStr(), e.getErrorCode(),e.what());
	}
	catch (std::exception * e)
	{
		printf("------------------%s\n",e->what());
	}

	return true;
}
