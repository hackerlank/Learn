#include "GuardEMeiProtS.h"

#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "GuardEMei.h"
#include "GameNetMgr.h"

CGuardEMeiProtS g_GuardEMeiProtS;

//接收：请求守卫峨眉信息
bool CGuardEMeiProtS::OnRecv_ReqGEMInfo(
    shared_func<SReqGEMInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
        return false;

    bool bRet = pGuardEMei->ReqGEMInfo(fnAck->vecGEMMissionInfo);
    if (!bRet)
        return false;

    return true;
}

//接收：请求购买守卫峨眉进入次数
bool CGuardEMeiProtS::OnRecv_BuyGEMEntryNum(
    shared_func<SBuyGEMEntryNumAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eGEMOptResult = eGEMOptResultFailed;
        return false;                       
    }

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
    {
        fnAck->eGEMOptResult = eGEMOptResultFailed;
        return false;                       
    }

    bool bRet = pGuardEMei->BuyGEMEntryNum();
    if (bRet)
        fnAck->eGEMOptResult = eGEMOptResultSucc;
    else
        fnAck->eGEMOptResult = eGEMOptResultFailed;

    return true;
}

//接收：请求使用Buff
bool CGuardEMeiProtS::OnRecv_ReqUseBuff(
    UINT32 dwBuffID, //BuffID
    shared_func<SReqUseBuffAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;                       

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
        return false;                       

    bool bRet = pGuardEMei->ReqUseGEMGuardBuff(dwBuffID, fnAck->vecGEMBattleFighterInfo, fnAck->vecGEMBuffInfo);
    if (!bRet)
        return false;

    return true;
}

//接收：请求重置关卡
bool CGuardEMeiProtS::OnRecv_ReqResetGEM(
    UINT16 wMissionID, //关卡ID
    shared_func<SReqResetGEMAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
    {
        fnAck->eGEMOptResult = eGEMOptResultFailed;
        return false;                       
    }

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
    {
        fnAck->eGEMOptResult = eGEMOptResultFailed;
        return false;                       
    }

    bool bRet = pGuardEMei->ReqResetGEMGuardMission(wMissionID);
    if (bRet)
        fnAck->eGEMOptResult = eGEMOptResultSucc;
    else
        fnAck->eGEMOptResult = eGEMOptResultFailed;
    
    return true;
}

//接收：请求守卫峨眉准备战斗信息
bool CGuardEMeiProtS::OnRecv_ReqGEMPrepareBattleInfo(
    UINT16 wMissionID, //关卡ID
    shared_func<SReqGEMPrepareBattleInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
        return false;                       

    bool bRet = pGuardEMei->ReqGEMGuardPrepareBattleInfo(wMissionID, fnAck->sGEMPrepareBattleInfo);
    if (!bRet)
        return false;

    return true;
}

//接收：请求守卫峨眉战斗
bool CGuardEMeiProtS::OnRecv_ReqGEMBattle(
    UINT16 wMissionID, //关卡ID
    UINT32 dwBuffID, //BuffID
    EGEMBattleType eGEMBattleType, //战斗类型
    shared_func<SReqGEMBattleAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       
    
    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
        return false;                       

    bool bRet = pGuardEMei->ReqGEMGuardBattle(wMissionID, dwBuffID, eGEMBattleType, fnAck->eGEMBattleRet, fnAck->sGEMPrepareBattleInfo);
    if (!bRet)
        return false;

    return true;
}

//接收：请求获取守卫峨眉扫荡开始
bool CGuardEMeiProtS::OnRecv_ReqSweepBegin(
    UINT16 wMissionID, //关卡ID
    shared_func<SReqSweepBeginAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
        return false;
    
    bool bRet = pGuardEMei->ReqGEMSweepBegin(wMissionID);
    if (bRet)
        fnAck->eGEMOptResult = eGEMOptResultSucc;
    else
        fnAck->eGEMOptResult = eGEMOptResultFailed;

    return true;
}

//接收：请求获取守卫峨眉扫荡结束(放弃扫荡)
bool CGuardEMeiProtS::OnRecv_ReqSweepEnd(
    UINT16 wMissionID, //关卡ID
    shared_func<SReqSweepEndAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
         return false;                       

    CGuardEMeiPtr pGuardEMei = pPlayer->GetGuardEMei();
    if (!pGuardEMei) 
        return false;
    
    fnAck->wCurProgress = pGuardEMei->ReqGEMSweepEnd(wMissionID);

    return true;
}
