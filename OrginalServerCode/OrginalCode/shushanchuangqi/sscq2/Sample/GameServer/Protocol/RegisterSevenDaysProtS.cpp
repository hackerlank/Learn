#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "RegisterSevenDays.h"
#include "RegisterSevenDaysProtS.h"
#include "GameNetMgr.h"

CRegisterSevenDaysProtS g_RegisterSevenDaysProtS;

//接收：请求当天目标信息
bool CRegisterSevenDaysProtS::OnRecv_GetCurTargetInfo(
    shared_func<SGetCurTargetInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    CRegisterSevenDaysPtr pRegisterSevenDays = pPlayer->GetRegisterSevenDays();
    if (!pRegisterSevenDays) 
        return false;
    
    pRegisterSevenDays->GetCurTargetInfo(fnAck->dwDayID, fnAck->qwTargetInfo);

    return true;
}


//接收：通过dwDayID获取目标信息
bool CRegisterSevenDaysProtS::OnRecv_GetTargetInfoByDayID(
    UINT32 dwDayID, //第几天
    shared_func<SGetTargetInfoByDayIDAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    CRegisterSevenDaysPtr pRegisterSevenDays = pPlayer->GetRegisterSevenDays();
    if (!pRegisterSevenDays) 
        return false;
    
    fnAck->qwTargetInfo = pRegisterSevenDays->GetTargetInfoByDayID(dwDayID);

    return true;
}

//接收：获取奖励
bool CRegisterSevenDaysProtS::OnRecv_GetAward(
    UINT32 dwDayID, //第几天
    UINT8 byTargetID, //目标ID
    shared_func<SGetAwardAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    
    CRegisterSevenDaysPtr pRegisterSevenDays = pPlayer->GetRegisterSevenDays();
    if (!pRegisterSevenDays) 
        return false;
    
    bool bRet = pRegisterSevenDays->GetAward(dwDayID, byTargetID);
    if (bRet)
    {
        fnAck->eResult = eSucceed;
        return true;
    }
    else
    {
        fnAck->eResult = eFailed;
        return false;
    }
}

//接收：请求当天购买信息
bool CRegisterSevenDaysProtS::OnRecv_GetCurBuyInfo(
    shared_func<SGetCurBuyInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    CRegisterSevenDaysPtr pRegisterSevenDays = pPlayer->GetRegisterSevenDays();
    if (!pRegisterSevenDays) 
        return false;
    
    pRegisterSevenDays->GetCurBuyInfo(fnAck->dwDayID, fnAck->eBuyStatus);

    return true;
}

//接收：请求购买
bool CRegisterSevenDaysProtS::OnRecv_ReqBuy(
    shared_func<SReqBuyAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;
    
    CRegisterSevenDaysPtr pRegisterSevenDays = pPlayer->GetRegisterSevenDays();
    if (!pRegisterSevenDays) 
        return false;
    
    bool bRet = pRegisterSevenDays->ReqBuy();
    if (bRet)
    {
        fnAck->eResult = eSucceed;
        return true;
    }
    else
    {
        fnAck->eResult = eFailed;
        return false;
    }
}

