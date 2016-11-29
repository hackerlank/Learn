#include "stdafx.h"
#include "DBServerLog.h"
#include "Protocols.h"

void CDBServerLog::LogToDB(LogDataBasePtr ptrLog)
{
    TVecLogDataBase vecLog;
    vecLog.push_back(ptrLog);
    g_LogEvent.Send_WriteLogToDB(vecLog);
}


