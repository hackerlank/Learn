#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "SittingProtS.h"
#include "GameNetMgr.h"

//接收：请求双修
bool CSittingProtS::OnRecv_DoSittingTogether(
        UINT64 qwOtherID, //对方ID
        shared_func<SDoSittingTogetherAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetActionManager().DoSitting(qwOtherID);
    if(fnAck->eResult != eSittingSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;

}

//接收：请求取消修炼
void CSittingProtS::OnRecv_CancelSitting(
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return ;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->GetActionManager().CancelAction(eACTION_SIT);

}


void CSittingProtS::SendSysMsgIDNotify(ESittingResult eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case    eSittingTogether: //没有找到双修的人
            eMsgID =  eMsgSitTargetError;
            break;
        case    eNotInCity:
            eMsgID = eMsgSitCityError;
            break;
        case 	eSittingErrOther: //其它错误
            eMsgID = eMsgTaskErrOther;
            break;
        case eLevelLow:
            eMsgID = eMsgSysNotOpenLvlErr;
            break;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}
