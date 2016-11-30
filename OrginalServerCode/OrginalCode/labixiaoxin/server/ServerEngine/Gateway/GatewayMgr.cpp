#include "GatewayMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"
#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif

GatewayMgr::GatewayMgr(ACE_UINT32 unID)
:SubAdapter(unID)
{
	m_unMaxChild = 0;
	m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
}

GatewayMgr::~GatewayMgr()
{

}

BaseObj *GatewayMgr::new_child_obj(ACE_UINT32 unID)
{
	return new GatewaySession(unID, this);
}
