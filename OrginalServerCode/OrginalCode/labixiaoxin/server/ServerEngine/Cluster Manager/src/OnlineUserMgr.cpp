#include "OnlineUserMgr.h"
#include "OnlineUser.h"

OnlineUserMgr::OnlineUserMgr()
:BaseAdapter(ADAPTER_ONLINE_USER)
{

}

OnlineUserMgr::~OnlineUserMgr()
{

}

int OnlineUserMgr::dealMsg(MessageInfo &msgInfo)
{
	if(msgInfo.m_head->unType == MSG_LOGIN_REQUEST)
	{
		OnlineUser *userObj;
		BaseObj *obj;
		MsgLoginRequest *body = (MsgLoginRequest *)msgInfo.body;

		if(m_objMap.find(body->unID, obj) == 0)
		{
			userObj = (OnlineUser *)obj;
		}
		else
		{
			userObj = new OnlineUser(body->unID, this);

			if(userObj == NULL)
			{
				return 0;
			}

			if(this->addChild(userObj) == -1)
			{
				delete userObj;
				return 0;
			}
		}
	}

	return 0;
}