#pragma once

#include "DBHandler.h"
#include "LogDefine.h"

class DBLoginHandler : public DBHandler
{
public:
	DBLoginHandler(ACE_UINT32 unID, BaseAdapter *parent);

	virtual void do_db_load(Connection *db_conn);
	virtual void do_db_request(Connection *db_conn, MessageInfo &msgInfo);
	virtual void update_cache(MessageInfo &msgInfo);

	//virtual void obj_timeout();
	
private:
	ACE_UINT32 get_user_id(Connection *db_conn, char *mac, char *email, ACE_UINT32 unUserID);
	int create_character(Connection *db_conn, ACE_UINT32 unUserID);
	//void SendLogInfoItemMSG(LogItemInfo & ver,ACE_UINT32 unUserID);//日志系统发送一条日志信息

	ACE_UINT32 m_unLiveCounter;
};