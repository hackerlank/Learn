#include "stdafx.h"
#include "GameServerLog.h"
#include "Protocols.h"
void CGameServerLog::LogToDB(LogDataBasePtr ptrLog)
{
    TVecLogDataBase vecLog;
    vecLog.push_back(ptrLog);
    g_LogEvent.Send_WriteLogToDB(vecLog);
}

