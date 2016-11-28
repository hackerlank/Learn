/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterGuildBattle.h
//  Purpose:      帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterGuildBattle.h"

namespace NGame2CenterGuildBattle
{

//协议类：帮派战相关协议
class CGame2CenterGuildBattleSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帮派等级更新
	bool Send_GuildLevelChanged( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wLevel //帮派等级
	);
	bool SendSvr_GuildLevelChanged(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wLevel //帮派等级
	);
	std::string& BuildPkg_GuildLevelChanged( //只组包不发送
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wLevel //帮派等级
	);

	//发送：帮主更新
	bool Send_GuildOwnerChanged( //发送给当前协议处理的服务器
		UINT64 qwGuildID, //帮派对应ID
		const std::string& strGuildOwnerName //帮主名称
	);
	bool SendSvr_GuildOwnerChanged(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID, //帮派对应ID
		const std::string& strGuildOwnerName //帮主名称
	);
	std::string& BuildPkg_GuildOwnerChanged( //只组包不发送
		UINT64 qwGuildID, //帮派对应ID
		const std::string& strGuildOwnerName //帮主名称
	);

	//发送：帮派解散
	bool Send_GuildDisband( //发送给当前协议处理的服务器
		UINT64 qwGuildID //帮派对应ID
	);
	bool SendSvr_GuildDisband(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwGuildID //帮派对应ID
	);
	std::string& BuildPkg_GuildDisband( //只组包不发送
		UINT64 qwGuildID //帮派对应ID
	);

	//发送：可以发送新帮派战数据
	bool Send_ReadyToSendNewGuildBattle( //发送给当前协议处理的服务器
	);
	bool SendSvr_ReadyToSendNewGuildBattle(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_ReadyToSendNewGuildBattle( //只组包不发送
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：帮派战状态设定
	virtual void OnRecv_SetState(
		NGuildBattleProt::EGBState eState //当前帮派战状态
	) = 0;

	struct SUserSignUpAck : public CServerFuncAck
	{
		UINT64 qwGuildID; //帮派ID
		UINT16 wLevel; //帮派等级
		std::string strGuildName; //帮派名称
		UINT32 dwScore; //帮派战积分
		NGuildBattleProt::EGBSignUpResult eResult; //玩家报名结果

		SUserSignUpAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派战用户报名
	virtual bool OnRecv_UserSignUp(
		UINT64 qwRoleID, //玩家ID
		shared_func<SUserSignUpAck>& fnAck //返回回调函数
	) = 0;

	//接收：帮派战相关广播
	virtual void OnRecv_InfoNotify(
		UINT64 qwGuildID, //帮派对应ID
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	) = 0;

	struct SGetAuthorityAck : public CServerFuncAck
	{
		bool bHasAuthority; //是否有帮派战操作权限

		SGetAuthorityAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：是否有帮派战操作权限
	virtual bool OnRecv_GetAuthority(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetAuthorityAck>& fnAck //返回回调函数
	) = 0;

	//接收：增加帮派战积分
	virtual void OnRecv_AddScore(
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore, //帮派战积分
		const TVecMemberScore& vecMemberScore //玩家获得积分
	) = 0;

	//接收：增加帮派战帮派积分
	virtual void OnRecv_AddGuildScore(
		UINT64 qwGuildID, //帮派ID
		UINT32 dwScore //帮派战积分
	) = 0;

	//接收：增加帮派战成员积分
	virtual void OnRecv_AddMemberScore(
		UINT64 qwGuildID, //帮派ID
		const TVecMemberScore& vecMemberScore //玩家获得积分
	) = 0;

	struct SGetPanelInfoAck : public CServerFuncAck
	{
		UINT32 dwSelfScore; //我的积分
		UINT32 dwGuildScore; //帮派积分
		UINT32 dwGuildRank; //帮派排名

		SGetPanelInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派战相关面板信息
	virtual bool OnRecv_GetPanelInfo(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetPanelInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：更新帮派战积分排名
	virtual void OnRecv_SyncGuildRank(
	) = 0;

	//接收：帮派战状态设定
	virtual void OnRecv_NewSetState(
		NNewGuildBattleProt::ENGBState eState //当前帮派战状态
	) = 0;

	struct SNewGetGuildIDAck : public CServerFuncAck
	{
		UINT64 qwGuildID; //帮派ID
		std::string strGuildName; //帮派名称
		UINT8 byGuildLvl; //帮派等级

		SNewGetGuildIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派ID
	virtual bool OnRecv_NewGetGuildID(
		UINT64 qwRoleID, //玩家ID
		shared_func<SNewGetGuildIDAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 77; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_SetState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UserSignUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InfoNotify(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAuthority(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddScore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddGuildScore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddMemberScore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPanelInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SyncGuildRank(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NewSetState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NewGetGuildID(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGame2CenterGuildBattleSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterGuildBattle
