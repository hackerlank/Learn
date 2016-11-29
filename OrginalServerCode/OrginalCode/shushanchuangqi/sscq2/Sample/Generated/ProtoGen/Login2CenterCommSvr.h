/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Login2CenterComm.h
//  Purpose:      LoginServer到CenterServer的基本通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Login2CenterComm.h"

namespace NLogin2CenterComm
{

//协议类：LoginServer到CenterServer的基本通信协议
class CLogin2CenterCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家请求进入服务器应答
	bool Send_UserLoginAck( //发送给当前协议处理的服务器
		EReqResult eResult, //登陆请求的结果
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		const std::string& strGateAddr, //GateServer的地址
		UINT16 wGatePort, //GateServer的端口
		UINT32 dwCryptoCode //登录验证码
	);
	bool SendSvr_UserLoginAck(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		EReqResult eResult, //登陆请求的结果
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		const std::string& strGateAddr, //GateServer的地址
		UINT16 wGatePort, //GateServer的端口
		UINT32 dwCryptoCode //登录验证码
	);
	std::string& BuildPkg_UserLoginAck( //只组包不发送
		EReqResult eResult, //登陆请求的结果
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		const std::string& strGateAddr, //GateServer的地址
		UINT16 wGatePort, //GateServer的端口
		UINT32 dwCryptoCode //登录验证码
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：心跳
	virtual void OnRecv_KeepAlive(
	) = 0;

	//接收：玩家请求进入服务器
	virtual void OnRecv_UserLoginReq(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		UINT8 byAddrType //地址类型
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 2; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLoginReq(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLogin2CenterCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLogin2CenterComm
