#include "LoginMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif
LoginMgr::LoginMgr(ACE_UINT32 unID)
:SubAdapter(unID)
{
	m_unMaxChild = 0;
	m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");

	m_unCurrentLoginID = 0;
}

LoginMgr::~LoginMgr()
{

}

BaseObj *LoginMgr::new_child_obj(ACE_UINT32 unID)
{
	return new LoginSession(unID, this);
}

int LoginMgr::deal_msg(MessageInfo &msgInfo)
{
	SubAdapter::deal_msg(msgInfo);

	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_CREATE_BASE_OBJ:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;

				m_unCurrentLoginID = body->unID;
			}
			break;
		}
	}

	return 0;
}