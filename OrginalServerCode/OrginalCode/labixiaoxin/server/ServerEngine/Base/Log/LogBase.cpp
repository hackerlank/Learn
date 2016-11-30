#include "LogBase.h"
#include <time.h>
#include "ace\Condition_Thread_Mutex.h"
#include "ace\Null_Condition.h"
#include "ace\Guard_T.h"
#include "../../GameBase/Common/GameUtils.h"

int CLogBase::RecordLog(E_Log_Type eType, const std::string &strLog)
{
	if (eType > Log_Type_Others)
	{
		return -1;
	}

	//time_t tNow = time(NULL);
	//tm t = *gmtime(&tNow);  
	//char buff[32]= {};  
	//strftime(buff, 32, "%Y-%m-%d %H:%M:%S", &t); // buff is what u want.
	char strTime[32] = {};
	GameUtils::get_current_time_str(strTime);
	std::string strRecord = strTime + m_Log_Tag[eType] + strLog + "\n";
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_AllLogLock);
	switch(eType)
	{
	case Log_Type_Info:
		{
//change by xxj 2015/07/28  14: 07:43 
// 			if (m_vecINFOLog.size() >= MAX_LOG_NUM)
// 			{
// 				if (m_iINFOLogOffset < MAX_LOG_NUM)
// 				{
// 					m_vecINFOLog[m_iINFOLogOffset++] = strRecord;
// 				}
// 				else
// 				{
// 					m_vecINFOLog[0] = strRecord;
// 					m_iINFOLogOffset = 1;
// 				}
// 			}
// 			else
// 			{
// 				m_vecINFOLog.push_back(strRecord);
// 				++m_iINFOLogOffset;
// 			}

		}break;
	case Log_Type_Warning:
		{
			if (m_vecWARNINGLog.size() >= MAX_LOG_NUM)
			{
				if (m_iWARNINGLogOffset < MAX_LOG_NUM)
				{
					m_vecWARNINGLog[m_iWARNINGLogOffset++] = strRecord;
				}
				else
				{
					m_vecWARNINGLog[0] = strRecord;
					m_iWARNINGLogOffset = 1;
				}
			}
			else
			{
				m_vecWARNINGLog.push_back(strRecord);
				++m_iWARNINGLogOffset;
			}
		}break;
	case Log_Type_Error:
		{
			if (m_vecERRORLog.size() >= MAX_LOG_NUM)
			{
				if (m_iERRORLogOffset < MAX_LOG_NUM)
				{
					m_vecERRORLog[m_iERRORLogOffset++] = strRecord;
				}
				else
				{
					m_vecERRORLog[0] = strRecord;
					m_iERRORLogOffset = 1;
				}
			}
			else
			{
				m_vecERRORLog.push_back(strRecord);
				++m_iERRORLogOffset;
			}
		}break;
	case Log_Type_Fatal:
		{
//change by xxj 2015/07/28  14: 38:20 
// 			if (m_vecFATALLog.size() >= MAX_LOG_NUM)
// 			{
// 				if (m_iFATALLogOffset < MAX_LOG_NUM)
// 				{
// 					m_vecFATALLog[m_iFATALLogOffset++] = strRecord;
// 				}
// 				else
// 				{
// 					m_vecFATALLog[0] = strRecord;
// 					m_iFATALLogOffset = 1;
// 				}
// 			}
// 			else
// 			{
// 				m_vecFATALLog.push_back(strRecord);
// 				++m_iFATALLogOffset;
// 			}
		}break;
	case Log_Type_Fucking:
		{
			if (m_vecFUCKINGLog.size() >= MAX_LOG_NUM)
			{
				if (m_iFUCKINGLogOffset < MAX_LOG_NUM)
				{
					m_vecFUCKINGLog[m_iFUCKINGLogOffset++] = strRecord;
				}
				else
				{
					m_vecFUCKINGLog[0] = strRecord;
					m_iFUCKINGLogOffset = 1;
				}
			}
			else
			{
				m_vecFUCKINGLog.push_back(strRecord);
				++m_iFUCKINGLogOffset;
			}
		}break;
	case Log_Type_Others:
		{
			if (m_vecOTHERSLog.size() >= MAX_LOG_NUM)
			{
				if (m_iOTHERSLogOffset < MAX_LOG_NUM)
				{
					m_vecOTHERSLog[m_iOTHERSLogOffset++] = strRecord;
				}
				else
				{
					m_vecOTHERSLog[0] = strRecord;
					m_iOTHERSLogOffset = 1;
				}
			}
			else
			{
				m_vecOTHERSLog.push_back(strRecord);
				++m_iOTHERSLogOffset;
			}
		}break;
	}
	return 0;
}

void CLogBase::InitLogTag()
{
	m_Log_Tag.push_back("[INFO]");
	m_Log_Tag.push_back("[WARNING]");
	m_Log_Tag.push_back("[ERROR]");
	m_Log_Tag.push_back("[FATAL]");
	m_Log_Tag.push_back("[FUCKING]");
	m_Log_Tag.push_back("[OTHERS]");

	m_iINFOLogOffset = 0;
	m_iWARNINGLogOffset = 0;
	m_iERRORLogOffset = 0;
	m_iFATALLogOffset = 0;
	m_iFUCKINGLogOffset = 0;
	m_iOTHERSLogOffset = 0;

	m_iINFOWriteOffset = 0;
	m_iWARNINGWriteOffset =0;
	m_iERRORWriteOffset = 0;
	m_iFATALWriteOffset = 0;
	m_iFUCKINGWriteOffset = 0;
	m_iOTHERSWriteOffset = 0;

}