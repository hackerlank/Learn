#include "GatewayService.h"
#include "EndPoint\GatewayEndPoint.h"
#include "..\Base\Communication\CommunicationMgr.h"
#include "GatewayMgr.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


GatewayService::GatewayService()
{

}

GatewayService::~GatewayService()
{

}

int GatewayService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	GatewayMgr *gatewayMgr = new GatewayMgr(ADAPTER_GATEWAY_MGR);

	if(gatewayMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(gatewayMgr) == -1)
	{
		delete gatewayMgr;
		return -1;
	}

	BaseEndPoint *endpoint = new GatewayEndPoint(this->msg_queue(), m_ownServiceInfo->wlanAdr.ip, m_ownServiceInfo->wlanAdr.port);

	if(endpoint == NULL)
	{
		return -1;
	}

	//((ClientEndPoint *)endpoint)->set_listen_addr("192.168.1.11", 1600);

	if(COMMUNICATION_MGR_INSTANCE::instance()->addEndpoint(endpoint) == -1)
	{
		return -1;
	}

	return GameService::obj_init(arg, unArgLen);
}

int GatewayService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;
	int c = 0;
	BaseAdapter *adapter = this->getAdapter(ADAPTER_GATEWAY_MGR);

	if(adapter != NULL)
	{
		c = adapter->get_obj_count();
	}

	char tmp[1024];
	ACE_OS::sprintf(tmp, "I'am Gateway!\nOnline User = %d", c);

	len = add_service_info_msg(buff, 0, nMaxSize, tmp);

	return len;
}

void GatewayService::quit_service()
{
	//COMMUNICATION_MGR_INSTANCE::instance()->removeEndpoint(ENDPOINT_TYPE_TCP_INTERNET);

	GameService::quit_service();
}