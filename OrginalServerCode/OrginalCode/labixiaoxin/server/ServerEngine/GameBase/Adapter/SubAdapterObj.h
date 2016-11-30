#pragma once

#include "..\..\Base\Service\BaseObj.h"

class SubAdapterObj : public BaseObj
{
public:
	enum
	{
		LRU_STATUS_NORMAL = 0,
		LRU_STATUS_REMOVING
	};

	SubAdapterObj(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~SubAdapterObj();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	virtual void wanna_remove_from_lru() = 0;
	virtual void cancel_remove_from_lru() = 0;

	virtual bool wanna_do_timeout();

	void self_active();

	virtual bool should_destroy();

	void set_lru_status(ACE_UINT32 unStatus);

	SubAdapterObj *m_prev;
	SubAdapterObj *m_next;

	ACE_UINT32 m_unLRUStatus;
	bool m_bLRUDestroyFlag;
private:

	
};