/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Example.h
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Example.h"

namespace NExample
{

//协议类：通信协议示例
class CExampleSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：S->C示例函数1
	bool Send_SampleFuncAck1( //发送给当前协议处理的客户端
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
		EExTest eTest14, //枚举值
		const TVecExDescend4& vecExDesc15 //继承结构体列表
	);
	bool SendClt_SampleFuncAck1(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
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
		EExTest eTest14, //枚举值
		const TVecExDescend4& vecExDesc15 //继承结构体列表
	);
	std::string& BuildPkg_SampleFuncAck1( //只组包不发送
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
		EExTest eTest14, //枚举值
		const TVecExDescend4& vecExDesc15 //继承结构体列表
	);
	std::string& BuildParamPkg_SampleFuncAck1( //只对参数组包
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
		EExTest eTest14, //枚举值
		const TVecExDescend4& vecExDesc15 //继承结构体列表
	);
	std::string& BuildFullPkg_SampleFuncAck1( //从参数包构造完整的协议函数包
		const string& strParamPkg //参数包
	);

	/////////////////////以下的接收函数需要重载/////////////////////
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
		EExTest eTest14, //枚举值
		const TVecExDescend4& vecExDesc15 //继承结构体列表
	) = 0;

	struct SSampleRetFunc2Ack : public CClientFuncAck
	{
		TVecExDescend3 vecExDescend; //结构体列表，返回值
		std::string strRet; //字符串，返回值

		SSampleRetFunc2Ack(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：C->S有返回值的示例函数
	virtual bool OnRecv_SampleRetFunc2(
		UINT8 byParam1, //参数1，不保存
		UINT64 qwParam2, //参数2，保存
		shared_func<SSampleRetFunc2Ack>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 255; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_SampleFunc1(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SampleRetFunc2(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CExampleSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NExample
