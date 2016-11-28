/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GroupTaskProt.h
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GroupTaskProt.h"

namespace NGroupTaskProt
{

//协议类：师门任务协议
class CGroupTaskProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：获取师门任务详情
	bool Send_ReturnAllInfoTask( //发送给当前协议处理的客户端
		const SGroupTaskInfoForClient& stGroupTaskInfo //师门任务详情
	);
	bool SendClt_ReturnAllInfoTask(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SGroupTaskInfoForClient& stGroupTaskInfo //师门任务详情
	);
	std::string& BuildPkg_ReturnAllInfoTask( //只组包不发送
		const SGroupTaskInfoForClient& stGroupTaskInfo //师门任务详情
	);

	//发送：任务列表更新
	bool Send_UpdateGroupTask( //发送给当前协议处理的客户端
		const SGroupTask& stTask //师门任务详情
	);
	bool SendClt_UpdateGroupTask(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SGroupTask& stTask //师门任务详情
	);
	std::string& BuildPkg_UpdateGroupTask( //只组包不发送
		const SGroupTask& stTask //师门任务详情
	);

	//发送：完成任务数更新
	bool Send_UpdateFinishTask( //发送给当前协议处理的客户端
		UINT8 byFinishTask, //今日完成的师门任务数
		UINT8 byAcceptTaskTimes, //剩余可接任务数
		UINT8 byVIPTaskTimes, //购买的可接任务数
		UINT8 byBuyTimesToday //今日购买的任务数
	);
	bool SendClt_UpdateFinishTask(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byFinishTask, //今日完成的师门任务数
		UINT8 byAcceptTaskTimes, //剩余可接任务数
		UINT8 byVIPTaskTimes, //购买的可接任务数
		UINT8 byBuyTimesToday //今日购买的任务数
	);
	std::string& BuildPkg_UpdateFinishTask( //只组包不发送
		UINT8 byFinishTask, //今日完成的师门任务数
		UINT8 byAcceptTaskTimes, //剩余可接任务数
		UINT8 byVIPTaskTimes, //购买的可接任务数
		UINT8 byBuyTimesToday //今日购买的任务数
	);

	//发送：更新清修状态
	bool Send_UpdateStudyState( //发送给当前协议处理的客户端
		EGroupStudyState eStudyState //清修状态
	);
	bool SendClt_UpdateStudyState(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EGroupStudyState eStudyState //清修状态
	);
	std::string& BuildPkg_UpdateStudyState( //只组包不发送
		EGroupStudyState eStudyState //清修状态
	);

	//发送：更新声望等级
	bool Send_UpdateGroupReputeLevel( //发送给当前协议处理的客户端
		UINT8 dwGroupLevel //声望等级
	);
	bool SendClt_UpdateGroupReputeLevel(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 dwGroupLevel //声望等级
	);
	std::string& BuildPkg_UpdateGroupReputeLevel( //只组包不发送
		UINT8 dwGroupLevel //声望等级
	);

	//发送：更新声望
	bool Send_UpdateGroupRepute( //发送给当前协议处理的客户端
		UINT32 dwGroupRepute //声望
	);
	bool SendClt_UpdateGroupRepute(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwGroupRepute //声望
	);
	std::string& BuildPkg_UpdateGroupRepute( //只组包不发送
		UINT32 dwGroupRepute //声望
	);

	//发送：更新今日清修领奖次数
	bool Send_UpdateStudyAward( //发送给当前协议处理的客户端
		UINT8 byStudyAward //今日领取的清修次数
	);
	bool SendClt_UpdateStudyAward(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byStudyAward //今日领取的清修次数
	);
	std::string& BuildPkg_UpdateStudyAward( //只组包不发送
		UINT8 byStudyAward //今日领取的清修次数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGroupTaskOpAck : public CClientFuncAck
	{
		EGroupTaskResult eResult; //操作结果
		EGroupStudyState eState; //当前清修状态

		SGroupTaskOpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求操作
	virtual bool OnRecv_GroupTaskOp(
		shared_func<SGroupTaskOpAck>& fnAck //返回回调函数
	) = 0;

	struct SFlushTaskAck : public CClientFuncAck
	{
		EGroupTaskResult eResult; //操作结果
		TVecGroupTask vecTask; //推的任务列表
		UINT8 byFlushTask; //今日刷新任务列表次数

		SFlushTaskAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：刷新师门任务列表
	virtual bool OnRecv_FlushTask(
		shared_func<SFlushTaskAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取师门任务详情
	virtual void OnRecv_GetAllInfoTask(
	) = 0;

	struct SBuyTaskTimesAck : public CClientFuncAck
	{
		EGroupTaskResult eResult; //操作结果

		SBuyTaskTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买师门任务
	virtual bool OnRecv_BuyTaskTimes(
		shared_func<SBuyTaskTimesAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 51; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GroupTaskOp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FlushTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllInfoTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyTaskTimes(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGroupTaskProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGroupTaskProt
