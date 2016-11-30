#pragma once

#include "..\..\Base\Event\BaseEvent.h"
#include "ace\ace.h"

class MapEvent : public BaseEvent
{
public:
	MapEvent(char *name, ACE_UINT32 unResID, ACE_UINT32 unCount);

	ACE_UINT32 m_unResID;
	//ACE_UINT32 m_unSubType;
	ACE_UINT32 m_unCount;
};