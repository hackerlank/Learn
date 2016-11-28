/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    VIPProt.h
//  Purpose:      VIP特权相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "VIPProt.h"

namespace NVIPProt
{

//协议类：VIP特权相关协议
class CVIPProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：个人VIP特权信息
	bool Send_SelfVIPInfo( //发送给当前协议处理的客户端
		const SVIPData& stVIPData //VIP特权信息
	);
	bool SendClt_SelfVIPInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SVIPData& stVIPData //VIP特权信息
	);
	std::string& BuildPkg_SelfVIPInfo( //只组包不发送
		const SVIPData& stVIPData //VIP特权信息
	);

	//发送：月卡过期通知消息
	bool Send_UpdateMonthCardOverdue( //发送给当前协议处理的客户端
		UINT8 byVal //0未过期 >0已过期
	);
	bool SendClt_UpdateMonthCardOverdue(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT8 byVal //0未过期 >0已过期
	);
	std::string& BuildPkg_UpdateMonthCardOverdue( //只组包不发送
		UINT8 byVal //0未过期 >0已过期
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：请求个人VIP特权信息
	virtual void OnRecv_GetVIPInfo(
	) = 0;

	struct SOpenSelfVIPAck : public CClientFuncAck
	{
		EVIPResult eResult; //操作结果

		SOpenSelfVIPAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求个人VIP特权
	virtual bool OnRecv_OpenSelfVIP(
		UINT8 byType, //VIP特权类型
		shared_func<SOpenSelfVIPAck>& fnAck //返回回调函数
	) = 0;

	struct SOpenOtherVIPAck : public CClientFuncAck
	{
		EVIPResult eResult; //操作结果
		UINT64 qwRoleID; //好友玩家ID

		SOpenOtherVIPAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求开启好友VIP特权
	virtual bool OnRecv_OpenOtherVIP(
		UINT8 byType, //VIP特权类型
		UINT64 qwRoleID, //好友玩家ID
		UINT64 qwRoleID2, //好友玩家ID(匹配验证)
		shared_func<SOpenOtherVIPAck>& fnAck //返回回调函数
	) = 0;

	struct SOpenSelfMonthCardAck : public CClientFuncAck
	{
		EVIPResult eResult; //操作结果

		SOpenSelfMonthCardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求开启个人月卡
	virtual bool OnRecv_OpenSelfMonthCard(
		shared_func<SOpenSelfMonthCardAck>& fnAck //返回回调函数
	) = 0;

	struct SOpenOtherMonthCardAck : public CClientFuncAck
	{
		EVIPResult eResult; //操作结果
		UINT64 qwRoleID; //好友玩家ID

		SOpenOtherMonthCardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求开启好友月卡
	virtual bool OnRecv_OpenOtherMonthCard(
		UINT64 qwRoleID, //好友玩家ID
		shared_func<SOpenOtherMonthCardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDayPackAwardAck : public CClientFuncAck
	{
		EVIPResult eResult; //操作结果
		UINT32 dwDayPack; //VIP特权每日礼包领取状态(低15位,按位取)

		SGetDayPackAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取VIP特权每日礼包
	virtual bool OnRecv_GetDayPackAward(
		shared_func<SGetDayPackAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetVIPLevelAwardAck : public CClientFuncAck
	{
		EVIPResult eResult; //操作结果
		UINT32 dwLvlAward; //VIP等级奖励领取状态(低15位,按位取)

		SGetVIPLevelAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取VIP特权等级奖励
	virtual bool OnRecv_GetVIPLevelAward(
		UINT8 byLevel, //VIP等级
		shared_func<SGetVIPLevelAwardAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 65; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetVIPInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenSelfVIP(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenOtherVIP(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenSelfMonthCard(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenOtherMonthCard(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDayPackAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetVIPLevelAward(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CVIPProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NVIPProt
