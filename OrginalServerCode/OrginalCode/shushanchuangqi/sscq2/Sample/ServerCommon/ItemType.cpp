
#include "ItemType.h"

EItemType CItemType::GetItemType(UINT16 wItemID)
{
    ID_IFBETWEEN(wItemID, Normal);
    ID_IFBETWEEN(wItemID, Trump);
    ID_IFBETWEEN(wItemID, Fashion);
    ID_IFBETWEEN(wItemID, Formation);
    ID_IFBETWEEN(wItemID, Citta);
    ID_IFBETWEEN(wItemID, Intensify);
    ID_IFBETWEEN(wItemID, Stone);
    ID_IFBETWEEN(wItemID, Task);
    ID_IFBETWEEN(wItemID, Spirit);
    ID_IFBETWEEN(wItemID, Soul);
    ID_IFBETWEEN(wItemID, Neidan);
    ID_IFBETWEEN(wItemID, Vigour);
    ID_IFBETWEEN(wItemID, EquipTrump);
	return eItemNone;
}

bool CItemType::IsCitta(UINT16 wItemID)
{
    return GetItemType(wItemID) == eItemCitta;
}

bool CItemType::IsTrump(UINT16 wItemID)
{
    return GetItemType(wItemID) == eItemTrump;
}

bool CItemType::IsFashion(UINT16 wItemID)
{
    return GetItemType(wItemID) == eItemFashion;
}

bool CItemType::IsEquipTrumpItem(UINT16 wItemID)
{
    return GetItemType(wItemID) == eItemEquipTrump;
}
