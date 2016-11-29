/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GameSvrComm.h
//  Purpose:      GameServer之间的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GameSvrComm.h"

namespace NGameSvrComm
{

//协议类：GameServer之间的通信协议
class CGameSvrCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：测试函数返回
	bool Send_TestFuncAck( //发送给当前协议处理的服务器
		const STest& rTest //参数1
	);
	bool SendSvr_TestFuncAck(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const STest& rTest //参数1
	);
	std::string& BuildPkg_TestFuncAck( //只组包不发送
		const STest& rTest //参数1
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：测试函数请求
	virtual void OnRecv_TestFuncReq(
		const STest& rTest //参数1
	) = 0;

	struct STestRetFuncReqAck : public CServerFuncAck
	{
		UINT32 dwRetParam; //返回参数1

		STestRetFuncReqAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：测试返回函数请求
	virtual bool OnRecv_TestRetFuncReq(
		const STest& rTest, //参数1
		shared_func<STestRetFuncReqAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 67; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_TestFuncReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TestRetFuncReq(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGameSvrCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGameSvrComm
