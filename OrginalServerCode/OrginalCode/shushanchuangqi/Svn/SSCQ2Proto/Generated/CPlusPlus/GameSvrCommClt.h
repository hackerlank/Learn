/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    GameSvrComm.h
//  Purpose:      GameServer之间的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GameSvrComm.h"

namespace NGameSvrComm
{

//协议类：GameServer之间的通信协议
class CGameSvrCommClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：测试函数请求
	bool Send_TestFuncReq( //发送给当前协议处理的服务器
		const STest& rTest //参数1
	);
	bool SendSvr_TestFuncReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const STest& rTest //参数1
	);
	std::string& BuildPkg_TestFuncReq( //只组包不发送
		const STest& rTest //参数1
	);

	//发送：测试返回函数请求
	bool Send_TestRetFuncReq( //发送给当前协议处理的服务器
		const STest& rTest, //参数1
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const STest& rTest, //(本地保存的函数参数)参数1
			UINT32 dwRetParam //(返回值)返回参数1
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_TestRetFuncReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const STest& rTest, //参数1
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const STest& rTest, //(本地保存的函数参数)参数1
			UINT32 dwRetParam //(返回值)返回参数1
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：测试函数返回
	virtual void OnRecv_TestFuncAck(
		const STest& rTest //参数1
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 67; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_TestFuncAck(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_TestRetFuncReq(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_TestRetFuncReq(UINT32 dwSessionID);

private:
	typedef bool (CGameSvrCommClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGameSvrCommClt::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGameSvrComm
