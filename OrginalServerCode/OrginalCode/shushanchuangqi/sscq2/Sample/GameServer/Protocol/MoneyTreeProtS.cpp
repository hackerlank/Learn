#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "MoneyTree.h"
#include "MoneyTreeProtS.h"
#include "GameNetMgr.h"

CMoneyTreeProtS g_MoneyTreeProtS;

//接收：请求摇钱树信息
bool CMoneyTreeProtS::OnRecv_GetMoneyTreeInfo(
    shared_func<SGetMoneyTreeInfoAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    CMoneyTreePtr pMoneyTree = pPlayer->GetMoneyTree();
    if (!pMoneyTree) 
        return false;
    
    pMoneyTree->GetMoneyTreeInfo(fnAck->todayUseCount);

    return true;
}

//接收：请求摇钱
bool CMoneyTreeProtS::OnRecv_GetMoney(
    shared_func<SGetMoneyAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    CMoneyTreePtr pMoneyTree = pPlayer->GetMoneyTree();
    if (!pMoneyTree) 
        return false;
    
    bool bRet = pMoneyTree->GetMoney(fnAck->todayUseCount);

    return bRet;
}

