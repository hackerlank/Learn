#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "DemonTowerSvrS.h"
#include "DemonTowerMgr.h"
 CDemonTowerSvrS g_DemonTowerSvrS;
//接收：进入锁妖塔(假的仅返回当前层的信息)
bool CDemonTowerSvrS::OnRecv_EnterDemonTower(
        UINT32 dwFloorID, //层数
        shared_func<SEnterDemonTowerAck>& fnAck //返回回调函数
        ) 
{

    UINT64 qwUserID = GetCurUsrID();
    fnAck->dwRet = g_DemonTowerMgr.PlayerEnter(qwUserID,dwFloorID);
    return true;
}

 //接收：离开锁妖塔
 bool CDemonTowerSvrS::OnRecv_LeaveDemonTower(
		shared_func<SLeaveDemonTowerAck>& fnAck //返回回调函数
	)
{


    UINT64 qwUserID = GetCurUsrID();
    fnAck->dwRet = g_DemonTowerMgr.PlayerLeave(qwUserID);
    return true;
}

//接收：封印怪物(挑战?)
bool CDemonTowerSvrS::OnRecv_SealMonster(
		UINT32 dwFloorID, //层数
		shared_func<SSealMonsterAck>& fnAck //返回回调函数
	)
{


    //UINT64 qwUserID = GetCurUsrID();
    //fnAck->dwRet = g_DemonTowerMgr.AttackMonster(qwUserID,dwFloorID);
    return true;
}


//接收：镇守锁妖塔
bool CDemonTowerSvrS::OnRecv_GuardAtk(
         UINT32 dwFloorID, //层数
         UINT32 dwGuardPos, //镇守位置
         shared_func<SGuardAtkAck>& fnAck //返回回调函数
       )
{
    UINT64 qwUserID = GetCurUsrID();
    fnAck->dwRet = g_DemonTowerMgr.AtkPlayer(qwUserID,dwFloorID,dwGuardPos);
    return true;
}

//接收：抢夺镇守位置
bool CDemonTowerSvrS::OnRecv_AtkPlayer(
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		shared_func<SAtkPlayerAck>& fnAck //返回回调函数
	)
{

    UINT64 qwUserID = GetCurUsrID();
    fnAck->dwRet = g_DemonTowerMgr.AtkPlayer(qwUserID,dwFloorID,dwGuardPos);
    return true;

}
                          

//接收：领取奖励
bool CDemonTowerSvrS::OnRecv_TakePrize(
		EDemonTowerPrize ePrizeType, //奖励类型
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	)
{
    UINT64 qwUserID = GetCurUsrID(); 
    switch(ePrizeType)
    {
        case eDemonTower_Prize_Fail:
            {
                fnAck->dwRet =  g_DemonTowerMgr.TakeGuardFailPrize(qwUserID);
            }
            break;
        case eDemonTower_Prize_Day:
            {
                fnAck->dwRet =  g_DemonTowerMgr.TakePassDayPrize(qwUserID);
            }
            break;
        case eDemonTower_Prize_Seal:
            {
                fnAck->dwRet =  eDemonTower_Invalid_PrizeType;//g_DemonTowerMgr.TakeSealPrize(qwUserID);
            }
            break;
        default:
            {
                fnAck->dwRet =  eDemonTower_Invalid_PrizeType;
                return false;
            }
            break;
    }

    return true;
}

//接收：获取镇守榜
bool CDemonTowerSvrS::OnRecv_GetTopList(
		UINT16 wPage, //页码 1开始
		UINT16 wPageItemCount, //每页显示数目 默认5
		shared_func<SGetTopListAck>& fnAck //返回回调函数
	)
{

    
    g_DemonTowerMgr.GetTopList(wPage,wPageItemCount,fnAck->oDemonFloorPage);
    return true;
}
//接收：获取本人镇妖塔相关信息
bool CDemonTowerSvrS::OnRecv_GetDemonTowerInfo(
		shared_func<SGetDemonTowerInfoAck>& fnAck //返回回调函数
	)
{
     UINT64 qwUserID = GetCurUsrID();
    bool bRet = g_DemonTowerMgr.GetDemonTowerInfo(qwUserID,fnAck->oDemonTowerPlayer);
    if(bRet)
    {
        fnAck->dwRet = 0;
    }
    else
    {
        fnAck->dwRet = 1;
    }
    return true;
}

//接收：获取镇守信息信息
bool CDemonTowerSvrS::OnRecv_GetGuardInfo(
		UINT32 dwFloorID, //镇守层
		shared_func<SGetGuardInfoAck>& fnAck //返回回调函数
	)
{

    g_DemonTowerMgr.GetGuardInfo(dwFloorID,fnAck->vecGuardInfo); 
    return true;
}

//接收：恢复元神
void CDemonTowerSvrS::OnRecv_Restore(
	UINT32 dwCount //物品数量
)
{
    UINT64 qwUserID = GetCurUsrID();
    g_DemonTowerMgr.Restore(qwUserID,dwCount);

}

//接收：增加聚魂速度
void CDemonTowerSvrS::OnRecv_AddSpeed(
	UINT32 dwCount //物品数量
)
{
    UINT64 qwUserID = GetCurUsrID();
    g_DemonTowerMgr.AddSpeed(qwUserID,dwCount);
}
	//接收：获取玩家镇守信息
bool CDemonTowerSvrS::OnRecv_GetPlayerInfo(
	UINT64 qwUserID, //账号ID
	shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
)
{
    fnAck->bRet = g_DemonTowerMgr.GetPlayerInfo(qwUserID,fnAck->oDemonFloorPlayer);
    return true;

}

//接收：清除pvp战斗cd
bool CDemonTowerSvrS::OnRecv_ClearFightCd(
	shared_func<SClearFightCdAck>& fnAck //返回回调函数
)
{
    UINT64 qwUserID = GetCurUsrID();
    g_DemonTowerMgr.OnClearFightCd(qwUserID,fnAck);
    return true;
}
//接收：获取过关信息
bool CDemonTowerSvrS::OnRecv_GetPassInfo(
	UINT16 wFloorID, //通关层
	shared_func<SGetPassInfoAck>& fnAck //返回回调函数
)
{
    g_DemonTowerMgr.OnGetPassInfo(wFloorID,fnAck->vecMinRound,fnAck->vecMinBattlePoint);

    return true;
}


