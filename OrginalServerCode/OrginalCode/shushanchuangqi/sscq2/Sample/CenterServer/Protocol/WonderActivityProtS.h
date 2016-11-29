#pragma once
#include "WonderActivityProtSvr.h"

using namespace NWonderActivityProt;

class CWonderActivityProtS : public CWonderActivityProtSvr
{
public:	
	//接收：获得活动时间配置
	virtual bool OnRecv_GetConfigTime(
		UINT16 wWActID, //精彩活动ID
		shared_func<SGetConfigTimeAck>& fnAck //返回回调函数
	);
    //接收：获得活动所有奖励配置
	virtual bool OnRecv_GetAllPrize(
		UINT16 wWActID, //精彩活动ID
		shared_func<SGetAllPrizeAck>& fnAck //返回回调函数
	);
    //接收：获得活动列表
	virtual bool OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	);
    void SendSysMsg();
	//接收：玩家领奖
	virtual bool OnRecv_TakePrize(
		UINT16 wActID, //精彩活动ID
		UINT32 wCond, //条件
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);
    //接收：玩家活动信息
	virtual bool OnRecv_GetRoleActInfo(
		UINT16 wActID, //活动ID
		shared_func<SGetRoleActInfoAck>& fnAck //返回回调函数
	);
    //接收：玩家在所有活动中的状态
	virtual bool OnRecv_GetRoleAllState(
		shared_func<SGetRoleAllStateAck>& fnAck //返回回调函数
	);
	//接收：请求七星龙珠活动信息
	virtual bool OnRecv_GetDragonBallAct(
		shared_func<SGetDragonBallActAck>& fnAck //返回回调函数
	);
	//接收：请求七日消费活动信息
	virtual bool OnRecv_GetSevenConsumeAct(
		shared_func<SGetSevenConsumeActAck>& fnAck //返回回调函数
	);
	//接收：请求Q养成活动信息
	virtual void OnRecv_GetQQCoinAct(
	);
	//接收：兑换仙石或者领取Q币
	virtual bool OnRecv_ExChange(
		UINT8 byType, //0表示Q币，1表示仙石
		shared_func<SExChangeAck>& fnAck //返回回调函数
	);
private:
};

extern CWonderActivityProtS g_WonderActivityProtS;
