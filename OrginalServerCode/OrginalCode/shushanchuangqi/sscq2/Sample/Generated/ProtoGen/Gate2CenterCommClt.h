/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Gate2CenterComm.h
//  Purpose:      GateServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "ServerCommon.h"

namespace NGate2CenterComm
{

//协议类：GateServer到CenterServer的通信协议
class CGate2CenterCommClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：心跳
	bool Send_KeepAlive( //发送给当前协议处理的服务器
		UINT32 dwUsrCnt //玩家数量
	);
	bool SendSvr_KeepAlive(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwUsrCnt //玩家数量
	);
	std::string& BuildPkg_KeepAlive( //只组包不发送
		UINT32 dwUsrCnt //玩家数量
	);

	//发送：玩家上线通知
	bool Send_UserLoginNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strIPAddr //IP地址
	);
	bool SendSvr_UserLoginNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const std::string& strIPAddr //IP地址
	);
	std::string& BuildPkg_UserLoginNtf( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const std::string& strIPAddr //IP地址
	);

	//发送：玩家下线通知
	bool Send_UserLogoutNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);
	bool SendSvr_UserLogoutNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);
	std::string& BuildPkg_UserLogoutNtf( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：玩家登录通知
	virtual void OnRecv_UserWantLoginNtf(
		UINT64 qwUsrID, //帐号ID
		UINT32 dwCryptoCode //登录验证码
	) = 0;

	//接收：踢玩家下线
	virtual void OnRecv_KickUserOffLine(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	) = 0;

	struct SReplaceUserAck : public CServerFuncAck
	{
		SReplaceUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：替换帐号
	virtual bool OnRecv_ReplaceUser(
		UINT64 qwUsrID, //帐号ID
		shared_func<SReplaceUserAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 6; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_UserWantLoginNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_KickUserOffLine(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReplaceUser(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGate2CenterCommClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGate2CenterComm
