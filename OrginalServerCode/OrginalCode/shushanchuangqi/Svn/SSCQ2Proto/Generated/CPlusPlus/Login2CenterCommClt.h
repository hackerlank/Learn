/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Login2CenterComm.h
//  Purpose:      LoginServer到CenterServer的基本通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Login2CenterComm.h"

namespace NLogin2CenterComm
{

//协议类：LoginServer到CenterServer的基本通信协议
class CLogin2CenterCommClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：心跳
	bool Send_KeepAlive( //发送给当前协议处理的服务器
	);
	bool SendSvr_KeepAlive(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_KeepAlive( //只组包不发送
	);

	//发送：玩家请求进入服务器
	bool Send_UserLoginReq( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		UINT8 byAddrType //地址类型
	);
	bool SendSvr_UserLoginReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		UINT8 byAddrType //地址类型
	);
	std::string& BuildPkg_UserLoginReq( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		UINT8 byAddrType //地址类型
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：玩家请求进入服务器应答
	virtual void OnRecv_UserLoginAck(
		EReqResult eResult, //登陆请求的结果
		UINT64 qwUsrID, //帐号ID
		UINT32 dwSessionID, //会话ID
		const std::string& strGateAddr, //GateServer的地址
		UINT16 wGatePort, //GateServer的端口
		UINT32 dwCryptoCode //登录验证码
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 2; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_UserLoginAck(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLogin2CenterCommClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLogin2CenterComm
