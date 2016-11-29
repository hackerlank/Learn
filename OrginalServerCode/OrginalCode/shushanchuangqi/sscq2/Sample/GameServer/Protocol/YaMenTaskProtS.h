#pragma once
#include "YaMenTaskProtSvr.h"
using namespace NYaMenTaskProt;

class CYaMenTaskProtS : public CYaMenTaskProtSvr
{
public:
    //接收：请求操作
	virtual bool OnRecv_YaMenTaskOp(
		shared_func<SYaMenTaskOpAck>& fnAck //返回回调函数
	) ;
	//接收：刷新衙门任务列表
	virtual bool OnRecv_FlushTask(
		shared_func<SFlushTaskAck>& fnAck //返回回调函数
	) ;
	//接收：获取衙门任务详情
	virtual void OnRecv_GetAllInfoTask(
	) ;
    //接收：购买衙门任务
	virtual bool OnRecv_BuyTaskTimes(
		shared_func<SBuyTaskTimesAck>& fnAck //返回回调函数
	);
private:
	void SendSysMsgIDNotify(EYaMenTaskResult eResult);
};
