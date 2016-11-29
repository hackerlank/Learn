/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DayTarget.h
//  Purpose:      七日目标活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DayTarget.h"

namespace NDayTarget
{

//协议类：七日目标活动
class CDayTargetSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：任务信息更新
	bool Send_UpdateTaskList( //发送给当前协议处理的客户端
		const SDayTargetTask& oDayTargetTask //任务信息
	);
	bool SendClt_UpdateTaskList(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SDayTargetTask& oDayTargetTask //任务信息
	);
	std::string& BuildPkg_UpdateTaskList( //只组包不发送
		const SDayTargetTask& oDayTargetTask //任务信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetTaskListAck : public CClientFuncAck
	{
		TVecDayTargetTask vecDayTargetTask; //任务列表

		SGetTaskListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取任务列表
	virtual bool OnRecv_GetTaskList(
		shared_func<SGetTaskListAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		EDayTargetRet eRet; //领奖结果

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取奖励
	virtual bool OnRecv_TakePrize(
		UINT16 wTaskID, //任务ID
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 125; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetTaskList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDayTargetSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDayTarget
