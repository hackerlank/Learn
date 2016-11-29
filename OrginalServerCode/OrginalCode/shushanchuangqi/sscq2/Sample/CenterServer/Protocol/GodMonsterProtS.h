#pragma once
#include "GodMonsterProtSvr.h"

using namespace NGodMonsterProt;

class CGodMonsterProtS : public CGodMonsterProtSvr
{
public:	
    //接收：打开活动面板
	virtual bool OnRecv_OnEnter(
		shared_func<SOnEnterAck>& fnAck //返回回调函数
	);
	//接收：喂养
	virtual bool OnRecv_OnFeed(
		UINT8 byType, //0: 表示喂养一次，1: 表示一键喂养
		shared_func<SOnFeedAck>& fnAck //返回回调函数
	);
	//接收：领奖
	virtual bool OnRecv_TakePrize(
		EMonsterPrizeType ePrizeType, //奖励类型
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);
	//接收：购买限购礼包
	virtual bool OnRecv_BuyPkg(
		UINT16 wIndex, //礼包ID
		UINT8 byCount, //数量
		shared_func<SBuyPkgAck>& fnAck //返回回调函数
	);
	//接收：表扬
	virtual void OnRecv_OnPraise(
		UINT64 qwRoleID //玩家
	);

	//接收：督促
	virtual void OnRecv_OnUrge(
		UINT64 qwRoleID //玩家
	);
private:
};

extern CGodMonsterProtS g_GodMonsterProtS;
