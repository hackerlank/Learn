#include "ServiceEndPoint.h"

#include "..\Protocol\ServiceProtocol.h"

#include "..\Service\BaseService.h"
#include "..\Service\ServiceConfigMgr.h"
#include "..\Utils\NetworkMutexMgr.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ServiceEndPoint::ServiceEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort, ACE_UINT32 bServiceMgr)
:BaseEndPoint(recvQueue, strIP, unListenPort)
{
	m_bServiceMgr = bServiceMgr;
	m_timerHandler = NULL;
	m_listenHandler.setEndPoint(this);
	m_connectHandler.setEndPoint(this);

	m_unType = ENDPOINT_TYPE_SERVICE;

	m_bRegister = false;
}

ServiceEndPoint::~ServiceEndPoint()
{
	destroy();

	while(NETWORK_MUTEXT_MGR_INSTANCE::instance()->get_connection_count(ENDPOINT_TYPE_SERVICE) > 0)
	{
		ACE_OS::sleep(1);
	}

	printf("delete service end point, type = %d\n", m_unType);
}

void ServiceEndPoint::set_register_flag(bool flag)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	m_bRegister = flag;
}

int ServiceEndPoint::activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_bServiceMgr == 0)
	{
		if(create_service_peer(SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrID, SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrIP, SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrPort) == NULL)
		{
			return -1;
		}
	}

	if(listen() != 0)
	{
		return -1;
	}

	register_service();
	
	return 0;
}

bool ServiceEndPoint::do_activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	/*
	if(m_bServiceMgr == 1)
	{
		return true;
	}

	return m_bRegister;
	*/

	return true;
}

void ServiceEndPoint::deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	//destroy();
	this->unregister_service();
}

bool ServiceEndPoint::do_deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	bool ret = false;

	if(m_bServiceMgr == 1)
	{
		ret = true;
	}
	else
	{
		ret = !m_bRegister;
	}

	if(ret)
	{
		this->destroy();
	}

	return ret;
}

int ServiceEndPoint::register_service()
{
	if(m_bServiceMgr == 1)
	{
		return -1;
	}

	MessageInfo msg_info;

	if(allocMessageWithInfo(msg_info, sizeof(MsgServiceInfo), SERVICE_MESSAGE_TYPE_CTRL, SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrID, 0, 0, BaseService::instance()->serviceID(), 0, 0, MSG_SERVICE_OPEN_REQUEST) == -1)
	{
		return -1;
	}

	MsgServiceInfo *msg_body = (MsgServiceInfo *)msg_info.body;

	msg_body->unServiceID = BaseService::instance()->serviceID();

	if(sendMessage(&msg_info.s_head->desAdr, msg_info.msg) == -1)
	{
		msg_info.msg->release();
		return -1;
	}

	return 0;
}

int ServiceEndPoint::unregister_service()
{
	if(m_bServiceMgr == 1)
	{
		return -1;
	}

	MessageInfo msg_info;

	if(allocMessageWithInfo(msg_info, sizeof(MsgServiceInfo), SERVICE_MESSAGE_TYPE_CTRL, SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrID, 0, 0, BaseService::instance()->serviceID(), 0, 0, MSG_SERIVCE_CLOSE_REQUEST) == -1)
	{
		return -1;
	}

	MsgServiceInfo *msg_body = (MsgServiceInfo *)msg_info.body;

	msg_body->unServiceID = BaseService::instance()->serviceID();

	if(sendMessage(&msg_info.s_head->desAdr, msg_info.msg) == -1)
	{
		msg_info.msg->release();
		return -1;
	}

	return 0;
}

int ServiceEndPoint::connect(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unPort)
{
	ACE_INET_Addr addr(unPort, unIP);

	printf("address = %s\n", addr.get_host_addr());

	ACE_INET_Addr local_addr;

	return m_connectHandler.connect(addr, local_addr, 1, SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance(unServiceID));
}

int ServiceEndPoint::listen()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ACE_INET_Addr listen_addr(m_unListenPort, m_unListenIP);

	//listen_addr.set_port_number(unPort);

	//m_unListenIP = listen_addr.get_ip_address();
	printf("listen ip = %s\n", listen_addr.get_host_addr());

	if(m_listenHandler.open(listen_addr) == -1)
	{
		return -1;
	}

	if(m_connectHandler.open() == -1)
	{
		return -1;
	}
	
	if((m_timerHandler = TIMER_MGR_INSTANCE::instance()->registerTimer(this, ServiceEndPoint::serviceEndPointTimerCallback, NULL, ACE_Time_Value(0, 0), ACE_Time_Value(1, 0))) == NULL)
	{
		//delete handler;
		destroy();
		return -1;
	}


	return 0;
}

int ServiceEndPoint::query_service_address(ACE_UINT32 unServiceID)
{
	if(m_bServiceMgr == 1)
	{
		return -1;
	}

	if(unServiceID == SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrID)
	{
		return 0;
	}

	MessageInfo msg_info;

	if(allocMessageWithInfo(msg_info, sizeof(MsgServiceInfo), SERVICE_MESSAGE_TYPE_CTRL, SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrID, 0, 0, BaseService::instance()->serviceID(), 0, 0, MSG_SERVICE_INFO_QUERY) == -1)
	{
		return -1;
	}

	MsgServiceInfo *msg_body = (MsgServiceInfo *)msg_info.body;

	msg_body->unServiceID = unServiceID;

	if(sendMessage(&msg_info.s_head->desAdr, msg_info.msg) == -1)
	{
		msg_info.msg->release();
		return -1;
	}

	return 0;
}



ServicePeer *ServiceEndPoint::set_service_peer_connection(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unPort, ServiceConnection *conn, ACE_UINT32 unType)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ServicePeer *peer = NULL;

	if(m_ServicePeerMap.find(unServiceID, peer) != 0)
	{
		
		peer = create_service_peer(unServiceID, unIP, unPort);

		if(peer == NULL)
		{
			return NULL;
		}
	}

	peer->set_connection(conn, unType);

	return peer;
}

void ServiceEndPoint::destroy()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(m_timerHandler != NULL)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(m_timerHandler->m_lTimerID);
		delete m_timerHandler;
		m_timerHandler = NULL;
	}

	m_listenHandler.close();
	m_connectHandler.close();

	disconnect_all_peer();
}

void ServiceEndPoint::serviceEndPointTimerCallback(void *p, long lTimerID)
{
	ServiceEndPoint *endpoint = (ServiceEndPoint *)p;
	endpoint->connect_all_peer();
}

void ServiceEndPoint::connect_all_peer()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	
	SERVICE_PEER_MAP_ITERATOR iter(m_ServicePeerMap);
	ServicePeer *peer;
	
	for(iter = m_ServicePeerMap.begin(); iter != m_ServicePeerMap.end(); iter++)
	{
		peer = (*iter).int_id_;

		if(peer == NULL)
		{
			continue;
		}

		peer->establish_send_connection();
	}
}

void ServiceEndPoint::disconnect_all_peer()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	
	SERVICE_PEER_MAP_ITERATOR iter(m_ServicePeerMap);
	ServicePeer *peer;
	
	for(iter = m_ServicePeerMap.begin(); iter != m_ServicePeerMap.end(); iter++)
	{
		peer = (*iter).int_id_;

		if(peer == NULL)
		{
			continue;
		}

		delete peer;
	}

	m_ServicePeerMap.unbind_all();
}

int ServiceEndPoint::send_service_status_msg(ACE_UINT32 unType, ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unPort, ACE_UINT32 unTargetServiceID)
{
	if(m_bServiceMgr == 0)
	{
		return -1;
	}

	MessageInfo msg_info;

	if(allocMessageWithInfo(msg_info, sizeof(MsgServiceInfo), SERVICE_MESSAGE_TYPE_CTRL, unTargetServiceID, 0, 0, BaseService::instance()->serviceID(), 0, 0, unType) == -1)
	{
		return -1;
	}

	MsgServiceInfo *msg_body = (MsgServiceInfo *)msg_info.body;

	msg_body->unServiceID = unServiceID;
	msg_body->unIP = unIP;
	msg_body->unPort = unPort;

	if(sendMessage(&msg_info.s_head->desAdr, msg_info.msg) == -1)
	{
		msg_info.msg->release();
		return -1;
	}

	return 0;
}

void ServiceEndPoint::broadcast_service_status_msg(ACE_UINT32 unType, ACE_UINT32 unServiceID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	
	SERVICE_PEER_MAP_ITERATOR iter(m_ServicePeerMap);
	ServicePeer *pObj;

	ServicePeer *srcObj;

	if(m_ServicePeerMap.find(unServiceID, srcObj) != 0)
	{
		return;
	}
	
	for(iter = m_ServicePeerMap.begin(); iter != m_ServicePeerMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		send_service_status_msg(unType, srcObj->m_unTargetServiceID, srcObj->m_unTargetIP, srcObj->m_unTargetPort, pObj->m_unTargetServiceID);
	}
}

int ServiceEndPoint::sendMessage(void *des_adr, ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(des_adr == NULL)
	{
		return -1;
	}

	ObjAdr *adr = (ObjAdr *)des_adr;

	if(adr->unServiceID == BaseService::instance()->serviceID())
	{
		if(this->putMsg(msg) == -1)
		{
			return -1;
		}
		return 0;
	}

	ServicePeer *peer = NULL;

	int nRet = m_ServicePeerMap.find(adr->unServiceID, peer);

	if(nRet == -1)
	{
		if(m_bServiceMgr)
		{
			return -1;
		}
		else
		{
			peer = create_service_peer(adr->unServiceID, 0, 0);
			if(peer == NULL)
			{
				return -1;
			}
		}
	}

	return peer->send_msg(msg);
}

ServicePeer *ServiceEndPoint::create_service_peer(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unListenPort)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ServicePeer *peer = new ServicePeer(unServiceID, unIP, unListenPort, this);
	if(peer == NULL)
	{
		return NULL;
	}

	if(m_ServicePeerMap.bind(unServiceID, peer) != 0)
	{
		delete peer;
		peer = NULL;
	}

	return peer;
}

void ServiceEndPoint::notify_send_done(ACE_UINT32 unServiceID, ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ServicePeer *peer = NULL;
	if(m_ServicePeerMap.find(unServiceID, peer) != 0)
	{
		return;
	}

	peer->notify_send_done(msg);
}

void ServiceEndPoint::remove_connection(ACE_UINT32 unServiceID, ACE_UINT32 unType)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ServicePeer *peer = NULL;
	if(m_ServicePeerMap.find(unServiceID, peer) != 0)
	{
		return;
	}

	peer->remove_connection(unType);
}

void ServiceEndPoint::clear_service_info(ACE_UINT32 unServiceID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ServicePeer *peer;

	if(m_ServicePeerMap.unbind(unServiceID, peer) != 0)
	{
		return;
	}

	delete peer;
}

void ServiceEndPoint::update_service_info(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unListenPort)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ServicePeer *peer;

	if(m_ServicePeerMap.find(unServiceID, peer) != 0)
	{
		return;
	}

	if(unIP == 0)
	{
		peer->reset(this->m_bServiceMgr == 0);
	}
	else
	{
		peer->update_service_info(unIP, unListenPort);
	}
}


void ServiceEndPoint::answer_service_info(ACE_UINT32 unQueryServiceID, ACE_UINT32 unServiceID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_bServiceMgr == 0)
	{
		return;
	}

	MessageInfo info;

	if(allocMessageWithInfo(info, sizeof(MsgServiceInfo), SERVICE_MESSAGE_TYPE_CTRL, unServiceID, 0, 0, BaseService::instance()->serviceID(), 0, 0, MSG_SERVICE_INFO_ANSWER) == -1)
	{
		return;
	}

	MsgServiceInfo *body = (MsgServiceInfo *)info.body;

	ServicePeer *peer;

	body->unServiceID = unQueryServiceID;

	if(m_ServicePeerMap.find(unQueryServiceID, peer) == -1)
	{
		
	}
	else
	{
		body->unIP = peer->m_unTargetIP;
		body->unPort = peer->m_unTargetPort;
	}

	if(sendMessage(&info.s_head->desAdr, info.msg) == -1)
	{
		info.msg->release();
	}
}


int ServiceEndPoint::putMsg(ACE_Message_Block *msg)
{
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
			if(nRet == -1)
			{
				//msg->release();
				printf("oooooooooooooo\n");
			}
		}
		else
		{
			nRet = 0;
			msg->release();
		}
	}

	return nRet;
}

int ServiceEndPoint::get_service_list(ServerBasicInfo desList[], int nMaxCount)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	SERVICE_PEER_MAP_ITERATOR iter(m_ServicePeerMap);
	ServicePeer *pObj;

	int c = 0;

	for(iter = m_ServicePeerMap.begin(); iter != m_ServicePeerMap.end(); iter++)
	{
		pObj = (*iter).int_id_;

		if(pObj == NULL)
		{
			continue;
		}

		if(pObj->m_unTargetIP == 0)
		{
			continue;
		}

		desList[c].unIP = pObj->m_unTargetIP;
		desList[c].unPort = pObj->m_unTargetPort;
		desList[c].unServiceID = pObj->m_unTargetServiceID;

		c ++;

		if(c >= nMaxCount)
		{
			break;
		}
	}

	return c;
}

bool ServiceEndPoint::is_service_on(ACE_UINT32 unServiceID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ServicePeer *pObj;

	if(m_ServicePeerMap.find(unServiceID, pObj) == 0)
	{
		if(pObj->m_unTargetIP != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}