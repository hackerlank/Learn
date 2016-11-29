#pragma once
#include "GameSvrCommSvr.h"

using namespace NGameSvrComm;

class CGameSvrCommS : public CGameSvrCommSvr
{
public:
	//接收：测试函数请求
	virtual void OnRecv_TestFuncReq(
		const STest& rTest //参数1
		);

	//接收：测试返回函数请求
	virtual bool OnRecv_TestRetFuncReq(
		const STest& rTest, //参数1
        shared_func<STestRetFuncReqAck>& fnAck //返回回调函数
		);
};
