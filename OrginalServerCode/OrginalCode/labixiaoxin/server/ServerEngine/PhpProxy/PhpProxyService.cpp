#include "PhpProxyService.h"
#include "PhpProxyEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "PhpProxyMgr.h"
#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


PhpProxyService::PhpProxyService()
{

}

PhpProxyService::~PhpProxyService()
{

}

int PhpProxyService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	PhpProxyMgr *proxyMgr = new PhpProxyMgr(ADAPTER_PHP_PROXY_MGR);

	if(proxyMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(proxyMgr) == -1)
	{
		delete proxyMgr;
		return -1;
	}


	BaseEndPoint *endpoint = new PhpProxyEndPoint(this->msg_queue(), m_ownServiceInfo->wlanAdr.ip, m_ownServiceInfo->wlanAdr.port);

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

	return GameService::obj_init(arg, unArgLen);
}

int PhpProxyService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;
	len = add_service_info_msg(buff, 0, nMaxSize, "I'am Php Proxy!");

	return len;
}

void PhpProxyService::quit_service()
{
	//COMMUNICATION_MGR_INSTANCE::instance()->removeEndpoint(ENDPOINT_TYPE_TCP_PHP);

	GameService::quit_service();
}