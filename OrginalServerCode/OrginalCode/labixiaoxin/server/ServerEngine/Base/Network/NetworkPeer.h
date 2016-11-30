#pragma once

#include "NetworkConnection.h"
#include "ace\Message_Queue.h"
#include "ace\Null_Condition.h"
#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"

class NetworkEndPoint;

class NetworkPeer
{
public:
	NetworkPeer(ACE_UINT32 unIP, ACE_UINT32 unListenPort, NetworkEndPoint *endpoint);
	~NetworkPeer();

private:

	NetworkEndPoint *m_endpoint;

	ACE_Message_Queue<ACE_NULL_SYNCH> m_sendQueue;

	ACE_Recursive_Thread_Mutex m_mutex;
};