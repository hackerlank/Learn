/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    TaskProt.h
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "TaskProt.h"

namespace NTaskProt
{

//协议类：任务协议
class CTaskProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：任务列表通知
	bool Send_TaskListNtf( //发送给当前协议处理的客户端
		const TVecTask& vecTask //任务列表
	);
	bool SendClt_TaskListNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecTask& vecTask //任务列表
	);
	std::string& BuildPkg_TaskListNtf( //只组包不发送
		const TVecTask& vecTask //任务列表
	);

	//发送：任务更新通知
	bool Send_TaskUpdateNtf( //发送给当前协议处理的客户端
		const STask& rTask //任务
	);
	bool SendClt_TaskUpdateNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const STask& rTask //任务
	);
	std::string& BuildPkg_TaskUpdateNtf( //只组包不发送
		const STask& rTask //任务
	);

	//发送：删除任务
	bool Send_DelTaskAck( //发送给当前协议处理的客户端
		UINT16 wTaskID //任务ID
	);
	bool SendClt_DelTaskAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wTaskID //任务ID
	);
	std::string& BuildPkg_DelTaskAck( //只组包不发送
		UINT16 wTaskID //任务ID
	);

	//发送：添加任务
	bool Send_AddTaskAck( //发送给当前协议处理的客户端
		UINT8 byCost, //立即完成
		const STask& rTask //任务
	);
	bool SendClt_AddTaskAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byCost, //立即完成
		const STask& rTask //任务
	);
	std::string& BuildPkg_AddTaskAck( //只组包不发送
		UINT8 byCost, //立即完成
		const STask& rTask //任务
	);

	//发送：任务记录
	bool Send_NotifyTaskRecordAck( //发送给当前协议处理的客户端
		const TVecUINT16& vecTaskID //任务完成记录
	);
	bool SendClt_NotifyTaskRecordAck(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecUINT16& vecTaskID //任务完成记录
	);
	std::string& BuildPkg_NotifyTaskRecordAck( //只组包不发送
		const TVecUINT16& vecTaskID //任务完成记录
	);

	//发送：通知播放剧情
	bool Send_NotifyStory( //发送给当前协议处理的客户端
		UINT16 wStoryID, //剧情ID
		UINT8 byType, //参数类型
		UINT32 dwParam //参数
	);
	bool SendClt_NotifyStory(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wStoryID, //剧情ID
		UINT8 byType, //参数类型
		UINT32 dwParam //参数
	);
	std::string& BuildPkg_NotifyStory( //只组包不发送
		UINT16 wStoryID, //剧情ID
		UINT8 byType, //参数类型
		UINT32 dwParam //参数
	);

	//发送：通知环任务信息
	bool Send_SendCircleTaskInfo( //发送给当前协议处理的客户端
		UINT8 byStar, //环任务星级
		UINT8 byNum //环任务环数
	);
	bool SendClt_SendCircleTaskInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byStar, //环任务星级
		UINT8 byNum //环任务环数
	);
	std::string& BuildPkg_SendCircleTaskInfo( //只组包不发送
		UINT8 byStar, //环任务星级
		UINT8 byNum //环任务环数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SAcceptTaskReqAck : public CClientFuncAck
	{
		ETaskResult eResult; //接受任务的结果
		UINT8 byCost; //参数回传
		UINT16 wTaskID; //任务ID

		SAcceptTaskReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：接受任务请求
	virtual bool OnRecv_AcceptTaskReq(
		UINT8 byCost, //0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		UINT16 wTaskID, //任务ID
		shared_func<SAcceptTaskReqAck>& fnAck //返回回调函数
	) = 0;

	struct SGiveUpTaskAck : public CClientFuncAck
	{
		ETaskResult eResult; //放弃任务的结果
		UINT16 wTaskID; //任务ID

		SGiveUpTaskAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：放弃任务请求
	virtual bool OnRecv_GiveUpTask(
		UINT16 wTaskID, //任务ID
		shared_func<SGiveUpTaskAck>& fnAck //返回回调函数
	) = 0;

	struct SFinishTaskAck : public CClientFuncAck
	{
		ETaskResult eResult; //完成任务的结果
		UINT8 byCost; //参数回传
		UINT16 wTaskID; //任务ID

		SFinishTaskAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：完成任务请求(领取奖励)
	virtual bool OnRecv_FinishTask(
		UINT8 byCost, //0,正常提交，1，付费提交，限未完成任务,支持师门,衙门任务
		UINT16 wTaskID, //任务ID
		UINT8 byIndex, //可选择的奖励索引
		shared_func<SFinishTaskAck>& fnAck //返回回调函数
	) = 0;

	//接收：完成特殊任务请求
	virtual void OnRecv_FinishSpeTask(
		UINT16 wTaskID //任务ID
	) = 0;

	//接收：获得任务列表
	virtual void OnRecv_GetTaskList(
	) = 0;

	//接收：获得环任务信息
	virtual void OnRecv_GetCircleTaskInfo(
	) = 0;

	struct SFinishCircleTaskOneKeyAck : public CClientFuncAck
	{
		ETaskResult eResult; //完成任务的结果

		SFinishCircleTaskOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：完成所有的环任务
	virtual bool OnRecv_FinishCircleTaskOneKey(
		shared_func<SFinishCircleTaskOneKeyAck>& fnAck //返回回调函数
	) = 0;

	struct SUpdateCircleTaskStarAck : public CClientFuncAck
	{
		ETaskResult eResult; //完成任务的结果

		SUpdateCircleTaskStarAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：提升环任务星级
	virtual bool OnRecv_UpdateCircleTaskStar(
		shared_func<SUpdateCircleTaskStarAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 15; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_AcceptTaskReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GiveUpTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishSpeTask(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTaskList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetCircleTaskInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishCircleTaskOneKey(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateCircleTaskStar(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CTaskProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NTaskProt
