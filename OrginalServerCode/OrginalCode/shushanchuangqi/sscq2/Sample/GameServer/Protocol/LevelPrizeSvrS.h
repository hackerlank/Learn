#pragma once

#include "LevelPrizeSvr.h"

#include "stdafx.h"

using namespace NLevelPrize;

class CLevelPrizeSvrS : public CLevelPrizeSvr
{
public:
	//接收：获取奖励
	virtual bool OnRecv_TakePrize(
		UINT16 wActID, //活动Id
		UINT8 byIndex, //第几个奖励
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);
   //接收：获取奖励状态
	virtual bool OnRecv_GetPrizeInfo(
		UINT16 wActID, //活动Id
		shared_func<SGetPrizeInfoAck>& fnAck //返回回调函数
	);
    //接收：玩家在个人服活动中的状态
	virtual bool OnRecv_GetRoleState(
		shared_func<SGetRoleStateAck>& fnAck //返回回调函数
	);
	//接收：QQAlarm获取奖励
	virtual bool OnRecv_TakePrizeForQQAlarm(
		UINT16 wActID, //活动Id
		shared_func<STakePrizeForQQAlarmAck>& fnAck //返回回调函数
	);
	//接收：QQAlarm获取奖励状态
	virtual void OnRecv_GetStateForQQAlarm(
		UINT16 wActID //活动Id
	);
};
extern CLevelPrizeSvrS g_LevelPrizeSvrS;
