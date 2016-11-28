/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
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
class CGame2CenterRankSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：获取玩家的外观信息
	bool Send_GetFeature( //发送给当前协议处理的服务器
		UINT64 qwRoleID, //玩家唯一ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 其他错误
			const std::string& strName, //(返回值)玩家姓名
			UINT16 wLevel, //(返回值)玩家等级
			const NBattleGS::SFeatureBasePtr& pFeature //(返回值)外观信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);
	bool SendSvr_GetFeature(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		UINT64 qwRoleID, //玩家唯一ID
		boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
			UINT8 byError, //(返回值)0 成功, 其他错误
			const std::string& strName, //(返回值)玩家姓名
			UINT16 wLevel, //(返回值)玩家等级
			const NBattleGS::SFeatureBasePtr& pFeature //(返回值)外观信息
		)> fnOnReturn_ = NULL //返回时的回调函数
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：更新排名信息
	virtual void OnRecv_UpdateRankInfo(
		NRankProt::ERankType eType, //更新类型
		UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	) = 0;

	//接收：更新所有待更新的等级信息
	virtual void OnRecv_UpdateAllLevelInfo(
		const TVecUINT64& vecRoleID, //玩家ID
		const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID) override;

	virtual UINT8 GetProtID() const override { return 81; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_UpdateRankInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_UpdateAllLevelInfo(const char* pBuf, UINT32 dwLen);

	/////////////////////协议返回函数/////////////////////
	bool _DoReturn_GetFeature(const char* pBuf, UINT32 dwLen);
	void _OnTimeOut_GetFeature(UINT32 dwSessionID);

private:
	typedef bool (CGame2CenterRankSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _ReturnFuncs[];
	static THandleFunc _HandleFuncs[];

	typedef void (CGame2CenterRankSvr::*TTimeOutFunc)(UINT32 dwSessionID);
	static TTimeOutFunc _TimeoutFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGame2CenterRank
