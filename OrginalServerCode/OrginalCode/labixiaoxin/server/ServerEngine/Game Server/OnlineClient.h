#pragma once

#include "..\Base\Service\BaseObj.h"
#include "..\GameBase\Protocol\ControlProtocol.h"

class OnlineClient : public BaseObj
{
public:
	OnlineClient(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~OnlineClient();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	//virtual void create_done();
	virtual int start_running();
	virtual int deal_msg(MessageInfo &msgInfo);

	void set_login_response_adr(ObjAdr &adr);

	bool is_same_login(ACE_UINT32 unLoginID);

private:
	//ACE_UINT32 m_unLoginID;
	ObjAdr m_loginResponseAdr;
	char m_strSession[CLIENT_SESSION_LEN + 1];

	//void send_login_info(ACE_UINT32 unIP, ACE_UINT32 unPort, ACE_UINT32 unAdapterID, ACE_UINT32 unLoginID);
	void send_login_info(ACE_UINT32 unIP, ACE_UINT32 unPort, ObjAdr &desAdr);
	void generate_session_id();
	void send_gateway_request();
};