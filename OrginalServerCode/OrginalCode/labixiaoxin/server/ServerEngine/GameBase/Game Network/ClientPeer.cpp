#include "ClientPeer.h"

#include "..\Protocol\ControlProtocol.h"

//#include "..\..\base\TimerMgr\TimerMgr.h"

#include "..\..\Base\Communication\CommunicationMgr.h"

#include "ClientEndPoint.h"

#include "..\..\Base\Service\BaseService.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

#define MAX_CLIENT_PEER_CACHE_MSG 60
#define MAX_CLIENT_MSG_PER_2_SECOND 60//没秒中不能超过n个消息否则踢掉

#define ACK_TYPE_IN_NETWORK (((MSG_CLIENT_MSG_ACK << 24) & 0xff000000) | ((MSG_CLIENT_MSG_ACK << 8) & 0x00ff0000) | ((MSG_CLIENT_MSG_ACK >> 8) & 0x0000ff00) | ((MSG_CLIENT_MSG_ACK >> 24) & 0x000000ff))

ClientPeer::ClientPeer(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, ACE_UINT32 unAdapterID, ACE_UINT32 unPeerID, char *strSession, ACE_UINT32 unMaxConnection, bool bReliable)
{
	//m_lTimerID = -1;
	m_recvQueue = recvQueue;
	m_unAdapterID = unAdapterID;
	m_unPeerID = unPeerID;
	m_unMaxConnection = unMaxConnection;
	if(m_unMaxConnection > MAX_CLIENT_CONNECTION)
	{
		m_unMaxConnection = MAX_CLIENT_CONNECTION;
	}

	ACE_OS::strncpy(m_strSession, strSession, CLIENT_SESSION_LEN);
	m_strSession[CLIENT_SESSION_LEN] = '\0';

	for(int i = 0;i < MAX_CLIENT_CONNECTION;i ++)
	{
		m_ConnectionList[i] = NULL;
	}

	m_unPacketNo = 0;

	m_bReliable = bReliable;
	m_slideWindow.reset();
	m_sendQueue.high_water_mark(0xA00000);
	m_sendQueue.low_water_mark(0xA00000);

	m_nCurrentConnectionCount = 0;
	m_nCurrentResendSlot = 0;

	m_unMsgCount = 0;
	m_dwResetTickCount = GetTickCount();

	m_clientMutex = NETWORK_MUTEXT_MGR_INSTANCE::instance()->acquire(ENDPOINT_TYPE_TCP_INTERNET, m_unPeerID);

	//m_lTimerID = TIMER_MGR_INSTANCE::instance()->registerTimer(this, ClientPeer::timerCallback, NULL, ACE_Time_Value(CLIENT_PEER_TIMER_INTERVAL, 0), ACE_Time_Value(CLIENT_PEER_TIMER_INTERVAL, 0));

}

ClientPeer::~ClientPeer()
{
	/*
	if(m_lTimerID != -1)
	{
		TIMER_MGR_INSTANCE::instance()->deleteTimer(m_lTimerID);
		m_lTimerID = -1;
	}
	*/

	remove_all_connection();

	NETWORK_MUTEXT_MGR_INSTANCE::instance()->release(ENDPOINT_TYPE_TCP_INTERNET, m_unPeerID);
}

int ClientPeer::add_client_connection(ClientConnection *pConnection, char *strSession)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	if(ACE_OS::strcmp(m_strSession, strSession) != 0)
	{
		return -1;
	}

	int idx = -1;

	for(ACE_UINT32 i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] == NULL)
		{
			//m_ConnectionList[i].isFree = true;
			m_ConnectionList[i] = pConnection;
			idx = i;
			break;
		}
	}
	if(idx == -1)
	{
		ClientConnection *tmp_conn = m_ConnectionList[0];

		tmp_conn->closeConnection();

		//tmp_conn->set_close_error_code(CLIENT_CLOSE_ERROR_NEW_CONNECTION);
		//tmp_conn->send_close_msg();

		m_ConnectionList[0] = pConnection;
	}

	notify_send();

	return 0;
}

void ClientPeer::reset()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);
	reset_all_connection();
	m_unPacketNo = 0;

	m_sendQueue.flush();
	m_slideWindow.reset();

	m_nCurrentResendSlot = 0;

	m_unMsgCount = 0;
	m_dwResetTickCount = GetTickCount();

	int i;

	for(i = 0;i < CLIENT_PEER_RESEND_SLOT_COUNT;i ++)
	{
		CLIENT_PEER_RESEND_SLOTITERATOR iter(m_resendList[i]);

		ACE_Message_Block *msg;

		while(!iter.done())
		{
			//add to send queen
			msg = iter.next();

			iter.remove();
			msg->release();

			//iter.advance();
		}

		m_resendList[i].reset();
	}
}

int ClientPeer::remove_client_connection(ClientConnection *pConnection)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	for(ACE_UINT32 i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] == pConnection)
		{
			m_ConnectionList[i] = NULL;
			return 0;
		}
	}

	return -1;
}

void ClientPeer::remove_all_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	//ClientConnection *pConnection;

	for(ACE_UINT32 i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] != NULL)
		{
			m_ConnectionList[i]->set_peer(NULL);
			m_ConnectionList[i]->closeConnection();
		}

		m_ConnectionList[i] = NULL;
	}
}

void ClientPeer::reset_all_connection()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	//ClientConnection *pConnection;

	for(ACE_UINT32 i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] != NULL)
		{
			m_ConnectionList[i]->set_close_error_code(CLIENT_CLOSE_ERROR_KICK_BY_ANOTHER);
			m_ConnectionList[i]->send_close_msg();
		}

		m_ConnectionList[i] = NULL;
	}
}

int ClientPeer::put_msg(ACE_Message_Block *msg, ACE_UINT32 unPacketNo)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	//judage is too many msg

	CLogBase *pLog = BaseService::GetLogInstance();

	m_unMsgCount ++;
	
	if (m_unMsgCount % MAX_CLIENT_MSG_PER_2_SECOND == 1)
	{
		if (m_unMsgCount == 1)
		{
			m_dwResetTickCount = GetTickCount();
		}
		else
		{
			ACE_UINT32 unNow = GetTickCount();
			if (unNow < m_dwResetTickCount + 1000)
			{
				sprintf(pLog->m_szLogBuffer, "[%s][%d]:m_unMsgCount = %d, peerid=%d",__FILE__, __LINE__, m_unMsgCount, m_unPeerID);
				pLog->RecordLog(Log_Type_Fucking, pLog->m_szLogBuffer);
				//m_endPoint->
				//发包数量异常，踢掉用户
				ClientEndPoint *endPoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);
				if(endPoint != NULL)
				{
					endPoint->delete_peer(m_unPeerID);
				}

				return -1;
			}
			else
			{
				m_dwResetTickCount = unNow;
			}
		}
	}
	

	ACE_Message_Block *new_msg = generate_msg(msg);

	if(new_msg == NULL)
	{
		return -1;
	}

	char tmp[1024];
	memcpy(tmp, new_msg->base(), new_msg->length());
	if(m_bReliable)
	{
		int nRet = m_slideWindow.put(unPacketNo, new_msg);

		if(nRet != -1)
		{

			if(nRet == 1)
			{
				ACE_Message_Block *tmp_msg;

				while((tmp_msg = m_slideWindow.get()) != NULL)
				{
					if(put_msg_2_logic(tmp_msg) == -1)
					{
						tmp_msg->release();
					}
				}
			}

			this->ack();
		}

		if(nRet != 1)
		{
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:nRet = %d, PacketNo=%d, currentno=%d",__FILE__, __LINE__, nRet, unPacketNo, m_slideWindow.currentSN());
			pLog->RecordLog(Log_Type_Fucking, pLog->m_szLogBuffer);
			new_msg->release();

			if(nRet == -1)
			{
				//delete this peer
			}
		}
	}
	else
	{
		if(put_msg_2_logic(new_msg) == -1)
		{
			new_msg->release();
		}
	}

	return 0;
}

int ClientPeer::put_Destroy_msg( ACE_Message_Block *msg, ACE_UINT32 unPacketNo /*= 0*/ )
{
	printf("put_Destroy_msg:[%d]\n",m_unPeerID);
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	//judage is too many msg

	CLogBase *pLog = BaseService::GetLogInstance();

//	m_unMsgCount ++;
// 	if (m_unMsgCount % MAX_CLIENT_MSG_PER_2_SECOND == 1)
// 	{
// 		if (m_unMsgCount == 1)
// 		{
// 			m_dwResetTickCount = GetTickCount();
// 		}
// 		else
// 		{
// 			ACE_UINT32 unNow = GetTickCount();
// 			if (unNow < m_dwResetTickCount + 1000)
// 			{
// 				sprintf(pLog->m_szLogBuffer, "[%s][%d]:m_unMsgCount = %d, peerid=%d",__FILE__, __LINE__, m_unMsgCount, m_unPeerID);
// 				pLog->RecordLog(Log_Type_Fucking, pLog->m_szLogBuffer);
// 				//m_endPoint->
// 				ClientEndPoint *endPoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);
// 
// 				if(endPoint != NULL)
// 				{
// 					endPoint->delete_peer(m_unPeerID);
// 				}
// 
// 				return -1;
// 			}
// 			else
// 			{
// 				m_dwResetTickCount = unNow;
// 			}
// 		}
// 	}

	sprintf(pLog->m_szLogBuffer, "[%s][%d]:m_unMsgCount = %d, peerid=%d",__FILE__, __LINE__, m_unMsgCount+1, m_unPeerID);
	pLog->RecordLog(Log_Type_Fucking, pLog->m_szLogBuffer);
	//m_endPoint->
// 	ClientEndPoint *endPoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);
// 	if(endPoint != NULL)
// 	{
// 		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(endPoint->m_mutex);
// 		ACE_Guard<ACE_Recursive_Thread_Mutex> guard1(m_clientMutex->m_mutex);
// 		ACE_Message_Block *new_msg = generate_Destroy_msg(msg);
// 		if(new_msg == NULL)
// 		{
// 			return -1;
// 		}
// 
// 		char tmp[1024];
// 		memcpy(tmp, new_msg->base(), new_msg->length());
// 		if(put_msg_2_logic(new_msg) == -1)
// 		{
// 			new_msg->release();
// 		}
// 
// 		endPoint->delete_peer(m_unPeerID);
// 	}
// 	else
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);
		ACE_Message_Block *new_msg = generate_Destroy_msg(msg);
		if(new_msg == NULL)
		{
			return -1;
		}

		char tmp[1024];
		memcpy(tmp, new_msg->base(), new_msg->length());
		if(put_msg_2_logic(new_msg) == -1)
		{
			new_msg->release();
		}
	}

	return 0;
}

int ClientPeer::send_fail(ACE_Message_Block *msg)
{
	m_sendQueue.enqueue_head(msg);

	return 0;
}


ACE_Message_Block *ClientPeer::generate_msg(ACE_Message_Block *msg)
{
	//copy msg info to msg body,and fill in adr,send to logic obj,set from internet flag

	int len = msg->total_length();

	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, len, SERVICE_MESSAGE_TYPE_USER, OBJ_ID_NONE, m_unAdapterID, m_unPeerID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, 0) == -1)
	{
		return NULL;
	}

	msgInfo.p_head->unCtrlCode |= SERVICE_MESSAGE_CTRL_FROM_INTERNET;

	char *p = msg->base();

	//ACE_OS::strncpy((char *)msgInfo.body, msg->base(), len);
	ACE_OS::memcpy((char *)msgInfo.body, msg->base(), len);

	return msgInfo.msg;
}

ACE_Message_Block * ClientPeer::generate_Destroy_msg( ACE_Message_Block *msg )
{
	//copy msg info to msg body,and fill in adr,send to logic obj,set from internet flag

	int len = msg->total_length();

	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, len, SERVICE_MESSAGE_TYPE_USER, OBJ_ID_NONE, m_unAdapterID, m_unPeerID, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, MSG_DESTROY_MSG_ACK) == -1)
	{
		return NULL;
	}

	msgInfo.p_head->unCtrlCode |= SERVICE_MESSAGE_CTRL_FROM_INTERNET;

	char *p = msg->base();

	//ACE_OS::strncpy((char *)msgInfo.body, msg->base(), len);
	ACE_OS::memcpy((char *)msgInfo.body, msg->base(), len);

	return msgInfo.msg;
}


int ClientPeer::put_msg_2_logic(ACE_Message_Block *msg)
{
	if(m_recvQueue->enqueue_tail(msg) == -1)
	{
		return -1;
	}
	return 0;
}

int ClientPeer::send_msg(ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	ACE_Message_Block *new_msg = NULL;

	StreamRW stream;
	int len = msg->total_length();

	if(m_bReliable)
	{
		//new_msg = new ACE_Message_Block(sizeof(ACE_UINT32) + sizeof(ACE_UINT32));
		new_msg = create_msg_for_send(sizeof(ACE_UINT32) + sizeof(ACE_UINT32));
		if(new_msg != NULL)
		{
			stream.reset(new_msg->base(), new_msg->total_length());
			if(stream.writeInt(m_unPacketNo) == -1 || stream.writeInt(len) == -1)
			{
				new_msg->release();
				new_msg = NULL;
			}
		}
	}
	else
	{
		//new_msg = new ACE_Message_Block(sizeof(ACE_UINT32));
		new_msg = create_msg_for_send(sizeof(ACE_UINT32));
		if(new_msg != NULL)
		{
			stream.reset(new_msg->base(), new_msg->total_length());
			if(stream.writeInt(len) == -1)
			{
				new_msg->release();
				new_msg = NULL;
			}
		}
	}

	if(new_msg == NULL)
	{
		return -1;
	}

	new_msg->cont(msg);

	/*
	if(send_msg_i(new_msg) == -1)
	{
		new_msg->cont(NULL);
		new_msg->release();
		return -1;
	}
	*/

	

	if(m_sendQueue.enqueue_tail(new_msg) == -1)
	{
		new_msg->cont(NULL);
		new_msg->release();
		return -1;
	}

	if(m_bReliable)
	{
		ACE_Message_Block *msg_cache = new_msg->duplicate();
		m_resendList[m_nCurrentResendSlot].insert_tail(msg_cache);
		m_unPacketNo ++;
	}

	this->notify_send();

	//if(m_resendList[m_nCurrentResendSlot].s

	return 0;
}

/*
int ClientPeer::send_msg_i(ACE_Message_Block *msg)
{
	
	if(send_msg_2_connection(msg) == -1)
	{
		if(m_sendQueue.enqueue_tail(msg) == -1)
		{
			return -1;
		}
	}
	return 0;
}
*/

int ClientPeer::send_msg_2_connection(ACE_Message_Block *msg)
{
	/*
	ACE_Message_Block *new_msg = msg->duplicate();

	for(int i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] != NULL && !m_ConnectionList[i]->m_bWriting)
		{
			if(m_ConnectionList[i]->send_msg(new_msg) == 0)
			{
				msg->release();

				return 0;
			}
		}
	}

	new_msg->release();
	return -1;
	*/

	for(ACE_UINT32 i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] != NULL && !m_ConnectionList[i]->m_bWriting)
		{
			if(m_ConnectionList[i]->send_msg(msg) == 0)
			{
				//msg->release();

				return 0;
			}
		}
	}

	return -1;
}

void ClientPeer::notify_send()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	/*
	for(int i = 0;i < m_unMaxConnection;i ++)
	{
		if(m_ConnectionList[i] == pConnection)
		{
			//m_ConnectionList[i].isFree = true;
			break;
		}
	}
	*/

	if(m_sendQueue.is_empty())
	{
		return;
	}

	ACE_Message_Block *msg;

	if(m_sendQueue.dequeue_head(msg) == -1)
	{
		return;
	}

	if(send_msg_2_connection(msg) == -1)
	{
		m_sendQueue.enqueue_head(msg);
	}
}

ACE_UINT32 ClientPeer::get_packet_no(ACE_Message_Block *msg)
{
	StreamRW stream;

	stream.reset(msg->base(), msg->total_length());

	ACE_UINT32 t = 0;

	stream.readInt(t);

	return t;
}

ACE_Message_Block *ClientPeer::create_msg_for_send(int size)
{
	ACE_Message_Block *msg = new ACE_Message_Block(size);
	if(msg == NULL)
	{
		return NULL;
	}

	msg->rd_ptr(msg->base());
	msg->wr_ptr(msg->base() + size);

	return msg;
}

/*
void ClientPeer::timerCallback(void *p, long lTimerID)
{
	ClientPeer *peer = (ClientPeer *)p;
	if(peer != NULL)
	{
		peer->resend_msg();
	}
}
*/

void ClientPeer::resend_msg()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	m_nCurrentResendSlot = (m_nCurrentResendSlot + 1) % CLIENT_PEER_RESEND_SLOT_COUNT;

	CLIENT_PEER_RESEND_SLOTITERATOR iter(m_resendList[m_nCurrentResendSlot]);

	ACE_Message_Block *msg;

	while(!iter.done())
	{
		//add to send queue
		msg = iter.next();

		m_sendQueue.enqueue_tail(msg->duplicate());

		iter.advance();
	}

	//m_unMsgCount = 0;

	this->notify_send();
}

void ClientPeer::get_ack(ACE_UINT32 unPacketNo)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	int i;

	for(i = 0;i < CLIENT_PEER_RESEND_SLOT_COUNT;i ++)
	{
		CLIENT_PEER_RESEND_SLOTITERATOR iter(m_resendList[i]);

		ACE_Message_Block *msg;

		while(!iter.done())
		{
			//add to send queen
			msg = iter.next();

			ACE_UINT32 tmp = get_packet_no(msg);

			if(tmp < unPacketNo)
			{
				iter.remove();
				msg->release();

				//printf("ack, remove msg = %d[%d]\n", tmp, m_unPacketNo);
			}
			else
			{
				//iter.advance();
				break;
			}
		}
	}
}

void ClientPeer::ack()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	if(!m_bReliable)
	{
		return;
	}

	ACE_Message_Block *new_msg = NULL;

	StreamRW stream;

	new_msg = create_msg_for_send(sizeof(ACE_UINT32) + sizeof(ACE_UINT32));

	if(new_msg == NULL)
	{
		return;
	}
	
	stream.reset(new_msg->base(), new_msg->total_length());
	if(stream.writeInt(m_slideWindow.currentSN()) == -1 || stream.writeInt(0) == -1)
	{
		new_msg->release();
		return;
	}

	if(m_sendQueue.enqueue_tail(new_msg) == -1)
	{
		new_msg->release();
		return;
	}

	//printf("ack msg, no = %d\n", m_slideWindow.currentSN());

	this->notify_send();
}

int ClientPeer::get_cached_msg_count()
{
	int c = 0;

	int i;

	for(i = 0;i < CLIENT_PEER_RESEND_SLOT_COUNT;i ++)
	{
		c += m_resendList[i].size();
	}

	return c;
}