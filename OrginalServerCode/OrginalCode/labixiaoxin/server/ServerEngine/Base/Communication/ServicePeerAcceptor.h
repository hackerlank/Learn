#pragma once

#include "ace\Asynch_Acceptor.h"
#include "ServiceConnection.h"

class ServiceEndPoint;

class ServicePeerAcceptor : public ACE_Asynch_Acceptor<ServiceConnection>
{
public:
	ServicePeerAcceptor();
	void setEndPoint(ServiceEndPoint *endpoint);
	void close();
protected:
	virtual ServiceConnection *make_handler(void);

private:
	ServiceEndPoint *m_endpoint;
};