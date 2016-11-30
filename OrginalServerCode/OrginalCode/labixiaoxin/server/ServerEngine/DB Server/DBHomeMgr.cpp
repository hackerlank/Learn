#include "DBHomeMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\DB Server\ConnectionPool.h"
#include "..\Base\Service\BaseService.h"

//#define MAX_DB_HANDLER 100

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


DBHomeMgr::DBHomeMgr(ACE_UINT32 unID)
:DBHandlerMgr(unID)
{
	m_unMaxChild = 4096;

	m_unPCU = 0;
	m_ACU = 0;

	m_unCurrentTimes = 0;

	m_tLastReloadTime = m_tLastStatisticsTime = GameUtils::get_utc();

	m_serviceACUTimerHandler = NULL;
	init_timer();

	LoadACU();
	LoadPCU();
}

DBHomeMgr::~DBHomeMgr()
{
	uninit_timer();
}

//加载一个在线用户角色
BaseObj *DBHomeMgr::new_child_obj(ACE_UINT32 unID)
{
	return new DBHomeHandler(unID, this);
}


bool DBHomeMgr::init_timer()
{
	if (m_serviceACUTimerHandler == NULL)
	{
		if ((m_serviceACUTimerHandler = TIMER_MGR_INSTANCE::instance()->registerTimer(this, ACUtimerCallback, NULL, ACE_Time_Value(30, 0), ACE_Time_Value(600, 0))) == NULL)
		{
			return false;
		}
	}
	return true;
}

void DBHomeMgr::uninit_timer()
{
	if(m_serviceACUTimerHandler != NULL)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(m_serviceACUTimerHandler->m_lTimerID);
		delete m_serviceACUTimerHandler;
		m_serviceACUTimerHandler = NULL;
	}
}

void DBHomeMgr::ACUtimerCallback(void *p, long lTimerID)
{
// 	DBHomeMgr *pMgr = static_cast<DBHomeMgr *>(p);
// 	if (pMgr != NULL)
// 	{
// 		pMgr->DoACUStatistics();
// 	}
}

void DBHomeMgr::DoACUStatistics()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	int iCurrentOnlineAmount = get_obj_count();
	if (m_unPCU < iCurrentOnlineAmount)
	{
		m_unPCU = iCurrentOnlineAmount;
		SavePCU();
	}
	ACE_UINT32 unTotal = 0;
	for (ACE_UINT32 i=0;i<m_unCurrentTimes;++i)
	{
		unTotal += m_ACUList[i];
	}
	m_ACU = unTotal / (m_unCurrentTimes+1);

	time_t tCurrentTime = GameUtils::get_utc();
	if (GameUtils::get_day_different(tCurrentTime, m_tLastStatisticsTime) > 0)
	{
		m_unCurrentTimes = 0;
		m_unPCU = 0;
	}

	m_ACUList[m_unCurrentTimes++] = iCurrentOnlineAmount;

	m_tLastStatisticsTime = tCurrentTime;
	SaveACU();
}

int DBHomeMgr::LoadStatistics(const ACE_UINT32 dwType, const char *strDate,ACE_UINT32 * paramList)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	int iData = 0;
	//ACE_UINT32 tCurrentTime = GameUtils::get_utc();
	//if (m_tLastReloadTime + Statistics_Reload_Interval < tCurrentTime)
	//{
		//m_tLastReloadTime = tCurrentTime;
	if (dwType == E_Statistics_ACU)
	{
		ACE_UINT32 unTotal = 0;
		for (ACE_UINT32 i=0;i<m_unCurrentTimes;++i)
		{
			unTotal += m_ACUList[i];
		}
		iData = unTotal / (m_unCurrentTimes+1);
		return iData;
	}
	else if (dwType == E_Statistics_PCU)
	{
		return m_unPCU;
	}
	Connection *db_conn = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	sql::ResultSet *db_res = NULL;
	sql::PreparedStatement *prep_stmt = NULL;
	try
	{
		switch (dwType)
		{
		case E_Statistics_Character_Amount:
			{
				prep_stmt = db_conn->prepareStatement("select count(1) from character_tbl ");
			}break;
		case E_Statistics_Daily_Online:
		case E_Statistics_Nextday_Remain:
		case E_Statistics_3days_Remain:
		case E_Statistics_7days_Remain:
		case E_Statistics_15days_Remain:
		case E_Statistics_30days_Remain:
		//case E_Statistics_PCU:
			{
				prep_stmt = db_conn->prepareStatement("select digital_data from statistics_info_tbl where record_time = DATE(?) AND statistics_type = ?");
				prep_stmt->setDateTime(1, strDate);
				prep_stmt->setInt(2, dwType);
			}break;

		//case E_Statistics_ACU:
		//	{
		//		prep_stmt = db_conn->prepareStatement("select blob_data from statistics_info_tbl where DATE(record_time) = DATE(?) AND statistics_type = 7")
		//	}break;
		case  E_Statistics_Tutorial://新手引导
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				//ACE_UINT32 day = std::atoi(strDate);
				v *= paramList[1]; 
				prep_stmt = db_conn->prepareStatement("select count(user_id) from character_tbl WHERE tutorial_flag > 1024 AND last_login_time-create_time < ?");
				prep_stmt->setInt(1, v);
			}
			break;
		case E_Statistics_Effect_Character://指定时间段内达到某一等级的用户的数量
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				//ACE_UINT32 day = std::atoi(strDate);
				v *= paramList[1]; 
				prep_stmt = db_conn->prepareStatement("select count(user_id) from character_tbl WHERE level = ?  AND last_login_time-create_time < ?");
				prep_stmt->setInt(1, paramList[2]);//等级
				prep_stmt->setInt(2, v);//时间段
			}
			break;
		case E_Statistics_Effect_Register://时间区间查询目前累计注册账号
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				v *= paramList[1]; 
				ACE_INT32 day = GameUtils::Get_Day_from_str(strDate);//以当前时间为起点查询
				prep_stmt = db_conn->prepareStatement("select count(user_id) from character_tbl WHERE create_time > ? and create_time < ?");
				prep_stmt->setInt(1, day);//时间起点
				prep_stmt->setInt(2, day + v);//时间段
			}
			break;
		case E_Statistics_Effect_Login://可设定时间区间查询目前累计登陆账号，可查询时间区间内登陆变化曲线
			{
				ACE_UINT32 v = 24L * 60L * 60L;
				v *= paramList[1]; 
				ACE_INT32 day = GameUtils::Get_Day_from_str(strDate);//以当前时间为起点查询
				prep_stmt = db_conn->prepareStatement("select count(user_id) from character_tbl WHERE last_login_time > ? and last_login_time < ?");
				prep_stmt->setInt(1, day);//时间起点
				prep_stmt->setInt(2, day + v);//时间段
			}
			break;

		default:
			{
				sql::ResultSet * db_res = NULL; 
				destroy_db_res(prep_stmt,db_res);
				return iData;
			}//break;
		}

		if (prep_stmt == NULL)
		{
			printf("get_statistical_data [%d] failed2!\n", dwType);
			return iData;
		}
		db_res = prep_stmt->executeQuery();

		if (db_res)//add by xxj 2015/05/14 14:49:06 
		{
			while(db_res->next())
			{
				iData = db_res->getInt(1);
			}
		}
	}
	catch(SQLException &e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadStatistics sql exception type[%u]",__FILE__, __LINE__, dwType);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	catch (...)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadStatistics data handle exception type[%u]",__FILE__, __LINE__, dwType);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}

	destroy_db_res(prep_stmt, db_res);
	db_conn->commit();
	CONNECTION_POOL_INSTANCE::instance()->release_connection(db_conn);
	return iData;

}

void DBHomeMgr::LoadACU()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	Connection *db_conn = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	sql::PreparedStatement *prep_stmt = NULL;
	ResultSet *db_res=NULL;
	try
	{
		prep_stmt = db_conn->prepareStatement("select blob_data from statistics_info_tbl where record_time = CURRENT_DATE() AND statistics_type = 7");
	
		if (prep_stmt == NULL)
		{
			printf("get_statistical_data failed2!\n");
			return;
		}
		db_res = prep_stmt->executeQuery();

		if (db_res)//add by xxj 2015/05/14 14:49:42 
		{
			while(db_res->next())
			{
				std::istream *stream = db_res->getBlob("blob_data");
				m_unCurrentTimes = 0;
				memset(m_ACUList, 0, Statistics_ACU_Num * sizeof(ACE_UINT32));
				while((m_unCurrentTimes < Statistics_ACU_Num) && stream->read((char *)&m_ACUList[m_unCurrentTimes], sizeof(ACE_UINT32)))
				{
					++m_unCurrentTimes;
				}
			}
		}
	}
	catch(SQLException &e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadACU sql exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	catch (...)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadACU data handle exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(prep_stmt, db_res);
	db_conn->commit();
	CONNECTION_POOL_INSTANCE::instance()->release_connection(db_conn);
}

void DBHomeMgr::LoadPCU()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	Connection *db_conn = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	sql::PreparedStatement *prep_stmt = NULL;
	ResultSet *db_res = NULL;
	try
	{
		prep_stmt = db_conn->prepareStatement("select digital_data from statistics_info_tbl where record_time = CURRENT_DATE() AND statistics_type = 8");

		if (prep_stmt == NULL)
		{
			printf("get_statistical_data failed2!\n");
			return;
		}
		db_res = prep_stmt->executeQuery();

		if (db_res)//add by xxj 2015/05/14 14:48:28 
		{
			while(db_res->next())
			{
				m_unPCU = db_res->getInt(1);
			}
		}
	}
	catch(SQLException &e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadPCU sql exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	catch (...)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:LoadPCU data handle exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	destroy_db_res(prep_stmt,db_res);
	db_conn->commit();
	CONNECTION_POOL_INSTANCE::instance()->release_connection(db_conn);
}

void DBHomeMgr::SavePCU()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	Connection *db_conn = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	sql::PreparedStatement *prep_stmt = db_conn->prepareStatement("insert into statistics_info_tbl(statistics_type, digital_data, record_time) VALUES(8, ?, CURRENT_DATE())  ON DUPLICATE KEY UPDATE digital_data=?;");
	if(prep_stmt == NULL)
	{
		return;
	}
	prep_stmt->setInt(1, m_unPCU);
	prep_stmt->setInt(2, m_unPCU);
	try
	{
		prep_stmt->executeUpdate();
	}
	catch(SQLException &e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:SavePCU sql exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	catch (...)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:SavePCU data handle exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}

	sql::ResultSet * db_res = NULL; 
	destroy_db_res(prep_stmt,db_res);
	db_conn->commit();
	CONNECTION_POOL_INSTANCE::instance()->release_connection(db_conn);
}


void DBHomeMgr::SaveACU()
{	
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	Connection *db_conn = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	sql::PreparedStatement *prep_stmt = db_conn->prepareStatement("CALL do_ACU_statistics(?, ?);");
	if(prep_stmt == NULL)
	{
		return;
	}

	DBDataBuf data((char *)&m_ACUList, sizeof(ACE_UINT32) * m_unCurrentTimes);
	std::istream is(&data);
	prep_stmt->setInt(1, m_ACU);
	prep_stmt->setBlob(2, &is);
	try
	{
		prep_stmt->executeUpdate();
	}
	catch(SQLException &e)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:SaveACU sql exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}
	catch (...)
	{
		CLogBase *pLog = BaseService::GetLogInstance();
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:SaveACU data handle exception",__FILE__, __LINE__);
		pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
	}

	sql::ResultSet * db_res = NULL; 
	destroy_db_res(prep_stmt,db_res);
	db_conn->commit();
	CONNECTION_POOL_INSTANCE::instance()->release_connection(db_conn);
}


void DBHomeMgr::destroy_db_res(sql::PreparedStatement *& prep_stmt, sql::ResultSet *& db_res)
{
	if(db_res != NULL)
	{
		try
		{
			db_res->close();
		}
		catch(SQLException& e) 
		{
		}

		delete db_res;
		db_res = NULL;
	}
	if(prep_stmt != NULL)
	{
		try
		{
			prep_stmt->close();
		}
		catch(SQLException& e) 
		{
		}

		delete prep_stmt;
		prep_stmt = NULL;
	}
}