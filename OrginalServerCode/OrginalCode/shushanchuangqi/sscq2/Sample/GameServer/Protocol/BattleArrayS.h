
#pragma once
#include "BattleArraySvr.h"

using namespace NBattleArray;

class CBattleArrayS : public CBattleArraySvr
{
public:
	//接收：获取阵信息
	virtual bool OnRecv_GetBattleArray(
		shared_func<SGetBattleArrayAck>& fnAck //返回回调函数
	);

	//接收：攻击阵图
	virtual bool OnRecv_AttackBattleArray(
		UINT32 dwBattleArrayLevelID, //阵图id
		shared_func<SAttackBattleArrayAck>& fnAck //返回回调函数
	);

	//接收：扫荡阵图
	virtual bool OnRecv_SweepBattleArray(
		UINT32 dwBattleArrayLevelID, //阵图id
		shared_func<SSweepBattleArrayAck>& fnAck //返回回调函数
	);

	//接收：领取通关奖励
	virtual bool OnRecv_BattleArrayTakePrize(
		UINT16 wBattleArrayID, //阵id
		shared_func<SBattleArrayTakePrizeAck>& fnAck //返回回调函数
	);
	
    //接收：获取当前购买价格
	virtual bool OnRecv_GetBuyAtkCountPrice(
		UINT32 dwCount, //购买次数
		shared_func<SGetBuyAtkCountPriceAck>& fnAck //返回回调函数
	);

	//接收：购买攻击阵图次数
	virtual bool OnRecv_BuyAtkCount(
		UINT32 dwCount, //购买次数
		shared_func<SBuyAtkCountAck>& fnAck //返回回调函数
	);

private:
};

extern CBattleArrayS g_BattleArrayS;
