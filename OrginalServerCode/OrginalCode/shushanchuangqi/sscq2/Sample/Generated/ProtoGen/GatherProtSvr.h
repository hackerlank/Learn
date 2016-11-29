/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GatherProt.h
//  Purpose:      采集协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "GatherProt.h"

namespace NGatherProt
{

//协议类：采集协议
class CGatherProtSvr : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：采集结束通知
	bool Send_GatherEndNotify( //发送给当前协议处理的客户端
		EGatherResult eResult //服务器返回结果
	);
	bool SendClt_GatherEndNotify(const UINT64* pUsrID, UINT16 wCnt, //发送给多个客户端
		EGatherResult eResult //服务器返回结果
	);
	std::string& BuildPkg_GatherEndNotify( //只组包不发送
		EGatherResult eResult //服务器返回结果
	);

	/////////////////////以下的接收函数需要重载/////////////////////
	struct SGatherReqAck : public CClientFuncAck
	{
		EGatherResult eResult; //采集结果
		UINT32 dwGatherTimer; //采集剩余时间

		SGatherReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：采集请求
	virtual bool OnRecv_GatherReq(
		UINT32 dwGatherId, //采集ID
		shared_func<SGatherReqAck>& fnAck //返回回调函数
	) = 0;

	struct SCancelGatherAck : public CClientFuncAck
	{
		EGatherResult eResult; //取消采集结果

		SCancelGatherAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：取消采集
	virtual bool OnRecv_CancelGather(
		shared_func<SCancelGatherAck>& fnAck //返回回调函数
	) = 0;

	struct SGetGatherInfoAck : public CClientFuncAck
	{
		UINT32 dwGtatherId; //采集实例
		UINT32 dwReserverTimer; //剩余时间

		SGetGatherInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID);
	private:
		virtual void SendReturn(bool bRet) override;
	};
	//接收：客户端查询采集信息
	virtual bool OnRecv_GetGatherInfo(
		shared_func<SGetGatherInfoAck>& fnAck //返回回调函数
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 60; }

	virtual bool IsForClient() const override { return true; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_GatherReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_CancelGather(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_GetGatherInfo(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CGatherProtSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NGatherProt
