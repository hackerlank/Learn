#pragma once

/*
1.管理所有的sub adapter(注册，注销)
2.处理sub adater下的obj添加和删除消息
*/
#include "ace\ace.h"
#include "ace\Singleton.h"

class LoggerClient
{
public:
	LoggerClient();
	~LoggerClient();

	void init();

	void log(char *fmtStr, ...);



private:
	ACE_UINT32 m_unGameServerID;

	void send_2_server(char *str);

};

typedef ACE_Singleton<LoggerClient, ACE_Thread_Mutex> LOGGER_CLIENT_INSTANCE;