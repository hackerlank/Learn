#ifndef ITEMSLOTS_H_
#define ITEMSLOTS_H_

#include "stdafx.h"

#include "ArrSlots.h"
#include "DataSlots.h"
#include "User.h"       // XXX: for GetUserID()
#include "Fighter.h"    // XXX: for GetID()

template <size_t SIZE, typename C = CArrSlots<int, CItemPtr, SIZE>>
//class CItemSlots : public CArrSlots<int, CItemPtr, SIZE>, public CDataSlots
class CItemSlots : public C, public CDataSlots
{
    public:
        //typedef CArrSlots<int, CItemPtr, SIZE> TYPE;
        typedef C TYPE;
        static const size_t size = SIZE;

    public:
        CItemSlots() : TYPE(SIZE) { }

        virtual ~CItemSlots() {}

        void SetUser(const CUserPtr& pUser) { _pUser = pUser; }
        CUserPtr GetUser() const { return _pUser.lock(); }

        CUserPtr GetPUser() const { return _pUser.lock(); }


        void SetFighter(const CFighterPtr& pFighter) { _pFighter = pFighter; }

        CFighterPtr GetFighter() const { return _pFighter.lock(); }

        virtual EStoreType GetStoreType() const = 0;

        virtual UINT64 GetRoleID() const
        {
            if (GetUser())
                return GetUser()->GetUserID();
            return 0;
        }

        virtual UINT64 GetOwnerID() const
        {
            if (GetFighter())
                return GetFighter()->GetInstID();
            return 0;
        }

        CItemPtr GetSlotByInstID(UINT64 qwInstID, int* pIdx = NULL)
        {
            ArrSlotsEnumerateByInstID<UINT64, int, CItemPtr, SIZE> en(qwInstID);
            TYPE::enumerate(en);
            if (pIdx)
                *pIdx = en._sSlot;
            return en._pObj;
        }

        CItemPtr GetSlotByID(UINT16 wID, int* pIdx = NULL)
        {
            ArrSlotsEnumerateByID<UINT64, int, CItemPtr, SIZE> en(wID);
            TYPE::enumerate(en);
            if (pIdx)
                *pIdx = en._sSlot;
            return en._pObj;
        }

    protected:
        CUserWtr _pUser;
        CFighterWtr _pFighter;
};

#endif // ITEMSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

