#pragma once

#include "..\..\Base\Service\BaseObj.h"

class GatewayInfo : public BaseObj
{
public:
	GatewayInfo(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~GatewayInfo();

	virtual int dealMsg(MessageInfo &msgInfo);
};