#ifndef GEMSTONE_SLOTS_H
#define GEMSTONE_SLOTS_H

#include "Gemstone.h"
#include "Fighter.h"
#include "Store.h"

#define GEMSTONE_SLOT_COUNT 6 // 心法位的个数
class CHeroFighter;
class CGemstoneSlots 
{
    public:
        CGemstoneSlots(CHeroFighter& rFighter);
        virtual ~CGemstoneSlots();
        EStoreType GetStoreType() const;
        void SetDirty() const;
        void GetGemstoneAll(TVecGemstonePtr &vecStone) const;

        EGemstoneResult    Ware       (UINT16 wItemId, UINT8 bySlotIndex,SGemstone &sItem,UINT16& wStoneLevel);
        EGemstoneResult    Takeoff    (UINT8 bySlotIndex);
        bool            GetAddAttr(TVecFloat& rvecAddAttr) const;
        bool AddItemFromDB(CGemstonePtr pGemstone);
        void Update2DB(CGemstonePtr pIterm,  EDataChange eDataChange);
        void GemstoneDismiss(TVecItemGenInfo& vecItems);

        //获取符合等级条件的宝石数量
        UINT32 GetStoneCount(UINT8 byMinLevel); 
   private:
        TVecGemstonePtr _vecStone;
        CHeroFighter& _rFighter;

};

#endif // #ifndef GEMSTONE_SLOTS_H
