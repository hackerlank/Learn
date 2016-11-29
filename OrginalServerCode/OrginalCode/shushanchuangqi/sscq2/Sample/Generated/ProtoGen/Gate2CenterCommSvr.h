/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
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
class CGate2CenterCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家登录通知
	bool Send_UserWantLoginNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwCryptoCode //登录验证码
	);
	bool SendSvr_UserWantLoginNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT32 dwCryptoCode //登录验证码
	);
	std::string& BuildPkg_UserWantLoginNtf( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT32 dwCryptoCode //登录验证码
	);

	//发送：踢玩家下线
	bool Send_KickUserOffLine( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);
	bool SendSvr_KickUserOffLine(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);
	std::string& BuildPkg_KickUserOffLine( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	);

	//发送：替换帐号
	bool Send_ReplaceUser( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_ReplaceUser(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUsrID //(本地保存的函数参数)帐号ID
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：心跳
	virtual void OnRecv_KeepAlive(
		UINT32 dwUsrCnt //玩家数量
	) = 0;

	//接收：玩家上线通知
	virtual void OnRecv_UserLoginNtf(
		UINT64 qwUsrID, //帐号ID
		const std::string& strIPAddr //IP地址
	) = 0;

	//接收：玩家下线通知
	virtual void OnRecv_UserLogoutNtf(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 6; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLoginNtf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLogoutNtf(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_ReplaceUser(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_ReplaceUser(UINT32 dwSessionID);

private:
	typedef bool (CGate2CenterCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGate2CenterCommSvr::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGate2CenterComm
