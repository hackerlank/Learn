/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GameSvrBasic.h
//  Purpose:      GameServer的基本协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GameSvrBasic.h"

namespace NGameSvrBasic
{

//协议类：GameServer的基本协议
class CGameSvrBasicSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：GM指令结果返回
	bool Send_GMCommandAck( //发送给当前协议处理的客户端
		const std::string& strResult //指令结果
	);
	bool SendClt_GMCommandAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const std::string& strResult //指令结果
	);
	std::string& BuildPkg_GMCommandAck( //只组包不发送
		const std::string& strResult //指令结果
	);

	//发送：打开所有功能
	bool Send_OpenAllSystem( //发送给当前协议处理的客户端
		bool bOpen //是否打开
	);
	bool SendClt_OpenAllSystem(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		bool bOpen //是否打开
	);
	std::string& BuildPkg_OpenAllSystem( //只组包不发送
		bool bOpen //是否打开
	);

	//发送：服务器断开连接通知
	bool Send_ServerDisconnectNtf( //发送给当前协议处理的客户端
		EBreakReason eBreakReason //断开连接原因
	);
	bool SendClt_ServerDisconnectNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EBreakReason eBreakReason //断开连接原因
	);
	std::string& BuildPkg_ServerDisconnectNtf( //只组包不发送
		EBreakReason eBreakReason //断开连接原因
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SKeepAliveAck : public CClientFuncAck
	{
		UINT32 dwServerTime; //服务器的当前时间(1970年1月1日0时开始的秒数)

		SKeepAliveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：心跳
	virtual bool OnRecv_KeepAlive(
		shared_func<SKeepAliveAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 13; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGameSvrBasicSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGameSvrBasic
