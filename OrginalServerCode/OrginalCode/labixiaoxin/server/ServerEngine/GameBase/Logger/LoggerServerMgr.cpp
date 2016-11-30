#include "LoggerServerMgr.h"

#include "..\Protocol\ControlProtocol.h"

#include "..\Common\GameUtils.h"


LoggerServerMgr::LoggerServerMgr(ACE_UINT32 unID)
:BaseAdapter(unID)
{
	m_unLastFileTime = 0;
	m_fp = NULL;
}

LoggerServerMgr::~LoggerServerMgr()
{
	close_log_file();
}

int LoggerServerMgr::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	//open_log_file();

	return BaseAdapter::obj_init(arg, unArgLen);
}

int LoggerServerMgr::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_ADD_LOG_REQUEST:
			{
				MsgAddLogRequest *body = (MsgAddLogRequest *)msgInfo.body;

				//printf("%s\n", body->strLog);

				open_log_file();
				write_log(body->strLog);
				close_log_file();
			}
			
			break;
		}
		
	}

	return OBJ_DEAL_MSG_SUCCESS;
}

void LoggerServerMgr::close_log_file()
{
	if(m_fp == NULL)
	{
		return;
	}

	ACE_OS::fclose(m_fp);
	m_fp = NULL;
}

int LoggerServerMgr::open_log_file()
{
	ACE_UINT32 tmp = GameUtils::get_utc();

	if(m_fp != NULL)
	{
		if(GameUtils::get_day_different(tmp, m_unLastFileTime) <= 0)
		{
			return 0;
		}
		else
		{
			close_log_file();
		}
	}

	char file_name[64];
	char day_str[32];

	GameUtils::get_current_day_str(day_str);

	ACE_OS::sprintf(file_name, "loginfo1/log-%s.txt", day_str);

	m_fp = ACE_OS::fopen(file_name, "a");

	return 0;
}

void LoggerServerMgr::write_log(char *strLog)
{
	if(m_fp == NULL)
	{
		return;
	}

	ACE_OS::fprintf(m_fp, "%s\n", strLog);
}