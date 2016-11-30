#include "UserInfoService.h"
#include "UserInfoEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "UserInfoMgr.h"
#include "InfoDBMgr.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif
#include "DBLogMgr.h"

UserInfoService::UserInfoService()
{

}

UserInfoService::~UserInfoService()
{

}

int UserInfoService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	if(GameService::obj_init(arg, unArgLen) == -1)
	{
		return -1;
	}

	if(INFO_DB_MGR_INSTANCE::instance()->init() == -1)
	{
		return -1;
	}

	if (DB_LOG_MGR_INSTANCE::instance()->init(this) == -1)
	{
		return -1;
	}

	UserInfoMgr *userInfoMgr = new UserInfoMgr(ADAPTER_USER_INFO_MGR);

	if(userInfoMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(userInfoMgr) == -1)
	{
		delete userInfoMgr;
		return -1;
	}

	/*
	BaseEndPoint *endpoint = new UserInfoEndPoint(this->msg_queue(), m_ownServiceInfo->wlanAdr.ip, m_ownServiceInfo->wlanAdr.port);

	if(endpoint == NULL)
	{
		return -1;
	}

	//((ClientEndPoint *)endpoint)->set_listen_addr("192.168.1.11", 1500);

	if(COMMUNICATION_MGR_INSTANCE::instance()->addEndpoint(endpoint) == -1)
	{
		delete endpoint;
		return -1;
	}
	*/

	//userInfoMgr->readAllFriendFromDB();
	return 0;
}

void UserInfoService::obj_fini()
{
	GameService::obj_fini();

	INFO_DB_MGR_INSTANCE::instance()->fini();
}

int UserInfoService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;
	int c = 0;

	UserInfoMgr *userInfoMgr = (UserInfoMgr *)this->getAdapter(ADAPTER_USER_INFO_MGR);

	if(userInfoMgr != NULL)
	{
		c = userInfoMgr->get_user_count();
	}

	char tmp[1024];
	ACE_OS::sprintf(tmp, "I'am User Info Server!\nUser Info Count = %d", c);

	len = add_service_info_msg(buff, 0, nMaxSize, tmp);

	return len;
}