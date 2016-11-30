#include "GatewayEndPoint.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


#define GATEWAY_CONNECTION_INIT_DATA_SIZE (sizeof(ACE_UINT32) + CLIENT_SESSION_LEN)

GatewayEndPoint::GatewayEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
:ClientEndPoint(recvQueue, strIP, unListenPort)
{
	m_unPeerMaxConnection = 1;
	//m_unListenPort = 1600;
	m_bReliable = true;
	m_unAdapterID = ADAPTER_GATEWAY_MGR;
}

GatewayEndPoint::~GatewayEndPoint()
{

}

int GatewayEndPoint::parse_connection_init_data(char *buff, int size, ConnectionInitData &info)
{
	if(size != GATEWAY_CONNECTION_INIT_DATA_SIZE)
	{
		return -1;
	}

	StreamRW stream;
	stream.reset(buff, size);

	//if(stream.readInt(info.unPeerID) == -1 || stream.readInt(info.unSessionID) == -1)
	if(stream.readInt(info.unPeerID) == -1 || stream.readStringFixLen(info.strSession, CLIENT_SESSION_LEN) == -1)
	{
		return -1;
	}

	info.strSession[CLIENT_SESSION_LEN] = '\0';

	printf("get size =%d,peerid=%d,session = %s\n",size,info.unPeerID, info.strSession);

	return 0;
}

ClientConnection *GatewayEndPoint::newConnection()
{
	ClientConnection *t = new ClientConnection();

	if(t == NULL)
	{
		return NULL;
	}

	t->set_info(GATEWAY_CONNECTION_INIT_DATA_SIZE, 3, true);

	return t;
}
