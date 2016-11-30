#pragma once

#include "PhpProxySession.h"
#include "..\GameBase\Adapter\SubAdapter.h"

class PhpProxyMgr : public SubAdapter
{
public:
	PhpProxyMgr(ACE_UINT32 unID);
	virtual ~PhpProxyMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);
	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};

	virtual int deal_msg(MessageInfo &msgInfo);

private:
	ACE_UINT32 m_unGameServerID;
};