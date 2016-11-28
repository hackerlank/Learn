/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DemonTower.h
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DemonTower.h"

namespace NDemonTower
{

//协议类：锁妖塔
class CDemonTowerSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：升级魄空间通知
	bool Send_UpgradeSoulSpaceNotify( //发送给当前协议处理的客户端
		UINT32 dwSoulSpaceID, //魄空间类型ID(升级结果)
		UINT32 dwSoulSpaceLevel //魄空间等级(升级结果)
	);
	bool SendClt_UpgradeSoulSpaceNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwSoulSpaceID, //魄空间类型ID(升级结果)
		UINT32 dwSoulSpaceLevel //魄空间等级(升级结果)
	);
	std::string& BuildPkg_UpgradeSoulSpaceNotify( //只组包不发送
		UINT32 dwSoulSpaceID, //魄空间类型ID(升级结果)
		UINT32 dwSoulSpaceLevel //魄空间等级(升级结果)
	);

	//发送：魄空间列表
	bool Send_SoulSpaceListNotify( //发送给当前协议处理的客户端
		const TVecSpaceInfo& vecSpaceInfo //魄空间列表
	);
	bool SendClt_SoulSpaceListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecSpaceInfo& vecSpaceInfo //魄空间列表
	);
	std::string& BuildPkg_SoulSpaceListNotify( //只组包不发送
		const TVecSpaceInfo& vecSpaceInfo //魄空间列表
	);

	//发送：每日重置奖励通知
	bool Send_DayPrizeResetNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID //层数
	);
	bool SendClt_DayPrizeResetNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID //层数
	);
	std::string& BuildPkg_DayPrizeResetNotify( //只组包不发送
		UINT32 dwFloorID //层数
	);

	//发送：被攻击列表通知
	bool Send_AttackListNotify( //发送给当前协议处理的客户端
		const TVecDemonToweAttackedInfo& oDemonToweAttackedInfo //被攻击列表
	);
	bool SendClt_AttackListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecDemonToweAttackedInfo& oDemonToweAttackedInfo //被攻击列表
	);
	std::string& BuildPkg_AttackListNotify( //只组包不发送
		const TVecDemonToweAttackedInfo& oDemonToweAttackedInfo //被攻击列表
	);

	//发送：被攻击通知(收到通知后拉取被攻击列表)
	bool Send_AttackChangedNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_AttackChangedNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_AttackChangedNotify( //只组包不发送
	);

	//发送：通关协议
	bool Send_FloorPassNotify( //发送给当前协议处理的客户端
		UINT32 dwFloorID //通关层数
	);
	bool SendClt_FloorPassNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwFloorID //通关层数
	);
	std::string& BuildPkg_FloorPassNotify( //只组包不发送
		UINT32 dwFloorID //通关层数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SEnterDemonTowerAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SEnterDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入锁妖塔 (暂时不用)
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
	//接收：离开锁妖塔 (暂时不用)
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
	//接收：封印怪物(暂时不用)
	virtual bool OnRecv_SealMonster(
		UINT32 dwFloorID, //层数
		shared_func<SSealMonsterAck>& fnAck //返回回调函数
	) = 0;

	struct SUpgradeSoulSpaceAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		SUpgradeSoulSpaceAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：升级魄空间
	virtual bool OnRecv_UpgradeSoulSpace(
		UINT32 dwSoulSpaceID, //魄空间类型ID
		shared_func<SUpgradeSoulSpaceAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取魄空间列表
	virtual void OnRecv_GetSoulSpace(
	) = 0;

	//接收：获取被攻击列表
	virtual void OnRecv_GetAttackedList(
	) = 0;

	struct STakeDayPrizeAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码

		STakeDayPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取每日奖励
	virtual bool OnRecv_TakeDayPrize(
		shared_func<STakeDayPrizeAck>& fnAck //返回回调函数
	) = 0;

	struct STakeLayerPrizeAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果 0成功其他错误码
		UINT32 dwFloorID; //最高已领奖层

		STakeLayerPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取每层奖励
	virtual bool OnRecv_TakeLayerPrize(
		UINT32 dwFloorID, //层数
		shared_func<STakeLayerPrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetTopPrizeLayerAck : public CClientFuncAck
	{
		UINT32 dwFloorID; //层数

		SGetTopPrizeLayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取最高已领奖层
	virtual bool OnRecv_GetTopPrizeLayer(
		shared_func<SGetTopPrizeLayerAck>& fnAck //返回回调函数
	) = 0;

	struct SClearFightMonsterCdAck : public CClientFuncAck
	{
		UINT8 bRet; //0成功 其他失败

		SClearFightMonsterCdAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：清除pve战斗cd
	virtual bool OnRecv_ClearFightMonsterCd(
		shared_func<SClearFightMonsterCdAck>& fnAck //返回回调函数
	) = 0;

	struct SGetLayerPrizedAck : public CClientFuncAck
	{
		TVecUINT32 vecFloorID; //已领奖励层数

		SGetLayerPrizedAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取已领奖励层数
	virtual bool OnRecv_GetLayerPrized(
		shared_func<SGetLayerPrizedAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 70; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_EnterDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SealMonster(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpgradeSoulSpace(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSoulSpace(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAttackedList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeDayPrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeLayerPrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTopPrizeLayer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ClearFightMonsterCd(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetLayerPrized(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDemonTowerSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDemonTower
