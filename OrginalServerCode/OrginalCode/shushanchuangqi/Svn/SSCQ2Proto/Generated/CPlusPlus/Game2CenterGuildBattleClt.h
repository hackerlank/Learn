/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterGuildBattle.h
//  Purpose:      帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterGuildBattle.h"

namespace NGame2CenterGuildBattle
{

//协议类：帮派战相关协议
class CGame2CenterGuildBattleClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帮派战状态设定
	bool Send_SetState( //发送给当前协议处理的服务器
		NGuildBattleProt::EGBState eState //当前帮派战状态
	);
	bool SendSvr_SetState(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NGuildBattleProt::EGBState eState //当前帮派战状态
	);
	std::string& BuildPkg_SetState( //只组包不发送
		NGuildBattleProt::EGBState eState //当前帮派战状态
	);

	//发送：帮派战用户报名
	bool Send_UserSignUp( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwGuildID, //(返回值)帮派ID
			UINT16 wLevel, //(返回值)帮派等级
			const std::string& strGuildName, //(返回值)帮派名称
			UINT32 dwScore, //(返回值)帮派战积分
			NGuildBattleProt::EGBSignUpResult eResult //(返回值)玩家报名结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_UserSignUp(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwGuildID, //(返回值)帮派ID
			UINT16 wLevel, //(返回值)帮派等级
			const std::string& strGuildName, //(返回值)帮派名称
			UINT32 dwScore, //(返回值)帮派战积分
			NGuildBattleProt::EGBSignUpResult eResult //(返回值)玩家报名结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：帮派战相关广播
	bool Send_InfoNotify( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	bool SendSvr_InfoNotify(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	std::string& BuildPkg_InfoNotify( //只组包不发送
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);

	//发送：是否有帮派战操作权限
	bool Send_GetAuthority( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			bool bHasAuthority //(返回值)是否有帮派战操作权限
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetAuthority(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			bool bHasAuthority //(返回值)是否有帮派战操作权限
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：增加帮派战积分
	bool Send_AddScore( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore, //帮派战积分
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);
	bool SendSvr_AddScore(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore, //帮派战积分
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);
	std::string& BuildPkg_AddScore( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore, //帮派战积分
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);

	//发送：增加帮派战帮派积分
	bool Send_AddGuildScore( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore //帮派战积分
	);
	bool SendSvr_AddGuildScore(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore //帮派战积分
	);
	std::string& BuildPkg_AddGuildScore( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore //帮派战积分
	);

	//发送：增加帮派战成员积分
	bool Send_AddMemberScore( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派ID
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);
	bool SendSvr_AddMemberScore(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派ID
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);
	std::string& BuildPkg_AddMemberScore( //只组包不发送
		UINT64 qwGuildID, //帮派ID
		const TVecMemberScore& vecMemberScore //玩家获得积分
	);

	//发送：获取帮派战相关面板信息
	bool Send_GetPanelInfo( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT32 dwSelfScore, //(返回值)我的积分
			UINT32 dwGuildScore, //(返回值)帮派积分
			UINT32 dwGuildRank //(返回值)帮派排名
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetPanelInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT32 dwSelfScore, //(返回值)我的积分
			UINT32 dwGuildScore, //(返回值)帮派积分
			UINT32 dwGuildRank //(返回值)帮派排名
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：更新帮派战积分排名
	bool Send_SyncGuildRank( //发送给当前协议处理的服务器
	);
	bool SendSvr_SyncGuildRank(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_SyncGuildRank( //只组包不发送
	);

	//发送：帮派战状态设定
	bool Send_NewSetState( //发送给当前协议处理的服务器
		NNewGuildBattleProt::ENGBState eState //当前帮派战状态
	);
	bool SendSvr_NewSetState(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NNewGuildBattleProt::ENGBState eState //当前帮派战状态
	);
	std::string& BuildPkg_NewSetState( //只组包不发送
		NNewGuildBattleProt::ENGBState eState //当前帮派战状态
	);

	//发送：获取帮派ID
	bool Send_NewGetGuildID( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwGuildID, //(返回值)帮派ID
			const std::string& strGuildName, //(返回值)帮派名称
			UINT8 byGuildLvl //(返回值)帮派等级
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_NewGetGuildID(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT64 qwGuildID, //(返回值)帮派ID
			const std::string& strGuildName, //(返回值)帮派名称
			UINT8 byGuildLvl //(返回值)帮派等级
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：帮派等级更新
	virtual void OnRecv_GuildLevelChanged(
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wLevel //帮派等级
	) = 0;

	//接收：帮主更新
	virtual void OnRecv_GuildOwnerChanged(
		UINT64 qwGuildID, //帮派对应ID
		const std::string& strGuildOwnerName //帮主名称
	) = 0;

	//接收：帮派解散
	virtual void OnRecv_GuildDisband(
		UINT64 qwGuildID //帮派对应ID
	) = 0;

	//接收：可以发送新帮派战数据
	virtual void OnRecv_ReadyToSendNewGuildBattle(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 77; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GuildLevelChanged(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildOwnerChanged(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GuildDisband(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReadyToSendNewGuildBattle(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_UserSignUp(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_UserSignUp(UINT32 dwSessionID);
	bool _DoReturn_GetAuthority(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetAuthority(UINT32 dwSessionID);
	bool _DoReturn_GetPanelInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetPanelInfo(UINT32 dwSessionID);
	bool _DoReturn_NewGetGuildID(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_NewGetGuildID(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterGuildBattleClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterGuildBattleClt::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterGuildBattle
