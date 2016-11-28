/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterDemonTower.h
//  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterDemonTower.h"

namespace NGame2CenterDemonTower
{

//协议类：GameServer到CenterServer关于镇妖塔的通信协议
class CGame2CenterDemonTowerSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家请求进入镇妖塔
	bool Send_EnterDemonTower( //发送给当前协议处理的服务器
		UINT64 qwUserID, //帐号ID
		UINT32 dwFloorID //层数
	);
	bool SendSvr_EnterDemonTower(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //帐号ID
		UINT32 dwFloorID //层数
	);
	std::string& BuildPkg_EnterDemonTower( //只组包不发送
		UINT64 qwUserID, //帐号ID
		UINT32 dwFloorID //层数
	);

	//发送：玩家请求离开镇妖塔
	bool Send_LeaveDemonTower( //发送给当前协议处理的服务器
		UINT64 qwUsrID //帐号ID
	);
	bool SendSvr_LeaveDemonTower(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID //帐号ID
	);
	std::string& BuildPkg_LeaveDemonTower( //只组包不发送
		UINT64 qwUsrID //帐号ID
	);

	//发送：获取每日魂值奖励
	bool Send_TakeDailyPrize( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_TakeDailyPrize(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：被攻击信息
	bool Send_Attacked( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
	);
	bool SendSvr_Attacked(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
	);
	std::string& BuildPkg_Attacked( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：玩家进入镇妖塔
	virtual void OnRecv_OnEnterDemonTower(
		const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
	) = 0;

	//接收：玩家离开镇妖塔
	virtual void OnRecv_OnLeaveDemonTower(
		UINT64 qwUserID //玩家账号
	) = 0;

	//接收：镇妖塔过关
	virtual void OnRecv_OnPassDemonTower(
		UINT64 qwUserID, //玩家账号
		UINT16 wFloorID, //过关层数
		UINT16 wMonsterColor, //怪物颜色
		const std::string& strMonsterName //封印怪物
	) = 0;

	//接收：击败锁妖塔怪物
	virtual void OnRecv_OnKillMonster(
		const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
	) = 0;

	//接收：19点重置事件
	virtual void OnRecv_OnPlayerReset(
		UINT64 qwUserID //玩家账号
	) = 0;

	//接收：玩家进入下一层
	virtual void OnRecv_OnPlayerEnterNextFloor(
		UINT64 qwUserID //玩家账号
	) = 0;

	//接收：玩家进入请求
	virtual void OnRecv_PlayerEnterFloorRequest(
		UINT64 qwUserID, //玩家账号
		UINT32 dwFloorID //层数
	) = 0;

	struct SGetAttackedLayerInfoAck : public CServerFuncAck
	{
		UINT64 qwUserID; //玩家账号
		NDemonTower::TVecDemonToweAttackedInfo oAttackedList; //被攻击列表

		SGetAttackedLayerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家被攻击信息列表
	virtual bool OnRecv_GetAttackedLayerInfo(
		UINT64 qwUserID, //玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
		shared_func<SGetAttackedLayerInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 73; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_OnEnterDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnLeaveDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnPassDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnKillMonster(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnPlayerReset(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnPlayerEnterNextFloor(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlayerEnterFloorRequest(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAttackedLayerInfo(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_TakeDailyPrize(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_TakeDailyPrize(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterDemonTowerSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterDemonTowerSvr::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterDemonTower
