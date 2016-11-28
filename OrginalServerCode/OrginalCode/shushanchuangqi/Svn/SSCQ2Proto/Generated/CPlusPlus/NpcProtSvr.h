/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    NpcProt.h
//  Purpose:      NPC相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "NpcProt.h"

namespace NNpcProt
{

//协议类：NPC相关协议
class CNpcProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：NPC对话通知
	bool Send_NpcTalkNtf( //发送给当前协议处理的客户端
		UINT64 qwCreatureID, //NPC的生物ID
		ETalkResult eResult, //对话结果
		const std::string& strContent //对话内容
	);
	bool SendClt_NpcTalkNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwCreatureID, //NPC的生物ID
		ETalkResult eResult, //对话结果
		const std::string& strContent //对话内容
	);
	std::string& BuildPkg_NpcTalkNtf( //只组包不发送
		UINT64 qwCreatureID, //NPC的生物ID
		ETalkResult eResult, //对话结果
		const std::string& strContent //对话内容
	);

	//发送：NPC任务状态通知
	bool Send_NpcTaskStateNtf( //发送给当前协议处理的客户端
		const TVecNpcTask& rVecNpcTask //NPC任务状态列表
	);
	bool SendClt_NpcTaskStateNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecNpcTask& rVecNpcTask //NPC任务状态列表
	);
	std::string& BuildPkg_NpcTaskStateNtf( //只组包不发送
		const TVecNpcTask& rVecNpcTask //NPC任务状态列表
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：打开NPC对话界面请求
	virtual void OnRecv_NpcTalkReq(
		UINT64 qwCreatureID //当前NPC的生物ID
	) = 0;

	//接收：执行NPC对话脚本函数
	virtual void OnRecv_ExecScriptFunc(
		UINT64 qwCreatureID, //当前NPC的生物ID
		const std::string& strFuncName //脚本函数名称
	) = 0;

	//接收：地图的NPC任务状态请求
	virtual void OnRecv_NpcTaskStateReq(
		UINT16 wMapID //地图ID
	) = 0;

	struct SFinishTaskTalkAck : public CClientFuncAck
	{
		std::string strContent; //对话内容

		SFinishTaskTalkAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：完成一任务对话
	virtual bool OnRecv_FinishTaskTalk(
		UINT64 qwCreatureID, //当前NPC的生物ID
		UINT16 wTaskID, //对话的任务
		shared_func<SFinishTaskTalkAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 14; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_NpcTalkReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ExecScriptFunc(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NpcTaskStateReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishTaskTalk(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CNpcProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NNpcProt
