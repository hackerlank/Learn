#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "GroupTaskProtS.h"
#include "GameNetMgr.h"

//接收：请求操作
bool CGroupTaskProtS::OnRecv_GroupTaskOp(
        shared_func<SGroupTaskOpAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetGroupPkg().DoGroupTaskOp(fnAck->eState);
    if(fnAck->eResult != eGroupTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}

//接收：刷新师门任务列表
bool CGroupTaskProtS::OnRecv_FlushTask(
        shared_func<SFlushTaskAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetGroupPkg().DoFlushTask(fnAck->vecTask,fnAck->byFlushTask);
    if(fnAck->eResult != eGroupTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }

    return true;
}

//接收：获取师门任务详情
void CGroupTaskProtS::OnRecv_GetAllInfoTask() 
{
      CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return ;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->GetGroupPkg().SendAllInfoTask();
}


void CGroupTaskProtS::SendSysMsgIDNotify(EGroupTaskResult eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case eGroupTaskLowMoney:
            eMsgID = eMsgGoldErr;
            break;
        case eGroupTaskErrOther:
            eMsgID = eMsgTaskErrOther;
            break;
        case NGroupTaskProt::eBuyTimesUpLimit:
            eMsgID = eMsgDailyShimentimes;
           break;
        case eGroupSaveTimesUpLimit:
            eMsgID = eMsgDailyShimenSave;
            break;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

bool CGroupTaskProtS::OnRecv_BuyTaskTimes(
		shared_func<SBuyTaskTimesAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetGroupPkg().DoBuyTask();
    if(fnAck->eResult != eGroupTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}

