/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterTeam.h
//  Purpose:      GameServer到CenterServer关于Team的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "Game2CenterTeam.h"

namespace NGame2CenterTeam
{

//协议类：GameServer到CenterServer关于Team的通信协议
class CGame2CenterTeamSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家请求加入，创建队伍
	bool Send_CanEnterCreateTeam( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT8 byHeroNum, //0,不需要将，>0，需要主将，散仙数量：byHeroNum，美女
		UINT16 wDgnType, //副本模板
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NTeamGS::ETEAMResult eResult, //(返回值)操作结果
			const NTeamGS::TVecTeamFighter& vecFighter //(返回值)获取战斗对象
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_CanEnterCreateTeam(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT8 byHeroNum, //0,不需要将，>0，需要主将，散仙数量：byHeroNum，美女
		UINT16 wDgnType, //副本模板
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NTeamGS::ETEAMResult eResult, //(返回值)操作结果
			const NTeamGS::TVecTeamFighter& vecFighter //(返回值)获取战斗对象
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：玩家加入/离开队伍信息同步
	bool Send_SynTeam( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		EPlayerTeam eStatus //玩家操作
	);
	bool SendSvr_SynTeam(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		EPlayerTeam eStatus //玩家操作
	);
	std::string& BuildPkg_SynTeam( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		EPlayerTeam eStatus //玩家操作
	);

	//发送：根据实例拉取将外观
	bool Send_GetFighterFeatureByInsID( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwFighterID, //将ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NTeamGS::CommonFighter& stFighter //(返回值)获取战斗对象
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetFighterFeatureByInsID(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT64 qwFighterID, //将ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const NTeamGS::CommonFighter& stFighter //(返回值)获取战斗对象
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：获取玩家战斗信息
	bool Send_GetPlayerBattleInfo( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT8 byPlayerPos, //玩家所在的队伍位置
		const TVecUINT64& vecFigther, //散仙唯一ID
		const TVecUINT8& vecPos, //玩家序列位置
		UINT8 byNeedBeauty, //0,不需要美女，1需要美女
		UINT16 wDgnType, //副本类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NTeamGS::ETEAMResult eResult, //(返回值)操作结果
			const NBattleGS::TVecBattleFighter& vecFighter //(返回值)战斗对象
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetPlayerBattleInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT8 byPlayerPos, //玩家所在的队伍位置
		const TVecUINT64& vecFigther, //散仙唯一ID
		const TVecUINT8& vecPos, //玩家序列位置
		UINT8 byNeedBeauty, //0,不需要美女，1需要美女
		UINT16 wDgnType, //副本类型
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			NTeamGS::ETEAMResult eResult, //(返回值)操作结果
			const NBattleGS::TVecBattleFighter& vecFighter //(返回值)战斗对象
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：请求发起战斗
	bool Send_StartBattle( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //队长ID
		UINT16 wDgnType, //副本类型
		const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TeamReport& stTeamReport //(返回值)通告战斗结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_StartBattle(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //队长ID
		UINT16 wDgnType, //副本类型
		const NBattleGS::TVecBattleFighter& vecFighter, //其他服战斗对象
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			const TeamReport& stTeamReport //(返回值)通告战斗结果
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	//发送：通告战斗结果
	bool Send_NoticeTeamReport( //发送给当前协议处理的服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wDgnType, //副本类型
		const TeamReport& stTeamReport, //副本类型
		UINT32 dwRewardRate //奖励系数
	);
	bool SendSvr_NoticeTeamReport(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwUsrID, //帐号ID
		UINT16 wDgnType, //副本类型
		const TeamReport& stTeamReport, //副本类型
		UINT32 dwRewardRate //奖励系数
	);
	std::string& BuildPkg_NoticeTeamReport( //只组包不发送
		UINT64 qwUsrID, //帐号ID
		UINT16 wDgnType, //副本类型
		const TeamReport& stTeamReport, //副本类型
		UINT32 dwRewardRate //奖励系数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：同步队伍成员
	virtual void OnRecv_SynTeamFighter(
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	) = 0;

	//接收：同步增加美女,如果原来有美女，替换
	virtual void OnRecv_SynTeamAddBeauty(
		UINT64 qwUsrID, //帐号ID
		const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
	) = 0;

	//接收：同步删除美女
	virtual void OnRecv_SynTeamDelBeauty(
		UINT64 qwUsrID //帐号ID
	) = 0;

	//接收：同步奖励系数
	virtual void OnRecv_SynRewardRate(
		UINT32 dwRewardRate //奖励系数万分比
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 57; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_SynTeamFighter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynTeamAddBeauty(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynTeamDelBeauty(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SynRewardRate(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_CanEnterCreateTeam(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_CanEnterCreateTeam(UINT32 dwSessionID);
	bool _DoReturn_GetFighterFeatureByInsID(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetFighterFeatureByInsID(UINT32 dwSessionID);
	bool _DoReturn_GetPlayerBattleInfo(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetPlayerBattleInfo(UINT32 dwSessionID);
	bool _DoReturn_StartBattle(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_StartBattle(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterTeamSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterTeamSvr::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterTeam
