#include "ServicePeer.h"
#include "ServiceEndPoint.h"
#include "..\Protocol\ServiceProtocol.h"
#include "..\Service\BaseService.h"

//to do
//add timer to judge connect fail

ServicePeer::ServicePeer(ACE_UINT32 unTargetServiceID, ACE_UINT32 unIP, ACE_UINT32 unListenPort, ServiceEndPoint *endpoint)
{
	for(int i = 0;i < ServiceConnection::TYPE_MAX;i ++)
	{
		m_connList[i] = NULL;
	}

	m_unTargetServiceID = unTargetServiceID;
	m_endpoint = endpoint;

	m_unTargetIP = unIP;
	m_unTargetPort = unListenPort;
	m_unSendStatus = SENDSTATUS_DISCONNECTED;
	m_bSending = false;
	m_bInited = false;

	m_sendQueue.high_water_mark(0xA00000);
	m_sendQueue.low_water_mark(0xA00000);
	//m_unSendSN = 0;
	//m_unRecvSN = 0;
	//m_unAckSN = 0;
	//m_bInitRecvSN = false;
	//m_bInitSendSN = false;
}

ServicePeer::~ServicePeer()
{
	reset(true);
}

void ServicePeer::reset(bool bNeedClose)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(bNeedClose)
	{
		close();
	}
	else
	{
		m_unTargetIP = m_unTargetPort = 0;
	}
}

void ServicePeer::update_service_info(ACE_UINT32 unIP, ACE_UINT32 unListenPort)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(unIP == m_unTargetIP && m_unTargetPort == unListenPort)
	{
		return;
	}

	//close connection
	//close();

	m_unTargetIP = unIP;
	m_unTargetPort = unListenPort;

	//connect();
}

int ServicePeer::send_msg(ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	int nRet = 0;

	if(m_sendQueue.enqueue_tail(msg) == -1)
	{
		printf("enqueue tail errorno = %d\n", errno);
		return -1;
	}

	if(m_connList[ServiceConnection::TYPE_SEND] == NULL)
	{
		establish_send_connection();
	}
	else
	{
		//m_bSending = false;
		send_msg_i();
	}

	return nRet;
}

void ServicePeer::notify_send_done(ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	m_bSending = false;

	if(msg == NULL)
	{
		send_msg_i();
	}
	else
	{
		printf("send msg faild !!\n");
		//if send failed, put back the msg to the queue
		m_sendQueue.enqueue_head(msg);

		//close send connection
		close(ServiceConnection::TYPE_SEND);
	}
}

void ServicePeer::send_msg_i()
{
	//printf("send msg i\n");
	if(m_bSending)
	{
		return;
	}

	if(m_sendQueue.is_empty())
	{
		return;
	}

	ACE_Message_Block *msg = NULL;
	if(m_sendQueue.dequeue(msg) == -1)
	{
		return;
	}

	if(m_connList[ServiceConnection::TYPE_SEND]->send_msg(msg) == -1)
	{
		printf("Send_msg error !!!!!!!\n");
		m_sendQueue.enqueue_head(msg);
		return;
	}

	m_bSending = true;
}

void ServicePeer::set_connection(ServiceConnection *conn, ACE_UINT32 unType)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_connList[unType] != NULL)
	{
		m_connList[unType]->closeConnection();
	}

	m_connList[unType] = conn;

	if(unType == ServiceConnection::TYPE_SEND)
	{
		//send init request
		m_unSendStatus = SENDSTATUS_CONNECTED;
		m_bSending = false;

		//send firt msg
		send_msg_i();
	}
}

void ServicePeer::remove_connection(ACE_UINT32 unType)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	m_connList[unType] = NULL;
}

void ServicePeer::close()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	for(int i = 0;i < ServiceConnection::TYPE_MAX;i ++)
	{
		close(i);
	}

	m_unTargetIP = m_unTargetPort = 0;
	
}

void ServicePeer::close(ACE_UINT32 unType)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(m_connList[unType] != NULL)
	{
		m_connList[unType]->closeConnection();
		m_connList[unType] = NULL;
	}

	if(unType == ServiceConnection::TYPE_SEND)
	{
		m_unSendStatus = SENDSTATUS_DISCONNECTED;
		m_bSending = false;
	}
}

void ServicePeer::connect()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_unSendStatus != SENDSTATUS_DISCONNECTED)
	{
		return;
	}

	//connect
	if(m_endpoint->connect(m_unTargetServiceID, m_unTargetIP, m_unTargetPort) == 0)
	{
		m_unSendStatus = SENDSTATUS_CONNECTING;
	}
}

void ServicePeer::establish_send_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_unTargetIP  == 0)
	{
		if(!m_bInited)
		{
			m_endpoint->query_service_address(m_unTargetServiceID);
			m_bInited = true;
		}
	}
	else
	{
		connect();
	}
}
