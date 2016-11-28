/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    CompareBattlePoint.h
//  Purpose:      变强(战力对比)相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "CompareBattlePoint.h"

namespace NCompareBattlePoint
{

//协议类：变强(战力对比)相关协议
class CCompareBattlePointSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SCompareOtherBPByIDAck : public CClientFuncAck
	{
		TVecCompareData vecCompareData; //玩家的对比数据信息

		SCompareOtherBPByIDAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：战斗力对比
	virtual bool OnRecv_CompareOtherBPByID(
		UINT64 qwRoleID, //对方的玩家ID
		shared_func<SCompareOtherBPByIDAck>& fnAck //返回回调函数
	) = 0;

	struct SCompareOtherBPByNameAck : public CClientFuncAck
	{
		TVecCompareData vecCompareData; //玩家的对比数据信息

		SCompareOtherBPByNameAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：战斗力对比
	virtual bool OnRecv_CompareOtherBPByName(
		const std::string& strName, //对方的玩家名字
		shared_func<SCompareOtherBPByNameAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 58; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_CompareOtherBPByID(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CompareOtherBPByName(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CCompareBattlePointSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCompareBattlePoint
