/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    AnswerProt.h
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "AnswerProt.h"

namespace NAnswerProt
{

//协议类：答题协议
class CAnswerProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：答题预告
	bool Send_AnswerAlarm( //发送给当前协议处理的客户端
		UINT32 dwTime //时间
	);
	bool SendClt_AnswerAlarm(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间
	);
	std::string& BuildPkg_AnswerAlarm( //只组包不发送
		UINT32 dwTime //时间
	);

	//发送：答题开始倒计时30秒通知
	bool Send_AnswerCountdown( //发送给当前协议处理的客户端
		UINT32 dwTime //时间
	);
	bool SendClt_AnswerCountdown(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间
	);
	std::string& BuildPkg_AnswerCountdown( //只组包不发送
		UINT32 dwTime //时间
	);

	//发送：答题开始
	bool Send_AnswerBegin( //发送给当前协议处理的客户端
		UINT32 dwTime //时间
	);
	bool SendClt_AnswerBegin(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间
	);
	std::string& BuildPkg_AnswerBegin( //只组包不发送
		UINT32 dwTime //时间
	);

	//发送：答题结束
	bool Send_AnswerEnd( //发送给当前协议处理的客户端
		UINT32 dwTime //时间
	);
	bool SendClt_AnswerEnd(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //时间
	);
	std::string& BuildPkg_AnswerEnd( //只组包不发送
		UINT32 dwTime //时间
	);

	//发送：发送题目
	bool Send_SendTopic( //发送给当前协议处理的客户端
		const SAnswerTopic& sTopic //题目信息
	);
	bool SendClt_SendTopic(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SAnswerTopic& sTopic //题目信息
	);
	std::string& BuildPkg_SendTopic( //只组包不发送
		const SAnswerTopic& sTopic //题目信息
	);

	//发送：答完一题信息发送
	bool Send_SendAnswerInfo( //发送给当前协议处理的客户端
		const SAnswerPlayer& sPlayerInfo, //玩家信息
		const TVecAnswerRank& vecRankInfo //排名列表
	);
	bool SendClt_SendAnswerInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SAnswerPlayer& sPlayerInfo, //玩家信息
		const TVecAnswerRank& vecRankInfo //排名列表
	);
	std::string& BuildPkg_SendAnswerInfo( //只组包不发送
		const SAnswerPlayer& sPlayerInfo, //玩家信息
		const TVecAnswerRank& vecRankInfo //排名列表
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：玩家报名
	virtual void OnRecv_Join(
	) = 0;

	//接收：玩家离开
	virtual void OnRecv_Leave(
	) = 0;

	struct SGetCoutdownAck : public CClientFuncAck
	{
		UINT32 dwTime; //倒计时时间
		SAnswerPlayer sPlayerInfo; //玩家信息
		bool bRet; //是否开启面板

		SGetCoutdownAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取活动开始倒计时
	virtual bool OnRecv_GetCoutdown(
		shared_func<SGetCoutdownAck>& fnAck //返回回调函数
	) = 0;

	struct SAnswerAck : public CClientFuncAck
	{
		UINT32 dwIndex; //题目
		EAnswerResult eResult; //答题结果返回

		SAnswerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家答题
	virtual bool OnRecv_Answer(
		UINT8 byAnswerID, //玩家选择答案
		shared_func<SAnswerAck>& fnAck //返回回调函数
	) = 0;

	struct SUseSkillAck : public CClientFuncAck
	{
		EAnswerSkill eSkillTypeRet; //技能ID
		UINT8 byAnswer1; //答案1
		UINT8 byAnswer2; //答案2
		EAnswerResult eResult; //结果

		SUseSkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家使用技能
	virtual bool OnRecv_UseSkill(
		EAnswerSkill eSkillType, //技能ID
		shared_func<SUseSkillAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 95; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_Join(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Leave(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetCoutdown(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Answer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UseSkill(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CAnswerProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NAnswerProt
