/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LangHuanBlessProt.h
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LangHuanBlessProt.h"

namespace NLangHuanBlessProt
{

//协议类：中午挂机活动
class CLangHuanBlessProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：挂机活动报名开始
	bool Send_EnrollNotify( //发送给当前协议处理的客户端
		UINT32 dwEnrollTime //开始时间
	);
	bool SendClt_EnrollNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwEnrollTime //开始时间
	);
	std::string& BuildPkg_EnrollNotify( //只组包不发送
		UINT32 dwEnrollTime //开始时间
	);

	//发送：挂机活动开始
	bool Send_BeginNotify( //发送给当前协议处理的客户端
		UINT32 dwBeginTime //开始时间
	);
	bool SendClt_BeginNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwBeginTime //开始时间
	);
	std::string& BuildPkg_BeginNotify( //只组包不发送
		UINT32 dwBeginTime //开始时间
	);

	//发送：发送经验值和修为值
	bool Send_PrizeNotify( //发送给当前协议处理的客户端
		UINT32 dwXiuwei, //修为值
		UINT32 dwExp //经验值
	);
	bool SendClt_PrizeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwXiuwei, //修为值
		UINT32 dwExp //经验值
	);
	std::string& BuildPkg_PrizeNotify( //只组包不发送
		UINT32 dwXiuwei, //修为值
		UINT32 dwExp //经验值
	);

	//发送：发送玩家在副本中的信息
	bool Send_TotalInfo( //发送给当前协议处理的客户端
		UINT64 qwPlayerID, //玩家ID
		const SLHBTotalInfo& sTotalInfo //玩家信息
	);
	bool SendClt_TotalInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwPlayerID, //玩家ID
		const SLHBTotalInfo& sTotalInfo //玩家信息
	);
	std::string& BuildPkg_TotalInfo( //只组包不发送
		UINT64 qwPlayerID, //玩家ID
		const SLHBTotalInfo& sTotalInfo //玩家信息
	);

	//发送：发送技能信息
	bool Send_SkillInfo( //发送给当前协议处理的客户端
		UINT64 qwAtkPlayerID, //攻击者
		UINT64 qwDfePlayerID, //被攻击者
		ELHBSkillType eLHBSkillType //使用的技能ID
	);
	bool SendClt_SkillInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwAtkPlayerID, //攻击者
		UINT64 qwDfePlayerID, //被攻击者
		ELHBSkillType eLHBSkillType //使用的技能ID
	);
	std::string& BuildPkg_SkillInfo( //只组包不发送
		UINT64 qwAtkPlayerID, //攻击者
		UINT64 qwDfePlayerID, //被攻击者
		ELHBSkillType eLHBSkillType //使用的技能ID
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SEnterMapAck : public CClientFuncAck
	{
		ELHBResult eLHBResult; //结果

		SEnterMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入LangHuanBless地图
	virtual bool OnRecv_EnterMap(
		shared_func<SEnterMapAck>& fnAck //返回回调函数
	) = 0;

	struct SSelectSkillAck : public CClientFuncAck
	{
		ELHBSkillType eRetLHBSkillType; //返回使用技能
		ELHBResult eLHBResult; //结果

		SSelectSkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：选择问道
	virtual bool OnRecv_SelectSkill(
		UINT64 qwPlayerID, //被选择的玩家
		ELHBSkillType eLHBSkillType, //技能类型
		shared_func<SSelectSkillAck>& fnAck //返回回调函数
	) = 0;

	struct SGetScoreAck : public CClientFuncAck
	{
		UINT32 wScore; //修为值

		SGetScoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得的修为值
	virtual bool OnRecv_GetScore(
		shared_func<SGetScoreAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSustainTimeAck : public CClientFuncAck
	{
		UINT32 dwTime; //时间值

		SGetSustainTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得游戏中持续时间
	virtual bool OnRecv_GetSustainTime(
		shared_func<SGetSustainTimeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTotalInfoAck : public CClientFuncAck
	{
		SLHBTotalInfo sTotalInfo; //时间值
		bool bRet; //结果

		SGetTotalInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得玩家所有信息
	virtual bool OnRecv_GetTotalInfo(
		shared_func<SGetTotalInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSkillInfoAck : public CClientFuncAck
	{
		TVecLHBSkillInfo vecLHBSkillInfo; //技能使用信息
		ELHBResult eLHBResult; //结果

		SGetSkillInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得技能使用信息
	virtual bool OnRecv_GetSkillInfo(
		shared_func<SGetSkillInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SLeaveMapAck : public CClientFuncAck
	{
		ELHBResult eLHBResult; //结果

		SLeaveMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：离开LangHuanBless地图
	virtual bool OnRecv_LeaveMap(
		shared_func<SLeaveMapAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 79; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_EnterMap(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SelectSkill(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetScore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSustainTime(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTotalInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSkillInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveMap(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLangHuanBlessProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLangHuanBlessProt
