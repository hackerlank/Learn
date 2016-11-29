#pragma once

#include "BeautySvr.h"

#include "stdafx.h"

using namespace NBeauty;

class CBeautyS : public CBeautySvr
{
public:
	//接收：获取美女信息
	virtual bool OnRecv_GetBeatyInfo(
		shared_func<SGetBeatyInfoAck>& fnAck //返回回调函数
	);

	//接收：结识美女
	virtual bool OnRecv_MeetBeauty(
		UINT16 wBeautyID, //美女id
		shared_func<SMeetBeautyAck>& fnAck //返回回调函数
	);

	//接收：和美女聊天
	virtual bool OnRecv_ChatBeauty(
		UINT16 wBeautyID, //美女id
		shared_func<SChatBeautyAck>& fnAck //返回回调函数
	);

	//接收：送美女礼品
	virtual bool OnRecv_SendPrizeBeauty(
		UINT16 wBeautyID, //美女id
		const NItemProt::TVecItemCount& vecItemCount, //物品列表
		shared_func<SSendPrizeBeautyAck>& fnAck //返回回调函数
	);

	//接收：抽奖
	virtual bool OnRecv_LotteryBeauty(
		ELotteryBeautyType eLotteryBeautyType, //抽奖类型
		shared_func<SLotteryBeautyAck>& fnAck //返回回调函数
	);

	//接收：美女出战
	virtual bool OnRecv_BeautyFight(
		UINT16 wBeautyID, //美女id
		shared_func<SBeautyFightAck>& fnAck //返回回调函数
	);

    //接收：获取稀有物品列表
    virtual bool OnRecv_GetRareItemList(
	shared_func<SGetRareItemListAck>& fnAck //返回回调函数
    );

	//接收：获取当前已免费抽奖次数
	virtual void OnRecv_GetLotteryFreeCnt(
	);
};

extern CBeautyS g_BeautyS;
