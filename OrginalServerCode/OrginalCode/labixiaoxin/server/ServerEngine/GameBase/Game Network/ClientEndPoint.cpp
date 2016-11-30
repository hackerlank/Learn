#include "ClientEndPoint.h"
#include "ace\OS_NS_unistd.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


ClientEndPoint::ClientEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
:BaseEndPoint(recvQueue,strIP, unListenPort)
{
	//m_lTimerID = -1;
	m_unPeerMaxConnection = 1;
	m_unAdapterID = 0;
	m_bReliable = true;
	m_listenHandler.setEndPoint(this);
	m_unType = ENDPOINT_TYPE_TCP_INTERNET;

	m_timerHandler = TIMER_MGR_INSTANCE::instance()->registerTimer(this, ClientEndPoint::timerCallback, NULL, ACE_Time_Value(1, 0), ACE_Time_Value(1, 0));
}

ClientEndPoint::~ClientEndPoint()
{
	/*
	while(!NETWORK_MUTEXT_MGR_INSTANCE::instance()->is_empty(ENDPOINT_TYPE_TCP_INTERNET))
	{
		ACE_OS::sleep(1);
	}
	*/
	if(m_timerHandler != NULL)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(m_timerHandler->m_lTimerID);
		delete m_timerHandler;
		m_timerHandler = NULL;
	}
}

int ClientEndPoint::activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ACE_INET_Addr listen_addr(m_unListenPort, m_unListenIP);

	//return m_listenHandler.open(listen_addr);
	return m_listenHandler.open(listen_addr, 0, false, ACE_DEFAULT_ASYNCH_BACKLOG, 1, 0, true);
}

bool ClientEndPoint::do_activate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	return true;
}

void ClientEndPoint::deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	printf("deactivate client endpoint\n");

	m_listenHandler.close();

	CLIENT_PEER_MAP_ITERATOR iter(m_peerMap);
	ClientPeer *peer;

	for(iter = m_peerMap.begin(); iter != m_peerMap.end(); iter++)
	{
		peer = (*iter).int_id_;

		if(peer == NULL)
		{
			continue;
		}

		delete peer;
	}

	m_peerMap.unbind_all();
}

bool ClientEndPoint::do_deactivate()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	bool ret = NETWORK_MUTEXT_MGR_INSTANCE::instance()->is_empty(m_unType);

	return ret;
}

int ClientEndPoint::sendMessage(void *des_adr, ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(des_adr == NULL)
	{
		return -1;
	}

	ACE_UINT32 *peerID = (ACE_UINT32 *)des_adr;

	ClientPeer *peer = find_peer(*peerID);

	if(peer == NULL)
	{
		return -1;
	}

	return peer->send_msg(msg);
}

int ClientEndPoint::validate_connection(char *buff, int size, ClientConnection *pConnection, bool canCreate)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ConnectionInitData info;
	if(parse_connection_init_data(buff, size, info) == -1)
	{
		return -1;
	}

	ClientPeer *peer = create_peer(info.unPeerID, info.strSession, canCreate);

	if(peer == NULL)
	{
		return -1;
	}

	pConnection->m_peer = peer;
	pConnection->exchange_mutex(peer->m_unPeerID);

	if(peer->add_client_connection(pConnection, info.strSession) == -1)
	{
		return -1;
	}

	return 0;
}


/*
ClientPeer *ClientEndPoint::create_client_peer(char *buff, int size, ClientConnection *pConnection, bool canCreate)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ConnectionInitData info;
	if(parse_connection_init_data(buff, size, info) == -1)
	{
		return NULL;
	}

	ClientPeer *peer = create_peer(info.unPeerID, info.strSession, canCreate);

	if(peer == NULL)
	{
		return NULL;
	}

	if(ACE_OS::strcmp(peer->m_strSession, info.strSession) == 0)
	{
		if(peer->add_client_connection(pConnection, info.strSession) == -1)
		{
			peer = NULL;
		}
	}
	else
	{
		pConnection->set_close_error_code(CLIENT_CLOSE_ERROR_INVALID_SESSION);
	}

	return peer;
}
*/

ClientPeer *ClientEndPoint::reset_peer(ACE_UINT32 unPeerID, char *strSession)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ClientPeer *peer = NULL;

	if(m_peerMap.find(unPeerID, peer) == 0)
	{
		peer->reset();

		ACE_OS::strncpy(peer->m_strSession, strSession, CLIENT_SESSION_LEN + 1);
		return peer;
	}

	peer = new ClientPeer(m_recvQueue, m_unAdapterID, unPeerID, strSession, m_unPeerMaxConnection, m_bReliable);

	if(peer == NULL)
	{
		return NULL;
	}

	if(m_peerMap.bind(unPeerID, peer) != 0)
	{
		delete peer;
		return NULL;
	}

	return peer;
}

ClientPeer *ClientEndPoint::create_peer(ACE_UINT32 unPeerID, char *strSession, bool canCreate)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ClientPeer *peer = NULL;

	if(unPeerID == 0)
	{
		return NULL;
	}

	if(m_peerMap.find(unPeerID, peer) == 0)
	{
		/*
		if(peer->m_unSessionID == unSessionID)
		{
			return peer;
		}
		*/
		printf("reconnect [%s, %s]\n", peer->m_strSession, strSession);

		/*
		if(ACE_OS::strcmp(peer->m_strSession, strSession) == 0)
		{
			return peer;
		}
		
		return NULL;
		*/

		return peer;
	}

	if(!canCreate)
	{
		return NULL;
	}

	peer = new ClientPeer(m_recvQueue, m_unAdapterID, unPeerID, strSession, m_unPeerMaxConnection, m_bReliable);

	if(peer == NULL)
	{
		return NULL;
	}

	if(m_peerMap.bind(unPeerID, peer) != 0)
	{
		delete peer;
		return NULL;
	}

	return peer;
}

//Ãﬂ»À
int ClientEndPoint::delete_peer(ACE_UINT32 unPeerID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ClientPeer *peer = NULL;

	if(m_peerMap.unbind(unPeerID, peer) == 0)
	{
		delete peer;
		return 0;
	}

	return -1;
}

ClientPeer *ClientEndPoint::find_peer(ACE_UINT32 unPeerID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ClientPeer *peer = NULL;

	if(m_peerMap.find(unPeerID, peer) == 0)
	{
		return peer;
	}

	return NULL;
}

void ClientEndPoint::timerCallback(void *p, long lTimerID)
{
	ClientEndPoint *endpoint = (ClientEndPoint *)p;
	
	endpoint->peer_timeout();
}

void ClientEndPoint::peer_timeout()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	CLIENT_PEER_MAP_ITERATOR iter(m_peerMap);
	ClientPeer *peer;

	for(iter = m_peerMap.begin(); iter != m_peerMap.end(); iter++)
	{
		peer = (*iter).int_id_;

		if(peer == NULL)
		{
			continue;
		}

		peer->resend_msg();
	}
}