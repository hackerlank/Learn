#pragma once
#include "GameSvrCommClt.h"

using namespace NGameSvrComm;

class CGameSvrCommC : public CGameSvrCommClt
{
public:
	//接收：测试函数返回
	virtual void OnRecv_TestFuncAck(
		const STest& rTest //参数1
		);
};