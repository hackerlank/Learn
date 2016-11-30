#include "GatewayInfo.h"

GatewayInfo::GatewayInfo(ACE_UINT32 unID, BaseAdapter *parent)
:BaseObj(unID, parent)
{

}

GatewayInfo::~GatewayInfo()
{

}

int GatewayInfo::dealMsg(MessageInfo &msgInfo)
{
	return 0;
}