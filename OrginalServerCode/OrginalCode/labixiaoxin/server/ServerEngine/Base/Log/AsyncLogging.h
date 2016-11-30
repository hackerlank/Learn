#pragma once

#include "LogBase.h"

class CAsyncLog : public CLogBase 
{
public:
	CAsyncLog(const char *strName);
	virtual ~CAsyncLog();

	virtual bool Print();

	bool m_bNeedWrite;
private:

	bool WriteToBuffer(const int iType, const std::string &strLog);
	bool FlushToFile();

	int m_iBufferOffset;
	char m_buffer[LOG_BUFFER_SIZE];
	char m_strName[32];
};