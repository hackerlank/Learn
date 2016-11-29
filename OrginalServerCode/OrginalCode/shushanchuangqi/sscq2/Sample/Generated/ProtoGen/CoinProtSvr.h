/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    CoinProt.h
//  Purpose:      888礼券协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "CoinProt.h"

namespace NCoinProt
{

//协议类：888礼券协议
class CCoinProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetCoinPacketAck : public CClientFuncAck
	{
		EResultInCoinProt eResult; //操作结果

		SGetCoinPacketAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取礼包
	virtual bool OnRecv_GetCoinPacket(
		NProtoCommon::EMoneyType eType, //礼包类型
		UINT32 dwMoney, //数量
		shared_func<SGetCoinPacketAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 91; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetCoinPacket(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CCoinProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NCoinProt
