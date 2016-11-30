#include "TestMgr.h"
#include "..\GameBase\Common\GameUtils.h"
#if _MEMORY_DEBUG
#include "./debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

TestMgr::TestMgr(ACE_UINT32 unID)
:BaseAdapter(unID)
{
}

TestMgr::~TestMgr()
{

}

BaseObj *TestMgr::new_child_obj(ACE_UINT32 unID)
{
	return new BaseObj(unID, this);
}

void TestMgr::service_obj_timer_callback()
{
	printf("test mgr children count = %d\n", this->m_objMap.current_size());

	ACE_Time_Value v = ACE_OS::gettimeofday();
	ACE_UINT64 t0 = 0;
	ACE_UINT64 t1;
	v.to_usec(t0);

	BaseAdapter::service_obj_timer_callback();

	v = ACE_OS::gettimeofday();
	v.to_usec(t1);

	t1 = t1 - t0;

	printf("test mgr timeout callback,duration = %d\n", (int)t1);
}