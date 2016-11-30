#include "ServiceConnection.h"
#include "..\Service\ServiceObj.h"
#include "ServiceEndPoint.h"
#include "..\Service\BaseService.h"
#include "..\Utils\NetworkMutexMgr.h"
#include "ace\OS_NS_sys_socket.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ServiceConnection::ServiceConnection()
{
	NETWORK_MUTEXT_MGR_INSTANCE::instance()->increase_connection_count(ENDPOINT_TYPE_SERVICE);

	m_unType = TYPE_SEND;
	m_recvMsg = NULL;
	m_sendMsg = NULL;
	m_unReadSize = 0;
	m_unWriteSize = 0;

	m_unTargetServiceID = OBJ_ID_NONE;
	m_unTargetIP = 0;
	m_unTargetPort = 0;

	//m_unOwnServiceID = m_unTargetServiceID = OBJ_ID_NONE;
	//m_peer = NULL;
	m_bReading = m_bWriting = false;
	m_endpoint = NULL;
	m_bInitSendDone = m_bInitRecvDone = false;
}

ServiceConnection::~ServiceConnection()
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

	printf("delete service connection[0x%08x][%d][0x%08x]\n", (int)this, m_unType, m_unTargetServiceID);

	NETWORK_MUTEXT_MGR_INSTANCE::instance()->decrease_connection_count(ENDPOINT_TYPE_SERVICE);
}

void ServiceConnection::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{
	if(openConnection() == -1)
	{
		closeConnection();
		delete this;
	}
}

int ServiceConnection::openConnection()
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

	if(read_id() == -1)
	{
		return -1;
	}

	m_unStep = STEP_INIT_ID;
	return 0;
}

void ServiceConnection::closeConnection()
{
	m_endpoint->remove_connection(m_unTargetServiceID, m_unType);

	m_rd.cancel();
	m_wd.cancel();

	ACE_OS::closesocket(this->handle());

	
}

void ServiceConnection::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
{
	bool isFailed = false;

	ACE_Message_Block &mb = result.message_block();

	//printf("service connection read callback[0x%08x][0x%08x]\n", (int)this, this->m_unTargetServiceID);

	m_bReading = false;

	if(!result.success() || result.bytes_transferred() == 0)
	{
		//printf("recv msg error,size = %d[%d]\n", m_unReadSize, result.bytes_transferred());
		isFailed = true;
	}
	else if(result.bytes_transferred() < result.bytes_to_read())
	{
		if(m_rd.read(mb, result.bytes_to_read() - result.bytes_transferred()) == -1)
		{
			isFailed = true;
		}
		else
		{
			m_bReading = true;
		}
	}
	else
	{
		switch(m_unStep)
		{
		case STEP_INIT_ID:
			{
				MsgServiceInfo *p = (MsgServiceInfo *)mb.base();
				if(init_recv_done(p->unServiceID, p->unIP, p->unPort) == -1)
				{
					isFailed = true;
				}
			}
			break;
		case STEP_RECV_SIZE:
			{
				ACE_UINT32 *p = (ACE_UINT32 *)mb.base();
				m_unReadSize = *p;

				if(read_body() == -1)
				{
					//closeConnection();
					isFailed = true;
				}
			}
			break;
		case STEP_RECV_BODY:
			{
				//printf("recv msg,size = %d\n", m_unReadSize);
				//put msg to peer
				if(m_endpoint->putMsg(&mb) == -1)
				{
					//change by xxj 2015/07/24  0: 12:24 
					mb.release();
				}
				
				if(read_size() == -1)
				{
					//closeConnection();
					isFailed = true;
				}
			}
			break;
		default:
			isFailed = true;
			break;
		}
	}

	if(isFailed)
	{
		this->closeConnection();

		//can destroy
		if(can_destroy())
		{
			delete this;
		}
	}
}

void ServiceConnection::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
{
	bool isFailed = true;

	bool success = true;
	bool writeDone = false;

	ACE_Message_Block &mb = result.message_block();
	ACE_Message_Block *msg = mb.cont();

	//printf("service connection write callback[0x%08x][0x%08x]\n", (int)this, this->m_unTargetServiceID);

	if(!result.success() || result.bytes_transferred() == 0)
	{
		success = false;
		writeDone = true;
	}
	else if(result.bytes_transferred() < result.bytes_to_write())
	{
		if(m_wd.writev(mb, result.bytes_to_write() - result.bytes_transferred()) == -1)
		{
			success = false;
			writeDone = true;
		}
		else
		{
			success = true;
			writeDone = false;
		}
	}
	else
	{
		success = true;
		writeDone = true;
	}

	if(success)
	{
		isFailed = false;
		if(writeDone)
		{
			mb.cont(NULL);
			if(m_unStep == STEP_INIT_ID)
			{
				if(init_send_done() == -1)
				{
					isFailed = true;
				}
			}
			else if(m_unStep == STEP_SEND)
			{
				if(msg != NULL)
				{
					msg->release();
				}
				m_endpoint->notify_send_done(m_unTargetServiceID, NULL);
			}
		}
	}
	else
	{
		isFailed = true;
		mb.cont(NULL);
		if(m_unStep == STEP_SEND)
		{
			m_endpoint->notify_send_done(m_unTargetServiceID, msg);
		}
	}

	{
		ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
		m_bWriting = !writeDone;
	}

	if(isFailed)
	{
		this->closeConnection();

		//can destroy
		if(can_destroy())
		{
			delete this;
		}
	}
}

//m_bInitSendDone = m_bInitRecvDone

int ServiceConnection::init_send_done()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_bInitSendDone)
	{
		return 0;
	}

	m_bInitSendDone = true;
	return set_init_done();
}

int ServiceConnection::init_recv_done(ACE_UINT32 unTargetServiceID, ACE_UINT32 unTargetIP, ACE_UINT32 unTargetPort)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_bInitRecvDone)
	{
		return 0;
	}

	m_bInitRecvDone = true;
	m_unTargetServiceID = unTargetServiceID;
	m_unTargetIP = unTargetIP;
	m_unTargetPort = unTargetPort;

	return set_init_done();
}

int ServiceConnection::set_init_done()
{
	if(!m_bInitRecvDone || !m_bInitSendDone)
	{
		return 1;
	}

	if(m_endpoint->set_service_peer_connection(m_unTargetServiceID, m_unTargetIP, m_unTargetPort, this, m_unType) == NULL)
	{
		return -1;
	}

	if(read_size() == -1)
	{
		return -1;
	}

	if(m_unType == TYPE_RECV)
	{
		
	}
	else
	{
		m_unStep = STEP_SEND;
	}

	return 0;
}

void ServiceConnection::reset_recv_msg()
{
	if(m_recvMsg == NULL)
	{
		return;
	}
	m_recvMsg->wr_ptr(m_recvMsg->base());
	m_recvMsg->rd_ptr(m_recvMsg->base());
}

void ServiceConnection::reset_send_msg(int size)
{
	if(m_sendMsg == NULL)
	{
		return;
	}
/*
	ACE_Message_Block * block = m_sendMsg->cont();
	if (block)
	{
		block->release();
	}
*/
	m_sendMsg->wr_ptr(m_sendMsg->base() + size);
	m_sendMsg->rd_ptr(m_sendMsg->base());
}

int ServiceConnection::send_msg(ACE_Message_Block *msg)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
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

	//printf("write msg size = %d\n", len);

	m_bWriting = true;

	return 0;
}

int ServiceConnection::read_id()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	reset_recv_msg();
	reset_send_msg(sizeof(MsgServiceInfo));

	m_unReadSize = sizeof(MsgServiceInfo);

	if(m_rd.read(*m_recvMsg, m_unReadSize) == -1)
	{
		return -1;
	}

	m_bReading = true;

	MsgServiceInfo *p = (MsgServiceInfo *)m_sendMsg->base();

	p->unServiceID = BaseService::instance()->serviceID();
	p->unIP = m_endpoint->get_listen_ip();
	p->unPort = m_endpoint->get_listen_port();

	m_unWriteSize = sizeof(MsgServiceInfo);

	if(m_wd.writev(*m_sendMsg, m_unWriteSize) == -1)
	{
		return -1;
	}

	m_bWriting = true;

	m_unStep = STEP_INIT_ID;

	return 0;
}

int ServiceConnection::read_size()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	reset_recv_msg();

	m_unReadSize = sizeof(ACE_UINT32);

	if(m_rd.read(*m_recvMsg, sizeof(ACE_UINT32)) == -1)
	{
		return -1;
	}

	m_unStep = STEP_RECV_SIZE;
	m_bReading = true;

	return 0;
}

int ServiceConnection::read_body()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	ACE_Message_Block * msg = new ACE_Message_Block(m_unReadSize);

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

	m_bReading = true;

	return 0;
}

bool ServiceConnection::can_destroy()
{
	bool flag = false;

	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	//flag = (!m_bReading && m_nDestroyStep == DESTROY_DONE);
	flag = (!m_bReading && !m_bWriting);

	return flag;
}