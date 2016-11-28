/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DemonTowerGS.h
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DemonTowerGS.h"

namespace NDemonTowerGS
{

//协议类：锁妖塔
class CDemonTowerGSSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：锁妖塔镇守信息
	bool Send_GuardInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID, //层数
		const TVecGuardInfo& vecGuardInfo //镇守玩家信息
	);
	bool SendClt_GuardInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID, //层数
		const TVecGuardInfo& vecGuardInfo //镇守玩家信息
	);
	std::string& BuildPkg_GuardInfoNotify( //只组包不发送
		UINT32 dwFloorID, //层数
		const TVecGuardInfo& vecGuardInfo //镇守玩家信息
	);

	//发送：锁妖塔镇守信息更新
	bool Send_GuardInfoChangeNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID, //层数
		UINT32 dwPos, //镇守玩家信息
		UINT64 qwUserID, //玩家ID 0 表示该位置放弃镇守
		const GuardInfo& oGuardInfo //镇守信息
	);
	bool SendClt_GuardInfoChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID, //层数
		UINT32 dwPos, //镇守玩家信息
		UINT64 qwUserID, //玩家ID 0 表示该位置放弃镇守
		const GuardInfo& oGuardInfo //镇守信息
	);
	std::string& BuildPkg_GuardInfoChangeNotify( //只组包不发送
		UINT32 dwFloorID, //层数
		UINT32 dwPos, //镇守玩家信息
		UINT64 qwUserID, //玩家ID 0 表示该位置放弃镇守
		const GuardInfo& oGuardInfo //镇守信息
	);

	//发送：锁妖塔过关通知
	bool Send_PassDemonTowerNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID //锁妖塔过关层数
	);
	bool SendClt_PassDemonTowerNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID //锁妖塔过关层数
	);
	std::string& BuildPkg_PassDemonTowerNotify( //只组包不发送
		UINT32 dwFloorID //锁妖塔过关层数
	);

	//发送：锁妖塔镇守攻击cd
	bool Send_DemonTowerAtkCDNotify( //发送给当前协议处理的客户端
		UINT32 dwGuardNextAttackTime //锁妖塔可攻击最早时间
	);
	bool SendClt_DemonTowerAtkCDNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwGuardNextAttackTime //锁妖塔可攻击最早时间
	);
	std::string& BuildPkg_DemonTowerAtkCDNotify( //只组包不发送
		UINT32 dwGuardNextAttackTime //锁妖塔可攻击最早时间
	);

	//发送：镇妖塔玩家信息
	bool Send_DemonTowerPlayerNotify( //发送给当前协议处理的客户端
		const SDemonTowerPlayer& oDemonTowerPlayerInfo //镇妖塔玩家信息
	);
	bool SendClt_DemonTowerPlayerNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SDemonTowerPlayer& oDemonTowerPlayerInfo //镇妖塔玩家信息
	);
	std::string& BuildPkg_DemonTowerPlayerNotify( //只组包不发送
		const SDemonTowerPlayer& oDemonTowerPlayerInfo //镇妖塔玩家信息
	);

	//发送：镇妖塔错误信息
	bool Send_DemonTowerErrorNotify( //发送给当前协议处理的客户端
		UINT32 dwError //错误码
	);
	bool SendClt_DemonTowerErrorNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwError //错误码
	);
	std::string& BuildPkg_DemonTowerErrorNotify( //只组包不发送
		UINT32 dwError //错误码
	);

	//发送：镇守锁妖塔通知
	bool Send_GuardSucessNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos //镇守位置
	);
	bool SendClt_GuardSucessNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos //镇守位置
	);
	std::string& BuildPkg_GuardSucessNotify( //只组包不发送
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos //镇守位置
	);

	//发送：19点重置奖励通知
	bool Send_DemonTowerResetNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		const TVecMoneyInfo& vecSoulPrize //获得的魄奖励
	);
	bool SendClt_DemonTowerResetNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		const TVecMoneyInfo& vecSoulPrize //获得的魄奖励
	);
	std::string& BuildPkg_DemonTowerResetNotify( //只组包不发送
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		const TVecMoneyInfo& vecSoulPrize //获得的魄奖励
	);

	//发送：镇妖塔被抢通知
	bool Send_DemonTowerBeAttackNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID, //层数
		UINT32 dwPos, //位置
		UINT64 qwAtkUserID, //抢夺人的Id
		const std::string& strRole, //抢夺人的名字
		const TVecMoneyInfo& vecFailSoulPrize //失败后的魄奖励
	);
	bool SendClt_DemonTowerBeAttackNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID, //层数
		UINT32 dwPos, //位置
		UINT64 qwAtkUserID, //抢夺人的Id
		const std::string& strRole, //抢夺人的名字
		const TVecMoneyInfo& vecFailSoulPrize //失败后的魄奖励
	);
	std::string& BuildPkg_DemonTowerBeAttackNotify( //只组包不发送
		UINT32 dwFloorID, //层数
		UINT32 dwPos, //位置
		UINT64 qwAtkUserID, //抢夺人的Id
		const std::string& strRole, //抢夺人的名字
		const TVecMoneyInfo& vecFailSoulPrize //失败后的魄奖励
	);

	//发送：玩家切层通知
	bool Send_EnterDemonTowerNotify( //发送给当前协议处理的客户端
		UINT32 dwCurFloorID //当前进入的层数
	);
	bool SendClt_EnterDemonTowerNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwCurFloorID //当前进入的层数
	);
	std::string& BuildPkg_EnterDemonTowerNotify( //只组包不发送
		UINT32 dwCurFloorID //当前进入的层数
	);

	//发送：镇妖塔分身崩溃通知
	bool Send_PrizeNotify( //发送给当前协议处理的客户端
		EDemonTowerPrize eDemonTowerPrize, //魄奖励类型
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		const TVecMoneyInfo& vecPrize //魄奖励
	);
	bool SendClt_PrizeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EDemonTowerPrize eDemonTowerPrize, //魄奖励类型
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		const TVecMoneyInfo& vecPrize //魄奖励
	);
	std::string& BuildPkg_PrizeNotify( //只组包不发送
		EDemonTowerPrize eDemonTowerPrize, //魄奖励类型
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		const TVecMoneyInfo& vecPrize //魄奖励
	);

	//发送：过关信息
	bool Send_PassInfoNotify( //发送给当前协议处理的客户端
		UINT16 wFloorID, //通关层
		const TVecDemonTowerKillMonster& vecMinRound, //最快通关
		const TVecDemonTowerKillMonster& vecMinBattlePoint //最小战斗力通关
	);
	bool SendClt_PassInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wFloorID, //通关层
		const TVecDemonTowerKillMonster& vecMinRound, //最快通关
		const TVecDemonTowerKillMonster& vecMinBattlePoint //最小战斗力通关
	);
	std::string& BuildPkg_PassInfoNotify( //只组包不发送
		UINT16 wFloorID, //通关层
		const TVecDemonTowerKillMonster& vecMinRound, //最快通关
		const TVecDemonTowerKillMonster& vecMinBattlePoint //最小战斗力通关
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SEnterDemonTowerAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SEnterDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入锁妖塔
	virtual bool OnRecv_EnterDemonTower(
		UINT32 dwFloorID, //层数
		shared_func<SEnterDemonTowerAck>& fnAck //返回回调函数
	) = 0;

	struct SLeaveDemonTowerAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SLeaveDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：离开锁妖塔
	virtual bool OnRecv_LeaveDemonTower(
		shared_func<SLeaveDemonTowerAck>& fnAck //返回回调函数
	) = 0;

	struct SSealMonsterAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SSealMonsterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：封印怪物(挑战?)
	virtual bool OnRecv_SealMonster(
		UINT32 dwFloorID, //层数
		shared_func<SSealMonsterAck>& fnAck //返回回调函数
	) = 0;

	struct SGuardAtkAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SGuardAtkAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：镇守锁妖塔
	virtual bool OnRecv_GuardAtk(
		UINT32 dwFloorID, //层数 0表示放弃镇守位置
		UINT32 dwGuardPos, //镇守位置
		shared_func<SGuardAtkAck>& fnAck //返回回调函数
	) = 0;

	struct SAtkPlayerAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SAtkPlayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：抢夺镇守位置
	virtual bool OnRecv_AtkPlayer(
		UINT32 dwFloorID, //层数
		UINT32 dwGuardPos, //镇守位置
		shared_func<SAtkPlayerAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取奖励
	virtual bool OnRecv_TakePrize(
		EDemonTowerPrize ePrizeType, //奖励类型
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTopListAck : public CClientFuncAck
	{
		SDemonFloorPage oDemonFloorPage; //分页信息

		SGetTopListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取镇守榜
	virtual bool OnRecv_GetTopList(
		UINT16 wPage, //页码 1开始
		UINT16 wPageItemCount, //每页显示数目 默认5
		shared_func<SGetTopListAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDemonTowerInfoAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功 1-失败（非错误，没有进过镇妖塔）
		SDemonTowerPlayer oDemonTowerPlayer; //玩家镇守信息

		SGetDemonTowerInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取本人镇妖塔相关信息
	virtual bool OnRecv_GetDemonTowerInfo(
		shared_func<SGetDemonTowerInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuardInfoAck : public CClientFuncAck
	{
		TVecGuardInfo vecGuardInfo; //镇守信息信息

		SGetGuardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取镇守信息信息
	virtual bool OnRecv_GetGuardInfo(
		UINT32 dwFloorID, //镇守层
		shared_func<SGetGuardInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：恢复元神
	virtual void OnRecv_Restore(
		UINT32 dwCount //物品数量
	) = 0;

	//接收：增加聚魂速度
	virtual void OnRecv_AddSpeed(
		UINT32 dwCount //物品数量
	) = 0;

	struct SGetPlayerInfoAck : public CClientFuncAck
	{
		UINT8 bRet; //0 成功 1玩家不存在
		SDemonFloorPlayer oDemonFloorPlayer; //玩家镇守信息

		SGetPlayerInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家镇守信息
	virtual bool OnRecv_GetPlayerInfo(
		UINT64 qwUserID, //账号ID
		shared_func<SGetPlayerInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SClearFightCdAck : public CClientFuncAck
	{
		UINT8 bRet; //0成功 其他失败

		SClearFightCdAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：清除pvp战斗cd
	virtual bool OnRecv_ClearFightCd(
		shared_func<SClearFightCdAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPassInfoAck : public CClientFuncAck
	{
		TVecDemonTowerKillMonster vecMinRound; //最快通关
		TVecDemonTowerKillMonster vecMinBattlePoint; //最小战斗力通关

		SGetPassInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取过关信息
	virtual bool OnRecv_GetPassInfo(
		UINT16 wFloorID, //通关层
		shared_func<SGetPassInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 71; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_EnterDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SealMonster(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuardAtk(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AtkPlayer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTopList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDemonTowerInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuardInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Restore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddSpeed(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ClearFightCd(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPassInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDemonTowerGSSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDemonTowerGS
