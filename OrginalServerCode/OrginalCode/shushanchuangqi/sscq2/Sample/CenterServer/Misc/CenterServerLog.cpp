#include "stdafx.h"
#include "CenterServerLog.h"
#include "Protocols.h"

void CCenterServerLog::LogToDB(LogDataBasePtr ptrLog)
{
    TVecLogDataBase vecLog;
    vecLog.push_back(ptrLog);
    g_LogEvent.Send_WriteLogToDB(vecLog);
}

