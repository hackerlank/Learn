/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Gate2GameComm.h
//  Purpose:      GateServer到GameServer的通信协议
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

namespace NGate2GameComm
{

//协议类：GateServer到GameServer的通信协议
class CGate2GameCommSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帐号进入GameServer通知
	bool Send_UserEnterNtf( //发送给当前协议处理的服务器
		UINT64 qwUsrID //帐号ID
	);
	bool SendSvr_UserEnterNtf(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID //帐号ID
	);
	std::string& BuildPkg_UserEnterNtf( //只组包不发送
		UINT64 qwUsrID //帐号ID
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

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：心跳
	virtual void OnRecv_KeepAlive(
	) = 0;

	//接收：玩家下线通知
	virtual void OnRecv_UserLogoutNtf(
		UINT64 qwUsrID, //帐号ID
		NServerCommon::ELeaveType eLeaveType //下线类型
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 7; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserLogoutNtf(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGate2GameCommSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGate2GameComm
