/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LogEvent.h
//  Purpose:      日志协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LogEvent.h"

namespace NLogEvent
{

//协议类：日志协议
class CLogEventSvr : public IProtocol
{
public:
	/////////////////////以下的接收函数需要重载/////////////////////
	//接收：心跳
	virtual void OnRecv_KeepAlive(
	) = 0;

	//接收：写日志请求
	virtual void OnRecv_WriteLogReq(
		ELogType eLogType, //日志类型
		const std::string& strLog //日志信息
	) = 0;

	//接收：写日志请求
	virtual void OnRecv_WriteLogToDB(
		const NLogDataDefine::TVecLogDataBase& vecLog //日志数据
	) = 0;

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 50; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:
	/////////////////////协议处理函数/////////////////////
	bool _DoRecv_KeepAlive(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WriteLogReq(const char* pBuf, UINT32 dwLen);
	bool _DoRecv_WriteLogToDB(const char* pBuf, UINT32 dwLen);

private:
	typedef bool (CLogEventSvr::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLogEvent
