#ifndef DBSVERLOG_H__
#define DBSVERLOG_H__
#include "LogDataDefine.h"
using namespace NLogDataDefine;

class CDBServerLog
{
    public:
    static void LogToDB(LogDataBasePtr ptrLog);
};

#endif //DBSVERLOG_H__

