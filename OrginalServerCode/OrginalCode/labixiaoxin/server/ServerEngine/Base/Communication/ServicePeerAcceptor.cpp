#include "ServicePeerAcceptor.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ServicePeerAcceptor::ServicePeerAcceptor()
{

}

void ServicePeerAcceptor::close()
{
	this->cancel();
	ACE_OS::closesocket(this->handle());
	this->handle(ACE_INVALID_HANDLE);
}

ServiceConnection *ServicePeerAcceptor::make_handler(void)
{
	ServiceConnection *conn = new ServiceConnection();

	if(conn != NULL)
	{
		conn->m_unType = ServiceConnection::TYPE_RECV;
		conn->m_endpoint = m_endpoint;
	}

	return conn;
}

void ServicePeerAcceptor::setEndPoint(ServiceEndPoint *endpoint)
{
	this->m_endpoint = endpoint;
}