#pragma once

#include <string>
#include <vector>

#include "ace\Recursive_Thread_Mutex.h"
#include "ace\ace.h"
#define LOG_BUFFER_SIZE 4096

#define MAX_LOG_NUM 128

enum E_Log_Type
{
	Log_Type_Info = 0,
	Log_Type_Warning = 1,
	Log_Type_Error = 2,
	Log_Type_Fatal = 3,
	Log_Type_Fucking = 4,

	//////////////////////////
	Log_Type_Others = 5,
};

class CLogBase
{
public:
	CLogBase()
	{
		InitLogTag();
	}
	virtual ~CLogBase() {};

	virtual int RecordLog(E_Log_Type eType, const std::string &strLog);

	virtual bool Print() = 0;
	
	char m_szLogBuffer[LOG_BUFFER_SIZE];
protected:
	std::vector<std::string> m_vecINFOLog;
	std::vector<std::string> m_vecWARNINGLog;
	std::vector<std::string> m_vecERRORLog;
	std::vector<std::string> m_vecFATALLog;
	std::vector<std::string> m_vecFUCKINGLog;
	std::vector<std::string> m_vecOTHERSLog;

	std::vector<std::string> m_Log_Tag;

	int m_iINFOLogOffset;
	int m_iWARNINGLogOffset;
	int m_iERRORLogOffset;
	int m_iFATALLogOffset;
	int m_iFUCKINGLogOffset;
	int m_iOTHERSLogOffset;

	int m_iINFOWriteOffset;
	int m_iWARNINGWriteOffset;
	int m_iERRORWriteOffset;
	int m_iFATALWriteOffset;
	int m_iFUCKINGWriteOffset;
	int m_iOTHERSWriteOffset;

	ACE_Recursive_Thread_Mutex m_AllLogLock;
private:
	void InitLogTag();
};