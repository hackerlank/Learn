#pragma once
#include "FeedBackProtSvr.h"
using namespace NFeedBackProt;

class CFeedBackProtS : public CFeedBackProtSvr
{
	//接收：获取回馈列表
	virtual bool OnRecv_GetFeedBackList(
		shared_func<SGetFeedBackListAck>& fnAck //返回回调函数
	);

	//接收：购买折扣物品
	virtual bool OnRecv_BuyDisCountItem(
		UINT32 dwBuyID, //购买id
		UINT32 dwCount, //购买id数量
		shared_func<SBuyDisCountItemAck>& fnAck //返回回调函数
	);

	//接收：领取奖励
	virtual bool OnRecv_TakeFeedBackPrize(
		UINT32 dwActID, //活动id
		shared_func<STakeFeedBackPrizeAck>& fnAck //返回回调函数
	);

public:
};
extern CFeedBackProtS g_FeedBackProtS;
