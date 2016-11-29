#pragma once
#include "ExampleSvr.h"

class CExampleS : public NExample::CExampleSvr
{
public:
	//接收：C->S示例函数1
	virtual void OnRecv_SampleFunc1(
		INT8 byParam1, //8位有符号整数
		INT16 wParam2, //16位有符号整数
		INT32 dwParam3, //32位有符号整数
		INT64 qwParam4, //64位有符号整数
		UINT8 byParam5, //8位无符号整数
		UINT16 wParam6, //16位无符号整数
		UINT32 dwParam7, //32位无符号整数
		UINT64 qwParam8, //64位无符号整数
		bool bParam9, //布尔值
		float fParam10, //单精度浮点数
		double dParam11, //双精度浮点数
		const std::string& strParam12, //字符串
		const std::string& strParam13, //AS字节数组
		NExample::EExTest eTest14, //枚举值
		const NExample::TVecExDescend4& vecSesc15 //继承结构体列表
		);

	//接收：C->S有返回值的示例函数
	virtual bool OnRecv_SampleRetFunc2(
		UINT8 byParam1, //参数1，不保存
		UINT64 qwParam2, //参数2，保存
		shared_func<SSampleRetFunc2Ack>& fnAck //返回回调函数
		);
};