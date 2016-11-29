/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterDemonTower.h
//  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterDemonTower.h"

namespace NGame2CenterDemonTower
{

//协议类：GameServer到CenterServer关于镇妖塔的通信协议
class CGame2CenterDemonTowerClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家进入镇妖塔
	bool Send_OnEnterDemonTower( //发送给当前协议处理的服务器
		const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
	);
	bool SendSvr_OnEnterDemonTower(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
	);
	std::string& BuildPkg_OnEnterDemonTower( //只组包不发送
		const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
	);

	//发送：玩家离开镇妖塔
	bool Send_OnLeaveDemonTower( //发送给当前协议处理的服务器
		UINT64 qwUserID //玩家账号
	);
	bool SendSvr_OnLeaveDemonTower(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID //玩家账号
	);
	std::string& BuildPkg_OnLeaveDemonTower( //只组包不发送
		UINT64 qwUserID //玩家账号
	);

	//发送：镇妖塔过关
	bool Send_OnPassDemonTower( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家账号
		UINT16 wFloorID, //过关层数
		UINT16 wMonsterColor, //怪物颜色
		const std::string& strMonsterName //封印怪物
	);
	bool SendSvr_OnPassDemonTower(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家账号
		UINT16 wFloorID, //过关层数
		UINT16 wMonsterColor, //怪物颜色
		const std::string& strMonsterName //封印怪物
	);
	std::string& BuildPkg_OnPassDemonTower( //只组包不发送
		UINT64 qwUserID, //玩家账号
		UINT16 wFloorID, //过关层数
		UINT16 wMonsterColor, //怪物颜色
		const std::string& strMonsterName //封印怪物
	);

	//发送：击败锁妖塔怪物
	bool Send_OnKillMonster( //发送给当前协议处理的服务器
		const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
	);
	bool SendSvr_OnKillMonster(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
	);
	std::string& BuildPkg_OnKillMonster( //只组包不发送
		const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
	);

	//发送：19点重置事件
	bool Send_OnPlayerReset( //发送给当前协议处理的服务器
		UINT64 qwUserID //玩家账号
	);
	bool SendSvr_OnPlayerReset(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID //玩家账号
	);
	std::string& BuildPkg_OnPlayerReset( //只组包不发送
		UINT64 qwUserID //玩家账号
	);

	//发送：玩家进入下一层
	bool Send_OnPlayerEnterNextFloor( //发送给当前协议处理的服务器
		UINT64 qwUserID //玩家账号
	);
	bool SendSvr_OnPlayerEnterNextFloor(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID //玩家账号
	);
	std::string& BuildPkg_OnPlayerEnterNextFloor( //只组包不发送
		UINT64 qwUserID //玩家账号
	);

	//发送：玩家进入请求
	bool Send_PlayerEnterFloorRequest( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家账号
		UINT32 dwFloorID //层数
	);
	bool SendSvr_PlayerEnterFloorRequest(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家账号
		UINT32 dwFloorID //层数
	);
	std::string& BuildPkg_PlayerEnterFloorRequest( //只组包不发送
		UINT64 qwUserID, //玩家账号
		UINT32 dwFloorID //层数
	);

	//发送：获取玩家被攻击信息列表
	bool Send_GetAttackedLayerInfo( //发送给当前协议处理的服务器
		UINT64 qwUserID, //玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUserID, //(返回值)玩家账号
			const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetAttackedLayerInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUserID, //玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwUserID, //(返回值)玩家账号
			const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：玩家请求进入镇妖塔
	virtual void OnRecv_EnterDemonTower(
		UINT64 qwUserID, //帐号ID
		UINT32 dwFloorID //层数
	) = 0;

	//接收：玩家请求离开镇妖塔
	virtual void OnRecv_LeaveDemonTower(
		UINT64 qwUsrID //帐号ID
	) = 0;

	struct STakeDailyPrizeAck : public CServerFuncAck
	{
		STakeDailyPrizeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取每日魂值奖励
	virtual bool OnRecv_TakeDailyPrize(
		UINT64 qwUsrID, //帐号ID
		shared_func<STakeDailyPrizeAck>& fnAck //返回回调函数
	) = 0;

	//接收：被攻击信息
	virtual void OnRecv_Attacked(
		UINT64 qwUsrID, //帐号ID
		const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 73; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_EnterDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeaveDemonTower(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeDailyPrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Attacked(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_GetAttackedLayerInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetAttackedLayerInfo(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterDemonTowerClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterDemonTowerClt::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterDemonTower
