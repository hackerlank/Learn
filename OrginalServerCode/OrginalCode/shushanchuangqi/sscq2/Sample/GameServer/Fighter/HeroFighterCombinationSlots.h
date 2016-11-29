
#ifndef HEROFIGHTERCOMBINATIONSLOTS_H_
#define HEROFIGHTERCOMBINATIONSLOTS_H_

#include "stdafx.h"
#include "VecSlots.h"
#include "HeroFighterCombination.h"
#include "FighterProt.h"

using namespace NFighterProt;
using namespace NProtoCommon;


class CUser;

class CHeroFighterCombinationSlots: public CVecSlots<int, CHeroFighterCombinationPtr>
{
public:
    CHeroFighterCombinationSlots(CUser& rUser);
    ~CHeroFighterCombinationSlots() {}
    CUser& GetUser() { return _rUser; }
    CHeroFighterCombinationPtr GetFighterCombination(UINT8 byGroupID, int* pIdx = NULL) const
    {
        VecSlotsEnumerateByID<UINT8, int, CHeroFighterCombinationPtr> en(byGroupID);
        enumerate(en);
        if (en._sSlot == INVALID_SLOT)
            return NULL;
        if (pIdx)
            *pIdx = en._sSlot;
        return en._pObj;
    }

    void GetAllFighterCombination(TVecFighterCombination&);
    void UpdateToClient();
    bool LoadFromDB(const TVecFighterCombination& vecFighterCombination);
    void Update2DB(CHeroFighterCombinationPtr& pFgtComb, EDataChange eDataChange = eOpUpdate);

private:
    CUser& _rUser;

};

#endif // HEROFIGHTERCOMBINATIONSLOTS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


