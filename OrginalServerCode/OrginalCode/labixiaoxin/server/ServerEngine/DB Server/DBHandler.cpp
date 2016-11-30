#include "DBHandler.h"
#include "ace\Thread_Manager.h"
#include "..\Base\Service\BaseAdapter.h"

#include "..\GameBase\Protocol\ControlProtocol.h"
#include "ConnectionPool.h"

#include "DBHandlerMgr.h"

#include "DBAccessMgr.h"
#include "..\Base\Service\BaseService.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\ace\Date_Time.h"


DBHandler::DBHandler(ACE_UINT32 unID, BaseAdapter *parent)
:SubAdapterObj(unID, parent)
{
	//m_msg = NULL;
	m_requestQueue.high_water_mark(0xA00000);
	m_requestQueue.low_water_mark(0xA00000);

	m_bProcessDBRequest = false;

	m_unCurrentDBRequestType = 0;
	m_strHandlerName[0] = '\0';
}

DBHandler::~DBHandler()
{

}

int DBHandler::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	//m_msg = (ACE_Message_Block *)arg;

	return SubAdapterObj::obj_init(arg, unArgLen);
}

int DBHandler::start_create()
{
	int ret = SubAdapterObj::start_create();

	if(ret == -1)
	{
		return -1;
	}

	//start loading info
	m_bIsLoad = true;
	m_bLoadingSuccess = true;

	m_bProcessDBRequest = false;

	add_load_msg();
	next_db_request();

	return 0;
}

int DBHandler::start_destroy()
{
	printf("db handler start destroy\n");

	return SubAdapterObj::start_destroy();
}

bool DBHandler::hasCreated()
{
	return (!m_bIsLoad);
}

bool DBHandler::hasDestoryed()
{
	printf("db handler destroyed[ID=%d]\n", m_unID);
	return true;
}

bool DBHandler::has_db_request()
{
	if(m_bProcessDBRequest || !m_requestQueue.is_empty())
	{
		return true;
	}
	return false;
}

int DBHandler::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_DB_REQUEST)
	{
		/*printf("get db request[0x%08x]\n", m_unID);*/
		if(m_bLoadingSuccess)
		{
			update_cache(msgInfo);//先缓存消息
			cache_db_request(msgInfo.msg);//将消息存人数据库
		}
		else
		{
			//send fail msg
			MsgDBLoadFailedResponse response;

			response.nResult = 0;
			response.unCode = 0;

			this->sendMsg(SERVICE_MESSAGE_TYPE_DB_RESPONSE, MSG_DB_LOAD_FAILED,(char*)&response, sizeof(MsgDBLoadFailedResponse), msgInfo.s_head->srcAdr, 0, false);
		}
		send_request_ack(msgInfo.m_head->unType, msgInfo.s_head->srcAdr);
	}
	else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		if(msgInfo.m_head->unType == MSG_SERVICE_DB_HANDLER_NOTIFY)
		{
			notify_free();
		}
	}

	return 0;
}

int DBHandler::add_load_msg()
{
	ACE_Message_Block *msg = NULL;
	MessageInfo tmpInfo;

	if(allocMessageWithInfo(tmpInfo, 0, 0, 0, m_ParentAdapter->m_unID, m_unID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, 0) == 0)
	{
		msg = tmpInfo.msg;
	}
	else
	{
		return -1;
	}

	if(m_requestQueue.enqueue_tail(msg) == -1)
	{
		msg->release();
		return -1;
	}

	return 0;
}

int DBHandler::next_db_request()
{
	if(m_bProcessDBRequest)
	{
		return -1;
	}

	ACE_Message_Block *msg = NULL;
	/*
	if(m_bIsLoad)
	{
		//m_semaphore.release();
		//printf("%s release semaphore\n", m_strHandlerName);
		//add dummy msg
		MessageInfo tmpInfo;

		if(allocMessageWithInfo(tmpInfo, 0, 0, 0, m_ParentAdapter->m_unID, m_unID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, 0) == 0)
		{
			msg = tmpInfo.msg;
		}
	}
	else
	{
		if(!m_requestQueue.is_empty())
		{
			if(m_requestQueue.dequeue_head(msg) == -1)
			{
				msg = NULL;
			}
		}
	}
	*/
	if(!m_requestQueue.is_empty())
	{
		if(m_requestQueue.dequeue_head(msg) == -1)
		{
			msg = NULL;
		}
	}

	if(msg != NULL)
	{
		m_bProcessDBRequest = true;
		DB_ACCESS_MGR_INSTANCE::instance()->add_deal_msg(msg);
	}
	else
	{
		return -1;
	}

	return 0;
}

void DBHandler::cache_db_request(ACE_Message_Block *msg)
{
	if(m_requestQueue.enqueue_tail(msg->duplicate()) == -1)
	{
		//printf("dfsfsfs\n");
		msg->release();
	}
	
	next_db_request();

	DBHandlerMgr *handlerMgr = (DBHandlerMgr *)this->m_ParentAdapter;

	handlerMgr->increase_request_count();
}

bool DBHandler::should_destroy()
{
	if(SubAdapterObj::should_destroy() && !has_db_request())
	{
		return true;
	}

	return false;
}

void DBHandler::notify_free()
{
	m_bProcessDBRequest = false;

	if(m_bIsLoad)
	{
		m_bIsLoad = false;
		/*
		if(m_bLoadingSuccess)
		{
			m_bIsLoad = false;
		}
		else
		{
			this->setObjStatus(SERVICE_OBJ_DESTROY);
		}
		*/
	}
	else
	{
		DBHandlerMgr *handlerMgr = (DBHandlerMgr *)this->m_ParentAdapter;
		handlerMgr->decrease_request_count();
	}

	if(next_db_request() == -1)
	{
		//printf("ffsdfsfsdf\n");
	}
}

void DBHandler::send_notify_msg()
{
	if (m_ParentAdapter)
	{
		int ret = this->send_local_msg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_SERVICE_DB_HANDLER_NOTIFY, NULL, 0, m_ParentAdapter->m_unID, m_unID);

		if(ret == -1)
		{
			//printf("fdfss\n");
		}
	}

}


void DBHandler::destroy_db_res( PreparedStatement *& _prep_stmt,ResultSet *& _db_res )
{
	if(_prep_stmt != NULL)
	{
		try
		{
			_prep_stmt->close();
		}
		catch(SQLException& e) 
		{
		}

		delete _prep_stmt;
		_prep_stmt = NULL;
	}

	if(_db_res != NULL)
	{
		try
		{
			_db_res->close();
		}
		catch(SQLException& e) 
		{
		}

		delete _db_res;
		_db_res = NULL;
	}
}
// 
// void DBHandler::destroy_db_res()
// {
// 	if(m_prep_stmt != NULL)
// 	{
// 		try
// 		{
// 			m_prep_stmt->close();
// 		}
// 		catch(SQLException& e) 
// 		{
// 		}
// 
// 		delete m_prep_stmt;
// 		m_prep_stmt = NULL;
// 	}
// 
// 	if(m_db_res != NULL)
// 	{
// 		try
// 		{
// 			m_db_res->close();
// 		}
// 		catch(SQLException& e) 
// 		{
// 		}
// 
// 		delete m_db_res;
// 		m_db_res = NULL;
// 	}
// }

void DBHandler::do_db_msg(MessageInfo &msgInfo, char *send_buff)
{
	//printf("acquire connection[%d]\n", m_unID);
	Connection *con = CONNECTION_POOL_INSTANCE::instance()->acquire_connection();
	//printf("acquire connection success[%d]\n", m_unID);
	Savepoint *savept = NULL;

	if(con == NULL)
	{
		printf("critical db error, db connection is null\n");
		return;
	}

	db_send_buff = send_buff;

	try
	{
		//数据库操作
		try
		{
			if(this->m_bIsLoad)
			{
				this->do_db_load(con);
			}
			else
			{
				//设置save point
				m_unCurrentDBRequestType = msgInfo.m_head->unType;
				savept = con->setSavepoint("SAVEPT1");//创建一个事物点
				this->do_db_request(con, msgInfo);

//test
#ifdef _DEBUG
				static std::map<ACE_UINT32 , ACE_UINT32> g_testMsgMap;
				static int ___n = 0;
				g_testMsgMap[msgInfo.m_head->unType]++;
				___n++;
				if (___n>1000)
				{
					ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_ParentAdapter->m_mutex);
					___n = 0;
					_mkdir("logss");
					char file_name[64];
					char day_str[32];
					ZeroVar(file_name);
					ZeroVar(day_str);
					GameUtils::get_current_day_str(day_str);
					ACE_Date_Time tvTime(ACE_OS::gettimeofday());
					ACE_OS::sprintf(day_str, "%02d-%02d-%02d-%02d-%02d", tvTime.year(), tvTime.month(), tvTime.day(),tvTime.hour(),tvTime.minute());

					ACE_OS::sprintf(file_name, "logss/log-%s.log", day_str);
					FILE * m_fp = ACE_OS::fopen(file_name, "a");
					if(m_fp)
					{
						std::map<ACE_UINT32 , ACE_UINT32>::const_iterator c_it = g_testMsgMap.begin();
						while(c_it != g_testMsgMap.end())
						{
							ACE_OS::fprintf(m_fp, "%05x\t %d \n",c_it->first,c_it->second);

							c_it++;
						}

						ACE_OS::fclose(m_fp);
						m_fp = NULL;
					}

				}
#endif
/////////////////////

				//save point release
				if(savept != NULL)
				{
					con->releaseSavepoint(savept);
					delete savept;
					savept = NULL;
				}
			}
			
		}
		catch (SQLException &e)
		{
			//printf("sql error:%s:%d:%s[%s, 0x%08x]\n", e.getSQLStateCStr(), e.getErrorCode(),e.what(), m_strHandlerName, m_unCurrentDBRequestType);
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:sql error:%s:%d:%s[%s, 0x%08x]",__FILE__, __LINE__, e.getSQLStateCStr(), e.getErrorCode(),e.what(), m_strHandlerName, m_unCurrentDBRequestType);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
			try
			{
				//save point release
				if(savept != NULL)
				{
					con->rollback(savept);//事务回滚
					con->releaseSavepoint(savept);
					delete savept;
					savept = NULL;
				}
			}
			catch (SQLException &e)
			{

			}
		}
		catch(std::exception & e)
		{
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:sql errorEx:%s[%s, 0x%08x]",__FILE__, __LINE__,e.what(), m_strHandlerName, m_unCurrentDBRequestType);
			pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
			try
			{
				//save point release
				if(savept != NULL)
				{
					con->rollback(savept);//事务回滚
					con->releaseSavepoint(savept);
					delete savept;
					savept = NULL;
				}
			}
			catch (SQLException &e)
			{

			}
		}

		con->commit();

		//this->destroy_db_res();

		//printf("release connection[%d]\n", m_unID);
		CONNECTION_POOL_INSTANCE::instance()->release_connection(con);

		//printf("release connection success[%d]\n", m_unID);

		//send notify msg
		this->send_notify_msg();
	}
	catch(std::exception &e)
	{
		printf("fffuck!!\n");
	}
}

int DBHandler::set_name(SQLString str, char *dest, int len)
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

void DBHandler::send_request_ack(ACE_UINT32 unType, ObjAdr &desAdr)
{
	this->sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST_ACK, unType, NULL, 0, desAdr, 0, false);
}