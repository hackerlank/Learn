#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "TreasureHunt.h"
#include "TreasureHuntProtS.h"
#include "GameNetMgr.h"

CTreasureHuntProtS g_TreasureHuntProtS;

//接收：请求寻宝信息
bool CTreasureHuntProtS::OnRecv_ReqTHInfo(
    shared_func<SReqTHInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
        return false;

    pTreasureHunt->ReqTHInfo(fnAck->byCopyID, fnAck->eTHStatus, fnAck->byKillNum, fnAck->byCurrentID);

    return true;
}

//接收：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
bool CTreasureHuntProtS::OnRecv_ReqTHBattlePrepareInfo(
		shared_func<SReqTHBattlePrepareInfoAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
        return false;

    pTreasureHunt->GetTHBattlePrepareInfo(fnAck->byKillNum, fnAck->dwCurBossHP, fnAck->dwTotalTimes, fnAck->vecTHAwardInfo, fnAck->vecTHBuffInfo);

    return true;
}

//接收：请求寻宝开始
bool CTreasureHuntProtS::OnRecv_ReqTHStart(
    UINT8 byCopyID, //副本ID
    shared_func<SReqTHStartAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }
    
    fnAck->eTHOptResult = pTreasureHunt->ReqTHStart(byCopyID);

    return true;
}
//接收：请求寻宝立即完成
bool CTreasureHuntProtS::OnRecv_ReqTHQuickFinish(
    shared_func<SReqTHQuickFinishAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }
    
    bool bRet = pTreasureHunt->ReqTHQuickFinish();
    if (bRet)
        fnAck->eTHOptResult = eTHOptResultSucc;
    else
        fnAck->eTHOptResult = eTHOptResultFailed;

    return true;
}

//接收：请求放弃寻宝
bool CTreasureHuntProtS::OnRecv_ReqTHGiveUp(
    shared_func<SReqTHGiveUpAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }
    
    bool bRet = pTreasureHunt->ReqGiveUpTH();
    if (bRet)
        fnAck->eTHOptResult = eTHOptResultSucc;
    else
        fnAck->eTHOptResult = eTHOptResultFailed;

    return true;
}

//接收：请求使用Buff
bool CTreasureHuntProtS::OnRecv_ReqUseBuff(
    UINT8 byBuffID, //BuffID
    shared_func<SReqUseBuffAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }
    
    bool bRet = pTreasureHunt->UseBuff(byBuffID);
    if (bRet)
        fnAck->eTHOptResult = eTHOptResultSucc;
    else
        fnAck->eTHOptResult = eTHOptResultFailed;

    return true;
}

//接收：请求寻宝奖励信息
bool CTreasureHuntProtS::OnRecv_ReqTHAwardInfo(
    shared_func<SReqTHAwardInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt) 
        return false;
    
    pTreasureHunt->ReqTHAwardInfo(fnAck->byCopyID, fnAck->vecTHAwardInfo);

    return true;
}

//接收：获取寻宝奖励
bool CTreasureHuntProtS::OnRecv_GetTHAward(
    shared_func<SGetTHAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }

    CTreasureHuntPtr pTreasureHunt = pPlayer->GetTreasureHunt();
    if (!pTreasureHunt)
    {
        fnAck->eTHOptResult = eTHOptResultFailed; 
        return false;
    }
    
    bool bRet = pTreasureHunt->GetTHAward();
    if (bRet)
        fnAck->eTHOptResult = eTHOptResultSucc;
    else
        fnAck->eTHOptResult = eTHOptResultFailed;
    
    return true;
}

