
#pragma once
#include "DemonTowerGSSvr.h"

using namespace NDemonTowerGS;

//协议类：锁妖塔
class CDemonTowerSvrS : public CDemonTowerGSSvr
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



	//接收：镇守锁妖塔
	virtual bool OnRecv_GuardAtk(
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		shared_func<SGuardAtkAck>& fnAck //返回回调函数
	) ;

    //接收：抢夺镇守位置
	virtual bool OnRecv_AtkPlayer(
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		shared_func<SAtkPlayerAck>& fnAck //返回回调函数
	);

	//接收：领取奖励
	virtual bool OnRecv_TakePrize(
		EDemonTowerPrize ePrizeType, //奖励类型
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);


	//接收：获取镇守榜
	virtual bool OnRecv_GetTopList(
		UINT16 wPage, //页码 1开始
		UINT16 wPageItemCount, //每页显示数目 默认5
		shared_func<SGetTopListAck>& fnAck //返回回调函数
	);

	//接收：获取本人镇妖塔相关信息
	virtual bool OnRecv_GetDemonTowerInfo(
		shared_func<SGetDemonTowerInfoAck>& fnAck //返回回调函数
	);

	//接收：获取镇守信息信息
	virtual bool OnRecv_GetGuardInfo(
		UINT32 dwFloorID, //镇守层
		shared_func<SGetGuardInfoAck>& fnAck //返回回调函数
	);

	//接收：恢复元神
	virtual void OnRecv_Restore(
		UINT32 dwCount //物品数量
	);

	//接收：增加聚魂速度
	virtual void OnRecv_AddSpeed(
		UINT32 dwCount //物品数量
	);

	//接收：获取玩家镇守信息
	virtual bool OnRecv_GetPlayerInfo(
		UINT64 qwUserID, //账号ID
		shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
	);

	//接收：清除pvp战斗cd
	virtual bool OnRecv_ClearFightCd(
		shared_func<SClearFightCdAck>& fnAck //返回回调函数
	);

	//接收：获取过关信息
	virtual bool OnRecv_GetPassInfo(
		UINT16 wFloorID, //通关层
		shared_func<SGetPassInfoAck>& fnAck //返回回调函数
	);

};

extern CDemonTowerSvrS g_DemonTowerSvrS;
