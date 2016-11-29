#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "DungeonMgr.h"
#include "PlayerDgn.h"
#include "GameNetMgr.h"

void CDungeonProtS::SystemMsgNotify(EDungeonResult result,UINT64 qwUserId )
{
    UINT16 wMsgId =0;
    switch(result)
    {
        case eDungeonSweepingErr: //正在扫荡中    
            {
                wMsgId = eMsgDungeonSweepingErr;
            }
            break;
        case eDungeonPowerErr: //体力不足    
            {
                wMsgId = eMsgDungeonPowerErr;
            }
            break;
        case eDungeonNotSweepingErr: //不在扫荡中    
            {
                wMsgId =eMsgDungeonNotSweepingErr;
            }
            break;
        case eDungeonSweepingSpeedUpErr: //扫荡加速中    
            {
                wMsgId = eMsgDungeonSweepingSpeedUpErr;
            }
            break;
        case eDungeonTypeNotExist: //此副本类型不存在    
            {
                wMsgId = eMsgDungeonTypeNotExist;
            }
            break;
        case eDungeonInDgn: //你在副本中    
            {
                wMsgId =  eMsgDungeonInDgn;
            }
            break;
        case eDungeonLowLevel: //你等级不够   
            {
                wMsgId = eMsgDungeonLowLevel;
            }
            break;
        case eDungeonCreateErrType: //副本类型不正确，不可以创建副本    
            {
                wMsgId = eMsgDungeonCreateErrType;
            }
            break;
        case eDungeonPreDgnNotFinish: //前置副本未完成    
            {
                wMsgId = eMsgDungeonPreDgnNotFinish;
            }
            break;
            /*
               case eDungeonPackEmptyMin: //包裹空格子不足
               {

               wMsgId = eMsgDgnLackPack;    
               }
               break;
               */
        case eDungeonOutDgn: //你不在副本中 
            {
                wMsgId = eMsgDungeonOutDgn;
            }
            break;
        case eDungeonInsNotExist: //副本不存在   
            {
                wMsgId = eMsgDungeonInsNotExist;
            }
            break;
        case eDungeonNotFinish: //副本未完成  
            {
                wMsgId  = eMsgDungeonNotFinish;
            }
            break;
        case eDungeonBusy: //玩家忙 
            {
                wMsgId =eMsgDungeonBusy;
            }
            break;
        case eDungeonNotSweeping: //不在扫荡状态    
            {
                wMsgId =eMsgDungeonNotSweeping;
            }
            break;
        case eDungeonOtherErr: //未知错误 
            {
                wMsgId = eMsgDungeonOtherErr;
            }
            break;
        case eSpeedUpItemLimit:
            {
                wMsgId = eMsgDungeonSpeedUpItemLimit;
            }
            break;
        case eDungeonTimesLimit:
            {
                wMsgId = eMsgLackCopyTimes;
            }
            break;
        case eDungeonTimesLimitForHero:
            {
                wMsgId = eHeroDungeonFreeTimesLack;
            }
            break;
        case eDungeonTimesLimitForLiXian:
            {
                wMsgId = eAdventureDungeonFreeTimesLack;
            }
            break;
        case eDungeonVipBuyHero:
            {
                wMsgId = eHeroDungeonBoughtTimesLack;
            }
            break;
        case eDungeonVipBuyLiXian:
            {
                wMsgId = eAdventureDungeonBoughtTimesLack;
            }
            break;
        default:
            break;

    }
    if(wMsgId != 0)
    {
        if(qwUserId == 0)
        {
            //Send_SystemFormatMsgIDNotify(wMsgId);
            g_ChatProtS.Send_SystemMsgIDNotify(wMsgId);
        }
        else
        {
            g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUserId,1,wMsgId);
        }
    }

}

//接收：扫荡
bool CDungeonProtS::OnRecv_Sweeping(
        UINT16 wDgnID, //副本ID
        UINT16 wCount, //次数
        UINT8 byOptions, //选项, 1位为gold，2位为key
        shared_func<SSweepingAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    fnAck->eResult = eDungeonOtherErr;
    if(wDgnID != 1)
    {
        fnAck->eResult = pPlayer->GetDgnPkg().Sweeping(wDgnID, byOptions, wCount, fnAck->dwSweepEndTime);
    }
    //SystemMessageNotify(*pUser, fnAck->eResult);
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    return true;
}

//接收：加速扫荡
bool CDungeonProtS::OnRecv_SweepingSpeedUp(
        UINT8 byOptions, //0为使用礼金，1为使用金币
        shared_func<SSweepingSpeedUpAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    fnAck->eResult = pPlayer->GetDgnPkg().SweepingSpeedUp(byOptions);
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    //SystemMessageNotify(*pUser, fnAck->eResult);
    return true;
}

//接收：取消扫荡
bool CDungeonProtS::OnRecv_CancelSweeping(
        shared_func<SCancelSweepingAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    fnAck->eResult = pPlayer->GetDgnPkg().CancelSweeping();
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    //SystemMessageNotify(*pUser, fnAck->eResult);
    return true;
}
//接收：进入单人副本
bool CDungeonProtS::OnRecv_EnterPlayerDungeon(
        UINT16 wDgnID ,//副本ID
        shared_func<SEnterPlayerDungeonAck>& fnAck
        )
{

    CUserPtr pUser;
    CPlayerPtr pPlayer;
    CGameMapPtr pMap = NULL;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer, &pMap))
        return false;
    fnAck->eResult = eDungeonOtherErr;
    if(wDgnID != 1)
    {
        fnAck->eResult = CDungeonMgr::PlayerEnterNewDungeon(*pPlayer, wDgnID);
        if (fnAck->eResult == eDungeonSuccess)
        {
            //TODO:进入成功
            return true;
        }
    }
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    return true;

}

//接收：离开单人副本
bool CDungeonProtS::OnRecv_LeavePlayerDungeon(shared_func<SLeavePlayerDungeonAck>& fnAck
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    CGameMapPtr pMap;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer, &pMap))
        return false;
    fnAck->eResult = eDungeonOtherErr;
    if(pPlayer->GetDgnID() != 1)
    {
        fnAck->eResult = CDungeonMgr::PlayerLeaveDungeon(*pPlayer);
    }
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    return true;
}
//接收：客户端确认领奖
bool CDungeonProtS::OnRecv_NotifyAcceptDgnAward(
        UINT64 qwDgnID, //副本唯一实例ID
        shared_func<SNotifyAcceptDgnAwardAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    if(qwDgnID != 0)
    {
        CDungeonPtr pDgn = CDungeonMgr::GetDungeon(qwDgnID);
        if(pDgn == NULL)
        {
            fnAck->eResult = eDungeonInsNotExist;
            LOG_CRI << "Can't find Dgn! DgnID: " << qwDgnID;
            return true;
        }
        fnAck->eResult =  pDgn->AcceptDgnAward(*pPlayer);
    }
    else
    {
        pPlayer->CheckLastPend();
        fnAck->eResult = eDungeonSuccess;
    }
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    return true;
}

//接收：查询副本星级
bool CDungeonProtS::OnRecv_GetAllDgnInfo(
        shared_func<SGetAllDgnInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    pPlayer->GetDgnPkg().GetDgnInfoForAll(fnAck->sLiXian,fnAck->vecStar);
    return true ;

}

//接收：客户端查询扫荡信息
bool CDungeonProtS::OnRecv_GetDgnSweepingInfo(
        shared_func<SGetDgnSweepingInfoAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return false;
    }
    pPlayer->GetActionManager().GetSweePingInfo(fnAck->oGetSweepInfo);
    return true;
}
//接收：查询副本进度和星级
void CDungeonProtS::OnRecv_GetDgnProcessAndStar(
        ) 
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return ;
    }
    CDungeonPtr pDgn = CDungeonMgr::GetDungeon(pPlayer->GetDgnInstID());
    if(pDgn == NULL)
    {
        LOG_CRI << "Can't find Dgn! DgnID: " << pPlayer->GetDgnID();
        return ;
    }
    if(pDgn->GetDgnType() != ePlayerDgn && pDgn->GetDgnType() !=  eGatherDgn)
    {
        return;
    }
    CPlayerDgnPtr pPlayerDgn = dynamic_pointer_cast<CPlayerDgn>(pDgn);
    if(NULL == pPlayerDgn)
    {
        return ;
    }
    pPlayerDgn->GetDgnProcessFromClient(*pPlayer);

};
//接收：副本中玩家复活
void CDungeonProtS::OnRecv_ReliveInDgn(
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        PRINT_CALL_STACK_DEBUG;
        return ;
    }
    CDungeonPtr pDgn = CDungeonMgr::GetDungeon(pPlayer->GetDgnInstID());
    if(pDgn == NULL)
    {
        LOG_CRI << "Can't find Dgn! DgnID: " << pPlayer->GetDgnID();
        return ;
    }
    if(pDgn->GetDgnType() != ePlayerDgn && pDgn->GetDgnType() !=  eGatherDgn)
    {
        return;
    }
    CPlayerDgnPtr pPlayerDgn = dynamic_pointer_cast<CPlayerDgn>(pDgn);
    if(NULL == pPlayerDgn)
    {
        return ;
    }
    pPlayerDgn->PlayerRelive();

}
void CDungeonProtS::OnRecv_GetTeamInfo(
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return ;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return ;
    }
    pPlayer->GetDgnPkg().UpdateTeamAward();


}

//接收：购买英雄副本次数
bool CDungeonProtS::OnRecv_BuyHeroDgnTimes(
        UINT16 wDgnID, //副本ID
        shared_func<SBuyHeroDgnTimesAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return false;
    }
    fnAck->eResult = pPlayer->GetDgnPkg().BuyHeroDgnTimes(wDgnID);
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    return true;
}



//接收：购买历险副本次数
bool CDungeonProtS::OnRecv_BuyLiXianDgnTimes(
        shared_func<SBuyLiXianDgnTimesAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return false;
    }
    fnAck->eResult = pPlayer->GetDgnPkg().BuyLiXianDgnTimes();
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());

    return true;


}
//接收：查询副本星级领奖状态
 bool CDungeonProtS::OnRecv_GetDgnStarAwardInfo(
        shared_func<SGetDgnStarAwardInfoAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return false;
    }
    pPlayer->GetStarAwardInfo(fnAck->vecAward);
    return true;
}

//接收：领取副本星级奖励
 bool CDungeonProtS::OnRecv_GetDgnStarAward(
        UINT16 wStarID, //领奖ID
        shared_func<SGetDgnStarAwardAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUsrID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
    if(pUser == NULL)
    {
        LOG_CRI << "Can't find user! UserID: " << qwUsrID;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(pPlayer == NULL)
    {
        LOG_DBG << "User has no player! UserID: " << qwUsrID;
        return false;
    }
    if(pPlayer->CheckStarAwardIsGet(wStarID))
    {
        fnAck->eResult = eDungeonOtherErr;
        SystemMsgNotify(fnAck->eResult,pUser->GetUserID());   
        return true;
    }
    fnAck->eResult = pPlayer->GetDgnPkg().DoStarAward(wStarID);
    if(fnAck->eResult == eDungeonSuccess)
    {
        pPlayer->AddStarAwardInfo(wStarID);
        pPlayer->GetStarAwardInfo(fnAck->vecAward); 
    }
    else
    {
        SystemMsgNotify(fnAck->eResult,pUser->GetUserID());  
    }
    return true;

}
