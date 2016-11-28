/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BeautyLogGS.h
//  Purpose:      美女log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "BeautyLogGS.h"

namespace NBeautyLogGS
{

//协议类：美女log
class CBeautyLogGSSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：美女log添加
	bool Send_AddBeautyLogNotify( //发送给当前协议处理的客户端
		const SBeautyLog& oAddBeautyLog //美女log信息
	);
	bool SendClt_AddBeautyLogNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		const SBeautyLog& oAddBeautyLog //美女log信息
	);
	std::string& BuildPkg_AddBeautyLogNotify( //只组包不发送
		const SBeautyLog& oAddBeautyLog //美女log信息
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGetBeautyLogAck : public CClientFuncAck
	{
		TVecBeautyLog vecBeautyLog; //美女log信息

		SGetBeautyLogAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：获取美女log信息
	virtual bool OnRecv_GetBeautyLog(
		shared_func<SGetBeautyLogAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 133; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GetBeautyLog(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CBeautyLogGSSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NBeautyLogGS
