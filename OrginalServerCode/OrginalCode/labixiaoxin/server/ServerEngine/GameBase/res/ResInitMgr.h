#pragma once

#include "ace\Singleton.h"
#include "..\Common\GameDefine.h"

typedef struct tagResInitInfo
{
	bool isInited;
	ACE_UINT32 unCount;
	int size;
	void *data;
	void (*func)(tagResInitInfo *info);
}ResInitInfo;

enum
{
	RES_INIT_COOLDOWN = 0,
	RES_INIT_MAX
};

class ResInitMgr
{
public:
	ResInitMgr();
	~ResInitMgr();

	ResInitInfo *get_inited_res(int type);

	ResInitInfo m_list[RES_INIT_MAX];
};

typedef ACE_Singleton<ResInitMgr, ACE_Thread_Mutex> RES_INIT_MGR_INSTANCE;