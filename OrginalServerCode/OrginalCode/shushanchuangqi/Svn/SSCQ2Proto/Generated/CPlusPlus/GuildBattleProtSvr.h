/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GuildBattleProt.h
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GuildBattleProt.h"

namespace NGuildBattleProt
{

//协议类：帮派相关协议
class CGuildBattleProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：帮派战状态通知
	bool Send_StateNotify( //发送给当前协议处理的客户端
		EGBState eState, //当前帮派战状态
		UINT8 byBattleCount, //当前已经战斗的数量
		UINT32 dwRemainTime, //当前状态剩余时间
		EGBSpot eSpotType, //自己所在据点(报名的据点或者目前被调整到的据点)
		EGBSide eSelfSide //自己所在帮派方向
	);
	bool SendClt_StateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EGBState eState, //当前帮派战状态
		UINT8 byBattleCount, //当前已经战斗的数量
		UINT32 dwRemainTime, //当前状态剩余时间
		EGBSpot eSpotType, //自己所在据点(报名的据点或者目前被调整到的据点)
		EGBSide eSelfSide //自己所在帮派方向
	);
	std::string& BuildPkg_StateNotify( //只组包不发送
		EGBState eState, //当前帮派战状态
		UINT8 byBattleCount, //当前已经战斗的数量
		UINT32 dwRemainTime, //当前状态剩余时间
		EGBSpot eSpotType, //自己所在据点(报名的据点或者目前被调整到的据点)
		EGBSide eSelfSide //自己所在帮派方向
	);

	//发送：帮派战信息通知
	bool Send_FieldInfoNotify( //发送给当前协议处理的客户端
		const SFieldInfo& sFieldInfo //战场信息
	);
	bool SendClt_FieldInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SFieldInfo& sFieldInfo //战场信息
	);
	std::string& BuildPkg_FieldInfoNotify( //只组包不发送
		const SFieldInfo& sFieldInfo //战场信息
	);

	//发送：帮派战据点信息通知
	bool Send_SpotInfoNotify( //发送给当前协议处理的客户端
		const TVecSpotInfo& vecSpotInfo //据点详细信息
	);
	bool SendClt_SpotInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecSpotInfo& vecSpotInfo //据点详细信息
	);
	std::string& BuildPkg_SpotInfoNotify( //只组包不发送
		const TVecSpotInfo& vecSpotInfo //据点详细信息
	);

	//发送：据点战斗通知
	bool Send_SpotBattleNotify( //发送给当前协议处理的客户端
		EGBSpot eType, //据点类型
		const TVecBattleData& vecBattleData //战报信息
	);
	bool SendClt_SpotBattleNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EGBSpot eType, //据点类型
		const TVecBattleData& vecBattleData //战报信息
	);
	std::string& BuildPkg_SpotBattleNotify( //只组包不发送
		EGBSpot eType, //据点类型
		const TVecBattleData& vecBattleData //战报信息
	);

	//发送：帮派战技能信息通知
	bool Send_SkillInfoNotify( //发送给当前协议处理的客户端
		const TVecSkillInfo& vecSkillInfo //具体已购买技能
	);
	bool SendClt_SkillInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecSkillInfo& vecSkillInfo //具体已购买技能
	);
	std::string& BuildPkg_SkillInfoNotify( //只组包不发送
		const TVecSkillInfo& vecSkillInfo //具体已购买技能
	);

	//发送：更新帮派战小面板信息
	bool Send_PanelInfoNotify( //发送给当前协议处理的客户端
		UINT32 dwSelfScore, //我的积分
		UINT32 dwGuildScore, //帮派积分
		UINT32 dwGuildRank //帮派排名
	);
	bool SendClt_PanelInfoNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwSelfScore, //我的积分
		UINT32 dwGuildScore, //帮派积分
		UINT32 dwGuildRank //帮派排名
	);
	std::string& BuildPkg_PanelInfoNotify( //只组包不发送
		UINT32 dwSelfScore, //我的积分
		UINT32 dwGuildScore, //帮派积分
		UINT32 dwGuildRank //帮派排名
	);

	//发送：报名还没进入的通知进入
	bool Send_SignupEnterNotify( //发送给当前协议处理的客户端
	);
	bool SendClt_SignupEnterNotify(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_SignupEnterNotify( //只组包不发送
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
	struct SSignUpAck : public CClientFuncAck
	{
		EGBSignUpResult eResult; //报名返回结果

		SSignUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派战报名
	virtual bool OnRecv_SignUp(
		EGBSpot eSpotType, //据点类型
		shared_func<SSignUpAck>& fnAck //返回回调函数
	) = 0;

	struct SEnterAck : public CClientFuncAck
	{
		EGBEnterResult eResult; //报名返回结果

		SEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：进入帮派战(进入准备场地)
	virtual bool OnRecv_Enter(
		shared_func<SEnterAck>& fnAck //返回回调函数
	) = 0;

	struct SQuitAck : public CClientFuncAck
	{
		EGBQuitResult eResult; //退出返回结果

		SQuitAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派战退出
	virtual bool OnRecv_Quit(
		shared_func<SQuitAck>& fnAck //返回回调函数
	) = 0;

	struct SAdjustMemberAck : public CClientFuncAck
	{
		EGBAdjustResult eResult; //调整返回结果

		SAdjustMemberAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派成员调整
	virtual bool OnRecv_AdjustMember(
		UINT64 qwRoleID, //成员角色ID
		EGBSpot eSpotType, //目标据点类型
		UINT8 byIndex, //新目标对应位置(从1开始)
		shared_func<SAdjustMemberAck>& fnAck //返回回调函数
	) = 0;

	struct SGetStateAck : public CClientFuncAck
	{
		EGBState eState; //当前帮派战状态
		UINT8 byBattleCount; //当前已经战斗的数量
		UINT32 dwRemainTime; //当前状态剩余时间
		EGBSpot eSpotType; //自己所在据点(不为None也可能在准备地图中)
		bool bGuildJoined; //自己所在帮派是否已经参加
		EGBSide eSelfSide; //自己所在帮派方向

		SGetStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派战状态
	virtual bool OnRecv_GetState(
		shared_func<SGetStateAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFieldInfoAck : public CClientFuncAck
	{
		EGBResult eResult; //返回结果
		TVecFieldInfo vecFieldInfo; //帮派战场信息

		SGetFieldInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派战场信息
	virtual bool OnRecv_GetFieldInfo(
		shared_func<SGetFieldInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSpotInfoAck : public CClientFuncAck
	{
		EGBResult eResult; //返回结果
		TVecSpotInfo vecSpotInfo; //据点详细信息（数量为0/1）

		SGetSpotInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派据点信息
	virtual bool OnRecv_GetSpotInfo(
		EGBSpot eType, //据点类型
		shared_func<SGetSpotInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSpotBattleAck : public CClientFuncAck
	{
		EGBBattleResult eResult; //战报获取结果
		TVecBattleData vecBattleData; //战报信息

		SGetSpotBattleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：据点战报获取
	virtual bool OnRecv_GetSpotBattle(
		EGBSpot eType, //据点类型
		shared_func<SGetSpotBattleAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSkillInfoAck : public CClientFuncAck
	{
		EGBSkillResult eResult; //购买结果
		TVecSkillInfo vecSkillInfo; //具体已购买技能

		SGetSkillInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派战技能信息获取
	virtual bool OnRecv_GetSkillInfo(
		shared_func<SGetSkillInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SBuySkillAck : public CClientFuncAck
	{
		EGBSkillResult eResult; //购买结果

		SBuySkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：帮派购买技能结果
	virtual bool OnRecv_BuySkill(
		EGBSkill eType, //购买的技能类型
		shared_func<SBuySkillAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPanelInfoAck : public CClientFuncAck
	{
		UINT32 dwSelfScore; //我的积分
		UINT32 dwGuildScore; //帮派积分
		UINT32 dwGuildRank; //帮派排名

		SGetPanelInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取帮派战小面板信息
	virtual bool OnRecv_GetPanelInfo(
		shared_func<SGetPanelInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SCallMemberAck : public CClientFuncAck
	{
		EGBResult eResult; //召集结果

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

	virtual UINT8 GetProtID() const override { return 76; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_SignUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Enter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Quit(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AdjustMember(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFieldInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSpotInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSpotBattle(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSkillInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuySkill(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPanelInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CallMember(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGuildBattleProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGuildBattleProt
