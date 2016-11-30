#include "BaseConnection.h"

BaseConnection::BaseConnection()
{
	m_endpoint = NULL;
	m_unStatus = DEACTIVE;
}

BaseConnection::BaseConnection(BaseEndPoint *endpoint)
{
	m_endpoint = endpoint;
	m_unStatus = DEACTIVE;
}

BaseConnection::~BaseConnection()
{

}

void BaseConnection::setEndPoint(BaseEndPoint *endpoint)
{
	m_endpoint = endpoint;
}
