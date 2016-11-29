#pragma once
#include "SittingProtSvr.h"
using namespace NSittingProt;

class CSittingProtS : public CSittingProtSvr
{
public:
	//接收：请求双修
	virtual bool OnRecv_DoSittingTogether(
		UINT64 qwOtherID, //对方ID
		shared_func<SDoSittingTogetherAck>& fnAck //返回回调函数
	) ;
 //接收：请求取消修炼
	virtual void OnRecv_CancelSitting(
	) ;

public:
	void SendSysMsgIDNotify(ESittingResult eResult);
};
