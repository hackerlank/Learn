#include "BaseEvent.h"
#include "ace\OS_NS_string.h"

BaseEvent::BaseEvent(char *name)
{
	ACE_OS::strncpy(m_name, name, MAX_EVENT_NAME_LEN);
	m_name[MAX_EVENT_NAME_LEN] = '\0';
}

BaseEvent::~BaseEvent()
{

}