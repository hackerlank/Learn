
#include "FighterSlots.h"
#include "Parameter.h"

// ===  FUNCTION  ======================================================================
//         Name:  CFighterSlots
//  Description:  构造函数
// =====================================================================================
CFighterSlots::CFighterSlots() : 
    CVecSlots(SParamConfig::byHeroLimit)
{
}		// -----  end of function CFighterSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  ~CFighterSlots
//  Description:  虚构函数
// =====================================================================================
CFighterSlots::~CFighterSlots ()
{
}		// -----  end of function ~CFighterSlots  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetMainFighter
//  Description:  获取主将
// =====================================================================================
CFighterPtr CFighterSlots::GetMainFighter () const
{
    return Get(0);
}		// -----  end of function GetMainFighter  ----- //

CFighterPtr CFighterSlots::GetFighterByInstID(UINT64 qwFighterID, int* pIdx)
{
    VecSlotsEnumerateByInstID<UINT64, int, CFighterPtr> en(qwFighterID);
    enumerate(en);
    if (en._sSlot == INVALID_SLOT)
        return NULL;
    if (pIdx)
        *pIdx = en._sSlot;
    return en._pObj;
}

CFighterPtr CFighterSlots::GetFighterByID(UINT16 wFighterID, int* pIdx)
{
    VecSlotsEnumerateByID<UINT16, int, CFighterPtr> en(wFighterID);
    enumerate(en);
    if (en._sSlot == INVALID_SLOT)
        return NULL;
    if (pIdx)
        *pIdx = en._sSlot;
    return en._pObj;
}

bool CFighterSlots::HasFighter(UINT16 wFighterID, int* pIdx)
{
    VecSlotsEnumerateByID<UINT16, int, CFighterPtr> en(wFighterID);
    enumerate(en);
    if (en._sSlot == INVALID_SLOT)
        return false;
    if (en._pObj)
    {
        if (pIdx)
            *pIdx = en._sSlot;
        return true;
    }
    return false;
}

bool CFighterSlots::HasRecruitFighter(UINT16 wFighterID, int* pIdx)
{
    VecSlotsEnumerateByID<UINT16, int, CFighterPtr> en(wFighterID);
    enumerate(en);
    if (en._sSlot == INVALID_SLOT)
        return false;
    if (en._pObj)
    {
        if (!(en._pObj)->GetRecruited())
            return false;
        if (pIdx)
            *pIdx = en._sSlot;
        return true;
    }
    return false;
}

// 返回所有将的CBattleFighter对象
bool CFighterSlots::GetBattleFighters(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType)
{
    int iCount = GetSlots();
    for (int iIndex = 0; iIndex < iCount; ++iIndex)
    {
        if (HasObj(iIndex))
        {
            IBattleFighterPtr pBattleFighter = NULL;
            CFighterPtr pFighter = Get(iIndex);
            if (pFighter && pFighter->IsRecruited() && pFighter->GetPos() >= 0)
                pBattleFighter = pFighter->ToBattleFighter(0, eBattleType);
            if (pBattleFighter)
                vecBattleFighter.push_back(pBattleFighter);
        }
    }
    return true;
}

