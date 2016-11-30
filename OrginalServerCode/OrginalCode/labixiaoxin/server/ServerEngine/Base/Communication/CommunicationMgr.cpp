#include "CommunicationMgr.h"

#include "ace\Proactor.h"

#include "ServiceEndPoint.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

CommunicationMgr::CommunicationMgr()
{
	m_nProactorThreadID = -1;

	for(int i = 0;i < MAX_ENDPOINT_COUNT;i ++)
	{
		m_endpointList[i] = NULL;
	}
}

CommunicationMgr::~CommunicationMgr()
{

}

int CommunicationMgr::addEndpoint(BaseEndPoint *endpoint)
{
	if(endpoint == NULL)
	{
		return 0;
	}

	ACE_UINT32 t_type = endpoint->m_unType;

	if(m_endpointList[t_type] != NULL)
	{
		removeEndpoint(t_type);
	}

	if(endpoint->activate() == -1)
	{
		return -1;
	}

	while(!endpoint->do_activate())
	{
		ACE_OS::sleep(1);
	}

	m_endpointList[t_type] = endpoint;

	return 0;
}

void CommunicationMgr::removeEndpoint(ACE_UINT32 unType)
{
	if(m_endpointList[unType] == NULL)
	{
		return;
	}

	m_endpointList[unType]->deactivate();

	delete m_endpointList[unType];
	m_endpointList[unType] = NULL;
}

ACE_INT32 CommunicationMgr::startup(ACE_Message_Queue<ACE_MT_SYNCH> *msg_queue,ACE_Message_Queue<ACE_MT_SYNCH> *msg_delete_queue, char *strIP, ACE_UINT32 unListenIP, ACE_UINT32 bServiceMgr)
{
	if(m_nProactorThreadID != -1)
	{
		return 1;
	}

	m_recvMsgQueue = msg_queue;

	ServiceEndPoint *endpoint = new ServiceEndPoint(m_recvMsgQueue, strIP, unListenIP, bServiceMgr);

	if(addEndpoint(endpoint) == -1)
	{
		delete endpoint;
		return -1;
	}

	m_nProactorThreadID = ACE_Thread_Manager::instance()->spawn_n(1, activateProactor, NULL);

	if(m_nProactorThreadID == -1)
	{
		removeEndpoint(ENDPOINT_TYPE_SERVICE);

		return -1;
	}

	return 0;
}

void CommunicationMgr::shutdown()
{
	int i;

	//send unregister msg
	ServiceEndPoint *serviceEndPoint = (ServiceEndPoint *)this->getEndPoint(ENDPOINT_TYPE_SERVICE);

	if(serviceEndPoint != NULL)
	{
		serviceEndPoint->unregister_service();
	}

	for(i = 0;i < MAX_ENDPOINT_COUNT;i ++)
	{
		if(m_endpointList[i] == NULL)
		{
			continue;
		}

		m_endpointList[i]->deactivate();
	}

	//if there's no send msg
	bool flag = true;

	while(flag)
	{
		flag = false;

		for(i = 0;i < MAX_ENDPOINT_COUNT;i ++)
		{
			if(m_endpointList[i] == NULL)
			{
				continue;
			}
			if(!m_endpointList[i]->do_deactivate())
			{
				flag = true;
			}
			else
			{
				delete m_endpointList[i];
				m_endpointList[i] = NULL;
			}
		}

		ACE_OS::sleep(0);
	}

	if(m_nProactorThreadID != -1)
	{
		ACE_Proactor::instance()->proactor_end_event_loop();
		ACE_Thread_Manager::instance()->wait_grp(m_nProactorThreadID);
		m_nProactorThreadID = -1;
	}
}

ACE_THR_FUNC_RETURN CommunicationMgr::activateProactor(void *opParam)
{
	intptr_t nRc = ACE_Proactor::instance()->proactor_run_event_loop();

	while(ACE_Proactor::instance()->proactor_event_loop_done() != 1)
	{
		Sleep(1);
	}

	return static_cast<ACE_THR_FUNC_RETURN>(nRc);
}

int CommunicationMgr::sendMsg(ACE_UINT32 unEndpointType, void *des_adr, ACE_Message_Block *msg)
{
	if(m_endpointList[unEndpointType] == NULL)
	{
		return -1;
	}

	return m_endpointList[unEndpointType]->sendMessage(des_adr, msg);
}

int CommunicationMgr::send_local_msg(ACE_Message_Block *msg)
{
	if(m_recvMsgQueue->enqueue_tail(msg) == -1)
	{
		return -1;
	}
	return 0;
}