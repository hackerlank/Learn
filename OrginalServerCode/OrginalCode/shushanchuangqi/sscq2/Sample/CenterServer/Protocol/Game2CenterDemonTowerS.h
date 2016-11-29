#pragma once
#include "Game2CenterDemonTowerSvr.h"
#include "stdafx.h"
#include "DemonTower.h"
using namespace NGame2CenterDemonTower;


class CGame2CenterDemonTowerS : public CGame2CenterDemonTowerSvr
{
    public:
	//接收：玩家进入镇妖塔
	virtual void OnRecv_OnEnterDemonTower(
		const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
	);

    //接收：玩家离开镇妖塔
	virtual void OnRecv_OnLeaveDemonTower(
		UINT64 qwUserID //玩家账号
	) ;

	//接收：镇妖塔过关
	virtual void OnRecv_OnPassDemonTower(
		UINT64 qwUserID, //玩家账号
		UINT16 wFloorID, //过关层数
        UINT16 wMonsterColor, //怪物颜色 
        const std::string& strMonsterName //封印怪物
	);
	
    //接收：击败锁妖塔怪物
	virtual void OnRecv_OnKillMonster(
		const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
	);


	//接收：19点重置事件
	virtual void OnRecv_OnPlayerReset(
		UINT64 qwUserID //玩家账号
	);

	//接收：玩家进入下一层
	virtual void OnRecv_OnPlayerEnterNextFloor(
		UINT64 qwUserID //玩家账号
	) ;

    //接收：玩家进入请求
	virtual void OnRecv_PlayerEnterFloorRequest(
		UINT64 qwUserID, //玩家账号
		UINT32 dwFloorID //层数
	);

	//接收：获取玩家被攻击信息列表
	virtual bool OnRecv_GetAttackedLayerInfo(
		UINT64 qwUserID, //玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
		shared_func<SGetAttackedLayerInfoAck>& fnAck //返回回调函数
	);


};
extern CGame2CenterDemonTowerS g_Game2CenterDemonTowerS;
