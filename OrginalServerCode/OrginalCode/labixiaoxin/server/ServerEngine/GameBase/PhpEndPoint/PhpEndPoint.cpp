#include "PhpEndPoint.h"
#include "ace\OS_NS_unistd.h"

PhpEndPoint::PhpEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
:BaseEndPoint(recvQueue,strIP, unListenPort)
{
	m_unPeerIDCounter = 1;
	m_listenHandler.setEndPoint(this);
	m_unType = ENDPOINT_TYPE_TCP_PHP;
	m_unDesAdapterID = OBJ_ID_NONE;
}

PhpEndPoint::~PhpEndPoint()
{
	/*
	delete_all_connection();

	while(!is_connection_empty())
	{
		ACE_OS::sleep(1);
	}
	*/
}

void PhpEndPoint::delete_all_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	PHP_CONNECTION_MAP_ITERATOR iter(m_connectionMap);

	PhpConnection *connection;

	for(iter = m_connectionMap.begin(); iter != m_connectionMap.end(); iter++)
	{
		connection = (*iter).int_id_;

		if(connection == NULL)
		{
			continue;
		}

		connection->closeConnection();
	}

}

int PhpEndPoint::activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ACE_INET_Addr listen_addr(m_unListenPort, m_unListenIP);

	return m_listenHandler.open(listen_addr);
}

bool PhpEndPoint::do_activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return true;
}

void PhpEndPoint::deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	m_listenHandler.close();

	delete_all_connection();
}

bool PhpEndPoint::do_deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return is_connection_empty();
}

int PhpEndPoint::sendMessage(void *des_adr, ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(des_adr == NULL)
	{
		return -1;
	}

	ACE_UINT32 *connectionID = (ACE_UINT32 *)des_adr;

	PhpConnection *connection = NULL;// = find_peer(*peerID);

	if(m_connectionMap.find(*connectionID, connection) != 0)
	{
		return -1;
	}

	return connection->send_msg(msg);
}

void PhpEndPoint::delete_peer(ACE_UINT32 unPeerID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	PhpConnection *connection = NULL;

	if(m_connectionMap.find(unPeerID, connection) != 0)
	{
		return;
	}

	connection->closeConnection();
}

void PhpEndPoint::remove_connection(ACE_UINT32 unPeerID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	//int ret = m_connectionMap.find(unPeerID, connection);

	m_connectionMap.unbind(unPeerID);

	//printf("ret");
}

bool PhpEndPoint::is_connection_empty()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return (m_connectionMap.current_size() == 0);
}

int PhpEndPoint::put_msg(ACE_Message_Block *msg, PhpConnection *connection)
{
	if(m_unDesAdapterID == OBJ_ID_NONE)
	{
		return -1;
	}

	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, sizeof(MsgServiceObjOpArg), SERVICE_MESSAGE_TYPE_SYSTEM, OBJ_ID_NONE, m_unDesAdapterID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, MSG_CREATE_BASE_OBJ) == -1)
	{
		return -1;
	}

	MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;
	body->unID = m_unPeerIDCounter;

	if(this->putMsg(msgInfo.msg) == -1)
	{
		msgInfo.msg->release();
		return -1;
	}

	if(m_connectionMap.bind(m_unPeerIDCounter, connection) != 0)
	{
		return -1;
	}

	MessageInfo tmpInfo;

	parseMsg(tmpInfo, msg);
	tmpInfo.s_head->desAdr.unAdapterID = m_unDesAdapterID;
	tmpInfo.s_head->desAdr.unObjID = m_unPeerIDCounter;

	if(this->putMsg(msg) == -1)
	{
		return -1;
	}

	connection->m_unPeerID = m_unPeerIDCounter;

	m_unPeerIDCounter ++;
	if(m_unPeerIDCounter == 0)
	{
		m_unPeerIDCounter = 1;
	}

	return 0;
}



