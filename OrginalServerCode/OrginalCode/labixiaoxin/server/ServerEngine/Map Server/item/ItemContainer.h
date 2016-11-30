#pragma once

//#include "..\res\BaseItemRes.h"
#include "BaseItem.h"
//#include "..\..\GameBase\res\ItemSlotMappingData.h"

class ItemContainer
{
public:
	ItemContainer();
	virtual ~ItemContainer();

	void init(ACE_UINT32 unContainerType, ACE_UINT32 unSize, ACE_UINT32 unMaxSize);

	//get
	BaseItem *get_item(int nSlot);

	//set
	int set_item(BaseItem *pInfo, int nSlot);
	int set_item(BaseItem *pInfo, int nSlot, BaseItem *&pOldItem);

	//delete
	BaseItem *delete_item();

	ACE_UINT32 get_size(){return m_unSize;};

	//add
	int add_item(BaseItem *pInfo);

	BaseItem *delete_and_swap_last(int nSlot);

private:
	//bool is_valid_type(ACE_UINT32 unItemID);
	bool is_valid_type(BaseRes *pInfo);

	ACE_UINT32 m_unSize;
	ACE_UINT32 m_unMaxSize;

	ACE_UINT32 m_unContainerType;

	PBaseItem *m_pSlotList;
};