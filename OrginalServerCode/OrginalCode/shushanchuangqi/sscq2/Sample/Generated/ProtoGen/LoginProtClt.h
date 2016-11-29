/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    LoginProt.h
//  Purpose:      登陆LoginServer的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LoginProt.h"

namespace NLoginProt
{

//协议类：登陆LoginServer的协议
class CLoginProtClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：登陆请求
	bool Send_LoginReq( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 usGroupID, //区号
		UINT32 dwVersion, //版本号
		const std::string& strPassword //验证key
	);
	bool SendSvr_LoginReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 usGroupID, //区号
		UINT32 dwVersion, //版本号
		const std::string& strPassword //验证key
	);
	std::string& BuildPkg_LoginReq( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT16 usGroupID, //区号
		UINT32 dwVersion, //版本号
		const std::string& strPassword //验证key
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：登陆结果返回
	virtual void OnRecv_LoginAck(
		ELoginResult eLoginResult, //请求登录结果
		UINT64 qwRoleId, //角色ID
		const std::string& strGateIP, //GateServer的IP
		UINT16 wGatePort, //GateServer端口
		UINT32 dwCryptoCode //登录验证码
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 1; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_LoginAck(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLoginProtClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLoginProt
