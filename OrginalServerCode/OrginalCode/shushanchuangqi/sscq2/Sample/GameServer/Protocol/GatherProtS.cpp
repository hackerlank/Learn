#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "GatherProtS.h"
void CGatherProtS::SystemMsgNotify(EGatherResult result,UINT64 qwUserId )
{
    UINT16 wMsgId =0;
    switch(result)
    {
        case eGatherIn: //正在采集中
            {
                wMsgId = eMsgGatherIn;
            }
            break; 
        case eGatherOut: //没有采集中
            {
                wMsgId = eMsgGatherOut;
            }
            break; 

        case eGatherItemLimit: //采集所需物品不足
            {
                wMsgId = eMsgGatherItemLimit;
            }
            break; 
            /*     
                   case eGatherBusy: //玩家忙
                   {
                   wMsgId = eMsgGatherBusy;
                   }
                   break; 
                   */
        case eGatherPackEmptyMin: //采集空格子不足
            {
                wMsgId = eMsgGatherPackEmptyMin;
            }
            break; 
        case eGatherVIP: //VIP等级不足
            {
                wMsgId = eMsgGatherVIP;
            }
            break; 
        case eGatherLevel: //等级不足
            {
                wMsgId = eMsgGatherLevel;
            }
            break; 
        case eGatherNotExist: //采集物不存在
            {
                wMsgId = eMsgGatherNotExist;
            }
            break; 
        case eGatherTooFar: //采集物太远
            {
                wMsgId = eMsgGatherTooFar;
            }
            break; 
        case eGatherTask://需要接相关任务才可以采集
            {
                wMsgId = eMsgGatherTask;
            }
            break;
        case eGatherNumLimit: //采集物数量不足
            {
                wMsgId = eMsgGatherNumLimit;
            }
            break; 
        case eGatherCancel: //采集中断
            {
                wMsgId = eMsgGatherCancel;
            }
            break; 
        case eGatherOtherErr: //未知错误
            {
                wMsgId = eMsgGatherOtherErr;
            }
            break; 
        case eGatherLuaErr: //脚本错误
            {
                wMsgId = eMsgGatherLuaErr;
            }
            break; 

        default:
            {
            }
            break; 
    }
    if(wMsgId != 0)
    {
        if(qwUserId == 0)
        {
            g_ChatProtS.Send_SystemMsgIDNotify(wMsgId);
        }
        else
        {
            g_ChatProtS.SendClt_SystemMsgIDNotify(&qwUserId,1,wMsgId);
        }
    }

}

bool CGatherProtS::OnRecv_GatherReq(
        UINT32 dwGatherId, //采集ID
        shared_func<SGatherReqAck>& fnAck //返回回调函数
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
    pPlayer->OnRecv_GatherReq(dwGatherId,fnAck);
    SystemMsgNotify(fnAck->eResult,pUser->GetUserID());
    return true;

}

//接收：取消采集
bool CGatherProtS::OnRecv_CancelGather(
        shared_func<SCancelGatherAck>& fnAck //返回回调函数
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
    pPlayer->OnRecv_CancelGather(fnAck);

    if(fnAck->eResult != eGatherSuccess)
        SystemMsgNotify(fnAck->eResult,pUser->GetUserID());

    return true;

}

//接收：客户端查询采集信息
bool CGatherProtS::OnRecv_GetGatherInfo(
        shared_func<SGetGatherInfoAck>& fnAck //返回回调函数
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
    pPlayer->OnRecv_GetGatherInfo(fnAck);
    return true;

}

