#include "SubAdapter.h"

#include "..\Protocol\ControlProtocol.h"

SubAdapter::SubAdapter(ACE_UINT32 unID)
:BaseAdapter(unID)
{
	m_unMaxChild = 2048;
	m_ChildHead = m_ChildTail = NULL;
}

SubAdapter::~SubAdapter()
{

}

int SubAdapter::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_REGISTER_ADAPTER_RESPONSE:
			set_register_done(msgInfo.s_head->srcAdr.unServiceID, msgInfo.s_head->srcAdr.unAdapterID);
			break;
		case MSG_UNREGISTER_ADAPTER_RESPONSE:
			set_unregister_done(msgInfo.s_head->srcAdr.unServiceID, msgInfo.s_head->srcAdr.unAdapterID);
			break;
		}
	}

	return OBJ_DEAL_MSG_SUCCESS;
}

int SubAdapter::register_adapter(ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID)
{
	if(unDesServiceID == OBJ_ID_NONE || unDesAdapterID == OBJ_ID_NONE)
	{
		return -1;
	}

	if(m_MainAdapterInfo.unServiceID != OBJ_ID_NONE)
	{
		return -1;
	}

	if(this->sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_REGISTER_ADAPTER_REQUEST, NULL, 0, unDesServiceID, unDesAdapterID, OBJ_ID_NONE) == -1)
	{
		return -1;
	}

	m_MainAdapterInfo.unServiceID = unDesServiceID;
	m_MainAdapterInfo.unAdapterID = unDesAdapterID;
	m_MainAdapterInfo.unStatus = MainAdapterInfo::MAIN_ADAPTER_REGISER;

	return 0;
}

int SubAdapter::unregister_adapter()
{
	if(m_MainAdapterInfo.unServiceID == OBJ_ID_NONE)
	{
		return 0;
	}

	if(this->sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_UNREGISTER_ADAPTER_REQUEST, NULL, 0, m_MainAdapterInfo.unServiceID, m_MainAdapterInfo.unAdapterID, OBJ_ID_NONE) == -1)
	{
		return -1;
	}

	m_MainAdapterInfo.unStatus = MainAdapterInfo::MAIN_ADAPTER_UNREGISTER;

	return 0;
}

void SubAdapter::set_register_done(ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID)
{
	if(m_MainAdapterInfo.unStatus != MainAdapterInfo::MAIN_ADAPTER_REGISER)
	{
		return;
	}

	if(m_MainAdapterInfo.unServiceID == unDesServiceID && m_MainAdapterInfo.unAdapterID == unDesAdapterID)
	{
		m_MainAdapterInfo.unStatus = MainAdapterInfo::MAIN_ADAPTER_REGISTER_DONE;
		printf("register adapter[%d] success\n", m_unID);
	}
}

void SubAdapter::set_unregister_done(ACE_UINT32 unDesServiceID, ACE_UINT32 unDesAdapterID)
{
	if(m_MainAdapterInfo.unStatus != MainAdapterInfo::MAIN_ADAPTER_UNREGISTER)
	{
		return;
	}

	if(m_MainAdapterInfo.unServiceID == unDesServiceID && m_MainAdapterInfo.unAdapterID == unDesAdapterID)
	{
		m_MainAdapterInfo.unServiceID = OBJ_ID_NONE;
	}
}

void SubAdapter::obj_timeout()
{
	if(m_MainAdapterInfo.unServiceID == OBJ_ID_NONE)
	{
		return;
	}

	switch(m_MainAdapterInfo.unStatus)
	{
	case MainAdapterInfo::MAIN_ADAPTER_REGISER:
		sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_REGISTER_ADAPTER_REQUEST, NULL, 0, m_MainAdapterInfo.unServiceID, m_MainAdapterInfo.unAdapterID, OBJ_ID_NONE);
		break;
	case MainAdapterInfo::MAIN_ADAPTER_REGISTER_DONE:
		break;
	case MainAdapterInfo::MAIN_ADAPTER_UNREGISTER:
		sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_UNREGISTER_ADAPTER_REQUEST, NULL, 0, m_MainAdapterInfo.unServiceID, m_MainAdapterInfo.unAdapterID, OBJ_ID_NONE);
		break;
	}

	if (m_MainAdapterInfo.unStatus != MainAdapterInfo::MAIN_ADAPTER_REGISTER_DONE)
		printf("-------------SubAdapter time out:[%d]\n",m_MainAdapterInfo.unStatus);
}

int SubAdapter::start_create()
{
	int ret = BaseAdapter::start_create();

	if(ret == -1)
	{
		return -1;
	}

	return register_adapter(get_register_service_id(), get_register_adapter_id());
}

int SubAdapter::start_destroy()
{
	int ret = BaseAdapter::start_destroy();

	if(ret == -1)
	{
		return -1;
	}

	return unregister_adapter();
}

bool SubAdapter::isAdapterRegisterDone()
{
	if(m_MainAdapterInfo.unServiceID == OBJ_ID_NONE)
	{
		return true;
	}

	if(m_MainAdapterInfo.unStatus == MainAdapterInfo::MAIN_ADAPTER_REGISTER_DONE)
	{
		return true;
	}

	return false;
}

bool SubAdapter::isAdapterUnregisterDone()
{
	if(m_MainAdapterInfo.unServiceID == OBJ_ID_NONE)
	{
		return true;
	}

	return false;
}

bool SubAdapter::hasCreated()
{
	return isAdapterRegisterDone();
}

bool SubAdapter::hasDestoryed()
{
	return isAdapterUnregisterDone();
}

void SubAdapter::lru_add(SubAdapterObj *obj)
{
	if(m_ChildTail == NULL)
	{
		obj->m_prev = obj->m_next = NULL;
		m_ChildHead = m_ChildTail = obj;
	}
	else
	{
		m_ChildTail->m_next = obj;
		obj->m_prev = m_ChildTail;
		obj->m_next = NULL;
		m_ChildTail = obj;
	}

	obj->m_unLRUStatus = SubAdapterObj::LRU_STATUS_NORMAL;

	if(m_unMaxChild > 0 && m_objMap.current_size() > m_unMaxChild)
	{
		lru_full_notify();
	}
}

void SubAdapter::lru_remove(SubAdapterObj *obj)
{
	if(obj->m_next != NULL)
	{
		obj->m_next->m_prev = obj->m_prev;
	}
	else
	{
		m_ChildTail = obj->m_prev;
	}
	if(obj->m_prev != NULL)
	{
		obj->m_prev->m_next = obj->m_next;
	}
	else
	{
		m_ChildHead = obj->m_next;
	}
}

void SubAdapter::lru_update(SubAdapterObj *obj)
{
	if(obj->m_unObjStatus == SERVICE_OBJ_STATUS_NONE || obj->m_unObjStatus == SERVICE_OBJ_DESTROY)
	{
		return;
	}

	if(obj->m_unLRUStatus == SubAdapterObj::LRU_STATUS_REMOVING)
	{
		remove_lru_obj();

		obj->set_lru_status(SubAdapterObj::LRU_STATUS_NORMAL);
		printf("remove lru obj\n");
	}

	lru_remove(obj);
	lru_add(obj);
}

void SubAdapter::lru_full_notify()
{
	remove_lru_obj();

	printf("lru full notify\n");
}

void SubAdapter::remove_lru_obj()
{
	SubAdapterObj *p = m_ChildHead;

	while(p != NULL)
	{
		if(p->m_unLRUStatus == SubAdapterObj::LRU_STATUS_NORMAL)
		{
			p->set_lru_status(SubAdapterObj::LRU_STATUS_REMOVING);
			break;
		}

		p = p->m_next;
	}

	printf("remove lru obj\n");
}
