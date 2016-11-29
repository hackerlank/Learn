#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "TaskConfMgr.h"
#include "Map.h"
#include "DungeonMgr.h"
#include "MoneyParam.h"
#include "SysMsgDefine.h"
#include "Task.h"
#include "GameNetMgr.h"

//接收：接受任务请求
bool CTaskProtS::OnRecv_AcceptTaskReq(	
        UINT8 byCost,//0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
        UINT16 wTaskID, //任务ID
        shared_func<SAcceptTaskReqAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTaskErrOther;
        return false;
    }
    fnAck->wTaskID = wTaskID;
    fnAck->byCost = byCost;
    fnAck->eResult = pUser->GetTaskPkg().AcceptTask(wTaskID,byCost);
    if(eTaskSucceed != fnAck->eResult)
        SendSysMsgIDNotify(fnAck->eResult,*pUser);
    return fnAck->eResult == eTaskSucceed;
}

//接收：放弃任务请求
bool CTaskProtS::OnRecv_GiveUpTask(
        UINT16 wTaskID, //任务ID
        shared_func<SGiveUpTaskAck>& fnAck //返回回调函数
        )
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eResult = eTaskErrOther;
        return false;
    }

    fnAck->eResult = pUser->GetTaskPkg().GiveUpTask(wTaskID);
    fnAck->wTaskID = wTaskID;
    if(eTaskSucceed != fnAck->eResult)
        SendSysMsgIDNotify(fnAck->eResult,*pUser);
    return fnAck->eResult == eTaskSucceed;
}

//接收：完成任务请求(领取奖励)
bool CTaskProtS::OnRecv_FinishTask(
        UINT8 byCost,//0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
        UINT16 wTaskID, //任务ID
        UINT8 byIndex, //可选择的奖励索引
        shared_func<SFinishTaskAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUserID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        fnAck->eResult = eTaskErrOther;
        return false;
    }
    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(NULL == pPlayer)
    {
        fnAck->eResult = eTaskErrOther;
        return false;
    }
    fnAck->wTaskID = wTaskID;
    fnAck->byCost = byCost;
    fnAck->eResult = pUser->GetTaskPkg().FinishTask(wTaskID, byIndex,byCost);
    if(eTaskSucceed != fnAck->eResult)
    {
        SendSysMsgIDNotify(fnAck->eResult,*pUser);
    }
    return fnAck->eResult == eTaskSucceed;
}

//接收：完成特殊任务请求
void CTaskProtS::OnRecv_FinishSpeTask(
        UINT16 wTaskID //任务ID
        )
{
    if (0 == wTaskID)
        return;

    UINT64 qwUserID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
        return;

    CPlayerPtr pPlayer = pUser->GetPlayer();
    if(NULL == pPlayer)
        return;

    switch(wTaskID)
    {
        case 13:
            {
                pUser->GetTaskPkg().OnAction(*pPlayer, eProcessAction_CollectGame);
            }
            break;
        default:
            break;
    }
    return;
}

/*
//接收：立刻完成任务请求
bool CTaskProtS::OnRecv_FinishTaskReq(
UINT16 wTaskID, //任务ID
shared_func<SFinishTaskReqAck>& fnAck //返回回调函数
)
{
UINT64 qwUsrID = GetCurUsrID();
CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
if(pUser == NULL)
{
fnAck->eResult = eTaskErrOther;
return false;
}
CPlayerPtr pPlayer = pUser->GetPlayer();
if(pPlayer == NULL)
{
fnAck->eResult = eTaskErrOther;
return false;
}
fnAck->eResult = pUser->GetTaskPkg()->ForceFinishTask(wTaskID);
if(eTaskSucceed != fnAck->eResult)
SendSysMsgIDNotify(fnAck->eResult);
return eTaskSucceed == fnAck->eResult;
}
*/
void CTaskProtS::OnRecv_GetTaskList(
        )
{
    UINT64 qwUserID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        return ;
    }

    pUser->GetTaskPkg().AllTaskNotify();

}

void CTaskProtS::OnRecv_GetCircleTaskInfo()
{
    UINT64 qwUserID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        return ;
    }
    pUser->GetTaskPkg().SendCircleInfo();
}
//接收：完成所有的环任务
bool CTaskProtS::OnRecv_FinishCircleTaskOneKey(
        shared_func<SFinishCircleTaskOneKeyAck>& fnAck //返回回调函数
        )
{
    UINT64 qwUserID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        return false;
    }
    fnAck->eResult = pUser->GetTaskPkg().FinishAllCircleTaskOneKey();
    if(fnAck->eResult != eTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult, *pUser);
    }
    return true;
}
//接收：提升环任务星级
bool CTaskProtS::OnRecv_UpdateCircleTaskStar(
        shared_func<SUpdateCircleTaskStarAck>& fnAck //返回回调函数
        ) 
{
    UINT64 qwUserID = GetCurUsrID();
    CUserPtr pUser = CUserMgr::GetUserByUserID(qwUserID);
    if(NULL == pUser)
    {
        return false;
    }
    fnAck->eResult = pUser->GetTaskPkg().UpdateCircleTaskStar();
    if(fnAck->eResult != eTaskSucceed)
    {
        SendSysMsgIDNotify(fnAck->eResult,*pUser);
    }
    return true;
}

void CTaskProtS::SendSysMsgIDNotify(ETaskResult eResult,CUser& rUser)
{
    ESystemMsgID eMsgID = eMsgSuccess;
    switch(eResult)
    {
        case eTaskNotExist:
            eMsgID = eMsgTaskNotExist;
            break;
        case eTaskAlreadyAccept:
            eMsgID = eMsgTaskAlreadyAccept;
            break;
        case eTaskErrFinish:
            eMsgID = eMsgTaskErrFinish;
            break;
        case eTaskErrGiveUp:
            eMsgID = eMsgTaskErrGiveUp;
            break;
        case eTaskErrAccept:
            eMsgID = eMsgTaskErrAccept;
            break;
        case eTaskErrPackFull:
            eMsgID = eMsgPackFullErr;
            break;
        case eTaskErrRepeat:
            eMsgID = eMsgTaskErrRepeat;
            break;
        case eTaskErrFull:
            eMsgID = eMsgTaskErrFull;
            break;
        case eTaskErrSex:
            eMsgID = eMsgRoleSexErr;
            break;
        case eTaskErrPrepTask:
            eMsgID = eMsgTaskErrPrepTask;
            break;
        case eTaskErrLevel:
            eMsgID = eMsgRoleLevelErr;
            break;
        case eTaskErrNoSelOptAward:
            eMsgID = eMsgTaskErrNoSelOptAward;
            break;
        case eTaskErrMap:
            eMsgID = eMsgTaskErrMap;
            break;
        case eTaskNoRepution:
            eMsgID = eMsgTaskNoRepution;
            break;
        case eTaskNoJob:
            eMsgID = eMsgTaskNoJob;
            break;
        case eTaskNoRace:
            eMsgID = eMsgTaskNoRace;
            break;
        case eTaskNoGold:
            eMsgID = eMsgGoldErr;
            break;
        case eTaskGroupFull:
            eMsgID = eMsgShiMenTaskNumFull;
            break;
        case eTaskYaMenFull:
            eMsgID = eMsgYaMenTaskNumFull;
            break;
        case eTaskErrOther:
        case eTaskCircleFull:
            eMsgID = eMsgTaskErrOther;
            break;
        case eTaskNoSliver:
            eMsgID = eMsgSilverErr;
        default:
            break;
    }
    if(eMsgID != eMsgSuccess)
        rUser.SendPkg(g_ChatProtS.BuildPkg_SystemMsgIDNotify(eMsgID));
}
