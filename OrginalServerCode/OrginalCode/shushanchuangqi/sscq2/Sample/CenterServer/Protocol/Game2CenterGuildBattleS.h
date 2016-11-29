#ifndef GAME_2_CENTER_GUILD_BATTLE_S_H
#define GAME_2_CENTER_GUILD_BATTLE_S_H

#pragma once

#include "Game2CenterGuildBattleSvr.h"

using namespace NGame2CenterGuildBattle;

class CGame2CenterGuildBattleS: public CGame2CenterGuildBattleSvr
{
    public:
        virtual ~CGame2CenterGuildBattleS();

	//接收：帮派战状态设定
	virtual void OnRecv_SetState(
		NGuildBattleProt::EGBState eState //当前帮派战状态
	);
	//接收：帮派战用户报名
	virtual bool OnRecv_UserSignUp(
		UINT64 qwRoleID, //玩家ID
		shared_func<SUserSignUpAck>& fnAck //返回回调函数
	);
	//接收：帮派战相关广播
	virtual void OnRecv_InfoNotify(
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	//接收：是否有帮派战操作权限
	virtual bool OnRecv_GetAuthority(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetAuthorityAck>& fnAck //返回回调函数
	);
	//接收：增加帮派战积分
	virtual void OnRecv_AddScore(
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore, //帮派战积分
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);
	//接收：增加帮派战帮派积分
	virtual void OnRecv_AddGuildScore(
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore //帮派战积分
	);
	//接收：增加帮派战成员积分
	virtual void OnRecv_AddMemberScore(
		UINT64 qwGuildID, //帮派ID
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);
	//接收：获取帮派战相关面板信息
	virtual bool OnRecv_GetPanelInfo(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetPanelInfoAck>& fnAck //返回回调函数
	);
	//接收：更新帮派战积分排名
	virtual void OnRecv_SyncGuildRank(
	);

	//接收：帮派战状态设定
	virtual void OnRecv_NewSetState(
		NNewGuildBattleProt::ENGBState eState //当前帮派战状态
	);

	//接收：获取帮派ID
	virtual bool OnRecv_NewGetGuildID(
		UINT64 qwRoleID, //玩家ID
		shared_func<SNewGetGuildIDAck>& fnAck //返回回调函数
	);

};

#endif
