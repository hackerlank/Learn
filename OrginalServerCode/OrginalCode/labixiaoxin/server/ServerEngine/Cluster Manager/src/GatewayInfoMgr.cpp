#include "GatewayInfoMgr.h"

GatewayInfoMgr::GatewayInfoMgr()
:BaseAdapter(ADAPTER_GATEWAY_INFO)
{

}

GatewayInfoMgr::~GatewayInfoMgr()
{

}

int GatewayInfoMgr::dealMsg(MessageInfo &msgInfo)
{
	return 0;
}