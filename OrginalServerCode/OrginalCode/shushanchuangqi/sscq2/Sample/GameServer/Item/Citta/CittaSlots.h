#ifndef CITTA_SLOTS_H
#define CITTA_SLOTS_H

#include "Citta.h"
#include "ItemSlots.h"
#include "Fighter.h"
#include "Store.h"

#define CITTA_SLOT_COUNT 8 // 心法位的个数


class CCittaSlots : public CItemSlots<CITTA_SLOT_COUNT>, public CStore
{
    public:
        CCittaSlots();
        virtual ~CCittaSlots();


        bool  InitSlot(UINT16 wMaxSlot, UINT16 wMaxAvaliableSlot);

        UINT8   GetAvaliableSlotsCount() const;
        
        virtual EStoreType GetStoreType() const;
        virtual CUser& GetUser() const;

        virtual void SetDirty(bool bDirty) const;

        ECittaResult    Ware       (CCittaPtr pCitta, UINT8 bySlotIndex);
        ECittaResult    Takeoff    (UINT8 bySlotIndex);
        bool            TestUnlockSlot(UINT8 byNewLevel);

        bool            GetAddAttr(TVecFloat& rvecAddAttr) const;

    private:
        UINT8   _byAvaliableCount;
};

class CCittaEnumerateToAttr : public Enumerator<typename CItemSlots<CITTA_SLOT_COUNT>::value_type>
{
    public:
        typedef CItemSlots<CITTA_SLOT_COUNT>::value_type value_type;

    public:
        CCittaEnumerateToAttr(TVecFloat& rvecAddAttr) : _rvecAddAttr(rvecAddAttr) {}

        bool operator()(const value_type* obj) const
        {
            if (obj && std::get<1>(*obj))
            {
                CCittaPtr pCitta = dynamic_pointer_cast<CCitta>(std::get<2>(*obj));
                if (pCitta)
                {
                    const TMapCittaAttr& rmapCittaAttr = pCitta->GetAttr();
                    for (auto it = rmapCittaAttr.begin(); it != rmapCittaAttr.end(); ++it)
                    {
                        if (it->first >= _rvecAddAttr.size())
                            _rvecAddAttr.resize(it->first + 1);
                        _rvecAddAttr[it->first] += it->second;
                        if (it->first == EFIGHTATTR_PHYATK)
                            _rvecAddAttr[EFIGHTATTR_MGCATK] += it->second;
                    }
                }
            }
            return true;
        }

    public:
        TVecFloat& _rvecAddAttr;
};

class CCittaEnumerateGetSignet : public Enumerator<typename CItemSlots<CITTA_SLOT_COUNT>::value_type>
{
    public:
        typedef CItemSlots<CITTA_SLOT_COUNT>::value_type value_type;

    public:
        CCittaEnumerateGetSignet(TSetUINT32& rsetSignet) : _rsetSignet(rsetSignet) {}

        bool operator()(const value_type* obj) const
        {
            if (obj && std::get<1>(*obj))
            {
                CCittaPtr pCitta = dynamic_pointer_cast<CCitta>(std::get<2>(*obj));
                if (pCitta)
                    _rsetSignet.insert(pCitta->GetSignetID());
            }
            return true;
        }

    public:
        TSetUINT32& _rsetSignet;
};


#endif // #ifndef CITTA_SLOTS_H
