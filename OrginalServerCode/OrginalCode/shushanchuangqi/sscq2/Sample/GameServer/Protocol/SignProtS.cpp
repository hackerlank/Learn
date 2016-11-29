#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "SignProtS.h"
#include "Parameter.h"
#include "GameNetMgr.h"

//接收：请求签到信息
bool CSignProtS::OnRecv_GetSignInfo(
        shared_func<SGetSignInfoAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->GetSignInPkg().GetSignInfo(fnAck->dwSignData,fnAck->byReSignTimes,fnAck->dwAward);
    return true;
}

//接收：请求签到
bool CSignProtS::OnRecv_DoSign(
        shared_func<SDoSignAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetSignInPkg().DoSign(fnAck->dwSignData);
    if(fnAck->eResult != eSignSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}

//接收：请求补签
bool CSignProtS::OnRecv_DoReSign(
        UINT8 byDay, //补签日期
        shared_func<SDoReSignAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetSignInPkg().DoReSign(byDay,fnAck->dwSignData,fnAck->byReSignTimes);
    if(fnAck->eResult != eSignSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}

//接收：请求领取奖励
bool CSignProtS::OnRecv_DoGetAward(
        UINT8 byId, //奖励ID
        shared_func<SDoGetAwardAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetSignInPkg().DoGetAward(byId,fnAck->dwAward);
    if(fnAck->eResult != eSignSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;

}

void CSignProtS::SendSysMsgIDNotify(ESignResult eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case  eSignHasDone: //今日已签到
            {
                eMsgID = eMsgSignHasDone;
            }
            break;
        case  eSignResignDone: //补签日已签到
            {
                eMsgID = eMsgSignResignDone;
            }
            break;
        case  eSignResignErrDate: //补签日期错误
            {
                eMsgID = eMsgSignResignErrDate;
            }
            break;
        case  eSignResignOverTimes: //补签次数用完
            {
                eMsgID = eMsgSignResignOverTimes;
            }
            break;
        case  eSignAwardHasGet: //该签到奖励已领
            {
                eMsgID = eMsgSignAwardHasGet;
            }
            break;
        case  eSignAwardIdErr: //该签到奖励id不正确
            {
                eMsgID = eMsgSignAwardIdErr;
            }
            break;
        case  eSignAwardLowDays: //该签到奖励的签到天数不足
            {
                eMsgID = eMsgSignAwardLowDays;
            }
            break;
        case  eSignAwardPacketFull: //签到奖励包裹放不下
            {
                eMsgID = eMsgSignAwardPacketFull;
            }
            break;
         case eSignVIP://提醒开启御剑
            {
                 eMsgID = eMsgSignVIP;
            }
            break;
        case  eSignOther: //其它错误
            {
                eMsgID = eMsgTaskErrOther;
            }
            break;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
