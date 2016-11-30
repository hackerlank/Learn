#pragma once

#include "..\GameBase\Common\GameService.h"

class UserInfoService : public GameService
{
public:
	UserInfoService();
	~UserInfoService();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	virtual void obj_fini();

	virtual int get_service_info_msg(char *buff, int nMaxSize);
};