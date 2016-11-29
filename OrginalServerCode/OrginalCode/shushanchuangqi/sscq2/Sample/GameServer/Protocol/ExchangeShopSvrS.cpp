#include "stdafx.h"
#include "Protocols.h"
#include "UserMgr.h"
#include "Player.h"
#include "ExchangeShopSvrS.h"
#include "ExchangeShopMgr.h"
#include "GameNetMgr.h"

CExchangeShopProtSvrS g_ExchangeShopProtSvrS;

//接收：兑换物品
bool CExchangeShopProtSvrS::OnRecv_ExchangeItem(
	UINT32 dwExchangeID, //兑换id
    UINT32 dwCount, //兑换数量
	shared_func<SExchangeItemAck>& fnAck //返回回调函数
) 
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       

    CExchangeShopMgrPtr pExchangeShopMgr = pPlayer->GetExchangeShopMgr();
    if(pExchangeShopMgr)
    {
        fnAck->dwRet = pExchangeShopMgr->ExchangeItem(dwExchangeID,dwCount,
                [fnAck](UINT32 dwRet)
                {
                    fnAck->dwRet = dwRet;
                    fnAck(true);
                });
    }
    return true;

}

//接收：已兑换列表
bool CExchangeShopProtSvrS::OnRecv_ExchangeItemList(
	shared_func<SExchangeItemListAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;                         
    CPlayerPtr pPlayer;                     
    if(!NetMgr.GetCurUser(&pUser, &pPlayer))
    {                                       
         return false;                       
    }                                       
    
    CExchangeShopMgrPtr pExchangeShopMgr = pPlayer->GetExchangeShopMgr();
    if(pExchangeShopMgr)
    {
        pExchangeShopMgr->GetExchangedItemList(fnAck->vecExchangeInfo);
    }

    return true;


}


