#include "BaseEndPoint.h"
#include "ace\INET_Addr.h"

BaseEndPoint::BaseEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
{
	m_recvQueue = recvQueue;
	m_unType = 0;
	set_listen_addr(strIP, unListenPort);
}

BaseEndPoint::~BaseEndPoint()
{
	
}

ACE_Message_Queue<ACE_MT_SYNCH> *BaseEndPoint::recvQueue()
{
	return m_recvQueue;
}

int _n = 0;
int BaseEndPoint::putMsg(ACE_Message_Block *msg)
{
	_n++;
	if (_n >= 1000)
	{
		printf("--:%d\n",m_recvQueue->message_count());
		_n = 0;
	}
	ACE_Time_Value nowait(ACE_OS::gettimeofday());
	nowait += 2;
	if(m_recvQueue->enqueue_tail(msg,&nowait) == -1)
	{
		printf("recvQueue is full!!\n");
		return -1;
	}
	return 0;
}

void BaseEndPoint::set_listen_addr(char *strIP, ACE_UINT32 unListenPort)
{
	u_short port = (u_short)unListenPort;
	ACE_INET_Addr t_adr(port, strIP);
	m_unListenIP = t_adr.get_ip_address();
	m_unListenPort = unListenPort;
}