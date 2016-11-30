#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "ace\Singleton.h"
#include "..\..\GameBase\res\ActivityRes.h"

#define MAX_ONLINE_ACTIVITY 32

#define MAX_ACTIVITY_RELATED_ID_PER_TYPE 128

typedef struct tagOnlineActivityInfo
{
	bool isStart;
	ActivityRes *res;
}OnlineActivityInfo;

typedef struct tagActivityItemInfo
{
	bool bOnline;
	OnlineActivityInfo *activity;
}ActivityItemInfo;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, ActivityItemInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> ACTIVITY_ITEM_MAP;
typedef ACTIVITY_ITEM_MAP::ITERATOR ACTIVITY_ITEM_MAP_ITERATOR;

enum
{
	ACTIVITY_STATUS_NONE = 0,
	ACTIVITY_STATUS_ONLINE,
	ACTIVITY_STATUS_OFFLINE
};

class ActivityMgr : public BaseModule
{
public:
	ActivityMgr();
	~ActivityMgr();

	void init();
	virtual void update(ACE_UINT32 unCurrentTime);

	bool is_activity(ACE_UINT32 unID);
	int get_status(ACE_UINT32 unID, ACE_UINT32 unCurrentTime, ACE_UINT32 unTimes);

	ACE_UINT32 m_unTimer;

private:
	ACTIVITY_ITEM_MAP m_itemMap;


	ACE_UINT32 m_unOnlineActivityCount;

	OnlineActivityInfo m_onlineActivityList[MAX_ONLINE_ACTIVITY];
};

typedef ACE_Singleton<ActivityMgr, ACE_Thread_Mutex> ACTIVITY_MGR_INSTANCE;