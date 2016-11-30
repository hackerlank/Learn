#pragma once

#include "ace\Asynch_Acceptor.h"
#include "ClientConnection.h"
#include "..\..\Base\Communication\BaseEndPoint.h"

class ClientEndPoint;

class ClientAcceptor : public ACE_Asynch_Acceptor<ClientConnection>
{
public:
	ClientAcceptor();
	void setEndPoint(ClientEndPoint *endPoint);
	void close();

protected:
	virtual ClientConnection *make_handler(void);
	virtual int validate_connection(const ACE_Asynch_Accept::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local);

private:
	ClientEndPoint *m_endPoint;
};