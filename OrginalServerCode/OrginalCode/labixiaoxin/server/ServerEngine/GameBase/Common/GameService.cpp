#include "GameService.h"
#include "..\Protocol\ControlProtocol.h"

#include "..\res\ItemResMgr.h"
//#include "..\res\MapResMgr.h"
//#include "..\res\QuestResMgr.h"
#include "..\res\GameConfig.h"
#include "..\..\Base\Service\ServiceConfigMgr.h"

#include "..\Logger\LoggerClient.h"

//#define MAX_STATUS_BUFFER 512
//char gStatusReporterBuffer[MAX_STATUS_BUFFER];

GameService::GameService()
{
	/*
	for(int i = 0;i < MAX_REGISTER_CHILD_SERVICE_TYPE;i ++)
	{
		m_ChildServiceList[i].useFlag = 0;
	}
	*/
}

GameService::~GameService()
{

}

int GameService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	
	ACE_OS::srand((int)time(0));

	ObjAdr adr;
	adr.unServiceID = SERVICE_CONFIG_MGR_INSTANCE::instance()->m_unServiceMgrID;
	adr.unAdapterID = ADAPTER_GAME_SERVER_MGR;
	adr.unObjID = OBJ_ID_NONE;

	SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_MAP_MGR, adr, true);
	SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_GATEWAY_MGR, adr, true);
	//SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_LOGIN_MGR, adr);
	SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_DB_HOME_MGR, adr, true);
	SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_DB_LOGIN_MGR, adr, true);
	SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_DB_USER_MGR, adr, true);
	SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_DB_FRIEND_INFO_MGR, adr, true);
	//SERVICE_MSG_CTRL_INSTANCE::instance()->register_query_data(ADAPTER_PHP_PROXY_MGR, adr, false);

	int nRet = ITEM_RES_MGR_INSTANCE::instance()->load_all_config();

	if(nRet == -1)
	{
		//return -1;
	}

	if(GAME_CONFIG_INSTANCE::instance()->load_all_config() == -1)
	{

	}

	LOGGER_CLIENT_INSTANCE::instance()->init();

	//ITEM_RES_MGR_INSTANCE::instance()->process_res_by_name();

	return BaseService::obj_init(arg, unArgLen);
}

int GameService::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_SYSTEM)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_GET_SERVICE_STATUS_REQUEST:
			{
				MsgGetServiceStatusResponse response;
				response.unStatus = get_service_current_status();
				int len = get_service_info_msg(response.info, MAX_SERVICE_INFO_MSG_LEN);
				response.info[len] = '\0';

				this->sendMsg(SERVICE_MESSAGE_TYPE_SYSTEM, MSG_GET_SERVICE_STATUS_RESPONSE, (char *)&response, sizeof(MsgGetServiceStatusResponse), msgInfo.s_head->srcAdr);
			}
			break;
		}
	}

	return OBJ_DEAL_MSG_SUCCESS;
}

int GameService::get_service_info_msg(char *buff, int nMaxSize)
{
	buff[0] = '\0';
	return 0;
}

int GameService::add_service_info_msg(char *buff, int offset, int nMaxSize, char *str)
{
	int len = ACE_OS::strlen(str);

	if((offset + len + 1) > nMaxSize)
	{
		return -1;
	}

	ACE_OS::memcpy(&buff[offset], str, len);
	buff[offset + len] = '\n';

	return (offset + len + 1);
}

int GameService::get_service_current_status()
{
	if(m_bStopService)
	{
		if(m_adapterMap.current_size() == 0)
		{
			return SERVICE_STATUS_UNAVAILABLE;
		}

		return SERVICE_STATUS_CLOSING;
	}

	return SERVICE_STATUS_AVAILABLE;
}