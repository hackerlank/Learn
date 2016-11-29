
#pragma once
#include "BeautyLogGSSvr.h"

using namespace NBeautyLogGS;

//协议类：锁妖塔
class CBeautyLogSvrS : public CBeautyLogGSSvr
{
public:
	//接收：获取美女log信息
	virtual bool OnRecv_GetBeautyLog(
		shared_func<SGetBeautyLogAck>& fnAck //返回回调函数
	);
};

extern CBeautyLogSvrS g_BeautyLogSvrS;
