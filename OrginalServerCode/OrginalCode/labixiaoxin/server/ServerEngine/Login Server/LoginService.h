#pragma once

#include "..\GameBase\Common\GameService.h"

class LoginService : public GameService
{
public:
	LoginService();
	~LoginService();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);

	virtual int get_service_info_msg(char *buff, int nMaxSize);

	virtual void quit_service();
};