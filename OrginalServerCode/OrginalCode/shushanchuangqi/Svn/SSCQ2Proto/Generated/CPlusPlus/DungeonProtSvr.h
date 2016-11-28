/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DungeonProt.h
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "DungeonProt.h"

namespace NDungeonProt
{

//协议类：副本相关协议
class CDungeonProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：扫荡更新通知
	bool Send_SweepingUpdateNotify( //发送给当前协议处理的客户端
		const NItemProt::TVecItemGenInfo& vecItem, //获得物品
		const NItemProt::TVecResource& vecResSource, //获得资源
		UINT16 wCurrCount, //当前次数
		UINT32 dwSweepEndTime //扫荡结束时间
	);
	bool SendClt_SweepingUpdateNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const NItemProt::TVecItemGenInfo& vecItem, //获得物品
		const NItemProt::TVecResource& vecResSource, //获得资源
		UINT16 wCurrCount, //当前次数
		UINT32 dwSweepEndTime //扫荡结束时间
	);
	std::string& BuildPkg_SweepingUpdateNotify( //只组包不发送
		const NItemProt::TVecItemGenInfo& vecItem, //获得物品
		const NItemProt::TVecResource& vecResSource, //获得资源
		UINT16 wCurrCount, //当前次数
		UINT32 dwSweepEndTime //扫荡结束时间
	);

	//发送：扫荡结束通知
	bool Send_SweepingEndNotify( //发送给当前协议处理的客户端
		EDungeonResult eResult //服务器返回结果
	);
	bool SendClt_SweepingEndNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EDungeonResult eResult //服务器返回结果
	);
	std::string& BuildPkg_SweepingEndNotify( //只组包不发送
		EDungeonResult eResult //服务器返回结果
	);

	//发送：副本地图怪物采集物索引通知
	bool Send_DungeonMapIdxNotify( //发送给当前协议处理的客户端
		const TVecUINT8& vecIdx //索引ID
	);
	bool SendClt_DungeonMapIdxNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TVecUINT8& vecIdx //索引ID
	);
	std::string& BuildPkg_DungeonMapIdxNotify( //只组包不发送
		const TVecUINT8& vecIdx //索引ID
	);

	//发送：通知通关副本领奖
	bool Send_NotifyDgnAward( //发送给当前协议处理的客户端
		UINT64 qwDgnId, //副本唯一实例
		UINT16 wDgnType, //副本类型
		UINT64 qwLastBattleID, //最后战报
		UINT8 byStar, //战斗评级
		const NItemProt::TVecItemGenInfo& vecItem, //获得物品
		const NItemProt::TVecResource& vecResSource //获得资源
	);
	bool SendClt_NotifyDgnAward(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT64 qwDgnId, //副本唯一实例
		UINT16 wDgnType, //副本类型
		UINT64 qwLastBattleID, //最后战报
		UINT8 byStar, //战斗评级
		const NItemProt::TVecItemGenInfo& vecItem, //获得物品
		const NItemProt::TVecResource& vecResSource //获得资源
	);
	std::string& BuildPkg_NotifyDgnAward( //只组包不发送
		UINT64 qwDgnId, //副本唯一实例
		UINT16 wDgnType, //副本类型
		UINT64 qwLastBattleID, //最后战报
		UINT8 byStar, //战斗评级
		const NItemProt::TVecItemGenInfo& vecItem, //获得物品
		const NItemProt::TVecResource& vecResSource //获得资源
	);

	//发送：通告副本进程
	bool Send_NotifyDgnProcess( //发送给当前协议处理的客户端
		UINT16 wDgnType, //副本类型
		const TVecMulCond& vecProcess //副本进度
	);
	bool SendClt_NotifyDgnProcess(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wDgnType, //副本类型
		const TVecMulCond& vecProcess //副本进度
	);
	std::string& BuildPkg_NotifyDgnProcess( //只组包不发送
		UINT16 wDgnType, //副本类型
		const TVecMulCond& vecProcess //副本进度
	);

	//发送：通告副本星级
	bool Send_NotifyDgnStar( //发送给当前协议处理的客户端
		UINT16 wDgnType, //副本类型
		const TVecMulCond& vecStar //副本星级
	);
	bool SendClt_NotifyDgnStar(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 wDgnType, //副本类型
		const TVecMulCond& vecStar //副本星级
	);
	std::string& BuildPkg_NotifyDgnStar( //只组包不发送
		UINT16 wDgnType, //副本类型
		const TVecMulCond& vecStar //副本星级
	);

	//发送：同步领奖记录
	bool Send_SynTeamAwardRecord( //发送给当前协议处理的客户端
		const TeamAwardAllRecord& stAward //同步数据
	);
	bool SendClt_SynTeamAwardRecord(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const TeamAwardAllRecord& stAward //同步数据
	);
	std::string& BuildPkg_SynTeamAwardRecord( //只组包不发送
		const TeamAwardAllRecord& stAward //同步数据
	);

	//发送：队伍战斗结果
	bool Send_TeamBattleResult( //发送给当前协议处理的客户端
		UINT16 DgnType, //副本类型
		UINT8 bySuc //0,失败，1成功
	);
	bool SendClt_TeamBattleResult(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		UINT16 DgnType, //副本类型
		UINT8 bySuc //0,失败，1成功
	);
	std::string& BuildPkg_TeamBattleResult( //只组包不发送
		UINT16 DgnType, //副本类型
		UINT8 bySuc //0,失败，1成功
	);

	//发送：更新历险副本信息
	bool Send_UpdateLiXian( //发送给当前协议处理的客户端
		const DgnLiXian& sLiXian //历险副本信息
	);
	bool SendClt_UpdateLiXian(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const DgnLiXian& sLiXian //历险副本信息
	);
	std::string& BuildPkg_UpdateLiXian( //只组包不发送
		const DgnLiXian& sLiXian //历险副本信息
	);

	//发送：更新单个副本信息
	bool Send_UpdateDgnInfo( //发送给当前协议处理的客户端
		const DgnStar& sDgnStar //副本信息
	);
	bool SendClt_UpdateDgnInfo(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const DgnStar& sDgnStar //副本信息
	);
	std::string& BuildPkg_UpdateDgnInfo( //只组包不发送
		const DgnStar& sDgnStar //副本信息
	);

	//发送：更新所有副本信息
	bool Send_UpdateDgnInfoForAll( //发送给当前协议处理的客户端
		const DgnLiXian& sLiXian, //历险副本信息
		const TVecDgnStar& vecStar //副本星级
	);
	bool SendClt_UpdateDgnInfoForAll(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const DgnLiXian& sLiXian, //历险副本信息
		const TVecDgnStar& vecStar //副本星级
	);
	std::string& BuildPkg_UpdateDgnInfoForAll( //只组包不发送
		const DgnLiXian& sLiXian, //历险副本信息
		const TVecDgnStar& vecStar //副本星级
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SSweepingAck : public CClientFuncAck
	{
		EDungeonResult eResult; //扫荡结果
		UINT32 dwSweepEndTime; //扫荡结束时间

		SSweepingAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：扫荡
	virtual bool OnRecv_Sweeping(
		UINT16 wDgnID, //副本ID
		UINT16 wCount, //次数
		UINT8 byOptions, //选项, 1位为gold，2位为key,采集相关
		shared_func<SSweepingAck>& fnAck //返回回调函数
	) = 0;

	struct SSweepingSpeedUpAck : public CClientFuncAck
	{
		EDungeonResult eResult; //加速扫荡结果

		SSweepingSpeedUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：加速扫荡
	virtual bool OnRecv_SweepingSpeedUp(
		UINT8 byOptions, //0为使用仙石
		shared_func<SSweepingSpeedUpAck>& fnAck //返回回调函数
	) = 0;

	struct SCancelSweepingAck : public CClientFuncAck
	{
		EDungeonResult eResult; //取消扫荡结果

		SCancelSweepingAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：取消扫荡
	virtual bool OnRecv_CancelSweeping(
		shared_func<SCancelSweepingAck>& fnAck //返回回调函数
	) = 0;

	struct SEnterPlayerDungeonAck : public CClientFuncAck
	{
		EDungeonResult eResult; //服务器返回结果

		SEnterPlayerDungeonAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：
	virtual bool OnRecv_EnterPlayerDungeon(
		UINT16 wDgnID, //副本ID
		shared_func<SEnterPlayerDungeonAck>& fnAck //返回回调函数
	) = 0;

	struct SLeavePlayerDungeonAck : public CClientFuncAck
	{
		EDungeonResult eResult; //服务器返回结果

		SLeavePlayerDungeonAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：离开单人副本
	virtual bool OnRecv_LeavePlayerDungeon(
		shared_func<SLeavePlayerDungeonAck>& fnAck //返回回调函数
	) = 0;

	struct SNotifyAcceptDgnAwardAck : public CClientFuncAck
	{
		EDungeonResult eResult; //服务器返回结果

		SNotifyAcceptDgnAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：客户端确认领奖
	virtual bool OnRecv_NotifyAcceptDgnAward(
		UINT64 qwDgnID, //副本唯一实例ID
		shared_func<SNotifyAcceptDgnAwardAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAllDgnInfoAck : public CClientFuncAck
	{
		DgnLiXian sLiXian; //历险副本信息
		TVecDgnStar vecStar; //副本星级

		SGetAllDgnInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查询副本星级
	virtual bool OnRecv_GetAllDgnInfo(
		shared_func<SGetAllDgnInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDgnSweepingInfoAck : public CClientFuncAck
	{
		SGetSweepInfo oGetSweepInfo; //扫荡信息

		SGetDgnSweepingInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：客户端查询扫荡信息
	virtual bool OnRecv_GetDgnSweepingInfo(
		shared_func<SGetDgnSweepingInfoAck>& fnAck //返回回调函数
	) = 0;

	//接收：查询副本进度和星级
	virtual void OnRecv_GetDgnProcessAndStar(
	) = 0;

	//接收：副本中玩家复活
	virtual void OnRecv_ReliveInDgn(
	) = 0;

	//接收：获取组队副本信息
	virtual void OnRecv_GetTeamInfo(
	) = 0;

	struct SBuyHeroDgnTimesAck : public CClientFuncAck
	{
		EDungeonResult eResult; //服务器返回结果

		SBuyHeroDgnTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买英雄副本次数
	virtual bool OnRecv_BuyHeroDgnTimes(
		UINT16 wDgnID, //副本ID
		shared_func<SBuyHeroDgnTimesAck>& fnAck //返回回调函数
	) = 0;

	struct SBuyLiXianDgnTimesAck : public CClientFuncAck
	{
		EDungeonResult eResult; //服务器返回结果

		SBuyLiXianDgnTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：购买历险副本次数
	virtual bool OnRecv_BuyLiXianDgnTimes(
		shared_func<SBuyLiXianDgnTimesAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDgnStarAwardInfoAck : public CClientFuncAck
	{
		TVecUINT16 vecAward; //副本星级已领奖ID

		SGetDgnStarAwardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：查询副本星级领奖状态
	virtual bool OnRecv_GetDgnStarAwardInfo(
		shared_func<SGetDgnStarAwardInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetDgnStarAwardAck : public CClientFuncAck
	{
		EDungeonResult eResult; //服务器返回结果
		TVecUINT16 vecAward; //副本星级已领奖ID

		SGetDgnStarAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：领取副本星级奖励
	virtual bool OnRecv_GetDgnStarAward(
		UINT16 wStarID, //领奖ID
		shared_func<SGetDgnStarAwardAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 59; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_Sweeping(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SweepingSpeedUp(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CancelSweeping(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_EnterPlayerDungeon(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_LeavePlayerDungeon(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_NotifyAcceptDgnAward(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAllDgnInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDgnSweepingInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDgnProcessAndStar(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_ReliveInDgn(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetTeamInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyHeroDgnTimes(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_BuyLiXianDgnTimes(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDgnStarAwardInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetDgnStarAward(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CDungeonProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NDungeonProt
