#ifndef PACK_H
#define PACK_H

#pragma once
#include "Store.h"

#include "EquipTrumpProt.h"

using namespace NEquipTrumpProt;

class CPack : public CStore
{
    public:
        CPack(CUser& rUser, UINT16 wInitCount);
        virtual ~CPack();

        CUser& GetUser() { return _rUser; }
        CUser& GetUser() const { return _rUser; }
        virtual EStoreType GetStoreType() const { return eStorePack; }

        //堆叠道具批量使用
        EItemResult UseItem(CItem& rItem, UINT16 wCount, UINT64 qwMercenID = 0, CUser* pOther = NULL);
        EItemResult UseItem(UINT64 qwInstID, UINT16 wCount, UINT64 qwMercenID = 0, CUser* pOther = NULL);
        EItemResult UseItem(UINT64 qwInstID, UINT16 wItemID, UINT16 wCount, bool bBind, UINT64 qwMercenID = 0, CUser* pOther = NULL);
        EItemResult SellItem(const TVecUINT64& qwInstIDVec);
        EItemResult SellItemWithCount(UINT64 qwInstID, UINT16 wItemID, UINT16 wCount, bool bBind);
        EItemResult SellItemWithCount(UINT64 qwInstID, UINT16 wCount);

        ECittaResult MergeCitta(UINT16 wItemID, UINT16 wCount, EBindUseType eBindUseType, TVecItem& vecItemInfo);
        ECittaResult BreakCitta(const TVecUINT64& qwInstIDVec, TVecItemGenInfo& vecItemInfo);

        EEquipTrumpMergeResult MergeEquipTrump(UINT16 wItemID, UINT16 wCount, TVecItem& vecItemInfo);
        EEquipTrumpBreakResult BreakEquipTrump(const TVecUINT64& qwInstIDVec, TVecItemGenInfo& vecItemInfo);

        // 获取背包内的所有装备法宝
        void GetAllEquipTrump(TVecEquipTrumpPtr& rvecEquipTrumpPtr);

        EGemstoneResult MergeGenStone(UINT16 wItemID,UINT32 dwNum); 

        bool AddItemOrMail(CItem& rItem, INT16 wIndex = -1, bool bNotify = true, bool bNew = false, bool bUpdate = true, UINT16 fromWhere = 0);

        CUser& _rUser;
};
#endif // #ifndef PACK_H
