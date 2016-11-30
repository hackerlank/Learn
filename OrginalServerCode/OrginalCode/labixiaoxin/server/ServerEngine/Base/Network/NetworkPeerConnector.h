#pragma once

#include "ace\Asynch_Connector.h"
#include "NetworkConnection.h"

class NetworkEndPoint;

class NetworkPeerConnector : public ACE_Asynch_Connector<NetworkConnection>
{
public:
	
	NetworkPeerConnector();
	void setEndPoint(NetworkEndPoint *endpoint);
	void close();
	
protected:
	virtual NetworkConnection *make_handler(void);
	virtual void handle_time_out(const ACE_Time_Value &tv, const void *act = 0);
	virtual int validate_connection(const ACE_Asynch_Connect::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local);

private:
	NetworkEndPoint *m_endpoint;
};