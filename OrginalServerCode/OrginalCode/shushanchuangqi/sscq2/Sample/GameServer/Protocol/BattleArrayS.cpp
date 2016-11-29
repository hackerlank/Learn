
#include "BattleArrayS.h"
#include "User.h"
#include "Player.h"
#include "UserMgr.h"
#include "BattleArrayMgr.h"
#include "GameNetMgr.h"

CBattleArrayS g_BattleArrayS;

//接收：获取阵信息
bool CBattleArrayS::OnRecv_GetBattleArray(
	shared_func<SGetBattleArrayAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CBattleArrayMgrPtr pBattleArrayMgr =  pPlayer->GetBattleArrayMgr();
    if(pBattleArrayMgr)
    {
        pBattleArrayMgr->OnGetBattleArray(fnAck);
    }

    return true;
}


//接收：攻击阵图
bool CBattleArrayS::OnRecv_AttackBattleArray(
	UINT32 dwBattleArrayLevelID, //阵图id
	shared_func<SAttackBattleArrayAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CBattleArrayMgrPtr pBattleArrayMgr =  pPlayer->GetBattleArrayMgr();
    if(pBattleArrayMgr)
    {
        fnAck->eBattleArrayRet = pBattleArrayMgr->OnAttackBattleArray(dwBattleArrayLevelID);
        fnAck->dwFailCd = pBattleArrayMgr->GetFailCD();
    }


    return true;
}

//接收：扫荡阵图
bool CBattleArrayS::OnRecv_SweepBattleArray(
	UINT32 dwBattleArrayLevelID, //阵图id
	shared_func<SSweepBattleArrayAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CBattleArrayMgrPtr pBattleArrayMgr =  pPlayer->GetBattleArrayMgr();
    if(pBattleArrayMgr)
    {
        fnAck->eBattleArrayRet = pBattleArrayMgr->OnSweepBattleArray(dwBattleArrayLevelID);
    }

    return true;
}

//接收：领取通关奖励
bool CBattleArrayS::OnRecv_BattleArrayTakePrize(
	UINT16 wBattleArrayID, //阵id
	shared_func<SBattleArrayTakePrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CBattleArrayMgrPtr pBattleArrayMgr =  pPlayer->GetBattleArrayMgr();
    if(pBattleArrayMgr)
    {
        fnAck->eBattleArrayRet = pBattleArrayMgr->OnBattleArrayTakePrize(wBattleArrayID);
    }

    return true;

}

//接收：获取当前购买价格
bool CBattleArrayS::OnRecv_GetBuyAtkCountPrice(
	UINT32 dwCount, //购买次数
	shared_func<SGetBuyAtkCountPriceAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CBattleArrayMgrPtr pBattleArrayMgr =  pPlayer->GetBattleArrayMgr();
    if(pBattleArrayMgr)
    {
        pBattleArrayMgr->OnGetBuyAtkCountPrice(dwCount,fnAck);
    }

    return true;
}

//接收：购买攻击阵图次数
bool CBattleArrayS::OnRecv_BuyAtkCount(
	UINT32 dwCount, //购买次数
	shared_func<SBuyAtkCountAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }
    CBattleArrayMgrPtr pBattleArrayMgr =  pPlayer->GetBattleArrayMgr();
    if(pBattleArrayMgr)
    {
        fnAck->eRet = pBattleArrayMgr->OnBuyAtkCount(dwCount,fnAck);
    }

    return true;

}
/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

