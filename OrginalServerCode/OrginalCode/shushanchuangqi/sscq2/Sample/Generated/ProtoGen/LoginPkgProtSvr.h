/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LoginPkgProt.h
//  Purpose:      累计登入礼包协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LoginPkgProt.h"

namespace NLoginPkgProt
{

//协议类：累计登入礼包协议
class CLoginPkgProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：登入礼包信息
	bool Send_SendPkgInfo( //发送给当前协议处理的客户端
		UINT16 wDays, //连续登入的天数
		UINT16 wResult //操作结果:从地位向高位，1表示领取，0表示没有领
	);
	bool SendClt_SendPkgInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wDays, //连续登入的天数
		UINT16 wResult //操作结果:从地位向高位，1表示领取，0表示没有领
	);
	std::string& BuildPkg_SendPkgInfo( //只组包不发送
		UINT16 wDays, //连续登入的天数
		UINT16 wResult //操作结果:从地位向高位，1表示领取，0表示没有领
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetLoginPkgAck : public CClientFuncAck
	{
		UINT16 wResult; //操作结果:从地位向高位，1表示领取，0表示没有领
		EResultInLoginProt eResult; //操作结果

		SGetLoginPkgAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取礼包
	virtual bool OnRecv_GetLoginPkg(
		UINT8 byIndex, //累计天数
		shared_func<SGetLoginPkgAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPkgInfoAck : public CClientFuncAck
	{
		UINT16 wDays; //连续登入的天数
		UINT16 wResult; //操作结果:从地位向高位，1表示领取，0表示没有领

		SGetPkgInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：登入礼包信息
	virtual bool OnRecv_GetPkgInfo(
		shared_func<SGetPkgInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 92; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetLoginPkg(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPkgInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLoginPkgProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLoginPkgProt
