#include "ServiceObj.h"

#include "..\Communication\CommunicationMgr.h"
#include "..\Protocol\ServiceProtocol.h"
#include "BaseService.h"
#include "ServiceMsgCtrl.h"

#include "SubAdapterStatusMgr.h"

#define MAX_LOADING_TIMEOUT 15	//15秒

//static char *Service_Obj_Loading_Task_Name = "Service Obj Loading Task";

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
DebugNewTracer DebugNewTrace;
#endif

ACE_UINT32 ServiceObj::m_TaskIDCursor = OBJ_ID_NONE + 1;

ServiceObj::ServiceObj(ACE_UINT32 unID)
{
	m_unID = unID;
	m_unNextObjStatus = m_unObjStatus = SERVICE_OBJ_STATUS_NONE;
	//m_currentDBRequest = NULL;
	//m_unDBSN = 0;
	m_bServiceObjActive = false;
	//m_bCreateWhenQueryFail = false;
	m_bNeedCreateStep = true;
	m_unWaitDBAckCount = 0;
	m_bDestroyFlag = false;
	m_unCurrentSig = 0;
	//SERVICE_TASK_FACTORY_INSTANCE::instance()->registerTask(Service_Obj_Loading_Task_Name, ObjLoadingTask::createObjLoadingTask);
}

ServiceObj::~ServiceObj()
{
	//resetObjLocationMap();
}

void ServiceObj::setAddr(ObjAdr &addr)
{
	addr.unServiceID = OBJ_ID_NONE;
	addr.unAdapterID = OBJ_ID_NONE;
	addr.unObjID = OBJ_ID_NONE;
	addr.unTaskID = OBJ_ID_NONE;
}

int ServiceObj::sendMsg(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ObjAdr &desAdr, ACE_UINT32 unPacketNo, bool bQuery)
{
	return sendMsg(unMsgType, unBodyType, strBody, unBodyLen, desAdr.unServiceID, desAdr.unAdapterID, desAdr.unObjID, unPacketNo, bQuery);
}

int ServiceObj::sendMsg(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ACE_UINT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unPacketNo, bool bQuery)
{
	MessageInfo msg;

	if(allocMessageWithInfo(msg, unBodyLen, unMsgType, unServiceID, unAdapterID, unObjID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unBodyType) == -1)
	{
		printf("no enough memory for send msg\n");
		return -1;
	}

	setAddr(msg.s_head->srcAdr);
	msg.m_head->unPacketNO = unPacketNo;
	msg.i_head->unSig = m_unCurrentSig;
	if(unBodyLen > 0)
	{
		memcpy(msg.body, strBody, unBodyLen);
	}

	int nRet = SERVICE_MSG_CTRL_INSTANCE::instance()->send_msg(msg, bQuery);

	if(nRet == -1)
	{
		printf("service msg ctrl instance send msg failed\n");
		msg.msg->release();
		return -1;
	}
	else if(nRet == 1)
	{
		if(SERVICE_MSG_CTRL_INSTANCE::instance()->pause_send_msg(unAdapterID, unObjID, OBJ_ID_NONE) == 0)
		{
			//printf("pause send failed\n");
			//query location
			//change by xxj 2015/06/14  21: 30:25 
			query_service_obj_location(unAdapterID, unObjID, 0);
			msg.msg->release();
		}
		else
		{
			msg.msg->release();
			return -1;
		}
	}

	return 0;
}

int ServiceObj::forward_msg(MessageInfo &msgInfo, ACE_UINT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	MessageInfo new_info = msgInfo;

	new_info.msg = msgInfo.msg->duplicate();

	new_info.s_head->desAdr.unServiceID = unServiceID;
	new_info.s_head->desAdr.unAdapterID = unAdapterID;
	new_info.s_head->desAdr.unObjID = unObjID;
	new_info.i_head->unSig = m_unCurrentSig;

	setAddr(new_info.s_head->srcAdr);

	int nRet = SERVICE_MSG_CTRL_INSTANCE::instance()->send_msg(new_info, true);

	if(nRet == -1)
	{
		new_info.msg->release();
		return -1;
	}
	else if(nRet == 1)
	{
		if(SERVICE_MSG_CTRL_INSTANCE::instance()->pause_send_msg(unAdapterID, unObjID, OBJ_ID_NONE) == 0)
		{
			//query location
			query_service_obj_location(unAdapterID, unObjID, 0);
			new_info.msg->release();
		}
		else
		{
			new_info.msg->release();
			return -1;
		}
	}

	return 0;
}

int ServiceObj::send_local_msg(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	MessageInfo msg;

	if(allocMessageWithInfo(msg, unBodyLen, unMsgType, OBJ_ID_NONE, unAdapterID, unObjID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unBodyType) == -1)
	{
		return -1;
	}

	setAddr(msg.s_head->srcAdr);
	msg.i_head->unSig = m_unCurrentSig;
	if(unBodyLen > 0)
	{
		memcpy(msg.body, strBody, unBodyLen);
	}

	if(COMMUNICATION_MGR_INSTANCE::instance()->send_local_msg(msg.msg) == -1)
	{
		msg.msg->release();
		return -1;
	}

	return 0;
}

/*
int ServiceObj::send_msg_with_query(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ObjAdr &desAdr, ACE_UINT32 unPacketNo)
{
	return 0;
}

int ServiceObj::send_msg_with_query(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ACE_UINT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unPacketNo)
{
	return 0;
}

int ServiceObj::send_msg_with_query(MessageInfo &msgInfo)
{
	return 0;
}
*/

int ServiceObj::obj_msg_callback(MessageInfo &msgInfo)
{
	if(!m_bServiceObjActive)
	{
		return OBJ_DEAL_MSG_SUCCESS;
	}

	if(msgInfo.s_head->desAdr.unTaskID != OBJ_ID_NONE)
	{
		dealTaskMsg(msgInfo);

		return OBJ_DEAL_MSG_SUCCESS;
	}

	//if it is db save result, then deal it
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_DB_REQUEST_ACK)
	{
		//printf("old db ack count = %d\n", m_unWaitDBAckCount);
		if(m_unWaitDBAckCount > 0)
		{
			m_unWaitDBAckCount --;
		}
		//printf("new db ack count = %d\n", m_unWaitDBAckCount);
	}
	else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_DB_RESPONSE)
	{
		//parse db result

		//int nResult, char *pData, ACE_UINT32 unSize

		//MsgDBResponse *body = (MsgDBResponse *)msgInfo.body;

		int nRet = deal_db_msg(msgInfo.m_head->unType, msgInfo.body);


		return OBJ_DEAL_MSG_SUCCESS;
	}
	/*
	else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_DB_SAVE_RESPONSE)
	{
		//parse save result
		MsgDBResponse *body = (MsgDBResponse *)msgInfo.body;

		if(body->unType == m_currentSaving->unType && body->unSN == m_currentSaving->unSN)
		{
			if(body->unRet == 0)
			{
				//success
				delete m_currentSaving;
				m_currentSaving = NULL;
			}
			else
			{
				m_SaveQueue.enqueue_head(m_currentSaving);
				m_currentSaving = NULL;
			}

			sendSaveRequest();
		}

		return OBJ_DEAL_MSG_SUCCESS;
	}
	*/
	else if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_OBJ_LOCATION)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_SERVICE_OBJ_UNREACHABLE:
			//call pause send to msg ctrl,if success，send location query
			{
				MsgServiceObjInfo *body = (MsgServiceObjInfo *)msgInfo.body;

				if(SERVICE_MSG_CTRL_INSTANCE::instance()->pause_send_msg(body->unAdapterID, body->unObjID, msgInfo.s_head->srcAdr.unServiceID) == 0)
				{
					//query location
					query_service_obj_location(body->unAdapterID, body->unObjID, 0);
				}
			}
			
			break;
		case MSG_SERVICE_OBJ_MSG_REACHED:
			//call ack to msg ctrl
			{
				MsgServiceObjInfo *body = (MsgServiceObjInfo *)msgInfo.body;
				
				SERVICE_MSG_CTRL_INSTANCE::instance()->ack(body->unAdapterID, body->unObjID, msgInfo.m_head->unPacketNO);
			}
			break;
		case MSG_SERVICE_QUERY_OBJ_LOCATION:
			//check if has this obj location,if false,ignore,else do query
			{
				MsgServiceObjLoaction *body = (MsgServiceObjLoaction *)msgInfo.body;

				//printf("get query obj location msg[%d, %d]\n", body->unAdapterID, body->unObjID);

				if(body->unAdapterID == ADAPTER_MAP_MGR)
				{
					int t = 0;
				}

				if(has_obj_location_info(body->unAdapterID, body->unObjID))
				{
					if(do_obj_location_query(body->unAdapterID, body->unObjID, msgInfo.s_head->srcAdr) == -1)
					{
						//send obj not found msg
						MsgServiceObjLoaction info;
						info.unServiceID = OBJ_ID_NONE;
						info.unAdapterID = body->unAdapterID;
						info.unObjID = body->unObjID;

						this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_ANSWER_OBJ_LOCATION, (char *)&info, sizeof(MsgServiceObjLoaction), msgInfo.s_head->srcAdr);
					}
				}
			}
			break;
		case MSG_SERVICE_ANSWER_OBJ_LOCATION:
			//call query to msg ctrl
			{
				MsgServiceObjLoaction *body = (MsgServiceObjLoaction *)msgInfo.body;

				if(body->unAdapterID == ADAPTER_DB_HOME_MGR)
				{
					int t = 0;
				}

				/*printf("get obj location[%d,%d,%d]\n", body->unAdapterID, body->unObjID, body->unServiceID);*/

				SERVICE_MSG_CTRL_INSTANCE::instance()->resume_send_msg(body->unAdapterID, body->unObjID, body->unServiceID);
			}
			break;
		case MSG_SERVICE_WANNA_CREATE_SERVICE_OBJ:
			//check if can send create command, if false ,ignore, else call create to obj status mgr
			{
				MsgServiceObjOP *body = (MsgServiceObjOP *)msgInfo.body;
				if(has_obj_location_info(body->unAdapterID, body->unObjID))
				{
					create_service_obj(body->unAdapterID, body->unObjID);
				}
			}
			break;
		case MSG_SERVICE_WANNA_DESTROY_SERVICE_OBJ:
			//call destroy to obj status mgr
			{
				MsgServiceObjOP *body = (MsgServiceObjOP *)msgInfo.body;

				destroy_service_obj(body->unAdapterID, body->unObjID);
			}
			break;
		case MSG_SERVICE_CREATE_SERVICE_OBJ_RESULT:
			{
				MsgServiceObjOP *body = (MsgServiceObjOP *)msgInfo.body;
				if(body->unAdapterID == ADAPTER_DB_HOME_MGR)
				{
					int t = 0;
				}
				deal_create_service_obj_result(body->nResult, body->unAdapterID, body->unObjID, msgInfo.s_head->srcAdr.unServiceID, body->unSN);

				//printf("get obj create result[%d,%d,%d]\n", body->unAdapterID, body->unObjID, msgInfo.s_head->srcAdr.unServiceID);
			}
			break;
		case MSG_SERVICE_DESTROY_SERVICE_OBJ_RESULT:
			{
				MsgServiceObjOP *body = (MsgServiceObjOP *)msgInfo.body;
				deal_destroy_service_obj_result(body->nResult, body->unAdapterID, body->unObjID, msgInfo.s_head->srcAdr.unServiceID, body->unSN);
			}
			break;
		}
	}

	return deal_msg(msgInfo);
}

void ServiceObj::query_service_obj_location(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unFlag)
{
	ObjAdr *queryAdr = SERVICE_MSG_CTRL_INSTANCE::instance()->get_query_service_id(unAdapterID, unObjID);

	if(queryAdr == NULL)
	{
		return;
	}

	MsgServiceObjLoaction body;

	body.unAdapterID = unAdapterID;
	body.unObjID = unObjID;
	body.unFlag = unFlag;

	sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_QUERY_OBJ_LOCATION, (char *)&body, sizeof(MsgServiceObjLoaction), *queryAdr);
}



int ServiceObj::create_service_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, bool bForce)
{
	ACE_UINT32 unServiceID, unSN;

	int ret = SUB_ADAPTER_STATUS_MGR::instance()->create_obj(unAdapterID, unObjID, unServiceID, unSN);

	if(ret == -1)
	{
		return -1;
	}
	else if(ret == 1)
	{
		if(bForce)
		{
			return destroy_service_obj(unAdapterID, unObjID, true);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		//send create msg;
		MsgServiceObjOP info;
		info.unAdapterID = unAdapterID;
		info.unObjID = unObjID;
		info.unSN = unSN;

		if(sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_CREATE_SERVICE_OBJ, (char*)&info, sizeof(MsgServiceObjOP), unServiceID, unAdapterID, OBJ_ID_NONE) == -1)
		{
			deal_create_service_obj_result(-1, unAdapterID, unObjID, unServiceID, unSN);

			return -1;
		}

		return 0;
	}
}

int ServiceObj::destroy_service_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, bool bRecreate)
{
	ACE_UINT32 unServiceID, unSN;
	if(SUB_ADAPTER_STATUS_MGR::instance()->destroy_obj(unAdapterID, unObjID, unServiceID, unSN, bRecreate) == -1)
	{
		//do nothing
		return -1;
	}
	else
	{
		//send destroy msg
		MsgServiceObjOP info;
		info.unAdapterID = unAdapterID;
		info.unObjID = unObjID;
		info.unSN = unSN;

		if(sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_DESTROY_SERVICE_OBJ, (char*)&info, sizeof(MsgServiceObjOP), unServiceID, unAdapterID, OBJ_ID_NONE) == -1)
		{
			deal_destroy_service_obj_result(-1, unAdapterID, unObjID, unServiceID, unSN);
			return -1;
		}
	}

	return 0;
}

int ServiceObj::do_obj_location_query(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ObjAdr &srcAdr)
{
	ServiceObjStatusInfo *info = SUB_ADAPTER_STATUS_MGR::instance()->find_obj(unAdapterID, unObjID);

	if(info == NULL)
	{
		if(SERVICE_MSG_CTRL_INSTANCE::instance()->is_create_when_qyery_fail(unAdapterID))
		{
			int nRet = create_service_obj(unAdapterID, unObjID);

			if(nRet == -1)
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}

		info = SUB_ADAPTER_STATUS_MGR::instance()->find_obj(unAdapterID, unObjID);
	}

	switch(info->unStatus)
	{
	case SubAdapterStatusMgr::SUB_ADAPTER_OBJ_CREATE:
		//add to queue
		SUB_ADAPTER_STATUS_MGR::instance()->add_queue(info, srcAdr);
		break;
	case SubAdapterStatusMgr::SUB_ADAPTER_OBJ_NORMAL:
		//return obj location
		{
			MsgServiceObjLoaction body;
			body.unServiceID = info->unServiceID;
			body.unAdapterID = unAdapterID;
			body.unObjID = unObjID;

			this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_ANSWER_OBJ_LOCATION, (char *)&body, sizeof(MsgServiceObjLoaction), srcAdr);
		}
		break;
	case SubAdapterStatusMgr::SUB_ADAPTER_OBJ_DESTROY:
		//add to queue
		SUB_ADAPTER_STATUS_MGR::instance()->add_queue(info, srcAdr);
		break;
	}

	return 0;
}

void ServiceObj::deal_create_service_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN)
{
	ServiceObjStatusInfo *pInfo = SUB_ADAPTER_STATUS_MGR::instance()->create_obj_result(nResult, unAdapterID, unObjID, unServiceID, unSN);

	if(pInfo == NULL)
	{
		//do nothing
		printf("deal create service obj result info null\n");
	}
	else
	{
		//get wait queue, then send msg
		OBJ_QUERY_ADDR_LIST_ITERATOR iter(pInfo->query_list);
		ObjAdr *padr;

		MsgServiceObjLoaction body;

		if(pInfo == NULL)
		{
			body.unServiceID = OBJ_ID_NONE;
		}
		else
		{
			body.unServiceID = unServiceID;
		}
		
		body.unAdapterID = unAdapterID;
		body.unObjID = unObjID;

		while(!iter.done())
		{
			padr = iter.next();

			int send_ret = this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_ANSWER_OBJ_LOCATION, (char *)&body, sizeof(MsgServiceObjLoaction), *padr);

			iter.advance();
			//printf("send answer msg[%d,%d,%d]\n", unAdapterID, unObjID, send_ret);

			if(send_ret == -1)
			{
				printf("send answer failed\n");
			}
		}

		//clear query list
		pInfo->query_list.reset();

		if(nResult == -1)
		{
			delete pInfo;
		}
	}
}

void ServiceObj::deal_destroy_service_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN)
{
	ServiceObjStatusInfo *pInfo = SUB_ADAPTER_STATUS_MGR::instance()->destroy_obj_result(nResult, unAdapterID, unObjID, unServiceID, unSN);

	if(pInfo == NULL)
	{
		//do nothing
	}
	else
	{
		if(pInfo->bRecreate && pInfo->query_list.size() > 0)
		{
			//recreate
			ACE_UINT32 unServiceID, unSN;
			if(SUB_ADAPTER_STATUS_MGR::instance()->create_obj(pInfo, unServiceID, unSN) == 0)
			{
				MsgServiceObjOP info;
				info.unAdapterID = unAdapterID;
				info.unObjID = unObjID;
				info.unSN = unSN;

				if(sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_CREATE_SERVICE_OBJ, (char*)&info, sizeof(MsgServiceObjOP), unServiceID, unAdapterID, OBJ_ID_NONE) == -1)
				{
					deal_create_service_obj_result(-1, unAdapterID, unObjID, unServiceID, unSN);
				}
			}
			else
			{
				delete pInfo;
			}
		}
		else
		{
			//send not found msg
			OBJ_QUERY_ADDR_LIST_ITERATOR iter(pInfo->query_list);
			ObjAdr *padr;

			MsgServiceObjLoaction body;

			body.unServiceID = OBJ_ID_NONE;
			body.unAdapterID = unAdapterID;
			body.unObjID = unObjID;

			while(!iter.done())
			{
				padr = iter.next();
				this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_ANSWER_OBJ_LOCATION, (char *)&body, sizeof(MsgServiceObjLoaction), *padr);
				iter.advance();
			}

			delete pInfo;
		}
	}
}

int ServiceObj::add_db_request(ACE_UINT32 unDBAdapter, ACE_UINT32 unType, char *pData, ACE_UINT32 unSize)
{
	int nRet = sendMsg(SERVICE_MESSAGE_TYPE_DB_REQUEST, unType, pData, unSize, OBJ_ID_NONE, unDBAdapter, m_unID);

	if(nRet != 0)
	{
		printf("add db request failed\n");
	}

	m_unWaitDBAckCount ++;

	return nRet;

	/*
	MessageInfo msg;
	if(allocMessageWithInfo(msg, unSize, SERVICE_MESSAGE_TYPE_DB_REQUEST, SERVICE_TYPE_SERVICE_DB, unDBAdapter, m_unID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType) == -1)
	{
		return -1;
	}

	ACE_OS::memcpy(msg.body, pData, unSize);
	this->setAddr(msg.s_head->srcAdr);

	if(m_DBQueue.enqueue_tail(msg.msg) == -1)
	{
		msg.msg->release();
		return -1;
	}

	send_db_request();

	return 0;
	*/
}

/*
int ServiceObj::addLoadRequest(ACE_UINT32 unType, ACE_UINT32 unSize, char *pData)
{
	MsgDBRequest *tmp = (MsgDBRequest *)(new char[sizeof(MsgDBRequest) + unSize]);
	if(tmp == NULL)
	{
		return -1;
	}

	tmp->unType = unType;
	tmp->unSN = nextDBSN();
	tmp->unSize = unSize + sizeof(MsgDBRequest);
	memcpy(tmp->data, pData, unSize);

	if(m_LoadQueue.enqueue_tail(tmp) == -1)
	{
		delete tmp;
		return -1;
	}

	return 0;
}

int ServiceObj::addSaveRequest(ACE_UINT32 unType, ACE_UINT32 unSize, char *pData)
{
	//push in queue

	MsgDBRequest *tmp = (MsgDBRequest *)(new char[sizeof(MsgDBRequest) + unSize]);
	if(tmp == NULL)
	{
		return -1;
	}

	tmp->unType = unType;
	tmp->unSN = nextDBSN();
	tmp->unSize = unSize + sizeof(MsgDBRequest);
	memcpy(tmp->data, pData, unSize);

	if(m_SaveQueue.enqueue_tail(tmp) == -1)
	{
		delete tmp;
		return -1;
	}

	//send save request
	sendSaveRequest();

	return 0;
}
*/

/*
void ServiceObj::send_db_request()
{
	if(m_currentDBRequest != NULL || m_DBQueue.is_empty())
	{
		return;
	}

	if(m_DBQueue.dequeue_head(m_currentDBRequest) == -1)
	{
		m_currentDBRequest = NULL;
		return;
	}

	ACE_Message_Block *msg = m_currentDBRequest->duplicate();

	MessageInfo msgInfo;
	parseMsg(msgInfo, msg);

	if(SERVICE_MSG_CTRL_INSTANCE::instance()->send_msg(msgInfo) == -1)
	{
		msg->release();
		if(m_DBQueue.enqueue_head(m_currentDBRequest) == -1)
		{
			m_currentDBRequest->release();
		}
		
		m_currentDBRequest = NULL;
	}
}
*/

/*
void ServiceObj::sendSaveRequest()
{
	if(m_currentSaving != NULL || m_SaveQueue.is_empty())
	{
		return;
	}

	if(m_SaveQueue.dequeue_head(m_currentSaving) == -1)
	{
		m_currentSaving = NULL;
		return;
	}

	if(this->sendMsg(SERVICE_MESSAGE_TYPE_DB, MSG_SERVICE_OBJ_DB_SAVE_REQUEST, (char *)m_currentSaving, m_currentSaving->unSize, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE) == -1)
	{
		m_SaveQueue.enqueue_head(m_currentSaving);
		m_currentSaving = NULL;
	}
}

int ServiceObj::sendLoadRequest()
{
	if(isLoadingDone())
	{
		return 0;
	}

	if(m_currentLoading != NULL)
	{
		return 1;
	}


	if(m_LoadQueue.dequeue_head(m_currentLoading) == -1)
	{
		m_currentLoading = NULL;
		return 0;
	}

	if(this->sendMsg(SERVICE_MESSAGE_TYPE_DB, MSG_SERVICE_OBJ_DB_SAVE_REQUEST, (char *)m_currentSaving, m_currentSaving->unSize, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE) == -1)
	{
		return -1;
	}

	return 1;
}
*/

/*
int ServiceObj::startLoad()
{
	return createTask(Service_Obj_Loading_Task_Name, "");
}
*/

/*
ACE_UINT32 ServiceObj::nextDBSN()
{
	ACE_UINT32 t = m_unDBSN;

	m_unDBSN = m_unDBSN + 1;

	return t;
}
*/

ACE_UINT32 ServiceObj::generateTaskID()
{
	ACE_UINT32 t = m_TaskIDCursor;

	m_TaskIDCursor ++;

	if(m_TaskIDCursor == OBJ_ID_NONE)
	{
		m_TaskIDCursor = m_TaskIDCursor + 1;
	}

	return t;
}

int ServiceObj::createTask(char *taskName, char *arg)
{
	//ObjTaskInterface *tmp_i = objTaskFactory(unTaskType);
	ObjTaskInterface *tmp_i = SERVICE_TASK_FACTORY_INSTANCE::instance()->createTask(taskName);

	if(tmp_i == NULL)
	{
		return -1;
	}

	tmp_i->setTaskInfo(generateTaskID(), this);

	if(tmp_i->initTask(arg) == -1)
	{
		delete tmp_i;
		return -1;
	}

	m_TaskList.insert_tail(tmp_i);
	
	return 0;
}


void ServiceObj::dealTaskMsg(MessageInfo &msgInfo)
{
	ACE_Double_Linked_List_Iterator<ObjTaskInterface> iter(m_TaskList);

	ObjTaskInterface *tmp_i;

	while((tmp_i = iter.next()) != NULL)
	{
		if(tmp_i->m_unTaskID == msgInfo.s_head->desAdr.unTaskID)
		{
			tmp_i->resetTimer();
			if(tmp_i->task_run(msgInfo) == 0)
			{
				iter.advance_and_remove(false);
				delete tmp_i;
			}

			return;
		}

		iter.advance();
	}
}

void ServiceObj::runTaskList()
{

}

void ServiceObj::service_obj_timer_callback()
{
	if(!m_bServiceObjActive)
	{
		return;
	}

	//objStatusChange();

	if(m_unObjStatus == SERVICE_OBJ_RUN)
	{
		if(m_unWaitDBAckCount == 0 && should_destroy())
		{
			this->setObjStatus(SERVICE_OBJ_DESTROY);
		}
	}

	runTaskList();

	switch(m_unObjStatus)
	{
	case SERVICE_OBJ_CREATE:
		obj_timeout();

		if(hasCreated())
		{
			create_done();
			setObjStatus(SERVICE_OBJ_RUN);
		}
		break;
	case SERVICE_OBJ_RUN:
		obj_timeout();
		break;
	case SERVICE_OBJ_DESTROY:
		obj_timeout();

		//if(is_db_request_done() && hasDestoryed())
		if(hasDestoryed())
		{
			destroy_done();
			obj_fini();
			m_bServiceObjActive = false;
		}
		break;
	default:
		break;
	}
}

void ServiceObj::status_run()
{
	if(!m_bServiceObjActive)
	{
		return;
	}

	if(m_unObjStatus == SERVICE_OBJ_RUN)
	{
		if(m_unWaitDBAckCount == 0 && should_destroy())
		{
			this->setObjStatus(SERVICE_OBJ_DESTROY);
		}
	}

	switch(m_unObjStatus)
	{
	case SERVICE_OBJ_CREATE:
		if(hasCreated())
		{
			create_done();
			setObjStatus(SERVICE_OBJ_RUN);
		}
		break;
	case SERVICE_OBJ_RUN:
		break;
	case SERVICE_OBJ_DESTROY:
		//if(is_db_request_done() && hasDestoryed())
		if(hasDestoryed())
		{
			destroy_done();
			obj_fini();
			m_bServiceObjActive = false;
		}
		break;
	default:
		break;
	}
}

int ServiceObj::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	if(m_bNeedCreateStep)
	{
		setObjStatus(SERVICE_OBJ_CREATE);
	}
	else
	{
		setObjStatus(SERVICE_OBJ_RUN);
	}
	m_bServiceObjActive = true;
	return 0;
}


void ServiceObj::obj_fini()
{
	m_bServiceObjActive = false;
}

void ServiceObj::setObjStatus(ACE_UINT32 unStatus)
{
	m_unNextObjStatus = unStatus;

	objStatusChange();
}

void ServiceObj::objStatusChange()
{
	if(m_unObjStatus == m_unNextObjStatus)
	{
		return;
	}

	printf("obj status change from %d to %d[ID=%d]\n", m_unObjStatus, m_unNextObjStatus, m_unID);

	m_unObjStatus = m_unNextObjStatus;

	switch(m_unObjStatus)
	{
	case SERVICE_OBJ_CREATE:
		if(start_create() == -1)
		{
			setObjStatus(SERVICE_OBJ_DESTROY);
		}
		break;
	case SERVICE_OBJ_RUN:
		if(start_running() == -1)
		{
			setObjStatus(SERVICE_OBJ_DESTROY);
		}
		break;
	case SERVICE_OBJ_DESTROY:
		if(start_destroy() == -1)
		{
			//直接结束生命周期
			obj_fini();
		}
		break;
	default:
		break;
	}
}

/*
void ServiceObj::clearLoadingQueue()
{
	
}
*/

/*
bool ServiceObj::is_db_request_done()
{
	if(m_currentDBRequest == NULL && m_DBQueue.is_empty())
	{
		return true;
	}

	return false;
}
*/

/*
bool ServiceObj::isSavingDone()
{
	if(m_currentSaving == NULL && m_SaveQueue.is_empty())
	{
		return true;
	}

	return false;
}

bool ServiceObj::isLoadingDone()
{
	if(m_currentLoading == NULL && m_LoadQueue.is_empty())
	{
		return true;
	}

	return false;
}
*/

BaseTimerHandler *ServiceObj::activateTimer(time_t sec, suseconds_t usec)
{
	return TIMER_MGR_INSTANCE::instance()->registerTimer(this, ServiceObj::service_obj_timer_func, NULL, ACE_Time_Value(0, 0), ACE_Time_Value(sec, usec));
}

void ServiceObj::deactivateTimer(BaseTimerHandler *timerHandler)
{
	if(timerHandler != NULL)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(timerHandler->m_lTimerID);
	}
}

void ServiceObj::service_obj_timer_func(void *owner, long lTimerID)
{
	//发送消息
	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, sizeof(MsgServiceTimer), SERVICE_MESSAGE_TYPE_TIMER, 0, 0, 0, 0, 0, 0, 0) == -1)
	{
		return;
	}

	ServiceObj *obj = (ServiceObj *)owner;

	obj->setAddr(msgInfo.s_head->desAdr);

	MsgServiceTimer *p = (MsgServiceTimer *)msgInfo.body;
	p->lTimerID = lTimerID;

	BaseService::instance()->put(msgInfo.msg);
}

void ServiceObj::service_timer(long lTimerID)
{

}

bool ServiceObj::has_obj_location_info(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	//return false;

	ObjAdr *adr0 = SERVICE_MSG_CTRL_INSTANCE::instance()->get_query_service_id(unAdapterID, unObjID);
	if(adr0 == NULL)
	{
		return false;
	}

	ObjAdr adr1;
	this->setAddr(adr1);
	if(adr0->unServiceID == adr1.unServiceID && adr0->unAdapterID == adr1.unAdapterID && adr0->unObjID == adr1.unObjID)
	{
		return true;
	}

	return false;
}

void ServiceObj::add_event_listener(EventListener *listener, char *strEventName)
{
	if(listener == NULL || strEventName == NULL)
	{
		return;
	}

	ACE_CString str(strEventName);

	EVENT_LISTENER_LIST *list = NULL;

	if(m_listenerMap.find(str, list) != 0)
	{
		list = new EVENT_LISTENER_LIST();
		if(list == NULL)
		{
			return;
		}

		if(m_listenerMap.bind(str, list) != 0)
		{
			delete list;
			return;
		}
	}

	EVENT_LISTENER_LIST_ITERATOR iter(*list);

	EventListenerInfo *tmp;

	while(!iter.done())
	{
		tmp = iter.next();

		if(tmp->listener == listener)
		{
			return;
		}

		iter.advance();
	}

	tmp = new EventListenerInfo();
	if(tmp == NULL)
	{
		return;
	}

	tmp->listener = listener;

	list->insert_tail(tmp);
}

void ServiceObj::remove_event_listener(EventListener *listener, char *strEventName)
{
	if(listener == NULL || strEventName == NULL)
	{
		return;
	}

	ACE_CString str(strEventName);

	EVENT_LISTENER_LIST *list = NULL;

	if(m_listenerMap.find(str, list) != 0)
	{
		return;
	}

	EVENT_LISTENER_LIST_ITERATOR iter(*list);

	EventListenerInfo *tmp;

	while(!iter.done())
	{
		tmp = iter.next();

		if(tmp->listener == listener)
		{
			tmp->listener = NULL;
			//iter.remove();
			//tmp->m_bRemoved = true;
			//listener不在这里delete
			break;
		}

		iter.advance();
	}

	/*
	if(list->size() == 0)
	{
		m_listenerMap.unbind(str);
		delete list;
	}
	*/
}

void ServiceObj::dispatcher_event(BaseEvent *e)
{
	ACE_CString str(e->m_name);

	EVENT_LISTENER_LIST *list = NULL;

	if(m_listenerMap.find(str, list) != 0)
	{
		return;
	}

	EVENT_LISTENER_LIST_ITERATOR iter(*list);

	EventListenerInfo *tmp;

	while(!iter.done())
	{
		tmp = iter.next();

		//if(tmp->m_bRemoved)
		if(tmp->listener == NULL)
		{
			iter.remove();
			//iter.advance_and_remove(false);
			delete tmp;
		}
		else
		{
			tmp->listener->handle_event(e);
			iter.advance();
		}
		/*
		if(tmp->handle_event(&e) == EventListener::HANDLE_EVENT_REMOVE)
		{
			//iter.remove();
			iter.advance_and_remove();
		}
		else
		{
			iter.advance();
		}
		*/
	}
}