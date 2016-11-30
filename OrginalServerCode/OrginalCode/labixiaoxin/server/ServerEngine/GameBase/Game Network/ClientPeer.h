#pragma once

#include "ClientConnection.h"
#include "ace\Message_Queue.h"
#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "ace\Null_Condition.h"
#include "ace\Containers.h"

#include "..\..\Base\Communication\SlideWindow.h"
#include "..\Protocol\ControlProtocol.h"

#include "..\..\Base\Utils\NetworkMutexMgr.h"

#define MAX_CLIENT_CONNECTION 3

//#define CLIENT_PEER_TIMER_INTERVAL 2
#define CLIENT_PEER_RESEND_SLOT_COUNT 10

typedef ACE_DLList<ACE_Message_Block> CLIENT_PEER_RESEND_SLOT;
typedef ACE_DLList_Iterator<ACE_Message_Block> CLIENT_PEER_RESEND_SLOTITERATOR;

/*
typedef struct tagClientConnectionInfo
{
	ClientConnection *pConnection;
	bool isFree;
}ClientConnectionInfo;
*/

class ClientPeer
{
public:
	ClientPeer(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, ACE_UINT32 unAdapterID, ACE_UINT32 unPeerID, char *strSession, ACE_UINT32 unMaxConnection, bool bReliable);
	virtual ~ClientPeer();

	int add_client_connection(ClientConnection *pConnection, char *strSession);
	int remove_client_connection(ClientConnection *pConnection);
	void remove_all_connection();
	void reset_all_connection();

	void reset();

	int put_msg(ACE_Message_Block *msg, ACE_UINT32 unPacketNo = 0);
	int send_msg(ACE_Message_Block *msg);
	int send_fail(ACE_Message_Block *msg);
	void get_ack(ACE_UINT32 unPacketNo);
	void ack();

	void notify_send();

	ACE_UINT32 m_unPeerID;
	ACE_UINT32 m_unAdapterID;
	//ACE_UINT32 m_unSessionID;
	char m_strSession[CLIENT_SESSION_LEN + 1];

	static ACE_Message_Block *create_msg_for_send(int size);

	void resend_msg();

	int put_Destroy_msg(ACE_Message_Block *msg, ACE_UINT32 unPacketNo = 0);
	//ACE_Recursive_Thread_Mutex m_mutex;
private:
	//void resendMsg();

	int send_msg_2_connection(ACE_Message_Block *msg);
	//int send_msg_i(ACE_Message_Block *msg);
	//void send_ack(ACE_UINT32 unPacketNo);
	//bool is_ack_msg(char *buff, int offset);
	ACE_UINT32 get_packet_no(ACE_Message_Block *msg);
	ACE_Message_Block *generate_msg(ACE_Message_Block *msg);
	ACE_Message_Block *generate_Destroy_msg(ACE_Message_Block *msg);

	
	
	int put_msg_2_logic(ACE_Message_Block *msg);

	ACE_UINT32 m_unMaxConnection;
	
	ClientConnection *m_ConnectionList[MAX_CLIENT_CONNECTION];

	bool m_bReliable;
	ACE_Message_Queue<ACE_MT_SYNCH> *m_recvQueue;
	ACE_Message_Queue<ACE_NULL_SYNCH> m_sendQueue;

	int m_nCurrentResendSlot;
	CLIENT_PEER_RESEND_SLOT m_resendList[CLIENT_PEER_RESEND_SLOT_COUNT];

	SlideWindow m_slideWindow;
	//SendSlot m_sendSlot;

	ACE_UINT32 m_unPacketNo;
	int m_nCurrentConnectionCount;

	NetworkMutex *m_clientMutex;

	

	ACE_UINT32 m_unMsgCount;
	ACE_UINT32 m_dwResetTickCount;
	int get_cached_msg_count();
};