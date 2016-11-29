#include "CittaSlots.h"

#include "CittaMgr.h"
#include "User.h"
#include "Player.h"
#include "FighterManager.h"

CCittaSlots::CCittaSlots()
    : CStore(0), _byAvaliableCount(0)
{
}

CCittaSlots::~CCittaSlots()
{
}

UINT8 CCittaSlots::GetAvaliableSlotsCount() const
{
    return _byAvaliableCount;
}

EStoreType CCittaSlots::GetStoreType() const 
{ 
    return eStorePlayerCitta; 
}

CUser& CCittaSlots::GetUser() const
{
    return *(GetPUser());
}

void CCittaSlots::SetDirty(bool bDirty) const
{
    CArrSlots::SetDirty(bDirty);
    if (!GetUserPtr())
        return;
    if (!bDirty)
        return;

    CPlayerPtr pPlayer = GetUserPtr()->GetPlayer();
    if (!pPlayer)
        return;
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
        return;
    pFighterManager->SetDirty(eAttrGpCitta);
}

bool  CCittaSlots::InitSlot(UINT16 wMaxSlot, UINT16 wMaxAvaliableSlot)
{
    if (wMaxAvaliableSlot <= CITTA_SLOT_COUNT && wMaxAvaliableSlot >= _byAvaliableCount)
    {
        _byAvaliableCount = wMaxAvaliableSlot;
        SetMaxSlot(CITTA_SLOT_COUNT, true);
        SetMaxAvaliable(_byAvaliableCount, true);
        SetCapacity(_byAvaliableCount);
        SetDirty(true);
        return true;
    }
    return false;
}

ECittaResult CCittaSlots::Ware(CCittaPtr pCitta, UINT8 bySlotIndex)
{
    if (!pCitta)
        return eCittaFailed;
    if (HasObj(bySlotIndex))
        return eCittaSlotNotEmpty;
    if (!Set(bySlotIndex, pCitta))
        return eCittaFailed;
    if (!CanAddItem(*pCitta, bySlotIndex))
        return eCittaFailed;
    CStore* pFromStore = GetUser().GetStoreByType(EStoreType(pCitta->GetStoreType()));
    if (pFromStore)
        pFromStore->DelItem(*pCitta, true, false, NLogDataDefine::ItemTo_MergeCitta);
    if (GetFighter())
        pCitta->SetOwnerID(GetFighter()->GetInstID());
    pCitta->SetBind(true);
    AddItem(*pCitta, bySlotIndex, true, false, true);
    SetDirty(true);
    return eCittaSuccess;
}

ECittaResult CCittaSlots::Takeoff(UINT8 bySlotIndex)
{
    // XXX: 这里要想办法不调用Slot
    CItemPtr pItem = NULL;
    pItem = GetItem(static_cast<INT16>(bySlotIndex));
    if (!pItem)
        return eCittaFailed;
    Unset(bySlotIndex, pItem);
    pItem = GetItem(static_cast<INT16>(bySlotIndex));

    CStore* pStore = GetUser().GetStoreByType(eStorePack);
    if (!pStore)
        return eCittaFailed;
    if (pItem->IsCittaItem())
    {
        CCittaPtr pCitta = dynamic_pointer_cast<CCitta>(pItem);
        if (!pStore->CanAddItem(*pCitta))
            return eCittaPackFull;
        DelItem(*pCitta, true, false, NLogDataDefine::ItemTo_MergeCitta);
        pStore->AddItem(*pCitta, -1, true, false, true, NLogDataDefine::ItemFrom_CittaStore);
        SetDirty(true);
        return eCittaSuccess;
    }
    else
        return eCittaFailed;
}

bool CCittaSlots::TestUnlockSlot(UINT8 byNewLevel)
{
    static const UINT16 s_wUnlockLevel[] =
    {
        SParamConfig::wBooks1,
        SParamConfig::wBooks2,
        SParamConfig::wBooks3,
        SParamConfig::wBooks4,
        SParamConfig::wBooks5
            /*
        30,     // 30级1个
        35,     // 35级2个
        40,     // 40级3个
        45,     // 45级4个
        50,     // 50级5个
        55,     // 55级6个
        60,     // 60级7个
        65      // 65级8个
            */
    };
    UINT8 byNewCount = 0;
    for (UINT8 byIndex = 0; byIndex < sizeof(s_wUnlockLevel) / sizeof(UINT16); ++byIndex)
    {
        if (s_wUnlockLevel[byIndex] <= byNewLevel)
            ++byNewCount;
        else
            break;
    }
    if (byNewCount > CITTA_SLOT_COUNT || byNewCount <= _byAvaliableCount)
        return false;
    _byAvaliableCount = byNewCount;
    SetMaxSlot(CITTA_SLOT_COUNT, true);
    SetMaxAvaliable(_byAvaliableCount);
    if (_byAvaliableCount > _wCapacity)
        Expand(_byAvaliableCount - _wCapacity);
    SetDirty(true);
    return true;
}

bool CCittaSlots::GetAddAttr(TVecFloat& rvecAddAttr) const
{
    vector<CItemPtr> vecItem;
    GetAllItemList(vecItem);
    TSetUINT32 setSignetID;

    for (auto it = vecItem.begin(); it != vecItem.end(); ++it)
    {
        if (!(*it))
            continue;
        CCittaPtr pCitta = dynamic_pointer_cast<CCitta>(*it);
        if (pCitta)
        {
            const TMapCittaAttr& rmapCittaAttr = pCitta->GetAttr();
            for (auto it = rmapCittaAttr.begin(); it != rmapCittaAttr.end(); ++it)
            {
                if (it->first >= rvecAddAttr.size())
                    rvecAddAttr.resize(it->first + 1);
                rvecAddAttr[it->first] += it->second;
                if (it->first == EFIGHTATTR_PHYATK)
                    rvecAddAttr[EFIGHTATTR_MGCATK] += it->second;
            }
            setSignetID.insert(pCitta->GetSignetID());
        }
    }
    CCittaMgr::Instance().SignetToAttr(setSignetID, rvecAddAttr);
    SetDirty(false);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

