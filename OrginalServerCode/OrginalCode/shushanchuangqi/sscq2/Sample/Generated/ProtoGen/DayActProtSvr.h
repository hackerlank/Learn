/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DayActProt.h
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DayActProt.h"

namespace NDayActProt
{

//协议类：活动
class CDayActProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：活动状态改变通知
	bool Send_ActChangeNotify( //发送给当前协议处理的客户端
		UINT32 dwActType, //活动id
		UINT32 dwActStatus //活动状态
	);
	bool SendClt_ActChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT32 dwActType, //活动id
		UINT32 dwActStatus //活动状态
	);
	std::string& BuildPkg_ActChangeNotify( //只组包不发送
		UINT32 dwActType, //活动id
		UINT32 dwActStatus //活动状态
	);

	//发送：蜀山基金活动改变通知
	bool Send_ShushanFoundChangeNotify( //发送给当前协议处理的客户端
		UINT16 wGrowFoundInfo, //成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wPExpFoundInfo, //修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wSilverFoundInfo, //银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wItemFoundInfo, //宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT32 dwLoginDays //玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
	);
	bool SendClt_ShushanFoundChangeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wGrowFoundInfo, //成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wPExpFoundInfo, //修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wSilverFoundInfo, //银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wItemFoundInfo, //宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT32 dwLoginDays //玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
	);
	std::string& BuildPkg_ShushanFoundChangeNotify( //只组包不发送
		UINT16 wGrowFoundInfo, //成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wPExpFoundInfo, //修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wSilverFoundInfo, //银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT16 wItemFoundInfo, //宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
		UINT32 dwLoginDays //玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetActListAck : public CClientFuncAck
	{
		TVecActInfo vecActInfo; //活动列表

		SGetActListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取活动列表
	virtual bool OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFirstRechargeStatusAck : public CClientFuncAck
	{
		UINT8 byRet; //0未充值 1已充值但未领取 2已领取

		SGetFirstRechargeStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：是否已领取首充礼包
	virtual bool OnRecv_GetFirstRechargeStatus(
		shared_func<SGetFirstRechargeStatusAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFirstRechargeAwardAck : public CClientFuncAck
	{
		UINT8 byRet; //0失败 1成功 2未充值 3已领取

		SGetFirstRechargeAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取首充礼包
	virtual bool OnRecv_GetFirstRechargeAward(
		shared_func<SGetFirstRechargeAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyShushanFoundSelfAck : public CClientFuncAck
	{
		UINT8 byRet; //0失败 1成功

		SBuyShushanFoundSelfAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：为自己购买蜀山基金
	virtual bool OnRecv_BuyShushanFoundSelf(
		UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		shared_func<SBuyShushanFoundSelfAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyShushanFoundFirendAck : public CClientFuncAck
	{
		UINT8 byRet; //0失败 1成功

		SBuyShushanFoundFirendAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：为好友购买蜀山基金
	virtual bool OnRecv_BuyShushanFoundFirend(
		UINT64 qwFriendID, //好友ID
		UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		shared_func<SBuyShushanFoundFirendAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取玩家购买及领取蜀山基金的信息
	virtual void OnRecv_GetShushanFoundInfo(
	) = 0;

	struct SGetShushanFoundAwardAck : public CClientFuncAck
	{
		UINT8 byRet; //0失败 1成功

		SGetShushanFoundAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取蜀山基金奖励
	virtual bool OnRecv_GetShushanFoundAward(
		UINT8 byType, //基金类型(1成长基金 2修为投资计划 3银币投资计划 4宝物投资计划)
		UINT8 byDay, //领取第几个(1~7)
		shared_func<SGetShushanFoundAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSecondRechargeStatusAck : public CClientFuncAck
	{
		UINT8 byRet; //0未充值 1已充值但未领取 2已领取
		UINT32 dwSecondRechargeValue; //二次充值累计金额

		SGetSecondRechargeStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取二次充值礼包状态
	virtual bool OnRecv_GetSecondRechargeStatus(
		shared_func<SGetSecondRechargeStatusAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSecondRechargeAwardAck : public CClientFuncAck
	{
		UINT8 byRet; //0失败 1成功 2未充值 3已领取

		SGetSecondRechargeAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取二次充值礼包
	virtual bool OnRecv_GetSecondRechargeAward(
		shared_func<SGetSecondRechargeAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetOpenServerTimeAck : public CClientFuncAck
	{
		UINT32 dwTime; //时间

		SGetOpenServerTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取开服时间
	virtual bool OnRecv_GetOpenServerTime(
		shared_func<SGetOpenServerTimeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 69; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetActList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFirstRechargeStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFirstRechargeAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyShushanFoundSelf(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyShushanFoundFirend(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetShushanFoundInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetShushanFoundAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSecondRechargeStatus(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSecondRechargeAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetOpenServerTime(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDayActProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDayActProt
