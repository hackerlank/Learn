/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MiscProt.h
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "MiscProt.h"

namespace NMiscProt
{

//协议类：不好归类的小协议
class CMiscProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：聊天信息通知
	bool Send_IndulgeTimeNotify( //发送给当前协议处理的客户端
		UINT32 dwIndulgeTime //防沉迷时间(秒)
	);
	bool SendClt_IndulgeTimeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwIndulgeTime //防沉迷时间(秒)
	);
	std::string& BuildPkg_IndulgeTimeNotify( //只组包不发送
		UINT32 dwIndulgeTime //防沉迷时间(秒)
	);

	//发送：聊天信息通知
	bool Send_IndulgeNextLoginTime( //发送给当前协议处理的客户端
		UINT32 dwTime //可以登陆时间(秒)
	);
	bool SendClt_IndulgeNextLoginTime(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //可以登陆时间(秒)
	);
	std::string& BuildPkg_IndulgeNextLoginTime( //只组包不发送
		UINT32 dwTime //可以登陆时间(秒)
	);

	//发送：Buffer中的体力
	bool Send_GetActionBuffNotify( //发送给当前协议处理的客户端
		UINT32 dwValue, //Buffer中的体力
		UINT32 TakeTime //最近领取时间
	);
	bool SendClt_GetActionBuffNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwValue, //Buffer中的体力
		UINT32 TakeTime //最近领取时间
	);
	std::string& BuildPkg_GetActionBuffNotify( //只组包不发送
		UINT32 dwValue, //Buffer中的体力
		UINT32 TakeTime //最近领取时间
	);

	//发送：通知活动开始
	bool Send_OnBegin( //发送给当前协议处理的客户端
	);
	bool SendClt_OnBegin(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_OnBegin( //只组包不发送
	);

	//发送：宝箱下一波公告
	bool Send_SendNotice( //发送给当前协议处理的客户端
		UINT8 byRount, //剩余波数
		UINT8 byMaxRount //最大波数
	);
	bool SendClt_SendNotice(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byRount, //剩余波数
		UINT8 byMaxRount //最大波数
	);
	std::string& BuildPkg_SendNotice( //只组包不发送
		UINT8 byRount, //剩余波数
		UINT8 byMaxRount //最大波数
	);

	//发送：通知倒计时
	bool Send_OnCountDown( //发送给当前协议处理的客户端
		UINT32 dwTime //活动倒计时时间
	);
	bool SendClt_OnCountDown(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTime //活动倒计时时间
	);
	std::string& BuildPkg_OnCountDown( //只组包不发送
		UINT32 dwTime //活动倒计时时间
	);

	//发送：通知活动结束
	bool Send_OnEnd( //发送给当前协议处理的客户端
	);
	bool SendClt_OnEnd(const UINT64* pUsrID, UINT16 wCnt //发送给多个客户端
	);
	std::string& BuildPkg_OnEnd( //只组包不发送
	);

	//发送：通知宝箱活动剩余轮次
	bool Send_SyncChestInfo( //发送给当前协议处理的客户端
		const SGodChestInfo& sInfo //宝箱信息
	);
	bool SendClt_SyncChestInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SGodChestInfo& sInfo //宝箱信息
	);
	std::string& BuildPkg_SyncChestInfo( //只组包不发送
		const SGodChestInfo& sInfo //宝箱信息
	);

	//发送：通知宝箱活动剩余轮次
	bool Send_SyncLotteryInfo( //发送给当前协议处理的客户端
		UINT32 dwLottery, //抽奖券
		const TVecLotteryInfo& vecTotalInfo, //总的抽奖信息
		const TVecLotteryInfo& vecSelfInfo //自己抽奖信息
	);
	bool SendClt_SyncLotteryInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwLottery, //抽奖券
		const TVecLotteryInfo& vecTotalInfo, //总的抽奖信息
		const TVecLotteryInfo& vecSelfInfo //自己抽奖信息
	);
	std::string& BuildPkg_SyncLotteryInfo( //只组包不发送
		UINT32 dwLottery, //抽奖券
		const TVecLotteryInfo& vecTotalInfo, //总的抽奖信息
		const TVecLotteryInfo& vecSelfInfo //自己抽奖信息
	);

	//发送：同步今日冲值仙石总数
	bool Send_SyncRechargeToday( //发送给当前协议处理的客户端
		UINT32 dwTotalRechargeToday //仙石
	);
	bool SendClt_SyncRechargeToday(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwTotalRechargeToday //仙石
	);
	std::string& BuildPkg_SyncRechargeToday( //只组包不发送
		UINT32 dwTotalRechargeToday //仙石
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：设置防沉迷状态
	virtual void OnRecv_SetIndulge(
		bool bIndulge //设置防沉迷状态
	) = 0;

	//接收：设置防沉迷收益率
	virtual void OnRecv_SetIndulgeRate(
		UINT32 dwIndulgeRate //设置防沉迷收益率
	) = 0;

	struct SBuyActionAck : public CClientFuncAck
	{
		UINT32 dwRet; //结果
		UINT32 dwCount; //购买体力次数
		UINT32 dwPrice; //购买体力价格

		SBuyActionAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买体力
	virtual bool OnRecv_BuyAction(
		shared_func<SBuyActionAck>& fnAck //返回回调函数
	) = 0;

	struct SGetBuyActionCountAck : public CClientFuncAck
	{
		UINT32 dwCount; //购买体力次数
		UINT32 dwPrice; //购买体力价格
		UINT32 dwAction; //体力

		SGetBuyActionCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取购买体力次数
	virtual bool OnRecv_GetBuyActionCount(
		shared_func<SGetBuyActionCountAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取体力buff数值
	virtual void OnRecv_GetActionBuff(
	) = 0;

	//接收：发送udplog
	virtual void OnRecv_SendUdpLog(
		const std::string& strParam1, //参数1
		const std::string& strParam2 //参数2
	) = 0;

	struct SGetMoneyListAck : public CClientFuncAck
	{
		NProtoCommon::TVecMoneyCount vecMoneyCount; //货币列表（货币数量为0的不发送）

		SGetMoneyListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取货币基础数值
	virtual bool OnRecv_GetMoneyList(
		shared_func<SGetMoneyListAck>& fnAck //返回回调函数
	) = 0;

	//接收：领取体力buff
	virtual void OnRecv_TakeActionBuff(
	) = 0;

	//接收：客户端黑屏Log
	virtual void OnRecv_ClientBlankScreenLog(
		const std::string& strParam1 //参数1
	) = 0;

	//接收：天赐宝箱
	virtual void OnRecv_OnEnter(
	) = 0;

	//接收：获得回合数和活动状态
	virtual void OnRecv_GetRount(
	) = 0;

	struct SDrawAck : public CClientFuncAck
	{
		UINT16 wLotteryID; //抽奖号码
		ELotteryRes eResult; //操作结果

		SDrawAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家抽奖
	virtual bool OnRecv_Draw(
		shared_func<SDrawAck>& fnAck //返回回调函数
	) = 0;

	//接收：客户端通知动画播放完毕
	virtual void OnRecv_DrawRet(
	) = 0;

	//接收：同步客户端玩家抽奖
	virtual void OnRecv_SendLottery(
		UINT32 dwTotalNum, //总的抽奖信息条数
		UINT32 dwSelfNum //自己的抽奖信息条数
	) = 0;

	struct SGetEveryDayRechargeAwardAck : public CClientFuncAck
	{
		EEveryDayReChargeAward eResult; //消息返回

		SGetEveryDayRechargeAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取每日冲值奖励
	virtual bool OnRecv_GetEveryDayRechargeAward(
		shared_func<SGetEveryDayRechargeAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetEveryDayRechargeAck : public CClientFuncAck
	{
		UINT32 dwTotalRechargeToday; //仙石

		SGetEveryDayRechargeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取每日冲值金额
	virtual bool OnRecv_GetEveryDayRecharge(
		shared_func<SGetEveryDayRechargeAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyFenbaoyanAck : public CClientFuncAck
	{
		EMiscOptRes eRet; //购买结果

		SBuyFenbaoyanAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：分宝岩购买活动
	virtual bool OnRecv_BuyFenbaoyan(
		UINT16 wNum, //购买数量
		shared_func<SBuyFenbaoyanAck>& fnAck //返回回调函数
	) = 0;

	struct SFenbaoyanTimeAck : public CClientFuncAck
	{
		UINT32 dwBegin; //开始时间
		UINT32 dwEnd; //结束时间

		SFenbaoyanTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：分宝岩购买活动时间
	virtual bool OnRecv_FenbaoyanTime(
		shared_func<SFenbaoyanTimeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 72; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_SetIndulge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetIndulgeRate(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyAction(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetBuyActionCount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetActionBuff(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendUdpLog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetMoneyList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakeActionBuff(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ClientBlankScreenLog(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OnEnter(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_Draw(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DrawRet(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SendLottery(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetEveryDayRechargeAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetEveryDayRecharge(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyFenbaoyan(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FenbaoyanTime(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CMiscProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NMiscProt
