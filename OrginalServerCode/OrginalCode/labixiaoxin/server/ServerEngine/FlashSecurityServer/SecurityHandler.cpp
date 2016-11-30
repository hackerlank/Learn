#include "SecurityHandler.h"

#include "ace\OS_NS_sys_socket.h"
#include "ace\Message_Block.h"
#include "ace\OS_NS_string.h"
//#if _MEMORY_DEBUG
//#include "../GameBase/Common/debugnew.h"
//#define new new(__FILE__, __LINE__)
//#endif


const char *strSecurityRequest="<policy-file-request/>";


const char *strSecurityResponse="<cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"*\" /></cross-domain-policy>";

SecurityHandler::SecurityHandler()
{

}

SecurityHandler::~SecurityHandler()
{
	if(this->handle() != ACE_INVALID_HANDLE)
	{
		ACE_OS::closesocket(this->handle());
	}
}

void SecurityHandler::open(ACE_HANDLE h, ACE_Message_Block &msg)
{
	this->handle(h);

	if(this->_reader.open(*this) != 0 || this->_writer.open(*this) != 0)
	{
		delete this;
		return;
	}

	ACE_Message_Block *mb;
	ACE_NEW_NORETURN(mb, ACE_Message_Block(1024));

	if(this->_reader.read(*mb, strlen(strSecurityRequest) + 1) != 0)
	{
		mb->release();
		delete this;
		return;
	}
}

void SecurityHandler::handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
{
	ACE_Message_Block &mb = result.message_block();

	if(!result.success() || result.bytes_transferred() == 0)
	{
		mb.release();
		delete this;
	}
	else if(result.bytes_transferred() < result.bytes_to_read())
	{
		if(_reader.read(mb, result.bytes_to_read() - result.bytes_transferred()) == -1)
		{
			mb.release();
			ACE_OS::closesocket(this->handle());
		}
		return;
	}
	else
	{
		char *str = mb.base();

		str[strlen(strSecurityRequest)] = '\0';

		if(ACE_OS::strcmp(str, strSecurityRequest) == 0)
		{
			if(write_response() == -1)
			{
				ACE_OS::closesocket(this->handle());
			}
		}
		else
		{
			ACE_OS::closesocket(this->handle());
		}

		mb.release();
	}
}

void SecurityHandler::handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
{
	ACE_Message_Block &mb = result.message_block();

	if(!result.success() || result.bytes_transferred() == 0)
	{
		mb.release();
		ACE_OS::closesocket(this->handle());
	}
	else if(result.bytes_transferred() < result.bytes_to_write())
	{
		if(_writer.writev(mb, result.bytes_to_write() - result.bytes_transferred()) == -1)
		{
			mb.release();
			ACE_OS::closesocket(this->handle());
		}
	}
	else
	{
		mb.release();
		ACE_OS::closesocket(this->handle());
	}
}

int SecurityHandler::write_response()
{
	ACE_Message_Block *mb;

	int size = strlen(strSecurityResponse) + 1;
	
	mb = new ACE_Message_Block(size);

	if(mb == NULL)
	{
		return -1;
	}

	ACE_OS::memcpy(mb->base(), strSecurityResponse, size);

	mb->rd_ptr(mb->base());
	mb->wr_ptr(mb->base() + size);

	if(_writer.writev(*mb, size) == -1)
	{
		mb->release();
		return -1;
	}
	
	return 0;
}