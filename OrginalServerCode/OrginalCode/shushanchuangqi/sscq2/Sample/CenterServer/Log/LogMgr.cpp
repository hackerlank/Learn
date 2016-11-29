#include "stdafx.h"
#include "LogMgr.h"
#include "Protocols.h"

CLogMgr::CLogMgr()
{

}

CLogMgr::~CLogMgr()
{

}

CLogMgr& CLogMgr::Instance()
{
	static CLogMgr g_logMgr;
	return g_logMgr;
}

SLogStream& CLogMgr::Stream()
{
	_oStream.clear();
	_oStream.str("");
	return _oStream;
}

void CLogMgr::LogUdpInfo(const std::string& strMsg)
{
	g_LogEvent.Send_WriteLogReq(NLogEvent::eLogUDPLog, strMsg);
}
