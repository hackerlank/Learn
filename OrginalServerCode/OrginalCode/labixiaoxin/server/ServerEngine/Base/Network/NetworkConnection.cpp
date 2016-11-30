#include "NetworkConnection.h"
#include "..\Service\ServiceObj.h"
#include "NetworkEndPoint.h"
#include "..\Service\BaseService.h"

#include "ace\OS_NS_sys_socket.h"
#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

NetworkConnection::NetworkConnection()
{
	m_recvMsg = NULL;
	m_sendMsg = NULL;
	m_unReadSize = 0;
	m_unWriteSize = 0;
	m_peer = NULL;
	m_endpoint = NULL;
}

NetworkConnection::~NetworkConnection()
{
	if(m_recvMsg != NULL)
	{
		m_recvMsg->release();
		m_recvMsg = NULL;
	}

	if(m_sendMsg != NULL)
	{
		m_sendMsg->release();
		m_sendMsg = NULL;
	}
}

void NetworkConnection::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{
	if(openConnection() == -1)
	{
		closeConnection();

		delete this;
	}
}

int NetworkConnection::openConnection()
{
	if((m_recvMsg = new ACE_Message_Block(sizeof(MsgServiceInfo))) == NULL)
	{
		return -1;
	}

	if((m_sendMsg = new ACE_Message_Block(sizeof(MsgServiceInfo))) == NULL)
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

	/*
	if(read_id() == -1)
	{
		return -1;
	}

	m_unStep = STEP_INIT_ID;
	*/
	return 0;
}

void NetworkConnection::closeConnection()
{
	m_rd.cancel();
	m_wd.cancel();

	ACE_OS::closesocket(this->handle());

	/*
	if(m_peer != NULL)
	{
		m_peer->remove_connection(m_unType);
		m_peer = NULL;
	}
	*/
}

void NetworkConnection::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
{
	ACE_Message_Block &mb = result.message_block();

	if(!result.success() || result.bytes_transferred() == 0)
	{
		//printf("recv msg error,size = %d[%d]\n", m_unReadSize, result.bytes_transferred());
		//closeConnection();
		//delete this;
		//return;
	}
	else if(result.bytes_transferred() < result.bytes_to_read())
	{
		if(m_rd.read(mb, result.bytes_to_read() - result.bytes_transferred()) == -1)
		{
			closeConnection();
		}
		//return;
	}
	else
	{
	}
	
}

void NetworkConnection::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
{
	ACE_Message_Block &mb = result.message_block();
	ACE_Message_Block *msg = mb.cont();
	//mb.cont(NULL);

	if(!result.success() || result.bytes_transferred() == 0)
	{
		
	}
	else if(result.bytes_transferred() < result.bytes_to_write())
	{
		
	}
	else
	{
		
	}
}

void NetworkConnection::reset_recv_msg()
{
	if(m_recvMsg == NULL)
	{
		return;
	}
	m_recvMsg->wr_ptr(m_recvMsg->base());
	m_recvMsg->rd_ptr(m_recvMsg->base());
}

void NetworkConnection::reset_send_msg(int size)
{
	if(m_sendMsg == NULL)
	{
		return;
	}
	m_sendMsg->wr_ptr(m_sendMsg->base() + size);
	m_sendMsg->rd_ptr(m_sendMsg->base());
}

int NetworkConnection::send_msg(ACE_Message_Block *msg)
{
	/*
	reset_send_msg(sizeof(ACE_UINT32));

	ACE_UINT32 len = msg->length();
	ACE_UINT32 *p = (ACE_UINT32 *)m_sendMsg->base();
	*p = len;

	m_sendMsg->cont(msg);

	m_unWriteSize = sizeof(ACE_UINT32) + len;

	if(m_wd.writev(*m_sendMsg, m_unWriteSize) == -1)
	{
		m_sendMsg->cont(NULL);
		return -1;
	}
	*/

	return 0;
}


int NetworkConnection::read_size()
{
	/*
	reset_recv_msg();

	m_unReadSize = sizeof(ACE_UINT32);

	if(m_rd.read(*m_recvMsg, sizeof(ACE_UINT32)) == -1)
	{
		return -1;
	}

	m_unStep = STEP_RECV_SIZE;
	*/

	return 0;
}

int NetworkConnection::read_body()
{
	/*
	ACE_Message_Block *msg = new ACE_Message_Block(m_unReadSize);

	if(msg == NULL)
	{
		return -1;
	}

	if(m_rd.read(*msg, m_unReadSize) == -1)
	{
		msg->release();
		return -1;
	}

	m_unStep = STEP_RECV_BODY;
	*/

	return 0;
}