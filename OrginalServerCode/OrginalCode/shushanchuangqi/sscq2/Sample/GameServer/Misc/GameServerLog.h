#ifndef GAMESVERLOG_H__
#define GAMESVERLOG_H__

#include "LogDataDefine.h"

using namespace NLogDataDefine;
class CGameServerLog
{
    public:
    static void LogToDB(LogDataBasePtr ptrLog);
};

#endif //GAMESVERLOG_H__
