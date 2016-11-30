#pragma once

#include "ace\Asynch_Acceptor.h"
#include "PhpConnection.h"
#include "..\..\Base\Communication\BaseEndPoint.h"

//class ClientEndPoint;
class PhpEndPoint;

class PhpAcceptor : public ACE_Asynch_Acceptor<PhpConnection>
{
public:
	PhpAcceptor();
	void setEndPoint(PhpEndPoint *endPoint);
	void close();
protected:
	virtual PhpConnection *make_handler(void);

private:
	PhpEndPoint *m_endPoint;
};