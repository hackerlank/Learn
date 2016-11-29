/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Activity.h
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ActivityProt.h"

namespace NActivityProt
{

//协议类：活力任务协议
class CActivityProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：获取活力任务详情
	bool Send_ReturnAllInfoActivity( //发送给当前协议处理的客户端
		const SActivityInfoForClient& stActivityInfo //活力任务详情
	);
	bool SendClt_ReturnAllInfoActivity(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SActivityInfoForClient& stActivityInfo //活力任务详情
	);
	std::string& BuildPkg_ReturnAllInfoActivity( //只组包不发送
		const SActivityInfoForClient& stActivityInfo //活力任务详情
	);

	//发送：活力监测点更新
	bool Send_UpdateActivityTask( //发送给当前协议处理的客户端
		const NRoleInfoDefine::SActivityTaskInfo& stActivityTask, //活力监测点更新
		UINT32 dwTotolActivity, //活力总值
		UINT16 wActivity //今日活力值
	);
	bool SendClt_UpdateActivityTask(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NRoleInfoDefine::SActivityTaskInfo& stActivityTask, //活力监测点更新
		UINT32 dwTotolActivity, //活力总值
		UINT16 wActivity //今日活力值
	);
	std::string& BuildPkg_UpdateActivityTask( //只组包不发送
		const NRoleInfoDefine::SActivityTaskInfo& stActivityTask, //活力监测点更新
		UINT32 dwTotolActivity, //活力总值
		UINT16 wActivity //今日活力值
	);

	//发送：活力总值更新
	bool Send_UpdateActivityTotal( //发送给当前协议处理的客户端
		UINT32 dwTotolActivity //活力总值
	);
	bool SendClt_UpdateActivityTotal(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTotolActivity //活力总值
	);
	std::string& BuildPkg_UpdateActivityTotal( //只组包不发送
		UINT32 dwTotolActivity //活力总值
	);

	//发送：成就分享通知
	bool Send_ShareNotify( //发送给当前协议处理的客户端
		const SActivityShare& oActivityShare //成就分享信息
	);
	bool SendClt_ShareNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SActivityShare& oActivityShare //成就分享信息
	);
	std::string& BuildPkg_ShareNotify( //只组包不发送
		const SActivityShare& oActivityShare //成就分享信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetActivityPoolAck : public CClientFuncAck
	{
		EActivityResult eResult; //操作结果
		UINT32 dwTotolActivity; //活力总值

		SGetActivityPoolAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求获得奖池
	virtual bool OnRecv_GetActivityPool(
		shared_func<SGetActivityPoolAck>& fnAck //返回回调函数
	) = 0;

	struct SGetActivityAwardAck : public CClientFuncAck
	{
		EActivityResult eResult; //操作结果
		SActivityAward stActivityPost; //奖励Id

		SGetActivityAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求活力奖励
	virtual bool OnRecv_GetActivityAward(
		const SActivityAward& stActivityGet, //奖励Id
		shared_func<SGetActivityAwardAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取活力任务详情
	virtual void OnRecv_GetAllInfoActivity(
	) = 0;

	struct SGeShareListAck : public CClientFuncAck
	{
		TVecActivityShare vecActivityShare; //成就分享信息

		SGeShareListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取成就分享信息
	virtual bool OnRecv_GeShareList(
		shared_func<SGeShareListAck>& fnAck //返回回调函数
	) = 0;

	struct STakeSharePrizeAck : public CClientFuncAck
	{
		EActivityResult eRet; //结果

		STakeSharePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取成就分享奖励
	virtual bool OnRecv_TakeSharePrize(
		UINT32 dwActivityID, //活跃度ID
		shared_func<STakeSharePrizeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 53; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetActivityPool(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetActivityAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllInfoActivity(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GeShareList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeSharePrize(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CActivityProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NActivityProt
