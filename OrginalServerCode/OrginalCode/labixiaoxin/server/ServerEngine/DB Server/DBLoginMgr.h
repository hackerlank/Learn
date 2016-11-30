#pragma once

#include "DBHandlerMgr.h"
#include "DBLoginHandler.h"

class DBLoginMgr : public DBHandlerMgr
{
public:
	DBLoginMgr(ACE_UINT32 unID);
	virtual ~DBLoginMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);

	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};
};