/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterTeam.h
//  Purpose:      GameServer到CenterServer关于Team的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterTeam.h"

namespace NGame2CenterTeam
{

//协议类：GameServer到CenterServer关于Team的通信协议
class CGame2CenterTeamClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：同步队伍成员
	bool Send_SynTeamFighter( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);
	bool SendSvr_SynTeamFighter(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);
	std::string& BuildPkg_SynTeamFighter( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);

	//发送：同步增加美女,如果原来有美女，替换
	bool Send_SynTeamAddBeauty( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);
	bool SendSvr_SynTeamAddBeauty(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);
	std::string& BuildPkg_SynTeamAddBeauty( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	);

	//发送：同步删除美女
	bool Send_SynTeamDelBeauty( //发送给当前协议处理的服务器
		UINT64 qwUsrID //帐号ID
	);
	bool SendSvr_SynTeamDelBeauty(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID //帐号ID
	);
	std::string& BuildPkg_SynTeamDelBeauty( //只组包不发送
		UINT64 qwUsrID //帐号ID
	);

	//发送：同步奖励系数
	bool Send_SynRewardRate( //发送给当前协议处理的服务器
		UINT32 dwRewardRate //奖励系数万分比
	);
	bool SendSvr_SynRewardRate(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT32 dwRewardRate //奖励系数万分比
	);
	std::string& BuildPkg_SynRewardRate( //只组包不发送
		UINT32 dwRewardRate //奖励系数万分比
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SCanEnterCreateTeamAck : public CServerFuncAck
	{
		NTeamGS::ETEAMResult eResult; //操作结果
		NTeamGS::TVecTeamFighter vecFighter; //获取战斗对象

		SCanEnterCreateTeamAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家请求加入，创建队伍
	virtual bool OnRecv_CanEnterCreateTeam(
		UINT64 qwUsrID, //帐号ID
		UINT8 byHeroNum, //0,不需要将，>0，需要主将，散仙数量：byHeroNum，美女
		UINT16 wDgnType, //副本模板
		shared_func<SCanEnterCreateTeamAck>& fnAck //返回回调函数
	) = 0;

	//接收：玩家加入/离开队伍信息同步
	virtual void OnRecv_SynTeam(
		UINT64 qwUsrID, //帐号ID
		EPlayerTeam eStatus //玩家操作
	) = 0;

	struct SGetFighterFeatureByInsIDAck : public CServerFuncAck
	{
		NTeamGS::CommonFighter stFighter; //获取战斗对象

		SGetFighterFeatureByInsIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：根据实例拉取将外观
	virtual bool OnRecv_GetFighterFeatureByInsID(
		UINT64 qwUsrID, //帐号ID
		UINT64 qwFighterID, //将ID
		shared_func<SGetFighterFeatureByInsIDAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerBattleInfoAck : public CServerFuncAck
	{
		NTeamGS::ETEAMResult eResult; //操作结果
		NBattleGS::TVecBattleFighter vecFighter; //战斗对象

		SGetPlayerBattleInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家战斗信息
	virtual bool OnRecv_GetPlayerBattleInfo(
		UINT64 qwUsrID, //帐号ID
		UINT8 byPlayerPos, //玩家所在的队伍位置
		const TVecUINT64& vecFigther, //散仙唯一ID
		const TVecUINT8& vecPos, //玩家序列位置
		UINT8 byNeedBeauty, //0,不需要美女，1需要美女
		UINT16 wDgnType, //副本类型
		shared_func<SGetPlayerBattleInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SStartBattleAck : public CServerFuncAck
	{
		TeamReport stTeamReport; //通告战斗结果

		SStartBattleAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求发起战斗
	virtual bool OnRecv_StartBattle(
		UINT64 qwUsrID, //队长ID
		UINT16 wDgnType, //副本类型
		const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
		shared_func<SStartBattleAck>& fnAck //返回回调函数
	) = 0;

	//接收：通告战斗结果
	virtual void OnRecv_NoticeTeamReport(
		UINT64 qwUsrID, //帐号ID
		UINT16 wDgnType, //副本类型
		const TeamReport& stTeamReport, //副本类型
		UINT32 dwRewardRate //奖励系数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 57; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_CanEnterCreateTeam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynTeam(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFighterFeatureByInsID(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerBattleInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_StartBattle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NoticeTeamReport(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGame2CenterTeamClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterTeam
