#pragma once

#include "..\GameBase\Obj\ClientObj.h"

class LoginSession : public ClientObj
{
public:
	LoginSession(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~LoginSession();

	virtual int deal_client_msg(MessageInfo &msgInfo);
	//virtual int deal_other_msg(MessageInfo &msgInfo);

	virtual void obj_timeout();
	virtual int start_destroy();

	virtual int deal_db_msg(ACE_UINT32 unType, void *msg);

	virtual int parse_into_intranet_msg(MessageInfo &msgInfo,char *buff, int size);
	virtual ACE_Message_Block *parse_into_internet_msg(MessageInfo &msgInfo);

private:
	ACE_Message_Block *create_login_response(int nResult, ACE_UINT32 unIP, ACE_UINT32 unPort, ACE_UINT32 unClientID, char *strSession);

	ACE_UINT32 m_unLiveCounter;

	static ACE_UINT32 m_unGameServerID;

};