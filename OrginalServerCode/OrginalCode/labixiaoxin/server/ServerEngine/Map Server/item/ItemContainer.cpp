#include "ItemContainer.h"
#include "..\..\GameBase\Common\GameDefine.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


ItemContainer::ItemContainer()
{
	m_pSlotList = NULL;
	m_unSize = m_unMaxSize = 0;
}

ItemContainer::~ItemContainer()
{
	
}

void ItemContainer::init(ACE_UINT32 unContainerType, ACE_UINT32 unSize, ACE_UINT32 unMaxSize)
{
	m_unContainerType = unContainerType;
	m_unSize = unSize;
	m_unMaxSize = unMaxSize;

	m_pSlotList = new PBaseItem[m_unMaxSize];

	for(int i = 0;i < m_unSize;i ++)
	{
		m_pSlotList[i] = NULL;
	}
}

BaseItem *ItemContainer::get_item(int nSlot)
{
	if(nSlot >= m_unSize || nSlot < 0)
	{
		return NULL;
	}

	return m_pSlotList[nSlot];
}

int ItemContainer::set_item(BaseItem *pInfo, int nSlot)
{
	BaseItem *pOldItem;

	int ret = set_item(pInfo, nSlot, pOldItem);

	if(ret == 0 && pOldItem != NULL)
	{
		delete pOldItem;
	}

	return ret;
}

int ItemContainer::set_item(BaseItem *pInfo, int nSlot, BaseItem *&pOldItem)
{
	if(nSlot >= m_unSize || nSlot < 0)
	{
		return -1;
	}

	if(pInfo != NULL && !is_valid_type(pInfo->m_pItemRes))
	{
		return -1;
	}

	/*
	if(m_slotRestrictTbl != NULL && m_slotRestrictTbl->nCount > nSlot && pInfo != NULL)
	{
		if(pInfo->m_pItemRes != NULL && m_slotRestrictTbl->typeList[nSlot] != pInfo->m_pItemRes->m_unSubType)
		{
			return -1;
		}
	}
	*/

	pOldItem = m_pSlotList[nSlot];
	/*
	if(m_pSlotList[nSlot] != NULL)
	{
		delete m_pSlotList[nSlot];
	}
	*/

	m_pSlotList[nSlot] = pInfo;

	return 0;
}

//delete
BaseItem *ItemContainer::delete_item()
{
	BaseItem *pInfo = NULL;
	if(m_unSize > 0)
	{
		pInfo = m_pSlotList[m_unSize - 1];
		m_unSize --;
	}

	return pInfo;
}

//add
int ItemContainer::add_item(BaseItem *pInfo)
{
	if(m_unSize >= m_unMaxSize)
	{
		return -1;
	}

	if(!is_valid_type(pInfo->m_pItemRes))
	{
		return -1;
	}

	m_pSlotList[m_unSize] = pInfo;
	m_unSize ++;

	return 0;
}

BaseItem *ItemContainer::delete_and_swap_last(int nSlot)
{
	BaseItem *pInfo = NULL;

	if(nSlot >= 0 && nSlot < m_unSize)
	{
		pInfo = m_pSlotList[nSlot];
		if(nSlot < (m_unSize - 1))
		{
			m_pSlotList[nSlot] = m_pSlotList[m_unSize - 1];
		}

		m_unSize --;
	}

	return pInfo;
}

bool ItemContainer::is_valid_type(BaseRes *pInfo)
{
	return true;
}