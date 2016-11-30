#include "BaseObj.h"
#include "BaseService.h"
#include "BaseAdapter.h"

BaseObj::BaseObj(ACE_UINT32 unID, BaseAdapter *parent)
:ServiceObj(unID)
{
	m_ParentAdapter = parent;
	m_unOPSN = 0;

	m_bDoTimeout = false;
	//m_bDoDestroyMyself = false;
	//m_unObjTransferStatus = OBJ_TRANSFER_NONE;
	//m_unTransferServiceID = OBJ_ID_NONE;
}

BaseObj::~BaseObj()
{
	m_ParentAdapter->clear_timeout_map(m_unID);
}

void BaseObj::setAddr(ObjAdr &addr)
{
	addr.unServiceID = BaseService::instance()->m_unID;
	addr.unAdapterID = m_ParentAdapter->m_unID;
	addr.unObjID = m_unID;
}


void BaseObj::obj_fini()
{
	printf("base obj fini %d\n", m_ParentAdapter->m_unID);
	ServiceObj::obj_fini();
	m_ParentAdapter->removeChild(m_unID);
}

void BaseObj::create_done()
{
	ObjAdr *addr = get_own_query_addr();
	if(addr == NULL)
	{
		return;
	}

	MsgServiceObjOP retInfo;
	retInfo.unAdapterID = m_ParentAdapter->m_unID;
	retInfo.unObjID = m_unID;
	retInfo.unSN = m_unOPSN;
	retInfo.nResult = 0;

	this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_CREATE_SERVICE_OBJ_RESULT, (char*)&retInfo, sizeof(MsgServiceObjOP), *addr);
}

void BaseObj::destroy_done()
{
	ObjAdr *addr = get_own_query_addr();
	if(addr == NULL)
	{
		return;
	}

	MsgServiceObjOP retInfo;
	retInfo.unAdapterID = m_ParentAdapter->m_unID;
	retInfo.unObjID = m_unID;
	retInfo.unSN = m_unOPSN;
	retInfo.nResult = 0;
	
	//if (!m_bDoDestroyMyself)
	this->sendMsg(SERVICE_MESSAGE_TYPE_OBJ_LOCATION, MSG_SERVICE_DESTROY_SERVICE_OBJ_RESULT, (char*)&retInfo, sizeof(MsgServiceObjOP), *addr);
}

ObjAdr *BaseObj::get_own_query_addr()
{
	if(m_ParentAdapter == NULL)
	{
		return NULL;
	}

	return SERVICE_MSG_CTRL_INSTANCE::instance()->get_query_service_id(m_ParentAdapter->m_unID, m_unID);
}

int BaseObj::start_create()
{
	int ret = ServiceObj::start_create();
	if(ret == -1)
	{
		return -1;
	}

	set_timeout_status();

	return 0;
}

int BaseObj::start_running()
{
	int ret = ServiceObj::start_running();
	if(ret == -1)
	{
		return -1;
	}

	set_timeout_status();

	return 0;
}

int BaseObj::start_destroy()
{
	set_timeout_status();

	return ServiceObj::start_destroy();
}

void BaseObj::set_destroy(bool flag)
{
	ServiceObj::set_destroy(flag);

	set_timeout_status();
}

bool BaseObj::wanna_do_timeout()
{
	bool flag = false;

	switch(m_unObjStatus)
	{
	case SERVICE_OBJ_CREATE:
		flag = true;
		break;
	case SERVICE_OBJ_RUN:
		if(m_bDestroyFlag)
		{
			flag = true;
		}
		else
		{
			if(m_bDoTimeout)
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
		}
		break;
	case SERVICE_OBJ_DESTROY:
		flag = true;
		break;
	default:
		flag = false;
		break;
	}

	return flag;
}

void BaseObj::set_timeout_status()
{
	bool flag = wanna_do_timeout();

	if(flag)
	{
		m_ParentAdapter->add_child_to_timeout_map(this);
	}
	else
	{
		m_ParentAdapter->remove_child_from_timeout_map(this);
	}
}