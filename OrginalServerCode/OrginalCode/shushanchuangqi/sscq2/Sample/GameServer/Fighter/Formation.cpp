
#include "stdafx.h"
#include "Protocols.h"
#include "Formation.h"
#include "Fighter.h"
#include "FighterMgr.h"
#include "UtilFunc.h" // XXX: for ValueInVec
#include "Battle.h"

bool CFormation::Init()
{
    return true;
}

CFighterPtr CFormation::GetMainFighter()
{
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter && rLineup.pFighter->IsMainFighter())
            return rLineup.pFighter;
    }
    return NULL;
}

CFighterPtr CFormation::GetMainFighter() const
{
    for (int i = 0; i < GetSlots(); ++i)
    {
        const LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter && rLineup.pFighter->IsMainFighter())
            return rLineup.pFighter;
    }
    return NULL;
}

bool CFormation::Set(int iSlot, const CFighterPtr& pFighter)
{
    if (iSlot > GetSlots())
        return false;

    LineupGrid& rLineup = Get(iSlot);
    if (HasObj(iSlot) && rLineup.pFighter)
    {
        rLineup.pFighter->SetPos(-1);
        rLineup.pFighter->Update2DB(eOpUpdate);
        rLineup.pFighter->SetFormation(-1);
        rLineup.pFighter = NULL;
        g_PropInfoS.FighterPropNotify(rLineup.pFighter, ePropPos, (UINT32)-1);
    }

    rLineup.pFighter = pFighter;
    pFighter->SetPos(iSlot);
    pFighter->Update2DB(eOpUpdate);
    SetHasObj(iSlot, true);
    g_PropInfoS.FighterPropNotify(const_cast<CFighterPtr&>(pFighter), ePropPos, (UINT32)iSlot);
    return true;
}

bool CFormation::Reset(int iSlot)
{
    if (iSlot > GetSlots())
        return false;
    LineupGrid& rLineup = Get(iSlot);
    if (HasObj(iSlot) && rLineup.pFighter)
    {
        rLineup.pFighter->SetPos(-1);
        rLineup.pFighter->Update2DB(eOpUpdate);
        rLineup.pFighter->SetFormation(-1);
        rLineup.pFighter = NULL;
        SetHasObj(iSlot, false);
        g_PropInfoS.FighterPropNotify(rLineup.pFighter, ePropPos, (UINT32)-1);
        return true;
    }
    return false;
}

bool CFormation::Swap(int iSlotSrc, int iSlotDst)
{
    if (iSlotSrc > GetSlots() || iSlotDst > GetSlots())
        return false;

    bool bHasOSrc = HasObj(iSlotSrc);
    bool bHasODst = HasObj(iSlotDst);
    LineupGrid& rLineupSrc = Get(iSlotSrc);
    LineupGrid& rLineupDst = Get(iSlotDst);
    if (!rLineupSrc.pFighter && !rLineupDst.pFighter)
        return true;
    if (rLineupSrc.pFighter)
    {
        rLineupSrc.pFighter->SetPos(iSlotDst);
        rLineupSrc.pFighter->Update2DB();
        g_PropInfoS.FighterPropNotify(rLineupSrc.pFighter, ePropPos, (UINT32)iSlotDst);
    }
    if (rLineupDst.pFighter)
    {
        rLineupDst.pFighter->SetPos(iSlotSrc);
        rLineupDst.pFighter->Update2DB();
        g_PropInfoS.FighterPropNotify(rLineupDst.pFighter, ePropPos, (UINT32)iSlotSrc);
    }
    std::swap(rLineupSrc.pFighter, rLineupDst.pFighter);
    SetHasObj(iSlotSrc, bHasODst);
    SetHasObj(iSlotDst, bHasOSrc);
    return true;
}

bool CFormation::Move(int iSlotSrc, int iSlotDst)
{
    if (iSlotSrc > GetSlots() || iSlotDst > GetSlots())
        return false;

    bool bHasOSrc = HasObj(iSlotSrc);
    if (!bHasOSrc)
        return false;

    bool bHasODst = HasObj(iSlotDst);
    LineupGrid& rLineupSrc = Get(iSlotSrc);
    if (!rLineupSrc.pFighter)
        return false;
    if (bHasODst)
        return Swap(iSlotSrc, iSlotDst);

    LineupGrid& rLineupDst = Get(iSlotDst);
    rLineupDst.pFighter = rLineupSrc.pFighter;
    rLineupDst.pFighter->SetPos(iSlotDst);
    rLineupDst.pFighter->Update2DB();
    SetHasObj(iSlotDst, true);

    rLineupSrc.pFighter = NULL;
    SetHasObj(iSlotSrc, false);

    g_PropInfoS.FighterPropNotify(rLineupDst.pFighter, ePropPos, (UINT32)iSlotDst);
    return true;
}

int CFormation::GetEmptySlot()
{
    //优先4号位
    if(!HasObj(4))
    {
        return 4;
    }

    for (size_t i = 0; i < MAX_POS; ++i)
    {
        if (!HasObj(i))
            return i;
    }

    return INVALID_SLOT;
}

bool CFormation::CanPutInto(int iSlot, const CFighterPtr& pFighter)
{
    if (!pFighter || iSlot < 0 || iSlot >= MAX_POS)
        return false;

    INT32 iOldPos = pFighter->GetPos();
    if (iOldPos < 0) // 不在阵型里
    {
        if (iSlot < 0)
            return false;
        return true;
    }
    else if (iSlot < 0) // 在阵型里请求下阵
    {
        if (pFighter->IsMainFighter())
            return false;
        return true;
    }
    else if (iOldPos != iSlot) // 交换位置
    {
       return true;
    }
    else if (iOldPos == iSlot) // 同一位置
        return true;

    return false;
}

bool CFormation::PutInto(int iSlot, const CFighterPtr& pFighter)
{
    if (!pFighter)
        return false;
    if(!CanPutInto(iSlot,pFighter))
        return false;

   INT32 iOldPos = pFighter->GetPos();
    if (iOldPos < 0) // 不在阵型里
    {
        if (iSlot < 0)
            return false;
        if (HasObj(iSlot))
            Reset(iSlot);
        if (!Set(iSlot, pFighter))
            return false;
    }
    else if (iSlot < 0) // 在阵型里请求下阵
    {
       if (!Reset(iOldPos))
            return false;
    }
    else if (iOldPos != iSlot) // 交换位置
    {
        if (HasObj(iSlot))
        {
            if (!Swap(iOldPos, iSlot))
                return false;
        }
        else
        {
            if (!Move(iOldPos, iSlot))
                return false;
        }
    }

    return true;
}

bool CFormation::PutIntoFormation(CFighterPtr pFighter)
{
    int iSlot = GetEmptySlot();
    if (iSlot == INVALID_SLOT)
        return false;
    return Set(iSlot, pFighter);
}

class FormatEnumerate4Lineup : public Enumerator<typename CArrSlots<int, LineupGrid, MAX_POS>::value_type>
{
public:
    typedef typename CArrSlots<int, LineupGrid, MAX_POS>::value_type value_type;

public:
    FormatEnumerate4Lineup(TVecLineup& vecLineup) : _vecLineup(vecLineup) {}

    bool operator()(value_type* obj)
    {
        if (obj && std::get<1>(*obj))
            _vecLineup.push_back(Lineup(std::get<2>(*obj).pFighter, std::get<0>(*obj)));
        return true;
    }

public:
    TVecLineup& _vecLineup;
};

void CFormation::GetLineup(TVecLineup& vecLineup)
{
    FormatEnumerate4Lineup en(vecLineup);
    enumerate(en);
}

void CFormation::Clear()
{
    int size = GetSlots();
    for (int i = 0; i < size; ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (!rLineup.pFighter)
            continue;
        if (rLineup.pFighter && rLineup.pFighter->IsMainFighter())
            continue;
        rLineup.pFighter->SetPos(-1);
        rLineup.pFighter->Update2DB(eOpUpdate);
        rLineup.pFighter->SetFormation(-1);
        rLineup.pFighter = NULL;
        SetHasObj(i, false);
    }
}

bool CFormation::SetFomation(TVecLineup& vecLineup)
{

    //卸下不在新阵上的阵上散仙
    if(!ClearWithOrigin(vecLineup))
        return false;

    if(vecLineup.size()>MAX_FIGHTER_SIZE)
    {
        return false;
    }

    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!CanPutInto(vecLineup[i].iPos,vecLineup[i].pFighter))
            return false;
    }
 
    for (size_t i = 0; i < vecLineup.size(); ++i)
    {
        if (!PutInto(vecLineup[i].iPos,vecLineup[i].pFighter))
            return false;
        vecLineup[i].pFighter->Update2DB();
    }

    return true;

}


bool CFormation::ClearWithOrigin(TVecLineup& vecLineup)
{
    size_t sz = vecLineup.size();
    int size = GetSlots();
    for (int i = 0; i < size; ++i)
    {
        bool bIn = false;
        LineupGrid& rLineup = Get(i);
        for (size_t i = 0; i < sz; ++i)
        {
            if (rLineup.pFighter && vecLineup[i].pFighter && rLineup.pFighter->GetInstID() == vecLineup[i].pFighter->GetInstID())
            {
               bIn = true;
                break;
            }
        }

        if(rLineup.pFighter)
        {
            rLineup.pFighter->SetPos(-1);
        }

        if (!bIn && rLineup.pFighter)
        {
            if (rLineup.pFighter->IsMainFighter())
                return false;

            rLineup.pFighter->Update2DB(eOpUpdate);
            g_PropInfoS.FighterPropNotify(rLineup.pFighter, ePropPos, (UINT32)-1);
        }

        rLineup.pFighter = NULL;
        SetHasObj(i, false);
    }
    return true;
}

UINT64 CFormation::GetBattleFighters(TVecBattleFighterPtr& vecBattleFighter, EBattleType eBattleType)
{
    UINT64 qwMainInstID = 0;
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
        {
            vecBattleFighter.push_back(rLineup.pFighter->ToBattleFighter(0, eBattleType));
            if (!qwMainInstID || rLineup.pFighter->IsMainFighter())
                qwMainInstID = rLineup.pFighter->GetInstID();
        }
    }
    return qwMainInstID;
}

void CFormation::GetDefaultFightFormation(FightFormationInfo& rFightFormationInfo)
{
    //rFightFormationInfo.wFormationID = _wFormationID;
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
        {
            rFightFormationInfo.vecBattlePosInfo.emplace_back(rLineup.pFighter->GetInstID(),rLineup.pFighter->GetPos());
        }
    }

}

UINT32 CFormation::GetFightersCurrHP()
{
    UINT32 dwHP = 0;
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
            dwHP += rLineup.pFighter->GetHP();
    }
    return dwHP;
}

UINT32 CFormation::GetFightersMaxHP()
{
    UINT32 dwHP = 0;
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
            dwHP += rLineup.pFighter->GetHPMax();
    }
    return dwHP;
}

UINT32 CFormation::GetFightersMaxHP2()
{
    UINT32 dwHP = 0;
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
            dwHP += rLineup.pFighter->GetHPMax2();
    }
    return dwHP;
}

void CFormation::RegenAllHP()
{
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
            rLineup.pFighter->RegenAllHP();
    }
}

bool CFormation::RecoverFighters(TVecBattleFighterPtr& vecBattleFighter)
{
    for (size_t j = 0; j < vecBattleFighter.size(); ++ j)
    {
        for (size_t i = 0; i < static_cast<size_t>(GetSlots()); ++i)
        {
            LineupGrid& rLineup = Get(i);
            if (HasObj(i) && rLineup.pFighter && rLineup.pFighter->GetID() == vecBattleFighter[j]->GetID())
            {
                rLineup.pFighter->SetHP(vecBattleFighter[j]->GetHP());
            }
        }
    }
    return true;
}

void CFormation::AddFightersCurrHP(UINT32 dwHP)
{
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
            rLineup.pFighter->AddHP(dwHP);
    }
}

void CFormation::AddFightersCurrHPPer(float fFactor)
{
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
        {
            UINT32 dwHP = rLineup.pFighter->GetHPMax() * fFactor;
            rLineup.pFighter->AddHP(dwHP);
        }
    }
}


std::string CFormation::GetInfoLog()
{
    std::string strLog;
    for (int i = 0; i < GetSlots(); ++i)
    {
        LineupGrid& rLineup = Get(i);
        if (HasObj(i) && rLineup.pFighter)
        {
            strLog += rLineup.pFighter->GetInfoLog();
        }
    }

    return strLog;
}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

