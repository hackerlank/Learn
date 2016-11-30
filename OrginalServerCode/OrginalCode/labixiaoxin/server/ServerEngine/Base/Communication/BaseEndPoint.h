#pragma once

#include "ace\Message_Queue.h"
#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "..\Protocol\Protocol.h"

enum
{
	ENDPOINT_TYPE_SERVICE = 0
};

class BaseEndPoint
{
public:
	BaseEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue,char *strIP, ACE_UINT32 unListenPort);
	virtual ~BaseEndPoint();

	virtual int activate() = 0;
	//return true is activate is done
	virtual bool do_activate() = 0;
	virtual void deactivate() = 0;
	virtual bool do_deactivate() = 0;
	//return true is deactivate is done
	virtual int putMsg(ACE_Message_Block *msg);

	virtual int sendMessage(void *des_adr, ACE_Message_Block *msg) = 0;

	//
	ACE_UINT32 get_listen_port(){return m_unListenPort;};
	ACE_UINT32 get_listen_ip(){return m_unListenIP;};

	ACE_UINT32 m_unType;
	ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue();
	ACE_Recursive_Thread_Mutex m_mutex;

protected:

	ACE_Message_Queue<ACE_MT_SYNCH> *m_recvQueue;

	//ACE_Message_Queue<ACE_MT_SYNCH> *m_deleteQueue;//要删除的队列

	ACE_UINT32 m_unListenIP;
	ACE_UINT32 m_unListenPort;

private:
	void set_listen_addr(char *strIP, ACE_UINT32 unListenPort);
};