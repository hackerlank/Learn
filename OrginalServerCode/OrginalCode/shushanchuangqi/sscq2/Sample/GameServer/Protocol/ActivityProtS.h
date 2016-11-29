#pragma once
#include "ActivityProtSvr.h"
using namespace NActivityProt;

class CActivityProtS : public CActivityProtSvr
{
public:
    //接收：请求获得奖池
	virtual bool OnRecv_GetActivityPool(
		shared_func<SGetActivityPoolAck>& fnAck //返回回调函数
	);
	//接收：请求活力奖励
	virtual bool OnRecv_GetActivityAward(
		const SActivityAward& stActivityGet, //奖励Id
		shared_func<SGetActivityAwardAck>& fnAck //返回回调函数
	);
	//接收：获取活力任务详情
	virtual void OnRecv_GetAllInfoActivity(
	);

	//接收：获取成就分享信息
	virtual bool OnRecv_GeShareList(
		shared_func<SGeShareListAck>& fnAck //返回回调函数
	);

	//接收：获取成就分享奖励
	virtual bool OnRecv_TakeSharePrize(
		UINT32 dwActivityID, //成就ID
		shared_func<STakeSharePrizeAck>& fnAck //返回回调函数
	);

public:
	void SendSysMsgIDNotify(EActivityResult eResult);
};
