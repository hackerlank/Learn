/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    FightFormation.h
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "FightFormation.h"

namespace NFightFormation
{

//协议类：新阵型相关协议
class CFightFormationSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetFightFormationAck : public CClientFuncAck
	{
		FightFormationInfo oFightFormation; //战斗阵形信息

		SGetFightFormationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：取得阵形信息
	virtual bool OnRecv_GetFightFormation(
		UINT16 wBattleType, //战斗类型 EBattleType
		shared_func<SGetFightFormationAck>& fnAck //返回回调函数
	) = 0;

	struct SSetFightFormationAck : public CClientFuncAck
	{
		EFightFormationResult eRet; //操作结果

		SSetFightFormationAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：设置阵形信息
	virtual bool OnRecv_SetFightFormation(
		UINT16 wBattleType, //战斗类型
		const FightFormationInfo& oFightFormation, //阵形ID
		shared_func<SSetFightFormationAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFightHeroInfoAck : public CClientFuncAck
	{
		TVecFightHeroInfo vecFightHeroInfo; //战斗阵形信息

		SGetFightHeroInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：战斗散仙信息
	virtual bool OnRecv_GetFightHeroInfo(
		UINT16 wBattleType, //战斗类型 EBattleType
		shared_func<SGetFightHeroInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 132; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetFightFormation(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_SetFightFormation(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFightHeroInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CFightFormationSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NFightFormation
