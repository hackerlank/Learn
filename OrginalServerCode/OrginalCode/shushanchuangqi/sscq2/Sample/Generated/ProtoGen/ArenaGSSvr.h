/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ArenaGS.h
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ArenaGS.h"

namespace NArenaGS
{

//协议类：竞技场协议
class CArenaGSSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：通告获得最好天梯排名
	bool Send_UpdateLadderMinRank( //发送给当前协议处理的客户端
		UINT32 dwLastRank, //前排名,0表示无排名
		UINT32 dwNowRank //现排名
	);
	bool SendClt_UpdateLadderMinRank(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwLastRank, //前排名,0表示无排名
		UINT32 dwNowRank //现排名
	);
	std::string& BuildPkg_UpdateLadderMinRank( //只组包不发送
		UINT32 dwLastRank, //前排名,0表示无排名
		UINT32 dwNowRank //现排名
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SArenaInfoReqAck : public CClientFuncAck
	{
		EArenaResult eResult; //结果提示
		SArenaPlayerBaseData2Client stReturn; //返回的自己信息

		SArenaInfoReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求自己竞技场信息,同时开启竞技场
	virtual bool OnRecv_ArenaInfoReq(
		shared_func<SArenaInfoReqAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaChallengeReqAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求挑战返回
		UINT64 qwBattleID; //战报ID
		UINT8 bySuc; //0,表示挑战失败，1表示挑战成功
		UINT32 dwScore; //当前积分
		UINT32 dwRanking; //当前排名
		UINT16 wChallenge; //今日挑战次数
		UINT16 wChallengeBuyTimes; //购买的挑战次数
		UINT32 dwCDTimer; //冷却时间戳

		SArenaChallengeReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求挑战
	virtual bool OnRecv_ArenaChallengeReq(
		UINT64 qwDefense, //被挑战者ID
		shared_func<SArenaChallengeReqAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaByChallengeTimesAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求挑战返回
		UINT16 wChallenge; //今日挑战次数
		UINT16 wChallengeBuyTimes; //购买的挑战次数

		SArenaByChallengeTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求购买挑战次数
	virtual bool OnRecv_ArenaByChallengeTimes(
		shared_func<SArenaByChallengeTimesAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaPageUpReqAck : public CClientFuncAck
	{
		EArenaResult eResult; //查询结果
		UINT32 dwSize; //本段位的人数总计
		TVecArenaRank2Client vecRankData; //排行榜数据

		SArenaPageUpReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求翻页
	virtual bool OnRecv_ArenaPageUpReq(
		EArenaLevel eLevel, //段位
		UINT32 dwRank, //请求排名开始名次
		UINT8 byNum, //请求数量
		shared_func<SArenaPageUpReqAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaClearCDReqAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求清除冷却返回

		SArenaClearCDReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求清除冷却
	virtual bool OnRecv_ArenaClearCDReq(
		UINT8 byType, //0,历练，1天梯
		shared_func<SArenaClearCDReqAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaGetRankingRewardReqAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求获取奖池奖励返回

		SArenaGetRankingRewardReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求获取奖池奖励
	virtual bool OnRecv_ArenaGetRankingRewardReq(
		UINT32 dwLootId, //奖励包
		EArenaAwardType eType, //奖励包类型
		shared_func<SArenaGetRankingRewardReqAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaWorshipAck : public CClientFuncAck
	{
		EArenaResult eResult; //膜拜请求返回

		SArenaWorshipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：膜拜请求
	virtual bool OnRecv_ArenaWorship(
		UINT64 qwRoleID, //膜拜对象
		shared_func<SArenaWorshipAck>& fnAck //返回回调函数
	) = 0;

	struct SFlushNewEnemyAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		UINT16 wSelfReflush; //当前购买刷新次数
		UINT16 wSelfFreeReflush; //当前VIP免费刷新次数

		SFlushNewEnemyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求刷将
	virtual bool OnRecv_FlushNewEnemy(
		shared_func<SFlushNewEnemyAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllEnemyAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		TVecSFlushFitherForClient vecFlushFigter; //最近刷的对手

		SGetAllEnemyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求对手信息
	virtual bool OnRecv_GetAllEnemy(
		shared_func<SGetAllEnemyAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllAwardAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		TVecArenaAward vecAwards; //奖励包状态

		SGetAllAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求奖励信息
	virtual bool OnRecv_GetAllAward(
		shared_func<SGetAllAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllWirshipAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		TVecArenaRank2Client vecWirshipFigter; //膜拜对象列表

		SGetAllWirshipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求膜拜信息
	virtual bool OnRecv_GetAllWirship(
		shared_func<SGetAllWirshipAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllAwardInfoAck : public CClientFuncAck
	{
		EArenaResult eResult; //返回
		TVecArenaAward vecAwards; //奖励包状态

		SGetAllAwardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求计算:奖励信息
	virtual bool OnRecv_GetAllAwardInfo(
		shared_func<SGetAllAwardInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SReFluseLadderEnemyAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		TVecSFlushFitherForClient vecFlushFigter; //最近刷的对手

		SReFluseLadderEnemyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求对手信息
	virtual bool OnRecv_ReFluseLadderEnemy(
		UINT8 byType, //0,默认刷对手，1顺次刷对手
		shared_func<SReFluseLadderEnemyAck>& fnAck //返回回调函数
	) = 0;

	struct SGetLadderAwardAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回

		SGetLadderAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：清求领取今日天梯奖励
	virtual bool OnRecv_GetLadderAward(
		shared_func<SGetLadderAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetArenaAwardAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回

		SGetArenaAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：清求领取今日历练奖励
	virtual bool OnRecv_GetArenaAward(
		shared_func<SGetArenaAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetLadderReportAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		TVecLadderReport vecReport; //请求刷将返回

		SGetLadderReportAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：清求战报
	virtual bool OnRecv_GetLadderReport(
		shared_func<SGetLadderReportAck>& fnAck //返回回调函数
	) = 0;

	struct SLadderBattleAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求刷将返回
		UINT8 bySuc; //0,失败，1成功
		TVecSFlushFitherForClient vecFlushFigter; //最近刷的对手
		UINT32 dwSelfRank; //自己排名
		UINT16 dwLadderTimes; //今日挑战天梯次数
		UINT32 dwLadderCDTimer; //冷却时间戳
		UINT32 dwMinLadderRank; //天梯最好排名,0表示无排名
		UINT32 dwLadderBuyTimes; //购买的天梯挑战次数

		SLadderBattleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求天梯挑战
	virtual bool OnRecv_LadderBattle(
		UINT64 qwEnemyID, //对手ID
		UINT32 dwEnemyRank, //对手天梯排名
		shared_func<SLadderBattleAck>& fnAck //返回回调函数
	) = 0;

	struct SLadderPageUpReqAck : public CClientFuncAck
	{
		EArenaResult eResult; //查询结果
		TVecArenaRank2Client vecRankData; //排行榜数据

		SLadderPageUpReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求天梯排名
	virtual bool OnRecv_LadderPageUpReq(
		UINT32 dwRank, //请求排名开始名次
		UINT8 byNum, //请求数量
		shared_func<SLadderPageUpReqAck>& fnAck //返回回调函数
	) = 0;

	struct SArenaBuyLadderTimesAck : public CClientFuncAck
	{
		EArenaResult eResult; //请求购买返回
		UINT32 dwLadderBuyTimesToday; //今日购买天梯挑战次数
		UINT32 dwLadderBuyTimes; //购买的天梯挑战次数

		SArenaBuyLadderTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求购买天梯挑战次数
	virtual bool OnRecv_ArenaBuyLadderTimes(
		shared_func<SArenaBuyLadderTimesAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 26; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_ArenaInfoReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaChallengeReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaByChallengeTimes(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaPageUpReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaClearCDReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaGetRankingRewardReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaWorship(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FlushNewEnemy(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllEnemy(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllWirship(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllAwardInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReFluseLadderEnemy(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLadderAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetArenaAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLadderReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LadderBattle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LadderPageUpReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ArenaBuyLadderTimes(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CArenaGSSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NArenaGS
