#pragma once
#include "GroupTaskProtSvr.h"
using namespace NGroupTaskProt;

class CGroupTaskProtS : public CGroupTaskProtSvr
{
public:
    //接收：请求操作
	virtual bool OnRecv_GroupTaskOp(
		shared_func<SGroupTaskOpAck>& fnAck //返回回调函数
	) ;
	//接收：刷新师门任务列表
	virtual bool OnRecv_FlushTask(
		shared_func<SFlushTaskAck>& fnAck //返回回调函数
	) ;
	//接收：获取师门任务详情
	virtual void OnRecv_GetAllInfoTask(
	) ;
    //接收：购买师门任务
	virtual bool OnRecv_BuyTaskTimes(
		shared_func<SBuyTaskTimesAck>& fnAck //返回回调函数
	);
private:
	void SendSysMsgIDNotify(EGroupTaskResult eResult);
};
