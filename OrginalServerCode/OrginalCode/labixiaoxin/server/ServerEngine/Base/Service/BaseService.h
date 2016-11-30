#pragma once

#include "ace\ace.h"
#include "ace\Task.h"
#include "ace\Sig_Handler.h"
#include "..\Protocol\Protocol.h"
#include "Service_Config.h"
#include "ServiceObj.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "BaseAdapter.h"
#include "ServiceMsgCtrl.h"
#include "ServiceConfigMgr.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "../Log/LogBase.h"

#include "..\Utils\StdinHandler.h"


typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, BaseAdapter *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> ACTIVE_ADAPTER_MAP;
typedef ACTIVE_ADAPTER_MAP::ITERATOR ACTIVE_ADAPTER_MAP_ITERATOR;

typedef struct tagObjLocationInfo
{
	ACE_UINT32 unServiceID;
	ACE_UINT32 unTimeStamp;
}ObjLocationInfo;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT64, ObjLocationInfo *, ACE_Hash<ACE_UINT64>, 
ACE_Equal_To<ACE_UINT64>, ACE_Null_Mutex> OBJ_LOCATION_MAP;
typedef OBJ_LOCATION_MAP::ITERATOR OBJ_LOCATION_MAP_ITERATOR;

#define MAX_ADAPTER_COUNT 64

class BaseService : public ACE_Task<ACE_MT_SYNCH>, public ServiceObj
{
public:
	static ACE_UINT32 g_msg_count;
	static ACE_UINT32 g_msg_time;
	// ACE_Message_Queue<ACE_MT_SYNCH> m_deleteQue;

	enum
	{
		SERVICE_STATUS_STARTUP = 0,
		SERVICE_STATUS_NORMAL,
		SERVICE_STATUS_SHUTDOWN
	};

	BaseService();
	virtual ~BaseService();

	virtual void obj_fini();

	static BaseService *instance();
	static ACE_UINT32 getServiceDaemonID();
	static ACE_UINT32 getServiceDaemonID(ACE_UINT32 unIP);

	static CLogBase *GetLogInstance();

	int Startup(int argc, ACE_TCHAR **argv);
	//int Startup(ACE_UINT32 unServiceID, ACE_UINT32 unServicePort, ACE_UINT32 bServiceMgr);
	int Startup(char *serviceName);
	int Startup_i();
	void Shutdown();

	virtual void quit_service();

	virtual void deal_console_cmd(char *pCmd);

	int addAdapter(BaseAdapter *obj, void *arg = NULL, ACE_UINT32 unArgLen = 0);
	void removeAdapter(ACE_INT32 unAdapterID);
	void removeAllAdapter();
	BaseAdapter *getAdapter(ACE_INT32 unAdapterID);
	

	//virtual int service_init();
	//virtual void service_fini();
	void load_config(char *config);

	virtual int svc(void);
	virtual int close(u_long flags = 0);
	virtual int put (ACE_Message_Block *, ACE_Time_Value * = 0);

	ACE_UINT32 serviceID();
	ACE_UINT32 servicePort();
	void servicePort(ACE_UINT32 unPort);

	virtual int obj_msg_callback(MessageInfo &msgInfo);

	virtual void service_obj_timer_callback();

	virtual void setAddr(ObjAdr &addr);

	virtual bool should_destroy();
	//virtual bool hasDestoryed();

	ServiceObj *findServiceObj(ObjAdr &adr);

	ServiceInstanceInfo *m_ownServiceInfo;
	
protected:
	bool m_bStopService;
	ACTIVE_ADAPTER_MAP m_adapterMap;

private:

	int startDefaultTimer();
	void stopDefaultTimer();
	
	
	//void sendObjNotFoundMsg(MessageInfo &msgInfo);
	//void sendObjReachedMsg(MessageInfo &msgInfo);

	void send_msg_obj_reach_result(ACE_UINT32 unType, ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ObjAdr &desAdr, ACE_UINT32 unPacketNo);

	int start_reator();
	void end_reator();

	void stop_service();

	int m_nReactorThreadID;

	static ACE_THR_FUNC_RETURN activateReactor(void *opParam);

	static ACE_THR_FUNC_RETURN activateLogThread(void *opParam);
	
	static BaseService *m_instance;

	ACE_UINT32 m_unServicePort;
	ACE_UINT32 m_bServiceMgr;
	ACE_UINT32 m_unServiceStatus;

	BaseTimerHandler *m_serviceDefaultTimerHandler;

	StdinHandler m_StdinHandler;

	bool is_stop();
	void set_stop_flag(bool flag);

	bool m_bStopFlag;

	

	ACE_Recursive_Thread_Mutex m_mutex;

	static CLogBase *m_pLogService;

public:
	static ACE_UINT32 g_OnlineCount;//在线人数
};