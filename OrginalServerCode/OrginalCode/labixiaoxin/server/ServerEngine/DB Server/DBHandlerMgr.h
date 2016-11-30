#pragma once

#include "..\GameBase\Adapter\SubAdapter.h"
#include "DBUserHandler.h"

class DBHandlerMgr : public SubAdapter
{
public:
	DBHandlerMgr(ACE_UINT32 unID);
	virtual ~DBHandlerMgr();

	//virtual BaseObj *new_child_obj(ACE_UINT32 unID){return new DBUserHandler(unID, this);};

	//virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	//virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};

	ACE_UINT32 m_unDBRequestCount;

	void increase_request_count();
	void decrease_request_count();

protected:
	ACE_UINT32 m_unGameServerID;
};