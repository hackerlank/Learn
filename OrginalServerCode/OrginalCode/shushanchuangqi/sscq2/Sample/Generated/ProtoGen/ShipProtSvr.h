/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ShipProt.h
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ShipProt.h"

namespace NShipProt
{

//协议类：元江金船协议
class CShipProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：发送玩家信息
	bool Send_SendView( //发送给当前协议处理的客户端
		const PlayerSelfView& stViewInfo //玩家信息
	);
	bool SendClt_SendView(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const PlayerSelfView& stViewInfo //玩家信息
	);
	std::string& BuildPkg_SendView( //只组包不发送
		const PlayerSelfView& stViewInfo //玩家信息
	);

	//发送：发送船只增加消息
	bool Send_UpDateShipAdd( //发送给当前协议处理的客户端
		const PlayerShipForList& stShipInfo //船只信息
	);
	bool SendClt_UpDateShipAdd(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const PlayerShipForList& stShipInfo //船只信息
	);
	std::string& BuildPkg_UpDateShipAdd( //只组包不发送
		const PlayerShipForList& stShipInfo //船只信息
	);

	//发送：发送船只删除消息
	bool Send_UpDateShipDel( //发送给当前协议处理的客户端
		UINT64 qwInsID //金船唯一ID
	);
	bool SendClt_UpDateShipDel(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwInsID //金船唯一ID
	);
	std::string& BuildPkg_UpDateShipDel( //只组包不发送
		UINT64 qwInsID //金船唯一ID
	);

	//发送：发送玩家战报信息
	bool Send_SendRePort( //发送给当前协议处理的客户端
		const TVecShipReportForClient& vecReportInfo //玩家战报信息
	);
	bool SendClt_SendRePort(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecShipReportForClient& vecReportInfo //玩家战报信息
	);
	std::string& BuildPkg_SendRePort( //只组包不发送
		const TVecShipReportForClient& vecReportInfo //玩家战报信息
	);

	//发送：发送记录增加消息
	bool Send_UpDateShipReportAdd( //发送给当前协议处理的客户端
		const ShipReportForClient& stReport //记录信息
	);
	bool SendClt_UpDateShipReportAdd(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const ShipReportForClient& stReport //记录信息
	);
	std::string& BuildPkg_UpDateShipReportAdd( //只组包不发送
		const ShipReportForClient& stReport //记录信息
	);

	//发送：邀请别人的回复
	bool Send_InviteAnswer( //发送给当前协议处理的客户端
		UINT64 qwDefense, //护卫者ID
		const std::string& strName, //护卫者的名字
		UINT8 byColor, //护卫者的颜色
		EShipResult eResult //操作结果
	);
	bool SendClt_InviteAnswer(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwDefense, //护卫者ID
		const std::string& strName, //护卫者的名字
		UINT8 byColor, //护卫者的颜色
		EShipResult eResult //操作结果
	);
	std::string& BuildPkg_InviteAnswer( //只组包不发送
		UINT64 qwDefense, //护卫者ID
		const std::string& strName, //护卫者的名字
		UINT8 byColor, //护卫者的颜色
		EShipResult eResult //操作结果
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：获取自己显示信息
	virtual void OnRecv_GetShipSelfView(
	) = 0;

	struct SGetShipListAck : public CClientFuncAck
	{
		TVecPlayerShipForList vecShip; //获取结果

		SGetShipListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取所有金船显示信息
	virtual bool OnRecv_GetShipList(
		shared_func<SGetShipListAck>& fnAck //返回回调函数
	) = 0;

	//接收：不再关注列表
	virtual void OnRecv_DelList(
	) = 0;

	struct SGetShipInfoAck : public CClientFuncAck
	{
		EShipResult eResult; //获取结果
		PlayerShipForClient stShipInfo; //金船信息

		SGetShipInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取某条船的信息
	virtual bool OnRecv_GetShipInfo(
		UINT64 qwInsID, //金船唯一ID
		shared_func<SGetShipInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：获取历史信息
	virtual void OnRecv_GetShipReport(
	) = 0;

	struct SOpenShipAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SOpenShipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：雇佣船只,开始运船
	virtual bool OnRecv_OpenShip(
		shared_func<SOpenShipAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyOpenShipTimesAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SBuyOpenShipTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买运船次数
	virtual bool OnRecv_BuyOpenShipTimes(
		shared_func<SBuyOpenShipTimesAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyRoBShipTimesAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SBuyRoBShipTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买抢劫次数
	virtual bool OnRecv_BuyRoBShipTimes(
		shared_func<SBuyRoBShipTimesAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyReflushShipTimesAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SBuyReflushShipTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买刷新次数
	virtual bool OnRecv_BuyReflushShipTimes(
		shared_func<SBuyReflushShipTimesAck>& fnAck //返回回调函数
	) = 0;

	struct SReFlushShipAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果
		UINT16 wShipId; //金船模板

		SReFlushShipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：刷新船只
	virtual bool OnRecv_ReFlushShip(
		UINT8 byVip, //0,表示非vip ,非0表示vip
		shared_func<SReFlushShipAck>& fnAck //返回回调函数
	) = 0;

	struct SInViteFriendAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SInViteFriendAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：邀请护送船只
	virtual bool OnRecv_InViteFriend(
		UINT64 qwFriend, //好友
		shared_func<SInViteFriendAck>& fnAck //返回回调函数
	) = 0;

	struct SInViteOtherAgreeAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SInViteOtherAgreeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：回应邀请护送船只
	virtual bool OnRecv_InViteOtherAgree(
		UINT8 bySuc, //0,同意，1拒绝
		UINT64 qwFriend, //好友
		UINT32 dwCode, //验证码
		shared_func<SInViteOtherAgreeAck>& fnAck //返回回调函数
	) = 0;

	struct SFireDefenseAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SFireDefenseAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：船主踢出护送者
	virtual bool OnRecv_FireDefense(
		UINT64 qwFriend, //好友
		shared_func<SFireDefenseAck>& fnAck //返回回调函数
	) = 0;

	struct SDoRoBShipAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果
		UINT8 bySuc; //0,失败，1胜利

		SDoRoBShipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：打劫船只
	virtual bool OnRecv_DoRoBShip(
		UINT64 qwInsID, //金船唯一ID
		shared_func<SDoRoBShipAck>& fnAck //返回回调函数
	) = 0;

	struct SDoGrapShipAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果
		UINT8 bySuc; //0,失败，1胜利

		SDoGrapShipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：返抢
	virtual bool OnRecv_DoGrapShip(
		UINT64 qwShipID, //金船唯一ID
		UINT64 qwRoBID, //打劫者ID
		shared_func<SDoGrapShipAck>& fnAck //返回回调函数
	) = 0;

	struct SFinishShipOneKeyAck : public CClientFuncAck
	{
		EShipResult eResult; //操作结果

		SFinishShipOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：一键完成运送
	virtual bool OnRecv_FinishShipOneKey(
		shared_func<SFinishShipOneKeyAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 84; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetShipSelfView(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetShipList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DelList(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetShipInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetShipReport(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_OpenShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyOpenShipTimes(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyRoBShipTimes(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyReflushShipTimes(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReFlushShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InViteFriend(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_InViteOtherAgree(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FireDefense(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DoRoBShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DoGrapShip(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_FinishShipOneKey(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CShipProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NShipProt
