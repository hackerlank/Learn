#include "PhpProxyMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"

PhpProxyMgr::PhpProxyMgr(ACE_UINT32 unID)
:SubAdapter(unID)
{
	m_unMaxChild = 0;
	m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
}

PhpProxyMgr::~PhpProxyMgr()
{

}

BaseObj *PhpProxyMgr::new_child_obj(ACE_UINT32 unID)
{
	return new PhpProxySession(unID, this);
}

int PhpProxyMgr::deal_msg(MessageInfo &msgInfo)
{
	SubAdapter::deal_msg(msgInfo);

	/*
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_CREATE_BASE_OBJ:
			{
				MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;

				if(create_child(body->unID) == -1)
				{
					//destroy client peer
				}
			}
			break;
		}
	}
	*/

	return 0;
}