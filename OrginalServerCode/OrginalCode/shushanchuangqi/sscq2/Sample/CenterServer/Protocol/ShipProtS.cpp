#include "stdafx.h"
#include "User.h"
#include "UserMgr.h"
#include "Archive.h"
#include "Protocols.h"
#include "ShipManager.h" 
#include "VarDefine.h"
#include "SysMsgDefine.h"
#include "ShipProtS.h"
#include "Parameter.h"
#include "VIPMgr.h"
#include "TaskConf.h"
//接收：获取自己显示信息
void CShipProtS::OnRecv_GetShipSelfView(
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return;
    pUser->GetShipPkg().Send2ClientSelfData();
}

//接收：获取所有金船显示信息
bool CShipProtS::OnRecv_GetShipList(
        shared_func<SGetShipListAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    g_ShipManager.GetAllShipForList(qwUsrID,fnAck->vecShip);
    return true;
}

//接收：不再关注列表
void CShipProtS::OnRecv_DelList(
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return;
    g_ShipManager.CloseNoticeShip(qwUsrID);

}

//接收：获取某条船的信息
bool CShipProtS::OnRecv_GetShipInfo(
        UINT64 qwInsID, //金船唯一ID
        shared_func<SGetShipInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    //这条船不存在
    RunShip *  pShip = g_ShipManager.GetShipByID(qwInsID);
    if(pShip == NULL)
    {
        fnAck->eResult = EShip_NoShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }

    g_ShipManager.GetPlayerShipForClient(pShip->sRunShip,fnAck->stShipInfo);
    return true;
}

//接收：获取历史信息
void CShipProtS::OnRecv_GetShipReport(
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return;
    pUser->GetShipPkg().SendShipReportList();

}

//接收：雇佣船只,开始运船
bool CShipProtS::OnRecv_OpenShip(
        shared_func<SOpenShipAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    //是否刷船
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    if(pSelfData.wReflushShip == 0)
    {
        fnAck->eResult = EShip_NoFlushShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }
    //开船次数是否足够
    if(pUser->GetCenterVar().GetVar(NVarDefine::ePlayerShipOpenTimes) >= SParamConfig::byShipDailyTime)
    {
        if(pSelfData.dwBuyOpenShipTimes == 0)
        {
            fnAck->eResult = EShip_DriveOverLimit;
            SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
            return true;

        }
    }
    //有无船在航行
    if(g_ShipManager.GetShipByOwer(qwUsrID) > 0)
    {
        fnAck->eResult = EShip_DriveHasShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }
    //开船
    if(!g_ShipManager.OpenShip(*pUser))
    {
        fnAck->eResult = EShip_OtherErr;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }
    //更新玩家信息
    if(pUser->GetCenterVar().GetVar(NVarDefine::ePlayerShipOpenTimes) >= SParamConfig::byShipDailyTime)
    {
        if(pSelfData.dwBuyOpenShipTimes > 0)
        {
            pSelfData.dwBuyOpenShipTimes--;

        }
    }
    pUser->GetCenterVar().AddVar(NVarDefine::ePlayerShipOpenTimes,1);
    if(pSelfData.qwInviteDefense > 0 && time(NULL) < pSelfData.dwInviteDefenseAgreeTime + dwAgreeTime)
    {
        //护送者肯定在
        CUserPtr pOtherUser = CUserMgr::GetUserByUserID(pSelfData.qwInviteDefense);
        if(pOtherUser ==NULL)
        {
            LOG_CRI << "Defense exist";
        }
        else
        {
            pOtherUser->GetCenterVar().AddVar(NVarDefine::ePlayerShipDefenseTimes,1);
            PlayerSelfShipData& pOtherData =  pOtherUser->GetShipPkg().GetSelfData();
            pOtherData.qwAgreeDefenseShipOwer = 0;
            pOtherData.dwAgreeDefenseShipOwerTime = 0;
            pOtherUser->GetShipPkg().Update2DBSelfData();
            if(pOtherUser->IsOnLine())
            {
                pOtherUser->GetShipPkg().Send2ClientSelfData();
            }
        }


    }
    const SShipCFG *  pCfg = g_ShipManager.GetConfigById(pSelfData.wReflushShip);
    if(pCfg)
    {
        if(pCfg->_Color >= 4)
        {
            TVecString vecStr;
            vecStr.push_back(NumberToString(pUser->GetColor()));
            vecStr.push_back(pUser->GetUserName());
            vecStr.push_back(NumberToString(pCfg->_Color));
            vecStr.push_back(pCfg->_Name);
            g_GlobalChatProtS. SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgShip4OverStar,vecStr);
        }
        if(pCfg->_Color >= 5)
        {
            TVecString vecStr;
            vecStr.push_back(NumberToString(pUser->GetColor()));
            vecStr.push_back(pUser->GetUserName());
            vecStr.push_back(NumberToString(pCfg->_Color));
            vecStr.push_back(pCfg->_Name);
            g_GlobalChatProtS. SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgShip5Star,vecStr);
        }
    }


    //
    pSelfData.wReflushShip = 0; //刷出来的船
    pSelfData.qwInviteDefense = 0; //邀请的护送者
    pSelfData.dwInviteDefenseAgreeTime = 0; //别人同意护送的时间
    pSelfData.dwInviteDefensePoint = 0; //护送者战斗力
    pSelfData.byInviteDefenseLevel = 0; //护送者等级
    pSelfData.byInviteDefenseColor = 0; //护送者颜色
    pUser->GetShipPkg().Update2DBSelfData();
    pUser->GetShipPkg().Send2ClientSelfData();
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ActionNotify(&dwServerID,1,pUser->GetUserID(),eProcessAction_OpenShip);
    return true;


}

//接收：购买运船次数
bool CShipProtS::OnRecv_BuyOpenShipTimes(
        shared_func<SBuyOpenShipTimesAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    //今日购买的运船次数
    UINT32 dwTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerBuyOpenShipTimesToday);
    UINT32  dwCost = SParamConfig::byShipTimeBuy +  dwTimes* SParamConfig::byShipTimeBuyGrowth;
    //VIP
    //察钱
    const SVIPLevelCFGEx* pVipCfg = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
    if(!pVipCfg || dwTimes >= pVipCfg->_ShipTime)
    {
        fnAck->eResult = EShip_GetShipOneKeyNoVip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    if(pUser->GetGold() < dwCost)
    {
        fnAck->eResult = EShip_BuyOpenGoldLimit;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    //扣钱
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwUsrID,NLogDataDefine::ItemTo_ByOpenShipTimes,NProtoCommon::EMONEY_GOLD,dwCost);
    pUser->GetCenterVar().AddVar(NVarDefine::ePlayerBuyOpenShipTimesToday,1);
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    pSelfData.dwBuyOpenShipTimes++;
    pUser->GetShipPkg().Update2DBSelfData();
    pUser->GetShipPkg().Send2ClientSelfData();
    return true;
}

//接收：购买抢劫次数
bool CShipProtS::OnRecv_BuyRoBShipTimes(
        shared_func<SBuyRoBShipTimesAck>& fnAck //返回回调函数
        ) 
{
    return false;
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    UINT32 dwTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerBuyRoBShipTimesToday);
    UINT32  dwCost = SParamConfig::byShipRobTimeBuy +  dwTimes* SParamConfig::byShipRobTimeBuyGrowth;
    //察钱
    if(pUser->GetGold() < dwCost)
    {
        fnAck->eResult = EShip_BuyRobGoldLimit;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    //扣钱
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwUsrID,NLogDataDefine::ItemTo_ByRobShipTimes,NProtoCommon::EMONEY_GOLD,dwCost);
    pUser->GetCenterVar().AddVar(NVarDefine::ePlayerBuyRoBShipTimesToday,1);
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    pSelfData.dwBuyRoBShipTimes++;
    pUser->GetShipPkg().Update2DBSelfData();
    pUser->GetShipPkg().Send2ClientSelfData();
    return true;


}
//接收：购买刷新次数
bool CShipProtS::OnRecv_BuyReflushShipTimes(
        shared_func<SBuyReflushShipTimesAck>& fnAck //返回回调函数
        ) 
{
    /*
       UINT64 qwUsrID = GetCurUsrID();
       CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
       if(!pUser)
       return false;
       UINT32 dwTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerBuyReflushShipTimesToday);
       UINT32 dwCost = SParamConfig::byShipChanceCost +  dwTimes* SParamConfig::byShipChanceCostGrowth;
    //察钱
    if(pUser->GetGold() < dwCost)
    {
    fnAck->eResult = EShip_RelushGoldLimit;
    SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
    return true;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();
    //扣钱
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwUsrID,NLogDataDefine::ItemTo_ByReFlushShipTimes,NProtoCommon::EMONEY_GOLD,dwCost);
    pUser->GetCenterVar().AddVar(NVarDefine::ePlayerBuyReflushShipTimesToday,1);
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    pSelfData.dwBuyReflushShipTimes++;
    pUser->GetShipPkg().Update2DBSelfData();
    pUser->GetShipPkg().Send2ClientSelfData();
    */
    return true;

}

//接收：刷新船只
bool CShipProtS::OnRecv_ReFlushShip(
        UINT8 byVip, //0,表示非vip ,非0表示vip
        shared_func<SReFlushShipAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    //是否不记次数
    UINT16 wShipID = 0;
    bool bCost = true;
    UINT32 dwCost = 0;
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    //VIP
    if(byVip == 0)
    {
        UINT8 byLowColor = 0;
        if(pSelfData.wReflushShip == 0)
        {
            bCost = false;
        }
        else
        {
            const SShipCFG *  pCfg = g_ShipManager.GetConfigById(pSelfData.wReflushShip);
            if(pCfg)
            {
                byLowColor = pCfg->_Color;
            }
        }

        if(bCost)
        {
            UINT32 dwTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerBuyReflushShipTimesToday);
            dwCost = SParamConfig::byShipChanceCost +  dwTimes* SParamConfig::byShipChanceCostGrowth;
            //察钱
            const SVIPLevelCFGEx* pVipCfg = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
            if(!pVipCfg || pVipCfg->_ShipRefresh == 0)
            {
                fnAck->eResult = EShip_GetShipOneKeyNoVip;
                SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
                return true;
            }

            if(pUser->GetGold() < dwCost)
            {
                fnAck->eResult = EShip_RelushGoldLimit;
                SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
                return true;
            }
        }
        wShipID = g_ShipManager.ReFlushShip(*pUser,byLowColor);
    }
    else
    {
        //检查vip
        const SVIPLevelCFGEx* pVipCfg = VIPMgr.GetVIPLevelCfg(pUser->GetVIPLevel());
        if(pVipCfg == NULL || pVipCfg->_ShipGet == 0)
        {
            fnAck->eResult = EShip_GetShipOneKeyNoVip;
            SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
            return true;
        }
        //检查钱
        dwCost = SParamConfig::wShipGetYellow;
        if(pUser->GetGold() < dwCost)
        {
            fnAck->eResult = EShip_FinishOneKeyNoGold;
            SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
            return true;
        }
        //刷船
        wShipID = g_ShipManager.ReFlushShipByVip(*pUser,pVipCfg->_ShipGet);

    }
    if(wShipID == 0)
    {
        fnAck->eResult = EShip_RelushShipUpLimit;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    if(bCost && dwCost > 0)
    {
        UINT32 dwServerID = pUser->GetGameSvrID();
        //扣钱
        if(byVip == 0)
        {
            g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwUsrID,NLogDataDefine::ItemTo_ByReFlushShipTimes,NProtoCommon::EMONEY_GOLD,dwCost);
            pUser->GetCenterVar().AddVar(NVarDefine::ePlayerBuyReflushShipTimesToday,1);
        }
        else
        {
            g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwUsrID,NLogDataDefine::ItemTo_GetShipOneKey,NProtoCommon::EMONEY_GOLD,dwCost);

        }
    }
    pSelfData.wReflushShip = wShipID;
    pSelfData.dwReflushShipTimer = time(NULL);
    pUser->GetShipPkg().Update2DBSelfData();
    pUser->GetShipPkg().Send2ClientSelfData();
    fnAck->wShipId = wShipID;
    TVecINT32 vecParam;
    vecParam.push_back(1);
    pUser->OnEvent(eEventType_BoatRefresh,vecParam);
    pUser->OnEvent(eEventType_BoatGet,vecParam);
    return true;

}

//接收：邀请护送船只
bool CShipProtS::OnRecv_InViteFriend(
        UINT64 qwFriend, //好友
        shared_func<SInViteFriendAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    if(qwFriend == qwUsrID)
    {
        fnAck->eResult = EShip_OtherErr;    
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID); 
        return true;

    }
    //self
    //无船不可邀请
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    if(pSelfData.wReflushShip == 0)
    {
        fnAck->eResult = EShip_NoFlushShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }
    //已有玩家同意不可邀请
    if(pSelfData.qwInviteDefense >0 && time(NULL) < pSelfData.dwInviteDefenseAgreeTime + dwAgreeTime )
    {
        fnAck->eResult = EShip_DeFenseIsAgree;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //有船在开不可邀请
    if(g_ShipManager.GetShipByOwer(qwUsrID) > 0)
    {
        fnAck->eResult = EShip_DriveHasShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //friend
    //不在线不可邀请
    CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwFriend);
    if(!pOtherUser || !pOtherUser->IsOnLine())
    {
        fnAck->eResult = EShip_InviteDeFenseOffLine;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //已同意别的玩家不可邀请
    PlayerSelfShipData& pOtherData =  pOtherUser->GetShipPkg().GetSelfData();
    if(pOtherData.qwAgreeDefenseShipOwer > 0 && time(NULL) < pOtherData.dwAgreeDefenseShipOwerTime + dwAgreeTime)
    {
        fnAck->eResult = EShip_DeFenseAgreeOther;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //已护送护送其他船不可接受邀请
    if(g_ShipManager.GetShipByDefense(qwFriend) > 0)
    {
        fnAck->eResult = EShip_DeFenseOtherShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //护送次数用完不可接受邀请
    UINT32 dwTimes = pOtherUser->GetCenterVar().GetVar(NVarDefine::ePlayerShipDefenseTimes);
    if(dwTimes >= SParamConfig::byShipDailyProtectTime)
    {
        fnAck->eResult = EShip_OtherDeFenseTimesOut;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //TODO:发送泡泡
    UINT32 dwServerID = pOtherUser->GetGameSvrID();
    TVecINT64 vecFriend;
    vecFriend.push_back(qwUsrID);
    vecFriend.push_back(pSelfData.dwReflushShipTimer);
    TVecString vecString;
    vecString.push_back(pUser->GetUserName());
    const SShipCFG *  pCfg = g_ShipManager.GetConfigById(pSelfData.wReflushShip);
    if(pCfg)
        vecString.push_back(pCfg->_Name);
    g_Game2CenterCommS.SendSvr_BubbleNotify(&dwServerID,1,qwFriend,NProtoCommon::eOpAdd,10,vecFriend,vecString);
    return true;

}

//接收：回应邀请护送船只
bool CShipProtS::OnRecv_InViteOtherAgree(
        UINT8 bySuc, //0,同意，1拒绝
        UINT64 qwFriend, //好友
        UINT32 dwCode, //验证码
        shared_func<SInViteOtherAgreeAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwFriend);
    do{
        if(qwFriend == qwUsrID)
        {
            fnAck->eResult = EShip_OtherErr;
            break;
        }
        if(bySuc == 1)
        {
            fnAck->eResult = EShip_DeFenseDisAgree2;
            break;
        }
        //friend
        //不在线不可邀请
        if(!pOtherUser || !pOtherUser->IsOnLine())
        {
            fnAck->eResult = EShip_InviteDeFenseOffLine2;
            break;
        }
        //已同意别的玩家不可邀请
        PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
        if(pSelfData.qwAgreeDefenseShipOwer > 0 && time(NULL) < pSelfData.dwAgreeDefenseShipOwerTime + dwAgreeTime)
        {
            fnAck->eResult = EShip_DeFenseAgreeOther2;
            break;
        }
        //已护送护送其他船不可接受邀请
        if(g_ShipManager.GetShipByDefense(qwUsrID) > 0)
        {
            fnAck->eResult = EShip_DeFenseOtherShip2;
            break;
        }
        //护送次数用完不可接受邀请
        UINT32 dwTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerShipDefenseTimes);
        if(dwTimes >= SParamConfig::byShipDailyProtectTime)
        {
            fnAck->eResult = EShip_OtherDeFenseTimesOut2;
            break;
        }

        PlayerSelfShipData& pOtherData =  pOtherUser->GetShipPkg().GetSelfData();
        if(pOtherData.wReflushShip == 0)
        {
            fnAck->eResult = EShip_NoFlushShip2;
            break;

        }
        if(pOtherData.dwReflushShipTimer != dwCode)
        {
            fnAck->eResult = EShip_NoFlushShip2;
            break;
        }
        //已有玩家同意不可邀请
        if(pOtherData.qwInviteDefense >0 && time(NULL) < pOtherData.dwInviteDefenseAgreeTime + dwAgreeTime )
        {
            fnAck->eResult = EShip_DeFenseIsAgree2;
            break;
        }
        //有船在开不可邀请
        if(g_ShipManager.GetShipByOwer(qwFriend) > 0)
        {
            fnAck->eResult = EShip_DriveHasShip2;
            return true;
        }

    }while(0);
    if(fnAck->eResult == EShip_Suc)//建立护送关系
    {
        PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
        pSelfData.qwAgreeDefenseShipOwer = qwFriend;
        pSelfData.dwAgreeDefenseShipOwerTime = time(NULL);
        pUser->GetShipPkg().Update2DBSelfData();
        PlayerSelfShipData& pOtherData =  pOtherUser->GetShipPkg().GetSelfData();
        pOtherData.qwInviteDefense = pUser->GetUserID(); //邀请的护送者
        pOtherData.dwInviteDefenseAgreeTime = time(NULL); //别人同意护送的时间
        pOtherData.dwInviteDefensePoint = pUser->GetFighterPower(); //护送者战斗力
        pOtherData.byInviteDefenseLevel = pUser->GetLevel(); //护送者等级
        pOtherData.byInviteDefenseColor = pUser->GetColor(); //护送者颜色
        pOtherUser->GetShipPkg().Update2DBSelfData();
    }
    if(pOtherUser && pOtherUser->IsOnLine())
    {
        EShipResult eResult = EShip_Suc;
        switch(fnAck->eResult)
        {
            case EShip_DeFenseDisAgree2:
                {
                    eResult = EShip_DeFenseDisAgree;
                }
                break;
            case EShip_OtherErr:
                {
                    eResult = EShip_OtherErr;
                }
                break;
            case EShip_DeFenseIsAgree2:
                {
                    eResult = EShip_DeFenseIsAgree;
                }
                break;
            case EShip_DriveHasShip2:
                {
                    eResult = EShip_DriveHasShip;
                }
                break;
            case EShip_InviteDeFenseOffLine2:
                {
                    eResult = EShip_InviteDeFenseOffLine;
                }
                break;
            case EShip_DeFenseAgreeOther2:
                {
                    eResult = EShip_DeFenseAgreeOther;
                }
                break;
            case EShip_DeFenseOtherShip2:
                {
                    eResult = EShip_DeFenseOtherShip;
                }
                break;
            case EShip_OtherDeFenseTimesOut2:
                {
                    eResult = EShip_OtherDeFenseTimesOut;
                }
                break;
            case EShip_NoFlushShip2:
                {
                    eResult = EShip_NoFlushShip;
                }
            default:
                break;
        }
        if(eResult != EShip_Suc)
        {
            SendSysMsgIDNotify(eResult,pOtherUser->GetUserID());
        }
        pOtherUser->SendPkg(BuildPkg_InviteAnswer(qwUsrID,pUser->GetUserName(),pUser->GetColor(),eResult));
    }
    if(fnAck->eResult != EShip_Suc && fnAck->eResult != EShip_DeFenseDisAgree2)
    {
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
    }
    return true;
}

//接收：船主踢出护送者
bool CShipProtS::OnRecv_FireDefense(
        UINT64 qwFriend, //好友
        shared_func<SFireDefenseAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    //没有建立护卫关系
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    if(qwFriend == 0 || pSelfData.qwInviteDefense != qwFriend || time(NULL) > pSelfData.dwInviteDefenseAgreeTime + dwAgreeTime)
    {
        fnAck->eResult = EShip_DeFenseErrFriend;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    CUserPtr pOtherUser = CUserMgr::GetUserByUserID(qwFriend);
    if(pOtherUser == NULL)
    {
        LOG_CRI << "Friend NOTExit";
        fnAck->eResult = EShip_OtherErr;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    PlayerSelfShipData& pOtherData = pOtherUser->GetShipPkg().GetSelfData();
    pOtherData.qwAgreeDefenseShipOwer = 0;
    pOtherData.dwAgreeDefenseShipOwerTime = 0;
    pOtherUser->GetShipPkg().Update2DBSelfData();
    if(pOtherUser->IsOnLine())
    {
        pOtherUser->GetShipPkg().Send2ClientSelfData();
    }
    pSelfData.qwInviteDefense = 0; //邀请的护送者
    pSelfData.dwInviteDefenseAgreeTime = 0; //别人同意护送的时间
    pSelfData.dwInviteDefensePoint = 0; //护送者战斗力
    pSelfData.byInviteDefenseLevel = 0; //护送者等级
    pSelfData.byInviteDefenseColor = 0; //护送者颜色
    pUser->GetShipPkg().Update2DBSelfData();
    pUser->GetShipPkg().Send2ClientSelfData();
    return true;
}

//接收：打劫船只
bool CShipProtS::OnRecv_DoRoBShip(
        UINT64 qwInsID, //金船唯一ID
        shared_func<SDoRoBShipAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
    //打劫次数用完
    UINT32 dwRobTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerShipRobTimes);
    if(dwRobTimes >= SParamConfig::byShipDailyRobTime)
    {
        if(pSelfData.dwBuyRoBShipTimes == 0)
        {
            fnAck->eResult = EShip_ROBOverLimit;
            SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
            return true;
        }
    }
    //船不存在
    RunShip *pShip =  g_ShipManager.GetShipByID(qwInsID);
    if(pShip == NULL)
    {
        fnAck->eResult = EShip_NoShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }

    //船被锁定
    if(pShip->HasLock())
    {
        return false;
    }
    //你是船主或护卫
    if(pShip->sRunShip.qwOwer == qwUsrID || pShip->sRunShip.qwDefense == qwUsrID)
    {
        fnAck->eResult = EShip_ROBSelf;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }
    //这条船被打劫次数已满
    TSetUINT64 setRoB;
    g_ShipManager.GetRobID(pShip->sRunShip,setRoB);
    if(setRoB.size() >= 3)
    {
        fnAck->eResult = EShip_ROBOverShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }

    LOG_CRI << "setRoB size is " << setRoB.size();
    //这条船已被你打劫
    if(setRoB.find(qwUsrID) != setRoB.end())
    {
        fnAck->eResult = EShip_ROBDone;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //战斗冷却
    UINT32 dwNow = time(NULL);
    if(dwNow < pUser->GetCenterVar().GetVar(NVarDefine::ePlayerFreezShipTimer) + SParamConfig::byShipBattleFailCD)
    {
        fnAck->eResult = EShip_BattleCool;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //你被锁定
    if(!pUser->GetOpLock().AddLock(eLock_Ship))
    {
        return false;
    }
    //锁船
    if(!pShip->Lock())
    {
        return false;
    }
    LOG_CRI << "Lock Ship";
    //开始战斗
    UINT32 dwServerID = pUser->GetGameSvrID();
    UINT64 qwEnemyID =  pShip->sRunShip.qwDefense > 0 ? pShip->sRunShip.qwDefense : pShip->sRunShip.qwOwer;
    g_Game2CenterCommS.SendSvr_FigtherToOther(&dwServerID, 1, qwUsrID, qwEnemyID,0,NBattleGS::EBShip,0,0,0,
            [this,fnAck,qwUsrID,qwInsID](UINT8 byRet_,UINT8 byRet,UINT8 bySuc, UINT64 qwBattleID, UINT32 dwSelfFighterPower, UINT8 bySelfQuality, UINT32 dwOtherFighterPower, UINT8 byOtherQuality, UINT32  wRetuns ){

            CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
            if(pUser == NULL)
            {
            fnAck->eResult = EShip_OtherErr;
            fnAck(false);
            return ;
            }
            pUser->GetOpLock().UnLock(eLock_Ship);
            RunShip *pShip =  g_ShipManager.GetShipByID(qwInsID);
            if(pShip == NULL)
            {
            fnAck->eResult = EShip_NoShip;
            fnAck(true);
            SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
            return ;
            }
            pShip->UnLock();
            LOG_CRI << "UnLOCK Ship";
            if(byRet_!= 0 && byRet != 0)
            {
                fnAck->eResult = EShip_OtherErr;
                SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
                fnAck(true);
                return;
            }

            TVecINT32 vecParam;
            vecParam.push_back(bySuc+1);
            pUser->OnEvent(eEventType_BoatRob,vecParam);
            g_ShipManager.RobShip(qwInsID,*pUser,bySuc > 0 ? NBattleGS::EBResultAttackWin : NBattleGS::EBResultDefenseWin,qwBattleID);
            PlayerSelfShipData& pSelfData =  pUser->GetShipPkg().GetSelfData();
            UINT32 dwRobTimes = pUser->GetCenterVar().GetVar(NVarDefine::ePlayerShipRobTimes);
            if(dwRobTimes >= SParamConfig::byShipDailyRobTime)
            {
                if(pSelfData.dwBuyRoBShipTimes > 0)
                {
                    pSelfData.dwBuyRoBShipTimes--;
                    pUser->GetShipPkg().Update2DBSelfData();
                }
            }
            LOG_CRI << "RoB Ship";
            pUser->GetCenterVar().AddVar(NVarDefine::ePlayerShipRobTimes,1);
            if(bySuc == 0)
            {
                pUser->GetCenterVar().SetVar(NVarDefine::ePlayerFreezShipTimer,time(NULL));
            }
            if(pUser->IsOnLine())
            {
                pUser->GetShipPkg().Send2ClientSelfData();
            }
            fnAck->bySuc = bySuc;
            fnAck(true);
            });

    return true;


}
//接收：返抢
bool CShipProtS::OnRecv_DoGrapShip(
        UINT64 qwShipID, //金船唯一ID
        UINT64 qwRoBID, //打劫者ID
        shared_func<SDoGrapShipAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    //船不存在
    RunShip *pShip =  g_ShipManager.GetShipByID(qwShipID);
    if(pShip == NULL)
    {
        fnAck->eResult = EShip_NoShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //船被锁定
    if(pShip->HasLock())
    {
        return false;
    }
    //你不是船主 也 不是护卫
    if(pShip->sRunShip.qwOwer !=  qwUsrID && pShip->sRunShip.qwDefense != qwUsrID)
    {
        fnAck->eResult = EShip_GRABErrOwer;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;

    }
    //打劫者不正确
    TSetUINT64 setRoB;
    g_ShipManager.GetRobID(pShip->sRunShip,setRoB);
    if(setRoB.find(qwRoBID) == setRoB.end())
    {
        fnAck->eResult = EShip_GRABErr;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //战斗冷却
    UINT32 dwNow = time(NULL);
    if(dwNow < pUser->GetCenterVar().GetVar(NVarDefine::ePlayerFreezShipTimer) + SParamConfig::byShipBattleFailCD)
    {
        fnAck->eResult = EShip_BattleCool;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //你被锁定
    if(!pUser->GetOpLock().AddLock(eLock_Ship))
    {
        return false;
    }
    //锁船
    if(!pShip->Lock())
    {
        return false;
    }
    //开始战斗
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_FigtherToOther(&dwServerID, 1, qwUsrID, qwRoBID,0,NBattleGS::EBShip,0,0,0,
            [this,fnAck,qwUsrID,qwShipID,qwRoBID](UINT8 byRet_,UINT8 byRet,UINT8 bySuc, UINT64 qwBattleID, UINT32 dwSelfFighterPower, UINT8 bySelfQuality, UINT32 dwOtherFighterPower, UINT8 byOtherQuality, UINT32  wRetuns ){

            CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
            if(pUser == NULL)
            {
            fnAck->eResult = EShip_OtherErr;
            fnAck(false);
            return ;
            }
            pUser->GetOpLock().UnLock(eLock_Ship);
            RunShip *pShip =  g_ShipManager.GetShipByID(qwShipID);
            if(pShip == NULL)
            {
            fnAck->eResult = EShip_NoShip;
            fnAck(true);
            SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
            return ;
            }
            pShip->UnLock();
            if(byRet_!= 0 && byRet != 0)
            {
                fnAck->eResult = EShip_OtherErr;
                SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
                fnAck(true);
                return;
            }
            g_ShipManager.GrabShip(qwShipID,*pUser,qwRoBID,bySuc > 0 ? NBattleGS::EBResultAttackWin : NBattleGS::EBResultDefenseWin,qwBattleID);
            if(bySuc == 0)
            {
                pUser->GetCenterVar().SetVar(NVarDefine::ePlayerFreezShipTimer,time(NULL));
            }
            if(pUser->IsOnLine())
            {
                pUser->GetShipPkg().Send2ClientSelfData();
            }
            fnAck->bySuc = bySuc;
            fnAck(true);
            });
    return true;
}
//接收：一键完成运送
bool CShipProtS::OnRecv_FinishShipOneKey(
        shared_func<SFinishShipOneKeyAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(!pUser)
        return false;
    UINT64 qwShipID = g_ShipManager.GetShipByOwer(qwUsrID);
    if(qwShipID == 0)
    {
        fnAck->eResult = EShip_NoShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //船不存在
    RunShip *pShip =  g_ShipManager.GetShipByID(qwShipID);
    if(pShip == NULL)
    {
        fnAck->eResult = EShip_NoShip;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //船被锁定
    if(pShip->HasLock())
    {
        return false;
    }
    UINT32 dwNow = time(NULL);
    //查时间
    if(pShip->sRunShip.dwEndTimer <= dwNow)
    {
        return false;
    }
    UINT32 dwMins = (pShip->sRunShip.dwEndTimer - dwNow)%60 == 0 ?(pShip->sRunShip.dwEndTimer - dwNow)/60 : (pShip->sRunShip.dwEndTimer - dwNow)/60 + 1;
    UINT32 dwCost = dwMins * SParamConfig::wShipFastCost;
    if(pUser->GetGold() < dwCost)
    {
        fnAck->eResult = EShip_FinishOneKeyNoGold;
        SendSysMsgIDNotify(fnAck->eResult,qwUsrID);
        return true;
    }
    //扣钱
    UINT32 dwServerID = pUser->GetGameSvrID();
    g_Game2CenterCommS.SendSvr_ReduceItem(&dwServerID,1,qwUsrID,NLogDataDefine::ItemTo_FinishShipOneKey,NProtoCommon::EMONEY_GOLD,dwCost);
    g_ShipManager.FinishShip(qwShipID);
    pUser->GetShipPkg().Send2ClientSelfData();
    return true;
}

void CShipProtS::SendSysMsgIDNotify(EShipResult eResult,UINT64 qwRoleID)
{
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwRoleID);
    if(NULL == pUser)
    {
        return ;
    }
    UINT32 dwServerID = pUser->GetGameSvrID();

    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case EShip_NoFlushShip: //你没有刷船
            {
                eMsgID = eMsgNoFlushShip; 
            }
            break;
        case EShip_NoFlushShip2: //邀请你的人没有刷船
            {
                eMsgID = eMsgNoFlushShip2;
            }
            break;
        case EShip_DeFenseIsAgree: //已经有人同意帮你护送
            {
                eMsgID = eMsgDeFenseIsAgree;
            }
            break;
        case EShip_DeFenseIsAgree2: //已经有人同意帮船主护送
            {
                eMsgID = eMsgDeFenseIsAgree2;
            }
            break;
        case EShip_DriveHasShip: //你的船已开
            {
                eMsgID = eMsgDriveHasShip;
            }
            break;
        case EShip_DriveHasShip2: //邀请你的人的船已开
            {
                eMsgID = eMsgDriveHasShip2;
            }
            break;
        case EShip_InviteDeFenseOffLine: //你邀请的人不在线
            {
                eMsgID = eMsgInviteDeFenseOffLine;
            }
            break;
        case EShip_InviteDeFenseOffLine2: //船主不在线
            {
                eMsgID = eMsgInviteDeFenseOffLine2;
            }
            break;
        case EShip_DeFenseAgreeOther: //你邀请的人答应护送其他船
            {
                eMsgID = eMsgDeFenseAgreeOther;
            }
            break;
        case EShip_DeFenseAgreeOther2: //你已答应护送其他船
            {
                eMsgID = eMsgDeFenseAgreeOther2;
            }
            break;
        case EShip_DeFenseOtherShip: //你邀请的人在护送其他船
            {
                eMsgID = eMsgDeFenseOtherShip;
            }
            break;
        case EShip_DeFenseOtherShip2: //你在护送其他船
            {
                eMsgID = eMsgDeFenseOtherShip2;
            }
            break;
        case EShip_OtherDeFenseTimesOut: //你邀请的人护送次数用完
            {
                eMsgID = eMsgOtherDeFenseTimesOut;
            }
            break;
        case EShip_OtherDeFenseTimesOut2: //你的护送次数用完
            {
                eMsgID = eMsgOtherDeFenseTimesOut2;
            }
            break;
        case EShip_DeFenseDisAgree: //邀请的人不同意帮你护送
            {
                eMsgID = eMsgDeFenseDisAgree;
            }
            break;
        case EShip_DeFenseErrFriend: //他不是你的护卫
            {
                eMsgID = eMsgDeFenseErrFriend;
            }
            break;
        case EShip_BuyOpenGoldLimit: //购买运船仙石不足
        case EShip_BuyRobGoldLimit: //购买抢劫仙石不足
        case EShip_RelushGoldLimit: //购买刷新次数仙石不足
        case EShip_FinishOneKeyNoGold:
        case  EShip_GetShipOneKeyNoGold:
            {
                eMsgID = eMsgGoldErr;
            }
            break;
        case EShip_DriveOverLimit: //今日开船到达上限
            {
                eMsgID = eMsgDriveOverLimit;
            }
            break;
        case EShip_ROBOverLimit: //今日抢劫次数到达上限
            {
                eMsgID = eMsgROBOverLimit;
            }
            break;
        case EShip_ROBOverShip: //这条船被抢劫次数到达上限
            {
                eMsgID = eMsgROBOverShip;
            }
            break;
        case EShip_ROBDone: //这条船你已经打劫
            {
                eMsgID = eMsgROBDone;
            }
            break;
        case EShip_ROBSelf: //这条船被你护卫或者是你的，不可抢劫
            {
                eMsgID = eMsgROBSelf;
            }
            break;
        case EShip_GRABErrOwer: //这条船不是你的或者你不是护卫，不可返抢
        case EShip_GRABErr: //返抢对手错误
            {
                eMsgID = eMsgGRABErr; 
            }
            break;
        case EShip_BattleCool: //战斗冷却
            {
                eMsgID = eMsgBattleCool;
            }
            break;
        case EShip_GetShipOneKeyNoVip:
            {
                eMsgID = eMsgVIPLevelTooLow;
            }
            break;
        case EShip_OtherErr: //其他错误
        case EShip_NoShip: //船不存在
            {
                eMsgID = eMsgOtherErr;
            }
            break;
        default:
            break;

    }
    if(eMsgID != eMsgSuccess)
    {
        g_Game2CenterCommS.SendSvr_SendSysMsg(&dwServerID,1,qwRoleID,eMsgID);

    }
}
