#include "stdafx.h"
#include "Game2CenterTeamC.h"
#include "ItemProtS.h"
#include "UserMgr.h"
#include "ItemMgr.h"
#include "Player.h"
#include "FighterManager.h"
#include "Parameter.h"
#include "MoneyParam.h"
#include "Map.h"
#include "MapInfo.h"
#include "SysMsgDefine.h"
#include "TrumpSlots.h"
#include "HeroFighter.h"
#include "GameNetMgr.h"

//接收：请求包裹信息(整个包裹)
bool CItemProtS::OnRecv_GetStore(
        EStoreType eStoreType, //存储类型
        shared_func<SGetStoreAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    pUser->StoreToStream(eStoreType, fnAck->stStoreStream);
    fnAck->dwNextUnlockTime = pPlayer->GetPackNextUnlockTime();
    return true;
}

//接收：请求使用包裹中的道具
bool CItemProtS::OnRecv_UseItem(
        EStoreType eStoreType, //存储类型
        UINT64 qwRoleID, //针对的角色ID
        UINT64 qwMercenID,	//针对的佣兵ID
        UINT64 qwInstID, //优先使用的物品实例ID
        UINT16 wStack, //使用个数(只针对堆叠道具)
        shared_func<SUseItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    //禁止使用道具状态判断
    if(pPlayer == NULL || !pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(wStack == 0)
    {
        fnAck->eResult = eItemErrOther;
        return false;
    }

    // XXX: 这个share_ptr能确保GameScript::ItemUseNormal所使用的pOtherUser的存在
    CUserPtr pOther;
    if (qwRoleID && qwRoleID != pUser->GetUserID())
        pOther = CUserMgr::GetUserByUserID(qwRoleID);

    switch(eStoreType)
    {
        case eStorePack:
            fnAck->eResult = pUser->GetPack().UseItem(qwInstID, wStack, qwMercenID, pOther.get());
            break;
        case eStoreDepot:
            fnAck->eResult = pUser->GetDepot().UseItem(qwInstID, wStack, qwMercenID, pOther.get());
            break;
        default:
            fnAck->eResult = eItemErrOther;
            break;
    }
    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgItemUseSuccess);
    /*
       else
       SendSysMsgIDNotify(fnAck->eResult);
       */
    return fnAck->eResult == eItemSucceed;
}

//接收：扩充包裹或仓库
bool CItemProtS::OnRecv_ExpandStore(
        EStoreType eStoreType, //存储类型
        UINT8 byCount, //扩充个数
        NProtoCommon::ECoinType eCoinType, //货币类型
        shared_func<SExpandStoreAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(byCount == 0)
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(eStoreType == eStoreDepot)
    {
        //XXX 策划取消此功能(花费仙石开启仓库格子)，改为VIP等级控制自动开启
        fnAck->eResult = eItemErrOper;
        return false;
    }

    CStore* pStore = NULL;
    UINT32 dwMoney = 0; 
    switch(eStoreType)
    {
        case eStorePack:
            {
                pStore = &pUser->GetPack();
                if(SParamConfig::wPackMaxCount < pStore->GetCapacity() + byCount)
                {
                    fnAck->eResult = eItemStoreMax;
                    return false;
                }

                UINT16 wInit = pStore->GetCapacity() - SParamConfig::wPackInitCount + 1;
                for(UINT8 i = 0; i < byCount; i++,wInit++)
                {
                    SBagCostCFG* pBagCostCfg = CItemMgr::GetBagCost(pStore->GetCapacity()+i+1);
                    if (!pBagCostCfg)
                    {
                        fnAck->eResult = eItemErrOper;
                        return false;
                    }
                    dwMoney += pBagCostCfg->_Cost;
                }
            }
            break;
        case eStoreDepot:
            {
                pStore = &pUser->GetDepot();
                if(SParamConfig::wDepotMaxCount < pStore->GetCapacity() + byCount)
                {
                    fnAck->eResult = eItemDepotMax;
                    return false;
                }
                UINT16 wInit = pStore->GetCapacity() - SParamConfig::wDepotInitCount + 1;
                for(UINT8 i = 0;i < byCount;i++, wInit++)
                {
                    SDepotCostCFG* pDepotCostCfg = CItemMgr::GetDepotCost(pStore->GetCapacity()+i+1);
                    if (!pDepotCostCfg)
                    {
                        fnAck->eResult = eItemErrOper;
                        return false;
                    }
                    dwMoney += pDepotCostCfg->_Cost;
                }
            }
            break;

        default:
            break;
    }

    if(NULL == pStore)
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    //判断钱够不够
    switch(eCoinType)
    {
        case eGoldCoin:
            {
                if(!pUser->CanSubMoney(EMONEY_GOLD,dwMoney))
                {
                    fnAck->eResult = eItemNoMoney;
                    //g_ChatProtS.Send_SystemMsgIDNotify(eMsgGoldErr);
                    return false;
                }
            }
            break;
        case eCouponCoin:
            break;
        default:
            fnAck->eResult = eItemErrOther;
            return false;
    }

    fnAck->eResult = pStore->Expand(byCount);
    if(eItemSucceed == fnAck->eResult)
    {
        switch(eCoinType)
        {
            case eGoldCoin:
                pUser->SubMoney(EMONEY_GOLD,dwMoney,NLogDataDefine::ItemTo_ExpandStore);
                break;
            default:
                break;
        }
        if (pPlayer->GetFighterManager())
            pPlayer->GetFighterManager()->SetDirty(eAttrGpBag);
        if(eStorePack == eStoreType)
        {
            CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
            if(pEventMgr)
            {
                UINT16 wExpandCount = pStore->GetCapacity() - SParamConfig::wPackInitCount;
                TVecINT32 vecParam;
                vecParam.push_back(wExpandCount);
                pEventMgr->OnEvent(eEventType_PackExpand,vecParam);
            }
        }
    }

    if(eItemSucceed == fnAck->eResult)
    {
        ESystemMsgID eMsgID = eMsgItem;
        switch(eStoreType)
        {
            case eStorePack:
                eMsgID = eMsgItemExpandPack;
                break;
            case eStoreDepot:
                eMsgID = eMsgItemExpandDepot;
                break;
            default:
                break;
        }
        g_ChatProtS.Send_SystemFormatMsgIDNotify(eMsgID, BuildStrVec(byCount));
    }
    else
        SendSysMsgIDNotify(fnAck->eResult);

    return fnAck->eResult == eItemSucceed;
}

//接收：包裹或仓库中道具换位置
bool CItemProtS::OnRecv_RelocateStoreItem(
        EStoreType eStoreType, //存储类型
        UINT64 qwInstID, //道具的实例ID
        INT16 wNewIndex, //道具在包裹中新的位置0开始
        shared_func<SRelocateStoreItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    switch(eStoreType)
    {
        case eStorePack:
            fnAck->eResult = pUser->GetPack().RelocateItem(qwInstID, wNewIndex);
            break;
        case eStoreDepot:
            fnAck->eResult = pUser->GetDepot().RelocateItem(qwInstID, wNewIndex);
            break;
        default:
            fnAck->eResult = eItemErrOper;
            break;
    }

    if(eItemSucceed != fnAck->eResult)
        SendSysMsgIDNotify(fnAck->eResult);

    return fnAck->eResult == eItemSucceed;
}

//接收：整理包裹或仓库
bool CItemProtS::OnRecv_TidyupStore(
        EStoreType eStoreType, //存储类型
        shared_func<STidyupStoreAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    switch(eStoreType)
    {
        case eStorePack:
            if(pUser->GetPack().Tidyup())
                fnAck->eResult = eItemSucceed;
            else
                fnAck->eResult = eItemStoreErr;
            break;

        case eStoreDepot:
            if(pUser->GetDepot().Tidyup())
                fnAck->eResult = eItemSucceed;
            else
                fnAck->eResult = eItemStoreErr;
            break;

        default:
            fnAck->eResult = eItemStoreErr;
            break;
    }
    if(eStorePack == eStoreType)
    {
        CEventMgrPtr pEventMgr = pPlayer->GetEventMgr();
        if(pEventMgr)
        {
            TVecINT32 vecParam;
            vecParam.push_back(1);
            pEventMgr->OnEvent(eEventType_PackArrange,vecParam);
        }
    }



    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgItemTidy);
    else
        SendSysMsgIDNotify(fnAck->eResult);

    return fnAck->eResult == eItemSucceed;
}

//接收：拆分包裹或仓库中的堆叠类道具
bool CItemProtS::OnRecv_SplitStackItem(
        EStoreType eStoreType, //存储类型
        UINT64 qwInstID, //道具的实例ID
        UINT16 wStack, //拆分出来的堆叠数量
        INT16 wIndex, //拆分出来的堆叠道具的存储位置(-1表示选第一个空位)
        shared_func<SSplitStackItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(0 == wStack)
    {
        fnAck->eResult = eItemErrOther;
        return false;
    }

    switch(eStoreType)
    {
        case eStorePack:
            fnAck->eResult = pUser->GetPack().SplitStackItem(qwInstID, wStack, wIndex);
            break;

        case eStoreDepot:
            fnAck->eResult = pUser->GetDepot().SplitStackItem(qwInstID, wStack, wIndex);
            break;

        default:
            fnAck->eResult = eItemStoreErr;
            break;
    }

    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgItemSplit);
    else
        SendSysMsgIDNotify(fnAck->eResult);

    return fnAck->eResult == eItemSucceed;
}

//接收：合并包裹或仓库中的堆叠类道具
bool CItemProtS::OnRecv_MergeStackItem(
        EStoreType eStoreType, //存储类型
        UINT64 qwFromInstID, //源道具的实例ID
        UINT64 qwToInstID, //目的道具的实例ID
        shared_func<SMergeStackItemAck>& fnAck //返回回调函数
        )
{
    return false;
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    switch(eStoreType)
    {
        case eStorePack:
            fnAck->eResult = pUser->GetPack().MergeStackItem(qwFromInstID,qwToInstID);
            break;
        case eStoreDepot:
            fnAck->eResult = pUser->GetDepot().MergeStackItem(qwFromInstID,qwToInstID);
            break;
        default:
            fnAck->eResult = eItemStoreErr;
            break;
    }

    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgItemMix);
    else
        SendSysMsgIDNotify(fnAck->eResult);

    return fnAck->eResult == eItemSucceed;
}

//接收：销毁包裹或仓库中的道具
bool CItemProtS::OnRecv_DestroyStoreItem(
        EStoreType eStoreType, //存储类型
        UINT64 qwInstID, //道具的实例ID
        shared_func<SDestroyStoreItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    //SLogItemData oLogData;
    switch(eStoreType)
    {
        case eStorePack:
            {
                CItemPtr pItem = pUser->GetPack().GetItem(qwInstID);
                if(NULL == pItem)
                {
                    fnAck->eResult = eItemNotExist;
                    return false;
                }
                //oLogData._wItemID = pItem->GetItemID();
                //oLogData._qwInstID = pItem->GetInstID();
                //oLogData._dwCount = pItem->GetCount();
                //oLogData._byQuality = pItem->GetQuality();
                fnAck->eResult = pUser->GetPack().DestroyItem(qwInstID);
            }
            break;
        case eStoreDepot:
            {
                CItemPtr pItem = pUser->GetDepot().GetItem(qwInstID);
                if(NULL == pItem)
                {
                    fnAck->eResult = eItemNotExist;
                    return false;
                }
                //oLogData._wItemID = pItem->GetItemID();
                //oLogData._qwInstID = pItem->GetInstID();
                //oLogData._dwCount = pItem->GetCount();
                //oLogData._byQuality = pItem->GetQuality();
                fnAck->eResult = pUser->GetDepot().DestroyItem(qwInstID);
            }
            break;
        default:
            fnAck->eResult = eItemStoreErr;
            break;
    }

    //if(eItemSucceed == fnAck->eResult)
    //	ItemLog.LogItemOper(LogOPID, *pPlayer, eItemLog_Drop, eOperLog_None, oLogData);

    if(eItemSucceed != fnAck->eResult)
        SendSysMsgIDNotify(fnAck->eResult);

    return eItemSucceed == fnAck->eResult;
}

//接收：在包裹和仓库之间移动道具
bool CItemProtS::OnRecv_TransferItem(
        EStoreType eFromStoreType, //源存储类型
        EStoreType eToStoreType, //目的存储类型
        UINT64 qwInstID, //道具的实例ID
        INT16 wIndex, //道具在目的存储中的位置(-1表示选第一个空位)
        shared_func<STransferItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(eFromStoreType == eToStoreType 
            || (eFromStoreType != eStorePack && eFromStoreType != eStoreDepot)
            || (eToStoreType != eStorePack && eToStoreType != eStoreDepot))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    CStore* pFromStore = pUser->GetStoreByType(eFromStoreType);
    CStore* pToStore = pUser->GetStoreByType(eToStoreType);
    if(pFromStore == NULL || pToStore == NULL)
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if (wIndex >= pToStore->GetCapacity())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    if(wIndex == -1 && pToStore->IsStoreFull())
    {
        fnAck->eResult = eItemStoreFull;
        return false;
    }
    INT16 wFromIndex = -1;
    CItemPtr pFromItem = pFromStore->GetItem(qwInstID, &wFromIndex);
    if(pFromItem == NULL || wFromIndex == -1)
    {
        fnAck->eResult = eItemNotExist;
        return false;
    }
    if(eItemTask == pFromItem->GetItemType())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    CItemPtr pToItem  = NULL ;
    if(wIndex != -1)
    {
        pToItem= pToStore->GetItem(wIndex);
    }
    else
    {
        wIndex = pToStore->GetEmptyIndex();    
    }
    fnAck->eResult = eItemErrOther;
    if(pToItem == NULL)//目标容器制定位置有道具则交换
    {
        if (pToStore->CanAddItem(*pFromItem, wIndex) && pFromStore->DelItem(*pFromItem, true, false, NLogDataDefine::ItemTo_UserDeptORPack))
        {
            pToStore->AddItem(*pFromItem, wIndex, true, false, true, NLogDataDefine::ItemFrom_UserDeptORPack);
            fnAck->eResult = eItemSucceed;
        }
        else
        {
            fnAck->eResult = eItemErrOper;
            return false;
        }
    }
    else
    {
        if(eItemTask == pToItem->GetItemType())
        {
            fnAck->eResult = eItemErrOper;
            return false;
        }
        //是否能叠加
        if(CItemMgr::MergeStackItem(*pFromStore, *pToStore, *pFromItem, *pToItem))
        {
            fnAck->eResult = eItemSucceed;
        }
        else
        {
            if(CItemMgr::TransferStoreItem(*pFromStore, *pToStore, *pFromItem, wFromIndex, *pToItem, wIndex))
                fnAck->eResult = eItemSucceed;
        }
    }

    /*
       if(eItemSucceed != fnAck->eResult)
       SendSysMsgIDNotify(fnAck->eResult);
       */

    return fnAck->eResult == eItemSucceed;
}

//接收：请求出售包裹中的道具
bool CItemProtS::OnRecv_SellItem(
        const TVecUINT64& vecInstID, //出售的道具实例ID集合
        shared_func<SSellItemAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    //禁止使用道具状态判断
    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    fnAck->eResult = pUser->GetPack().SellItem(vecInstID);
    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgItemSell);
    else
        SendSysMsgIDNotify(fnAck->eResult);
    return fnAck->eResult == eItemSucceed;
}

//接收：请求按个数出售包裹中的道具-出售给系统
bool CItemProtS::OnRecv_SellItemWithCount(
        EStoreType eStoreType, //存储类型
        UINT64 qwInstID, //优先卖出的物品实例ID
        UINT16 wStack, //卖出个数(只针对堆叠道具)
        shared_func<SSellItemWithCountAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }
    //禁止使用道具状态判断
    if(!pPlayer->CanUseItem())
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    switch (eStoreType)
    {
        case eStorePack:
            {
                fnAck->eResult = pUser->GetPack().SellItemWithCount(qwInstID, wStack);
            }
            break;
        case eStoreDepot:
            {
                fnAck->eResult = pUser->GetDepot().SellItemWithCount(qwInstID, wStack);
            }
            break;
        default:
            break;
    }

    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgItemSell);
    else
        SendSysMsgIDNotify(fnAck->eResult);
    return fnAck->eResult == eItemSucceed;
}

//接收：解锁背包格子
bool CItemProtS::OnRecv_UnlockPack(
        shared_func<SUnlockPackAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemFailed;
        return false;
    }
    if (!pPlayer->UnlockPack())
    {
        fnAck->eResult = eItemFailed;
        return false;
    }

    fnAck->eResult = eItemSucceed;
    return true;
}

//接收：打开道具日志
void CItemProtS::OnRecv_OpenItemLogger(
        EItemLoggerType eType
        )
{

}

//接收：记录传送点
bool CItemProtS::OnRecv_RecordTransfPoint(
        UINT64 qwInstID, //道具ID
        UINT16 wIndex, //存储序号
        shared_func<SRecordTransfPointAck>& fnAck //返回回调函数
        )
{
#if 0
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(wIndex == 0 || !NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(pPlayer->IsInDungeon())
    {
        fnAck->eResult = eItemErrDungeon;
        return false;
    }

    fnAck->eResult = CItemMgr::RecordTransfPoint(*pPlayer, qwInstID, wIndex);
    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsg_ItemTransfRecord);
    else
        SendSysMsgIDNotify(fnAck->eResult);
    return eItemSucceed == fnAck->eResult;
#endif
    return false;
}

//接收：传送
bool CItemProtS::OnRecv_TransfMapPoint(
        UINT64 qwInstID, //道具ID
        UINT16 wIndex, //存储序号
        UINT16 wMapID, //地图ID
        shared_func<STransfMapPointAck>& fnAck //返回回调函数
        )
{
#if 0
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(wIndex == 0 || !NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    if(pPlayer->IsInDungeon())
    {
        fnAck->eResult = eItemErrDungeon;
        return false;
    }

    CGameMapPtr pMap = pPlayer->GetMap();
    if(NULL == pMap)
    {
        fnAck->eResult = eItemErrOper;
        return false;
    }

    //是否敌对阵营
    if(pUser->GetCampRep().IsHostility(pMap->GetMapInfo().byCamp))
    {
        fnAck->eResult = eItemErrTransfMap;
        return false;
    }

    fnAck->eResult = CItemMgr::TransfMapPoint(*pPlayer, qwInstID, wIndex, wMapID);
    if(eItemSucceed == fnAck->eResult)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsg_ItemTransf);
    else
        SendSysMsgIDNotify(fnAck->eResult);

    return eItemSucceed == fnAck->eResult;
#endif
    return false;
}

//接收：请求装备心法
bool CItemProtS::OnRecv_WearCitta(
        UINT64 qwInstID, //装备的实例ID
        ECittaSlotType eSlotType, //装备位的类型
        shared_func<SWearCittaAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCittaFailed;
        return false;
    }

    CPack& rPack = pUser->GetPack();
    CItemPtr pItem = rPack.GetItem(qwInstID);
    if (!pItem || !pItem->IsCittaItem())
    {
        fnAck->eResult = eCittaFailed;
        return false;
    }
    CCittaSlots& rCittaSlots = pPlayer->GetFighterManager()->GetCittaSlots();

    CCittaPtr pCitta = dynamic_pointer_cast<CCitta>(pItem);
    fnAck->eResult = rCittaSlots.Ware(pCitta, eSlotType);
    if(fnAck->eResult == eCittaSuccess)
    {
        pUser->GetTaskPkg().OnAction(*pPlayer,eProcessAction_TianShu);
    }

    return true;
}

//接收：请求卸下心法
bool CItemProtS::OnRecv_TakeoffCitta(
        ECittaSlotType eSlotType, //装备位的类型
        INT16 wIndex, //放入心法栏位置：-1表示右击脱下，非-1表示放入包裹的位置
        shared_func<STakeoffCittaAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCittaFailed;
        return false;
    }

    CPack& rPack = pUser->GetPack();
    if (rPack.IsStoreFull())
        return eCittaPackFull;

    CCittaSlots& rCittaSlots = pPlayer->GetFighterManager()->GetCittaSlots();

    fnAck->eResult = rCittaSlots.Takeoff(eSlotType);
    return true;
}

// 接收：请求合成心法
bool CItemProtS::OnRecv_MergeCitta(
        EBindUseType eBindUseType, //合成方式
        UINT16 wItemID, //制作心法模版ID
        UINT16 wCount, //制作数量
        shared_func<SMergeCittaAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCittaFailed;
        return false;
    }
    fnAck->eResult = pUser->GetPack().MergeCitta(wItemID, wCount, eBindUseType, fnAck->vecItemCitta);
    return true;
}

// 接收：请求分解心法
bool CItemProtS::OnRecv_BreakCitta(
        const TVecUINT64& vecInstID, //物品唯一ID
        shared_func<SBreakCittaAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eCittaFailed;
        return false;
    }
    fnAck->eResult = pUser->GetPack().BreakCitta(vecInstID, fnAck->vecItemInfo);
    return true;
}

//接收：激活法宝
bool CItemProtS::OnRecv_ActiveTrump(
        UINT16 wItemID, //法宝道具ID
        shared_func<SActiveTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTrumpFailed;
        return false;
    }

    CTrumpSlots& rTrumpSlots = pPlayer->GetFighterManager()->GetTrumpSlots();
    fnAck->eResult = rTrumpSlots.ActiveTrump(wItemID, fnAck->vecTrump);
    /* if(eTrumpSuccess == fnAck->eResult)
       {
       pUser->GetTaskPkg().OnAction(*pPlayer, eProcessAction_GetTrump, 1);
       }*/
    return true;
}

//接收：出战法宝
bool CItemProtS::OnRecv_EquipTrump(
        UINT64 qwInstID, //法宝的实例ID
        shared_func<SEquipTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTrumpFailed;
        return false;
    }
    CTrumpSlots& rTrumpSlots = pPlayer->GetFighterManager()->GetTrumpSlots();
    fnAck->eResult = rTrumpSlots.EquipTrump(qwInstID, fnAck->vecTrump);
    return true;
}

//接收：卸下法宝
bool CItemProtS::OnRecv_UnEquipTrump(
        UINT64 qwInstID, //法宝的实例ID
        shared_func<SUnEquipTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTrumpFailed;
        return false;
    }
    CTrumpSlots& rTrumpSlots = pPlayer->GetFighterManager()->GetTrumpSlots();
    fnAck->eResult = rTrumpSlots.UnEquipTrump(qwInstID, fnAck->vecTrump);
    return true;
}

//接收：祭炼法宝
bool CItemProtS::OnRecv_UpgradeTrump(
        UINT64 qwInstID, //法宝的实例ID
        UINT8 byOneKey, //是否一键
        shared_func<SUpgradeTrumpAck>& fnAck //返回回调函
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTrumpFailed;
        return false;
    }
    CTrumpSlots& rTrumpSlots = pPlayer->GetFighterManager()->GetTrumpSlots();
    fnAck->eResult = rTrumpSlots.UpgradeTrump(qwInstID, byOneKey, fnAck->vecTrump);
    return true;
}

//接收：提升法宝品级
bool CItemProtS::OnRecv_EvolveTrump(
        UINT64 qwInstID, //法宝的实例ID
        shared_func<SEvolveTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTrumpFailed;
        return false;
    }
    CTrumpSlots& rTrumpSlots = pPlayer->GetFighterManager()->GetTrumpSlots();
    fnAck->eResult = rTrumpSlots.EvolveTrump(qwInstID, fnAck->vecTrump);
    return true;
}


//接收：激活时装
bool CItemProtS::OnRecv_FashionActive(
        UINT16 wItemID, //时装物品ID
        shared_func<SFashionActiveAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFashionSlots& rFashions = pFighterManager->GetFashionSlots();
    if (rFashions.AdoptFashion(wItemID))
    {
        fnAck->eResult = eFashionSucc;
        g_Game2CenterTeamC.UpFighter2Center(pUser->GetUserID(),pFighterManager->GetMainFighter()->GetID());
    }
    else
        fnAck->eResult = eFashionFailed;
    return true;
}

//接收：隐藏所选时装
bool CItemProtS::OnRecv_FashionHide(
        UINT8 byType, //0-神器时装 1-神依时装
        UINT8 byHide, //0-显示 1-隐藏
        shared_func<SFashionHideAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFashionSlots& rFashions = pFighterManager->GetFashionSlots();
    CFashionPtr pFashion = NULL;
    if (byType == 0)
        pFashion = rFashions.GetCurrW();
    else if (byType == 1)
        pFashion = rFashions.GetCurrD();

    fnAck->eResult = eFashionFailed;
    if (pFashion)
    {
        if (pFashion->GetHide() && !byHide)
        {
            pFashion->SetHide(0);
            rFashions.Update2DB(*pFashion);
            rFashions.SetDirty(false); // XXX: 外观不影响数值
            fnAck->eResult = eFashionSucc;
        }
        else if (!pFashion->GetHide() && byHide)
        {
            pFashion->SetHide(1);
            rFashions.Update2DB(*pFashion);
            rFashions.SetDirty(false); // XXX: 外观不影响数值
            fnAck->eResult = eFashionSucc;
        }
    }

    if (fnAck->eResult == eFashionSucc)
    {
        if (pPlayer->GetMap())
            pPlayer->GetMap()->AppearToSurround(*pPlayer);
        g_Game2CenterTeamC.UpFighter2Center(pUser->GetUserID(),pFighterManager->GetMainFighter()->GetID());
    }

    return true;
}

//接收：选择时装
bool CItemProtS::OnRecv_FashionChange(
        UINT64 qwInstID, //时装唯一ID
        shared_func<SFashionChangeAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFashionSlots& rFashions = pFighterManager->GetFashionSlots();
    fnAck->eResult = rFashions.ActiveFashion(qwInstID);
    if(fnAck->eResult == eFashionSucc)
    {
        g_Game2CenterTeamC.UpFighter2Center(pUser->GetUserID(), pFighterManager->GetMainFighter()->GetID());
    }
    return true;
}

//接收：时装炼化
bool CItemProtS::OnRecv_FashionUpgrade(
        UINT64 qwInstID, //时装物品ID
        UINT8 byOneKey, //是否一键
        shared_func<SFashionUpgradeAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if (!pFighterManager)
    {
        fnAck->eResult = eFashionFailed;
        return false;
    }
    CFashionSlots& rFashions = pFighterManager->GetFashionSlots();
    fnAck->eResult = rFashions.FashionUpgrade(qwInstID, byOneKey > 0);
    if(fnAck->eResult == eFashionSucc)
        g_Game2CenterTeamC.UpFighter2Center(pUser->GetUserID(),pFighterManager->GetMainFighter()->GetID());
    return true;
}
//接收：穿戴宝石
bool CItemProtS::OnRecv_WareGemStone(
        UINT16 wItemID, //宝石模板ID
        UINT64 qwFighterID, //将ID
        UINT8 byPos, //穿戴位置
        shared_func<SWareGemStoneAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        return false;
    }
    fnAck->qwFighterID = qwFighterID;
    fnAck->byPos = byPos;
    do{
        CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(qwFighterID);
        if(pFighter == NULL)
        {
            fnAck->eResult = eGemstoneHeroErr;
            break;
        }
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
        if(pHeroFighter == NULL)
        {
            fnAck->eResult = eGemstoneHeroErr;
            break;
        }
        if(!pUser->GetPack().HasItem(wItemID))
        {
            fnAck->eResult = eGemstoneNoStone;
            break;
        }
        UINT16 wStoneLevel = 0;
        fnAck->eResult = pHeroFighter->GetGemstoneSlots().Ware(wItemID,byPos,fnAck->Item,wStoneLevel);
        if(fnAck->eResult != eGemstoneSuccess)
        {
            break;
        }
        pUser->GetPack().DelItemByItemID(wItemID,1,true,NLogDataDefine::ItemTo_WareStone);

        //event

        TVecINT32 vecParam;
        vecParam.push_back(qwFighterID); 
        vecParam.push_back(wStoneLevel);

        ostringstream os;
        os<<qwFighterID<<";";
        os<<wStoneLevel<<";";

        TVecGemstonePtr vecStone;
        pHeroFighter->GetGemstoneSlots().GetGemstoneAll(vecStone);
        for(auto it = vecStone.begin(); it != vecStone.end();it++)
        {
            os<<(*it)->GetItemID()<<",";
            os<<(*it)->GetStoneLevel()<<"$";
            vecParam.push_back((*it)->GetStoneLevel());
        }

          pPlayer->OnEvent(eEventType_GemsSuit,vecParam);

    }while(0);
    if(fnAck->eResult != eGemstoneSuccess)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    else
    {
        pUser->GetTaskPkg().OnAction(*pPlayer,eProcessAction_SpecialStone);
    }
    return true;

}
//接收：取下宝石
bool CItemProtS::OnRecv_TakeOffGemStone(
        UINT64 qwFighterID, //将ID
        UINT8 byPos, //穿戴位置0~5,6表示全部卸下
        shared_func<STakeOffGemStoneAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        return false;
    }
    fnAck->qwFighterID = qwFighterID;
    fnAck->byPos = byPos;
    do{
        CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(qwFighterID);
        if(pFighter == NULL)
        {
            fnAck->eResult = eGemstoneHeroErr;
            break;
        }
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
        if(pHeroFighter == NULL)
        {
            fnAck->eResult = eGemstoneHeroErr;
            break;
        }
        fnAck->eResult = pHeroFighter->GetGemstoneSlots().Takeoff(byPos);
        if(fnAck->eResult != eGemstoneSuccess)
        {
            break;
        }

    }while(0);
    if(fnAck->eResult != eGemstoneSuccess)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;


}

//接收：合成宝石
bool CItemProtS::OnRecv_ComposeGemStone(
        UINT16 wItemID, //宝石模板ID
        UINT32 dwNum, //合成数量
        shared_func<SComposeGemStoneAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        return false;
    }
    fnAck->eResult = pUser->GetPack().MergeGenStone(wItemID,dwNum);
    if(fnAck->eResult != eGemstoneSuccess)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}
//接收：一键合成宝石
bool CItemProtS::OnRecv_ComposeGemStoneOneKey(
		const TVecGMMailItem& vecStone, //合成宝石列表
		shared_func<SComposeGemStoneOneKeyAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        return false;
    }
    EGemstoneResult eResult = eGemstoneSuccess;
    for(auto it = vecStone.begin(); it != vecStone.end();it++)
    {
        const SGMMailItem & rItem = *it;
        eResult = pUser->GetPack().MergeGenStone(rItem.wItemID,rItem.wItemCount);
        if(eResult != eGemstoneSuccess)
        {
            break;
        }
    }
    fnAck->eResult = eResult;
    if(fnAck->eResult != eGemstoneSuccess)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;

}


void CItemProtS::SendSysMsgIDNotify(EItemResult eResult)
{
    ESystemMsgID eMsg = eMsgItem;
    switch(eResult)
    {
        case eItemNotExist:
            eMsg = eMsgItemNotExistErr;
            break;
        case eItemErrBind:
            eMsg = eMsgItemBoundErr;
            break;
        case eItemStoreFull:
            eMsg = eMsgPackFullErr;
            break;
        case eItemStoreErr:
            eMsg = eMsgOtherErr;
            break;
        case eItemRangeErr:
            //eMsg = eMsg_DistanceErr;
            break;
        case eItemNoStack:
            eMsg = eMsgItemTypeStackErr;
            break;
        case eItemNoCoin:
            eMsg = eMsgGoldErr;
            break;
        case eItemCoinFull:
            //eMsg = eMsgGoldLimitErr;
            break;
        case eItemNoMoney:
            eMsg = eMsgGoldErr;
            break;
        case eItemMoneyFull:
            //eMsg = eMsg_DiamondLimitErr;
            break;
        case eItemErrOper:
            eMsg = eMsgItemErrOper;
            break;
        case eItemErrCD:
            eMsg = eMsgCooldownErr;
            break;
        case eItemErrSlot:
            eMsg = eMsgItemErrSlot;
            break;
        case eItemNotNeed:
            eMsg = eMsgItemNotNeed;
            break;
        case eItemSkillExist:
            //eMsg = eMsg_SkillExistErr;
            break;
        case eItemErrName:
            //eMsg = eMsg_NameLengthErr;
            break;
        case eItemExpired:
            eMsg = eMsgItemExpiredErr;
            break;
        case eItemErrOther:
            eMsg = eMsgOtherErr;
            break;
        case eItemErrSell:
            eMsg = eMsgItemTypeSellErr;
            break;
        case eItemErrDrop:
            eMsg = eMsgItemTypeDropErr;
            break;
        case eItemErrLevel:
            eMsg = eMsgItemLevelErr;
            break;
        case eItemErrJob:
            eMsg = eMsgItemJobErr;
            break;
        case eItemNoStuff:
            eMsg = eMsgStuffNotEnoughErr;
            break;
        case eItemErrDungeon:
            //eMsg = eMsg_ItemMapErr;
            break;
        case eItemErrTransfMap:
            //eMsg = eMsg_ItemMapErr;
            break;
        case eItemMountExist:
            //eMsg = eMsgItemMountExist;
            break;
        case eItemMutual:
            //eMsg = eMsg_ItemMutual;
            break;
        case eItemMutualEquip:
            //eMsg = eMsg_ItemMutualEquip;
            break;
        case eItemNoTakeOff:
            //eMsg = eMsg_ItemNoTakeOff;
            break;
        case eItemFashionExist:
            eMsg = eMsgItemFashionExist;
            break;
        default:
            break;
    }

    if(eMsg != eMsgItem)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsg);
}
void CItemProtS::SendSysMsgIDNotify(EGemstoneResult eResult)
{
    ESystemMsgID eMsg = eMsgItem;
    switch(eResult)
    {
        case eGemstoneSlotNotEmpty:
            eMsg = eMsgItemNotExistErr;
            break;
        case eGemstonePackFull:
            eMsg = eMsgGemstonePackFull;
            break;
        case eGemstoneMaterialLack:
            eMsg = eMsgGemstoneMaterialLack;
            break;
        case eGemstoneHasSameType:
            eMsg = eMsgGemstoneSlotSameType;
            break;
         default:
            break;
    }

    if(eMsg != eMsgItem)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsg);


}

