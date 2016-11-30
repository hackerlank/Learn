#pragma once

#include "..\GameBase\Adapter\SubAdapterObj.h"
#include "..\Base\Communication\StreamRW.h"

class PhpProxySession : public SubAdapterObj
{
public:
	PhpProxySession(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~PhpProxySession();

	virtual int deal_msg(MessageInfo &msgInfo);

	int deal_client_msg(MessageInfo &msgInfo);
	int deal_other_msg(MessageInfo &msgInfo);

	void wanna_remove_from_lru(){};
	void cancel_remove_from_lru(){};

	virtual void obj_timeout();
	virtual int start_destroy();

	int parse_into_intranet_msg(MessageInfo &msgInfo,char *buff, int size);
	ACE_Message_Block *parse_into_internet_msg(MessageInfo &msgInfo);

private:
	int send_msg_2_internet(const char *str);
	int send_msg_2_internet(ACE_Message_Block *msg);
	void send_fail_msg(int errorCode);

	ACE_UINT32 m_unLiveCounter;
	StreamRW m_stream;

	static ACE_UINT32 m_unGameServerID;
	static ACE_UINT32 m_unUserInfoServerID;
};