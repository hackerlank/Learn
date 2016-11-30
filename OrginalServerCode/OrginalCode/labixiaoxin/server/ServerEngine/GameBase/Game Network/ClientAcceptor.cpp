#include "ClientAcceptor.h"
#include "ClientEndPoint.h"

ClientAcceptor::ClientAcceptor()
{
	m_endPoint = NULL;
}

void ClientAcceptor::setEndPoint(ClientEndPoint *endPoint)
{
	m_endPoint = endPoint;
}

void ClientAcceptor::close()
{
	this->cancel();
	ACE_OS::closesocket(this->handle());
	this->handle(ACE_INVALID_HANDLE);
}

ClientConnection *ClientAcceptor::make_handler(void)
{
	ClientConnection *c = ((ClientEndPoint *)m_endPoint)->newConnection();

	if(c == NULL)
	{
		return NULL;
	}

	c->set_client_end_point(m_endPoint);

	return c;
}

int ClientAcceptor::validate_connection(const ACE_Asynch_Accept::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local)
{
	char tmp[64];

	remote.addr_to_string(tmp, 48);

	printf("client remote ip = %s\n", tmp);

	return 0;

}