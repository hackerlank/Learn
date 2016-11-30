#pragma 

#include "..\GameBase\Adapter\MainAdapter.h"
#define MAX_GameServer_SESSION_LIVE  10
/*
1.管理login
2.管理gateway
3.管理map server
4.管理db server
5.处理登录流程
*/

class GameServerMgr : public MainAdapter
{
public:
	GameServerMgr(ACE_UINT32 unID);
	virtual ~GameServerMgr();
// 	//在其他状态下调用的timeout
// 	virtual void obj_timeout();
// 	ACE_UINT32 m_unLiveCounter;

	//virtual BaseObj *new_child_obj(ACE_UINT32 unID);

	//virtual int deal_msg(MessageInfo &msgInfo);

private:
};