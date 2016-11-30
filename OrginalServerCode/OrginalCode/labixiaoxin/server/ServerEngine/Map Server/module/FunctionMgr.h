#pragma once

#include "ace\ace.h"
#include "BaseModule.h"

class FunctionMgr : public BaseModule
{
public:
	FunctionMgr();
	~FunctionMgr();

	void init(ACE_UINT32 *list);
	virtual void update(ACE_UINT32 unCurrentTime);

	virtual void send_info(ObjAdr &targetAdr, ACE_UINT32 unSN);

	void unlock(ACE_UINT32 unID);

	bool is_locked(ACE_UINT32 unID);

	ACE_UINT32 m_unLockedCount;
	ACE_UINT32 m_functionList[MAX_FUNCTION_COUNT];
private:
	void update_2_db();
};