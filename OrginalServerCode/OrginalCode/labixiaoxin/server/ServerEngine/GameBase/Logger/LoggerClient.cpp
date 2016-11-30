#include "LoggerClient.h"
#include "ace\OS_NS_string.h"

#include "..\Common\GameUtils.h"

#include "..\..\Base\Service\ServiceConfigMgr.h"

#include "..\Protocol\ControlProtocol.h"

#include "..\..\Base\Service\BaseService.h"

#include "..\..\Base\Communication\CommunicationMgr.h"


char logger_tmp_str[8192];
char logger_time_str[64];

LoggerClient::LoggerClient()
{

}

LoggerClient::~LoggerClient()
{

}

void LoggerClient::init()
{
	m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
}

void LoggerClient::log(char *fmtStr, ...)
{
	//MsgAddLogRequest *body = (MsgAddLogRequest *)public_send_buff;

	va_list ap;
	va_start(ap, fmtStr);
	ACE_OS::vsprintf(logger_tmp_str, fmtStr, ap);
	va_end(ap);

	GameUtils::get_current_time_str(logger_time_str);

	ACE_OS::sprintf(public_send_buff, "[%s] %s", logger_time_str, logger_tmp_str);

	
	send_2_server(public_send_buff);
	
	//send_2_server(logger_tmp_str);

	//COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, &msgInfo.s_head->desAdr, msgInfo.msg);
}

void LoggerClient::send_2_server(char *str)
{
	int len = ACE_OS::strlen(str) + 1;

	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, len, SERVICE_MESSAGE_TYPE_SYSTEM, m_unGameServerID, ADAPTER_LOGGER_SERVER_MGR, OBJ_ID_NONE, BaseService::instance()->m_unID, OBJ_ID_NONE, OBJ_ID_NONE, MSG_ADD_LOG_REQUEST) == -1)
	{
		printf("no enough memory for send msg\n");
		return;
	}

	ACE_OS::memcpy(msgInfo.body, str, len);

	COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, &msgInfo.s_head->desAdr, msgInfo.msg);
}