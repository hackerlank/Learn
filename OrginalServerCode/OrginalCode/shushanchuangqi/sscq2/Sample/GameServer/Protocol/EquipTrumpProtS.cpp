// =====================================================================================
//
//       Filename:  EquipTrumpProtS.cpp
//
//    Description:  装备法宝相关协议
//
//        Version:  1.0
//        Created:  05/18/2015 03:52:14 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  JiangLutian (JLT), jianglt@kingnet.com
//   Organization:  
//
// =====================================================================================

#include "EquipTrumpProtS.h"
//#include "FighterManager.h"

#include "EquipTrumpSlot.h"
#include "EquipTrump.h"
#include "GameNetMgr.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "FighterManager.h"
#include "Player.h"
#include "HeroFighter.h"
#include "EquipTrump.h"


CEquipTrumpProtS g_EquipTrumpProtS;

//接收：
bool CEquipTrumpProtS::OnRecv_GetAllEquipTrump(
        UINT64 qwOwnerID, //散仙唯一ID（0表示获取所有散仙法宝）
        shared_func<SGetAllEquipTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    if (!qwOwnerID)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(qwOwnerID);
    if (!pFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }
    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    if(!pHeroFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    return pHeroFighter->GetEquipTrumpSlot().GetAllInfo(fnAck->vecEquipTrump);
}

//接收：请求穿上装备法宝
bool CEquipTrumpProtS::OnRecv_Wear(
        UINT64 qwOwnerID, //散仙唯一ID
        UINT64 qwInstID, //装备法宝唯一ID
        shared_func<SWearAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    if (!qwOwnerID)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(qwOwnerID);
    if (!pFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }
    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    if(!pHeroFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    CItemPtr pItem = pUser->GetPack().GetItem(qwInstID);
    if (!pItem)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgExchangeShopErrorItemID);
        pUser->SendPkg(strPkg);
        return false;
    }

    if (!pItem->IsEquipTrumpItem())
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgExchangeShopErrorItemID);
        pUser->SendPkg(strPkg);
        return false;
    }

    CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
    if (!pEquipTrump)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgExchangeShopErrorItemID);
        pUser->SendPkg(strPkg);
        return false;
    }

    fnAck->eResult = pHeroFighter->GetEquipTrumpSlot().Wear(pEquipTrump,pFighter->GetID());
    if (fnAck->eResult == eETRSuccess)
        return true;
    else
        return false;
}

//接收：请求一键穿上装备法宝
bool CEquipTrumpProtS::OnRecv_WearOneKey(
        UINT64 qwOwnerID, //散仙唯一ID
        shared_func<SWearOneKeyAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    if (!qwOwnerID)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(qwOwnerID);
    if (!pFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }
    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    if(!pHeroFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    fnAck->eResult = pHeroFighter->GetEquipTrumpSlot().WearOneKey(pFighter->GetID());
    if (fnAck->eResult == eETRSuccess)
        return true;
    else
        return false;
}

//接收：请求脱下装备法宝
bool CEquipTrumpProtS::OnRecv_TakeOff(
        UINT64 qwInstID, //装备法宝唯一ID
        INT16 wIndex, //-1：右击脱下；其他：包裹的位置
        shared_func<STakeOffAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    if (!qwInstID)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    TVecFighterPtr vecFighter;
    if (!pPlayer->GetFighterManager()->GetAllFighters(vecFighter))
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    for (auto & pFighter : vecFighter)
    {
        if (!pFighter)
            continue;
        CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
        if(!pHeroFighter)
            continue;
        fnAck->eResult = pHeroFighter->GetEquipTrumpSlot().TakeOff(qwInstID, wIndex);
        if (fnAck->eResult == eETRSuccess)
            break;
    }
    if (fnAck->eResult == eETRSuccess)
        return true;
    else
        return false;
}

// 接收：交换法宝
bool CEquipTrumpProtS::OnRecv_Swap(
        UINT64 qwOwnerID, //散仙唯一ID
        UINT64 qwInstID, //装备法宝唯一ID
        INT16 wIndex, //-1：右击脱下；其他：包裹的位置
        shared_func<SSwapAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    if (!qwOwnerID)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgOtherErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    CFighterPtr pFighter = pPlayer->GetFighterManager()->GetFighterByInstID(qwOwnerID);
    if (!pFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }
    CHeroFighterPtr pHeroFighter = dynamic_pointer_cast<CHeroFighter>(pFighter);
    if(!pHeroFighter)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgETeamNewHeroErr);
        pUser->SendPkg(strPkg);
        return false;
    }

    CItemPtr pItem = pUser->GetPack().GetItem(qwInstID);
    if (!pItem)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgExchangeShopErrorItemID);
        pUser->SendPkg(strPkg);
        return false;
    }

    if (!pItem->IsEquipTrumpItem())
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgExchangeShopErrorItemID);
        pUser->SendPkg(strPkg);
        return false;
    }

    CEquipTrumpPtr pEquipTrump = dynamic_pointer_cast<CEquipTrump>(pItem);
    if (!pEquipTrump)
    {
        string strPkg;
        strPkg = g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgExchangeShopErrorItemID);
        pUser->SendPkg(strPkg);
        return false;
    }

    fnAck->eResult = pHeroFighter->GetEquipTrumpSlot().Swap(pEquipTrump, wIndex, pFighter->GetID());
    if (fnAck->eResult == eETRSuccess)
        return true;
    else
        return false;
}

//接收：请求合成装备法宝
bool CEquipTrumpProtS::OnRecv_MergeEquipTrump(
        UINT16 wItemID, //制作装备法宝模版ID
		UINT16 wCount, //数量
        shared_func<SMergeEquipTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    fnAck->eResult = pUser->GetPack().MergeEquipTrump(wItemID, wCount, fnAck->vecItem);
    if (fnAck->eResult == eETMRSuccess)
        return true;
    else
        return false;
}

//接收：请求分解装备法宝
bool CEquipTrumpProtS::OnRecv_BreakEquipTrump(
        const TVecUINT64& vecInstID, //物品唯一ID
        shared_func<SBreakEquipTrumpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    fnAck->eResult = pUser->GetPack().BreakEquipTrump(vecInstID, fnAck->vecItem);
    if (fnAck->eResult == eETBRSuccess)
        return true;
    else
        return false;
}

//接收：装备法宝强化
bool CEquipTrumpProtS::OnRecv_Intensify(
        UINT64 qwInstID, //装备法宝唯一ID
        ETIntensifyType eType, //强化类型
        shared_func<SIntensifyAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eETIRFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if(pFighterManager)
    {
       CEquipTrumpPtr pEquipTrump = pFighterManager->GetEquipTrumpByInstID(qwInstID);
       if(pEquipTrump)
       {
           fnAck->eResult = pEquipTrump->OnIntensify(*pUser,eType,fnAck);
       }
       else
       {
           fnAck->eResult = eETIRFailed;
       }

    }

    return true;
}

//接收：装备法宝一键强化
bool CEquipTrumpProtS::OnRecv_IntensifyOneKey(
        UINT64 qwInstID, //装备法宝唯一ID
        ETIntensifyType eType, //强化类型
        shared_func<SIntensifyOneKeyAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eETIRFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if(pFighterManager)
    {
       CEquipTrumpPtr pEquipTrump = pFighterManager->GetEquipTrumpByInstID(qwInstID);
       if(pEquipTrump)
       {
           fnAck->eResult = pEquipTrump->OnIntensifyOneKey(*pUser,eType,fnAck);
       }
       else
       {
           fnAck->eResult = eETIRFailed;
       }

    }

    return true;
}

//接收：装备法宝洗炼
bool CEquipTrumpProtS::OnRecv_ShuffleResult(
        UINT64 qwInstID, //装备法宝唯一ID
        UINT32 dwLock, //锁定属性（按位锁定 0x110 锁定2，3位）
        shared_func<SShuffleResultAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eETSRFailed;
        return false;
    }

    CFighterManagerPtr pFighterManager = pPlayer->GetFighterManager();
    if(pFighterManager)
    {
       CEquipTrumpPtr pEquipTrump = pFighterManager->GetEquipTrumpByInstID(qwInstID);
       if(pEquipTrump)
       {
           fnAck->eResult = pEquipTrump->OnShuffleResult(*pUser,dwLock);
       }
       else
       {
           fnAck->eResult = eETSRFailed;
       }

    }

    return true;
}

