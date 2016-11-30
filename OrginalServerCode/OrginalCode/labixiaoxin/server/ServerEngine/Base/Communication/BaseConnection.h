#pragma once

#include "ace\Asynch_IO.h"
#include "ace\Message_Queue.h"
#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"

class BaseEndPoint;

class BaseConnection : public ACE_Service_Handler
{
public:
	enum
	{
		DEACTIVE = 0,
		DISCONNECTED,
		CONNECTING,
		CONNECTED,
		DISCONNECTING
	};

	BaseConnection();
	BaseConnection(BaseEndPoint *endpoint);
	virtual ~BaseConnection();

	void setEndPoint(BaseEndPoint *endpoint);

	virtual int openConnection() = 0;
	virtual void closeConnection() = 0;

	BaseEndPoint *m_endpoint;
protected:
	//ACE_Message_Queue<ACE_MT_SYNCH> m_recvQueue;
	//ACE_Message_Queue<ACE_MT_SYNCH> m_sendQueue;

	ACE_Recursive_Thread_Mutex m_mutex;

	ACE_UINT32 m_unStatus;
};