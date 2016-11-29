
#include "BossProtS.h"
#include "WorldBossMgr.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "GameNetMgr.h"


CBossProtS g_BossProtS;

//接收：世界BOSS中复活
bool CBossProtS::OnRecv_WBAlive(
	shared_func<SWBAliveAck>& fnAck //返回回调函数
) 
{
    //CWorldBossMgr::Instance().
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->bRet = false;     
         return false;                       
    }

   fnAck->bRet = CWorldBossMgr::Instance().OnRelive(*pPlayer);
   return true;
 
}
//接收：加持
bool CBossProtS::OnRecv_WBStrength(
	EBossBuyType eBuyType, //购买类型
	shared_func<SWBStrengthAck>& fnAck //返回回调函数
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->bRet = false;     
         return false;                       
    }

    fnAck->bRet = CWorldBossMgr::Instance().BuyStrength(*pPlayer,eBuyType,fnAck->dwSilverBufferCnt,fnAck->dwGoldBufferCnt,fnAck->dwSilverBufferCdTime);


    return true;
}

//接收：直接攻击boss
bool CBossProtS::OnRecv_WBAttack(
	shared_func<SWBAttackAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->bRet = false;     
         return false;                       
    }

    fnAck->bRet = CWorldBossMgr::Instance().AttackBoss(*pPlayer);
    return true;
}


//接收：获取排行榜信息
void CBossProtS::OnRecv_GetTopList(
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }

    CWorldBossMgr::Instance().OnGetTopList(*pPlayer);

}
//接收：获取玩家自己的排行榜信息
void CBossProtS::OnRecv_GetSelfInfo(
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }

    CWorldBossMgr::Instance().OnGetSelfInfo(*pPlayer);
}

//接收：获取boss信息
void CBossProtS::OnRecv_GetBossInfo(
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return;                       
    }

    CWorldBossMgr::Instance().OnGetBossInfo(*pPlayer);

}
//接收：进入boss地图
bool CBossProtS::OnRecv_EnterMap(
	shared_func<SEnterMapAck>& fnAck //返回回调函数
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->bRet = false;     
         return false;                       
    }
    
    fnAck->bRet = CWorldBossMgr::Instance().OnEnterMap(*pPlayer);

    return true;
}
//接收：离开boss地图
bool CBossProtS::OnRecv_LeaveMap(
	shared_func<SLeaveMapAck>& fnAck //返回回调函数
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         fnAck->bRet = false;     
         return false;                       
    }

    fnAck->bRet = CWorldBossMgr::Instance().OnLeaveMap(*pPlayer);
    return true;
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

