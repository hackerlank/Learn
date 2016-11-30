#pragma once

#include "..\..\GameBase\Game Network\ClientEndPoint.h"

class LoginEndPoint : public ClientEndPoint
{
public:
	LoginEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort);
	virtual ~LoginEndPoint();

	virtual int parse_connection_init_data(char *buff, int size, ConnectionInitData &info);
	virtual ClientConnection *newConnection();

private:
	ACE_UINT32 m_unPeerIDCounter;

};