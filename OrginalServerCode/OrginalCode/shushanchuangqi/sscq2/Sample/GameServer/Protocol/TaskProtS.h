#pragma once
#include "TaskProtSvr.h"

using namespace NTaskProt;

class CTaskProtS : public CTaskProtSvr
{
public:
	//接收：接受任务请求
	virtual bool OnRecv_AcceptTaskReq(
        UINT8 byCost,//0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		UINT16 wTaskID, //任务ID
        shared_func<SAcceptTaskReqAck>& fnAck //返回回调函数
		);

	//接收：放弃任务请求
	virtual bool OnRecv_GiveUpTask(
		UINT16 wTaskID, //任务ID
		shared_func<SGiveUpTaskAck>& fnAck //返回回调函数
		);

	//接收：完成任务请求(领取奖励)
	virtual bool OnRecv_FinishTask(
        UINT8 byCost,//0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		UINT16 wTaskID, //任务ID
		UINT8 byIndex, //可选择的奖励索引
		shared_func<SFinishTaskAck>& fnAck //返回回调函数
		);
/*
	//接收：立刻完成任务请求
	virtual bool OnRecv_FinishTaskReq(
		UINT16 wTaskID, //任务ID
		shared_func<SFinishTaskReqAck>& fnAck //返回回调函数
		);
*/
	//接收：获得任务列表
	virtual void OnRecv_GetTaskList(
	);

    //接收：完成特殊任务请求
    virtual void OnRecv_FinishSpeTask(
        UINT16 wTaskID //任务ID
    );
    //接收：获得环任务信息
	virtual void OnRecv_GetCircleTaskInfo(
	) ;
	//接收：完成所有的环任务
	virtual bool OnRecv_FinishCircleTaskOneKey(
		shared_func<SFinishCircleTaskOneKeyAck>& fnAck //返回回调函数
	);
//接收：提升环任务星级
	virtual bool OnRecv_UpdateCircleTaskStar(
		shared_func<SUpdateCircleTaskStarAck>& fnAck //返回回调函数
	) ;


public:
	void SendSysMsgIDNotify(ETaskResult eResult,CUser& rUser);
};
