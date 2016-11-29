#include "stdafx.h"
#include "Pack.h"
#include "Protocols.h"
#include "User.h"
#include "Player.h"
#include "ItemMgr.h"
#include "CittaMgr.h"
#include "GameServerSysMail.h"
#include "EquipTrumpProt.h"
#include "Loot.h"
#include "EquipTrumpMgr.h"
#include "EquipTrump.h"
#include "Item.h"
#include "FeedBackMgr.h"

CPack::CPack(CUser& rUser, UINT16 wInitCount) : CStore(wInitCount), _rUser(rUser) 
{ 
}

CPack::~CPack()
{
}

EItemResult CPack::UseItem(UINT64 qwInstID, UINT16 wCount, UINT64 qwMercenID/* = 0*/, CUser* pOther/* = NULL*/)
{
    if (!qwInstID)
        return eItemErrUse;
    if (!wCount)
        wCount = 1;
    CItemPtr pItem = GetItem(qwInstID);
    if(pItem == NULL)
        return eItemNotExist;

    if (wCount > pItem->GetCount())
        return UseItem(qwInstID, pItem->GetItemID(), wCount, pItem->IsBind(), qwMercenID, pOther);

    return UseItem(*pItem, wCount, qwMercenID, pOther);
}

EItemResult CPack::UseItem(CItem& rItem, UINT16 wCount, UINT64 qwMercenID/* = 0*/, CUser* pOther/* = NULL*/)
{
    if (!wCount)
        wCount = 1;
    //判断类型
    CCreaturePtr pCreature = _rUser.GetPlayer();
    if(NULL == pCreature)
        return eItemErrUse;

    EItemResult eItemResult = CanUseItem(*pCreature, rItem, wCount);
    if(eItemResult != eItemSucceed)
        return eItemResult;

    eItemResult = eItemErrUse;
    BeginUseItem(rItem.GetItemID());
    UINT16 wUsed = SCRIPT.ItemUseNormal(GetUser(), rItem, wCount, qwMercenID, pOther);
    EndUseItem(wUsed);
    if (wUsed)
        eItemResult = eItemSucceed;

    if (eItemSucceed == eItemResult)
    {
        // XXX: 在OnUse之后可能会把CItem对象删除，所以如果要对CItem对象继续操作最好在OnUse之前完成
        if (!rItem.OnUse(*this, wUsed, true, NLogDataDefine::ItemTo_UseItem))
            LOG_CRI << "OnUse Error=> UserID: " << GetUser().GetUserID() << "InstID: "
                << rItem.GetInstID() << " ItemID: " << rItem.GetItemID();
    }
    return eItemResult;
}

EItemResult CPack::UseItem(UINT64 qwInstID, UINT16 wItemID, UINT16 wCount, bool bBind, UINT64 qwMercenID, CUser* pOther)
{
    if (!wCount)
        wCount = 1;
    CCreaturePtr pCreature = _rUser.GetPlayer();
    if(NULL == pCreature)
        return eItemErrUse;

    TVecSStoreSlot oVecStoreSlot;
    //EItemResult eItemResult = CanUseItem(*pCreature, wItemID, 0/*ALL*/, (EBindUseType)bBind, oVecStoreSlot);  //TODO 谁这样写的，为啥是0/*ALL*/？
    EItemResult eItemResult = CanUseItem(*pCreature, wItemID, wCount, (EBindUseType)bBind, oVecStoreSlot);
    if(eItemResult != eItemSucceed)
        return eItemResult;

    size_t szItems = oVecStoreSlot.size();
    if (qwInstID)
    {
        for (auto i = oVecStoreSlot.begin(); i != oVecStoreSlot.end(); ++i)
        {
            if (qwInstID == i->pItem->GetInstID())
            {
                SStoreSlot t = *i;
                oVecStoreSlot.erase(i);
                oVecStoreSlot.insert(oVecStoreSlot.begin(), t);
                break;
            }
        }
    }

    eItemResult = eItemErrUse;
    BeginUseItem(wItemID);
    UINT16 wUsed = SCRIPT.ItemUseNormal(GetUser(), wItemID, wCount, bBind, qwMercenID, pOther);
    EndUseItem(wUsed);
    if (wUsed)
    {
        eItemResult = eItemSucceed;

        for (size_t i = 0; i < szItems; ++i)
        {
            UINT16 wYaCount = oVecStoreSlot[i].pItem->GetCount();
            if (wYaCount <= wUsed)
            {
                if (oVecStoreSlot[i].pItem->OnUse(*this, wYaCount, true, NLogDataDefine::ItemTo_UseItem))
                {
                    wUsed -= wYaCount;
                }
                else
                {
                    LOG_CRI << "OnUse Error=> UserID: " << GetUser().GetUserID() << "InstID: "
                        << oVecStoreSlot[i].pItem->GetInstID() << " ItemID: " << oVecStoreSlot[i].pItem->GetItemID();
                    return eItemErrUse;
                }
            }
            else
            {
                if (oVecStoreSlot[i].pItem->OnUse(*this, wUsed, true, NLogDataDefine::ItemTo_UseItem))
                {
                    wUsed = 0;
                }
                else
                {
                    LOG_CRI << "OnUse Error=> UserID: " << GetUser().GetUserID() << "InstID: "
                        << oVecStoreSlot[i].pItem->GetInstID() << " ItemID: " << oVecStoreSlot[i].pItem->GetItemID();
                    return eItemErrUse;
                }
            }

            if (!wUsed)
                break;
        }
    }

    return eItemResult;
}

EItemResult CPack::SellItem(const TVecUINT64& vecInstID)
{
    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(NULL == pPlayer)
        return eItemErrOther;
    //UINT32 dwOPID = LogOPID;
    for(size_t i = 0 ;i < vecInstID.size(); ++i)
    {
        CItemPtr pItem = GetItem(vecInstID[i]);
        if(pItem == NULL)
            return eItemNotExist;
        else if(pItem->GetSellPrice() == 0)
            return eItemErrSell;

        _rUser.AddMoney(EMONEY_SILVER,pItem->GetSellPrice()*pItem->GetCount(),NLogDataDefine::ItemFrom_SellItem);
        //MoneyLog.LogAddCoin(dwOPID, eLogGoldCoin, *pPlayer, pItem->GetSellPrice(), _rUser.GetGoldCoin(), eLogOC_SellItem, pItem->GetItemID(), pItem->GetInstID());
        //ItemLog.LogItemOper(dwOPID, *pPlayer, eItemLog_Sell, eOperLog_None, SLogItemData(pItem->GetItemID(),pItem->GetInstID(),pItem->GetCount(),pItem->GetQuality()));
        pItem->OnUse(*this, pItem->GetCount(), true, (NLogDataDefine::ItemTo_Sell));
    }

    return eItemSucceed;
}

EItemResult CPack::SellItemWithCount(UINT64 qwInstID, UINT16 wCount)
{
    if (!qwInstID || !wCount)
        return eItemErrSell;

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(NULL == pPlayer)
        return eItemErrOther;
    //UINT32 dwOPID = LogOPID;
    CItemPtr pItem = GetItem(qwInstID);
    if(pItem == NULL)
        return eItemNotExist;
    else if(pItem->GetSellPrice() == 0)
        return eItemErrSell;

    if (wCount > pItem->GetCount())
        return SellItemWithCount(qwInstID, pItem->GetItemID(), wCount, pItem->IsBind());

    _rUser.AddMoney(EMONEY_SILVER,pItem->GetSellPrice()*wCount,NLogDataDefine::ItemFrom_SellItem);

    CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
    if(pEventMgr)
    {
        TVecINT32 vecParam;
        vecParam.push_back(wCount);
        vecParam.push_back(pItem->GetItemID());
        pEventMgr->OnEvent(eEventType_PackItemSold,vecParam);
    }

    //MoneyLog.LogAddCoin(dwOPID, eLogGoldCoin, *pPlayer, pItem->GetSellPrice(), _rUser.GetGoldCoin(), eLogOC_SellItem, pItem->GetItemID(), pItem->GetInstID());
    //ItemLog.LogItemOper(dwOPID, *pPlayer, eItemLog_Sell, eOperLog_None, SLogItemData(pItem->GetItemID(),pItem->GetInstID(),pItem->GetCount(),pItem->GetQuality()));
    pItem->OnUse(*this, wCount, true, (NLogDataDefine::ItemTo_Sell));

    return eItemSucceed;
}

EItemResult CPack::SellItemWithCount(UINT64 qwInstID, UINT16 wItemID, UINT16 wCount, bool bBind)
{
    if (!wItemID || !wCount)
        return eItemErrSell;

    CPlayerPtr pPlayer = _rUser.GetPlayer();
    if(NULL == pPlayer)
        return eItemErrOther;
    //UINT32 dwOPID = LogOPID;
    TVecSStoreSlot oVecStoreSlot;
    UINT16 wCnt = GetItemList(wItemID, oVecStoreSlot, 0/*ALL*/, (EBindUseType)bBind); // 0-非绑定 1-绑定
    if (!wCnt || wCnt < wCount)
        return eItemErrSell;

    size_t szItems = oVecStoreSlot.size();
    if (qwInstID)
    {
        for (auto i = oVecStoreSlot.begin(); i != oVecStoreSlot.end(); ++i)
        {
            if (qwInstID == i->pItem->GetInstID())
            {
                SStoreSlot t = *i;
                oVecStoreSlot.erase(i);
                oVecStoreSlot.insert(oVecStoreSlot.begin(), t);
                break;
            }
        }
    }

    wCnt = wCount; // 要使用的个数
    CItemPtr pItem = NULL;
    for(size_t i = 0; i < szItems && wCnt; ++i)
    {
        pItem = oVecStoreSlot[i].pItem;
        if(pItem->GetSellPrice() == 0)
            return eItemErrSell;

        if (wCnt > pItem->GetCount())
        {
            wCnt -= pItem->GetCount();  //XXX 必须放在OnUse之前！！
            pItem->OnUse(*this, pItem->GetCount(), true, (NLogDataDefine::ItemTo_Sell));
        }
        else
        {
            pItem->OnUse(*this, wCnt, true, (NLogDataDefine::ItemTo_Sell));
            wCnt = 0;
        }
    }

    _rUser.AddMoney(EMONEY_SILVER,pItem->GetSellPrice()*wCount,NLogDataDefine::ItemFrom_SellItem);
    //MoneyLog.LogAddCoin(dwOPID, eLogGoldCoin, *pPlayer, pItem->GetSellPrice(), _rUser.GetGoldCoin(), eLogOC_SellItem, pItem->GetItemID(), pItem->GetInstID());
    //ItemLog.LogItemOper(dwOPID, *pPlayer, eItemLog_Sell, eOperLog_None, SLogItemData(pItem->GetItemID(),pItem->GetInstID(),pItem->GetCount(),pItem->GetQuality()));
    return eItemSucceed;
}

#if 0
// ===  FUNCTION  ======================================================================
//         Name:  MergeCitta
//  Description:  背包合成心法
// =====================================================================================
ECittaResult    CPack::MergeCitta(UINT32 dwFormulaID, UINT16 wCount, EBindUseType eBindUseType, TVecItem& vecItemInfo)
{
    ECittaResult eResult = eCittaFailed;
    if (wCount > GetEmptyCount())
    {
        eResult = eCittaPackFull;
        return eResult;
    }

    UINT32 dwCost = CCittaMgr::Instance().GetMergeSilver(dwFormulaID);
    dwCost *= wCount;
    if (!_rUser.CanSubMoney(EMONEY_SILVER,dwCost))
    {
        eResult = eCittaSilverLack;
        return eResult;
    }
    std::map<UINT16, UINT32>mapMaterial;
    eResult = CCittaMgr::Instance().GetMaterial(dwFormulaID, mapMaterial);
    // 所需材料异常
    if (eResult != eCittaSuccess)
        return eResult;


    for (auto it = mapMaterial.begin(); it != mapMaterial.end(); ++it)
    {
        // 材料不足
        if (GetItemCount(it->first, eBindUseType) < it->second * wCount)
        {
            eResult = eCittaMaterialLack;
            return eResult;
        }
    }

    UINT16 wMaxBindCount = 0;   // 最终绑定心法数量
    UINT16 wMaxNoBindCount = 0; // 最终非绑定心法数量

    TVecUINT16 vecBindCount;
    TVecUINT16 vecNoBindCount;

    // 扣除合成所用材料
    for (auto it = mapMaterial.begin(); it != mapMaterial.end(); ++it)
    {
        UINT16 wBindCount = 0;
        UINT16 wNoBindCount = 0;
        DelItemWithBindType(it->first, it->second * wCount, eBindUseType, wBindCount, wNoBindCount, true, NLogDataDefine::ItemTo_MergeCitta);
        CITTA_DBG << "wBindCount = " << wBindCount << ", wNoBindCount = " << wNoBindCount << ".";

        wBindCount = wBindCount / it->second; // 绑定心法数量
        wNoBindCount = wCount - wBindCount;   // 非绑定物品数量
        CITTA_DBG << "wBindCount = " << wBindCount << ", wNoBindCount = " << wNoBindCount << ".";

        vecBindCount.push_back(wBindCount);
        vecNoBindCount.push_back(wNoBindCount);

        //if (eBindUseType == eBindUseBindFirst)  // 如果优先使用绑定，更新最大绑定心法数量
        //else if (eBindUseType = eBindUseNoneFirst) // 如果优先使用非绑定，更新最大非绑定心法数量
        CITTA_DBG << "wBindCount = " << wBindCount << ", wNoBindCount = " << wNoBindCount << ".";
        CITTA_DBG << "wMaxBindCount = " << wMaxBindCount << ", wMaxNoBindCount = " << wMaxNoBindCount << ".";
    }
    for (auto itBind = vecBindCount.begin(), itNoBind = vecNoBindCount.begin(); itBind != vecBindCount.end() && itNoBind != vecNoBindCount.end(); ++itBind, ++itNoBind)
    {
        wMaxBindCount = wMaxBindCount <= *itBind ? *itBind:wMaxBindCount;
        wMaxNoBindCount = wMaxNoBindCount >= *itNoBind ? *itNoBind:wMaxNoBindCount;
    }
    if (eBindUseType == eBindUseBindFirst)  // 如果优先使用绑定，更新最大绑定心法数量
        wMaxNoBindCount = wCount - wMaxBindCount;
    else if (eBindUseType == eBindUseNoneFirst) // 如果优先使用非绑定，更新最大非绑定心法数量
        wMaxBindCount = wCount - wMaxNoBindCount;
    CITTA_DBG << "wMaxBindCount = " << wMaxBindCount << ", wMaxNoBindCount = " << wMaxNoBindCount << ".";

    if (dwCost)
        _rUser.SubMoney(EMONEY_SILVER,dwCost,NLogDataDefine::ItemTo_MergeCitta);

    // 新增心法的ID 
    TVecUINT32 vecCittaID;
    TVecUINT32 vecSignet;
    eResult = CCittaMgr::Instance().GetCittaID(dwFormulaID, wCount, vecCittaID, vecSignet);

    auto it = vecCittaID.begin();
    auto it2 = vecSignet.begin();
    vector<CCittaPtr> vecCittaPtr;

    // 先生产非绑定的心法
    for (UINT16 wIndex = 0; 
            wIndex < wMaxNoBindCount && it != vecCittaID.end() && it2 != vecSignet.end(); 
            ++wIndex, ++it, ++ it2)
    {
        CCittaPtr pCittaItem = CItemMgr::CreateCitta(*it, *it2);
        if (pCittaItem)
        {
            pCittaItem->SetBind(false);
            CITTA_DBG << "No bind Citta add.";
            if (AddItem(*pCittaItem, -1, true, false, true, NLogDataDefine::ItemFrom_MergeCitta))
                vecCittaPtr.push_back(pCittaItem);
        }
        else
        {
            eResult = eCittaFailed;
            return eResult;
        }
    }

    // 然后生成绑定的心法
    for (UINT16 wIndex = 0; 
            wIndex < wMaxBindCount && it != vecCittaID.end() && it2 != vecSignet.end(); 
            ++wIndex, ++it, ++ it2)
    {
        CCittaPtr pCittaItem = CItemMgr::CreateCitta(*it, *it2);
        if (pCittaItem)
        {
            pCittaItem->SetBind(true);
            CITTA_DBG << "Bind Citta add.";
            if (AddItem(*pCittaItem, -1, true, false, true, NLogDataDefine::ItemFrom_MergeCitta))
                vecCittaPtr.push_back(pCittaItem);
        }
        else
        {
            eResult = eCittaFailed;
            return eResult;
        }
    }

    if (eResult != eCittaSuccess)
        return eResult;
    CittaAddNotify(vecCittaPtr);
    for (auto it = vecCittaPtr.begin(); it != vecCittaPtr.end(); ++it)
    {
        vecItemInfo.push_back((*it)->ToProt());
    }


    return eResult;
}		// -----  end of function MergeCitta  ----- //
#endif

// ===  FUNCTION  ======================================================================
//         Name:  MergeCitta
//  Description:  背包合成心法
// =====================================================================================
ECittaResult    CPack::MergeCitta(UINT16 wItemID, UINT16 wCount, EBindUseType eBindUseType, TVecItem& vecItemInfo)
{
    ECittaResult eResult = eCittaFailed;

    // 包裹不足
    if (wCount > GetEmptyCount())
    {
        eResult = eCittaPackFull;;
        return eResult;
    }
    UINT32 dwCost = CEquipTrumpMgr::Instance().GetMergeCost(wItemID) * wCount;
    if (!_rUser.CanSubMoney(EMONEY_SILVER,dwCost))
    {
        eResult = eCittaSilverLack;
        return eResult;
    }
    if (dwCost)
        _rUser.SubMoney(EMONEY_SILVER,dwCost,NLogDataDefine::ItemTo_MergeCitta);

    std::map<UINT16, UINT32>mapMaterial;
    CEquipTrumpMgr::Instance().GetMaterial(wItemID, mapMaterial);

    // 所需材料异常
    if (mapMaterial.empty())
    {
        LOG_CRI << "GetMaterial(" << wItemID << ") error.";
        return eResult;
    }


    // 判断材料是否足够
    for (auto & rPair : mapMaterial)
    {
        // 材料不足
        if (GetItemCount(rPair.first) < rPair.second * wCount)
        {
            eResult = eCittaMaterialLack;
            return eResult;
        }
    }

    // 删除对应材料
    for (auto & rPair : mapMaterial)
    {
        DelItemByItemID(rPair.first, rPair.second * wCount, NLogDataDefine::ItemTo_MergeCitta);
    }

    vector<CCittaPtr> vecCittaPtr;

    SItemGenInfo sItemInfo;
    sItemInfo.wItemID = wItemID;
    sItemInfo.dwCount = wCount;
    if (AddItem(sItemInfo, NLogDataDefine::ItemFrom_MergeCitta))
        eResult = eCittaSuccess;
    else
        eResult = eCittaFailed;

    if (eResult != eCittaSuccess)
        return eResult;
    for (auto & pCitta : vecCittaPtr)
    {
        vecItemInfo.push_back(pCitta->ToProt());
    }

    //event

    TVecINT32 vecParam;
    vecParam.push_back(wItemID);
    if(_rUser.GetPlayer())
        _rUser.GetPlayer()->OnEvent(eEventType_ItemUpgrade,vecParam);

    return eResult;
}		// -----  end of function MergeCitta  ----- //

#if 0
// ===  FUNCTION  ======================================================================
//         Name:  BreakCitta
//  Description:  背包分解心法
// =====================================================================================
ECittaResult    CPack::BreakCitta(const TVecUINT64& qwInstIDVec, TVecItemGenInfo& vecItemInfo)
{
    if (qwInstIDVec.empty())
        return eCittaFailed;
    map<UINT16, UINT16> mapNoBindMaterialCount;
    map<UINT16, UINT16> mapBindMaterialCount;
    UINT32 dwTotalCost = 0;
    for (auto it = qwInstIDVec.begin(); it != qwInstIDVec.end(); ++it)
    {
        CItemPtr pItem = GetItem(*it);
        if (!pItem)
            return eCittaFailed;
        if (!pItem->IsCittaItem())
            return eCittaFailed;
        UINT16 wMaterialID = 0;
        UINT16 wCount = 0;
        ECittaResult eResult = CCittaMgr::Instance().GetBreakMaterial(pItem->GetItemID(), wMaterialID, wCount);
        dwTotalCost += CCittaMgr::Instance().GetBreakSilver(pItem->GetItemID());
        if (eResult != eCittaSuccess)
            return eResult;
        if (pItem->IsBind())
            mapBindMaterialCount[wMaterialID] += wCount;
        else
            mapNoBindMaterialCount[wMaterialID] += wCount;
    }

    if (!_rUser.CanSubMoney(EMONEY_SILVER,dwTotalCost))
        return eCittaSilverLack;
    if (dwTotalCost)
        _rUser.SubMoney(EMONEY_SILVER,dwTotalCost,NLogDataDefine::ItemTo_BreakCitta);

    TVecItemGenInfo vecItemGen;
    for (auto it = mapBindMaterialCount.begin(); it != mapBindMaterialCount.end(); ++it)
    {
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.eBindType = eBindGet;
        oItemGenInfo.dwCount = it->second;
        oItemGenInfo.wItemID = it->first;
        vecItemGen.push_back(oItemGenInfo);
    }

    for (auto it = mapNoBindMaterialCount.begin(); it != mapNoBindMaterialCount.end(); ++it)
    {
        SItemGenInfo oItemGenInfo;
        oItemGenInfo.eBindType = eBindNone;
        oItemGenInfo.dwCount = it->second;
        oItemGenInfo.wItemID = it->first;
        vecItemGen.push_back(oItemGenInfo);
    }
    if (!CanAddItem(vecItemGen))
        return eCittaPackFull;
    if (!AddItem(vecItemGen,NLogDataDefine::ItemFrom_BreakCitta))
        return eCittaFailed;
    vecItemInfo = vecItemGen;
    for (auto it = qwInstIDVec.begin(); it != qwInstIDVec.end(); ++it)
    {
        if (!DelItemByInstID(*it, 1, true, true, NLogDataDefine::ItemTo_MergeCitta))
            return eCittaFailed;
    }
    _rUser.SendPkg(g_ItemProtS.BuildPkg_StoreItemDelNtf(GetStoreType(), qwInstIDVec));
    return eCittaSuccess;
}		// -----  end of function BreakCitta  ----- //
#endif

// ===  FUNCTION  ======================================================================
//         Name:  BreakCitta
//  Description:  背包分解心法
// =====================================================================================
ECittaResult    CPack::BreakCitta(const TVecUINT64& qwInstIDVec, TVecItemGenInfo& vecItemInfo)
{
    if (qwInstIDVec.empty())
        return eCittaFailed;
    if(NULL == _rUser.GetPlayer())
        return eCittaFailed;
    TVecItemGenInfo vecItemGen;

    UINT32 dwTotalCost = 0;
    for (auto & rID : qwInstIDVec)
    {
        CItemPtr pItem = GetItem(rID);
        if (!pItem)
            return eCittaFailed;;
        if (!pItem->IsCittaItem())
            return eCittaFailed;;
        CCittaPtr pCitta = dynamic_pointer_cast<CCitta>(pItem);
        if (!pCitta)
            return eCittaFailed;;

        UINT32 dwLootID =  CCittaMgr::Instance().GetBreakLootID(pCitta->GetItemID());
        if (!dwLootID)
        {
            LOG_CRI << "Break error";
            return eCittaFailed;;
        }

        TVecResource vecRes;

        //奖励A
        LOOT.Roll(dwLootID, vecItemGen, vecRes);
        dwTotalCost += CCittaMgr::Instance().GetBreakSilver(pCitta->GetItemID());
    }

    map<UINT16, UINT32> mapItemPair;
    for (auto rInfo : vecItemGen)
    {
        mapItemPair[rInfo.wItemID] += rInfo.dwCount;
    }

    TVecItemGenInfo vecItemGen2;
    for (auto & rPair : mapItemPair)
    {
        vecItemGen2.push_back(SItemGenInfo(rPair.first, rPair.second, 0, eBindNone, 0));
    }

    if (!CanAddItem(vecItemGen2))
        return eCittaPackFull;

    if (!_rUser.CanSubMoney(EMONEY_SILVER,dwTotalCost))
        return eCittaSilverLack;
    if (dwTotalCost)
        _rUser.SubMoney(EMONEY_SILVER,dwTotalCost,NLogDataDefine::ItemTo_BreakCitta);


    if (!AddItem(vecItemGen2,NLogDataDefine::ItemFrom_BreakEquipTrump))
        return eCittaFailed;;

    vecItemInfo = vecItemGen2;
    for (auto & rID : qwInstIDVec)
    {
        if (!DelItemByInstID(rID, 1, false, true, NLogDataDefine::ItemTo_MergeEquipTrump))
            return eCittaFailed;;
    }
    _rUser.SendPkg(g_ItemProtS.BuildPkg_StoreItemDelNtf(GetStoreType(), qwInstIDVec));

    return eCittaSuccess;
}		// -----  end of function BreakCitta  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  MergeEquipTrump
//  Description:  背包合成装备法宝
// =====================================================================================
EEquipTrumpMergeResult    CPack::MergeEquipTrump(UINT16 wItemID, UINT16 wCount, TVecItem& vecItemInfo)
{
    EEquipTrumpMergeResult eResult = eETMRFailed;

    // 包裹不足
    if (wCount > GetEmptyCount())
    {
        eResult = eETMRPackFull;;
        return eResult;
    }
    UINT32 dwCost = CEquipTrumpMgr::Instance().GetMergeCost(wItemID) * wCount;
    if (!_rUser.CanSubMoney(EMONEY_SILVER,dwCost))
    {
        eResult = eETMRLackOfSilver;
        return eResult;
    }
    if (dwCost)
        _rUser.SubMoney(EMONEY_SILVER,dwCost,NLogDataDefine::ItemTo_MergeEquipTrump);

    std::map<UINT16, UINT32>mapMaterial;
    CEquipTrumpMgr::Instance().GetMaterial(wItemID, mapMaterial);

    // 所需材料异常
    if (mapMaterial.empty())
    {
        LOG_CRI << "GetMaterial(" << wItemID << ") error.";
        return eResult;
    }


    // 判断材料是否足够
    for (auto & rPair : mapMaterial)
    {
        // 材料不足
        if (GetItemCount(rPair.first) < rPair.second * wCount)
        {
            eResult = eETMRLackOfMaterial;
            return eResult;
        }
    }

    // 删除对应材料
    for (auto & rPair : mapMaterial)
    {
        DelItemByItemID(rPair.first, rPair.second * wCount, NLogDataDefine::ItemTo_MergeEquipTrump);
    }

    vector<CEquipTrumpPtr> vecEquipTrumpPtr;

    SItemGenInfo sItemInfo;
    sItemInfo.wItemID = wItemID;
    sItemInfo.dwCount = wCount;
    if (AddItem(sItemInfo, NLogDataDefine::ItemFrom_MergeEquipTrump))
        eResult = eETMRSuccess;
    else
        eResult = eETMRFailed;

    if (eResult != eETMRSuccess)
        return eResult;
    for (auto & pEquipTrump : vecEquipTrumpPtr)
    {
        vecItemInfo.push_back(pEquipTrump->ToProt());
    }

    //event

    TVecINT32 vecParam;
    vecParam.push_back(wItemID);
    if(_rUser.GetPlayer())
    {
        _rUser.GetPlayer()->OnEvent(eEventType_ItemUpgrade,vecParam);
    }

    return eResult;
}		// -----  end of function MergeEquipTrump  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  BreakEquipTrump
//  Description:  背包分解装备法宝
// =====================================================================================
EEquipTrumpBreakResult    CPack::BreakEquipTrump(const TVecUINT64& qwInstIDVec, TVecItemGenInfo& vecItemInfo)
{
    if (qwInstIDVec.empty())
        return eETBRFailed;
    if(NULL == _rUser.GetPlayer())
        return eETBRFailed;
    TVecItemGenInfo vecItemGen;

    for (auto & rID : qwInstIDVec)
    {
        CItemPtr pItem = GetItem(rID);
        if (!pItem)
            return eETBRFailed;;
        if (!pItem->IsEquipTrumpItem())
            return eETBRFailed;;
        CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
        if (!pEquipTrump)
            return eETBRFailed;;

        UINT32 dwLootID =  CEquipTrumpMgr::Instance().GetBreakLootID(pEquipTrump->GetItemID(), pEquipTrump->GetIntensify());
        if (!dwLootID)
        {
            LOG_CRI << "Break error";
            return eETBRFailed;;
        }

        TVecResource vecRes;

        //奖励A
        LOOT.Roll(dwLootID, vecItemGen, vecRes);

        TVecINT32 vecParam;
        vecParam.push_back(pEquipTrump->GetID());
        vecParam.push_back(pEquipTrump->GetIntensify());
        _rUser.GetPlayer()->OnEvent(eEventType_TrumpDes,vecParam);

    }


    if (!CanAddItem(vecItemGen))
        return eETBRPackFull;

    if (!AddItem(vecItemGen,NLogDataDefine::ItemFrom_BreakEquipTrump))
        return eETBRFailed;;

    vecItemInfo = vecItemGen;
    for (auto & rID : qwInstIDVec)
    {
        if (!DelItemByInstID(rID, 1, false, true, NLogDataDefine::ItemTo_MergeEquipTrump))
            return eETBRFailed;;
    }
    _rUser.SendPkg(g_ItemProtS.BuildPkg_StoreItemDelNtf(GetStoreType(), qwInstIDVec));

    return eETBRSuccess;
}		// -----  end of function BreakEquipTrump  ----- //

// ===  FUNCTION  ======================================================================
//         Name:  GetAllEquipTrump
//  Description:  获取所有装备法宝
// =====================================================================================
void CPack::GetAllEquipTrump (TVecEquipTrumpPtr& rvecEquipTrumpPtr)
{
    vector<CItemPtr> vecItem;
    GetAllItemList(vecItem);
    for (auto & pItem : vecItem)
    {
        if (pItem->IsEquipTrumpItem())
            rvecEquipTrumpPtr.push_back(dynamic_pointer_cast<CEquipTrump>(pItem));
    }
}		// -----  end of function GetAllEquipTrump  ----- //

EGemstoneResult  CPack::MergeGenStone(UINT16 wItemID,UINT32 dwNum)
{
    if(dwNum == 0)
    {
        return eGemstoneSuccess; 
    }
    map<UINT16,UINT32> mapGrade;
    SItemInfo* pInfo = CItemMgr::GetItemConfig(wItemID);
    if(!pInfo)
    {
        return eGemstoneErrStone;
    }
    if(!CItemMgr::GetUpdateMaterial(wItemID,mapGrade))
    {
        return eGemstoneErrStone;
    }

    //看叠加
    UINT16 wStack = pInfo->oItemCfg._Stack;
    UINT32 wCreateNum = dwNum % wStack == 0 ? dwNum / wStack : dwNum / wStack +1;
    //查空格
    if(GetEmptyCount() < wCreateNum)
    {
        return eGemstonePackFull;
    }
    //数量合并
    for(auto pos = mapGrade.begin(); pos != mapGrade.end(); pos++)
    {
        pos->second *= dwNum;
        if(GetItemCount(pos->first) < pos->second)
        {
            return eGemstoneMaterialLack;
        }
    }
    //扣物品
    for(auto pos = mapGrade.begin(); pos != mapGrade.end(); pos++)
    {
        UINT16 wUse = pos->second / wStack;
        UINT16 wRef = pos->second % wStack;
        if(wUse > 0)
        {
            for(auto i =0 ; i < wUse ; i++)
            {
                DelItemByItemID(pos->first,wStack, true,NLogDataDefine::ItemTo_MergeStone);

            }
        }
        if(wRef > 0)
        {
            DelItemByItemID(pos->first,wRef,true,NLogDataDefine::ItemTo_MergeStone);
        }

    }
    //物品生成
    UINT16 wUse = dwNum / wStack;
    UINT16 wRef = dwNum % wStack;

    if(wUse > 0)
    {
        for(auto i =0 ; i < wUse ; i++)
        {
            AddItemWithID(wItemID, wStack,eBindGet,0,NLogDataDefine::ItemFrom_MergeStone);

        }
    }
    if(wRef > 0)
    {
        AddItemWithID(wItemID, wRef,eBindGet,0,NLogDataDefine::ItemFrom_MergeStone);

    }
    if(wUse || wRef)
    {
        if(pInfo->oItemCfg._StoneLevel >=5 )
        {
            TVecString vecstring;
            vecstring.push_back(NumberToString(_rUser.GetPlayer()->GetColor()));
            vecstring.push_back(_rUser.GetPlayer()->GetName());
            vecstring.push_back(NumberToString(pInfo->oItemCfg._Quality));
            vecstring.push_back(pInfo->oItemCfg._Name);
            g_ChatProtS.SendClt_SystemFormatMsgIDNotify(NULL, 0, eMsgGemstoneGet, vecstring);
        }
    }

    if(NULL == _rUser.GetPlayer())
    {
        return eGemstoneSuccess;
    }

    g_FeedBackMgr.OnStoneChange(*_rUser.GetPlayer(),pInfo->oItemCfg._StoneLevel,dwNum);

    TVecINT32 vecParam;
    vecParam.push_back(1);
    _rUser.GetPlayer()->OnEvent(eEventType_GemsCompose,vecParam);

    _rUser.GetTaskPkg().OnAction(*_rUser.GetPlayer(), eProcessAction_MergeStone);

    return eGemstoneSuccess; 
}

bool CPack::AddItemOrMail(CItem& rItem, INT16 wIndex /* = -1 */, bool bNotify /* = true */, bool bNew /* = false */, bool bUpdate /* = true */, UINT16 fromWhere /* = 0 */)
{
    bool bRet = CStore::AddItem(rItem, wIndex, bNotify, bNew, bUpdate, fromWhere);

    // 放入没成功，发邮件
    if (!bRet)
    {
        NMailProt::SysMailSendTxt stBody;
        vector<CItemPtr> vecItem;
        vecItem.push_back(ToThisPtr(&rItem));
        stBody.dwstrMsgID = 1;
        TVecUINT64 vecTargets;
        vecTargets.push_back(GetUser().GetUserID());
        TVecItemGenInfo vecItems;
        GameServerSysMail::SendSysMail(1, 1, stBody, vecTargets, &vecItems);
        bRet = true;
    }
    return bRet;
}
