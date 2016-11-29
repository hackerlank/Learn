#include "stdafx.h"
#include "GameNetMgr.h"
#include "Player.h"
#include "FeedBackProtS.h"
#include "FeedBackMgr.h"

CFeedBackProtS g_FeedBackProtS;

//接收：获取回馈列表
bool CFeedBackProtS::OnRecv_GetFeedBackList(
		shared_func<SGetFeedBackListAck>& fnAck //返回回调函数
	)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    g_FeedBackMgr.OnGetFeedBackList(*pPlayer,fnAck->vecFeedBackInfo,fnAck->vecSBuyDiscountInfo);

    return true;
}

//接收：购买折扣物品
bool CFeedBackProtS::OnRecv_BuyDisCountItem(
	UINT32 dwBuyID, //购买id
	UINT32 dwCount, //购买id数量
	shared_func<SBuyDisCountItemAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    fnAck->eRet= (EFeedBackRet)g_FeedBackMgr.OnBuyDisCountItem(*pPlayer,dwBuyID,dwCount);
    return true;
}

//接收：领取奖励
bool CFeedBackProtS::OnRecv_TakeFeedBackPrize(
	UINT32 dwActID, //活动id
	shared_func<STakeFeedBackPrizeAck>& fnAck //返回回调函数
)
{
    CUserPtr pUser;
    CPlayerPtr pPlayer;
    if (!NetMgr.GetCurUser(&pUser, &pPlayer))
        return false;

    fnAck->eRet= (EFeedBackRet)g_FeedBackMgr.OnTakeFeedBackPrize(*pPlayer,dwActID);
    return true;
}

