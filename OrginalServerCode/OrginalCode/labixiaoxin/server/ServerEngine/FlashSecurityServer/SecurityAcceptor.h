#pragma once

#include "ace\Asynch_Acceptor.h"
#include "SecurityHandler.h"


class SecurityAcceptor : public ACE_Asynch_Acceptor<SecurityHandler>
{
public:
	SecurityAcceptor();
protected:
	virtual SecurityHandler *make_handler(void);
};