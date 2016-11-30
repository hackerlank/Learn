#pragma once

#include "ace\ace.h"
#include "ace\Singleton.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"

/*
typedef struct tagPropertyBuffData
{
	ACE_UINT32 unPropertyID;
	float baseValue;
	float scaleValue;
}PropertyBuffData;

typedef struct tagPropertyBuffList
{
	ACE_UINT32 unCount;
	PropertyBuffData list[MAX_PROPERTY_COUNT];
}PropertyBuffList;
*/

#define MAX_LOOT_IGNORE 32

class LootMgr : public BaseModule, public EventListener
{
public:
	LootMgr();
	~LootMgr();

	virtual void handle_event(BaseEvent *e);

	ACE_UINT32 loot(DropGroup &group, int nCount);

private:
	//ACE_UINT32 m_ignoreList[MAX_LOOT_IGNORE];
	//ACE_UINT32 m_unCount;
};
