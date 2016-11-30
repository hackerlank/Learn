#pragma once

#include "..\GameBase\Adapter\SubAdapterObj.h"
#include "ace\Semaphore.h"
#include "ace\Atomic_Op.h"
#include "ace\Thread_Mutex.h"
#include "ace\Condition_Thread_Mutex.h"

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/statement.h"   
#include "cppconn/prepared_statement.h"   
#include "cppconn/metadata.h"   
#include "cppconn/exception.h" 
//#include "ace\Thread.h"
//#include "ace\Synch.h"
//#include "ace\Condition_Thread_Mutex.h"

using namespace sql;

class DBDataBuf : public std::streambuf
{
public:
	DBDataBuf(char * d, size_t s) {
		setg(d, d, d + s);
	}
};

class DBHandler : public SubAdapterObj
{
public:
	DBHandler(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~DBHandler();

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	virtual int start_create();
	virtual int start_destroy();
	virtual bool hasCreated();
	virtual bool hasDestoryed();

	virtual int deal_msg(MessageInfo &msgInfo);

	virtual void do_db_load(Connection *db_conn) = 0;
	virtual void do_db_request(Connection *db_conn, MessageInfo &msgInfo) = 0;
	virtual void update_cache(MessageInfo &msgInfo) = 0;

	void do_db_msg(MessageInfo &msgInfo, char *send_buff);

	void cache_db_request(ACE_Message_Block *msg);

	void send_notify_msg();

	void wanna_remove_from_lru(){};
	void cancel_remove_from_lru(){};

	virtual bool should_destroy();

	bool m_bLoadingSuccess;

	bool m_bIsLoad;

	

	//ACE_Atomic_Op_Ex<ACE_Thread_Mutex, int> m_db_thread_flag;

protected:
	//ACE_Message_Block *m_msg;

	int add_load_msg();

// 	PreparedStatement *m_prep_stmt;
// 	ResultSet *m_db_res;

	char *db_send_buff;

	char m_strHandlerName[32];
	ACE_UINT32 m_unCurrentDBRequestType;

	void destroy_db_res(PreparedStatement *& _prep_stmt,ResultSet *& _db_res);
	//void destroy_db_res();
	int set_name(SQLString str, char *dest, int len);
private:
	ACE_Message_Queue<ACE_NULL_SYNCH> m_requestQueue;
	//static ACE_THR_FUNC_RETURN do_db_query(void *opParam);

	int next_db_request();
	void notify_free();

	bool has_db_request();

	void send_request_ack(ACE_UINT32 unType, ObjAdr &desAdr);

	bool m_bProcessDBRequest;
};