#include "NetworkEndPoint.h"

//#include "..\Protocol\ServiceProtocol.h"
#include "..\TimerMgr\TimerMgr.h"
#include "..\Service\BaseService.h"
//#include "..\Service\ServiceConfigMgr.h"

NetworkEndPoint::NetworkEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
:BaseEndPoint(recvQueue, strIP, unListenPort)
{
	//m_timer = -1;
	m_listenHandler.setEndPoint(this);
	m_connectHandler.setEndPoint(this);

	m_unType = ENDPOINT_TYPE_SERVICE;
}

NetworkEndPoint::~NetworkEndPoint()
{
	//destroy();
}

int NetworkEndPoint::activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	
	return 0;
}

bool NetworkEndPoint::do_activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return true;
}

void NetworkEndPoint::deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
}

bool NetworkEndPoint::do_deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return true;
}

int NetworkEndPoint::putMsg(ACE_Message_Block *msg)
{
	/*
	MessageInfo msgInfo;
	int nRet = -1;
	bool flag = false;
	if(parseMsg(msgInfo, msg) == 0)
	{
		if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_CTRL)
		{
			switch(msgInfo.m_head->unType)
			{
			case MSG_SERVICE_INFO_QUERY:
				{
					MsgServiceInfo *body = (MsgServiceInfo *)msgInfo.body;
					answer_service_info(body->unServiceID, msgInfo.s_head->srcAdr.unServiceID);
				}
				break;
			case MSG_SERVICE_INFO_ANSWER:
				{
					MsgServiceInfo *body = (MsgServiceInfo *)msgInfo.body;
					update_service_info(body->unServiceID, body->unIP, body->unPort);
				}
				break;
			case MSG_SERVICE_OPEN_REQUEST:
				{
					//broadcast service open response
					printf("get service open request\n");
					MsgServiceInfo *body = (MsgServiceInfo *)msgInfo.body;

					this->broadcast_service_status_msg(MSG_SERVICE_OPEN_RESPONSE, body->unServiceID);
				}
				break;
			case MSG_SERVICE_OPEN_RESPONSE:
				{
					//deal service open response,own should ignore
					printf("get service open response\n");
					MsgServiceInfo *body = (MsgServiceInfo *)msgInfo.body;

					update_service_info(body->unServiceID, body->unIP, body->unPort);

					if(body->unServiceID == BaseService::instance()->serviceID())
					{
						set_register_flag(true);
					}
				}
				break;
			case MSG_SERIVCE_CLOSE_REQUEST:
				{
					//broadcast service close response
					MsgServiceInfo *body = (MsgServiceInfo *)msgInfo.body;

					this->broadcast_service_status_msg(MSG_SERIVCE_CLOSE_RESPONSE, body->unServiceID);

					this->update_service_info(body->unServiceID, 0, 0);
				}
				break;
			case MSG_SERIVCE_CLOSE_RESPONSE:
				{
					//deal service close response
					MsgServiceInfo *body = (MsgServiceInfo *)msgInfo.body;
					if(body->unServiceID == BaseService::instance()->serviceID())
					{
						printf("Service close done\n");
						set_register_flag(false);
					}
					else
					{
						printf("Service ID = 0x%08x is off\n", body->unServiceID);
						this->update_service_info(body->unServiceID, 0, 0);
					}
				}
				break;
			default:
				flag = true;
				break;
			}
		}
		else
		{
			flag = true;
		}

		if(flag)
		{
			nRet = BaseEndPoint::putMsg(msg);
		}
		else
		{
			nRet = 0;
			msg->release();
		}
	}

	*/

	return 0;
}
