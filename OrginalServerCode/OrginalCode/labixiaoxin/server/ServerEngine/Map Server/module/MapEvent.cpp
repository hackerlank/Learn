#include "MapEvent.h"

MapEvent::MapEvent(char *name, ACE_UINT32 unResID, ACE_UINT32 unCount)
:BaseEvent(name)
{
	m_unResID = unResID;
	m_unCount = unCount;
}