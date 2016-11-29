#ifndef DATA_SLOTS_H
#define DATA_SLOTS_H

#pragma once

#include "ItemProt.h"

using namespace NItemProt;

class CDataSlots
{
    public:
        CDataSlots();
        virtual ~CDataSlots();

        virtual EStoreType GetStoreType() const = 0;

        virtual UINT64 GetRoleID() const = 0;
        virtual UINT64 GetOwnerID() const = 0;

        virtual bool  InitSlot(UINT16 wMaxSlot, UINT16 wMaxAvaliableSlot);

    public:
        UINT16 GetMaxSlot() const;
        UINT16 GetMaxAvaliableSlot() const;

        bool    SetMaxSlot(UINT16 wSlot, bool bInit = false);
        bool    SetMaxAvaliable(UINT16 wSlot, bool bInit = false);

    public:
        static void    Update2DB(const CDataSlots& rDataSlots);

    private:
        UINT16  _wMaxSlot;
        UINT16  _wMaxAvaliableSlot;
};

#endif // #ifndef DATA_SLOTS_H
