/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    FeedBackProt.h
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "FeedBackProt.h"

namespace NFeedBackProt
{

//协议类：消费回馈
class CFeedBackProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：回馈信息更新
	bool Send_FeedBackInfoNotify( //发送给当前协议处理的客户端
		const SFeedBackInfo& oFeedBackInfo //回馈信息
	);
	bool SendClt_FeedBackInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SFeedBackInfo& oFeedBackInfo //回馈信息
	);
	std::string& BuildPkg_FeedBackInfoNotify( //只组包不发送
		const SFeedBackInfo& oFeedBackInfo //回馈信息
	);

	//发送：回馈活动过期
	bool Send_FeedBackExpireNotify( //发送给当前协议处理的客户端
		UINT32 dwActID //活动id
	);
	bool SendClt_FeedBackExpireNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwActID //活动id
	);
	std::string& BuildPkg_FeedBackExpireNotify( //只组包不发送
		UINT32 dwActID //活动id
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetFeedBackListAck : public CClientFuncAck
	{
		TVecFeedBackInfo vecFeedBackInfo; //回馈信息列表
		TVecSBuyDiscountInfo vecSBuyDiscountInfo; //折扣限购信息

		SGetFeedBackListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取回馈列表
	virtual bool OnRecv_GetFeedBackList(
		shared_func<SGetFeedBackListAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyDisCountItemAck : public CClientFuncAck
	{
		EFeedBackRet eRet; //结果

		SBuyDisCountItemAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买折扣物品
	virtual bool OnRecv_BuyDisCountItem(
		UINT32 dwBuyID, //购买id
		UINT32 dwCount, //购买id数量
		shared_func<SBuyDisCountItemAck>& fnAck //返回回调函数
	) = 0;

	struct STakeFeedBackPrizeAck : public CClientFuncAck
	{
		EFeedBackRet eRet; //结果
		UINT32 dwBuyCount; //已购买次数（购买成功后返回次数）

		STakeFeedBackPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取奖励
	virtual bool OnRecv_TakeFeedBackPrize(
		UINT32 dwActID, //活动id
		shared_func<STakeFeedBackPrizeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 144; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetFeedBackList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyDisCountItem(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeFeedBackPrize(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CFeedBackProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NFeedBackProt
