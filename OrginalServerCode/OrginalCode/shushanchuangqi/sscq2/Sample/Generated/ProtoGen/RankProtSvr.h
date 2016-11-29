/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    RankProt.h
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "RankProt.h"

namespace NRankProt
{

//协议类：排行榜相关协议
class CRankProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetRankInfoAck : public CClientFuncAck
	{
		ERankType eType; //排行榜类型
		UINT32 dwMaxCount; //最大排名数量
		UINT32 dwCurIndex; //当前排名索引
		UINT32 dwSelfRank; //自己所在排名
		TVecRankInfo vecRankInfo; //排行榜数据
		TVecRankInfo vecSelfRankInfo; //自己所在排名

		SGetRankInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取排行榜数据
	virtual bool OnRecv_GetRankInfo(
		ERankType eType, //排行榜类型
		UINT32 dwIndex, //排名索引
		UINT32 dwCount, //排名个数
		shared_func<SGetRankInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetPlayerFeatureAck : public CClientFuncAck
	{
		ERankResult eResult; //崇拜结果
		NBattleGS::SFeatureBasePtr pFeature; //外观信息

		SGetPlayerFeatureAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得玩家外观信息
	virtual bool OnRecv_GetPlayerFeature(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetPlayerFeatureAck>& fnAck //返回回调函数
	) = 0;

	struct SGetAdoreCountAck : public CClientFuncAck
	{
		UINT32 dwCount; //崇拜数量
		UINT32 dwSelfCount; //自己剩余崇拜数量

		SGetAdoreCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获得崇拜数量
	virtual bool OnRecv_GetAdoreCount(
		UINT64 qwRoleID, //玩家ID
		shared_func<SGetAdoreCountAck>& fnAck //返回回调函数
	) = 0;

	struct SAdorePlayerAck : public CClientFuncAck
	{
		ERankResult eResult; //崇拜结果
		UINT32 dwCount; //崇拜数量
		UINT32 dwSelfCount; //自己剩余崇拜数量

		SAdorePlayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：崇拜玩家
	virtual bool OnRecv_AdorePlayer(
		UINT64 qwRoleID, //玩家ID
		shared_func<SAdorePlayerAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 80; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetRankInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetPlayerFeature(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetAdoreCount(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_AdorePlayer(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CRankProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NRankProt
