#include "MapService.h"
#include "MapMgr.h"
#include "module/LuckMgr.h"
//#include "module/GlobalLootMgr.h"
#include "module/GlobalInfoMgr.h"
#include "module/ActivityMgr.h"
#include "module/CooldownMgr.h"

#define MAX_CHARACTER_PER_QUERY 1

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


MapService::MapService()
{
	m_bUpdateDone = true;
	m_unCurrentUpdateID = 0;
	m_unLastUpdateID = 100000000;
	m_unUserInfoServerID = 0;
}

MapService::~MapService()
{

}

int MapService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	int ret = GameService::obj_init(arg, unArgLen);

	if(ret == -1)
	{
		return -1;
	}

	MapMgr *mapMgr = new MapMgr(ADAPTER_MAP_MGR);

	if(mapMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(mapMgr) == -1)
	{
		delete mapMgr;
		return -1;
	}

	LUCK_MGR_INSTANCE::instance()->init();
	//GLOBAL_LOOT_MGR_INSTANCE::instance()->init();
	GLOBAL_INFO_MGR_INSTANCE::instance()->init();
	ACTIVITY_MGR_INSTANCE::instance()->init();
	//LimitMgr::init_limit_info();

	return 0;
}

int MapService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;

	int c = 0;

	BaseAdapter *adapter = this->getAdapter(ADAPTER_MAP_MGR);

	if(adapter != NULL)
	{
		c = adapter->get_obj_count();
	}

	char tmp[1024];
	ACE_OS::sprintf(tmp, "I'am Map Server!\nCharacter loaded count = %d", c);

	len = add_service_info_msg(buff, 0, nMaxSize, tmp);

	return len;
}

int MapService::start_running()
{


	//get_character_id_list();

	return GameService::start_running();
}

int MapService::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_GET_CHARACTER_ID_LIST_RESPONSE:
			{
				MsgGetCharacterIDListResponse *body = (MsgGetCharacterIDListResponse *)msgInfo.body;

				this->do_character_db_update(body->unCount, body->list);

				//m_bUpdateDone = true;

				if(body->unCount < MAX_CHARACTER_PER_QUERY )
				{
					m_bUpdateDone = true;
					printf("update done\n");
				}

				if(body->unCount > 0)
				{
					m_unCurrentUpdateID = body->list[body->unCount - 1];

				}

				//printf("character count = %d, last id = %d\n", body->unCount, m_unCurrentUpdateID);

				//get_character_id_list();

			}
			break;
		}
	}

	return GameService::deal_msg(msgInfo);
}

void MapService::obj_timeout()
{
	GameService::obj_timeout();

	if(this->m_unObjStatus == SERVICE_OBJ_RUN)
	{
		get_character_id_list();
	}
}

void MapService::get_character_id_list()
{
	if(m_bUpdateDone)
	{
		return;
	}

	if(m_unLastUpdateID == m_unCurrentUpdateID)
	{
		return;
	}

	if(m_unUserInfoServerID == 0)
	{
		m_unUserInfoServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Test User Info Server");
		/*
		MsgGetCharacterIDListRequest request;
		request.unCurrentID = m_unCurrentUpdateID;
		request.unMaxCount = 0;
		this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_CHARACTER_ID_LIST_REQUEST, (char *)&request, sizeof(MsgGetCharacterIDListRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
		*/
	}

	m_unLastUpdateID = m_unCurrentUpdateID;

	MsgGetCharacterIDListRequest request;
	request.unCurrentID = m_unCurrentUpdateID;
	request.unMaxCount = MAX_CHARACTER_PER_QUERY;

	this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_CHARACTER_ID_LIST_REQUEST, (char *)&request, sizeof(MsgGetCharacterIDListRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
}

void MapService::do_character_db_update(ACE_UINT32 unCount, ACE_UINT32 *list)
{
	int i;

	for(i = 0;i < unCount;i ++)
	{
		//printf("map id = 0x%08x\n", list[i]);
		sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_CHARACTER_UPDATE_DATA_REQUEST, NULL, 0, OBJ_ID_NONE, ADAPTER_MAP_MGR, list[i]);
	}
}