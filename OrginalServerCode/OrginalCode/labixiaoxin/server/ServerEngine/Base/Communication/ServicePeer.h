#pragma once

#include "ServiceConnection.h"
#include "ace\Message_Queue.h"
#include "ace\Null_Condition.h"
#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"

class ServiceEndPoint;

class ServicePeer
{
public:
	enum
	{
		SENDSTATUS_DISCONNECTED = 0,
		SENDSTATUS_CONNECTING,
		SENDSTATUS_CONNECTED
	};
	

	ServicePeer(ACE_UINT32 unTargetServiceID, ACE_UINT32 unIP, ACE_UINT32 unListenPort, ServiceEndPoint *endpoint);
	~ServicePeer();

	void update_service_info(ACE_UINT32 unIP, ACE_UINT32 unListenPort);
	void reset(bool bNeedClose);
	int send_msg(ACE_Message_Block *msg);
	void set_connection(ServiceConnection *conn, ACE_UINT32 unType);
	void notify_send_done(ACE_Message_Block *msg);
	void remove_connection(ACE_UINT32 unType);
	void establish_send_connection();
	//void set_recv_sn(bool bInit, ACE_UINT32 unSendSN);
	//void put_msg(ACE_Message_Block *msg);

	ACE_UINT32 m_unTargetServiceID;

	ACE_UINT32 m_unTargetIP;
	ACE_UINT32 m_unTargetPort;

private:
	
	void close();
	void close(ACE_UINT32 unType);
	void connect();
	void send_msg_i();

	ServiceConnection *m_connList[ServiceConnection::TYPE_MAX];

	ACE_UINT32 m_unSendStatus;
	bool m_bSending;
	bool m_bInited;

	//ACE_UINT32 m_unSendSN;
	//ACE_UINT32 m_unRecvSN;
	//ACE_UINT32 m_unAckSN;
	//bool m_bInitRecvSN;
	//bool m_bInitSendSN;

	ServiceEndPoint *m_endpoint;

	ACE_Message_Queue<ACE_NULL_SYNCH> m_sendQueue;

	ACE_Recursive_Thread_Mutex m_mutex;
};