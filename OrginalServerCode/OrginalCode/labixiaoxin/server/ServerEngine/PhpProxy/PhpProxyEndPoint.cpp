#include "PhpProxyEndPoint.h"

PhpProxyEndPoint::PhpProxyEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
:PhpEndPoint(recvQueue, strIP, unListenPort)
{
	m_unDesAdapterID = ADAPTER_PHP_PROXY_MGR;
}
