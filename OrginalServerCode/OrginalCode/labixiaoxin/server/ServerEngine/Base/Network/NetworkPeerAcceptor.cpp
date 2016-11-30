#include "NetworkPeerAcceptor.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif

NetworkPeerAcceptor::NetworkPeerAcceptor()
{

}

void NetworkPeerAcceptor::close()
{
	this->cancel();
	ACE_OS::closesocket(this->handle());
	this->handle(ACE_INVALID_HANDLE);
}

NetworkConnection *NetworkPeerAcceptor::make_handler(void)
{
	NetworkConnection *conn = new NetworkConnection();

	if(conn != NULL)
	{
		//conn->m_unType = ServiceConnection::TYPE_RECV;
		conn->m_endpoint = m_endpoint;
	}

	return conn;
}

void NetworkPeerAcceptor::setEndPoint(NetworkEndPoint *endpoint)
{
	this->m_endpoint = endpoint;
}