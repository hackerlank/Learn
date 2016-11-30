#include "ServerCommandEndPoint.h"

ServerCommandEndPoint::ServerCommandEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue,char *strIP, ACE_UINT32 unListenPort)
:PhpEndPoint(recvQueue, strIP, unListenPort)
{
	m_unDesAdapterID = ADAPTER_ADMIN_COMMAND_MGR;
}
