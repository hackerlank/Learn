#pragma once

//#include "RootObj.h"
#include "..\Protocol\Protocol.h"
#include "..\Protocol\ServiceProtocol.h"
#include "Service_Config.h"
#include "ace\Containers.h"
#include "..\Utils\FixList.h"
#include "ace\Message_Queue.h"
#include "ace\Null_Condition.h"
#include "..\Task\ServiceTaskFactory.h"
#include "..\Event\BaseEvent.h"
#include "..\Event\EventListener.h"
#include "..\TimerMgr\TimerMgr.h"

class ServiceObj;


#define OBJ_ID_NONE 0x00

enum
{
	OBJ_DEAL_MSG_SUCCESS = 0,
	//OBJ_DEAL_MSG_PASS,
	OBJ_DEAL_MSG_REFUSE
};

typedef struct tagEventListenerInfo
{
	EventListener *listener;
}EventListenerInfo;

typedef ACE_DLList<EventListenerInfo> EVENT_LISTENER_LIST;
typedef ACE_DLList_Iterator<EventListenerInfo> EVENT_LISTENER_LIST_ITERATOR;

typedef ACE_Hash_Map_Manager_Ex<ACE_CString, EVENT_LISTENER_LIST *, ACE_Hash<ACE_CString>, 
ACE_Equal_To<ACE_CString>, ACE_Null_Mutex> EVENT_LISTENER_MAP;
typedef EVENT_LISTENER_MAP::ITERATOR EVENT_LISTENER_MAP_ITERATOR;

class ServiceObj
{
public:
	enum
	{
		SERVICE_OBJ_STATUS_NONE = -1,
		SERVICE_OBJ_CREATE,
		SERVICE_OBJ_RUN,
		SERVICE_OBJ_DESTROY
	};

	enum
	{
		SERVICE_OBJ_DB_REQUEST_DONE = 0,
		SERVICE_OBJ_DB_REQUEST_RETRY
	};

	virtual int obj_init(void *arg = NULL, ACE_UINT32 unArgLen = 0);
	virtual void obj_fini();

	ServiceObj(ACE_UINT32 unID);
	virtual ~ServiceObj();

	virtual void setAddr(ObjAdr &addr);
	
	int sendMsg(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ObjAdr &desAdr, ACE_UINT32 unPacketNo = 0, bool bQuery = true);
	int sendMsg(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ACE_UINT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unPacketNo = 0, bool bQuery = true);
	int forward_msg(MessageInfo &msgInfo, ACE_UINT32 unServiceID, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);

	int send_local_msg(ACE_UINT32 unMsgType, ACE_UINT32 unBodyType, char *strBody, ACE_UINT32 unBodyLen, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);

	int add_db_request(ACE_UINT32 unDBAdapter, ACE_UINT32 unType, char *pData, ACE_UINT32 unSize);

	int createTask(char *taskName, char *arg);
	void runTaskList();

	//定时器函数
	virtual void service_obj_timer_callback();

	//只有在loading状态调用的timeout
	//virtual void obj_loading_timeout(){};

	//在其他状态下调用的timeout
	virtual void obj_timeout(){};

	//消息处理函数,如果拒绝处理消息，返回OBJ_DEAL_MSG_REFUSE，那么Service会要求发送方重发，如果这个消息需要确保收到的话
	virtual int obj_msg_callback(MessageInfo &msgInfo);
	virtual int deal_msg(MessageInfo &msgInfo){return 0;};
	
	//service obj各状态的初始化
	//virtual int start_loading(){return 0;};
	virtual int start_create(){return 0;};
	virtual int start_running(){return 0;};
	virtual int start_destroy(){return 0;};

	virtual void create_done(){};
	virtual void destroy_done(){};

	virtual bool should_destroy(){return m_bDestroyFlag;};

	//是否已经创建成功
	virtual bool hasCreated(){return true;};
	//是否已经销毁完成
	virtual bool hasDestoryed(){return true;};

	//处理由DB Server返回的加载应答，返回0表示成功，返回-1表示失败
	virtual int deal_db_msg(ACE_UINT32 unType, void *msg){return SERVICE_OBJ_DB_REQUEST_DONE;};

	void setObjStatus(ACE_UINT32 unStatus);

	ACE_UINT32 m_unID;
	ACE_UINT32 m_unObjStatus;

	//除了缺省定时器，自定义定时器将会回调这个函数
	virtual void service_timer(long lTimerID);
	
	//激活一个新的定时器
	BaseTimerHandler *activateTimer(time_t sec, suseconds_t usec = 0);
	//停止一个定时器
	void deactivateTimer(BaseTimerHandler *timerHandler);

	bool has_obj_location_info(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	virtual int do_obj_location_query(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ObjAdr &srcAdr);
	int create_service_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, bool bForce = false);
	int destroy_service_obj(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, bool bRecreate = true);

	void add_event_listener(EventListener *listener, char *strEventName);
	void remove_event_listener(EventListener *listener, char *strEventName);
	void dispatcher_event(BaseEvent *e);

	virtual void set_destroy(bool flag){m_bDestroyFlag = flag;};

	ACE_UINT32 m_unCurrentSig;
	//ACE_CString
	//int create_service_obj(ServiceObjStatusInfo *pInfo);
protected:
	
	//bool m_bCreateWhenQueryFail;
	bool m_bNeedCreateStep;

	ACE_UINT32 m_unWaitDBAckCount;

	bool m_bDestroyFlag;

	void status_run();
	
private:

	//定时器管理器调用的函数
	static void service_obj_timer_func(void *owner, long lTimerID);

	void query_service_obj_location(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unFlag);
	void deal_create_service_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN);
	void deal_destroy_service_obj_result(int nResult, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID, ACE_UINT32 unSN);
	
	void objStatusChange();
	void dealTaskMsg(MessageInfo &msgInfo);

	//ACE_UINT32 nextDBSN();

	ACE_Double_Linked_List<ObjTaskInterface> m_TaskList;

	static ACE_UINT32 generateTaskID();

	static ACE_UINT32 m_TaskIDCursor;

	//ACE_UINT32 m_unDBSN;

	//如果该变量为false，那么不响应timeout，不响应消息
	bool m_bServiceObjActive;
	//int m_nLoadingTimer;
	
	ACE_UINT32 m_unNextObjStatus;

	EVENT_LISTENER_MAP m_listenerMap;
};