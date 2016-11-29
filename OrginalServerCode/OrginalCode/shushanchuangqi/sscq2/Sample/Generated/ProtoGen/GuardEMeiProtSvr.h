/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GuardEMeiProt.h
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GuardEMeiProt.h"

namespace NGuardEMeiProt
{

//协议类：守卫峨眉协议
class CGuardEMeiProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：扫荡信息通知
	bool Send_SweepInfoNotify( //发送给当前协议处理的客户端
		UINT16 wCurProgress, //当前进度
		const TVecGEMAwardInfo& vecGEMSAwardInfo //守卫峨眉扫荡奖励信息
	);
	bool SendClt_SweepInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wCurProgress, //当前进度
		const TVecGEMAwardInfo& vecGEMSAwardInfo //守卫峨眉扫荡奖励信息
	);
	std::string& BuildPkg_SweepInfoNotify( //只组包不发送
		UINT16 wCurProgress, //当前进度
		const TVecGEMAwardInfo& vecGEMSAwardInfo //守卫峨眉扫荡奖励信息
	);

	//发送：关卡通关成功通知
	bool Send_MissionPassSuccNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_MissionPassSuccNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_MissionPassSuccNotify( //只组包不发送
	);

	//发送：关卡通关失败通知
	bool Send_MissionPassFailedtify( //发送给当前协议处理的客户端
	);
	bool SendClt_MissionPassFailedtify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_MissionPassFailedtify( //只组包不发送
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SReqGEMInfoAck : public CClientFuncAck
	{
		TVecGEMMissionInfo vecGEMMissionInfo; //守卫峨眉关卡信息

		SReqGEMInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求守卫峨眉信息
	virtual bool OnRecv_ReqGEMInfo(
		shared_func<SReqGEMInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyGEMEntryNumAck : public CClientFuncAck
	{
		EGEMOptResult eGEMOptResult; //操作结果

		SBuyGEMEntryNumAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求购买守卫峨眉进入次数
	virtual bool OnRecv_BuyGEMEntryNum(
		shared_func<SBuyGEMEntryNumAck>& fnAck //返回回调函数
	) = 0;

	struct SReqUseBuffAck : public CClientFuncAck
	{
		TVecGEMBattleFighterInfo vecGEMBattleFighterInfo; //守卫峨眉参战散仙信息
		TVecGEMBuffInfo vecGEMBuffInfo; //守卫峨眉Buff信息

		SReqUseBuffAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求使用Buff
	virtual bool OnRecv_ReqUseBuff(
		UINT32 dwBuffID, //BuffID
		shared_func<SReqUseBuffAck>& fnAck //返回回调函数
	) = 0;

	struct SReqResetGEMAck : public CClientFuncAck
	{
		EGEMOptResult eGEMOptResult; //操作结果

		SReqResetGEMAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求重置关卡
	virtual bool OnRecv_ReqResetGEM(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqResetGEMAck>& fnAck //返回回调函数
	) = 0;

	struct SReqGEMPrepareBattleInfoAck : public CClientFuncAck
	{
		SGEMPrepareBattleInfo sGEMPrepareBattleInfo; //守卫峨眉准备战斗信息

		SReqGEMPrepareBattleInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求守卫峨眉准备战斗信息
	virtual bool OnRecv_ReqGEMPrepareBattleInfo(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqGEMPrepareBattleInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReqGEMBattleAck : public CClientFuncAck
	{
		EGEMBattleRet eGEMBattleRet; //战斗结果
		SGEMPrepareBattleInfo sGEMPrepareBattleInfo; //守卫峨眉下一波准备战斗信息

		SReqGEMBattleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求守卫峨眉战斗
	virtual bool OnRecv_ReqGEMBattle(
		UINT16 wMissionID, //关卡ID
		UINT32 dwBuffID, //BuffID
		EGEMBattleType eGEMBattleType, //战斗类型
		shared_func<SReqGEMBattleAck>& fnAck //返回回调函数
	) = 0;

	struct SReqSweepBeginAck : public CClientFuncAck
	{
		EGEMOptResult eGEMOptResult; //操作结果

		SReqSweepBeginAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求获取守卫峨眉扫荡开始
	virtual bool OnRecv_ReqSweepBegin(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqSweepBeginAck>& fnAck //返回回调函数
	) = 0;

	struct SReqSweepEndAck : public CClientFuncAck
	{
		UINT16 wCurProgress; //当前进度

		SReqSweepEndAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求获取守卫峨眉扫荡结束(放弃扫荡)
	virtual bool OnRecv_ReqSweepEnd(
		UINT16 wMissionID, //关卡ID
		shared_func<SReqSweepEndAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 86; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_ReqGEMInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyGEMEntryNum(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqUseBuff(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqResetGEM(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqGEMPrepareBattleInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqGEMBattle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqSweepBegin(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqSweepEnd(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGuardEMeiProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGuardEMeiProt
