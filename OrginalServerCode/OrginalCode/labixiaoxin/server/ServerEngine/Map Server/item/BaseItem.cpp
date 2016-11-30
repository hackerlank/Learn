#include "BaseItem.h"
#include "..\..\GameBase\res\ItemResMgr.h"

BaseItem::BaseItem(ACE_UINT32 unItemID)
{
	m_unItemID = unItemID;
	m_pItemRes = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unItemID);
}

BaseItem::~BaseItem()
{

}