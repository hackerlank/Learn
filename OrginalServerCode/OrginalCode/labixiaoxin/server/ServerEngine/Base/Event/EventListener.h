#pragma once

#include "BaseEvent.h"

#define MAX_EVENT_POOL 8

class EventListener
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handle_event(BaseEvent *e) = 0;
};