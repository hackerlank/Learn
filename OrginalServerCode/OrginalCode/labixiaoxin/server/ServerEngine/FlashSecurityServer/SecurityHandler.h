#pragma once

#include "ace\Asynch_IO.h"
#include "ace\Recursive_Thread_Mutex.h"

class SecurityHandler : public ACE_Service_Handler
{
public:
	SecurityHandler();
	~SecurityHandler();

	virtual void open(ACE_HANDLE h, ACE_Message_Block &msg);
	virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
	virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

private:
	ACE_Asynch_Read_Stream _reader;
	ACE_Asynch_Write_Stream _writer;

	int write_response();
};