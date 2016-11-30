#pragma once

#include "..\..\Base\Service\BaseAdapter.h"

#define ADAPTER_GATEWAY_INFO 0x11

class GatewayInfoMgr : public BaseAdapter
{
public:
	GatewayInfoMgr();
	virtual ~GatewayInfoMgr();

	virtual int dealMsg(MessageInfo &msgInfo);
};