#pragma once

#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"

class PhpProxyEndPoint : public PhpEndPoint
{
public:
	PhpProxyEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue,char *strIP, ACE_UINT32 unListenPort);
};