#pragma once

#define MAX_EVENT_NAME_LEN 32

class BaseEvent
{
public:
	BaseEvent(char *name);
	virtual ~BaseEvent();

	char m_name[MAX_EVENT_NAME_LEN + 1];
};