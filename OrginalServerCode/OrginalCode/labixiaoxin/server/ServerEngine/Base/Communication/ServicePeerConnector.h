#pragma once

#include "ace\Asynch_Connector.h"
#include "ServiceConnection.h"

class ServiceEndPoint;

class ServicePeerConnector : public ACE_Asynch_Connector<ServiceConnection>
{
public:
	
	ServicePeerConnector();
	void setEndPoint(ServiceEndPoint *endpoint);
	void close();
	
protected:
	virtual ServiceConnection *make_handler(void);
	virtual void handle_time_out(const ACE_Time_Value &tv, const void *act = 0);
	virtual int validate_connection(const ACE_Asynch_Connect::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local);

private:
	ServiceEndPoint *m_endpoint;
};