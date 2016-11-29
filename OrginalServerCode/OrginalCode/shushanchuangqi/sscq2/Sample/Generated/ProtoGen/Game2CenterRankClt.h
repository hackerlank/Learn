/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterRank.h
//  Purpose:      排行榜相关内部协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "BattleGS.h"
#include "RankProt.h"

namespace NGame2CenterRank
{

//协议类：排行榜相关内部协议
class CGame2CenterRankClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：更新排名信息
	bool Send_UpdateRankInfo( //发送给当前协议处理的服务器
		NRankProt::ERankType eType, //更新类型
		UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	);
	bool SendSvr_UpdateRankInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		NRankProt::ERankType eType, //更新类型
		UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	);
	std::string& BuildPkg_UpdateRankInfo( //只组包不发送
		NRankProt::ERankType eType, //更新类型
		UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	);

	//发送：更新所有待更新的等级信息
	bool Send_UpdateAllLevelInfo( //发送给当前协议处理的服务器
		const TVecUINT64& vecRoleID, //玩家ID
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	);
	bool SendSvr_UpdateAllLevelInfo(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const TVecUINT64& vecRoleID, //玩家ID
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	);
	std::string& BuildPkg_UpdateAllLevelInfo( //只组包不发送
		const TVecUINT64& vecRoleID, //玩家ID
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetFeatureAck : public CServerFuncAck
	{
		UINT8 byError; //0 成功, 其他错误
		std::string strName; //玩家姓名
		UINT16 wLevel; //玩家等级
		NBattleGS::SFeatureBasePtr pFeature; //外观信息

		SGetFeatureAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取玩家的外观信息
	virtual bool OnRecv_GetFeature(
		UINT64 qwRoleID, //玩家唯一ID
		shared_func<SGetFeatureAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 81; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetFeature(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGame2CenterRankClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterRank
