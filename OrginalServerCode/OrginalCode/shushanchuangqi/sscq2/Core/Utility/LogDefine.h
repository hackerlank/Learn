#ifdef _WIN32
#define CUR_FUNC_NAME __FUNCTION__
#else
#define CUR_FUNC_NAME __func__
#endif

#define THIS_FILE ((strrchr(__FILE__, '/') ?:__FILE__ - 1) +1)  // 去除文件名的绝对路径前缀

#define LOG(LEVEL) CLogObj(LOG_OBJ, LEVEL, CUR_FUNC_NAME, __LINE__,THIS_FILE)
#define LNF(LEVEL) CLogObj(LOG_OBJ, LEVEL)
#define LOG_ADD CLogObj(LOG_OBJ)
#define LOG_RAW CLogObj(LOG_OBJ)

#define LOGCTL_NONE CLogObj::eLogNone
#define LOGCTL_FLUSH CLogObj::eLogFlush
#define LOGCTL_NO_CONSOLE CLogObj::eLogNoConsole
#define LOGCTL_NO_NEWLINE CLogObj::eLogNoNewLine
//严重错误(Critical)
#ifdef OPEN_CRI
#define LOG_CRI LOG(eLogLevelCritical)
#define LNF_CRI LNF(eLogLevelCritical)
#else
#define LOG_CRI CNulLog::_sNulLog
#define LNF_CRI CNulLog::_sNulLog
#endif
//警告(Warning)
#ifdef OPEN_WRN
#define LOG_WRN LOG(eLogLevelWarning)
#define LNF_WRN LNF(eLogLevelWarning)
#else
#define LOG_WRN CNulLog::_sNulLog
#define LNF_WRN CNulLog::_sNulLog
#endif

//信息(Information)
#ifdef OPEN_INF
#define LOG_INF LOG(eLogLevelInfo)
#define LNF_INF LNF(eLogLevelInfo)
#else
#define LOG_INF CNulLog::_sNulLog
#define LNF_INF CNulLog::_sNulLog
#endif

//调试(Debug)
#ifdef OPEN_DBG
#define LOG_DBG LOG(eLogLevelDebug)
#define LNF_DBG LNF(eLogLevelDebug)
#else
#define LOG_DBG CNulLog::_sNulLog
#define LNF_DBG CNulLog::_sNulLog
#endif

//文字(Text)
#ifdef OPEN_TXT
#define LOG_TXT CLogObj(LOG_OBJ, eLogLevelInfo, NULL, 0)
#define LNF_TXT CLogObj(LOG_OBJ, eLogLevelInfo, NULL, 0)
#else
#define LOG_TXT CNulLog::_sNulLog
#define LNF_TXT CNulLog::_sNulLog
#endif

