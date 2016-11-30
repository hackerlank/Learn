#pragma once

#include "ace\Asynch_IO.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "..\..\Base\Service\ServiceObj.h"
#include "..\..\Base\Communication\StreamRW.h"
#include "..\..\Base\Utils\NetworkMutexMgr.h"

#define MAX_CLIENT_TCP_MSG 4096

class ClientPeer;
class ClientEndPoint;

//typedef void (*Timer_Callback_Func)(void *, long);
//typedef ACE_Message_Block *(*Read_Client_Msg_Func)(char *, int size, ObjAdr &adr);
//typedef int (*Write_Client_Msg_Func)(ACE_Message_Block *msg, char *, int size);

class ClientConnection : public ACE_Service_Handler
{
public:
	enum
	{
		READ_INIT = 0,
		//READ_PACKET_NO,
		READ_SIZE,
		READ_BODY,
		//DESTROY
	};

	enum
	{
		DESTROY_NONE = 0,
		DESTROY_WAIT_SEND_MSG,
		DESTROY_SEND_MSG,
		DESTROY_DONE
	};

	ClientConnection();
	virtual ~ClientConnection();

	//static void register_msg_parse_func(Read_Client_Msg_Func read_func, Write_Client_Msg_Func write_func);
	void set_info(ACE_UINT32 unInitDataSize, ACE_UINT32 unConnectionTimerout, bool bReliable);
	void set_client_end_point(ClientEndPoint *endPoint);

	virtual void open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);

	virtual int openConnection();
	virtual void closeConnection();


	//virtual int init_data_size(){return 0;};
	//virtual ClientPeer *get_client_peer(char *buff, int size) = 0;
	//virtual int recv_init_data(){return 0;};
	//virtual int parse_init_data(){return 0;};

	int send_msg(ACE_Message_Block *msg);

	void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
	void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);

	void set_close_error_code(ACE_UINT32 unErrorCode);

	int send_close_msg();
	void set_peer(ClientPeer *peer);

	void exchange_mutex(ACE_UINT32 unNewID);

	//ACE_Atomic_Op<ACE_Thread_Mutex, int> m_bWriting;

	bool m_bReading;
	bool m_bWriting;

	ClientPeer *m_peer;

protected:
	void reset_recv_msg();
	//void reset_send_msg();

	StreamRW m_stream;

	ACE_Message_Block *m_recvMsg;
	//ACE_Message_Block *m_writeMsg;
	ACE_Asynch_Read_Stream m_rd;
	ACE_Asynch_Write_Stream m_wd;
private:
	//void set_msg_adr();
	void recv_msg_fail();

	int read_msg(int step);
	int put_msg(ACE_Message_Block *msg, ACE_UINT32 unPacketNo);
	int send_done(bool success, ACE_Message_Block *msg);
	

	//static void timerCallback(void *p, long lTimerID);

	ClientEndPoint *m_endPoint;
	
	//ObjAdr m_MsgAdr;
	//static Read_Client_Msg_Func m_read_func;
	//static Write_Client_Msg_Func m_write_func;

	ACE_UINT32 m_unPacketNo;
	ACE_UINT32 m_unMsgSize;
	//ACE_UINT32 m_unReadSize;
	//ACE_UINT32 m_unWriteSize;

	//ACE_Recursive_Thread_Mutex m_mutex;

	//bool m_bDestroyed;
	ACE_UINT32 m_unPeerID;

	int m_nDestroyStep;
	int m_nStep;
	//int m_bWriting;
	ACE_UINT32 m_unConnectionTimerout;

	ACE_UINT32 m_unInitDataSize;

	//long m_lTimerID;
	bool m_bReliable;

	
	ACE_UINT32 m_unCloseErrorCode;

	bool can_destroy();

	ACE_Message_Block *make_close_error_msg(ACE_UINT32 unErrorCode);
	ACE_Message_Block *make_Dstroy_error_msg(ACE_UINT32 unErrorCode);

	bool make_Destroy_msg();

	NetworkMutex *m_clientMutex;

	

	//char m_writeBuffer[MAX_CLIENT_TCP_MSG];
};