#include "stdafx.h"
#include "DayTargetS.h"
#include "User.h"
#include "Player.h"
#include "DayTargetMgr.h"
#include "RoleInfoDefine.h"
#include "GameNetMgr.h"

using namespace NRoleInfoDefine;
CDayTargetS g_DayTargetS;

//extern CGame2CenterLogC g_Game2CenterLog;

//接收：获取任务列表
bool CDayTargetS::OnRecv_GetTaskList(
    shared_func<SGetTaskListAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CDayTargetMgrPtr pDayTargetMgr = pPlayer->GetDayTargetMgr();
    if(pDayTargetMgr)
    {
        pDayTargetMgr->GetTaskList(fnAck->vecDayTargetTask);
    }

    return true;
}

//接收：领取奖励
bool CDayTargetS::OnRecv_TakePrize(
	UINT16 wTaskID, //任务ID
	shared_func<STakePrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }

    CDayTargetMgrPtr pDayTargetMgr = pPlayer->GetDayTargetMgr();
    if(pDayTargetMgr)
    {
        fnAck->eRet = pDayTargetMgr->TakePrize(wTaskID);
    }


    return true;

}

