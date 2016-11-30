#include "DBUserMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"

//#define MAX_DB_HANDLER 100

#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

DBUserMgr::DBUserMgr(ACE_UINT32 unID)
:DBHandlerMgr(unID)
{
}

DBUserMgr::~DBUserMgr()
{
	
}

BaseObj *DBUserMgr::new_child_obj(ACE_UINT32 unID)
{
	return new DBUserHandler(unID, this);
}