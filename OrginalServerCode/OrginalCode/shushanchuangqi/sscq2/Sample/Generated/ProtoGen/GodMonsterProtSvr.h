/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GodMonsterProt.h
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GodMonsterProt.h"

namespace NGodMonsterProt
{

//协议类：天元神兽协议
class CGodMonsterProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：同步数据
	bool Send_SyncClientInfo( //发送给当前协议处理的客户端
		const SyncInfoToClient& sInfo //客户端数据
	);
	bool SendClt_SyncClientInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SyncInfoToClient& sInfo //客户端数据
	);
	std::string& BuildPkg_SyncClientInfo( //只组包不发送
		const SyncInfoToClient& sInfo //客户端数据
	);

	//发送：活动开始
	bool Send_OnBegin( //发送给当前协议处理的客户端
		UINT32 dwTime //时间
	);
	bool SendClt_OnBegin(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间
	);
	std::string& BuildPkg_OnBegin( //只组包不发送
		UINT32 dwTime //时间
	);

	//发送：活动结束
	bool Send_OnEnd( //发送给当前协议处理的客户端
		UINT32 dwTime //时间
	);
	bool SendClt_OnEnd(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间
	);
	std::string& BuildPkg_OnEnd( //只组包不发送
		UINT32 dwTime //时间
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SOnEnterAck : public CClientFuncAck
	{
		SyncInfoToClient sInfo; //客户端数据

		SOnEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：打开活动面板
	virtual bool OnRecv_OnEnter(
		shared_func<SOnEnterAck>& fnAck //返回回调函数
	) = 0;

	struct SOnFeedAck : public CClientFuncAck
	{
		EMonsterResult eResult; //操作结果

		SOnFeedAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：喂养
	virtual bool OnRecv_OnFeed(
		UINT8 byType, //0: 表示喂养一次，1: 表示一键喂养
		shared_func<SOnFeedAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		EMonsterResult eResult; //操作结果

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领奖
	virtual bool OnRecv_TakePrize(
		EMonsterPrizeType ePrizeType, //奖励类型
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyPkgAck : public CClientFuncAck
	{
		EMonsterResult eResult; //操作结果

		SBuyPkgAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买限购礼包
	virtual bool OnRecv_BuyPkg(
		UINT16 wIndex, //礼包ID
		UINT8 byCount, //礼包数量
		shared_func<SBuyPkgAck>& fnAck //返回回调函数
	) = 0;

	//接收：表扬
	virtual void OnRecv_OnPraise(
		UINT64 qwRoleID //玩家
	) = 0;

	//接收：督促
	virtual void OnRecv_OnUrge(
		UINT64 qwRoleID //玩家
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 96; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_OnEnter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnFeed(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyPkg(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnPraise(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnUrge(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGodMonsterProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGodMonsterProt
