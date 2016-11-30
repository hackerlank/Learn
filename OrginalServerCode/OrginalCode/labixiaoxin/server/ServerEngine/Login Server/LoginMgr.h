#pragma once

#include "LoginSession.h"
#include "..\GameBase\Adapter\SubAdapter.h"

class LoginMgr : public SubAdapter
{
public:
	LoginMgr(ACE_UINT32 unID);
	virtual ~LoginMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);
	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};

	virtual int deal_msg(MessageInfo &msgInfo);

	ACE_UINT32 current_login_ID(){return m_unCurrentLoginID;};

private:
	ACE_UINT32 m_unGameServerID;

	ACE_UINT32 m_unCurrentLoginID;
};