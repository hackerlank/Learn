#pragma once

#include "ace\ace.h"
#include "BaseModule.h"

class WingMgr:public BaseModule
{
public:
	WingMgr();
	~WingMgr();

	WingItemInfo m_list[MAX_WING_LIST];
	ACE_UINT32 m_unCount;

	void init(ACE_UINT32 unCount, WingItemInfo *list);//格子次数，刷新次数，上次刷新时间，物品列表 

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN,int result = 0);

	void update_2_db();

};