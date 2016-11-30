#include "DBLoginMgr.h"
#include "..\Base\Service\ServiceConfigMgr.h"

//#define MAX_DB_HANDLER 100
#if _MEMORY_DEBUG
#include "../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

DBLoginMgr::DBLoginMgr(ACE_UINT32 unID)
:DBHandlerMgr(unID)
{
}

DBLoginMgr::~DBLoginMgr()
{

}

BaseObj *DBLoginMgr::new_child_obj(ACE_UINT32 unID)
{
	return new DBLoginHandler(unID, this);
}