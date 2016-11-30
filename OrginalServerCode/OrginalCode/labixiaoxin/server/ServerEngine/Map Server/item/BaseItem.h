#pragma once

#include "ace\ace.h"
#include "..\..\GameBase\res\BaseRes.h"

class BaseItem
{
public:
	BaseItem(ACE_UINT32 unItemID);
	virtual ~BaseItem();

	BaseRes *m_pItemRes;
	ACE_UINT32 m_unItemID;
	//info
	
	ACE_UINT32 m_unCount;
	ACE_UINT32 m_unLockCount;
};


typedef BaseItem * PBaseItem;