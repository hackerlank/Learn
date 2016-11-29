/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ShushanBattleProt.h
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ShushanBattleProt.h"

namespace NShushanBattleProt
{

//协议类：蜀山论剑相关协议
class CShushanBattleProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：蜀山论剑准备/开始/结束信息
	bool Send_BattleStartInfo( //发送给当前协议处理的客户端
		UINT8 byStatus, //状态=>0:准备 1:开始 2:结束
		UINT32 dwTimeLeft //byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
	);
	bool SendClt_BattleStartInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byStatus, //状态=>0:准备 1:开始 2:结束
		UINT32 dwTimeLeft //byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
	);
	std::string& BuildPkg_BattleStartInfo( //只组包不发送
		UINT8 byStatus, //状态=>0:准备 1:开始 2:结束
		UINT32 dwTimeLeft //byStatus为0:距离开始的剩余时间;byStatus为1:距离结束的剩余时间;byStatus为2:距离下一次开始的剩余时间
	);

	//发送：蜀山论剑玩家的配对信息
	bool Send_PlayerPairInfo( //发送给当前协议处理的客户端
		const SSSBattlePairInfo& stPairInfo //玩家的配对信息
	);
	bool SendClt_PlayerPairInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SSSBattlePairInfo& stPairInfo //玩家的配对信息
	);
	std::string& BuildPkg_PlayerPairInfo( //只组包不发送
		const SSSBattlePairInfo& stPairInfo //玩家的配对信息
	);

	//发送：广播连杀王玩家信息
	bool Send_TopKiller( //发送给当前协议处理的客户端
		const std::string& strName, //玩家名字
		UINT8 byTopStreak //最高连杀数
	);
	bool SendClt_TopKiller(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const std::string& strName, //玩家名字
		UINT8 byTopStreak //最高连杀数
	);
	std::string& BuildPkg_TopKiller( //只组包不发送
		const std::string& strName, //玩家名字
		UINT8 byTopStreak //最高连杀数
	);

	//发送：广播荣誉王玩家信息
	bool Send_HonorKinger( //发送给当前协议处理的客户端
		const std::string& strName, //玩家名字
		UINT16 wMaxHonor //最高荣誉值
	);
	bool SendClt_HonorKinger(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const std::string& strName, //玩家名字
		UINT16 wMaxHonor //最高荣誉值
	);
	std::string& BuildPkg_HonorKinger( //只组包不发送
		const std::string& strName, //玩家名字
		UINT16 wMaxHonor //最高荣誉值
	);

	//发送：蜀山论剑玩家的战报信息
	bool Send_BattleReportInfo( //发送给当前协议处理的客户端
		UINT8 byType, //0表示个人战报 1表示全部
		const TVecSSBattleReport& vecReport //玩家的战斗信息
	);
	bool SendClt_BattleReportInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byType, //0表示个人战报 1表示全部
		const TVecSSBattleReport& vecReport //玩家的战斗信息
	);
	std::string& BuildPkg_BattleReportInfo( //只组包不发送
		UINT8 byType, //0表示个人战报 1表示全部
		const TVecSSBattleReport& vecReport //玩家的战斗信息
	);

	//发送：蜀山论剑玩家使用技能信息
	bool Send_UseSkillInfo( //发送给当前协议处理的客户端
		const SSSBattleUseSkill& stUseSkill //使用技能信息
	);
	bool SendClt_UseSkillInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SSSBattleUseSkill& stUseSkill //使用技能信息
	);
	std::string& BuildPkg_UseSkillInfo( //只组包不发送
		const SSSBattleUseSkill& stUseSkill //使用技能信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：蜀山论剑准备/开始/结束信息
	virtual void OnRecv_GetBattleStartInfo(
	) = 0;

	//接收：请求蜀山论剑玩家的配对信息
	virtual void OnRecv_GetPlayerPairInfo(
	) = 0;

	//接收：请求连杀王、荣誉王信息
	virtual void OnRecv_GetFirstPlayer(
	) = 0;

	struct SPlayerEnterAck : public CClientFuncAck
	{
		ESSBattleResult eResult; //请求参加蜀山论剑返回

		SPlayerEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：参加蜀山论剑活动
	virtual bool OnRecv_PlayerEnter(
		shared_func<SPlayerEnterAck>& fnAck //返回回调函数
	) = 0;

	struct SPlayerLeaveAck : public CClientFuncAck
	{
		ESSBattleResult eResult; //请求退出蜀山论剑返回

		SPlayerLeaveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：退出蜀山论剑活动
	virtual bool OnRecv_PlayerLeave(
		shared_func<SPlayerLeaveAck>& fnAck //返回回调函数
	) = 0;

	struct SUseSkillAck : public CClientFuncAck
	{
		UINT8 bySkillID; //技能ID
		ESSBattleResult eResult; //请求使用蜀山论剑技能返回

		SUseSkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：使用蜀山论剑技能
	virtual bool OnRecv_UseSkill(
		UINT8 bySkillID, //技能ID
		shared_func<SUseSkillAck>& fnAck //返回回调函数
	) = 0;

	struct SBuySkillAck : public CClientFuncAck
	{
		UINT8 byFlag; //购买类型:0霸气 1怒气
		ESSBattleResult eResult; //购买蜀山论剑霸气or怒气返回

		SBuySkillAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买蜀山论剑霸气or怒气
	virtual bool OnRecv_BuySkill(
		UINT8 byFlag, //购买类型:0霸气 1怒气
		shared_func<SBuySkillAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 66; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetBattleStartInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerPairInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFirstPlayer(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlayerEnter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_PlayerLeave(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UseSkill(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuySkill(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CShushanBattleProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NShushanBattleProt
