#pragma once

#include "SecurityAcceptor.h"

class SecurityService
{
public:
	SecurityService();
	~SecurityService();

	void activate(char *strIP);

private:
	SecurityAcceptor _listener;
};