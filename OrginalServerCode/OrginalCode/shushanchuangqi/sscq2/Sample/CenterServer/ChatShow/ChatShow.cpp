#include "stdafx.h"
#include "ChatShow.h"

map<UINT64, UINT64> CChatShow::_mapID2InstID;
map<UINT64, string> CChatShow::_mapID2Item;

UINT32 CChatShow::AddSItem(UINT64 qwRoleID, UINT64 qwInstID, EChatShowType eShowType, const string& strItem)
{
	if(!qwRoleID || !qwInstID || strItem.empty())
		return 0;
	_mapID2InstID[qwRoleID] = qwInstID;
	_mapID2Item[qwInstID] = strItem;
    return 0;
}

bool CChatShow::GetChatShowInfo(UINT32 dwShowID, string& strItem, EChatShowType& eType)
{
    strItem.clear();
    auto it = _mapID2InstID.find(dwShowID);
    if(it == _mapID2InstID.end())
        return false;

    switch(eType)
    {
        case eShowItem:
            {
                auto it_str = _mapID2Item.find(it->second);
                if(it_str == _mapID2Item.end())
                    return false;

                strItem = it_str->second;
                return true;
            }
        case eShowRole:
            return false;
        default:
            break;
    }

    return false;
}

