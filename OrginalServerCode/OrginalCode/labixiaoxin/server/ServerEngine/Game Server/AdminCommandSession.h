#pragma once

#include "..\Base\Service\BaseObj.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include "..\DB Server\LogDefine.h"

class AdminCommandSession : public BaseObj
{
public:
	AdminCommandSession(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~AdminCommandSession();


	virtual int deal_msg(MessageInfo &msgInfo);
	virtual int deal_db_msg(ACE_UINT32 unType, void *msg);

	virtual void obj_timeout();
	virtual int start_destroy();

	ACE_Message_Block *parse_into_internet_msg(MessageInfo &msgInfo);

private:
	int deal_client_msg(MessageInfo &msgInfo);//处理分发消息
	int send_msg_2_internet(const char *str);
	int send_msg_2_internet(ACE_Message_Block *msg);
	void send_fail_msg(int errorCode);
	bool is_service_on(ACE_UINT32 unServiceID);
	void GetLogInfoItemJson(const LogItemInfo & logInfo,Json::Value & root);

	ACE_UINT32 m_unLiveCounter;
	static ACE_UINT32 m_unUserInfoServerID;
};