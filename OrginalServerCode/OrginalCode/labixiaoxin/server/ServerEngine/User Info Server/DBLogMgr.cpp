#include "DBLogMgr.h"
#include "ace\Thread_Manager.h"
#include "..\Base\Service\BaseService.h"
#include "..\GameBase\Protocol\DBProtocol.h"
#include <sstream>
#include <exception>
#include <limits>
#include "..\GameBase\Common\GameUtils.h"
#include "..\ace\Date_Time.h"
#include "cppconn\exception.h"
#include "..\DB Server\ConnectionPool.h"
#include "InfoDBMgr.h"

DBLogMgr::DBLogMgr()
{
	m_nThreadGroupID = -1;
	ZeroVar(m_srcAdr);
	m_dbuserHandlerCallBack = NULL;
	ZeroVar(m_dealList);
	m_len = 0;
	m_index = 0;
	m_fp = NULL;
	m_level_time_index = MAX_LIVEL_TIME_INDEX;//默认做一次
	m_online_time_index = 0;
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
	if (m_queueDBLog.size() >= LIMIT_MSG_QUE_SIZE)
	{
		printf("m_queueDBLog size out of limit.\n");
		while(m_queueDBLog.size() >= MAX_MSG_QUE_SIZE)
		{
			printf("log wait!\n");
			Sleep(10);
		}
	}

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
// 	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_DBLogLock);
// 	m_queueDBadminLog.push(*msg);
	return 0;
}

bool DBLogMgr::Read_db_log()
{
	if (m_queueDBLog.empty())
	{
		return false;
	}
	else
	{
		m_len = 0;
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_DBLogLock);
		for(int i=0;i<MAX_LIST_QUE;i++)
		{
			if (!m_queueDBLog.empty())
			{
				m_dealList[m_len] = m_queueDBLog.front();
				m_queueDBLog.pop();
				++m_len;
			}
			else
				break;
		}

		return true;
	}
}

ACE_THR_FUNC_RETURN DBLogMgr::do_execute(void *opParam)
{
	DBLogMgr *mgr = (DBLogMgr *)opParam;

	ACE_UINT32 _time_now = GameUtils::get_utc();
	ACE_UINT32 _second = 0;
	int _n = 0;
	while(1)
	{
		while(_n  < 10)//条件变量
		{
			if (mgr->Empty())
			{
				Sleep(1000);
			}
			else
			{
				mgr->insert_db_message();
				break;
			}
			_n++;
		}
		_n = 0;

		_second =GameUtils::get_utc() - _time_now;
		if (_second > 0)
		{
			_time_now = GameUtils::get_utc();
			mgr->m_level_time_index += _second;
			//处理等级分布
			mgr->DealLevelDistributed();

			//同时在线
			mgr->m_online_time_index += _second;
			mgr->DealOnlineDistributed();
		}

		//mgr->m_con->commit();
	}

	return static_cast<ACE_THR_FUNC_RETURN>(0);
}

bool DBLogMgr::insert_db_message()
{
	if (OpenFile())
	{
		while(Read_db_log())
		{
			insert_list_to_File();
		}
		CloseFile();
	}

	return true;
}

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

	return true;
}

bool DBLogMgr::Empty()
{
	return m_queueDBLog.empty();
}

bool DBLogMgr::OpenFile()
{
	if (m_fp)
		CloseFile();

	_mkdir("log");
	char file_name[64];
	char day_str[32];
	ZeroVar(file_name);
	ZeroVar(day_str);
	GameUtils::get_current_day_str(day_str);
	ACE_Date_Time tvTime(ACE_OS::gettimeofday());
	ACE_OS::sprintf(day_str, "%02d-%02d-%02d-%02d-%02d", tvTime.year(), tvTime.month(), tvTime.day(),tvTime.hour(),tvTime.minute());

	ACE_OS::sprintf(file_name, "log/log-%s.log", day_str);
	m_fp = ACE_OS::fopen(file_name, "a");
	return m_fp;
}

void DBLogMgr::CloseFile()
{
	if(m_fp == NULL)
	{
		return;
	}

	ACE_OS::fclose(m_fp);
	m_fp = NULL;
}

void DBLogMgr::DealLevelDistributed()
{
	//m_level_time_index++;
	if (m_level_time_index >= MAX_LIVEL_TIME_INDEX)
	{
		m_level_time_index = 0;
		Connection * _con = InfoDBMgr::create_db_connection();
		if(_con == NULL)
		{
			printf("critical log db error, db log connection is null\n");
		}
		else
		{
			PreparedStatement *prep_stmt = NULL;
			prep_stmt = _con->prepareStatement("SELECT level,count(*) as _count FROM character_tbl GROUP BY level");
			if(prep_stmt == NULL)
			{
				return ;
			}

			ResultSet * php_res = prep_stmt->executeQuery();
			if(php_res == NULL)
			{
				prep_stmt->close();
				delete prep_stmt;
				return ;
			}

			LogItemInfo request;
			ZeroVar(request);
			ACE_UINT32 now = GameUtils::get_utc();

			if (OpenFile())
			{
				m_len = 0;
				while(php_res->next())
				{
					request.m_op_time = now;
					request.m_op_before = php_res->getInt("level"); 
					request.m_op_after = php_res->getInt("_count");
					request.m_unType = LOG_TYPE_Statistics;
					request.m_op_action = LOG_ACTION_level_count;
					request.SetOp_Way(_LOG_OP_WAY_level_count);

					m_dealList[m_len] = request;
					++m_len;

					if (m_len >= MAX_LIST_QUE )
					{
						insert_list_to_File();
						//ZeroVar(request);
						m_len = 0;
					}
				}

				if (m_len > 0)
				{
					insert_list_to_File();
				}

				CloseFile();
			}
			//delete

			php_res->close();
			delete php_res;

			prep_stmt->close();
			delete prep_stmt;

			_con->commit();
		}

		//断开数据库
		if(!_con)
		{
			try
			{
				_con->close();
				printf("delete log db succeed\n");
			}
			catch (std::exception &e)
			{
				printf("delete log db exception: %s\n",e.what());
			}

			delete _con;
			_con = NULL;
		}
	}
}

bool DBLogMgr::insert_list_to_File()
{
	char time_str[32];
	for (int i=0;i<m_len;i++)
	{
		ZeroVar(time_str);
		struct tm _tm;
		time_t _t = (time_t)m_dealList[i].m_op_time;
		gmtime_s(&_tm,&_t);
		_tm.tm_hour +=8;

		//ACE_UINT64 ret = m_dealList[i].m_op_time /** 1000000*/;
		ACE_Time_Value v((ACE_UINT64)m_dealList[i].m_op_time);
		ACE_Date_Time tvTime(v);

		sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", 
			tvTime.year(), tvTime.month(), tvTime.day(),tvTime.hour(),tvTime.minute(),tvTime.second());
		ACE_OS::fprintf(m_fp, "%d\001%d\001%d\001%d\001%d\001%d\001%d\001%d\001%d\001%d\001%s\001%s\001%s\001%d\001\n", 
			m_index, 
			m_dealList[i].m_unUserID, 
			m_dealList[i].m_unLevel,
			m_dealList[i].m_unChannel,
			m_dealList[i].m_unType,
			m_dealList[i].m_goodsID,
			m_dealList[i].m_op_before,
			m_dealList[i].m_op_after,
			m_dealList[i].m_op_involve,
			m_dealList[i].m_op_action,
			time_str,
			m_dealList[i].m_name,
			m_dealList[i].m_op_way,
			m_dealList[i].m_charactID);

		++m_index;
	}

	if ((m_index+MAX_LIST_QUE) > std::numeric_limits<int>::max())
		m_index = 0;

	return true;
}

void DBLogMgr::DealOnlineDistributed()
{
	if (m_online_time_index >= MAX_ONLINE_TIME_INDEX)
	{
		m_online_time_index = 0;

		LogItemInfo request;
		ZeroVar(request);
		ACE_UINT32 now = GameUtils::get_utc();


		if (OpenFile())
		{
			m_len = 0;

			request.m_op_time = now;
			request.m_op_before = 0; 
			request.m_op_after = BaseService::g_OnlineCount;
			request.m_unType = LOG_TYPE_Statistics;
			request.m_op_action = LOG_ACTION_Online_user_count;
			request.SetOp_Way(_LOG_OP_WAY_Online_user_count);

			m_dealList[m_len] = request;
			++m_len;
			insert_list_to_File();

			CloseFile();
		}

	}

}
