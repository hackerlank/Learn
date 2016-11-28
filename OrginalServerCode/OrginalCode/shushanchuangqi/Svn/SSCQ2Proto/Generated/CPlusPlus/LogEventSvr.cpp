/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LogEvent.cpp
//  Purpose:      日志协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LogEventSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLogEvent
{

CLogEventSvr::THandleFunc CLogEventSvr::_HandleFuncs[] =
{
	&CLogEventSvr::_DoRecv_KeepAlive, //FuncID: 1
	&CLogEventSvr::_DoRecv_WriteLogReq, //FuncID: 2
	&CLogEventSvr::_DoRecv_WriteLogToDB, //FuncID: 3
};

bool CLogEventSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	INT8 byFuncID = pBuf[0];
	if(byFuncID == 0 || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs))
	{
#ifdef _DEBUG
		LOG_CRI << "byFuncID is invalid: " << byFuncID;
#endif
		return false;
	}
	pBuf += sizeof(INT8);
	dwLen -= sizeof(INT8);
	if(byFuncID > 0)
	{
		--byFuncID;
		if(_HandleFuncs[static_cast<UINT8>(byFuncID)] != NULL)
			return (this->*_HandleFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);
	}
	return true;
}

bool CLogEventSvr::_DoRecv_KeepAlive(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_KeepAlive();
	return true;
}

bool CLogEventSvr::_DoRecv_WriteLogReq(const char* pBuf_, UINT32 dwLen_)
{
	ELogType eLogType = (ELogType)0;
	std::string strLog;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eLogType >> strLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 50, Function: 2";
		return false;
	}
	OnRecv_WriteLogReq(eLogType, strLog);
	return true;
}

bool CLogEventSvr::_DoRecv_WriteLogToDB(const char* pBuf_, UINT32 dwLen_)
{
	NLogDataDefine::TVecLogDataBase vecLog;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 50, Function: 3";
		return false;
	}
	OnRecv_WriteLogToDB(vecLog);
	return true;
}

} //namespace NLogEvent
