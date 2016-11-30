#pragma once

#include "..\..\GameBase\Game Network\ClientEndPoint.h"

class GatewayEndPoint : public ClientEndPoint
{
public:
	GatewayEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort);
	virtual ~GatewayEndPoint();

	virtual int parse_connection_init_data(char *buff, int size, ConnectionInitData &info);
	virtual ClientConnection *newConnection();
};