#pragma once

#include "..\..\Base\Service\BaseObj.h"

class OnlineUser : public BaseObj
{
public:
	enum{
		STATUS_VERIFY = 0,
		STATUS_CREATE_CLIENT_PROXY,
		STATUS_NORMAL
	};

	OnlineUser(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~OnlineUser();

	virtual int dealMsg(MessageInfo &msgInfo);

private:
	ACE_UINT32 m_unCurrentWorldID;
	ACE_UINT32 m_unCurrentEntityID;
};