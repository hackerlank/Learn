#pragma once
#include "GlobalChatProt.h"

using namespace NGlobalChatProt;

class CChatShow
{
    public:
        static UINT32 AddSItem(UINT64 qwRoleID, UINT64 qwInstID, EChatShowType eShowType, const string& strItem);
        static bool GetChatShowInfo(UINT32 dwShowID, string& strItem, EChatShowType& eType);
    private:
        //展示道具
        static map<UINT64, UINT64> _mapID2InstID;
        static map<UINT64, string> _mapID2Item;
};
