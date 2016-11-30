#pragma once

#include "DBHandlerMgr.h"
#include "DBUserHandler.h"

class DBUserMgr : public DBHandlerMgr
{
public:
	DBUserMgr(ACE_UINT32 unID);
	virtual ~DBUserMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);

	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};
};