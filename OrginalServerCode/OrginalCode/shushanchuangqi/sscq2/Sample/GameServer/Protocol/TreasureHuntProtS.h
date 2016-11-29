
#pragma once
#include "TreasureHuntProtSvr.h"

using namespace NTreasureHuntProt;

class CTreasureHuntProtS : public CTreasureHuntProtSvr 
{
public:

    //接收：请求寻宝信息
	virtual bool OnRecv_ReqTHInfo(
		shared_func<SReqTHInfoAck>& fnAck //返回回调函数
	);
    
    //接收：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
	virtual bool OnRecv_ReqTHBattlePrepareInfo(
		shared_func<SReqTHBattlePrepareInfoAck>& fnAck //返回回调函数
	);

	//接收：请求寻宝开始
	virtual bool OnRecv_ReqTHStart(
		UINT8 byCopyID, //副本ID
		shared_func<SReqTHStartAck>& fnAck //返回回调函数
	);
    
    //接收：请求寻宝立即完成
	virtual bool OnRecv_ReqTHQuickFinish(
		shared_func<SReqTHQuickFinishAck>& fnAck //返回回调函数
	);

    //接收：请求放弃寻宝
	virtual bool OnRecv_ReqTHGiveUp(
		shared_func<SReqTHGiveUpAck>& fnAck //返回回调函数
	);

	//接收：请求使用Buff
	virtual bool OnRecv_ReqUseBuff(
		UINT8 byBuffID, //BuffID
		shared_func<SReqUseBuffAck>& fnAck //返回回调函数
	);

	//接收：请求寻宝奖励信息
	virtual bool OnRecv_ReqTHAwardInfo(
		shared_func<SReqTHAwardInfoAck>& fnAck //返回回调函数
	);

    //接收：获取寻宝奖励
	virtual bool OnRecv_GetTHAward(
		shared_func<SGetTHAwardAck>& fnAck //返回回调函数
	);

};

extern CTreasureHuntProtS g_TreasureHuntProtS;

