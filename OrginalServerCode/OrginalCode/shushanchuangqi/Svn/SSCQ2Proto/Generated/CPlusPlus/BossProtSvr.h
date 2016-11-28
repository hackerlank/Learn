/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BossProt.h
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "BossProt.h"

namespace NBossProt
{

//协议类：BOSS相关协议
class CBossProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：世界BOSS信息通知
	bool Send_BossInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwBoosID, //bossID
		UINT32 dwCurHP, //当前血量
		UINT32 dwMaxHP, //最大血量
		UINT32 dwPlayerCnt //当前地图人数
	);
	bool SendClt_BossInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwBoosID, //bossID
		UINT32 dwCurHP, //当前血量
		UINT32 dwMaxHP, //最大血量
		UINT32 dwPlayerCnt //当前地图人数
	);
	std::string& BuildPkg_BossInfoNotify( //只组包不发送
		UINT32 dwBoosID, //bossID
		UINT32 dwCurHP, //当前血量
		UINT32 dwMaxHP, //最大血量
		UINT32 dwPlayerCnt //当前地图人数
	);

	//发送：排行榜通知
	bool Send_TopListNotify( //发送给当前协议处理的客户端
		const TVecPlayerInfo& vecTopList //排行榜列表
	);
	bool SendClt_TopListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPlayerInfo& vecTopList //排行榜列表
	);
	std::string& BuildPkg_TopListNotify( //只组包不发送
		const TVecPlayerInfo& vecTopList //排行榜列表
	);

	//发送：个人信息通知
	bool Send_SelfInfoNotify( //发送给当前协议处理的客户端
		const SPlayerInfo& oSelfInfo, //玩家信息
		UINT32 dwBeginTime, //开始时间
		UINT32 dwEndTime, //结束时间
		UINT32 dwReliveTime, //复活时间
		UINT32 dwSilverBufferCdTime, //银币加持cd
		UINT32 dwSilverBufferCnt, //银币加持次数
		UINT32 dwGoldBufferCnt, //金币加持次数
		UINT32 dwGoldAttackCnt //直接攻击次数
	);
	bool SendClt_SelfInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SPlayerInfo& oSelfInfo, //玩家信息
		UINT32 dwBeginTime, //开始时间
		UINT32 dwEndTime, //结束时间
		UINT32 dwReliveTime, //复活时间
		UINT32 dwSilverBufferCdTime, //银币加持cd
		UINT32 dwSilverBufferCnt, //银币加持次数
		UINT32 dwGoldBufferCnt, //金币加持次数
		UINT32 dwGoldAttackCnt //直接攻击次数
	);
	std::string& BuildPkg_SelfInfoNotify( //只组包不发送
		const SPlayerInfo& oSelfInfo, //玩家信息
		UINT32 dwBeginTime, //开始时间
		UINT32 dwEndTime, //结束时间
		UINT32 dwReliveTime, //复活时间
		UINT32 dwSilverBufferCdTime, //银币加持cd
		UINT32 dwSilverBufferCnt, //银币加持次数
		UINT32 dwGoldBufferCnt, //金币加持次数
		UINT32 dwGoldAttackCnt //直接攻击次数
	);

	//发送：伤害boss信息
	bool Send_AtkInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwDamage, //本次伤害
		UINT32 dwExp, //本次活动经验值
		UINT32 dwTotalDamage, //总伤害
		UINT32 dwBossMaxHp //boss最大血量
	);
	bool SendClt_AtkInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwDamage, //本次伤害
		UINT32 dwExp, //本次活动经验值
		UINT32 dwTotalDamage, //总伤害
		UINT32 dwBossMaxHp //boss最大血量
	);
	std::string& BuildPkg_AtkInfoNotify( //只组包不发送
		UINT32 dwDamage, //本次伤害
		UINT32 dwExp, //本次活动经验值
		UINT32 dwTotalDamage, //总伤害
		UINT32 dwBossMaxHp //boss最大血量
	);

	//发送：玩家名次变化通知
	bool Send_NoChangeNotify( //发送给当前协议处理的客户端
		UINT32 dwNo //玩家名次
	);
	bool SendClt_NoChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwNo //玩家名次
	);
	std::string& BuildPkg_NoChangeNotify( //只组包不发送
		UINT32 dwNo //玩家名次
	);

	//发送：玩家奖励获取通知
	bool Send_PrizeNotify( //发送给当前协议处理的客户端
		const TVecPlayerPrize& vecPlayerPrize //玩家奖励列表
	);
	bool SendClt_PrizeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPlayerPrize& vecPlayerPrize //玩家奖励列表
	);
	std::string& BuildPkg_PrizeNotify( //只组包不发送
		const TVecPlayerPrize& vecPlayerPrize //玩家奖励列表
	);

	//发送：玩家复活时间通知
	bool Send_ReliveTimeNotify( //发送给当前协议处理的客户端
		UINT32 dwReliveTime //复活时间
	);
	bool SendClt_ReliveTimeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwReliveTime //复活时间
	);
	std::string& BuildPkg_ReliveTimeNotify( //只组包不发送
		UINT32 dwReliveTime //复活时间
	);

	//发送：活动结束通知
	bool Send_EndNotify( //发送给当前协议处理的客户端
		UINT32 dwLeaveTime //离开时间
	);
	bool SendClt_EndNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwLeaveTime //离开时间
	);
	std::string& BuildPkg_EndNotify( //只组包不发送
		UINT32 dwLeaveTime //离开时间
	);

	//发送：玩家直接攻击次数
	bool Send_AttackCountNotify( //发送给当前协议处理的客户端
		UINT16 dwAttackCount //玩家直接攻击次数
	);
	bool SendClt_AttackCountNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 dwAttackCount //玩家直接攻击次数
	);
	std::string& BuildPkg_AttackCountNotify( //只组包不发送
		UINT16 dwAttackCount //玩家直接攻击次数
	);

	//发送：结算通知
	bool Send_GainPrizeNotify( //发送给当前协议处理的客户端
		UINT32 dwNo, //玩家名次
		UINT32 dwExp, //总共获得经验
		bool bKillBoss //是否击杀boss
	);
	bool SendClt_GainPrizeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwNo, //玩家名次
		UINT32 dwExp, //总共获得经验
		bool bKillBoss //是否击杀boss
	);
	std::string& BuildPkg_GainPrizeNotify( //只组包不发送
		UINT32 dwNo, //玩家名次
		UINT32 dwExp, //总共获得经验
		bool bKillBoss //是否击杀boss
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SWBAliveAck : public CClientFuncAck
	{
		bool bRet; //结果

		SWBAliveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：世界BOSS中复活
	virtual bool OnRecv_WBAlive(
		shared_func<SWBAliveAck>& fnAck //返回回调函数
	) = 0;

	struct SWBStrengthAck : public CClientFuncAck
	{
		UINT32 dwSilverBufferCnt; //银币加持次数
		UINT32 dwGoldBufferCnt; //金币加持次数
		UINT32 dwSilverBufferCdTime; //银币加持cd
		bool bRet; //结果

		SWBStrengthAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加持
	virtual bool OnRecv_WBStrength(
		EBossBuyType eBuyType, //购买类型
		shared_func<SWBStrengthAck>& fnAck //返回回调函数
	) = 0;

	struct SWBAttackAck : public CClientFuncAck
	{
		bool bRet; //结果

		SWBAttackAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：直接攻击boss
	virtual bool OnRecv_WBAttack(
		shared_func<SWBAttackAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取排行榜信息
	virtual void OnRecv_GetTopList(
	) = 0;

	//接收：获取玩家自己的排行榜信息
	virtual void OnRecv_GetSelfInfo(
	) = 0;

	//接收：获取boss信息
	virtual void OnRecv_GetBossInfo(
	) = 0;

	struct SEnterMapAck : public CClientFuncAck
	{
		bool bRet; //结果

		SEnterMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入boss地图
	virtual bool OnRecv_EnterMap(
		shared_func<SEnterMapAck>& fnAck //返回回调函数
	) = 0;

	struct SLeaveMapAck : public CClientFuncAck
	{
		bool bRet; //结果

		SLeaveMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：离开boss地图
	virtual bool OnRecv_LeaveMap(
		shared_func<SLeaveMapAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 25; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_WBAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WBStrength(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WBAttack(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTopList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSelfInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBossInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EnterMap(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveMap(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CBossProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NBossProt
