#include "AsyncLogging.h"
#include <stdio.h>
#include "ace/Recursive_Thread_Mutex.h"
#include "ace/Guard_T.h"
#include "../../GameBase/Common/GameUtils.h"

CAsyncLog::CAsyncLog(const char *strName)
{
	m_bNeedWrite = false;
	m_iBufferOffset = 0;
	int iLen = strlen(strName);
	if (iLen == 0)
	{
		strcpy(m_strName, "error_name");
	}
	else
	{
		if (iLen > 31)
			iLen = 31;
		memcpy(m_strName, strName, iLen);
		m_strName[iLen] = '\0';
	}
	
}

CAsyncLog::~CAsyncLog()
{
	
}

bool CAsyncLog::WriteToBuffer(const int iType, const std::string &strLog)
{
	if (m_iBufferOffset + strLog.size() >= LOG_BUFFER_SIZE)
	{
		FlushToFile();
	}
	memcpy(m_buffer+m_iBufferOffset, strLog.c_str(), strLog.size());
	m_iBufferOffset += strLog.size();
	return true;
}

bool CAsyncLog::Print()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_AllLogLock);
	m_bNeedWrite = false;
	for (;m_iINFOWriteOffset<m_iINFOLogOffset;++m_iINFOWriteOffset) //m_iINFOLogOffset 一定是小于m_vecINFOLog.size()的
	{
		WriteToBuffer(Log_Type_Info, m_vecINFOLog[m_iINFOWriteOffset]);
		m_bNeedWrite = true;
	}
	for (;m_iWARNINGWriteOffset<m_iWARNINGLogOffset;++m_iWARNINGWriteOffset)
	{
		WriteToBuffer(Log_Type_Warning, m_vecWARNINGLog[m_iWARNINGWriteOffset]);
		m_bNeedWrite = true;
	}
	for (;m_iERRORWriteOffset<m_iERRORLogOffset;++m_iERRORWriteOffset)
	{
		WriteToBuffer(Log_Type_Error, m_vecERRORLog[m_iERRORWriteOffset]);
		m_bNeedWrite = true;
	}
	for (;m_iFATALWriteOffset<m_iFATALLogOffset;++m_iFATALWriteOffset)
	{
		WriteToBuffer(Log_Type_Fatal, m_vecFATALLog[m_iFATALWriteOffset]);
		m_bNeedWrite = true;
	}
	for (;m_iFUCKINGWriteOffset<m_iFUCKINGLogOffset;++m_iFUCKINGWriteOffset)
	{
		WriteToBuffer(Log_Type_Fucking, m_vecFUCKINGLog[m_iFUCKINGWriteOffset]);
		m_bNeedWrite = true;
	}
	for (;m_iOTHERSWriteOffset<m_iOTHERSLogOffset;++m_iOTHERSWriteOffset)
	{
		WriteToBuffer(Log_Type_Others, m_vecOTHERSLog[m_iOTHERSWriteOffset]);
		m_bNeedWrite = true;
	}
	FlushToFile();
	if (m_iINFOWriteOffset > m_iINFOLogOffset)
	{
		m_iINFOWriteOffset = 0;
	}
	if (m_iWARNINGWriteOffset > m_iWARNINGLogOffset)
	{
		m_iWARNINGWriteOffset = 0;
	}
	if (m_iERRORWriteOffset > m_iERRORLogOffset)
	{
		m_iERRORWriteOffset = 0;
	}
	if (m_iFATALWriteOffset > m_iFATALLogOffset)
	{
		m_iFATALWriteOffset = 0;
	}
	if (m_iFUCKINGWriteOffset > m_iFUCKINGLogOffset)
	{
		m_iFUCKINGWriteOffset = 0;
	}
	if (m_iOTHERSWriteOffset > m_iOTHERSLogOffset)
	{
		m_iOTHERSWriteOffset = 0;
	}
	return m_bNeedWrite;
}

bool CAsyncLog::FlushToFile()
{
	if (m_bNeedWrite)
	{
		char strFilePath[128]= {}, strDate[32] = {};

		//if (system("md loginfo >nul") == 0)
		{
			_mkdir("loginfo");
		}
		GameUtils::get_current_day_str(strDate);
		sprintf(strFilePath, "loginfo/%s_%s.log",m_strName, strDate);
		//strftime(buff, 32, "%Y-%m-%d.log", &t); // buff is what u want.

		FILE *fp = fopen(strFilePath, "a");
		if (fp == NULL)
		{
			return false;
		}
		fwrite(m_buffer, m_iBufferOffset, 1, fp);
		m_iBufferOffset = 0;
		fclose(fp);
	}
	return true;
}