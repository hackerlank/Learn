#pragma once

#include "..\..\Base\Service\BaseAdapter.h"

#define ADAPTER_ONLINE_USER 0x10 

class OnlineUserMgr : public BaseAdapter
{
public:
	OnlineUserMgr();
	virtual ~OnlineUserMgr();

	virtual int dealMsg(MessageInfo &msgInfo);
};