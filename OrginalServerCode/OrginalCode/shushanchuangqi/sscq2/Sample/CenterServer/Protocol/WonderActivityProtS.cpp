
#include "WonderActivityProtS.h"
#include "WonderActivityMgr.h"
#include "WonderActivityProt.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "User.h"
#include "UserMgr.h"
#include "DragonBallActMgr.h"
#include "SevenConsumeActMgr.h"

CWonderActivityProtS g_WonderActivityProtS;
//接收：获得活动时间配置
bool CWonderActivityProtS::OnRecv_GetConfigTime(
		UINT16 wWActID, //精彩活动ID
		shared_func<SGetConfigTimeAck>& fnAck //返回回调函数
	)
{
    fnAck->eRet = g_WonderActivityMgr.GetAllTime(wWActID,fnAck->sTimes);
    
    return true;
}
//接收：获得活动所有奖励配置
bool CWonderActivityProtS::OnRecv_GetAllPrize(
		UINT16 wWActID, //精彩活动ID
		shared_func<SGetAllPrizeAck>& fnAck //返回回调函数
	)
{
    UINT64 qwPlayerID = GetCurUsrID();
    UINT64 qwFist = 0;
    fnAck->wActID = wWActID;
    fnAck->eRet = g_WonderActivityMgr.GetAllPrize(wWActID,fnAck->vecPrizeConfig);
    fnAck->eRet = g_WonderActivityMgr.GetPlayerInfo(qwFist,true,wWActID,fnAck->sFirstPlayer);
    fnAck->eRet = g_WonderActivityMgr.GetPlayerInfo(qwPlayerID,false,wWActID,fnAck->sSelfPlayer);
    return true;
}

//接收：获得活动列表
bool CWonderActivityProtS::OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	)
{
    fnAck->eRet = g_WonderActivityMgr.GetActList(fnAck->vecTimes);
    return true;
}

//接收：玩家领奖
bool CWonderActivityProtS::OnRecv_TakePrize(
		UINT16 wActID, //精彩活动ID
		UINT32 wCond, //条件
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	)
{
   UINT64 qwRoleID = GetCurUsrID();
   fnAck->wActIDRet = wActID;
   fnAck->wCondRet = wCond;
   g_WonderActivityMgr.TakePrize(qwRoleID,wActID,wCond);
   return true;
}

//接收：玩家活动信息
bool CWonderActivityProtS::OnRecv_GetRoleActInfo(
		UINT16 wActID, //活动ID
		shared_func<SGetRoleActInfoAck>& fnAck //返回回调函数
	)
{

   UINT64 qwRoleID = GetCurUsrID();
   fnAck->wActIDRet = wActID;
   g_WonderActivityMgr.GetRoleActInfo(qwRoleID,wActID,fnAck->vecRet);
   return true;
}
//接收：玩家在所有活动中的状态
bool CWonderActivityProtS::OnRecv_GetRoleAllState(
		shared_func<SGetRoleAllStateAck>& fnAck //返回回调函数
	)
{
   UINT64 qwRoleID = GetCurUsrID();
   g_WonderActivityMgr.GetRoleAllState(qwRoleID,fnAck->vecRet);
    return true;
}

//接收：请求七星龙珠活动信息
bool CWonderActivityProtS::OnRecv_GetDragonBallAct(
    shared_func<SGetDragonBallActAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
        return false;
    if (!CDragonBallActMgr::Instance().IsOpenAct())
        return false;

    fnAck->byRet = 1;
    CDragonBallActMgr::Instance().UpdateDragonBallAct(pUser);
    return true;
}

//接收：请求七日消费活动信息
bool CWonderActivityProtS::OnRecv_GetSevenConsumeAct(
    shared_func<SGetSevenConsumeActAck>& fnAck //返回回调函数
)
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
        return false;
    if (!CSevenConsumeActMgr::Instance().IsOpenAct())
        return false;

    fnAck->byRet = 1;
    CSevenConsumeActMgr::Instance().UpdateSevenConsumeAct(pUser);
    return true;
}

//接收：请求Q养成活动信息
void CWonderActivityProtS::OnRecv_GetQQCoinAct(
    ) 
{
    
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
        return ;
    g_WonderActivityMgr.SyncCoinInfo(*pUser);
}

//接收：兑换仙石或者领取Q币
bool CWonderActivityProtS::OnRecv_ExChange(
		UINT8 byType, //0表示Q币，1表示仙石
		shared_func<SExChangeAck>& fnAck //返回回调函数
	) 
{
	UINT64 qwUsrID = GetCurUsrID();
	CUserPtr pUser = CUserMgr::GetUserByUserID(qwUsrID);
	if(!pUser)
    {
        fnAck->eResult = eWActResult_error;
        return false;
    }
    fnAck->eResult = g_WonderActivityMgr.ExChange(*pUser,byType);
    return true;
}

void CWonderActivityProtS::SendSysMsg()
{

}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

