/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ShushanweiweiProt.h
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ShushanweiweiProt.h"

namespace NShushanweiweiProt
{

//协议类：蜀山微微协议
class CShushanweiweiProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：同步玩家奖励信息
	bool Send_SyncPrizeInfo( //发送给当前协议处理的客户端
		const TVecPrizeInfo& vecResult //奖励结果
	);
	bool SendClt_SyncPrizeInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPrizeInfo& vecResult //奖励结果
	);
	std::string& BuildPkg_SyncPrizeInfo( //只组包不发送
		const TVecPrizeInfo& vecResult //奖励结果
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct STakePrizeAck : public CClientFuncAck
	{
		EPkgType eRetType; //活动类型返回
		UINT16 wRetIndex; //领奖类型返回：0表示个人奖励，1..16 表示领取全服第几个奖励
		EPkgResult eRet; //操作结果返回

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取礼包
	virtual bool OnRecv_TakePrize(
		EPkgType eType, //活动类型
		UINT16 wIndex, //领奖类型：0表示个人奖励，1..16位 表示领取全服第几个奖励
		const std::string& strCDK, //CDK
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	//接收：获得玩家奖励信息
	virtual void OnRecv_GetPrizeInfo(
	) = 0;

	struct SListenWeiboAck : public CClientFuncAck
	{
		EPkgResult eRet; //操作结果返回

		SListenWeiboAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：收听微博
	virtual bool OnRecv_ListenWeibo(
		shared_func<SListenWeiboAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 93; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPrizeInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ListenWeibo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CShushanweiweiProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NShushanweiweiProt
