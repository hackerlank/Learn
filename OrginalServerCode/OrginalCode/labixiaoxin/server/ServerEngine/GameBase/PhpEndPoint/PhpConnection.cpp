#include "PhpConnection.h"

#include "..\..\base\TimerMgr\TimerMgr.h"

#include "ace\OS_NS_sys_socket.h"
#include "PhpEndPoint.h"

//#define MAX_CLIENT_TCP_MSG 1024

//Read_Client_Msg_Func ClientConnection::m_read_func = NULL;
//Write_Client_Msg_Func ClientConnection::m_write_func = NULL;

PhpConnection::PhpConnection()
{
	//m_recvMsg = NULL;
	m_bReading = false;
	m_bWriting = false;
	m_unPeerID = 0;
}

PhpConnection::~PhpConnection()
{
	m_endPoint->remove_connection(m_unPeerID);
}

void PhpConnection::setEndPoint(PhpEndPoint *endPoint)
{
	m_endPoint = endPoint;
}

void PhpConnection::open(ACE_HANDLE new_handle, ACE_Message_Block &message_block)
{
	if(openConnection() == -1)
	{
		closeConnection();
		delete this;
	}
}

int PhpConnection::openConnection()
{
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

	if(read_msg_body() == -1)
	{
		return -1;
	}

	return 0;
}

void PhpConnection::closeConnection()
{
	m_wd.cancel();
	m_rd.cancel();

	ACE_OS::closesocket(this->handle());
}

void PhpConnection::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
{
	bool isFailed = true;
	m_bReading = false;

	ACE_Message_Block &mb = result.message_block();

	if(!result.success() || result.bytes_transferred() == 0)
	{
		printf("connection error:%d,%d,%d\n",result.error(),result.success(),result.bytes_transferred());
		//mb.release();
		//closeConnection();
		//delete this;
		//return;
	}
	else if(result.bytes_transferred() < result.bytes_to_read())
	{
		if(isStringEnd(mb.base(), m_nReadOffset, m_nReadOffset + result.bytes_transferred()))
		{
			//put msg 2 client
			if(putPhpRequest(&mb) == -1)
			{
				//closeConnection();
			}
			else
			{
				isFailed = false;
			}
		}
		else
		{
			m_nReadOffset = (PACKET_HEAD_SIZE + result.bytes_transferred());
			if(m_rd.read(mb, result.bytes_to_read() - result.bytes_transferred()) == -1)
			{
				//closeConnection();
			}
			else
			{
				isFailed = false;
				m_bReading = true;
			}
		}
	}
	else
	{
		if(isStringEnd(mb.base(), m_nReadOffset, m_nReadOffset + result.bytes_transferred()))
		{
			//put msg 2 client
			if(putPhpRequest(&mb) == -1)
			{
				//closeConnection();
			}
			else
			{
				isFailed = false;
			}
		}
		else
		{
			//closeConnection();
		}
	}

	if(isFailed)
	{
		mb.release();
		this->closeConnection();

		if(can_destroy())
		{
			printf("connection destroyed from read callback\n");
			delete this;
		}
	}
}

void PhpConnection::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
{
	//bool success = true;
	//bool writeDone = false;
	m_bWriting = false;
	//bool isFailed = true;

	if(!result.success() || result.bytes_transferred() == 0)
	{
	}
	else if(result.bytes_transferred() < result.bytes_to_write())
	{
		if(m_wd.writev(result.message_block(), result.bytes_to_write() - result.bytes_transferred()) == -1)
		{
		}
		else
		{
			m_bWriting = true;
			//isFailed = false;
		}
	}
	else
	{
		//isFailed = false;
	}

	if(!m_bWriting)
	{
		result.message_block().release();
		this->closeConnection();
	}


	if(can_destroy())
	{
		printf("connection destroyed from write callback\n");
		delete this;
	}
}

int PhpConnection::send_msg(ACE_Message_Block *msg)
{
	if(m_wd.writev(*msg, msg->total_length()) == -1)
	{
		return -1;
	}

	m_bWriting = true;

	return 0;
}


int PhpConnection::read_msg_body()
{
	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, MAX_PHP_TCP_MSG, SERVICE_MESSAGE_TYPE_USER, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, 0) == -1)
	{
		return -1;
	}

	m_nReadOffset = PACKET_HEAD_SIZE;

	msgInfo.msg->wr_ptr((msgInfo.msg->base() + m_nReadOffset));
	msgInfo.msg->rd_ptr(msgInfo.msg->base());

	msgInfo.p_head->unCtrlCode |= SERVICE_MESSAGE_CTRL_FROM_INTERNET;

	if(m_rd.read(*msgInfo.msg, MAX_PHP_TCP_MSG) == -1)
	{
		msgInfo.msg->release();
		return -1;
	}

	m_bReading = true;

	return 0;
}

bool PhpConnection::isStringEnd(char *str, int start, int end)
{
	for(int i = end - 1;i >= start;i --)
	{
		if(str[i] == '\n')
		{
			return true;
		}
	}

	return false;
}

int PhpConnection::putPhpRequest(ACE_Message_Block *msg)
{
	return m_endPoint->put_msg(msg ,this);
}

bool PhpConnection::can_destroy()
{
	bool flag = false;

	flag = (!m_bReading && !m_bWriting);

	return flag;
}