/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LevelPrize.h
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LevelPrize.h"

namespace NLevelPrize
{

//协议类：等级奖励
class CLevelPrizeSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：等级奖励活动状态通知
	bool Send_LevelPrizeNotify( //发送给当前协议处理的客户端
		UINT16 wActID, //活动Id
		EActState eStatus //活动状态
	);
	bool SendClt_LevelPrizeNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wActID, //活动Id
		EActState eStatus //活动状态
	);
	std::string& BuildPkg_LevelPrizeNotify( //只组包不发送
		UINT16 wActID, //活动Id
		EActState eStatus //活动状态
	);

	//发送：可领状态通知
	bool Send_SendReachCondNfy( //发送给当前协议处理的客户端
		UINT16 wActID, //活动Id
		UINT8 byIndex //第几个奖励
	);
	bool SendClt_SendReachCondNfy(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wActID, //活动Id
		UINT8 byIndex //第几个奖励
	);
	std::string& BuildPkg_SendReachCondNfy( //只组包不发送
		UINT16 wActID, //活动Id
		UINT8 byIndex //第几个奖励
	);

	//发送：QQAlarm奖励状态通知
	bool Send_SendStateForQQAlarm( //发送给当前协议处理的客户端
		UINT16 wActID, //活动ID
		ELevelActStatus eRet //结果
	);
	bool SendClt_SendStateForQQAlarm(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wActID, //活动ID
		ELevelActStatus eRet //结果
	);
	std::string& BuildPkg_SendStateForQQAlarm( //只组包不发送
		UINT16 wActID, //活动ID
		ELevelActStatus eRet //结果
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetPrizeInfoAck : public CClientFuncAck
	{
		UINT16 wActID; //活动ID
		TVecPrize vecPrize; //结果

		SGetPrizeInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取奖励
	virtual bool OnRecv_GetPrizeInfo(
		UINT16 wActID, //活动Id
		shared_func<SGetPrizeInfoAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		UINT16 wActID; //活动Id
		UINT8 byIndex; //活动Id
		ELevelActStatus eRet; //领取结果

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取奖励
	virtual bool OnRecv_TakePrize(
		UINT16 wActID, //活动Id
		UINT8 byIndex, //第几个奖励
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetRoleStateAck : public CClientFuncAck
	{
		NWonderActivityProt::TVecRoleAllStatus vecRet; //结果

		SGetRoleStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家在个人服活动中的状态
	virtual bool OnRecv_GetRoleState(
		shared_func<SGetRoleStateAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeForQQAlarmAck : public CClientFuncAck
	{
		ELevelActStatus eRet; //领取结果

		STakePrizeForQQAlarmAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：QQAlarm获取奖励
	virtual bool OnRecv_TakePrizeForQQAlarm(
		UINT16 wActID, //活动Id
		shared_func<STakePrizeForQQAlarmAck>& fnAck //返回回调函数
	) = 0;

	//接收：QQAlarm获取奖励状态
	virtual void OnRecv_GetStateForQQAlarm(
		UINT16 wActID //活动Id
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 121; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetPrizeInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRoleState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrizeForQQAlarm(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetStateForQQAlarm(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLevelPrizeSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLevelPrize
