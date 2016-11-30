#include "PhpAcceptor.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

PhpAcceptor::PhpAcceptor()
{

}

void PhpAcceptor::close()
{
	this->cancel();
	ACE_OS::closesocket(this->handle());
	this->handle(ACE_INVALID_HANDLE);
}

void PhpAcceptor::setEndPoint(PhpEndPoint *endPoint)
{
	m_endPoint = endPoint;
}

PhpConnection *PhpAcceptor::make_handler(void)
{
	PhpConnection *c = new PhpConnection();

	if(c == NULL)
	{
		return NULL;
	}

	c->setEndPoint(m_endPoint);

	return c;
}