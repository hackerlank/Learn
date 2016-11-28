/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MoneyTree.h
//  Purpose:      摇钱树协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "MoneyTreeProt.h"

namespace NMoneyTreeProt
{

//协议类：摇钱树协议
class CMoneyTreeProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetMoneyTreeInfoAck : public CClientFuncAck
	{
		UINT16 todayUseCount; //今日使用次数

		SGetMoneyTreeInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求摇钱树信息
	virtual bool OnRecv_GetMoneyTreeInfo(
		shared_func<SGetMoneyTreeInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetMoneyAck : public CClientFuncAck
	{
		UINT16 todayUseCount; //今日使用次数

		SGetMoneyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求摇钱
	virtual bool OnRecv_GetMoney(
		shared_func<SGetMoneyAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 88; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetMoneyTreeInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetMoney(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CMoneyTreeProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NMoneyTreeProt
