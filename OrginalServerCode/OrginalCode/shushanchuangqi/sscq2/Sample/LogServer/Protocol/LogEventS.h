#pragma once
#include "LogEventSvr.h"

using namespace NLogEvent;

class CLogEventS : public CLogEventSvr
{
public:
	virtual void OnRecv_KeepAlive(
		);
	virtual void OnRecv_WriteLogReq(
		ELogType eLogType, 
		const std::string& strLog 
		);
    //接收：写日志请求
	virtual void OnRecv_WriteLogToDB(
		const NLogDataDefine::TVecLogDataBase& vecLog //日志数据
	);

};
