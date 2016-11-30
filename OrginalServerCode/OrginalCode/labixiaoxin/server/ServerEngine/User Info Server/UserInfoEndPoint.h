#pragma once

#include "..\GameBase\PhpEndPoint\PhpEndPoint.h"

class UserInfoEndPoint : public PhpEndPoint
{
public:
	UserInfoEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort);

	virtual int put_msg(ACE_Message_Block *msg, PhpConnection *connection);
};