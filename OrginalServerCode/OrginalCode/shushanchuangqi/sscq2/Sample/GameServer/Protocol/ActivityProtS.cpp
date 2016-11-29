#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "ActivityProtS.h"
#include "GameNetMgr.h"

//接收：请求获得奖池
bool CActivityProtS::OnRecv_GetActivityPool(
        shared_func<SGetActivityPoolAck>& fnAck //返回回调函数
        )
{
#if 0 //应策划要求取消
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(!pPlayer->GetActivityPkg().HasIcon())
    { 
        fnAck->eResult = eActivityErrOther;        
        SendSysMsgIDNotify(fnAck->eResult); 
        return true;
    }
    fnAck->eResult = pPlayer->GetActivityPkg().GetActivityPool(fnAck->dwTotolActivity);
    if(fnAck->eResult != eActivitySucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
#endif
    return true;


}
//接收：请求活力奖励
bool CActivityProtS::OnRecv_GetActivityAward(
        const SActivityAward& stActivityGet, //奖励Id
        shared_func<SGetActivityAwardAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(!pPlayer->GetActivityPkg().HasIcon())
    { 
        fnAck->eResult = eActivityErrOther;        
        SendSysMsgIDNotify(fnAck->eResult); 
        return true;
    }
    fnAck->eResult = pPlayer->GetActivityPkg().GetActivityAward(stActivityGet);
    fnAck->stActivityPost = stActivityGet;
    if(fnAck->eResult != eActivitySucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;


}
//接收：获取活力任务详情
void CActivityProtS::OnRecv_GetAllInfoActivity(
        )
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
        return ;
    
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(!pPlayer->GetActivityPkg().HasIcon())
    { 
        //SendSysMsgIDNotify(eActivityErrOther); 
        return ;
    }
    pPlayer->GetActivityPkg().SendAllInfoActivity();
}
//接收：获取成就分享信息
bool CActivityProtS::OnRecv_GeShareList(
	shared_func<SGeShareListAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
        return false;
    
    pPlayer->GetActivityPkg().OnGeShareList(fnAck->vecActivityShare);

    return true;
}

//接收：获取成就分享奖励
bool CActivityProtS::OnRecv_TakeSharePrize(
	UINT32 dwActivityID, //成就ID
	shared_func<STakeSharePrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser,&pPlayer))
        return false;
    
    fnAck->eRet = pPlayer->GetActivityPkg().OnTakeSharePrize(dwActivityID);

    return true;
}

void CActivityProtS::SendSysMsgIDNotify(EActivityResult  eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case eActivityMin:
            eMsgID = eMsgActivityMin;
            break;
        case eActivityTotalMin:
            eMsgID = eMsgActivityTotalMin;
            break;
        case eActivityHasGet:
            eMsgID = eMsgAwardHasGet;
            break;
        case eActivityVip:
            eMsgID = eMsgVIPLevelTooLow;
            break;
        case eActivityPackNoSpace:
            eMsgID = eMsgPackFullErr;
            break;
        case eActivityErrOther:
            eMsgID = eMsgTaskErrOther;
            break;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

