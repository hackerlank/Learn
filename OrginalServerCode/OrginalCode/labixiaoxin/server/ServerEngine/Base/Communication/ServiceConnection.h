#pragma once

#include "ace\Asynch_IO.h"
#include "ace\Message_Block.h"
#include "ace\Recursive_Thread_Mutex.h"

class ServiceEndPoint;

class ServiceConnection : public ACE_Service_Handler
{
public:
	enum{
		TYPE_SEND = 0,
		TYPE_RECV,
		TYPE_MAX
	};

	enum
	{
		STEP_INIT_ID = 0,
		STEP_RECV_SIZE,
		STEP_RECV_BODY,
		STEP_SEND
	};


	ServiceConnection();
	virtual ~ServiceConnection();

	virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

	int openConnection();
	void closeConnection();

	void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
	void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

	int send_msg(ACE_Message_Block *msg);

	ACE_UINT32 m_unType;

	//ACE_UINT32 m_unOwnServiceID;
	//ACE_UINT32 m_unTargetServiceID;
	ServiceEndPoint *m_endpoint;

private:
	int read_id();
	int read_size();
	int read_body();

	void reset_recv_msg();
	void reset_send_msg(int size);

	int init_send_done();
	int init_recv_done(ACE_UINT32 unTargetServiceID, ACE_UINT32 unTargetIP, ACE_UINT32 unTargetPort);

	int set_init_done();

	bool can_destroy();

	bool m_bReading;
	bool m_bWriting;

	//ServicePeer *m_peer;
	ACE_Recursive_Thread_Mutex m_mutex;

	bool m_bInitSendDone;
	bool m_bInitRecvDone;
	
	ACE_UINT32 m_unTargetServiceID;
	ACE_UINT32 m_unTargetIP;
	ACE_UINT32 m_unTargetPort;

	ACE_UINT32 m_unStep;

	ACE_UINT32 m_unReadSize;
	ACE_UINT32 m_unWriteSize;

	ACE_Message_Block *m_recvMsg;
	ACE_Message_Block *m_sendMsg;
	ACE_Asynch_Read_Stream m_rd;
	ACE_Asynch_Write_Stream m_wd;
};