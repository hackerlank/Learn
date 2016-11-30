#pragma once

#include "..\GameBase\Adapter\SubAdapter.h"
#include "GatewaySession.h"



class GatewayMgr : public SubAdapter
{
public:
	GatewayMgr(ACE_UINT32 unID);
	virtual ~GatewayMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);
	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};
private:
	ACE_UINT32 m_unGameServerID;
};