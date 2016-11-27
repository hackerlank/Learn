#ifndef BASE_LOGGER_H
#define BASE_LOGGER_H
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
using namespace std;
#include "baseLock.h"

//日志类
class Logger
{
	public:
		typedef enum
		{
			LEVEL_OFF = 6,
			LEVEL_FATAL = 5,
			LEVEL_ERROR = 4,
			LEVEL_WARN  = 3,
			LEVEL_INFO  = 2,
			LEVEL_DEBUG = 1,
			LEVEL_ALL = 0
		}LogLevel;
	private:
		FILE *m_hourFile;
		FILE *m_Console;
		FILE *m_fpFile;
		int m_hour;
		std::string m_name;
		std::string m_file;
		LogLevel m_level;
		Mutex m_logMutex;
	private:
		void logva(const LogLevel level,const char* pattern,va_list vp);
		void setLevel(const LogLevel level);
	public:
		Logger(char *name = "Logger");
		void setFile(const char *fileName);
		~Logger();
		void debug(const char *pattern,...);
		void error(const char* pattern,...);
		void info(const char *pattern,...);
		void warn(const char *pattern,...);
		void fatal(const char *pattern,...);
		void setLevel(const std::string &level);
		void log(const LogLevel level,const char * pattern,...);
		void removeConsole();
		const char* getName();
		void setName(const char* loggName);
};

#endif
