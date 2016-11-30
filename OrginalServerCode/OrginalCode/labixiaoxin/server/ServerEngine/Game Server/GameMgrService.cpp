#include "GameMgrService.h"
#include "GameServerMgr.h"
#include "ServerCommandEndPoint.h"
#include "AdminCommandMgr.h"
#include "TestMgr.h"
#include "..\GameBase\Common\GameUtils.h"

#include "..\Base\TimerMgr\TimerMgr.h"

#include "..\GameBase\Logger\LoggerClient.h"

#include "..\GameBase\Logger\LoggerServerMgr.h"

#include "..\GameBase\res\BaseRes.h"

#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif


GameMgrService::GameMgrService()
{

}

GameMgrService::~GameMgrService()
{

}

int GameMgrService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	/*
	ACE_UINT32 unTmpID = 0x8c200013;

	unTmpID = ACE_OS::strtol("0xc200013", NULL, 16);

	unTmpID = unTmpID + (ITEM_RES_TYPE_HANDBOOK_OFFSET << 24);

	unTmpID = GameUtils::parse_res_id("8c200013");
	unTmpID = GameUtils::parse_res_id("1c200013");
	unTmpID = GameUtils::parse_res_id("c200013");
	*/
	//int t = GameUtils::get_week(GameUtils::get_utc());

	GameServerMgr *gameServerMgr = new GameServerMgr(ADAPTER_GAME_SERVER_MGR);

	if(gameServerMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(gameServerMgr) == -1)
	{
		delete gameServerMgr;
		return -1;
	}

	AdminCommandMgr *adminCommandMgr = new AdminCommandMgr(ADAPTER_ADMIN_COMMAND_MGR);

	if(adminCommandMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(adminCommandMgr) == -1)
	{
		delete adminCommandMgr;
		return -1;
	}

	LoggerServerMgr *loggerServerMgr = new LoggerServerMgr(ADAPTER_LOGGER_SERVER_MGR);

	if(loggerServerMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(loggerServerMgr) == -1)
	{
		delete loggerServerMgr;
		return -1;
	}

	BaseEndPoint *endpoint = new ServerCommandEndPoint(this->msg_queue(), m_ownServiceInfo->wlanAdr.ip, m_ownServiceInfo->wlanAdr.port);

	if(endpoint == NULL)
	{
		return -1;
	}

	//((ClientEndPoint *)endpoint)->set_listen_addr("192.168.1.11", 1500);
	

	if(COMMUNICATION_MGR_INSTANCE::instance()->addEndpoint(endpoint) == -1)
	{
		delete endpoint;
		return -1;
	}

	return GameService::obj_init(arg, unArgLen);
}

int GameMgrService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;
	len = add_service_info_msg(buff, 0, nMaxSize, "I'am Game Server!");
	return len;
}