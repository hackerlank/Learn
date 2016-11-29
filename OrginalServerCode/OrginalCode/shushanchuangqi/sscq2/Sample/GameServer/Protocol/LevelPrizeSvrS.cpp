#include "stdafx.h"
#include "LevelPrizeSvrS.h"
#include "User.h"
#include "Player.h"
#include "WondActMgr.h"
#include "QQAlarm.h"
#include "GameNetMgr.h"

CLevelPrizeSvrS g_LevelPrizeSvrS;

//接收：获取奖励
bool CLevelPrizeSvrS::OnRecv_TakePrize(
	UINT16 wActID, //活动Id
    UINT8 ePrizeNo, //第几个奖励
	shared_func<STakePrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    fnAck->wActID = wActID;
    fnAck->byIndex= ePrizeNo;

    fnAck->eRet = g_WondActMgr.TakePrize(*pPlayer,wActID,ePrizeNo);
    return true;
}
//接收：获取奖励状态
bool CLevelPrizeSvrS::OnRecv_GetPrizeInfo(
		UINT16 wActID, //活动Id
		shared_func<SGetPrizeInfoAck>& fnAck //返回回调函数
	) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    fnAck->wActID = wActID ;
    g_WondActMgr.GetPrize(*pPlayer,wActID,fnAck->vecPrize);
    return true;

}
//接收：玩家在个人服活动中的状态
bool CLevelPrizeSvrS::OnRecv_GetRoleState(
		shared_func<SGetRoleStateAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    g_WondActMgr.GetRoleState(*pPlayer,fnAck->vecRet);
    return true;
}

//接收：QQAlarm获取奖励
bool CLevelPrizeSvrS::OnRecv_TakePrizeForQQAlarm(
		UINT16 wActID, //活动Id
		shared_func<STakePrizeForQQAlarmAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
        fnAck->eRet = eLevleActStatus_Error ;
        return false;                       
    }
    fnAck->eRet = g_QQAlarmMgr.TakePrize(*pUser,wActID);
    return true;
}
//接收：QQAlarm获取奖励状态
void CLevelPrizeSvrS::OnRecv_GetStateForQQAlarm(
		UINT16 wActID //活动Id
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }
    g_QQAlarmMgr.GetState(*pUser,wActID);
}
