#pragma once

#include "..\GameBase\Common\GameService.h"

class DBService : public GameService
{
public:
	DBService();
	~DBService();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	virtual void obj_fini();

	virtual int get_service_info_msg(char *buff, int nMaxSize);

	ACE_UINT32 m_unLoginDBRequestCount;
	ACE_UINT32 m_unUserDBRequestCount;
};