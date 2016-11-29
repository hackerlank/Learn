/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    WonderActivityProt.h
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "WonderActivityProt.h"

namespace NWonderActivityProt
{

//协议类：精彩活动
class CWonderActivityProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：领奖状态通知
	bool Send_SendTakePrizeNtf( //发送给当前协议处理的客户端
		UINT16 wActID, //活动ID
		UINT32 wCond, //条件ID
		EGainResult eRet //状态
	);
	bool SendClt_SendTakePrizeNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wActID, //活动ID
		UINT32 wCond, //条件ID
		EGainResult eRet //状态
	);
	std::string& BuildPkg_SendTakePrizeNtf( //只组包不发送
		UINT16 wActID, //活动ID
		UINT32 wCond, //条件ID
		EGainResult eRet //状态
	);

	//发送：达到条件通知
	bool Send_SendReachCondNtf( //发送给当前协议处理的客户端
		UINT16 wActID, //活动ID
		UINT32 wCond //条件ID
	);
	bool SendClt_SendReachCondNtf(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wActID, //活动ID
		UINT32 wCond //条件ID
	);
	std::string& BuildPkg_SendReachCondNtf( //只组包不发送
		UINT16 wActID, //活动ID
		UINT32 wCond //条件ID
	);

	//发送：更新七星龙珠活动信息
	bool Send_UpdateDragonBallAct( //发送给当前协议处理的客户端
		const SDragonBallAct& oDragonBallAct //七星龙珠活动信息
	);
	bool SendClt_UpdateDragonBallAct(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SDragonBallAct& oDragonBallAct //七星龙珠活动信息
	);
	std::string& BuildPkg_UpdateDragonBallAct( //只组包不发送
		const SDragonBallAct& oDragonBallAct //七星龙珠活动信息
	);

	//发送：更新七日消费活动信息
	bool Send_UpdateSevenConsumeAct( //发送给当前协议处理的客户端
		const SSevenConsumeAct& oSevenConsumeAct //七日消费活动信息
	);
	bool SendClt_UpdateSevenConsumeAct(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SSevenConsumeAct& oSevenConsumeAct //七日消费活动信息
	);
	std::string& BuildPkg_UpdateSevenConsumeAct( //只组包不发送
		const SSevenConsumeAct& oSevenConsumeAct //七日消费活动信息
	);

	//发送：同步QQ养成信息
	bool Send_SyncQQCoinInfo( //发送给当前协议处理的客户端
		const SQQCoinActInfo& oQQCoinInfo //Q养成活动信息
	);
	bool SendClt_SyncQQCoinInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SQQCoinActInfo& oQQCoinInfo //Q养成活动信息
	);
	std::string& BuildPkg_SyncQQCoinInfo( //只组包不发送
		const SQQCoinActInfo& oQQCoinInfo //Q养成活动信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetConfigTimeAck : public CClientFuncAck
	{
		STime sTimes; //时间
		EWActResult eRet; //操作结果

		SGetConfigTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得活动时间配置
	virtual bool OnRecv_GetConfigTime(
		UINT16 wWActID, //精彩活动ID
		shared_func<SGetConfigTimeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllPrizeAck : public CClientFuncAck
	{
		UINT16 wActID; //活动ID
		SWActPlayerInfo sFirstPlayer; //第一名玩家信息
		SWActPlayerInfo sSelfPlayer; //玩家自己信息
		TVecPrizeConfig vecPrizeConfig; //奖励信息
		EWActResult eRet; //操作结果

		SGetAllPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得活动所有奖励配置
	virtual bool OnRecv_GetAllPrize(
		UINT16 wWActID, //精彩活动ID
		shared_func<SGetAllPrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetActListAck : public CClientFuncAck
	{
		TVecTime vecTimes; //奖励信息
		EWActResult eRet; //操作结果

		SGetActListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得活动列表
	virtual bool OnRecv_GetActList(
		shared_func<SGetActListAck>& fnAck //返回回调函数
	) = 0;

	struct STakePrizeAck : public CClientFuncAck
	{
		UINT16 wActIDRet; //返回活动ID
		UINT32 wCondRet; //返回条件

		STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家领奖
	virtual bool OnRecv_TakePrize(
		UINT16 wActID, //精彩活动ID
		UINT32 wCond, //条件
		shared_func<STakePrizeAck>& fnAck //返回回调函数
	) = 0;

	struct SGetRoleActInfoAck : public CClientFuncAck
	{
		UINT16 wActIDRet; //活动ID
		TVecRoleStatus vecRet; //操作结果

		SGetRoleActInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家活动信息
	virtual bool OnRecv_GetRoleActInfo(
		UINT16 wActID, //活动ID
		shared_func<SGetRoleActInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetRoleAllStateAck : public CClientFuncAck
	{
		TVecRoleAllStatus vecRet; //结果

		SGetRoleAllStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：玩家在所有活动中的状态
	virtual bool OnRecv_GetRoleAllState(
		shared_func<SGetRoleAllStateAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDragonBallActAck : public CClientFuncAck
	{
		UINT8 byRet; //0活动未开启 >0活动已开启

		SGetDragonBallActAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求七星龙珠活动信息
	virtual bool OnRecv_GetDragonBallAct(
		shared_func<SGetDragonBallActAck>& fnAck //返回回调函数
	) = 0;

	struct SGetSevenConsumeActAck : public CClientFuncAck
	{
		UINT8 byRet; //0活动未开启 >0活动已开启

		SGetSevenConsumeActAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求七日消费活动信息
	virtual bool OnRecv_GetSevenConsumeAct(
		shared_func<SGetSevenConsumeActAck>& fnAck //返回回调函数
	) = 0;

	//接收：请求Q养成活动信息
	virtual void OnRecv_GetQQCoinAct(
	) = 0;

	struct SExChangeAck : public CClientFuncAck
	{
		EWActResult eResult; //结果

		SExChangeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：兑换仙石或者领取Q币
	virtual bool OnRecv_ExChange(
		UINT8 byType, //0表示Q币，1表示仙石
		shared_func<SExChangeAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 199; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetConfigTime(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllPrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetActList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_TakePrize(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRoleActInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetRoleAllState(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDragonBallAct(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetSevenConsumeAct(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetQQCoinAct(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ExChange(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CWonderActivityProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NWonderActivityProt
