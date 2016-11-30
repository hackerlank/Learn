#pragma once

#include "..\GameBase\Adapter\SubAdapter.h"

#include "Map.h"

/*
管理所有的家,通过最近最少用原则，动态加载家的数据，家的数据有一个最大值,内存中的家作为cache，以提高访问速度
*/
//#define MAX_HOME_IN_CACHE 300

class MapMgr : public SubAdapter
{
public:
	MapMgr(ACE_UINT32 unID);
	virtual ~MapMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);
	virtual ACE_UINT32 get_register_service_id(){return m_unGameServerID;};
	virtual ACE_UINT32 get_register_adapter_id(){return ADAPTER_GAME_SERVER_MGR;};

	//virtual int deal_msg(MessageInfo &msgInfo);

	bool init_timer();

	void uninit_timer();

	static void DoubleDropTimerCallback(void *p, long lTimerID);
	void DoDoubleDropTimer();


	BaseTimerHandler *m_doubleDropTimerHandler;
private:
	ACE_UINT32 m_unGameServerID;
};