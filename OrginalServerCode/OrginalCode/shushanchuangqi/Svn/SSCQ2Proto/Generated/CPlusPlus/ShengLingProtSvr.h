/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ShengLingProt.h
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ShengLingProt.h"

namespace NShengLingProt
{

//协议类：圣陵协议
class CShengLingProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：玩家通关
	bool Send_Clearance( //发送给当前协议处理的客户端
	);
	bool SendClt_Clearance(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_Clearance( //只组包不发送
	);

	//发送：玩家数据推送（0点)
	bool Send_SyncData( //发送给当前协议处理的客户端
		const SShengLingInfo& sInfo //玩家数据
	);
	bool SendClt_SyncData(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SShengLingInfo& sInfo //玩家数据
	);
	std::string& BuildPkg_SyncData( //只组包不发送
		const SShengLingInfo& sInfo //玩家数据
	);

	//发送：播放特效
	bool Send_PlayEffect( //发送给当前协议处理的客户端
	);
	bool SendClt_PlayEffect(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_PlayEffect( //只组包不发送
	);

	//发送：获得奖励道具
	bool Send_GetPrizeInfo( //发送给当前协议处理的客户端
		const NItemProt::TVecItemGenInfo& vecItem //玩家物品
	);
	bool SendClt_GetPrizeInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NItemProt::TVecItemGenInfo& vecItem //玩家物品
	);
	std::string& BuildPkg_GetPrizeInfo( //只组包不发送
		const NItemProt::TVecItemGenInfo& vecItem //玩家物品
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SOnOpenAck : public CClientFuncAck
	{
		UINT8 byUseEnter; //玩家当日使用进入次数
		UINT8 byBuyEnter; //玩家购买进入次数
		UINT8 byBuyEnterToday; //玩家今天购买进入次数
		bool bContinue; //是否继续

		SOnOpenAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家打开活动面板
	virtual bool OnRecv_OnOpen(
		shared_func<SOnOpenAck>& fnAck //返回回调函数
	) = 0;

	struct SOnEnterAck : public CClientFuncAck
	{
		UINT8 byBuyEnterToday; //玩家今天购买进入次数
		SShengLingInfo sInfo; //玩家数据
		EShengLingResult eResult; //操作结果

		SOnEnterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家进入圣陵
	virtual bool OnRecv_OnEnter(
		shared_func<SOnEnterAck>& fnAck //返回回调函数
	) = 0;

	struct SDrawDiceAck : public CClientFuncAck
	{
		UINT8 byIndex; //骰子数
		UINT64 qwBattleID; //战报ID
		SPlayerInfo sInfo; //玩家数据
		EShengLingResult eResult; //操作结果

		SDrawDiceAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家摇骰子
	virtual bool OnRecv_DrawDice(
		shared_func<SDrawDiceAck>& fnAck //返回回调函数
	) = 0;

	struct SUseCardAck : public CClientFuncAck
	{
		SCard sCard; //卡片信息
		SPlayerInfo sInfo; //玩家数据
		UINT64 qwBattleID; //战报ID
		EShengLingResult eResult; //操作结果

		SUseCardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：使用卡片
	virtual bool OnRecv_UseCard(
		ECardType eCardType, //卡片类型
		UINT8 byIndex, //骰子数(转向时byIndex=0)
		shared_func<SUseCardAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyAck : public CClientFuncAck
	{
		EBuyType eBuyTypeRet; //返回购买类型
		UINT8 byBuy; //返回购买次数
		UINT8 byBuyToday; //返回今日购买次数
		UINT8 byUse; //返回当日使用次数
		EShengLingResult eResult; //操作结果

		SBuyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买
	virtual bool OnRecv_Buy(
		EBuyType eBuyType, //购买类型
		UINT8 byNum, //购买次数
		shared_func<SBuyAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		UINT8 byBit; //奖励状态(其他忽略此参数）
		EShengLingResult eResult; //操作结果

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家领奖
	virtual bool OnRecv_TakePrize(
		EGridType eGridType, //格子类型(小游戏）
		UINT8 byIndex, //三消中第几个奖励或者拼图是否一键完成(其他忽略此参数）
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SAddScoreAck : public CClientFuncAck
	{
		UINT16 wNextPwd; //下一次密码
		UINT8 byTotalStep; //剩余步数
		UINT16 wTotalScore; //总积分
		EShengLingResult eResult; //操作结果

		SAddScoreAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：三消中积分累计
	virtual bool OnRecv_AddScore(
		UINT16 wScore, //积分
		UINT8 byStep, //减少步数
		UINT16 wPassword, //密码
		shared_func<SAddScoreAck>& fnAck //返回回调函数
	) = 0;

	struct SFinishTrapGridAck : public CClientFuncAck
	{
		EShengLingResult eResult; //操作结果

		SFinishTrapGridAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家完成或者放弃小游戏
	virtual bool OnRecv_FinishTrapGrid(
		shared_func<SFinishTrapGridAck>& fnAck //返回回调函数
	) = 0;

	//接收：玩家离开圣陵
	virtual void OnRecv_Leave(
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 98; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_OnOpen(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnEnter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DrawDice(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UseCard(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Buy(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AddScore(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishTrapGrid(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Leave(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CShengLingProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NShengLingProt
