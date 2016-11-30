#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"

class UnlockMgr : public BaseModule, public EventListener
{
public:
	UnlockMgr();
	~UnlockMgr();

	void init();
	virtual void update(ACE_UINT32 unCurrentTime);

	virtual void handle_event(BaseEvent *e);

private:
	void update_2_db();

	static void init_unlock_data();
};