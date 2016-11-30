#pragma once

#include "ace\ace.h"
#include "BaseModule.h"

class SecretMgr:public BaseModule
{
public:
	SecretMgr();
	~SecretMgr();

	SecretItemInfo m_list[MAX_SECRET_LIST];  //物品的id和个数
	ACE_UINT32 m_unCellCount;//当前拥有格子数
	ACE_UINT32 m_refreshTimes;//刷新次数
	ACE_UINT32 m_unLastRefreshTime;//上次刷新的时间戳

	ACE_UINT32 m_unPaidRefreshPrice; //本次付费刷新价格
	
	void init(ACE_UINT32 unCellCount,ACE_UINT32 refreshTimes,ACE_UINT32 lastRefreshTime,SecretItemInfo *list);//格子次数，刷新次数，上次刷新时间，物品列表 
	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN,int result = 0);


	void update_2_db();

};