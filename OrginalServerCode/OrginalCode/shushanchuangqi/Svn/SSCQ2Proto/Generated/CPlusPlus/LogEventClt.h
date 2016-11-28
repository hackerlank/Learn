/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    LogEvent.h
//  Purpose:      日志协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include "LogEvent.h"

namespace NLogEvent
{

//协议类：日志协议
class CLogEventClt : public IProtocol
{
public:
	/////////////////////以下为发送函数/////////////////////
	//发送：心跳
	bool Send_KeepAlive( //发送给当前协议处理的服务器
	);
	bool SendSvr_KeepAlive(const UINT32* pSvrID, UINT8 byCnt //发送给多个服务器
	);
	std::string& BuildPkg_KeepAlive( //只组包不发送
	);

	//发送：写日志请求
	bool Send_WriteLogReq( //发送给当前协议处理的服务器
		ELogType eLogType, //日志类型
		const std::string& strLog //日志信息
	);
	bool SendSvr_WriteLogReq(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		ELogType eLogType, //日志类型
		const std::string& strLog //日志信息
	);
	std::string& BuildPkg_WriteLogReq( //只组包不发送
		ELogType eLogType, //日志类型
		const std::string& strLog //日志信息
	);

	//发送：写日志请求
	bool Send_WriteLogToDB( //发送给当前协议处理的服务器
		const NLogDataDefine::TVecLogDataBase& vecLog //日志数据
	);
	bool SendSvr_WriteLogToDB(const UINT32* pSvrID, UINT8 byCnt, //发送给多个服务器
		const NLogDataDefine::TVecLogDataBase& vecLog //日志数据
	);
	std::string& BuildPkg_WriteLogToDB( //只组包不发送
		const NLogDataDefine::TVecLogDataBase& vecLog //日志数据
	);

	/////////////////////以下为协议接口函数/////////////////////
	virtual bool HandleMessage(const char* pBuf, UINT32 dwLen) override;

	virtual void OnTimeOut(UINT8, UINT32) override { }

	virtual UINT8 GetProtID() const override { return 50; }

	virtual bool IsForClient() const override { return false; }

	std::string& GetEmptyPkg() { _strPkg.clear(); return _strPkg; }

protected:

private:
	typedef bool (CLogEventClt::*THandleFunc)(const char* pBuf, UINT32 dwLen);
	static THandleFunc _HandleFuncs[];
	std::string _strPkg;

protected:
	CInArchive _oInArchive;
};

} //namespace NLogEvent
