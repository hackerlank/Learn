/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    TreasureHuntProt.h
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "TreasureHuntProt.h"

namespace NTreasureHuntProt
{

//协议类：寻宝协议
class CTreasureHuntProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：寻宝开始/结束通知
	bool Send_THNotify( //发送给当前协议处理的客户端
		ETHNotify eTHNotify, //开始/结束
		UINT8 byKillNum, //今日已击杀BOSS次数
		const TVecTHBuffInfo& vecTHBuffInfo //Buff信息
	);
	bool SendClt_THNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ETHNotify eTHNotify, //开始/结束
		UINT8 byKillNum, //今日已击杀BOSS次数
		const TVecTHBuffInfo& vecTHBuffInfo //Buff信息
	);
	std::string& BuildPkg_THNotify( //只组包不发送
		ETHNotify eTHNotify, //开始/结束
		UINT8 byKillNum, //今日已击杀BOSS次数
		const TVecTHBuffInfo& vecTHBuffInfo //Buff信息
	);

	//发送：战斗结果通知
	bool Send_THBattleResultNotify( //发送给当前协议处理的客户端
		const STHBattleResult& sBattleResult //战斗结果
	);
	bool SendClt_THBattleResultNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const STHBattleResult& sBattleResult //战斗结果
	);
	std::string& BuildPkg_THBattleResultNotify( //只组包不发送
		const STHBattleResult& sBattleResult //战斗结果
	);

	//发送：寻宝掉落通知
	bool Send_THLootNotify( //发送给当前协议处理的客户端
		const TVecTHAwardInfo& vecTHAwardInfo //掉落
	);
	bool SendClt_THLootNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecTHAwardInfo& vecTHAwardInfo //掉落
	);
	std::string& BuildPkg_THLootNotify( //只组包不发送
		const TVecTHAwardInfo& vecTHAwardInfo //掉落
	);

	//发送：日志通知
	bool Send_THLogNotify( //发送给当前协议处理的客户端
		ETHLogType eTHLogType, //寻宝日志类型
		UINT32 dwParamA, //参数A
		UINT32 dwParamB, //参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
		UINT64 dwParamC //参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
	);
	bool SendClt_THLogNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ETHLogType eTHLogType, //寻宝日志类型
		UINT32 dwParamA, //参数A
		UINT32 dwParamB, //参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
		UINT64 dwParamC //参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
	);
	std::string& BuildPkg_THLogNotify( //只组包不发送
		ETHLogType eTHLogType, //寻宝日志类型
		UINT32 dwParamA, //参数A
		UINT32 dwParamB, //参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
		UINT64 dwParamC //参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SReqTHInfoAck : public CClientFuncAck
	{
		UINT8 byCopyID; //0:没有副本进行中；非0:正在进行该副本
		ETHStatus eTHStatus; //寻宝状态
		UINT8 byKillNum; //剩余击杀次数
		UINT8 byCurrentID; //当前通关到副本ID

		SReqTHInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求寻宝信息
	virtual bool OnRecv_ReqTHInfo(
		shared_func<SReqTHInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReqTHBattlePrepareInfoAck : public CClientFuncAck
	{
		UINT8 byKillNum; //剩余击杀次数
		UINT32 dwCurBossHP; //当前BOSS血量
		UINT32 dwTotalTimes; //寻宝时间
		TVecTHAwardInfo vecTHAwardInfo; //寻宝奖励信息
		TVecTHBuffInfo vecTHBuffInfo; //Buff信息

		SReqTHBattlePrepareInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求寻宝准备战斗信息(注：离线寻宝，重新登录游戏时请求此消息)
	virtual bool OnRecv_ReqTHBattlePrepareInfo(
		shared_func<SReqTHBattlePrepareInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReqTHStartAck : public CClientFuncAck
	{
		ETHOptResult eTHOptResult; //操作结果

		SReqTHStartAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求寻宝开始
	virtual bool OnRecv_ReqTHStart(
		UINT8 byCopyID, //副本ID
		shared_func<SReqTHStartAck>& fnAck //返回回调函数
	) = 0;

	struct SReqTHQuickFinishAck : public CClientFuncAck
	{
		ETHOptResult eTHOptResult; //操作结果

		SReqTHQuickFinishAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求寻宝立即完成
	virtual bool OnRecv_ReqTHQuickFinish(
		shared_func<SReqTHQuickFinishAck>& fnAck //返回回调函数
	) = 0;

	struct SReqTHGiveUpAck : public CClientFuncAck
	{
		ETHOptResult eTHOptResult; //操作结果

		SReqTHGiveUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求放弃寻宝
	virtual bool OnRecv_ReqTHGiveUp(
		shared_func<SReqTHGiveUpAck>& fnAck //返回回调函数
	) = 0;

	struct SReqUseBuffAck : public CClientFuncAck
	{
		ETHOptResult eTHOptResult; //操作结果

		SReqUseBuffAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求使用Buff
	virtual bool OnRecv_ReqUseBuff(
		UINT8 byBuffID, //BuffID
		shared_func<SReqUseBuffAck>& fnAck //返回回调函数
	) = 0;

	struct SReqTHAwardInfoAck : public CClientFuncAck
	{
		UINT8 byCopyID; //副本ID
		TVecTHAwardInfo vecTHAwardInfo; //寻宝奖励信息

		SReqTHAwardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求寻宝奖励信息
	virtual bool OnRecv_ReqTHAwardInfo(
		shared_func<SReqTHAwardInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTHAwardAck : public CClientFuncAck
	{
		ETHOptResult eTHOptResult; //操作结果

		SGetTHAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取寻宝奖励
	virtual bool OnRecv_GetTHAward(
		shared_func<SGetTHAwardAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 85; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_ReqTHInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqTHBattlePrepareInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqTHStart(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqTHQuickFinish(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqTHGiveUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqUseBuff(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReqTHAwardInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTHAward(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CTreasureHuntProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NTreasureHuntProt
