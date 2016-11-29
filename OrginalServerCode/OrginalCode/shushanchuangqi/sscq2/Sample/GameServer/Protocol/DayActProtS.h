#pragma once
#include "DayActProtSvr.h"
using namespace NDayActProt;

class CDayActProtS : public CDayActProtSvr
{
public:
    //接收：获取活动列表
	virtual bool OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	);

	//接收：是否已领取首充礼包
	virtual bool OnRecv_GetFirstRechargeStatus(
		shared_func<SGetFirstRechargeStatusAck>& fnAck //返回回调函数
	);

	//接收：领取首充礼包
	virtual bool OnRecv_GetFirstRechargeAward(
		shared_func<SGetFirstRechargeAwardAck>& fnAck //返回回调函数
	);

	//接收：为自己购买蜀山基金
	virtual bool OnRecv_BuyShushanFoundSelf(
		UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		shared_func<SBuyShushanFoundSelfAck>& fnAck //返回回调函数
	);

	//接收：为好友购买蜀山基金
	virtual bool OnRecv_BuyShushanFoundFirend(
		UINT64 qwFriendID, //好友ID
		UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		shared_func<SBuyShushanFoundFirendAck>& fnAck //返回回调函数
	);

	//接收：获取玩家购买及领取蜀山基金的信息
	virtual void OnRecv_GetShushanFoundInfo(
	);

	//接收：领取蜀山基金奖励
	virtual bool OnRecv_GetShushanFoundAward(
		UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
        UINT8 byTimes, //领取第几个(1~7)
		shared_func<SGetShushanFoundAwardAck>& fnAck //返回回调函数
	);

    //接收：获取二次充值礼包状态
	virtual bool OnRecv_GetSecondRechargeStatus(
		shared_func<SGetSecondRechargeStatusAck>& fnAck //返回回调函数
	);

	//接收：领取二次充值礼包
	virtual bool OnRecv_GetSecondRechargeAward(
		shared_func<SGetSecondRechargeAwardAck>& fnAck //返回回调函数
    );

	//接收：获取开服时间
	virtual bool OnRecv_GetOpenServerTime(
		shared_func<SGetOpenServerTimeAck>& fnAck //返回回调函数
	);

};
extern CDayActProtS g_DayActProtS;
