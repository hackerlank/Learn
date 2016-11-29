
#pragma once
#include "DemonTowerSvr.h"

using namespace NDemonTower;

//协议类：锁妖塔
class CDemonTowerSvrS : public CDemonTowerSvr
{
public:
	//接收：进入锁妖塔(假的仅返回当前层的信息)
	virtual bool OnRecv_EnterDemonTower(
		UINT32 dwFloorID, //层数
		shared_func<SEnterDemonTowerAck>& fnAck //返回回调函数
	) ;

    //接收：离开锁妖塔
	virtual bool OnRecv_LeaveDemonTower(
		shared_func<SLeaveDemonTowerAck>& fnAck //返回回调函数
	);

    //接收：封印怪物(挑战?)
	virtual bool OnRecv_SealMonster(
		UINT32 dwFloorID, //层数
		shared_func<SSealMonsterAck>& fnAck //返回回调函数
	);

	//接收：升级魄空间
	virtual bool OnRecv_UpgradeSoulSpace(
		UINT32 dwSoulSpaceID, //魄空间ID
		shared_func<SUpgradeSoulSpaceAck>& fnAck //返回回调函数
	);
	
    //接收：获取魄空间列表
	virtual void OnRecv_GetSoulSpace(
	);

	//接收：获取被攻击列表
	virtual void OnRecv_GetAttackedList(
	);

	//接收：获取每日奖励
	virtual bool OnRecv_TakeDayPrize(
		shared_func<STakeDayPrizeAck>& fnAck //返回回调函数
	);
    
	//接收：领取每层奖励
	virtual bool OnRecv_TakeLayerPrize(
		UINT32 dwFloorID, //层数
		shared_func<STakeLayerPrizeAck>& fnAck //返回回调函数
	);

	//接收：获取最高已领奖层
	virtual bool OnRecv_GetTopPrizeLayer(
		shared_func<SGetTopPrizeLayerAck>& fnAck //返回回调函数
	);

	//接收：清除pve战斗cd
	virtual bool OnRecv_ClearFightMonsterCd(
		shared_func<SClearFightMonsterCdAck>& fnAck //返回回调函数
	);

	//接收：获取已领奖励层数
	virtual bool OnRecv_GetLayerPrized(
		shared_func<SGetLayerPrizedAck>& fnAck //返回回调函数
	);
};

extern CDemonTowerSvrS g_DemonTowerSvrS;
