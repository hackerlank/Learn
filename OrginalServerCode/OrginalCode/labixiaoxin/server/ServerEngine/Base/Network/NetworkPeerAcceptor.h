#pragma once

#include "ace\Asynch_Acceptor.h"
#include "NetworkConnection.h"

class NetworkEndPoint;

class NetworkPeerAcceptor : public ACE_Asynch_Acceptor<NetworkConnection>
{
public:
	NetworkPeerAcceptor();
	void setEndPoint(NetworkEndPoint *endpoint);
	void close();
protected:
	virtual NetworkConnection *make_handler(void);

private:
	NetworkEndPoint *m_endpoint;
};