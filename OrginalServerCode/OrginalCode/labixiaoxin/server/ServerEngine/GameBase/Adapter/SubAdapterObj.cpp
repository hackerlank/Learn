#include "SubAdapterObj.h"
#include "SubAdapter.h"

SubAdapterObj::SubAdapterObj(ACE_UINT32 unID, BaseAdapter *parent)
:BaseObj(unID, parent)
{
	m_prev = m_next = NULL;
	m_bLRUDestroyFlag = false;
}

SubAdapterObj::~SubAdapterObj()
{
	((SubAdapter *)m_ParentAdapter)->lru_remove(this);
}

int SubAdapterObj::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	BaseObj::obj_init(arg, unArgLen);

	((SubAdapter *)m_ParentAdapter)->lru_add(this);

	return 0;
}

void SubAdapterObj::self_active()
{
	((SubAdapter *)m_ParentAdapter)->lru_update(this);
}

bool SubAdapterObj::should_destroy()
{
	return (BaseObj::should_destroy() || m_bLRUDestroyFlag);
}

void SubAdapterObj::set_lru_status(ACE_UINT32 unStatus)
{
	if(m_unLRUStatus == unStatus)
	{
		return;
	}

	m_unLRUStatus = unStatus;

	if(m_unLRUStatus == LRU_STATUS_NORMAL)
	{
		m_bLRUDestroyFlag = false;
		cancel_remove_from_lru();
	}
	else
	{
		m_bLRUDestroyFlag = true;
		wanna_remove_from_lru();
	}

	set_timeout_status();
}

bool SubAdapterObj::wanna_do_timeout()
{
	bool flag = false;

	if(m_unLRUStatus == LRU_STATUS_NORMAL)
	{
		flag = BaseObj::wanna_do_timeout();
	}
	else
	{
		flag = true;
	}

	return flag;
}