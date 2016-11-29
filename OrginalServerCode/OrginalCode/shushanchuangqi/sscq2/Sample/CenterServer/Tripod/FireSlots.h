
#ifndef FIRESLOTS_H_
#define FIRESLOTS_H_

#include "stdafx.h"
#include "VecSlots.h"
#include "TripodFire.h"
#include "TripodProt.h"

using namespace NTripodProt;

class CUser;

class CFireSlots: public CVecSlots<int, CFirePtr>, public CPoolObj<CFireSlots>
{
public:
    CFireSlots(CUser& rUser): CVecSlots(100), _rUser(rUser) {}
    ~CFireSlots() {}

    CFirePtr GetFire(UINT16 wFireID, int* pIdx = NULL) const
    {
        VecSlotsEnumerateByID<UINT8, int, CFirePtr> en(wFireID);
        enumerate(en);
        if (en._sSlot == INVALID_SLOT)
            return NULL;
        if (pIdx)
            *pIdx = en._sSlot;
        return en._pObj;
    }

    bool HasRemainCnt(UINT16 wFireID);
    void AddRemainCnt(UINT16 wFireID, UINT32 dwCnt);
    bool LoadFireFromDB(const TVecFireInfo& vecFireInfo);
    void GetAllFires(TVecFireInfo& vecFires);
    bool ActiveFire(UINT16 wFireID);
    void Update2DB(CFirePtr& pFire, EDataChange eDataChange/* = eOpUpdate*/);

private:
    CUser& _rUser;
};

#endif // FIRESLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

