#include "DBService.h"
#include "DBHomeMgr.h"
#include "DBLoginMgr.h"
#include "DBUserMgr.h"
#include "DBAccessMgr.h"

#if _MEMORY_DEBUG
#include "./debugnew.h"
DebugNewTracer DebugNewTrace;
#define new new(__FILE__, __LINE__)
#endif

DBService::DBService()
{

}

DBService::~DBService()
{

}

int DBService::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	if(GameService::obj_init(arg, unArgLen) == -1)
	{
		return -1;
	}

	//DBUserHandler::init_weapon_skill_list();
	if(DB_ACCESS_MGR_INSTANCE::instance()->init() == -1)
	{
		return -1;
	}

// 	if (DB_LOG_MGR_INSTANCE::instance()->init(this) == -1)
// 	{
// 		return -1;
// 	}

	SubAdapter *dbMgr = new DBHomeMgr(ADAPTER_DB_HOME_MGR);

	if(dbMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(dbMgr) == -1)
	{
		delete dbMgr;
		return -1;
	}

	dbMgr = new DBLoginMgr(ADAPTER_DB_LOGIN_MGR);

	if(dbMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(dbMgr) == -1)
	{
		delete dbMgr;
		return -1;
	}

	dbMgr = new DBUserMgr(ADAPTER_DB_USER_MGR);

	if(dbMgr == NULL)
	{
		return -1;
	}

	if(this->addAdapter(dbMgr) == -1)
	{
		delete dbMgr;
		return -1;
	}

	return 0;
}

void DBService::obj_fini()
{
	GameService::obj_fini();

	DB_ACCESS_MGR_INSTANCE::instance()->fini();
}

int DBService::get_service_info_msg(char *buff, int nMaxSize)
{
	int len = 0;

	int c0 = 0;
	int c1 = 0;
	int c2 = 0;

	char tmp[1024];

	DBHomeMgr *dbHomeMgr = (DBHomeMgr *)getAdapter(ADAPTER_DB_HOME_MGR);
	DBLoginMgr *dbLoginMgr = (DBLoginMgr *)getAdapter(ADAPTER_DB_LOGIN_MGR);
	DBUserMgr *dbUserMgr = (DBUserMgr *)getAdapter(ADAPTER_DB_USER_MGR);

	if(dbHomeMgr == NULL)
	{
		c0 = 0;
	}
	else
	{
		c0 = dbHomeMgr->m_unDBRequestCount;
	}

	if(dbLoginMgr == NULL)
	{
		c1 = 0;
	}
	else
	{
		c1 = dbLoginMgr->m_unDBRequestCount;
	}

	if(dbUserMgr == NULL)
	{
		c2 = 0;
	}
	else
	{
		c2 = dbUserMgr->m_unDBRequestCount;
	}

	ACE_OS::sprintf(tmp, "home db request = %d,login db request = %d,user db request = %d", c0, c1, c2);

	len = add_service_info_msg(buff, 0, nMaxSize, tmp);

	if(dbHomeMgr == NULL)
	{
		c0 = 0;
	}
	else
	{
		c0 = dbHomeMgr->get_obj_count();
	}

	if(dbLoginMgr == NULL)
	{
		c1 = 0;
	}
	else
	{
		c1 = dbLoginMgr->get_obj_count();
	}

	if(dbUserMgr == NULL)
	{
		c2 = 0;
	}
	else
	{
		c2 = dbUserMgr->get_obj_count();
	}

	ACE_OS::sprintf(tmp, "home obj = %d,login obj = %d,user obj = %d", c0, c1, c2);

	len = add_service_info_msg(buff, len, nMaxSize, tmp);

	return len;
}