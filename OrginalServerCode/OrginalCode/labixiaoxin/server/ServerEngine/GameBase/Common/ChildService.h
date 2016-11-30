#pragma once

#include "ace\ace.h"

class ChildService
{
public:
	ChildService(ACE_UINT32 unServiceID);
	~ChildService();

	virtual void set_status(void *pbuff, int size) = 0;
	virtual void *get_status() = 0;

	ACE_UINT32 m_unServiceID;
};