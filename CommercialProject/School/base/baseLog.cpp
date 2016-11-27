#include "baseLog.h"
#include "baseTime.h"
#include "basePthread.h"
Logger::Logger(char *name)
{
	m_name = name;
	m_hourFile = NULL;
	m_fpFile = NULL;
	m_hour = 0;
	m_file = "/home/flyer/flyer/SchoolProgress/trunk/School/log/";
	m_level = LEVEL_ALL;
	m_Console = stdout;
}

Logger::~Logger()
{
	if(m_fpFile)
	{
		fclose(m_fpFile);
		m_fpFile = NULL;
	}
	if(m_hourFile)
	{
		fclose(m_hourFile);
		m_hourFile= NULL;
	}
}

void Logger::debug(const char* pattern,...)
{
	CheckConditonVoid(m_level<=LEVEL_DEBUG);
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_DEBUG,pattern,vp);
	va_end(vp);
}

void Logger::setFile( const char *fileName )
{
	m_logMutex.lock();
	m_file = fileName;
	m_logMutex.unlock();
}

void Logger::setLevel(const LogLevel level)
{
	m_logMutex.lock();
	m_level = level;
	m_logMutex.unlock();
}

void Logger::setLevel(const std::string &level)
{
	if ("off" == level) setLevel(LEVEL_OFF);
	else if ("fatal" == level) setLevel(LEVEL_FATAL);    else if ("error" == level) setLevel(LEVEL_ERROR);
	else if ("warn" == level) setLevel(LEVEL_WARN);
	else if ("info" == level) setLevel(LEVEL_INFO);
	else if ("debug" == level) setLevel(LEVEL_DEBUG);
	else if ("all" == level) setLevel(LEVEL_ALL);
}

void Logger::warn(const char *pattern,...)
{
	CheckConditonVoid(m_level<=LEVEL_WARN);
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_WARN,pattern,vp);
	va_end(vp);
}

void Logger::fatal(const char *pattern,...)
{
	CheckConditonVoid(m_level<=LEVEL_FATAL);
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_FATAL,pattern,vp);
	va_end(vp);
}

void Logger::info(const char *pattern,...)
{
	CheckConditonVoid(m_level<=LEVEL_ERROR);
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_INFO,pattern,vp);
	va_end(vp);
}

void Logger::error(const char* pattern,...)
{
	CheckConditonVoid(m_level<=LEVEL_ERROR);
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_ERROR,pattern,vp);
	va_end(vp);
}

void Logger::log(const LogLevel level,const char * pattern,...)
{
	CheckConditonVoid(m_level<=level);
	va_list vp;
	va_start(vp,pattern);
	logva(level,pattern,vp);
	va_end(vp);
}

void Logger::logva(const LogLevel level,const char* pattern,va_list vp)
{
	CheckConditonVoid(m_level<=level);
	char szName[100] = {'\0'};
	SYSTEMTIME systemTime;
	CheckConditonVoid(getSystemTime(&systemTime));
	m_logMutex.lock();
	if(!m_file.empty())
	{
		if(m_hour != systemTime.wHour)
		{
			if(m_hourFile)
			{
				fclose(m_hourFile);
			}
			snprintf(szName,sizeof(szName),"%s%04d%02d%02d.log",m_file.c_str(),systemTime.wYear,systemTime.wMonth,systemTime.wDay);
			m_hourFile = fopen(szName,"at");
			m_hour = systemTime.wHour;
		}
		if(!m_fpFile)
		{
			m_fpFile = fopen(m_file.c_str(),"at");
		}
	}
	if(m_hourFile)
	{
		fprintf(m_hourFile,"[%s] ",m_name.c_str());
		fprintf(m_hourFile,"%04d/%02d/%02d ",systemTime.wYear,systemTime.wMonth,systemTime.wDay);
		fprintf(m_hourFile,"%02d:%02d:%02d ",systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
	 	vfprintf(m_hourFile,pattern,vp);
		fprintf(m_hourFile,"\n");
		fflush(m_hourFile);
	}
	if(m_fpFile)
	{
		fprintf(m_fpFile,"[%s] ",m_name.c_str());
		fprintf(m_fpFile,"%04d/%02d/%02d ",systemTime.wYear,systemTime.wMonth,systemTime.wDay);
		fprintf(m_fpFile,"%02d:%02d:%02d ",systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
	 	vfprintf(m_fpFile,pattern,vp);
		fprintf(m_fpFile,"\n");
		fflush(m_fpFile);
	}
	if(m_Console)
	{
		fprintf(m_Console,"[%s] ",m_name.c_str());
		fprintf(m_Console,"%04d/%02d/%02d ",systemTime.wYear,systemTime.wMonth,systemTime.wDay);
		fprintf(m_Console,"%02d:%02d:%02d ",systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
		vfprintf(m_Console,pattern,vp);
		fprintf(m_Console,"\n");
		fflush(m_Console);
	}
	m_logMutex.unlock();
}

void Logger::removeConsole()
{
	m_logMutex.lock();
	m_Console = NULL;
	m_logMutex.unlock();
}

const char* Logger::getName()
{
	return m_name.c_str();
}

void Logger::setName(const char* name)
{
	m_name = name;
}




		
