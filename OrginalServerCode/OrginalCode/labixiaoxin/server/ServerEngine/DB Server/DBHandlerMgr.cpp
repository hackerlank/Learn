#include "DBHandlerMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"

//#define MAX_DB_HANDLER 100

DBHandlerMgr::DBHandlerMgr(ACE_UINT32 unID)
:SubAdapter(unID)
{
	m_unDBRequestCount = 0;
	m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
}

DBHandlerMgr::~DBHandlerMgr()
{
	
}

void DBHandlerMgr::increase_request_count()
{
	m_unDBRequestCount ++;
}

void DBHandlerMgr::decrease_request_count()
{
	if(m_unDBRequestCount > 0)
	{
		m_unDBRequestCount --;
	}
}