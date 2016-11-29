/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    NewGuildBattleProt.h
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "NewGuildBattleProt.h"

namespace NNewGuildBattleProt
{

//协议类：新帮派战相关协议
class CNewGuildBattleProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：状态变更广播
	bool Send_StateNotify( //发送给当前协议处理的客户端
		ENGBState eState, //当前帮派战状态
		UINT32 dwRemainTime, //新帮派战剩余时间
		const TVecMountainPanelInfo& vecInfo //各个灵山信息
	);
	bool SendClt_StateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ENGBState eState, //当前帮派战状态
		UINT32 dwRemainTime, //新帮派战剩余时间
		const TVecMountainPanelInfo& vecInfo //各个灵山信息
	);
	std::string& BuildPkg_StateNotify( //只组包不发送
		ENGBState eState, //当前帮派战状态
		UINT32 dwRemainTime, //新帮派战剩余时间
		const TVecMountainPanelInfo& vecInfo //各个灵山信息
	);

	//发送：城门战广播
	bool Send_GateInfoNotify( //发送给当前协议处理的客户端
		const SMountainGateInfo& sInfo //城门信息
	);
	bool SendClt_GateInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SMountainGateInfo& sInfo //城门信息
	);
	std::string& BuildPkg_GateInfoNotify( //只组包不发送
		const SMountainGateInfo& sInfo //城门信息
	);

	//发送：城门战列表通知
	bool Send_GateListNotify( //发送给当前协议处理的客户端
		const TVecPlayerPanelInfo& vecInfo //城门玩家列表信息通知
	);
	bool SendClt_GateListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPlayerPanelInfo& vecInfo //城门玩家列表信息通知
	);
	std::string& BuildPkg_GateListNotify( //只组包不发送
		const TVecPlayerPanelInfo& vecInfo //城门玩家列表信息通知
	);

	//发送：城门被攻破广播
	bool Send_GateBrokenNotify( //发送给当前协议处理的客户端
		ENGBMountain eMountainType, //灵山类型
		const TVecUINT64& vecAttackGuildID //（洞府战）攻击帮派ID
	);
	bool SendClt_GateBrokenNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ENGBMountain eMountainType, //灵山类型
		const TVecUINT64& vecAttackGuildID //（洞府战）攻击帮派ID
	);
	std::string& BuildPkg_GateBrokenNotify( //只组包不发送
		ENGBMountain eMountainType, //灵山类型
		const TVecUINT64& vecAttackGuildID //（洞府战）攻击帮派ID
	);

	//发送：洞府战广播
	bool Send_CaveInfoNotify( //发送给当前协议处理的客户端
		const SCaveInfo& sInfo //洞府具体信息
	);
	bool SendClt_CaveInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SCaveInfo& sInfo //洞府具体信息
	);
	std::string& BuildPkg_CaveInfoNotify( //只组包不发送
		const SCaveInfo& sInfo //洞府具体信息
	);

	//发送：洞府战列表通知
	bool Send_CaveListNotify( //发送给当前协议处理的客户端
		const TVecPlayerPanelInfo& vecInfo //洞府玩家列表信息通知
	);
	bool SendClt_CaveListNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecPlayerPanelInfo& vecInfo //洞府玩家列表信息通知
	);
	std::string& BuildPkg_CaveListNotify( //只组包不发送
		const TVecPlayerPanelInfo& vecInfo //洞府玩家列表信息通知
	);

	//发送：洞府战阵眼信息通知
	bool Send_CaveCoreNotify( //发送给当前协议处理的客户端
		const TVecCaveCoreInfo& vecCaveCoreInfo //阵眼信息
	);
	bool SendClt_CaveCoreNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecCaveCoreInfo& vecCaveCoreInfo //阵眼信息
	);
	std::string& BuildPkg_CaveCoreNotify( //只组包不发送
		const TVecCaveCoreInfo& vecCaveCoreInfo //阵眼信息
	);

	//发送：洞府战被占领通知
	bool Send_CaveCapture( //发送给当前协议处理的客户端
		ENGBMountain eMountainType, //灵山类型
		const std::string& strGuildName //当前占领帮派名称
	);
	bool SendClt_CaveCapture(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		ENGBMountain eMountainType, //灵山类型
		const std::string& strGuildName //当前占领帮派名称
	);
	std::string& BuildPkg_CaveCapture( //只组包不发送
		ENGBMountain eMountainType, //灵山类型
		const std::string& strGuildName //当前占领帮派名称
	);

	//发送：战斗日志通知
	bool Send_BattleLogNotify( //发送给当前协议处理的客户端
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	bool SendClt_BattleLogNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);
	std::string& BuildPkg_BattleLogNotify( //只组包不发送
		UINT16 wMsgID, //消息ID
		const TVecString& vecStr //聊天信息参数
	);

	//发送：战斗日志通知
	bool Send_PuppetAttackNotify( //发送给当前协议处理的客户端
		UINT8 byIndex //所属站位(0,1,2; 0为系统战争傀儡)
	);
	bool SendClt_PuppetAttackNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byIndex //所属站位(0,1,2; 0为系统战争傀儡)
	);
	std::string& BuildPkg_PuppetAttackNotify( //只组包不发送
		UINT8 byIndex //所属站位(0,1,2; 0为系统战争傀儡)
	);

	//发送：战功榜帮派排名信息广播
	bool Send_GuildRankInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecGuildRankInfo& vecInfo //排名信息
	);
	bool SendClt_GuildRankInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecGuildRankInfo& vecInfo //排名信息
	);
	std::string& BuildPkg_GuildRankInfoNotify( //只组包不发送
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecGuildRankInfo& vecInfo //排名信息
	);

	//发送：战功榜帮派成员排名信息广播
	bool Send_GuildMemberRankInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecGuildMemberRankInfo& vecInfo //排名信息
	);
	bool SendClt_GuildMemberRankInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecGuildMemberRankInfo& vecInfo //排名信息
	);
	std::string& BuildPkg_GuildMemberRankInfoNotify( //只组包不发送
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecGuildMemberRankInfo& vecInfo //排名信息
	);

	//发送：战功榜个人排名信息广播
	bool Send_PlayerRankInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecPlayerRankInfo& vecInfo //排名信息
	);
	bool SendClt_PlayerRankInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecPlayerRankInfo& vecInfo //排名信息
	);
	std::string& BuildPkg_PlayerRankInfoNotify( //只组包不发送
		UINT32 dwMaxCount, //最大排名数量
		UINT32 dwCurIndex, //当前排名索引
		const TVecPlayerRankInfo& vecInfo //排名信息
	);

	//发送：召集帮众广播
	bool Send_CallMemberNotify( //发送给当前协议处理的客户端
		UINT8 byQuality, //品质
		const std::string& strName //名字
	);
	bool SendClt_CallMemberNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byQuality, //品质
		const std::string& strName //名字
	);
	std::string& BuildPkg_CallMemberNotify( //只组包不发送
		UINT8 byQuality, //品质
		const std::string& strName //名字
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetStateAck : public CClientFuncAck
	{
		ENGBState eState; //当前帮派战状态
		UINT32 dwRemainTime; //新帮派战剩余时间
		TVecMountainPanelInfo vecInfo; //各个灵山信息
		ENGBMountain eMountainType; //自己所在战斗信息

		SGetStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派战状态
	virtual bool OnRecv_GetState(
		shared_func<SGetStateAck>& fnAck //返回回调函数
	) = 0;

	struct SGetOwnerHistoryAck : public CClientFuncAck
	{
		TVecOwnerHistoryInfo vecInfo; //理解帮派信息

		SGetOwnerHistoryAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取历届占领帮会
	virtual bool OnRecv_GetOwnerHistory(
		ENGBMountain eMountainType, //灵山类型
		shared_func<SGetOwnerHistoryAck>& fnAck //返回回调函数
	) = 0;

	struct SEnterAck : public CClientFuncAck
	{
		ENGBEnterResult eResult; //进入结果
		ENGBMountainState eState; //灵山状态

		SEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入帮派战(进入准备场地)
	virtual bool OnRecv_Enter(
		ENGBMountain eMountainType, //灵山类型
		shared_func<SEnterAck>& fnAck //返回回调函数
	) = 0;

	struct SGateAttackPlayerAck : public CClientFuncAck
	{
		ENGBGateAttackResult eResult; //攻击返回结果

		SGateAttackPlayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：城门战攻击玩家/城门
	virtual bool OnRecv_GateAttackPlayer(
		UINT64 qwTargetRoleID, //目标唯一ID(0为城墙)
		shared_func<SGateAttackPlayerAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyPuppetAck : public CClientFuncAck
	{
		ENGBBuyPuppetResult eResult; //购买结果

		SBuyPuppetAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买傀儡
	virtual bool OnRecv_BuyPuppet(
		shared_func<SBuyPuppetAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGateInfoAck : public CClientFuncAck
	{
		ENGBResult eResult; //返回结果
		SMountainGateInfo sInfo; //城门信息

		SGetGateInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取城门战信息
	virtual bool OnRecv_GetGateInfo(
		shared_func<SGetGateInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SCaveCaptureAck : public CClientFuncAck
	{
		ENGBCaveAttackResult eResult; //返回结果

		SCaveCaptureAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：洞府战占领阵眼
	virtual bool OnRecv_CaveCapture(
		ENGBCaveCore eCaveType, //阵眼类型
		shared_func<SCaveCaptureAck>& fnAck //返回回调函数
	) = 0;

	struct SCaveAttackAck : public CClientFuncAck
	{
		ENGBCaveAttackResult eResult; //返回结果

		SCaveAttackAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：洞府战攻击他人
	virtual bool OnRecv_CaveAttack(
		UINT64 qwTargetRoleID, //目标唯一ID
		shared_func<SCaveAttackAck>& fnAck //返回回调函数
	) = 0;

	struct SCaveRestAck : public CClientFuncAck
	{
		ENGBCaveAttackResult eResult; //返回结果

		SCaveRestAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：洞府战从阵眼下阵
	virtual bool OnRecv_CaveRest(
		shared_func<SCaveRestAck>& fnAck //返回回调函数
	) = 0;

	struct SGetCaveInfoAck : public CClientFuncAck
	{
		ENGBResult eResult; //返回结果
		SCaveInfo sInfo; //洞府信息

		SGetCaveInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取洞府战信息
	virtual bool OnRecv_GetCaveInfo(
		shared_func<SGetCaveInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SClearDeadCDAck : public CClientFuncAck
	{
		ENGBClearDeadCDResult eResult; //返回类型

		SClearDeadCDAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：立即买活
	virtual bool OnRecv_ClearDeadCD(
		shared_func<SClearDeadCDAck>& fnAck //返回回调函数
	) = 0;

	struct SQuitAck : public CClientFuncAck
	{
		ENGBQuitResult eResult; //退出返回结果

		SQuitAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派战退出
	virtual bool OnRecv_Quit(
		shared_func<SQuitAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuildRankInfoAck : public CClientFuncAck
	{
		ENGBResult eResult; //返回结果
		UINT32 dwMaxCount; //最大排名数量
		UINT32 dwCurIndex; //当前排名索引
		TVecGuildRankInfo vecInfo; //排名信息

		SGetGuildRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取战功榜帮派排名信息
	virtual bool OnRecv_GetGuildRankInfo(
		UINT32 dwIndex, //排名索引
		UINT32 dwCount, //排名个数
		shared_func<SGetGuildRankInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGuildMemberRankInfoAck : public CClientFuncAck
	{
		ENGBResult eResult; //返回结果
		UINT32 dwMaxCount; //最大排名数量
		UINT32 dwCurIndex; //当前排名索引
		TVecGuildMemberRankInfo vecInfo; //排名信息

		SGetGuildMemberRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取战功榜帮派成员排名信息
	virtual bool OnRecv_GetGuildMemberRankInfo(
		UINT32 dwIndex, //排名索引
		UINT32 dwCount, //排名个数
		shared_func<SGetGuildMemberRankInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerRankInfoAck : public CClientFuncAck
	{
		ENGBResult eResult; //返回结果
		UINT32 dwMaxCount; //最大排名数量
		UINT32 dwCurIndex; //当前排名索引
		TVecPlayerRankInfo vecInfo; //排名信息

		SGetPlayerRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取战功榜个人排名信息
	virtual bool OnRecv_GetPlayerRankInfo(
		UINT32 dwIndex, //排名索引
		UINT32 dwCount, //排名个数
		shared_func<SGetPlayerRankInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SCallMemberAck : public CClientFuncAck
	{
		ENGBResult eResult; //召集结果

		SCallMemberAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：召集帮众广播
	virtual bool OnRecv_CallMember(
		shared_func<SCallMemberAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 68; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetOwnerHistory(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Enter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GateAttackPlayer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyPuppet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGateInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CaveCapture(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CaveAttack(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CaveRest(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetCaveInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ClearDeadCD(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Quit(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildRankInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGuildMemberRankInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerRankInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CallMember(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CNewGuildBattleProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NNewGuildBattleProt
