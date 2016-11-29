#pragma once
#include "VIPProtSvr.h"
using namespace NVIPProt;

class CVIPProtS : public CVIPProtSvr
{
public:
	//接收：请求个人VIP特权信息
	virtual void OnRecv_GetVIPInfo(
	);

	//接收：请求开启个人VIP特权
	virtual bool OnRecv_OpenSelfVIP(
		UINT8 byType, //VIP特权类型
		shared_func<SOpenSelfVIPAck>& fnAck //返回回调函数
	);

	//接收：请求开启好友VIP特权
	virtual bool OnRecv_OpenOtherVIP(
		UINT8 byType, //VIP特权类型
		UINT64 qwRoleID, //好友玩家ID
		UINT64 qwRoleID2, //好友玩家ID(匹配验证)
		shared_func<SOpenOtherVIPAck>& fnAck //返回回调函数
	);

	//接收：请求开启个人月卡
	virtual bool OnRecv_OpenSelfMonthCard(
		shared_func<SOpenSelfMonthCardAck>& fnAck //返回回调函数
	);

	//接收：请求开启好友月卡
	virtual bool OnRecv_OpenOtherMonthCard(
		UINT64 qwRoleID, //好友玩家ID
		shared_func<SOpenOtherMonthCardAck>& fnAck //返回回调函数
	);

	//接收：领取VIP特权每日礼包
	virtual bool OnRecv_GetDayPackAward(
		shared_func<SGetDayPackAwardAck>& fnAck //返回回调函数
	);

	//接收：领取VIP特权等级奖励
	virtual bool OnRecv_GetVIPLevelAward(
		UINT8 byLevel, //VIP等级
		shared_func<SGetVIPLevelAwardAck>& fnAck //返回回调函数
	);

public:
	void SendSysMsgIDNotify(EVIPResult eResult);
};
