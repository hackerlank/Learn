#include "GemstoneSlots.h"
#include "User.h"
#include "Player.h"
#include "HeroFighter.h"
#include "FighterManager.h"
CGemstoneSlots::CGemstoneSlots(CHeroFighter& rFighter):_rFighter(rFighter)
{
    _vecStone.resize(GEMSTONE_SLOT_COUNT,NULL);
}

CGemstoneSlots::~CGemstoneSlots()
{
}


EStoreType CGemstoneSlots::GetStoreType() const 
{ 
    return eStoreGemstone; 
}


void CGemstoneSlots::SetDirty() const
{
    _rFighter.SetDirty(true);
}


void CGemstoneSlots::GetGemstoneAll(TVecGemstonePtr &vecStone) const
{
    for(auto it =_vecStone.begin();it != _vecStone.end();it++)
    {
        if(*it != NULL)
        {
            vecStone.push_back(*it);
        }
    }
}

EGemstoneResult CGemstoneSlots::Ware(UINT16 wItemId, UINT8 bySlotIndex,SGemstone &sItem,UINT16& wStoneLevel)
{
    //检查相同Type
    if(bySlotIndex >= GEMSTONE_SLOT_COUNT)
    {
        return eGemstoneFailed;
    }
    CItemPtr pItem = CItemMgr::CreateGemstone(wItemId);
    if(!pItem)
        return eGemstoneFailed; 
    CGemstonePtr pGemstone = dynamic_pointer_cast<CGemstone>(pItem);
    if(!pGemstone)
        return eGemstoneFailed;
    if (!pGemstone)
        return eGemstoneFailed;
    bool bReplace = false;
    if (_vecStone[bySlotIndex] != NULL)//非空
    {
        if(_vecStone[bySlotIndex]->GetItemCfgType() != pGemstone->GetItemCfgType())
        {
            return eGemstoneFailed;
        }
        if(_vecStone[bySlotIndex]->GetItemID() == pGemstone->GetItemID())
        {
            return eGemstoneFailed;
        }
        bReplace =true;
    }
    if(!pGemstone->IsGemstone())
    {
        return  eGemstoneFailed;
    }
    if(!bReplace)
    {
        TVecGemstonePtr vecStone;
        GetGemstoneAll(vecStone); 
        for(auto it = vecStone.begin(); it != vecStone.end();it++)
        {
            CGemstonePtr& pStone = *it; 
            if(pGemstone->GetItemCfgType() == pStone->GetItemCfgType())
            {
                return  eGemstoneHasSameType;
            }
        }
    }
    else
    {
        Takeoff(bySlotIndex);
    }
    _vecStone[bySlotIndex] = pGemstone;
    pGemstone->SetOwnerID(_rFighter.GetInstID());
    pGemstone->SetIndex(bySlotIndex);
    pGemstone->SetBind(true);
    pGemstone->SetStoreType(eStoreGemstone);
    pGemstone->ToStream(sItem);
    Update2DB(pGemstone,eOpAdd);
    SetDirty();
    wStoneLevel = pGemstone->GetStoneLevel();
    return eGemstoneSuccess;
}

EGemstoneResult CGemstoneSlots::Takeoff(UINT8 bySlotIndex)
{
    if(bySlotIndex < GEMSTONE_SLOT_COUNT)
    {
        CGemstonePtr pGemstone =  _vecStone[bySlotIndex];
        if(pGemstone == NULL)
        {
            return eGemstoneSlotEmpty;
        }
        CStore* pStore = _rFighter.GetUser()->GetStoreByType(eStorePack);
        if (!pStore)
            return eGemstoneFailed;
        SItemGenInfo rItemGenInfo;
        rItemGenInfo.wItemID = pGemstone->GetItemID();
        rItemGenInfo.dwCount = 1;
        if (!pStore->CanAddItem(rItemGenInfo))
            return eGemstonePackFull;
        //TODO:
        SetDirty();
        Update2DB(pGemstone,eOpDel);
        pStore->AddItem(rItemGenInfo, NLogDataDefine::ItemFrom_OffStone);
        _vecStone[bySlotIndex] = NULL;
    }
    else if( bySlotIndex == GEMSTONE_SLOT_COUNT)
    {
        CStore* pStore = _rFighter.GetUser()->GetStoreByType(eStorePack);
        if (!pStore)
            return eGemstoneFailed;
        TVecItemGenInfo rVecItemGenInfo;
        for(auto pos = _vecStone.begin(); pos != _vecStone.end();pos ++)
        {
            CGemstonePtr pGemstone =  *pos;
            if(pGemstone != NULL)
            {
                SItemGenInfo rItemGenInfo;
                rItemGenInfo.wItemID = pGemstone->GetItemID();
                rItemGenInfo.dwCount = 1;
                rVecItemGenInfo.push_back(rItemGenInfo);

            }
        }
        if(rVecItemGenInfo.empty())
        {
            return eGemstoneSuccess;
        }
        if (!pStore->CanAddItem(rVecItemGenInfo))
            return eGemstonePackFull;
        for(auto pos = 0; pos != GEMSTONE_SLOT_COUNT;pos++)
        {
            CGemstonePtr& pGemstone = _vecStone[pos];
            if (!pGemstone)
            {
                continue;
            }
            Update2DB(pGemstone,eOpDel);
            _vecStone[pos] = NULL;
        }
        pStore->AddItem(rVecItemGenInfo, NLogDataDefine::ItemFrom_OffStone);

        SetDirty();

    }
    return eGemstoneSuccess;

}


bool CGemstoneSlots::GetAddAttr(TVecFloat& rvecAddAttr) const
{
    TVecGemstonePtr vecStone;
    GetGemstoneAll(vecStone);
    for(auto it = vecStone.begin(); it != vecStone.end();it++)
    {
        CGemstonePtr& pStone = *it; 
        SItemInfo* pInfo = CItemMgr::GetItemConfig(pStone->GetItemID());
        if(pInfo && pInfo->pItemAttr)
        {
            pInfo->pItemAttr->SetIntoVec(rvecAddAttr);
        }
    }
    return true;
}

//获取符合等级条件的宝石数量
UINT32 CGemstoneSlots::GetStoneCount(UINT8 byMinLevel)
{
    UINT32 dwCount = 0;

    TVecGemstonePtr vecStone;
    GetGemstoneAll(vecStone);
    for(auto it = vecStone.begin(); it != vecStone.end();it++)
    {
        CGemstonePtr& pStone = *it; 
        if(pStone && pStone->GetStoneLevel() >= byMinLevel )
        {
            dwCount++;
        }
    }

    return dwCount;
}

void CGemstoneSlots::Update2DB(CGemstonePtr pItem,  EDataChange eDataChange)
{
    UINT64 qwFighterID = _rFighter.GetInstID();
    UINT64  qwUserID = _rFighter.GetUser()->GetUserID();
    if (!qwFighterID) 
    {
        return;
    }
    if(!qwUserID)
    {
        return ;
    }
    if(pItem->GetOwnerID() != qwFighterID)
    {
        pItem->SetOwnerID(qwFighterID);
    }

    SGemstonePtr ptr(new SGemstone);
    pItem->ToStream(*ptr);
    string strData;
    COutArchive iar(strData);
    SItem_Wrapper wrapper(ptr);
    iar << wrapper;
    g_Game2DBCommC.Send_RoleDataUpdate(qwUserID, eTypeGemstone, eDataChange, strData);

}

bool CGemstoneSlots::AddItemFromDB(CGemstonePtr pGemstone)
{
    if(!pGemstone)
        return false;
    if(pGemstone->GetIndex() >= GEMSTONE_SLOT_COUNT)
    {
        return false;
    }
    if (_vecStone[pGemstone->GetIndex()] != NULL)
        return false;
    //检查相同Type
    TVecGemstonePtr vecStone;
    GetGemstoneAll(vecStone);
    for(auto it = vecStone.begin(); it != vecStone.end();it++)
    {
        CGemstonePtr& pStone = *it; 
        if(pGemstone->GetItemCfgType() == pStone->GetItemCfgType())
        {
            return  false;
        }
    }
    _vecStone[pGemstone->GetIndex()] =  pGemstone;
    return true;
}

void CGemstoneSlots::GemstoneDismiss(TVecItemGenInfo& vecItems)
{
    for(auto pos = 0; pos != GEMSTONE_SLOT_COUNT; pos++)
    {
        CGemstonePtr& pGemstone = _vecStone[pos];
        if (!pGemstone)
            continue;
        SItemGenInfo stItemGen;
        stItemGen.wItemID = pGemstone->GetItemID();
        stItemGen.dwCount = 1;
        stItemGen.eBindType = eBindGet;
        vecItems.push_back(stItemGen);

        Update2DB(pGemstone, eOpDel);
        _vecStone[pos] = NULL;
    }
    SetDirty();
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

