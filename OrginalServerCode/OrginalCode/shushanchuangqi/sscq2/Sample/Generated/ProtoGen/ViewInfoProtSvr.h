/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ViewInfoProt.h
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "ViewInfoProt.h"

namespace NViewInfoProt
{

//协议类：查看信息协议
class CViewInfoProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetRoleInfoAck : public CClientFuncAck
	{
		SRoleData RoleData; //对方主角信息

		SGetRoleInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取对方主角信息
	virtual bool OnRecv_GetRoleInfo(
		const std::string& strReceiveName, //对方玩家名字
		shared_func<SGetRoleInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SGetFighterInfoAck : public CClientFuncAck
	{
		SFighterData FighterData; //对方散仙信息

		SGetFighterInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取散仙信息
	virtual bool OnRecv_GetFighterInfo(
		const std::string& strReceiveName, //对方玩家名字
		UINT64 qwInstID, //散仙唯一ID
		shared_func<SGetFighterInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 82; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetRoleInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetFighterInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CViewInfoProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NViewInfoProt
