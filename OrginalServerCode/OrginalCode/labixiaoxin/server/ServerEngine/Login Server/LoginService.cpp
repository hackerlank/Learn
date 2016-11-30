#include "LoginService.h"
#include "EndPoint\LoginEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "LoginMgr.h"
#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


LoginService::LoginService()
{

}

LoginService::~LoginService()
{

}

int LoginService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	if(GameService::obj_init(arg, unArgLen) == -1)
	{
		return -1;
	}

	LoginMgr *loginMgr = new LoginMgr(ADAPTER_LOGIN_MGR);

	if(loginMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(loginMgr) == -1)
	{
		delete loginMgr;
		return -1;
	}


	BaseEndPoint *endpoint = new LoginEndPoint(this->msg_queue(), m_ownServiceInfo->wlanAdr.ip, m_ownServiceInfo->wlanAdr.port);

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

	return 0;
}

int LoginService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;

	ACE_UINT32 c = 0;

	LoginMgr *loginMgr = (LoginMgr *)this->getAdapter(ADAPTER_LOGIN_MGR);

	if(loginMgr != NULL)
	{
		c = loginMgr->current_login_ID();
	}

	char tmp[1024];
	ACE_OS::sprintf(tmp, "I'am Login Server!\nCurrent login ID = %d", c);

	len = add_service_info_msg(buff, 0, nMaxSize, tmp);

	return len;
}

void LoginService::quit_service()
{
	//COMMUNICATION_MGR_INSTANCE::instance()->removeEndpoint(ENDPOINT_TYPE_TCP_INTERNET);

	GameService::quit_service();
}