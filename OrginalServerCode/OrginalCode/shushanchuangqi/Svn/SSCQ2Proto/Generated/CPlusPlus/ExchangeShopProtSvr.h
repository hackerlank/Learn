/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ExchangeShopProt.h
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ExchangeShopProt.h"

namespace NExchangeShopProt
{

//协议类：兑换商店
class CExchangeShopProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：已兑换信息更新
	bool Send_ExchangeItemUpdate( //发送给当前协议处理的客户端
		const ExchangeInfo& oExchangeInfo //更新已兑换信息
	);
	bool SendClt_ExchangeItemUpdate(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const ExchangeInfo& oExchangeInfo //更新已兑换信息
	);
	std::string& BuildPkg_ExchangeItemUpdate( //只组包不发送
		const ExchangeInfo& oExchangeInfo //更新已兑换信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SExchangeItemAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果

		SExchangeItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：兑换物品
	virtual bool OnRecv_ExchangeItem(
		UINT32 dwExchangeID, //兑换id
		UINT32 dwCount, //兑换数量
		shared_func<SExchangeItemAck>& fnAck //返回回调函数
	) = 0;

	struct SExchangeItemListAck : public CClientFuncAck
	{
		TVecExchangeInfo vecExchangeInfo; //已兑换列表

		SExchangeItemListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：已兑换列表
	virtual bool OnRecv_ExchangeItemList(
		shared_func<SExchangeItemListAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 101; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_ExchangeItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ExchangeItemList(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CExchangeShopProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NExchangeShopProt
