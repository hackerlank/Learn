#include "stdafx.h"
#include "Store.h"
#include "Protocols.h"
#include "StackItem.h"
#include "ItemMgr.h"
#include "StackItem.h"
#include "Player.h"
#include "Map.h"
#include "SysMsgDefine.h"
#include "Parameter.h"
#include "Citta.h"
#include "GameServerLog.h"
#include "Loot.h"
#include "Game2CenterLog.h"
#include "HeroFighter.h"
#include "TrumpSlots.h"
#include "FighterManager.h"
#include "CittaSlots.h"

using namespace NGame2CenterLog;

CStore::~CStore()
{
    _mapID2Slot.clear();
    //LOG_CRI << "delete Store";
}

CUserPtr CStore::GetUserPtr() const
{
    return ToThisPtr(GetUser());
}

bool CStore::SendPkg(const string& strPkg)
{
    return GetUser().SendPkg(strPkg);
}

bool CStore::ItemAddNotify(CItem& rItem, bool bNew)
{
    TVecItem vecStoreItem;
    vecStoreItem.push_back(rItem.ToProt());
    GetUser().GetTaskPkg().OnCollectItem(rItem.GetItemID());
    

    if(rItem.IsGemstone())
    {
        CPlayerPtr pPlayer = GetUser().GetPlayer();
        if(pPlayer)
        {
            TVecINT32 vecParam;
            vecParam.push_back(rItem.GetType());
            vecParam.push_back(rItem.GetStoneLevel());
            pPlayer->OnEvent(eEventType_GemsGet,vecParam);
        }

    }

    //法宝碎片
    if(bNew && rItem.GetType()==14)
    {
        CPlayerPtr pPlayer = GetUser().GetPlayer();
        if(pPlayer)
        {
        TVecINT32 vecParam;
        vecParam.push_back(rItem.GetID());
        pPlayer->OnEvent(eEventType_TrumpGet,vecParam);
        }

    }
    //橙色以上广播
    if(bNew && rItem.IsEquipTrumpItem())
    {
        
        CPlayerPtr pPlayer = GetUser().GetPlayer();
        if(pPlayer)
        {
            if(rItem.GetQuality()>=5)
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eEquipTrumpGet,
                 BuildStrVec(pPlayer->GetColor(),pPlayer->GetName(),rItem.GetQuality(),rItem.GetItemName()));

            TVecINT32 vecParam;
            vecParam.push_back(rItem.GetID());
            pPlayer->OnEvent(eEventType_TrumpGet,vecParam);
        }
    }

    return GetUser().SendPkg(g_ItemProtS.BuildPkg_StoreItemAddNtf(GetStoreType(), vecStoreItem, bNew));
}

bool CStore::ItemAddNotify(SStoreSlot& rStoreSlot, bool bNew)
{
    if(rStoreSlot.pItem == NULL)
        return false;
    CItem& rItem = *rStoreSlot.pItem;
    return ItemAddNotify(rItem, bNew);
}

bool CStore::CittaAddNotify(const vector<CCittaPtr>& vecCittaPtr)
{
    TVecItem vecStoreItem;
    for (auto it = vecCittaPtr.begin(); it != vecCittaPtr.end(); ++it)
    {
        vecStoreItem.push_back((*it)->ToProt());
    }
    return  GetUser().SendPkg(g_ItemProtS.BuildPkg_CittaAddNtf(GetStoreType(), vecStoreItem, true));
}

//是否有足够的物品扣除
bool CStore::CanSubItem(const TVecItemCount& vecItemCount,EBindUseType eBindUseType)
{
    TVecSStoreSlot oVecStoreSlot;
    UINT32 dwCount = 0;
    for (size_t i = 0; i < vecItemCount.size(); ++i)
    {
        dwCount = GetItemList(vecItemCount[i].wItemID, oVecStoreSlot, vecItemCount[i].wCount, eBindUseType);
        if (dwCount < vecItemCount[i].wCount)
            return false;
    }

    return true;
}

bool CStore::CanSubItemWithID(UINT16 wItemID,UINT32 dwCount,EBindUseType eBindUseType)
{
    TVecSStoreSlot oVecStoreSlot;
    return GetItemList(wItemID,oVecStoreSlot,dwCount,eBindUseType)>= dwCount;
}

//扣除物品
void CStore::SubItem(const TVecItemCount& vecItemCount, UINT16 toWhere,EBindUseType eBindUseType)
{
    for (size_t i = 0; i < vecItemCount.size(); ++i)
    {
        SubItemWithID(vecItemCount[i].wItemID,vecItemCount[i].wCount,toWhere,eBindUseType);
    }
}

void CStore::SubItemWithID(UINT16 wItemID,UINT32 dwCount,UINT32 dwLogType,EBindUseType eBindUseType)
{   
    TVecSStoreSlot oVecStoreSlot; 
    UINT32 dwTotal = GetItemList(wItemID,oVecStoreSlot,dwCount,eBindUseType);
    if (dwTotal)
    {
        DelItemFromSlots(dwCount, oVecStoreSlot, dwLogType);
    }
}


bool CStore::ItemDelNotify(CItem& rItem)
{
    TVecUINT64 vecInstID;
    vecInstID.push_back(rItem.GetInstID());
    GetUser().GetTaskPkg().OnCollectItem(rItem.GetItemID());
    return GetUser().SendPkg(g_ItemProtS.BuildPkg_StoreItemDelNtf(GetStoreType(), vecInstID));
}

bool CStore::StoreItemNotify()
{
    TVecItem vecStoreItem;
    GetItemList(vecStoreItem);
    UINT64 qwUsrID = GetUser().GetUserID();
    return g_ItemProtS.SendClt_StoreNotify(&qwUsrID, 1, GetStoreType(), GetCapacity(), vecStoreItem);
}


UINT32 CStore::GetItemCount(UINT16 wItemID)
{
    UINT32 wCount = 0;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->GetItemID() == wItemID)
        {
            if(rStoreSlot.pItem->IsStackItem())
                wCount += rStoreSlot.pItem->GetCount();
            else
                ++wCount;
        }
    }
    return wCount;
}

UINT32 CStore::GetItemCount(UINT16 wItemID) const
{
    UINT32 wCount = 0;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->GetItemID() == wItemID)
        {
            if(rStoreSlot.pItem->IsStackItem())
                wCount += rStoreSlot.pItem->GetCount();
            else
                ++wCount;
        }
    }
    return wCount;
}

// ===  FUNCTION  ======================================================================
//         Name:  GetItemCount
//  Description:  根据绑定类型获取对应物品数量
// =====================================================================================
UINT16 CStore::GetItemCount(UINT16 wItemID, EBindUseType eBindUseType) const
{
    UINT16 wCount = 0;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->GetItemID() == wItemID)
        {
            if ( 
                    (rStoreSlot.pItem->IsBind() && (eBindUseType == eBindUseBindFirst || eBindUseType == eBindUseBind)) // 绑定，优先使用绑定或者只使用绑定
                    ||
                    (!rStoreSlot.pItem->IsBind() && (eBindUseType == eBindUseNoneFirst || eBindUseType == eBindUseNone)) // 非绑定，优先使用非绑定或者只是用非绑定
               )
            {
                if(rStoreSlot.pItem->IsStackItem())
                    wCount += rStoreSlot.pItem->GetCount();
                else
                    ++wCount;
            }
        }
    }
    if (eBindUseType == eBindUseNone || eBindUseType == eBindUseBind) // 只使用一种的判断完毕
        return wCount;

    // 优先使用的检查另一种绑定类型物品的数量
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->GetItemID() == wItemID)
        {
            if (
                    (!rStoreSlot.pItem->IsBind() && (eBindUseType == eBindUseBindFirst))  // 优先绑定，检查非绑定的数量
                    ||
                    (rStoreSlot.pItem->IsBind() && (eBindUseType == eBindUseNoneFirst))   // 优先非绑定，检查绑定的数量
               )
            {
                if(rStoreSlot.pItem->IsStackItem())
                    wCount += rStoreSlot.pItem->GetCount();
                else
                    ++wCount;
            }
        }
    }
    return wCount;
}

UINT32 CStore::GetEquipTrumpCount(UINT8 byMinQuality,UINT8 byMinInsifyLevel)
{
    UINT32 wCount = 0;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        if(NULL == rStoreSlot.pItem)
            continue;
        if(rStoreSlot.pItem->IsEquipTrumpItem())
        {
            if(rStoreSlot.pItem->GetQuality()==byMinQuality && rStoreSlot.pItem->GetEquipTrumpLevel()>= byMinInsifyLevel)
            {
                ++wCount;
            }
        }
    }

    return wCount;
}

UINT32 CStore::GetStoneCount(UINT8 byMinLevel)
{

    UINT32 wCount = 0;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->IsGemstone())
        {
            if(rStoreSlot.pItem->GetStoneLevel()>=byMinLevel)
            {
                wCount += rStoreSlot.pItem->GetCount();
            }
        }
    }

    return wCount;
}


UINT16 CStore::GetEmptyCount() const
{
    UINT16 wItemCount = (UINT16)_mapID2Slot.size();
    if(GetCapacity() < wItemCount)
    {
        LOG_CRI << "error! _wCapacity:" << GetCapacity() << ", wItemCount:" << wItemCount;
        return 0;
    }
    return GetCapacity() - wItemCount;
}

SStoreSlot* CStore::GetSlot(UINT64 qwInstID)
{
    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return NULL;
    return &it->second;
}

CItemPtr CStore::GetItem(UINT64 qwInstID, INT16* pIndex /*= NULL*/)
{
    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return NULL;
    if(it->second.wIndex >= GetCapacity())
        return NULL;
    if(pIndex != NULL)
        *pIndex = it->second.wIndex;
    return it->second.pItem;
}

CItemPtr CStore::GetItem(INT16 wIndex) const
{
    auto it = _mapID2Slot.find(GetInstByIndex(wIndex));
    if(it == _mapID2Slot.end())
        return NULL;
    if(it->second.wIndex >= GetCapacity())
        return NULL;
    return it->second.pItem;
}

CItemPtr CStore::GetItem(INT16 wIndex)
{
    auto it = _mapID2Slot.find(GetInstByIndex(wIndex));
    if(it == _mapID2Slot.end())
        return NULL;
    if(it->second.wIndex >= GetCapacity())
        return NULL;
    return it->second.pItem;
}

UINT64 CStore::GetInstByIndex(INT16 wIndex) const
{
    auto it = _mapIndex2Item.find(wIndex);
    if(it == _mapIndex2Item.end())
        return 0;
    return it->second;
}

UINT64 CStore::GetInstByIndex(INT16 wIndex)
{
    auto it = _mapIndex2Item.find(wIndex);
    if(it == _mapIndex2Item.end())
        return 0;
    return it->second;
}

INT16 CStore::GetIndexByInst(UINT64 qwInstID)
{
    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return -1;
    return it->second.wIndex;
}

bool CStore::HasItem(UINT64 qwInstID)
{
    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return false;
    SStoreSlot& rStoreSlot = it->second;
    if(rStoreSlot.wIndex >= GetCapacity())
    {
        LOG_CRI << "Slot index is invalid! wIndex: " << rStoreSlot.wIndex;
        return false;
    }
    return true;
}

bool CStore::HasItem(UINT16 wItemID)
{
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        SStoreSlot& rSlot = it->second;
        if(rSlot.pItem != NULL && rSlot.pItem->GetItemID() == wItemID)
            return true;
    }
    return false;
}

bool CStore::CanAddItemWithID(UINT16 wItemID, UINT32 dwNum, EBindType eBindType, UINT8 byQuality)
{
    if(wItemID < EMONEY_END)
    {
        return true;
    }
    SItemGenInfo oItemGenInfo;
    oItemGenInfo.wItemID = wItemID;
    oItemGenInfo.dwCount = dwNum;
    oItemGenInfo.byQuality = byQuality;
    oItemGenInfo.eBindType = eBindType;
    return CanAddItem(oItemGenInfo);
}

bool CStore::CanAddItem(const SItemGenInfo& rItemGenInfo)
{
    TVecItemGenInfo vecItemGenInfo(1, rItemGenInfo);
    return CanAddItem(move(vecItemGenInfo));
}

bool CStore::CanAddItem(const TVecItemGenInfo& rVecItemGenInfo, bool bNotify /* = false */)
{
    //是否包裹足够
    UINT16 wPackCount = 0;
    map<UINT16, UINT32> mapID2RemCount;
    for(auto it = rVecItemGenInfo.begin();it != rVecItemGenInfo.end();it++)
    {
        UINT16 wItemID = it->wItemID;
        UINT16 wCount = (UINT16)it->dwCount;
        UINT8 byQuality = it->byQuality;
        UINT32 dwTimeID = it->dwTimeID;
        EBindType eBindType = it->eBindType;
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
        if (!pItemInfo)
            return false;
        SItemCFG& rItemCFG = pItemInfo->oItemCfg;

        if(eItemResource == rItemCFG._Type)
            continue;
        //XXX 绑定类型根据配置表来！！
        if (eBindType == eBindNone)
            eBindType = EBindType(rItemCFG._Binding);
        bool bBind = eBindType == eBindGet;

        // TODO:
#if 0
        if (SParamConfig::wSwingFashionItemID == rItemCFG._ID
                && eItemSubFashion == CItem::GetItemSubType(rItemCFG))
            continue;
#endif

        if(byQuality == eColorNone || byQuality >= eColorEnd)
            byQuality = rItemCFG._Quality;

        if(wCount == 0)
            return false;

        if(CItem::IsStackItem(rItemCFG))
        {
            UINT32 dwRemCount = 0;
            auto it_count = mapID2RemCount.find(wItemID);
            if(it_count != mapID2RemCount.end())
            {
                dwRemCount = it_count->second;
            }
            else
            {
                vector<CStackItemPtr> vecStackItem;
                for(auto itID = _mapID2Slot.begin(); itID != _mapID2Slot.end(); ++itID)
                {
                    SStoreSlot& rStoreSlot = itID->second;
                    if(rStoreSlot.pItem == NULL)
                        continue;
                    if(rStoreSlot.pItem->IsStackItem())
                    {
                        CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
                        if(pStackItem == NULL)
                        {
                            return false;
                        }
                        if(pStackItem->CanMerge(wItemID, byQuality, bBind, dwTimeID))
                            vecStackItem.push_back(pStackItem);
                    }
                }
                if(!vecStackItem.empty())
                {
                    sort(vecStackItem.begin(), vecStackItem.end(), [](const CStackItemPtr& left, const CStackItemPtr& right)->bool{ return left->GetCount() > right->GetCount(); });
                    for(size_t i = 0; i < vecStackItem.size(); ++i)
                    {
                        CStackItemPtr pStackItem = vecStackItem[i];
                        dwRemCount += (UINT32)pStackItem->GetEmptyCount();
                    }
                }
            }
            if((UINT32)wCount > dwRemCount)
            {
                wCount -= (UINT16)dwRemCount;
                dwRemCount = 0;
            }
            else
            {
                dwRemCount -= wCount;
                wCount = 0;
            }
            while(wCount >= rItemCFG._Stack)
            {
                wPackCount++;
                wCount -= rItemCFG._Stack;
            }
            if(wCount > 0)
            {
                wPackCount++;
                dwRemCount = (UINT32)(rItemCFG._Stack - wCount);
                wCount = 0;
            }
            if (dwRemCount > 0)
                mapID2RemCount.insert(make_pair(wItemID, dwRemCount));
        }
        else
        {
            wPackCount += wCount;
        }
    }
    if(wPackCount > GetEmptyCount())
    {
        if (bNotify)
        {
            string strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgStovePackageFull);
            GetUser().SendPkg(strPkg);
        }
        return false;
    }
    return true;
}

bool CStore::CanAddItem( vector<CItemPtr>& rVecCItem)
{
    INT16 wTotalEmptyCount = GetEmptyCount();//总的空格数
    map<UINT64,UINT16> mapUse;//现存物品已用数量 
    vector<CStackItemPtr> NewSlot;
    for(auto iter = rVecCItem.begin();iter != rVecCItem.end();iter++)
    {
        CItem& rItem=*(*(iter));
        UINT64 qwInstID = rItem.GetInstID();
        if(_mapID2Slot.find(qwInstID) != _mapID2Slot.end())
            continue; 
        //堆叠
        if(rItem.IsStackItem())
        {
            CStackItemPtr pFromItem = ToPtr<CStackItem>(rItem);
            if(NULL == pFromItem)
                return false;
            UINT16 wCount = pFromItem->GetCount();//欲插入数量
            vector<CStackItemPtr> vecStackItem;
            for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
            {
                SStoreSlot& rStoreSlot = it->second;
                if(rStoreSlot.pItem == NULL)
                    continue;
                if(rStoreSlot.pItem->IsStackItem())
                {
                    CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
                    if(pStackItem->CanMerge(*pFromItem))//察看可否合并
                        vecStackItem.push_back(pStackItem);//这是合并物品
                }
            }
            //在原包裹查找
            if(!vecStackItem.empty())
            {
                /*测试不必排序 
                  sort(vecStackItem.begin(), vecStackItem.end(), [](const CStackItemPtr& left, const CStackItemPtr& right)->bool{ return left->GetCount() > right->GetCount(); });//从大到小排序*/
                for(size_t i = 0; i < vecStackItem.size(); ++i)
                {   
                    CStackItemPtr pStackItem = vecStackItem[i];
                    UINT64 qwStackInstID = pStackItem->GetInstID();
                    auto iter = mapUse.find(qwStackInstID);
                    UINT16 wPreUse = 0;
                    if(iter != mapUse.end())
                    {
                        wPreUse = iter->second;
                    }
                    UINT16 wCurrentEmpty = pStackItem->GetEmptyCount() - wPreUse;
                    if(wCurrentEmpty == 0)
                    {
                        continue;
                    }
                    if(wCount >= wCurrentEmpty)
                    {
                        wCount -= wCurrentEmpty;
                        mapUse[qwStackInstID] =  pStackItem->GetEmptyCount();
                    }
                    else 
                    {

                        mapUse[qwStackInstID] = wPreUse + wCount;
                        wCount = 0;
                        break;

                    }
                }
            }
            if(wCount != 0 && !NewSlot.empty())
            {
                vector<CStackItemPtr> vecNewStackItem;
                for(auto it = NewSlot.begin(); it != NewSlot.end(); ++it)
                {
                    if((*it)->IsStackItem())
                    {
                        CStackItemPtr pStackItem = *it;
                        if(pStackItem->CanMerge(*pFromItem))//察看可否合并
                            vecNewStackItem.push_back(pStackItem);//这是合并物品
                    }
                }
                for(size_t i = 0; i < vecNewStackItem.size(); ++i)
                {   
                    CStackItemPtr pStackItem = vecNewStackItem[i];
                    UINT64 qwStackInstID = pStackItem->GetInstID();
                    auto iter = mapUse.find(qwStackInstID);
                    UINT16 wPreUse = 0;
                    if(iter != mapUse.end())
                    {
                        wPreUse = iter->second;
                    }
                    UINT16 wCurrentEmpty = pStackItem->GetEmptyCount() - wPreUse;
                    if(wCurrentEmpty == 0)
                    {
                        continue;
                    }
                    if(wCount >= wCurrentEmpty)
                    {
                        wCount -= wCurrentEmpty;
                        mapUse[qwStackInstID] =  pStackItem->GetEmptyCount();
                    }
                    else 
                    {

                        mapUse[qwStackInstID] = wPreUse + wCount;
                        wCount = 0;
                        break;

                    }
                }

            }

            if(wCount != 0)//没有全部合并
            {
                wTotalEmptyCount--;//扣除一个空格子
                if(wTotalEmptyCount < 0)
                {
                    return false;
                }
                else //生成一个新格子
                {
                    pFromItem->SetCount(wCount);
                    NewSlot.push_back(pFromItem);
                }
            }
        }
    }
    return true;
}

bool CStore::CanAddItem(CItem& rItem, INT16 wIndex/* = -1*/)
{
    UINT64 qwInstID = rItem.GetInstID();
    if(_mapID2Slot.find(qwInstID) != _mapID2Slot.end())
        return true;

    if(wIndex == -1)
    {
        //堆叠
        if(rItem.IsStackItem())
        {
            CStackItemPtr pFromItem = ToPtr<CStackItem>(rItem);
            UINT16 wCount = pFromItem->GetCount();
            if(NULL == pFromItem)
                return false;
            vector<CStackItemPtr> vecStackItem;
            for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
            {
                SStoreSlot& rStoreSlot = it->second;
                if(rStoreSlot.pItem == NULL)
                    continue;
                if(rStoreSlot.pItem->IsStackItem())
                {
                    CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
                    if(pStackItem->CanMerge(*pFromItem))
                        vecStackItem.push_back(pStackItem);
                }
            }
            if(!vecStackItem.empty())
            {
                sort(vecStackItem.begin(), vecStackItem.end(), [](const CStackItemPtr& left, const CStackItemPtr& right)->bool{ return left->GetCount() > right->GetCount(); });
                for(size_t i = 0; i < vecStackItem.size(); ++i)
                {
                    CStackItemPtr pStackItem = vecStackItem[i];
                    if(wCount > pStackItem->GetEmptyCount())
                    {
                        wCount -= pStackItem->GetEmptyCount();
                    }
                    else
                    {
                        wCount = 0;
                        break;
                    }
                }
            }
            if(wCount == 0)
                return true;
        }
    }
    if(GetEmptyCount() == 0)
        return false;

    return true;
}

bool CStore::CanAddItem(const TVecSStoreSlot& vecStore)
{
    //是否包裹足够
    UINT16 wPackCount = 0;
    map<UINT16, UINT32> mapID2RemCount;
    for(const SStoreSlot& rStore : vecStore)
    {
        UINT16 wItemID = rStore.pItem->GetItemID();
        UINT16 wCount = (UINT16)rStore.pItem->GetCount();
        UINT8 byQuality = rStore.pItem->GetQuality();
        UINT32 dwTimeID = rStore.pItem->GetTimeID();
        bool bBind = rStore.pItem->IsBind();
        const SItemCFG& rItemCFG = rStore.pItem->GetItemCfg();

        if(eItemResource == CItem::GetItemType(rItemCFG))
            continue;

        // TODO:
#if 0
        if (SParamConfig::wSwingFashionItemID == rItemCFG._ID
                && eItemSubFashion == CItem::GetItemSubType(rItemCFG))
            continue;
#endif

        if(wCount == 0)
            return false;

        if(rStore.pItem->IsStackItem())
        {
            UINT32 dwRemCount = 0;
            auto it_count = mapID2RemCount.find(wItemID);
            if(it_count != mapID2RemCount.end())
            {
                dwRemCount = it_count->second;
            }
            else
            {
                vector<CStackItemPtr> vecStackItem;
                for(auto itID = _mapID2Slot.begin(); itID != _mapID2Slot.end(); ++itID)
                {
                    SStoreSlot& rStoreSlot = itID->second;
                    if(rStoreSlot.pItem == NULL)
                        continue;
                    if(rStoreSlot.pItem->IsStackItem())
                    {
                        CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
                        if(pStackItem->CanMerge(wItemID, byQuality, bBind, dwTimeID))
                            vecStackItem.push_back(pStackItem);
                    }
                }
                if(!vecStackItem.empty())
                {
                    sort(vecStackItem.begin(), vecStackItem.end(), [](const CStackItemPtr& left, const CStackItemPtr& right)->bool{ return left->GetCount() > right->GetCount(); });
                    for(size_t i = 0; i < vecStackItem.size(); ++i)
                    {
                        CStackItemPtr pStackItem = vecStackItem[i];
                        dwRemCount += (UINT32)pStackItem->GetEmptyCount();
                    }
                }
            }
            if((UINT32)wCount > dwRemCount)
            {
                wCount -= (UINT16)dwRemCount;
                dwRemCount = 0;
            }
            else
            {
                dwRemCount -= wCount;
                wCount = 0;
            }
            while(wCount >= rItemCFG._Stack)
            {
                wPackCount++;
                wCount -= rItemCFG._Stack;
            }
            if(wCount > 0)
            {
                wPackCount++;
                dwRemCount = (UINT32)(rItemCFG._Stack - wCount);
                wCount = 0;
            }
            if (dwRemCount > 0)
                mapID2RemCount.insert(make_pair(wItemID, dwRemCount));
        }
        else
        {
            wPackCount += wCount;
        }
    }
    if(wPackCount > GetEmptyCount())
    {
        return false;
    }
    return true;
}

bool CStore::AddItem(const SItemGenInfo& rItemGenInfo, UINT16 fromWhere, bool bNotify /*= true*/, bool bNotifyMsg /*= true*/, bool bBuy /*= false*/)
{
    TVecItemGenInfo vecItemGenInfo(1, rItemGenInfo);
    return AddItem(vecItemGenInfo, fromWhere, bNotify, bNotifyMsg, bBuy);
}

bool CStore::AddItem(const TVecItemGenInfo& rVecItemGenInfo, UINT16 fromWhere, bool bNotify/* = true*/, bool bNotifyMsg /*= true*/, bool bBuy /*= false*/)
{
    CUser& rUser = GetUser();

    if(rVecItemGenInfo.empty())
        return true;
    if(!CanAddItem(rVecItemGenInfo))
        return false;
    TVecAddItemMsg vecItemMsg;
    TVecResource vecRes;
    for(auto it = rVecItemGenInfo.begin();it != rVecItemGenInfo.end();it++)
    {
        const SItemGenInfo& rItemGenInfo = *it;
        SItemInfo* pItemInfo = CItemMgr::GetItemConfig(it->wItemID);
        if (!pItemInfo)
            return false;
        SItemCFG& rItemCFG = pItemInfo->oItemCfg;

        // TODO:
#if 0
        if (SParamConfig::wSwingFashionItemID == rItemCFG._ID
                && eItemSubFashion == CItem::GetItemSubType(rItemCFG))
        {
            if (CFashionMgr::AddFashion(rUser, (UINT16)rItemCFG._P1))
                CFashionMgr::UseFashion(rUser, 0, (UINT16)rItemCFG._P1);
            continue;
        }
#endif

        if(eItemResource == rItemCFG._Type)
        {
            SResource sRes;
            sRes._eRes = NProtoCommon::EMoneyType(it->wItemID);
            sRes._dwValue = it->dwCount;
            vecRes.push_back(sRes);
            if(IsInUseItem())
            {
                _vecUseItemRes.push_back(sRes);
            }
        }
        else if(6 == rItemCFG._Type)
        {
            UINT32 wFighterID = rItemCFG._AttrIdx_3;
            CPlayerPtr pPlayer = GetUser().GetPlayer();
            if(pPlayer&&pPlayer->GetFighterManager())
            {
                pPlayer->GetFighterManager()->GetFighterForce(wFighterID);
            }
        }
        else
        {
            SAddItemMsg oAddItemMsg;
            if(IsInUseItem())
            {
                _vecUseItemItems.push_back(rItemGenInfo);
            }
            if (InternalAddItem(rItemGenInfo, oAddItemMsg, bNotify, fromWhere))
                vecItemMsg.emplace_back(std::move(oAddItemMsg));
        }
    }

    if(!vecRes.empty())
        AddResource(rUser, vecRes, fromWhere,NULL, bNotify);

    if(bNotify && bNotifyMsg && !vecItemMsg.empty())
        GetUser().SendPkg(g_ItemProtS.BuildPkg_AddItemSystemMsg(vecItemMsg)); 

    CPlayerPtr pPlayer = GetUser().GetPlayer();
    if (pPlayer)
        GetUser().GetTaskPkg().OnAction(*pPlayer, eProcessAction_GetItem); 
    
    return true;
}

bool CStore::InternalAddItem(const SItemGenInfo& rItemGenInfo, SAddItemMsg& rAddItemMsg, bool bNotify /*= true*/, UINT16 fromWhere /*= 0*/)
{
    UINT16 wItemID = rItemGenInfo.wItemID;
    UINT16 wCount = rItemGenInfo.dwCount;
    UINT8 byQuality = rItemGenInfo.byQuality;
    EBindType eBindType = rItemGenInfo.eBindType;
    UINT32 dwTimeID = rItemGenInfo.dwTimeID;

    SItemInfo* pItemInfo = CItemMgr::GetItemConfig(wItemID);
    if (!pItemInfo)
        return false;
    SItemCFG& rItemCFG = pItemInfo->oItemCfg;

    if(byQuality == eColorNone || byQuality >= eColorEnd)
        byQuality = rItemCFG._Quality;
    //XXX 绑定类型根据配置表来！！
    if (eBindType == eBindNone)
        eBindType = EBindType(rItemCFG._Binding);
    bool bBind = eBindType == eBindGet;

    if(wCount == 0)
        return false;
    //XXX udpLog
    TVecUserItemChange vecItemChange;
    float fPrice = 0.0f;
    if (fromWhere == ItemFrom_Mall)
        fPrice = CItemMgr::GetGoldPrice(wItemID);
    SUserItemChange oItemChange(wItemID, wCount, fPrice, fromWhere);
    vecItemChange.push_back(oItemChange);
    GetUser().SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogItemChange(GetUser().GetUserID(), eOpTypeItemChange, vecItemChange));

    rAddItemMsg.wItemID = wItemID;
    rAddItemMsg.byQuality = byQuality;
    rAddItemMsg.wCount = wCount;

    CItemPtr pItem = NULL;
    if(CItem::IsStackItem(rItemCFG)) // 是否是可以堆叠的物品
    {
        TVecSStoreSlot vecStackItem;
        for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
        {
            SStoreSlot& rStoreSlot = it->second;
            if(rStoreSlot.pItem == NULL)
                continue;
            if(rStoreSlot.pItem->IsStackItem())
            {
                CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
                if(pStackItem->CanMerge(wItemID, byQuality, bBind, dwTimeID))
                    vecStackItem.push_back(it->second);
            }
        }

        if(!vecStackItem.empty())
        {
            sort(vecStackItem.begin(), vecStackItem.end(),
                    [](const SStoreSlot& left, const SStoreSlot& right)->bool
                    {
                    return left.pItem->GetCount() > right.pItem->GetCount();
                    }
                );

            for(size_t i = 0; i < vecStackItem.size(); ++i)
            {
                CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(vecStackItem[i].pItem);
                UINT16 wIndex = vecStackItem[i].wIndex;
                if(wCount > pStackItem->GetEmptyCount())
                {
                    UINT16 wNum = pStackItem->GetEmptyCount();
                    pStackItem->SetOptCount(wNum);
                    wCount -= pStackItem->GetEmptyCount();
                    pStackItem->SetCount(pStackItem->GetMaxNum());
                    Update2DB(wIndex, *pStackItem, eOpUpdate, fromWhere);
                    pStackItem->NotifyCount(*this);
                }
                else
                {
                    pStackItem->SetOptCount(wCount);
                    pStackItem->AddCount(wCount);
                    Update2DB(wIndex, *pStackItem, eOpUpdate, fromWhere);
                    pStackItem->NotifyCount(*this);
                    wCount = 0;
                    break;
                }
            }
        }

        while(wCount >= rItemCFG._Stack)
        {
            pItem = CItemMgr::CreateAllTypeItem(wItemID, rItemCFG._Stack, byQuality);
            if(pItem == NULL)
                return false;
            pItem->SetBindType(GetStoreType(), eBindType);
            UINT16 wEmptyIndex = GetEmptyIndex();
            CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(pItem);
            pStackItem->SetOptCount(rItemCFG._Stack);
            if(!AddItem(*pItem, wEmptyIndex, bNotify, true, true,fromWhere))
                return false;

            wCount -= rItemCFG._Stack;
        }

        if(wCount > 0)
        {
            pItem = CItemMgr::CreateAllTypeItem(wItemID, wCount, byQuality);
            if(pItem == NULL)
                return false;
            pItem->SetBindType(GetStoreType(), eBindType);
            UINT16 wEmptyIndex = GetEmptyIndex();
            CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(pItem);
            if(!pStackItem)
                return false;
            pStackItem->SetOptCount(wCount);
            if(!AddItem(*pItem, wEmptyIndex, bNotify, true, true, fromWhere))
                return false;
        }
    }
    else
    {
        for(UINT16 i = 0; i < wCount; ++i)
        {
            pItem = CItemMgr::CreateAllTypeItem(wItemID, 1, byQuality);
            if(pItem == NULL)
                return false;
            pItem->SetBindType(GetStoreType(), eBindType);
            UINT16 wEmptyIndex = GetEmptyIndex();
            if(!AddItem(*pItem, wEmptyIndex, bNotify, true, true, fromWhere))
                return false;
        }
    }
    return true;
}

UINT16 CStore::GetEmptyIndex()
{
    UINT16 wEmptyIndex = 0;
    for(auto itIndex = _mapIndex2Item.begin(); itIndex != _mapIndex2Item.end(); ++itIndex)
    {
        if(wEmptyIndex != itIndex->first)
            break;
        ++wEmptyIndex;
    }

    return wEmptyIndex;
}

bool CStore::AddItemWithID(UINT16 wItemID, UINT32 dwNum, EBindType eBindType, UINT8 byQuality, UINT16 fromWhere )
{
    SItemGenInfo oItemGenInfo;
    oItemGenInfo.wItemID = wItemID;
    oItemGenInfo.dwCount = dwNum;
    oItemGenInfo.byQuality = byQuality;
    oItemGenInfo.eBindType = eBindType;
    return AddItem(oItemGenInfo, fromWhere);
}

bool CStore::AddItem(CItem& rItem, INT16 wIndex/* = -1*/, bool bNotify /*= true*/, bool bNew/* = false*/, bool bUpdate/* = true*/, UINT16 fromWhere /*= 0*/)
{
    UINT64 qwInstID = rItem.GetInstID();
    if(_mapID2Slot.find(qwInstID) != _mapID2Slot.end())
        return true;

    if(!CanAddItem(rItem, wIndex))
        return false;

    UINT16 wEmptyIndex = 0;
    if(wIndex == -1)
    {
        //堆叠
        if(rItem.IsStackItem())
        {
            CStackItemPtr pFromItem = ToPtr<CStackItem>(rItem);
            if(NULL == pFromItem)
                return false;
            UINT16 wCount = pFromItem->GetCount();
            TVecSStoreSlot vecStackItem;
            for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
            {
                SStoreSlot& rStoreSlot = it->second;
                if(rStoreSlot.pItem == NULL)
                    continue;
                if(rStoreSlot.pItem->IsStackItem())
                {
                    CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
                    if(pStackItem->CanMerge(*pFromItem))
                        vecStackItem.push_back(it->second);
                }
            }

            if(!vecStackItem.empty())
            {
                sort(vecStackItem.begin(), vecStackItem.end(), 
                        [](const SStoreSlot& left, const SStoreSlot& right)->bool
                        {
                        return left.pItem->GetCount() > right.pItem->GetCount();
                        }
                    );

                for(size_t i = 0; i < vecStackItem.size(); ++i)
                {
                    CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(vecStackItem[i].pItem);
                    UINT16 wIndex = vecStackItem[i].wIndex;
                    if(wCount > pStackItem->GetEmptyCount())
                    {
                        UINT16 wNum = pStackItem->GetEmptyCount();
                        pStackItem->SetOptCount(wNum);
                        wCount -= pStackItem->GetEmptyCount();
                        pStackItem->SetCount(pStackItem->GetMaxNum());
                        Update2DB(wIndex, *pStackItem, eOpUpdate, fromWhere);
                        pStackItem->NotifyCount(*this);
                    }
                    else
                    {
                        pStackItem->SetOptCount(wCount);
                        pStackItem->AddCount(wCount);
                        Update2DB(wIndex, *pStackItem, eOpUpdate, fromWhere);
                        pStackItem->NotifyCount(*this);
                        wCount = 0;
                        break;
                    }
                }
            }

            if(wCount > 0)
            {
                pFromItem->SetCount(wCount);
            }
            else
            {
                return true;
            }
        }

        wEmptyIndex = GetEmptyIndex();
    }
    else
    {
        if(_mapIndex2Item.find(wIndex) != _mapIndex2Item.end())
            return false;
        wEmptyIndex = wIndex;
    }

    //是否过界
    if(wEmptyIndex >= GetCapacity())
        return false;

    SStoreSlot& rStoreSlot = _mapID2Slot[qwInstID];
    rStoreSlot.pItem = ToThisPtr(rItem);
    rStoreSlot.wIndex = wEmptyIndex;
    _mapIndex2Item[wEmptyIndex] = rItem.GetInstID();
    rItem.OnAddToStore(*this, bNotify);
    if (bUpdate || bNotify)
        Update2DB(wEmptyIndex, rItem, eOpAdd, fromWhere);

    if(bNotify)
        ItemAddNotify(rStoreSlot, bNew);
    return true;
}

EItemResult CStore::DestroyItem(UINT64 qwInstID, UINT16 toWhere /*=0*/)
{
    CItemPtr rItem = GetItem(qwInstID);
    //判断是否能丢弃
    if(rItem == NULL || !rItem->GetItemCfg()._SellPrice)
        return eItemErrDrop;
    if(!DelItemByInstID(rItem->GetInstID(), true, true, toWhere))
        return eItemErrOther;

    return eItemSucceed;
}

bool CStore::DelItem(CItem& rItem, UINT16 wCount, bool bNotify/* = true*/, bool bUpdate/* = true*/, UINT16 toWhere /*=0*/)
{
    if (!rItem.IsStackItem() || rItem.GetCount() == wCount)
    {
        // 通知弹框
        string strPkg = g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgUseItem, BuildStrVec(rItem.GetQuality(),rItem.GetItemName(),wCount));
        GetUser().SendPkg(strPkg);
        //XXX udpLog
        TVecUserItemChange vecItemChange;
        SUserItemChange oItemChange(rItem.GetItemID(), -wCount, CItemMgr::GetGoldPrice(rItem.GetItemID()), toWhere);
        vecItemChange.push_back(oItemChange);
        GetUser().SendCenterSvrPkg(g_Game2CenterLog.BuildPkg_LogItemChange(GetUser().GetUserID(), eOpTypeItemChange, vecItemChange));

        return DelItem(rItem, bNotify, bUpdate, toWhere);
    }

    CStackItem& rStackItem = static_cast<CStackItem&>(rItem);
    if (!rStackItem.OnUse(*this, wCount, true, toWhere))
        return false;
    /*
       rStackItem.SetCount(rItem.GetCount() - wCount);
       rStackItem.SetOptCount(wCount);
       Update2DB(rStackItem.GetIndex(), rItem, eOpUpdate, toWhere);
       rStackItem.NotifyCount(*this);
       */
    return true;
}

bool CStore::DelItemByInstID(UINT64 qwInstID, UINT16 wCount, bool bNotify/* = true*/, bool bUpdate/* = true*/, UINT16 toWhere /*=0*/)
{
    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return false;
    SStoreSlot& rStoreSlot = it->second;
    if(rStoreSlot.wIndex > GetCapacity())
        return false;
    if (!rStoreSlot.pItem)
        return false;
    return DelItem(*rStoreSlot.pItem, wCount, bNotify, bUpdate, toWhere);
}

bool CStore::DelItem(CItem& rItem, bool bNotify /*= true*/, bool bUpdate /* = true*/, UINT16 toWhere /*=0*/)
{
    return DelItemByInstID(rItem.GetInstID(), bNotify, bUpdate, toWhere);
}

bool CStore::DelItemByInstID(UINT64 qwInstID, bool bNotify /*= true*/, bool bUpdate /* = true*/, UINT16 toWhere /*=0*/)
{
    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return false;
    SStoreSlot& rStoreSlot = it->second;
    if(rStoreSlot.wIndex > GetCapacity())
        return false;

    CItemPtr rItem = rStoreSlot.pItem;
    if (bUpdate) Update2DB(rStoreSlot.wIndex, *rItem, eOpDel, toWhere); // XXX: 必须要删除数据之前

    _mapIndex2Item.erase(rStoreSlot.wIndex);
    _mapID2Slot.erase(it);
    if(bNotify)
        ItemDelNotify(*rItem);
    return true;
}

bool CStore::DelItemByItemID(UINT16 wItemID, UINT16 wCount/* = 1*/, bool bNotify/* = true*/, UINT16 toWhere/* = 0*/)
{
    /*UINT16 wRemCount = GetItemCount(wItemID);
      if(wRemCount < wCount)
      return false; //不够

      vector<UINT64> vecDelItem;
      auto it = _mapID2Slot.begin();
      for(;it != _mapID2Slot.end() && wCount > 0;it++)
      {
      SStoreSlot& rStoreSlot = it->second;
      if(rStoreSlot.wIndex > GetCapacity())
      continue;
      CItemPtr pItem = rStoreSlot.pItem;

      if(NULL != pItem && pItem->GetItemID() == wItemID)
      {
      if(wCount <= pItem->GetCount())
      {
      pItem->OnUse(*this, wCount, true, toWhere);
      wCount = 0;
      }
      else
      {
      vecDelItem.push_back(pItem->GetInstID());
      wCount -= pItem->GetCount();
      }
      }
      }

      for(auto itItem = vecDelItem.begin(); itItem != vecDelItem.end(); ++itItem)
      DelItem(*itItem,bNotify, true, toWhere);

      return true;*/
    UINT16 bind = 0;
    UINT16 noBind = 0;
    return DelItemWithBindType(wItemID, wCount, eBindUseBindFirst, bind, noBind, bNotify, toWhere);
}

bool CStore::DelItemType(UINT16 wItemID, UINT16 toWhere/* = 0*/)
{
    //vector<UINT64> vecDelItem;
    vector<CItemPtr> vecDelItem;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); it++)
    {
        SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->GetItemID() == wItemID)
            vecDelItem.push_back(rStoreSlot.pItem);
        //vecDelItem.push_back(rStoreSlot.pItem->GetInstID());
    }

    for(auto itItem = vecDelItem.begin(); itItem != vecDelItem.end(); ++itItem)
        //DelItem(*itItem, true, true, toWhere);
        DelItem(**itItem, (*itItem)->GetCount(), true, true, toWhere);

    return true;
}

bool CStore::DelItemWithBindType(UINT16 wItemID, UINT16 wCount, EBindUseType eBindUseType, UINT16& wBindCount, UINT16& wNoBindCount, bool bNotify /* = true */, UINT16 toWhere/* = 0*/)
{
    wBindCount = 0;
    wNoBindCount = 0;
    UINT16 wRemCount = GetItemCount(wItemID, eBindUseType);
    if(wRemCount < wCount)
        return false; //不够

    //vector<UINT64> vecDelItem;
    vector<CItemPtr> vecDelItem;
    //  扣除优先类型的物品
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end() && wCount > 0; ++it)
    {
        SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.wIndex > GetCapacity())
            continue;
        CItemPtr pItem = rStoreSlot.pItem;

        if(NULL != pItem && pItem->GetItemID() == wItemID)
        {
            if ( 
                    (rStoreSlot.pItem->IsBind() && (eBindUseType == eBindUseBindFirst || eBindUseType == eBindUseBind)) // 绑定
                    ||
                    (!rStoreSlot.pItem->IsBind() && (eBindUseType == eBindUseNoneFirst || eBindUseType == eBindUseNone)) //物品非绑定
               )
            {
                if(wCount < pItem->GetCount())
                {
                    if (rStoreSlot.pItem->IsBind())
                        wBindCount += wCount;
                    else
                        wNoBindCount += wCount;
                    pItem->OnUse(*this, wCount, true, toWhere);
                    wCount = 0;
                }
                else
                {
                    if (rStoreSlot.pItem->IsBind())
                        wBindCount += pItem->GetCount();
                    else
                        wNoBindCount += pItem->GetCount();
                    //vecDelItem.push_back(pItem->GetInstID());
                    vecDelItem.push_back(pItem);
                    wCount -= pItem->GetCount();
                }
            }
        }
    }

    // 优先类型已经用光，需要扣除第二绑定类型的物品
    if (wCount > 0)
    {
        for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end() && wCount > 0; ++it)
        {
            SStoreSlot& rStoreSlot = it->second;
            if(rStoreSlot.wIndex > GetCapacity())
                continue;
            CItemPtr pItem = rStoreSlot.pItem;

            if(NULL != pItem && pItem->GetItemID() == wItemID)
            {
                if ((!rStoreSlot.pItem->IsBind() && 
                            (eBindUseType == eBindUseBindFirst))
                        ||
                        (rStoreSlot.pItem->IsBind() && 
                         (eBindUseType == eBindUseNoneFirst)))
                {
                    if(wCount < pItem->GetCount())
                    {
                        if (rStoreSlot.pItem->IsBind())
                            wBindCount += wCount;
                        else
                            wNoBindCount += wCount;
                        pItem->OnUse(*this, wCount, true, toWhere);
                        wCount = 0;
                    }
                    else
                    {
                        //vecDelItem.push_back(pItem->GetInstID());
                        vecDelItem.push_back(pItem);
                        if (rStoreSlot.pItem->IsBind())
                            wBindCount += pItem->GetCount();
                        else
                            wNoBindCount += pItem->GetCount();
                        wCount -= pItem->GetCount();
                    }
                }
            }
        }
    }

    for(auto itItem = vecDelItem.begin(); itItem != vecDelItem.end(); ++itItem)
        //DelItem(*itItem, true, true, toWhere);
        DelItem(**itItem, (*itItem)->GetCount(), true, true, toWhere);

    return true;
}

bool CStore::DelItemFromSlots(UINT16 wCount, TVecSStoreSlot& vecStore, UINT16 toWhere/* = 0*/)
{
    if (!wCount)
        return false;

    size_t size = vecStore.size();
    if (!size)
        return false;

    CItemPtr pItem = NULL;
    UINT16 wCnt = wCount;
    for (size_t i = 0; i < size && wCnt; ++i)
    {
        pItem = vecStore[i].pItem;
        if (!pItem)
            continue;

        UINT16 wyaCnt = pItem->GetCount();
        if (pItem->IsStackItem() && wyaCnt > wCnt)
        {
            CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(pItem);
            pStackItem->OnUse(*this, wCnt, true, toWhere);
            /*
               pStackItem->SetCount(wyaCnt - wCnt);
               pStackItem->SetOptCount(wCnt);
               Update2DB(vecStore[i].wIndex, *pStackItem, eOpUpdate, toWhere);
               pStackItem->NotifyCount(*this);
               */
            return true;
        }

        wCnt -= wyaCnt;
        //DelItem(*pItem, true, true, toWhere);
        DelItem(*pItem, wyaCnt, true, true, toWhere);
    }

    return !wCnt;
}

void CStore::DelItemFromList(const vector<SIdxCount>& rVecList, UINT16 toWhere/* = 0*/)
{
    auto it = rVecList.begin();
    for(;it != rVecList.end();it++)
    {
        UINT16 wItemID = (UINT16)it->dwIdx;
        if(eItemTask == CItem::GetItemType(wItemID))
            DelItemType(wItemID);
        else
            DelItemByItemID(wItemID, it->wCount, true, toWhere);
    }
}

void CStore::DelItemFromList(const vector<SCollectItem>& rVecList, UINT16 toWhere/* = 0*/)
{
    for(auto& rCollectItem : rVecList)
    {
        UINT16 wItemID = rCollectItem.wItemID;
        UINT16 wCount = rCollectItem.wCount;
        if(eItemTask == CItem::GetItemType(wItemID))
            DelItemType(wItemID);
        else
            DelItemByItemID(wItemID, wCount, true, toWhere);
    }
}

void CStore::DelGatherItemFromList(const vector<SIdxCount>& rVecList)
{
    auto it = rVecList.begin();
    for(;it != rVecList.end();it++)
    {
#if 0 
        SGatherCFG* pGatherCFG = CGatherMgr::GetGatherConfig(it->dwIdx);
        if(pGatherCFG != NULL && eGT_SubTask == IGather::GetSubType(*pGatherCFG))
            DelItemType((UINT16)pGatherCFG->_Award);
#endif
    }
}

bool CStore::OnUseItem(CPlayer& rPlayer, CItem& rItem, UINT16 wCount)
{
    // TODO:
#if 0
    CScriptPtr pScript = rItem.GetScript();
    if(pScript != NULL && rItem.GetItemInfo().bHasOnUseItem)
    {
        INT32 dwRet = 0;
        if(pScript->Call("OnUseItem", dwRet, SLuaUInt64(rPlayer.GetRoleID()), rItem.GetItemID()))
        {
            if(dwRet != 0)
            {
                LOG_CRI << "OnUseItem error! ItemID: " << rItem.GetItemID() << " return value: " << dwRet;
                return false;
            }
        }
        else
        {
            LOG_CRI << "Call fails! ItemID: " << rItem.GetItemID();
            //return false;
        }
    }
#endif
    if(rItem.OnUse(*this, wCount, false, NLogDataDefine::ItemTo_UseItem))
        return true;

    return false;
}

EItemResult CStore::RelocateItem(UINT64 qwInstID, INT16 wNewIndex)
{
    auto itInst = _mapID2Slot.find(qwInstID);
    if(itInst == _mapID2Slot.end())
        return eItemNotExist;

    SStoreSlot& rStoreSlot = itInst->second;
    INT16 wIndex = rStoreSlot.wIndex;
    if((UINT16)wNewIndex >= GetCapacity())
        return eItemStoreErr;

    ItemDelNotify(*rStoreSlot.pItem);
    auto itIndex = _mapIndex2Item.find(wNewIndex);
    if(itIndex != _mapIndex2Item.end())
    {
        UINT64 qwOtherInstID = itIndex->second;
        auto itOther = _mapID2Slot.find(qwOtherInstID);
        if(itOther == _mapID2Slot.end())
            return eItemStoreErr;

        SStoreSlot& rOtherStoreSlot = itOther->second;
        rOtherStoreSlot.wIndex = wIndex;
        _mapIndex2Item[wIndex] = qwOtherInstID;

        Update2DB(wIndex, *rOtherStoreSlot.pItem, eOpUpdate);
        ItemDelNotify(*rOtherStoreSlot.pItem);
        ItemAddNotify(rOtherStoreSlot, false);
    }
    else
    {
        _mapIndex2Item.erase(wIndex);
    }

    rStoreSlot.wIndex = wNewIndex;
    Update2DB(wNewIndex, *rStoreSlot.pItem, eOpUpdate);
    ItemAddNotify(rStoreSlot, false);
    _mapIndex2Item[wNewIndex] = qwInstID;
    return eItemSucceed;
}

bool CStore::Tidyup()
{
    multimap<CItemPtr, SStoreSlot*> mapItem2Slot;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        SStoreSlot& rStoreSlot = it->second;
        mapItem2Slot.insert(make_pair(rStoreSlot.pItem, &rStoreSlot));
    }

    CStackItemPtr pPrevStackItem = NULL;
    for(auto it = mapItem2Slot.begin(), itCur = mapItem2Slot.end(); it != mapItem2Slot.end();)
    {
        itCur = it;
        CItemPtr pItem = it->first;
        ++it;
        if(!pItem->IsStackItem())
            continue;
        CStackItemPtr pCurStackItem = dynamic_pointer_cast<CStackItem>(pItem);
        if(pCurStackItem == NULL)
            LOG_CRI << "StackItem Type Error! ItemID: " << pItem->GetItemID();
        else if(pPrevStackItem != NULL && pPrevStackItem->CanMerge(*pCurStackItem) && MergeStackItem(*pCurStackItem, *pPrevStackItem))
            mapItem2Slot.erase(itCur);
        else
            pPrevStackItem = pCurStackItem;
    }

    INT16 wIndex = 0;
    _mapIndex2Item.clear();

    for(auto it = mapItem2Slot.begin(); it != mapItem2Slot.end(); ++it)
    {
        CItemPtr pItem = it->first;
        SStoreSlot* pStoreSlot = it->second;
        UINT64 qwInstID = pItem->GetInstID();
        _mapIndex2Item.insert(make_pair(wIndex, qwInstID));
        pStoreSlot->wIndex = wIndex++;
        Update2DB(pStoreSlot->wIndex, *pStoreSlot->pItem, eOpUpdate);
    }
    return StoreItemNotify();
}

EItemResult CStore::SplitStackItem(UINT64 qwInstID, UINT16 wStackCount, INT16 wIndex)
{
    if(0 == wStackCount)
        return eItemErrOther;

    if(IsStoreFull())
        return eItemStoreFull;
    if(-1 == wIndex)
        wIndex = GetEmptyIndex();

    if(GetInstByIndex(wIndex) != 0)
        return eItemErrOper;

    auto it = _mapID2Slot.find(qwInstID);
    if(it == _mapID2Slot.end())
        return eItemNotExist;

    SStoreSlot& rStoreSlot = it->second;
    if(rStoreSlot.pItem == NULL)
        return eItemNotExist;

    if(!rStoreSlot.pItem->IsStackItem())
        return eItemNoStack;

    CStackItemPtr pStackItem = dynamic_pointer_cast<CStackItem>(rStoreSlot.pItem);
    if(pStackItem == NULL || !pStackItem->IsStackItem())
        return eItemNoStack;

    if(pStackItem->GetCount() <= wStackCount)
        return eItemErrOther;

    UINT16 wRemCount = pStackItem->GetCount() - wStackCount;
    pStackItem->SetCount(wRemCount);
    Update2DB(rStoreSlot.wIndex, *pStackItem, eOpUpdate);
    pStackItem->NotifyCount(*this);

    CItemPtr pNewItem = CItemMgr::CreateItem(pStackItem->GetItemID(), wStackCount, pStackItem->GetQuality());
    if(pNewItem == NULL)
        return eItemErrOther;

    pNewItem->SetBindType(GetStoreType(), pStackItem->GetBindType());
    pNewItem->SetExpiration(pStackItem->GetExpireTime(), pStackItem->IsExpired());
    AddItem(*pNewItem, wIndex, true, false, true, NLogDataDefine::ItemFrom_UserDeptORPack);
    return eItemSucceed;
}

bool CStore::MergeStackItem(CStackItem& rFromStackItem, CStackItem& rToStackItem, INT16* wFromIndex, INT16* wToIndex)
{
    bool bMerged = false;
    bool bBind = false;
    if(rFromStackItem.IsBind() || rToStackItem.IsBind())
        bBind = true;

    UINT16 wTotalCount = rFromStackItem.GetCount() + rToStackItem.GetCount();
    if(wTotalCount > rToStackItem.GetMaxNum())
    {
        rToStackItem.SetCount(rToStackItem.GetMaxNum());
        UINT16 wRemCount = wTotalCount - rToStackItem.GetMaxNum();
        rFromStackItem.SetCount(wRemCount);
        if (wFromIndex && wToIndex)
        {
            Update2DB(*wFromIndex, rFromStackItem, eOpUpdate);
            Update2DB(*wToIndex, rToStackItem, eOpUpdate);
        }
        rFromStackItem.NotifyCount(*this);
    }
    else
    {
        rToStackItem.SetCount(wTotalCount);
        DelItem(rFromStackItem, true, true, NLogDataDefine::ItemTo_UserDeptORPack);
        bMerged = true;

        if (wFromIndex && wToIndex)
            Update2DB(*wToIndex, rToStackItem, eOpUpdate);
    }

    if(bBind && !rToStackItem.IsBind())
        rToStackItem.SetBindType(GetStoreType(), eBindGet, GetUserPtr());
    rToStackItem.NotifyCount(*this);
    return bMerged;
}

EItemResult CStore::MergeStackItem(UINT64 qwFromInstID, UINT64 qwToInstID)
{
    INT16 wFromIndex = 0;
    CItemPtr pFromItem = GetItem(qwFromInstID, &wFromIndex);
    INT16 wToIndex = 0;
    CItemPtr pToItem = GetItem(qwToInstID, &wToIndex);
    if(pFromItem == NULL || pToItem == NULL)
        return eItemNotExist;

    if(!pFromItem->IsStackItem() || !pToItem->IsStackItem())
        return eItemNoStack;

    CStackItemPtr pFromStackItem = dynamic_pointer_cast<CStackItem>(pFromItem);
    CStackItemPtr pToStackItem = dynamic_pointer_cast<CStackItem>(pToItem);
    if(pFromStackItem == NULL || pToStackItem == NULL)
        return eItemNoStack;

    if(!pFromStackItem->CanMerge(*pToStackItem, false))
        return RelocateItem(qwFromInstID, wToIndex);

    MergeStackItem(*pFromStackItem, *pToStackItem, &wFromIndex, &wToIndex);
    return eItemSucceed;
}

void CStore::GetAllItemList(vector<CItemPtr>& rvecItem) const
{
    for(auto& p : _mapID2Slot)
    {
        CItemPtr pItem = p.second.pItem;
        rvecItem.push_back(pItem);
    }
}

void CStore::GetItemList(TVecItem& rVecStoreItem) const
{
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        rVecStoreItem.push_back(rStoreSlot.pItem->ToProt());
    }
}

void CStore::GetItemList(TVecItem& rVecStoreItem)
{
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        SStoreSlot& rStoreSlot = it->second;
        rVecStoreItem.push_back(rStoreSlot.pItem->ToProt());
    }
}

void CStore::GetItemList(UINT16 wItemID, vector<CItemPtr>& rVecItem)
{
    for(auto& p : _mapID2Slot)
    {
        CItemPtr& pItem = p.second.pItem;
        if(pItem->GetItemID() == wItemID)
            rVecItem.push_back(pItem);
    }
}

UINT16 CStore::GetItemList(UINT16 wItemID, TVecSStoreSlot& rVecStoreSlot, UINT16 wCount, EBindUseType eBind)
{
    UINT16 wCnt = 0;
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        SStoreSlot& rStoreSlot = it->second;
        if(rStoreSlot.pItem->GetItemID() == wItemID)
        {
            bool bAccepted = false;
            if ((eBind == eBindUseNone && !rStoreSlot.pItem->IsBind()) || (eBind == eBindUseBind && rStoreSlot.pItem->IsBind()))
            {
                rVecStoreSlot.push_back(rStoreSlot);
                bAccepted = true;
            }

            if (eBind == eBindUseNoneFirst || eBind == eBindUseBindFirst)
            {
                bAccepted = true;
                if ((eBind == eBindUseNoneFirst && rStoreSlot.pItem->IsBind()) || (eBind == eBindUseBindFirst && !rStoreSlot.pItem->IsBind()))
                    rVecStoreSlot.insert(rVecStoreSlot.begin(), rStoreSlot);
                else
                    rVecStoreSlot.push_back(rStoreSlot);
            }

            if (bAccepted)
            {
                if(rStoreSlot.pItem->IsStackItem())
                    wCnt += rStoreSlot.pItem->GetCount();
                else
                    ++wCnt;
            }

            if (wCount && wCnt >= wCount)
                return wCnt;
        }
    }
    return wCnt;
}

EItemResult CStore::CanUseItem(CCreature& rCreature, CItem& rItem, UINT16 wCount)
{
    if(rItem.IsExpired())
        return eItemExpired;

    if(!rItem.CanUse(wCount))
    {
        rCreature.SendPkg(g_ChatProtS.BuildPkg_SystemFormatMsgIDNotify(eMsgItemCantUseErr, BuildStrVec(rItem.GetItemName())));
        return eItemErrUse;
    }

    const SItemCFG& rItemCfg = rItem.GetItemCfg();
    if (!rItemCfg._Useable)
        return eItemErrUse; 

    if(rCreature.GetLevel() < rItem.GetLevel())
        return eItemErrLevel;

    UINT8 byLimitJob = rItemCfg._Job;
    if(0 != byLimitJob && rCreature.GetJob() != byLimitJob)
        return eItemErrJob;

    return eItemSucceed;
}

// XXX: eBind: 0-非绑定 1-绑定 2-优先使用非绑定 3-优先使用绑定 
EItemResult CStore::CanUseItem(CCreature& rCreature, UINT16 wItemID, UINT16 wCount, EBindUseType eBind, TVecSStoreSlot& rVecStoreSlot)
{
    UINT16 wCnt = GetItemList(wItemID, rVecStoreSlot, wCount, eBind);
    if (wCount && wCnt >= wCount)
        return eItemSucceed;
    if (!wCnt)
        return eItemNotEnougth;

    size_t size = rVecStoreSlot.size();
    for (size_t i = 0; i < size; ++i)
    {
        if (rVecStoreSlot[i].pItem->IsExpired())
            return eItemExpired;
    }

    CItem& rItem = *rVecStoreSlot[0].pItem;
    const SItemCFG& rItemCfg = rItem.GetItemCfg();
    if (!rItemCfg._Useable)
        return eItemErrUse; 

    if(rCreature.GetLevel() < rItem.GetLevel())
        return eItemErrLevel;

    UINT8 byLimitJob = rItemCfg._Job;
    if(0 != byLimitJob && rCreature.GetJob() != byLimitJob)
        return eItemErrJob;

    return eItemNotEnougth;
}

EItemResult CStore::Expand(UINT16 wCount)
{
    CPlayerPtr pPlayer = GetUser().GetPlayer();
    switch(GetStoreType())
    {
        case eStorePack:
            //包裹是否已最大
            if(GetCapacity() >= SParamConfig::wPackMaxCount)
                return eItemNotNeed;
            if(wCount == 0)
                return eItemErrOther;

            AddCapacity(wCount);
            if(GetCapacity() > SParamConfig::wPackMaxCount)
                SetCapacity(SParamConfig::wPackMaxCount);
            pPlayer->SetPackCapacity(GetCapacity());
            pPlayer->CalcPackNextUnlockTime(*this);
            break;
        case eStoreDepot:
            //仓库是否已最大
            if(GetCapacity() > SParamConfig::wDepotMaxCount)
                return eItemNotNeed;
            if(wCount == 0)
                return eItemErrOther;

            AddCapacity(wCount);
            if(GetCapacity() > SParamConfig::wDepotMaxCount)
                SetCapacity(SParamConfig::wDepotMaxCount);
            pPlayer->SetDepotCapacity(GetCapacity());
            break;
        case eStorePlayerCitta:
            AddCapacity(wCount);
            break;
        case eStorePlayerTrump:
            AddCapacity(wCount);
            if (GetCapacity() > TRUMP_SLOTS_COUNT)
                SetCapacity(TRUMP_SLOTS_COUNT);
            break;
        default:
            return eItemErrOther;
    }

    // XXX: 更新到tblslotsdata
    string strData;
    COutArchive iar(strData);
    SRoleSlotsInfo sRoleSlotsInfo;
    sRoleSlotsInfo.qwRoleID = GetUser().GetUserID();

    sRoleSlotsInfo.eStoreType = GetStoreType();
    switch (GetStoreType())
    {
        case eStorePlayerCitta:
            if (pPlayer)
                sRoleSlotsInfo.qwOwnerID = pPlayer->GetMainFighter()->GetInstID();
            sRoleSlotsInfo.wMaxSlot = CITTA_SLOT_COUNT;
            break;
        case eStorePlayerTrump:
            sRoleSlotsInfo.wMaxSlot = TRUMP_SLOTS_COUNT;
            break;
        default:
            sRoleSlotsInfo.qwOwnerID = GetUser().GetUserID();
            sRoleSlotsInfo.wMaxSlot = GetCapacity();
            break;
    }

    sRoleSlotsInfo.wMaxAvaliableSlot = GetCapacity();
    iar << sRoleSlotsInfo;
    g_Game2DBCommC.Send_RoleDataUpdate(GetUser().GetUserID(), eTypeSlotsInfo, eOpUpdate, strData);

    CapacityNotify();
    return eItemSucceed;
}

bool CStore::CapacityNotify()
{
    return GetUser().SendPkg(g_ItemProtS.BuildPkg_StoreSizeChangeNotify(GetStoreType(), GetCapacity()));
}

bool CStore::ToStream(SStoreStream& rStream) const
{
    rStream.wCapacity = GetCapacity();
    //LOG_DBG << "wCapacity = " << GetCapacity() << ".";
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end(); ++it)
    {
        const SStoreSlot& rStoreSlot = it->second;
        const CItem& rItem = *rStoreSlot.pItem;
        rStream.vecItem.push_back(rItem.ToProt());
    }
    return true;
}

void CStore::MergeResource(TVecResource& vecRes)
{
    TVecResource TepvecRes;
    TepvecRes.swap(vecRes);
    for (auto it = TepvecRes.begin();it != TepvecRes.end();it++)
    {
        SResource &rSource = *(it);
        bool bFind =false;
        for (size_t i = 0;i < vecRes.size();i++)
        {
            SResource &rDestSource = vecRes[i];

            if (rSource._eRes == rDestSource._eRes)
            {
                rDestSource._dwValue += rSource._dwValue;
                bFind = true;
                break;
            }
        }
        if(!bFind)
        {
            vecRes.push_back(rSource);
        }
    }
}

void CStore::AddResource(CUser& rUser, TVecResource& vecRes, UINT16 fromWhere,CPlayerPtr pPlayer/* = NULL*/, bool bNotify)
{
    if(vecRes.empty())
        return;

    if(NULL == pPlayer)
        pPlayer = rUser.GetPlayer();

    //UINT32 dwOPID = LogOPID;
    //NGame2CenterLog::TVecUserMoneyChange oMoneyChange;
    for(auto it_res = vecRes.begin();it_res != vecRes.end();it_res++)
    {
        switch(it_res->_eRes)
        {
            /*case EMONEY_ACTION: //药剂增加体力不检测上限
              {
              rUser.AddAction(it_res->_dwValue);
              }
              break;
              */   
            case EMONEY_GIFTCOIN:       //金券
                // TODO:
                break;
            case EMONEY_EXP:		    //经验
                {
                    if(pPlayer != NULL)
                    {
                        pPlayer->AddExp(it_res->_dwValue, bNotify);
                    }
                }
                break;
            case EMONEY_GUILDCONTRIB:	//帮派贡献
                {
                    // TODO:
                    g_Game2CenterCommC.Send_AddGuildContribution(rUser.GetUserID(), it_res->_dwValue);
                }
                break;
            default:
                rUser.AddMoney(it_res->_eRes,it_res->_dwValue,fromWhere,bNotify);
                break;
        }
    }
    //if(!oMoneyChange.empty())
    //	g_Game2CenterLog.Send_LogMoneyChange(rUser.GetUserID(), NGame2CenterLog::eOpTypeGiftBox, dwOPID, oMoneyChange);
}

bool CStore::CanSubResource(CUser& rUser, TVecResource& vecRes, CPlayerPtr pPlayer /*=NULL*/)
{
    if(NULL == pPlayer)
        pPlayer = rUser.GetPlayer();

    //UINT32 dwOPID = LogOPID;
    //NGame2CenterLog::TVecUserMoneyChange oMoneyChange;
    for(auto it_res = vecRes.begin();it_res != vecRes.end();it_res++)
    {
        switch(it_res->_eRes)
        {
            case EMONEY_GIFTCOIN:       //金券
                // TODO:
                break;
            case EMONEY_EXP:		    //经验
                // TODO:
                break;
            case EMONEY_ACTION: //先扣bufer体力
                if(!rUser.CanSubAction(it_res->_dwValue))
                {
                    return false;
                }
                break;
            case EMONEY_GUILDCONTRIB:	//帮派贡献
                // TODO:
                break;
            default:
                if(!rUser.CanSubMoney(it_res->_eRes,it_res->_dwValue))
                {
                    return false;
                }
                break;
        }
    }
    return true;

}

bool CStore::SubResource(CUser& rUser, TVecResource& vecRes,UINT16 fromWhere, CPlayerPtr pPlayer /*=NULL*/, bool bNotify/* = true*/)
{
    if(!CanSubResource(rUser,vecRes,pPlayer))
    {
        return false;
    }

    if(NULL == pPlayer)
        pPlayer = rUser.GetPlayer();

    //UINT32 dwOPID = LogOPID;
    //NGame2CenterLog::TVecUserMoneyChange oMoneyChange;
    for(auto it_res = vecRes.begin();it_res != vecRes.end();it_res++)
    {
        switch(it_res->_eRes)
        {
            case EMONEY_ACTION://检查buffer体力和实际体力之和
                {
                    rUser.SubAction(it_res->_dwValue);
                }
                break;
            case EMONEY_GIFTCOIN:       //金券
                //TODO
                break;
            case EMONEY_EXP:		    //经验
                //TODO
                break;
            case EMONEY_GUILDCONTRIB:	//帮派贡献
                // TODO:
                break;
            default:
                rUser.SubMoney(it_res->_eRes,it_res->_dwValue,(NLogDataDefine::ItemTo)fromWhere,bNotify);
                break;
        }
    }
    return true;
    //if(!oMoneyChange.empty())
    //	g_Game2CenterLog.Send_LogMoneyChange(rUser.GetUserID(), NGame2CenterLog::eOpTypeGiftBox, dwOPID, oMoneyChange);

}

void CStore::TimerCheck(time_t tNow)
{
    for(auto it = _mapID2Slot.begin(); it != _mapID2Slot.end();)
    {
        SStoreSlot& rStoreSlot = it->second;
        ++it;
        CItemPtr pItem = rStoreSlot.pItem;
        pItem->TimerCheck(tNow, *this);
    }
}

// XXX: 必须放在修改数据之后和通知客户端之前
void CStore::Update2DB(UINT16 wIndex, CItem& rItem, EDataChange eDataChange, UINT16 fromWhere/* = 0*/)
{
    CItem::Update2DB(rItem, GetUser().GetUserID(), GetUser().GetUserID(), GetStoreType(), wIndex, eDataChange);

    if(fromWhere > 0)
    {
        UINT16 num = 0;
        if(rItem.IsStackItem())
            num = rItem.GetOptCount();
        else
            num = rItem.GetCount();
        if(0 == num)
            return;

        NLogDataDefine::SItemCoursesLogPtr ptrLog(new NLogDataDefine::SItemCoursesLog());
        if(NULL == ptrLog)
            return;
        NLogDataDefine::SItemCoursesLog& rLog = *ptrLog;
        rLog.serverId = Config._wGroup;
        rLog.playerId = GetUser().GetUserID();
        rLog.strOpenId = GetUser().GetPlayer()->GetOpenId();
        rLog.qwInstId = rItem.GetInstID();
        rLog.itemId   = rItem.GetItemID();
        rLog.itemNum  = num;
        rLog.fromto   = fromWhere;
        if (fromWhere >= 5000)
            rLog.fromtoStr = NLogDataDefine::GetDescription(NLogDataDefine::ItemTo(fromWhere));
        else
            rLog.fromtoStr = NLogDataDefine::GetDescription(NLogDataDefine::ItemFrom(fromWhere));
        rLog.happenedTime = time(NULL);
        CGameServerLog::LogToDB(ptrLog);
    }
}

void CStore::PrintResInfo(const TVecResource& vecRes)
{
    for(size_t i = 0 ;i != vecRes.size();i++)
    {
        const SResource &rRes = vecRes[i];
        LOG_INF << NProtoCommon::GetDescription(rRes._eRes) <<": Is " <<rRes._dwValue;
    }
}

bool  CStore::AddItemByLootID(UINT32 dwLootId,UINT16 fromWhere,bool bIsAppend,TVecItemGenInfo* pvecItems ,TVecResource* pvecRes )
{
    TVecItemGenInfo vecItems;
    TVecResource vecRes;
    LOOT.Roll(dwLootId, vecItems,vecRes);
    if(!vecItems.empty())
    {
        if(!CanAddItem(vecItems))
        {
            return false;
        }
        else
        {
            if(!bIsAppend)
            {
                AddItem(vecItems,fromWhere);
            }
            else
            {
                AddItem(vecItems,fromWhere,true,false);
            }
        }
    }

    if( NULL != pvecItems)
    {
        for(auto iter =vecItems.begin();iter != vecItems.end();iter++)
        {
            pvecItems->push_back(*iter);
        }
    }
    if(!vecRes.empty()&&!bIsAppend)
    {
        CStore::AddResource(GetUser(),vecRes,fromWhere);
    }
    if(NULL != pvecRes)
    {
        for(auto iter =vecRes.begin();iter != vecRes.end();iter++)
        {
            pvecRes->push_back(*iter);
        }

    }
    return true;
}

void CStore::BeginUseItem(UINT16 wItemId)
{
    _wUseItem = wItemId;
    _vecUseItemRes.clear();
    _vecUseItemItems.clear();

}

void CStore::EndUseItem(UINT32 dwNum)
{
    if(dwNum != 0 &&(!_vecUseItemRes.empty() || !_vecUseItemItems.empty()))
    {
        GetUser().SendPkg(g_ItemProtS.BuildPkg_NoticeUseItemNotify(_wUseItem,dwNum,_vecUseItemRes,_vecUseItemItems));
        UINT32 dwFenBaoYan = 0;
        if(_wUseItem == 190)
        {
            for(auto it = _vecUseItemItems.begin(); it != _vecUseItemItems.end();it++)
            {
                SItemGenInfo &rItem = *it;
                if(rItem.wItemID == 1132)
                {
                    dwFenBaoYan = rItem.dwCount;
                    break;
                }
            }
        }
        if(dwFenBaoYan > 0)
        {
            CPlayerPtr pPlayer = GetUser().GetPlayer();
            SItemInfo* pItemInfo = CItemMgr::GetItemConfig(1132);
            if (pPlayer && pItemInfo)
            {
                TVecString vecstring;
                vecstring.push_back(NumberToString(pPlayer->GetColor()));
                vecstring.push_back(pPlayer->GetName());
                vecstring.push_back(NumberToString(pItemInfo->oItemCfg._Quality));
                vecstring.push_back(pItemInfo->oItemCfg._Name);
                vecstring.push_back(NumberToString(dwFenBaoYan));
                g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMSgTrumpBuyAlert, vecstring);
            }

        }

    }
    _wUseItem = 0;
}

bool CStore::IsInUseItem()
{
    return _wUseItem != 0;
}

UINT32 CStore::ToSize()
{
    UINT32 dwSize = 0;
    LOG_INF<<"CStore:"<<sizeof(*this);
    dwSize += sizeof(*this);
    dwSize += _vecUseItemRes.capacity()*sizeof(SResource);
    dwSize += _vecUseItemItems.capacity()*sizeof(SItemGenInfo);

    dwSize += _mapID2Slot.size()*sizeof(SStoreSlot);
    
    UINT32 dwItemSize = 0;
    for(auto& p : _mapID2Slot)
    {
        CItemPtr pItem = p.second.pItem;
        if(pItem)
        {
            dwItemSize += pItem->ToSize();
        }
    }

    LOG_INF<<"itemcount:"<<_mapID2Slot.size()<<"item total size:"<<dwItemSize;

    dwSize += dwItemSize;

    dwSize += _mapIndex2Item.size()*sizeof(UINT64);
   
    return dwSize;
}

