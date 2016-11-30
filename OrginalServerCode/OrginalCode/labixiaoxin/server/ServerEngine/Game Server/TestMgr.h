#pragma 

#include "..\Base\Service\BaseAdapter.h"
/*
1.管理login
2.管理gateway
3.管理map server
4.管理db server
5.处理登录流程
*/

class TestMgr : public BaseAdapter
{
public:
	TestMgr(ACE_UINT32 unID);
	virtual ~TestMgr();

	virtual BaseObj *new_child_obj(ACE_UINT32 unID);

	virtual void service_obj_timer_callback();
};