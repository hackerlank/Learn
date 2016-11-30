#include "ClientConnection.h"

#include "ClientPeer.h"
#include "ClientEndPoint.h"

#include "..\..\base\TimerMgr\TimerMgr.h"

#include "ace\OS_NS_sys_socket.h"

//#define MAX_CLIENT_TCP_MSG 1024

//Read_Client_Msg_Func ClientConnection::m_read_func = NULL;
//Write_Client_Msg_Func ClientConnection::m_write_func = NULL;
#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ClientConnection::ClientConnection()
{
	m_recvMsg = NULL;
	m_peer = NULL;
	m_endPoint = NULL;
	m_unConnectionTimerout = 0;
	m_unInitDataSize = 0;
	m_unPacketNo = 0;
	m_bWriting = false;
	m_bReading = false;
	m_nDestroyStep = DESTROY_NONE;
	m_unCloseErrorCode = CLIENT_CLOSE_ERROR_NONE;
	m_unPeerID = 0;
	m_clientMutex = NETWORK_MUTEXT_MGR_INSTANCE::instance()->acquire(ENDPOINT_TYPE_TCP_INTERNET, m_unPeerID);
}

ClientConnection::~ClientConnection()
{
	if(m_recvMsg != NULL)
	{
		m_recvMsg->release();
		m_recvMsg = NULL;
	}

	NETWORK_MUTEXT_MGR_INSTANCE::instance()->release(ENDPOINT_TYPE_TCP_INTERNET, m_unPeerID);
}

void ClientConnection::set_info(ACE_UINT32 unInitDataSize, ACE_UINT32 unConnectionTimerout, bool bReliable)
{
	m_unConnectionTimerout = unConnectionTimerout;
	m_unInitDataSize = unInitDataSize;
	m_bReliable = bReliable;
}

void ClientConnection::set_client_end_point(ClientEndPoint *endPoint)
{
	m_endPoint = endPoint;
}

bool ClientConnection::can_destroy()
{
	bool flag = false;

	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);
	//flag = (!m_bReading && m_nDestroyStep == DESTROY_DONE);
	flag = (!m_bReading && !m_bWriting);

	return flag;
}

void ClientConnection::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{
	if(openConnection() == -1)
	{
		closeConnection();
		delete this;
	}
}

int ClientConnection::openConnection()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if((m_recvMsg = new ACE_Message_Block(MAX_CLIENT_TCP_MSG)) == NULL)
	{
		return -1;
	}

	if(m_rd.open(*this, this->handle()) == -1)
	{
		ACE_ERROR ((LM_ERROR,"%p\n","ACE_Asynch_Read_Stream::open"));
		return -1;
	}

	if(m_wd.open(*this, this->handle()) == -1)
	{
		ACE_ERROR ((LM_ERROR,"%p\n","ACE_Asynch_Write_Stream::open"));
		return -1;
	}

	reset_recv_msg();

	if(m_unInitDataSize == 0)
	{
		if(m_endPoint->validate_connection(NULL, 0, this, true) == -1)
		{
			return -1;
		}

		if(read_msg(READ_SIZE) == -1)
		{
			return -1;
		}

		/*
		m_peer = m_endPoint->create_client_peer(NULL, 0, this, true);

		if(m_peer == NULL)
		{
			return -1;
		}

		exchange_mutex(m_peer->m_unPeerID);

		if(read_msg(READ_SIZE) == -1)
		{
			return -1;
		}
		*/
	}
	else
	{
		m_nStep = READ_INIT;
		//m_unReadSize = m_unInitDataSize;
		if(m_rd.read(*m_recvMsg, m_unInitDataSize) == -1)
		{
			return -1;
		}
		else
		{
			m_bReading = true;
		}
	}

	return 0;
}

void ClientConnection::closeConnection()
{
	m_wd.cancel();
	m_rd.cancel();

	ACE_OS::closesocket(this->handle());
}

void ClientConnection::reset_recv_msg()
{
	if(m_recvMsg == NULL)
	{
		return;
	}
	m_recvMsg->wr_ptr(m_recvMsg->base());
	m_recvMsg->rd_ptr(m_recvMsg->base());
}

void ClientConnection::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
{
	bool isFailed = true;
	//bool readFlag = false;

	int nextStep = -1;

	m_bReading = false;

	ACE_Message_Block &mb = result.message_block();

	if(!result.success() || result.bytes_transferred() == 0)
	{
		printf("connection error:%d,%d,%d\n",result.error(),result.success(),result.bytes_transferred());
	}
	else if(result.bytes_transferred() < result.bytes_to_read())
	{
		if(m_rd.read(mb, result.bytes_to_read() - result.bytes_transferred()) == -1)
		{
		}
		else
		{
			isFailed = false;
			m_bReading = true;
		}
	}
	else
	{
		if(m_nStep == READ_INIT)
		{
			if(m_recvMsg->total_length() == m_unInitDataSize)
			{
				if(m_endPoint->validate_connection(m_recvMsg->base(), m_unInitDataSize, this, false) == -1)
				{
					this->set_close_error_code(CLIENT_CLOSE_ERROR_INVALID_SESSION);
				}
				
				if(send_close_msg() == 0)
				{
					nextStep = READ_SIZE;
					isFailed = false;
				}
				else
				{
					isFailed = true;
				}
			}
		}
		else if(m_nStep == READ_SIZE)
		{
			m_stream.reset(m_recvMsg->base(), m_recvMsg->total_length());

			if(m_bReliable)
			{
				if(m_stream.readInt(m_unPacketNo) == 0 && m_stream.readInt(m_unMsgSize) == 0)
				{
					nextStep = READ_BODY;
					/*printf("get msg size, packet no = %d, size = %d[%d]\n", m_unPacketNo, m_unMsgSize, (int)this);*/

					if(m_unMsgSize == 0)
					{
						//ack msg
						ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);
						if(m_peer != NULL)
						{
							m_peer->get_ack(m_unPacketNo);
						}
						
						nextStep = READ_SIZE;
					}
				}
			}
			else
			{
				if(m_stream.readInt(m_unMsgSize) == 0)
				{
					nextStep = READ_BODY;
					//printf("get msg size, size = %d[%d]\n", m_unMsgSize, (int)this);
				}
			}		
		}
		else if(m_nStep == READ_BODY)
		{
			if(m_recvMsg->total_length() == m_unMsgSize)
			{
				/*printf("get msg body, size = %d[%d]\n", m_unMsgSize, (int)this);*/
				put_msg(m_recvMsg, m_unPacketNo);
				nextStep = READ_SIZE;
				/*
				if(put_msg(m_recvMsg, m_unPacketNo) == 0)
				{
					nextStep = READ_SIZE; 
				}
				*/
			}
		}
	}

	if(nextStep != -1)
	{
		int read_ret = this->read_msg(nextStep);
		if(read_ret == -1)
		{
			isFailed = true;
		}
		else if(read_ret == -2)
		{
			isFailed = false;

			this->set_close_error_code(CLIENT_CLOSE_ERROR_NEW_CONNECTION);
				
			if(send_close_msg() == 0)
			{
				
			}
			else
			{
				isFailed = true;
			}
		}
		else
		{
			isFailed = false;
		}
	}

	if(isFailed)
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);
		if(m_peer != NULL)
		{
			m_peer->remove_client_connection(this);
		}

		this->closeConnection();
	}
	
	if(can_destroy())
	{
		if (make_Destroy_msg())//É¾³ý
			printf("connection destroyed from read callback\n");
		else
			printf("connection destroyed from read callback error\n");

		delete this;
	}
}

void ClientConnection::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
{
	bool success = true;
	bool writeDone = false;
	bool isFailed = true;
	if(!result.success() || result.bytes_transferred() == 0)
	{
		success = false;
	}
	else if(result.bytes_transferred() < result.bytes_to_write())
	{
		if(m_wd.writev(result.message_block(), result.bytes_to_write() - result.bytes_transferred()) == -1)
		{
			success = false;
		}
		else
		{
			success = true;
			writeDone = false;
		}
	}
	else
	{
		/*printf("write data success[%d][%d]\n", result.bytes_transferred(), (int)this);*/
		writeDone = true;
		success = true;
	}

	if(success && !writeDone)
	{
		isFailed = false;
	}
	else
	{
		if(this->send_done(success, &result.message_block()) == -1)
		{
			isFailed = true;
		}
		else
		{
			isFailed = false;
		}
	}

	if(isFailed)
	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);
		if(m_peer != NULL)
		{
			m_peer->remove_client_connection(this);
		}

		this->closeConnection();
	}

	//judge can destroy
	if(can_destroy())
	{
		if (make_Destroy_msg())//É¾³ý
			printf("connection destroyed from read callback\n");
		else
			printf("connection destroyed from read callback error\n");

		delete this;
	}
}

int ClientConnection::send_msg(ACE_Message_Block *msg)
{
	int s = msg->total_length();

	if(m_wd.writev(*msg, s) == -1)
	{
		return -1;
	}

	m_bWriting = true;

	return 0;
}

int ClientConnection::read_msg(int step)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	m_bReading = false;

	int s = 0;
	if(step == READ_SIZE)
	{
		s = sizeof(ACE_UINT32);
		if(m_bReliable)
		{
			s += sizeof(ACE_UINT32);
		}
	}
	else if(step == READ_BODY)
	{
		s = m_unMsgSize;
	}
	else
	{
		return -1;
	}

	if(s > MAX_CLIENT_TCP_MSG || s <= 0)
	{
		return -2;
	}

	reset_recv_msg();

	if(m_rd.read(*m_recvMsg, s) == -1)
	{
		return -1;
	}

	m_bReading = true;
	m_nStep = step;
	return 0;
}

int ClientConnection::put_msg(ACE_Message_Block *msg, ACE_UINT32 unPacketNo)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	if(m_nDestroyStep != DESTROY_NONE)
	{
		return -1;
	}

	if(m_peer != NULL && m_peer->put_msg(msg, unPacketNo) == 0)
	{
		return 0;
	}

	return -1;
}

int ClientConnection::send_done(bool success, ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	m_bWriting = false;

	int nRet = -1;

	if(success)
	{
		msg->release();
		if(m_nDestroyStep == DESTROY_NONE)
		{
			if(m_peer != NULL)
			{
				m_peer->notify_send();
			}
			nRet = 0;
		}
		else if(m_nDestroyStep == DESTROY_WAIT_SEND_MSG)
		{
			if(send_close_msg() == -1)
			{
				nRet = -1;
			}
			else
			{
				nRet = 0;
				
			}
		}
		else if(m_nDestroyStep == DESTROY_SEND_MSG)
		{
			m_nDestroyStep = DESTROY_DONE;
			nRet = -1;
		}

	}
	else
	{
		if(m_nDestroyStep == DESTROY_NONE)
		{
			if(m_peer != NULL)
			{
				m_peer->send_fail(msg);	
			}
		}
		else
		{
			msg->release();
		}

		m_nDestroyStep = DESTROY_DONE;
		nRet = -1;
	}

	return nRet;
}

int ClientConnection::send_close_msg()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	if(m_bWriting)
	{
		return 0;
	}

	if(m_nDestroyStep == DESTROY_WAIT_SEND_MSG)
	{
		//send msg
		ACE_Message_Block *msg = make_close_error_msg(m_unCloseErrorCode);

		if(msg == NULL)
		{
			return -1;
		}

		if(this->send_msg(msg) == -1)
		{
			return -1;
		}

		m_nDestroyStep = DESTROY_SEND_MSG;
	}
	
	

	return 0;
}

void ClientConnection::set_close_error_code(ACE_UINT32 unErrorCode)
{
	if(m_nDestroyStep != DESTROY_NONE)
	{
		return;
	}

	m_nDestroyStep = DESTROY_WAIT_SEND_MSG;
	m_unCloseErrorCode = unErrorCode;
}

ACE_Message_Block *ClientConnection::make_close_error_msg(ACE_UINT32 unErrorCode)
{
	int s = 2 * sizeof(ACE_UINT32);

	ACE_Message_Block *msg = ClientPeer::create_msg_for_send(s);

	if(msg == NULL)
	{
		return NULL;
	}

	StreamRW stream;
	stream.reset(msg->base(), msg->total_length());

	if(stream.writeInt(0xffffffff) == -1 || stream.writeInt(unErrorCode) == -1)
	{
		msg->release();
		return NULL;
	}

	return msg;
}

ACE_Message_Block * ClientConnection::make_Dstroy_error_msg( ACE_UINT32 unErrorCode )
{
	int s = 2 * sizeof(ACE_UINT32);

	ACE_Message_Block *msg = ClientPeer::create_msg_for_send(s);

	if(msg == NULL)
	{
		return NULL;
	}

	StreamRW stream;
	stream.reset(msg->base(), msg->total_length());

	if(stream.writeInt(MSG_DESTROY_MSG_ACK) == -1 || stream.writeInt(unErrorCode) == -1)
	{
		msg->release();
		return NULL;
	}

	return msg;
}

void ClientConnection::set_peer(ClientPeer *peer)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

	m_peer = peer;
}

void ClientConnection::exchange_mutex(ACE_UINT32 unNewID)
{
	if(m_unPeerID == unNewID)
	{
		return;
	}

	NETWORK_MUTEXT_MGR_INSTANCE::instance()->release(ENDPOINT_TYPE_TCP_INTERNET, m_unPeerID);
	m_unPeerID = unNewID;
	m_clientMutex = NETWORK_MUTEXT_MGR_INSTANCE::instance()->acquire(ENDPOINT_TYPE_TCP_INTERNET, m_unPeerID);
}

bool ClientConnection::make_Destroy_msg()
{
	if (m_peer)
	{
		//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_clientMutex->m_mutex);

		ACE_Message_Block *msg = make_Dstroy_error_msg(m_unCloseErrorCode);

		if(msg == NULL)
		{
			return false;
		}

		if(m_nDestroyStep != DESTROY_NONE)
		{
			return false;
		}

		if(m_peer->put_Destroy_msg(msg, m_unPacketNo+1) == 0)
		{
			return true;
		}
	}

	return false;
}

