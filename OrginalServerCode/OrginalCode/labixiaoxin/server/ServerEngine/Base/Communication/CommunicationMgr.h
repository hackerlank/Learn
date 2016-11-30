#pragma once

#include "ace\ace.h"
#include "ace\Singleton.h"
#include "ace\Mutex.h"

#include "BaseEndPoint.h"
#include "..\Protocol\Protocol.h"

#define MAX_ENDPOINT_COUNT 16

class CommunicationMgr
{
public:
	CommunicationMgr();
	~CommunicationMgr();

	ACE_INT32 startup(ACE_Message_Queue<ACE_MT_SYNCH> *msg_queue,ACE_Message_Queue<ACE_MT_SYNCH> *msg_delete_queue, char *strIP, ACE_UINT32 unListenIP, ACE_UINT32 bServiceMgr);
	void shutdown();

	int addEndpoint(BaseEndPoint *endpoint);
	BaseEndPoint *getEndPoint(ACE_UINT32 unType){return m_endpointList[unType];};
	void removeEndpoint(ACE_UINT32 unType);

	int sendMsg(ACE_UINT32 unEndpointType, void *des_adr, ACE_Message_Block *msg);
	int send_local_msg(ACE_Message_Block *msg);

private:
	static ACE_THR_FUNC_RETURN activateProactor(void *opParam);

	int m_nProactorThreadID;

	BaseEndPoint *m_endpointList[MAX_ENDPOINT_COUNT];
	ACE_Message_Queue<ACE_MT_SYNCH> *m_recvMsgQueue;
	//ACE_Message_Queue<ACE_MT_SYNCH> *m_deleteMsgQueue;
};

typedef ACE_Singleton<CommunicationMgr, ACE_Thread_Mutex> COMMUNICATION_MGR_INSTANCE;