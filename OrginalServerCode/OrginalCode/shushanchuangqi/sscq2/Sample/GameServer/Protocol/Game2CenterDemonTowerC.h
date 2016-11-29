#pragma once
#include "Game2CenterDemonTowerClt.h"
using namespace NGame2CenterDemonTower;
class CGame2CenterDemonTowerC : public CGame2CenterDemonTowerClt
{
    public:
    //接收：玩家请求进入镇妖塔
	virtual void OnRecv_EnterDemonTower(
		UINT64 qwUserID, //帐号ID
		UINT32 dwFloorID //层数
	);

	//接收：玩家请求离开镇妖塔
	virtual void OnRecv_LeaveDemonTower(
		UINT64 qwUsrID //帐号ID
	);

	//接收：获取每日魂值奖励
	virtual bool OnRecv_TakeDailyPrize(
		UINT64 qwUsrID, //帐号ID
		shared_func<STakeDailyPrizeAck>& fnAck //返回回调函数
	);

	//接收：被攻击信息
	virtual void OnRecv_Attacked(
        UINT64 qwUsrID, //帐号ID
		const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
	);


};
extern CGame2CenterDemonTowerC g_Game2CenterDemonTowerC;
