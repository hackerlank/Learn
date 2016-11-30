#pragma once

#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"

class ServerCommandEndPoint : public PhpEndPoint
{
public:
	ServerCommandEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort);
};