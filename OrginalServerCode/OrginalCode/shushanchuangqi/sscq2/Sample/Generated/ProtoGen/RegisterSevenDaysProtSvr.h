/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    RegisterSevenDays.h
//  Purpose:      注册七天目标协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "RegisterSevenDaysProt.h"

namespace NRegisterSevenDaysProt
{

//协议类：注册七天目标协议
class CRegisterSevenDaysProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetCurTargetInfoAck : public CClientFuncAck
	{
		UINT32 dwDayID; //第几天
		UINT64 qwTargetInfo; //目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)

		SGetCurTargetInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求当天目标信息
	virtual bool OnRecv_GetCurTargetInfo(
		shared_func<SGetCurTargetInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTargetInfoByDayIDAck : public CClientFuncAck
	{
		UINT64 qwTargetInfo; //目标信息(注：每2位代表一个目标奖励的状态0：不能领取；1：能够领取；2：已领取)

		SGetTargetInfoByDayIDAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：通过dwDayID获取目标信息
	virtual bool OnRecv_GetTargetInfoByDayID(
		UINT32 dwDayID, //第几天
		shared_func<SGetTargetInfoByDayIDAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAwardAck : public CClientFuncAck
	{
		ERegisterSevenDaysResult eResult; //结果

		SGetAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取奖励
	virtual bool OnRecv_GetAward(
		UINT32 dwDayID, //第几天
		UINT8 byTargetID, //目标ID
		shared_func<SGetAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetCurBuyInfoAck : public CClientFuncAck
	{
		UINT32 dwDayID; //第几天
		EBuyStatus eBuyStatus; //购买状态

		SGetCurBuyInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求当天购买信息
	virtual bool OnRecv_GetCurBuyInfo(
		shared_func<SGetCurBuyInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReqBuyAck : public CClientFuncAck
	{
		ERegisterSevenDaysResult eResult; //结果

		SReqBuyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求购买
	virtual bool OnRecv_ReqBuy(
		shared_func<SReqBuyAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 89; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetCurTargetInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTargetInfoByDayID(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetCurBuyInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqBuy(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CRegisterSevenDaysProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NRegisterSevenDaysProt
