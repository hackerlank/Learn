#pragma once

#include "..\GameBase\Common\GameService.h"

/*
负责管理几个地图，维护每一个地图的家的数据，包括是否有人占领，如果占领的话，保存一些基本信息

*/

class MapService : public GameService
{
public:
	MapService();
	~MapService();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);

	virtual int get_service_info_msg(char *buff, int nMaxSize);

	virtual int start_running();
	virtual int deal_msg(MessageInfo &msgInfo);
	virtual void obj_timeout();

private:
	void get_character_id_list();
	void do_character_db_update(ACE_UINT32 unCount, ACE_UINT32 *list);

	
	ACE_UINT32 m_unLastUpdateID;
	ACE_UINT32 m_unCurrentUpdateID;
	bool m_bUpdateDone;
	ACE_UINT32 m_unUserInfoServerID;
	
};