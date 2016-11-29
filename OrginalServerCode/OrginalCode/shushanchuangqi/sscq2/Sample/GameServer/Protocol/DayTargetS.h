#pragma once

#include "DayTargetSvr.h"

#include "stdafx.h"

using namespace NDayTarget;

class CDayTargetS : public CDayTargetSvr
{
public:

	//接收：获取任务列表
	virtual bool OnRecv_GetTaskList(
		shared_func<SGetTaskListAck>& fnAck //返回回调函数
	);

	//接收：领取奖励
	virtual bool OnRecv_TakePrize(
		UINT16 wTaskID, //任务ID
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	);


};

extern CDayTargetS g_DayTargetS;
