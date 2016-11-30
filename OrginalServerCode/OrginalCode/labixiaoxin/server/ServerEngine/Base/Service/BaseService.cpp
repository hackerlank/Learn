#include "BaseService.h"
#include "ace\Message_Block.h"

#include "..\Communication\CommunicationMgr.h"
#include "..\TimerMgr\TimerMgr.h"
//#include "ServiceTimerHandler.h"
#include "..\Protocol\ServiceProtocol.h"
//#include "..\Task\TaskManager.h"
#include "ace\INET_Addr.h"

#include "ace\Proactor.h"

#include "../Log/AsyncLogging.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif
#include "../../GameBase/Common/GameUtils.h"

ACE_UINT32 BaseService::g_msg_count = 0;
ACE_UINT32 BaseService::g_msg_time = 0;
ACE_UINT32 BaseService::g_OnlineCount = 0;




BaseService *BaseService::m_instance = NULL;

CLogBase *BaseService::m_pLogService = NULL;

/*
static void ServiceTimerCallback(long lTimerID)
{
	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, sizeof(MsgServiceTimer), SERVICE_MESSAGE_TYPE_TIMER, 0, 0, 0, 0, 0, 0, 0) == -1)
	{
		return;
	}

	MsgServiceTimer *p = (MsgServiceTimer *)msgInfo.body;
	p->lTimerID = lTimerID;

	BaseService::instance()->put(msgInfo.msg);

	return;
}
*/

BaseService *BaseService::instance()
{
	return m_instance;
}

CLogBase *BaseService::GetLogInstance()
{
	return m_pLogService;
}

ACE_UINT32 BaseService::getServiceDaemonID()
{
	ACE_INET_Addr *the_addr_array;
	size_t count = 0;

	int rc = ACE::get_ip_interfaces (count , the_addr_array);

	int i = 0;
	ACE_UINT32 unIP;

	if(count > 0)
	{
		unIP = the_addr_array->get_ip_address();
		delete[] the_addr_array;

		return getServiceDaemonID(unIP);
	}

	delete[] the_addr_array;

	return 0;
}

ACE_UINT32 BaseService::getServiceDaemonID(ACE_UINT32 unIP)
{
	return 0;
}

BaseService::BaseService()
:ServiceObj(0)
{
	//m_unServiceID = 0;
	m_serviceDefaultTimerHandler = NULL;
	m_nReactorThreadID  = -1;

	m_bStopFlag = false;

	m_bStopService = false;

	this->msg_queue()->high_water_mark(0xA00000);
	this->msg_queue()->low_water_mark(0xA00000);
}

BaseService::~BaseService()
{

}

int BaseService::Startup(int argc, ACE_TCHAR **argv)
{
	m_instance = this;

	

	//setActive(1);

	TIMER_MGR_INSTANCE::instance()->open();
	//COMMUNICATION_MGR_INSTANCE::instance()->startup(this->msg_queue(), TEST_SERVICE_ADDRESS, 1000, 1);
	
	this->activate();
	this->wait();

	return 0;
}

//int BaseService::Startup(ACE_UINT32 unServiceID, ACE_UINT32 unServicePort, ACE_UINT32 bServiceMgr)
int BaseService::Startup(char *serviceName)
{
	//load config
	SERVICE_CONFIG_MGR_INSTANCE::instance()->load_config(0, "config/service_config.xml");

	m_instance = this;

	m_ownServiceInfo = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance(serviceName);

	if(m_ownServiceInfo == NULL)
	{
		return -1;
	}

	m_unServicePort = m_ownServiceInfo->lanAdr.port;
	m_unID = m_ownServiceInfo->unID;
	m_bServiceMgr = m_ownServiceInfo->isServiceMgr;

	set_stop_flag(false);

	int ret = Startup_i();

	if(ret == 0)
	{
		while(!this->is_stop())
		{
			ACE_OS::sleep(1);
		}
	}
	
	Shutdown();

	this->wait();

	ACE_Proactor::close_singleton();

	//ACE_OS::sleep(10);

	return 0;
}

int BaseService::Startup_i()
{
	if(start_reator() == -1)
	{
		return -1;
	}

	m_pLogService = new CAsyncLog(m_ownServiceInfo->name);
	if (m_pLogService == NULL)
	{
		return -1;
	}

	if (ACE_Thread_Manager::instance()->spawn_n(1, activateLogThread, NULL) == -1)//启动日志线程
	{
		return -1;
	}

	if(m_StdinHandler.hook_stdin() == -1)
	{
		return -1;
	}

	if(TIMER_MGR_INSTANCE::instance()->open() == -1)
	{
		return -1;
	}

	if(COMMUNICATION_MGR_INSTANCE::instance()->startup(this->msg_queue(),this->msg_queue(), m_ownServiceInfo->lanAdr.ip, m_unServicePort, m_bServiceMgr) == -1)//开始主线程
	{
		return -1;
	}

	if(this->obj_init() == -1)
	{
		return -1;
	}

	if(startDefaultTimer() == -1)
	{
		return -1;
	}

	if(this->activate() == -1)
	{
		return -1;
	}

	return 0;
}

void BaseService::Shutdown()
{
	stopDefaultTimer();
	COMMUNICATION_MGR_INSTANCE::instance()->shutdown();
	TIMER_MGR_INSTANCE::instance()->close();
	end_reator();
}

void BaseService::quit_service()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ACTIVE_ADAPTER_MAP_ITERATOR iter(m_adapterMap);
	BaseAdapter *pAdapter;

	for(iter = m_adapterMap.begin(); iter != m_adapterMap.end(); iter++)
	{
		pAdapter = (*iter).int_id_;

		if(pAdapter == NULL)
		{
			continue;
		}

		pAdapter->closeAdapter();
	}

	set_destroy(true);;
}

void BaseService::stop_service()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_bStopService)
	{
		return;
	}

	ACTIVE_ADAPTER_MAP_ITERATOR iter(m_adapterMap);
	BaseAdapter *pAdapter;

	for(iter = m_adapterMap.begin(); iter != m_adapterMap.end(); iter++)
	{
		pAdapter = (*iter).int_id_;

		if(pAdapter == NULL)
		{
			continue;
		}

		pAdapter->closeAdapter();
	}

	m_bStopService = true;
}



void BaseService::obj_fini()
{
	ServiceObj::obj_fini();
	this->msg_queue()->close();
}

bool BaseService::should_destroy()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(ServiceObj::should_destroy() && m_adapterMap.current_size() == 0)
	{
		return true;
	}

	return false;
}


int BaseService::startDefaultTimer()
{
	if(m_serviceDefaultTimerHandler != NULL)
	{
		return 0;
	}
	

	m_serviceDefaultTimerHandler = activateTimer(1, 0);
	
	if(m_serviceDefaultTimerHandler == NULL)
	{
		return -1;
	}

	return 0;
}

void BaseService::stopDefaultTimer()
{
	if(m_serviceDefaultTimerHandler != NULL)
	{
		deactivateTimer(m_serviceDefaultTimerHandler);
		delete m_serviceDefaultTimerHandler;
	}
	m_serviceDefaultTimerHandler = NULL;
}

void BaseService::service_obj_timer_callback()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ServiceObj::service_obj_timer_callback();
	//遍历所有adapter
	ACTIVE_ADAPTER_MAP_ITERATOR iter(m_adapterMap);
	BaseAdapter *pObj;

	ACE_UINT32 adapterList[MAX_ADAPTER_COUNT];
	int count = 0;

	for(iter = m_adapterMap.begin(); iter != m_adapterMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		if(pObj->m_unObjStatus == SERVICE_OBJ_DESTROY && pObj->hasDestoryed())
		{
			adapterList[count] = pObj->m_unID;
			count ++;
		}

		pObj->service_obj_timer_callback();
	}

	for(int i = 0;i < count;i ++)
	{
		if(m_adapterMap.unbind(adapterList[i], pObj) == 0)
		{
			delete pObj;
		}
	}
}

int BaseService::addAdapter(BaseAdapter *obj, void *arg, ACE_UINT32 unArgLen)
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_adapterMap.bind(obj->m_unID, obj) != 0)
	{
		return -1;
	}

	if(obj->obj_init(arg, unArgLen) == -1)
	{
		return -1;
	}

	return 0;
}

void BaseService::removeAdapter(ACE_INT32 unAdapterID)
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	BaseAdapter *obj = getAdapter(unAdapterID);

	if (obj)
	{
		if(m_adapterMap.unbind(obj->m_unID, obj) == 0)
		{
			//obj->fini();
			delete obj;
		}
	}

}

void BaseService::removeAllAdapter()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ACTIVE_ADAPTER_MAP_ITERATOR iter(m_adapterMap);
	BaseAdapter *pObj;

	for(iter = m_adapterMap.begin(); iter != m_adapterMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		//pObj->fini();
		delete pObj;
	}

	m_adapterMap.unbind_all();
}

BaseAdapter *BaseService::getAdapter(ACE_INT32 unAdapterID)
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	BaseAdapter *obj = NULL;

	if(m_adapterMap.find(unAdapterID, obj) == 0)
	{
		return obj;
	}

	return obj;
}

int BaseService::svc(void)//路由主循环入口
{
	ACE_Message_Block * pMessage;
	//int t_type;
	MessageInfo msgInfo;
	MsgServiceTimer *pTimerInfo;
	//RootObj *obj;
	ServiceObj *sObj;
	printf("----start working!\n");

	while(1)
	{
// 		__try
// 		{
			if(this->getq(pMessage) == -1)
			{
				break;
			}
			g_msg_count = this->msg_queue()->message_count();

			if(parseMsg(msgInfo, pMessage) == 0)
			{
				if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_TASK)
				{
					//TASK_MGR_INSTANCE::instance()->deal_task_msg(msgInfo);
				}
				else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_TIMER)//定时器
				{
					pTimerInfo = (MsgServiceTimer *)msgInfo.body;

					//缺省定时器，遍历所有的obj
					if(pTimerInfo->lTimerID == m_serviceDefaultTimerHandler->m_lTimerID)
					{
						service_obj_timer_callback();
					}
					else
					{
						//TIMER_MGR_INSTANCE::instance()->doTimeout(pTimerInfo->lTimerID);
						sObj = findServiceObj(msgInfo.s_head->desAdr);
						if(sObj != NULL)
						{
							sObj->service_timer(pTimerInfo->lTimerID);
						}
					}
				}
				else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_CTRL)
				{
					if(msgInfo.m_head->unType == MSG_SERVICE_CONSOLE_CMD)
					{
						MsgConsoleCmd *body = (MsgConsoleCmd *)msgInfo.body;
						body->cmd[MAX_CONSOLE_CMD_LENGTH - 1] = '\0';
						deal_console_cmd(body->cmd);
					}
					else if(msgInfo.m_head->unType == MSG_SERVICE_STOP_SERVICE)
					{
						stop_service();
					}
				}
				else
				{
					if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_DB_REQUEST_ACK)
					{
						/*printf("get db ack\n");*/
					}
					//printf("get message %d:%d\n", msgInfo.p_head->unType, msgInfo.m_head->unType);
					/*
					if(m_unID == TEST_LOGIN_SERVER_ID && msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
					{
					int t = 0;
					}
					else if(m_unID == GAME_SERVER_ID && msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
					{
					int tt = 0;
					}
					else if(m_unID == GAME_SERVER_ID && msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
					{
					int ttt = 0;
					}
					*/
					sObj = findServiceObj(msgInfo.s_head->desAdr);

					if(sObj != NULL)
					{
						sObj->m_unCurrentSig = msgInfo.i_head->unSig;
					}

					if(msgInfo.s_head->desAdr.unAdapterID != OBJ_ID_NONE && msgInfo.s_head->desAdr.unObjID != OBJ_ID_NONE)
					{
						if(sObj != NULL)
						{
							if(sObj->m_unObjStatus == SERVICE_OBJ_DESTROY || sObj->m_unObjStatus == SERVICE_OBJ_STATUS_NONE)
							{
								if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) == 0)
									//if(true)
								{
									send_msg_obj_reach_result(MSG_SERVICE_OBJ_UNREACHABLE, msgInfo.s_head->desAdr.unAdapterID, msgInfo.s_head->desAdr.unObjID, msgInfo.s_head->srcAdr, msgInfo.m_head->unPacketNO);
								}

							}
							else
							{
								if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) == 0)
									//if(true)
								{
									send_msg_obj_reach_result(MSG_SERVICE_OBJ_MSG_REACHED, msgInfo.s_head->desAdr.unAdapterID, msgInfo.s_head->desAdr.unObjID, msgInfo.s_head->srcAdr, msgInfo.m_head->unPacketNO);
								}

								sObj->obj_msg_callback(msgInfo);
							}
						}
						else
						{
							if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) == 0)
								//if(true)
							{
								send_msg_obj_reach_result(MSG_SERVICE_OBJ_UNREACHABLE, msgInfo.s_head->desAdr.unAdapterID, msgInfo.s_head->desAdr.unObjID, msgInfo.s_head->srcAdr, msgInfo.m_head->unPacketNO);
							}

						}
					}
					else
					{
						if(sObj != NULL)
						{
							sObj->obj_msg_callback(msgInfo);
						}
					}

					if(sObj != NULL)
					{
						sObj->m_unCurrentSig = 0;
					}
				}
			}

			pMessage->release();
//		}
// 		__except(puts("exception error"),1)
// 		{
// 			FILE *_fp;
// 			char file_name[64];
// 			char day_str[32];
// 			GameUtils::get_current_day_str(day_str);
// 			ACE_OS::sprintf(file_name, "loginfo/error-%s.txt",day_str);
// 			_fp = ACE_OS::fopen(file_name, "a");
// 			if (_fp)
// 			{
// 				GameUtils::get_current_time_str(day_str);
// 				ACE_OS::fprintf(_fp, "Memory crash %s\n", day_str);
// 				ACE_OS::fclose(_fp);
// 				_fp = NULL;
// 			}
// 			
// 			printf("memory error !!!!!!!!!!!!!!!\n");
// 		}
	}

	printf("svc quit error!\n");
	set_stop_flag(true);
	return 0;
}

void BaseService::send_msg_obj_reach_result(ACE_UINT32 unType, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ObjAdr &desAdr, ACE_UINT32 unPacketNo)
{
	MsgServiceObjInfo body;
	body.unAdapterID = unAdapterID;
	body.unObjID = unObjID;

	this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, unType, (char *)&body, sizeof(MsgServiceObjInfo), desAdr.unServiceID, OBJ_ID_NONE, OBJ_ID_NONE, unPacketNo);
}

void BaseService::deal_console_cmd(char *pCmd)
{
	printf("console cmd = %s\n", pCmd);

	if(ACE_OS::strcmp(pCmd, "exit") == 0)
	{
		quit_service();
	}
}

int __n = 0;
ServiceObj *BaseService::findServiceObj(ObjAdr &adr)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ServiceObj *obj = NULL;
	if(adr.unAdapterID == OBJ_ID_NONE)
	{
		obj = this;
	}
	else
	{
		BaseAdapter *adapter = NULL;
		if(m_adapterMap.find(adr.unAdapterID, adapter) == 0)
		{
			if(adr.unObjID == OBJ_ID_NONE)
			{
				obj = adapter;
			}
			else
			{
				obj = adapter->findObj(adr.unObjID);

				g_OnlineCount = adapter->get_obj_count();//在线人数

				++__n;
				if (__n > 1000)
				{
					printf("--------obj count:[%d]\n",adapter->get_obj_count());
					__n = 0;
				}
			}
		}
	}

	return obj;
}

int BaseService::close(u_long flags)
{
	if(ACE_OS::thr_equal(ACE_Thread::self (), this->last_thread ()))
	{
		//do the clean
	}

	return 0;
}

int BaseService::put (ACE_Message_Block * pMessage, ACE_Time_Value * pTimeValue)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);//先锁住
	return this->putq(pMessage, pTimeValue);
}

ACE_UINT32 BaseService::serviceID()
{
	return m_unID;
}

ACE_UINT32 BaseService::servicePort()
{
	return m_unServicePort;
}

void BaseService::servicePort(ACE_UINT32 unPort)
{
	m_unServicePort = unPort;
}

int BaseService::obj_msg_callback(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_CREATE_BASE_ADAPTER:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;
			}
			break;
		case MSG_REMOVE_BASE_ADAPTER:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;
			}
			break;
		case MSG_SERVICE_SHUTDOWN:
			{
				this->quit_service();
			}
			break;
		}
	}

	return ServiceObj::obj_msg_callback(msgInfo);
}

/*
long BaseService::startTimer(RootObj *owner, time_t sec, suseconds_t usec)
{
	ServiceTimerHandler *handler = new ServiceTimerHandler();

	if(handler == NULL)
	{
		return -1;
	}

	if(TIMER_MGR_INSTANCE::instance()->registTimer(handler, NULL, ACE_Time_Value(0, 0), ACE_Time_Value(sec, usec), handler->m_unTimerID) == -1)
	{
		delete handler;
		return -1;
	}

	if(m_TimerMap.bind(handler->m_unTimerID, owner) != 0)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(handler->m_unTimerID);
		return -1;
	}

	return handler->m_unTimerID;
}

void BaseService::resetTimer(long nTimerID, time_t sec, suseconds_t usec)
{
	TIMER_MGR_INSTANCE::instance()->reschedule(nTimerID, ACE_Time_Value(sec, usec));
}

void BaseService::stopTimer(long nTimerID)
{
	TIMER_MGR_INSTANCE::instance()->deleteTimer(nTimerID);
	m_TimerMap.unbind(nTimerID);
}
*/

void BaseService::setAddr(ObjAdr &addr)
{
	addr.unServiceID = m_unID;
	addr.unAdapterID = OBJ_ID_NONE;
	addr.unObjID = OBJ_ID_NONE;
}

int BaseService::start_reator()
{
	if(m_nReactorThreadID != -1)
	{
		return 0;
	}
	m_nReactorThreadID = ACE_Thread_Manager::instance()->spawn_n(1, activateReactor, NULL);

	if(m_nReactorThreadID == -1)
	{
		return -1;
	}

	return 0;
}

void BaseService::end_reator()
{
	if(m_nReactorThreadID == -1)
	{
		return;
	}
	ACE_Reactor::end_event_loop();

	ACE_Thread_Manager::instance()->wait_grp(m_nReactorThreadID);
	m_nReactorThreadID = -1;
}

ACE_THR_FUNC_RETURN BaseService::activateReactor(void *opParam)
{
	intptr_t nRc = ACE_Reactor::run_event_loop();

	while(ACE_Reactor::event_loop_done() != 1)
	{
		Sleep(1);
	}

	return static_cast<ACE_THR_FUNC_RETURN>(nRc);
}

ACE_THR_FUNC_RETURN BaseService::activateLogThread(void *opParam)
{
	CAsyncLog *pLog = dynamic_cast<CAsyncLog *>(m_pLogService);
	if (pLog != NULL)
	{
		while(1)
		{
			if (!pLog->Print())//开始打印
				Sleep(5);
		}
	}
	return 0;
}

bool BaseService::is_stop()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return m_bStopFlag;
}

void BaseService::set_stop_flag(bool flag)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	m_bStopFlag = flag;
}