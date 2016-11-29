/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    SignProt.h
//  Purpose:      签到协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "SignProt.h"

namespace NSignProt
{

//协议类：签到协议
class CSignProtSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetSignInfoAck : public CClientFuncAck
	{
		UINT32 dwSignData; //按位计数，从右到左，一位表示1天，1表示该日已签到
		UINT8 byReSignTimes; //该月补签天数
		UINT32 dwAward; //签到奖励包获取状态

		SGetSignInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求签到信息
	virtual bool OnRecv_GetSignInfo(
		shared_func<SGetSignInfoAck>& fnAck //返回回调函数
	) = 0;

	struct SDoSignAck : public CClientFuncAck
	{
		ESignResult eResult; //处理结果
		UINT32 dwSignData; //按位计数，从右到左，一位表示1天，1表示该日已签到

		SDoSignAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求签到
	virtual bool OnRecv_DoSign(
		shared_func<SDoSignAck>& fnAck //返回回调函数
	) = 0;

	struct SDoReSignAck : public CClientFuncAck
	{
		ESignResult eResult; //处理结果
		UINT32 dwSignData; //按位计数，从右到左，一位表示1天，1表示该日已签到
		UINT8 byReSignTimes; //该月补签天数

		SDoReSignAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求补签
	virtual bool OnRecv_DoReSign(
		UINT8 byDay, //补签日期
		shared_func<SDoReSignAck>& fnAck //返回回调函数
	) = 0;

	struct SDoGetAwardAck : public CClientFuncAck
	{
		ESignResult eResult; //处理结果
		UINT32 dwAward; //签到奖励包获取状态

		SDoGetAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：请求领取奖励
	virtual bool OnRecv_DoGetAward(
		UINT8 byId, //奖励ID
		shared_func<SDoGetAwardAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 83; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetSignInfo(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DoSign(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DoReSign(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_DoGetAward(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CSignProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NSignProt
