#pragma once

#include "ace\Asynch_IO.h"
#include "ace\Message_Block.h"

class NetworkPeer;
class NetworkEndPoint;

class NetworkConnection : public ACE_Service_Handler
{
public:
	NetworkConnection();
	virtual ~NetworkConnection();

	virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

	virtual int openConnection();
	virtual void closeConnection();

	void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
	void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

	virtual int send_msg(ACE_Message_Block *msg);

	NetworkEndPoint *m_endpoint;

private:
	int read_size();
	int read_body();

	void reset_recv_msg();
	void reset_send_msg(int size);

	NetworkPeer *m_peer;
	
	ACE_UINT32 m_unTargetServiceID;

	ACE_UINT32 m_unReadSize;
	ACE_UINT32 m_unWriteSize;

	ACE_Message_Block *m_recvMsg;
	ACE_Message_Block *m_sendMsg;
	ACE_Asynch_Read_Stream m_rd;
	ACE_Asynch_Write_Stream m_wd;
};