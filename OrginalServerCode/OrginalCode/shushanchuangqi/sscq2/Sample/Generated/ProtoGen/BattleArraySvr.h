/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BattleArray.h
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "BattleArray.h"

namespace NBattleArray
{

//协议类：破阵
class CBattleArraySvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：阵信息更新
	bool Send_BattleArrayNotify( //发送给当前协议处理的客户端
		const SBattleArray& oBattleArray //阵信息
	);
	bool SendClt_BattleArrayNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SBattleArray& oBattleArray //阵信息
	);
	std::string& BuildPkg_BattleArrayNotify( //只组包不发送
		const SBattleArray& oBattleArray //阵信息
	);

	//发送：攻击阵图信息
	bool Send_SBattleArrayAttackCntNotify( //发送给当前协议处理的客户端
		const SBattleArrayAttackCnt& oBattleArrayAttackCnt //攻击阵图信息
	);
	bool SendClt_SBattleArrayAttackCntNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SBattleArrayAttackCnt& oBattleArrayAttackCnt //攻击阵图信息
	);
	std::string& BuildPkg_SBattleArrayAttackCntNotify( //只组包不发送
		const SBattleArrayAttackCnt& oBattleArrayAttackCnt //攻击阵图信息
	);

	//发送：总攻击次数
	bool Send_TotleAttackCntNotify( //发送给当前协议处理的客户端
		UINT32 dwAttackCnt, //总攻击次数
		UINT32 dwBuyCnt //剩余购买数
	);
	bool SendClt_TotleAttackCntNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwAttackCnt, //总攻击次数
		UINT32 dwBuyCnt //剩余购买数
	);
	std::string& BuildPkg_TotleAttackCntNotify( //只组包不发送
		UINT32 dwAttackCnt, //总攻击次数
		UINT32 dwBuyCnt //剩余购买数
	);

	//发送：获得物品通知
	bool Send_GainNotify( //发送给当前协议处理的客户端
		EBattleArrayGain eBattleArrayGain, //类型
		const NItemProt::TVecItemGenInfo& vecItemGenInfo //物品
	);
	bool SendClt_GainNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EBattleArrayGain eBattleArrayGain, //类型
		const NItemProt::TVecItemGenInfo& vecItemGenInfo //物品
	);
	std::string& BuildPkg_GainNotify( //只组包不发送
		EBattleArrayGain eBattleArrayGain, //类型
		const NItemProt::TVecItemGenInfo& vecItemGenInfo //物品
	);

	//发送：全部阵信息
	bool Send_GetBattleArrayNotify( //发送给当前协议处理的客户端
		const TVecBattleArray& vecBattleArray, //阵信息列表
		const TVecBattleArrayAttackCnt& vecBattleArrayAttackCnt, //攻击阵图信息
		UINT32 dwBuyCnt, //可用的次数
		UINT32 dwDayBuyCnt //当天购买次数
	);
	bool SendClt_GetBattleArrayNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecBattleArray& vecBattleArray, //阵信息列表
		const TVecBattleArrayAttackCnt& vecBattleArrayAttackCnt, //攻击阵图信息
		UINT32 dwBuyCnt, //可用的次数
		UINT32 dwDayBuyCnt //当天购买次数
	);
	std::string& BuildPkg_GetBattleArrayNotify( //只组包不发送
		const TVecBattleArray& vecBattleArray, //阵信息列表
		const TVecBattleArrayAttackCnt& vecBattleArrayAttackCnt, //攻击阵图信息
		UINT32 dwBuyCnt, //可用的次数
		UINT32 dwDayBuyCnt //当天购买次数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetBattleArrayAck : public CClientFuncAck
	{
		TVecBattleArray vecBattleArray; //阵信息列表
		TVecBattleArrayAttackCnt vecBattleArrayAttackCnt; //攻击阵图信息
		UINT32 dwBuyCnt; //可用的次数
		UINT32 dwDayBuyCnt; //当天购买次数
		UINT32 dwFailCd; //战败cd

		SGetBattleArrayAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取阵信息
	virtual bool OnRecv_GetBattleArray(
		shared_func<SGetBattleArrayAck>& fnAck //返回回调函数
	) = 0;

	struct SAttackBattleArrayAck : public CClientFuncAck
	{
		EBattleArrayRet eBattleArrayRet; //操作结果
		UINT32 dwFailCd; //战败cd

		SAttackBattleArrayAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：攻击阵图
	virtual bool OnRecv_AttackBattleArray(
		UINT32 dwBattleArrayLevelID, //阵图id
		shared_func<SAttackBattleArrayAck>& fnAck //返回回调函数
	) = 0;

	struct SSweepBattleArrayAck : public CClientFuncAck
	{
		EBattleArrayRet eBattleArrayRet; //操作结果

		SSweepBattleArrayAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扫荡阵图
	virtual bool OnRecv_SweepBattleArray(
		UINT32 dwBattleArrayLevelID, //阵图id
		shared_func<SSweepBattleArrayAck>& fnAck //返回回调函数
	) = 0;

	struct SBattleArrayTakePrizeAck : public CClientFuncAck
	{
		EBattleArrayRet eBattleArrayRet; //操作结果

		SBattleArrayTakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取通关奖励
	virtual bool OnRecv_BattleArrayTakePrize(
		UINT16 wBattleArrayID, //阵id
		shared_func<SBattleArrayTakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetBuyAtkCountPriceAck : public CClientFuncAck
	{
		UINT32 dwPrice; //价格
		UINT32 dwBuyCount; //当天已购买次数

		SGetBuyAtkCountPriceAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取当前购买价格
	virtual bool OnRecv_GetBuyAtkCountPrice(
		UINT32 dwCount, //购买次数
		shared_func<SGetBuyAtkCountPriceAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyAtkCountAck : public CClientFuncAck
	{
		EBattleArrayRet eRet; //结果
		UINT32 dwBuyCount; //已购买次数
		UINT32 dwDayBuyCnt; //当天购买次数

		SBuyAtkCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买攻击阵图次数
	virtual bool OnRecv_BuyAtkCount(
		UINT32 dwCount, //购买次数
		shared_func<SBuyAtkCountAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 130; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetBattleArray(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AttackBattleArray(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SweepBattleArray(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BattleArrayTakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBuyAtkCountPrice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyAtkCount(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CBattleArraySvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NBattleArray
