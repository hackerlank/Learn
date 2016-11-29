#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "SysMsgDefine.h"
#include "YaMenTaskProtS.h"
#include "GameNetMgr.h"

//接收：请求操作
bool CYaMenTaskProtS::OnRecv_YaMenTaskOp(
        shared_func<SYaMenTaskOpAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetYaMenPkg().DoYaMenTaskOp(fnAck->eState);
    if(fnAck->eResult != eYaMenTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}

//接收：刷新衙门任务列表
bool CYaMenTaskProtS::OnRecv_FlushTask(
        shared_func<SFlushTaskAck>& fnAck //返回回调函数
        ) 
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetYaMenPkg().DoFlushTask(fnAck->vecTask,fnAck->byFlushTask);
    if(fnAck->eResult != eYaMenTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }

    return true;
}

//接收：获取衙门任务详情
void CYaMenTaskProtS::OnRecv_GetAllInfoTask() 
{
      CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return ;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    pPlayer->GetYaMenPkg().SendAllInfoTask();
}


void CYaMenTaskProtS::SendSysMsgIDNotify(EYaMenTaskResult eResult)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case eYaMenTaskLowMoney:
            eMsgID = eMsgGoldErr;
            break;
        case eYaMenTaskErrOther:
            eMsgID = eMsgTaskErrOther;
            break;
       case eYaMenAwardPackFull:
            eMsgID = eMsgETeamPackFull;
            break;
       case eYaMenSaveTimesUpLimit:
            eMsgID = eMsgDailyYamenSave;
            break;
        case NYaMenTaskProt::eBuyTimesUpLimit:
            eMsgID = eMsgDailyShimentimes;
           break;
        default:
           break;
    }
    if(eMsgID != eMsgSuccess)
        g_ChatProtS.Send_SystemMsgIDNotify(eMsgID);
}

bool CYaMenTaskProtS::OnRecv_BuyTaskTimes(
		shared_func<SBuyTaskTimesAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    if(!NetMgr.GetCurUser(&pUser))
      return false;
    CPlayerPtr pPlayer = pUser->GetPlayer();
    fnAck->eResult = pPlayer->GetYaMenPkg().DoBuyTask();
    if(fnAck->eResult != eYaMenTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult);
    }
    return true;
}

