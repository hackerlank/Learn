#pragma once

#include "..\Adapter\SubAdapterObj.h"
#include "..\..\Base\Communication\StreamRW.h"

class ClientObj : public SubAdapterObj
{
public:
	ClientObj(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~ClientObj();

	virtual int deal_msg(MessageInfo &msgInfo);
	virtual int deal_client_msg(MessageInfo &msgInfo){return 0;};
	virtual int deal_other_msg(MessageInfo &msgInfo){return 0;};
	void wanna_remove_from_lru(){};
	void cancel_remove_from_lru(){};

	virtual int parse_into_intranet_msg(MessageInfo &msgInfo,char *buff, int size){return -1;};
	virtual ACE_Message_Block *parse_into_internet_msg(MessageInfo &msgInfo){return NULL;};

protected:
	int send_msg_2_internet(ACE_Message_Block *msg);
	ACE_Message_Block *create_send_msg(int size);
	int set_send_size(ACE_Message_Block *msg, int size);

protected:

	StreamRW m_stream;
};