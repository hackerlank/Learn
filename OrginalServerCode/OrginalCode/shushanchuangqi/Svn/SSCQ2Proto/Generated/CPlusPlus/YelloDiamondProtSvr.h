/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    YelloDiamondProt.h
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "YelloDiamondProt.h"

namespace NYelloDiamondProt
{

//协议类：QQ黄钻协议
class CYelloDiamondProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGainYDBagAck : public CClientFuncAck
	{
		EOpResult eOpResult; //操作结果

		SGainYDBagAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取黄钻礼包
	virtual bool OnRecv_GainYDBag(
		EBagType eBagType, //礼包类型
		UINT16 dLevel, //玩家等级成长礼包
		shared_func<SGainYDBagAck>& fnAck //返回回调函数
	) = 0;

	struct SGetYDBagInfoAck : public CClientFuncAck
	{
		SYDInfo ydInfo; //黄钻信息

		SGetYDBagInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取黄钻礼包领取信息
	virtual bool OnRecv_GetYDBagInfo(
		shared_func<SGetYDBagInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 200; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GainYDBag(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetYDBagInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CYelloDiamondProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NYelloDiamondProt
