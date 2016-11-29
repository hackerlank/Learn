// =====================================================================================
//
//       Filename:  EquipTrumpSlot.h
//
//    Description:  法宝槽
//
//        Version:  1.0
//        Created:  05/14/2015 02:46:14 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#ifndef EQUIP_TRUMP_SLOT_H
#define EQUIP_TRUMP_SLOT_H

#include "ItemSlots.h"

#include "EquipTrumpProt.h"
#include "ProtoCommon.h"    // XXX: for EDataChange

using namespace NEquipTrumpProt;
using namespace NProtoCommon;

const UINT8 EQUIP_TRUMP_SLOTS = 10;


// =====================================================================================
//        Class:  CEquipTrumpSlot
//  Description:  装备法宝槽
// =====================================================================================
class CEquipTrumpSlot : public CItemSlots<EQUIP_TRUMP_SLOTS>
{
    public:
        // ====================  LIFECYCLE     ======================================= //
        CEquipTrumpSlot ();                             // constructor //
        virtual ~CEquipTrumpSlot();

        // ====================  ACCESSORS     ======================================= //

        EStoreType GetStoreType() const { return eStoreEquipTrump; }
        void ToProt(TVecItem& vecItem) const;

        bool GetAllInfo(NItemProt::TVecEquipTrump& rvecEquipTrump) const;

        bool GetAddAttr(TVecFloat& rvecAddAttr) const;

        void GetAllSkills(TVecUINT32& rvecAllSkills) const;

        bool GetAllEquipTrump(TVecEquipTrumpPtr& rvecEquipTrump) const;

        // ====================  MUTATORS      ======================================= //
        
        bool InitSlot(UINT16 wMaxSlot, UINT16 wMaxAvaliableSlot);

        bool AddItemFromDB(CEquipTrumpPtr pEquipTrump);
        
        virtual void SetDirty(bool bDirty) const;

        // ====================  OPERATORS     ======================================= //
        bool TryUnlockSlot(UINT16 wLevel);

        EEquipTrumpResult Wear(CEquipTrumpPtr pEquipTrump,UINT32 dwFighterID);
        EEquipTrumpResult WearOneKey(UINT32 dwFighterID);

        EEquipTrumpResult TakeOff (UINT64 qwInstID, INT16 wIndex);

        EEquipTrumpResult Swap(CEquipTrumpPtr pEquipTrump, INT16 wIndex, UINT32 dwFighterID);

        void NotifyInfo() const;


        UINT32 GetEquipTrumpCount(UINT8 byMinQuality,UINT8 byMinInsifyLevel);  

    private:
        // ====================  METHODS       ======================================= //

        void Update2DB(int iSlot, CItem& rItem, EDataChange eDataChange);

        // ====================  DATA MEMBERS  ======================================= //
        mutable bool _bDirty;

        map<UINT8, EEquipTrumpSlotType> _mapSlotType;

}; // -----  end of class CEquipTrumpSlot  ----- //

#endif // EQUIP_TRUMP_SLOT_H

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

