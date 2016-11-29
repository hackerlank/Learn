
#pragma once
#include "BossProtSvr.h"

using namespace NBossProt;

class CBossProtS : public CBossProtSvr
{
public:
   	//接收：世界BOSS中复活
	virtual bool OnRecv_WBAlive(
		shared_func<SWBAliveAck>& fnAck //返回回调函数
	) ;

	//接收：加持
	virtual bool OnRecv_WBStrength(
		EBossBuyType eBuyType, //购买类型
		shared_func<SWBStrengthAck>& fnAck //返回回调函数
	) ;
	
    //接收：直接攻击boss
	virtual bool OnRecv_WBAttack(
		shared_func<SWBAttackAck>& fnAck //返回回调函数
	);


	//接收：获取排行榜信息
	virtual void OnRecv_GetTopList(
	) ;

	//接收：获取玩家自己的排行榜信息
	virtual void OnRecv_GetSelfInfo(
	) ;

	//接收：获取boss信息
	virtual void OnRecv_GetBossInfo(
	) ;

	//接收：进入boss地图
	virtual bool OnRecv_EnterMap(
		shared_func<SEnterMapAck>& fnAck //返回回调函数
	) ;

	//接收：离开boss地图
	virtual bool OnRecv_LeaveMap(
		shared_func<SLeaveMapAck>& fnAck //返回回调函数
	) ;

private:
};

extern CBossProtS g_BossProtS;
