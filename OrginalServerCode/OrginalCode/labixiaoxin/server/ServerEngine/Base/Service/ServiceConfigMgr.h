#pragma once

#include "..\Utils\ConfigLoader.h"
#include "ace\Singleton.h"

typedef struct tagConfigAddress
{
	char ip[32];
	int port;
}ConfigAddress;

#define MAX_SERVICE_INFO_NAME 32

typedef struct tagServiceDefineInfo
{
	char name[MAX_SERVICE_INFO_NAME + 1];
	ACE_UINT32 unID;
	bool isServiceMgr;
}ServiceDefineInfo;

typedef struct tagServiceInstanceInfo
{
	char name[MAX_SERVICE_INFO_NAME + 1];
	ACE_UINT32 unID;
	ConfigAddress lanAdr;
	ConfigAddress wlanAdr;
	ConfigAddress publicAdr;
	bool isServiceMgr;
}ServiceInstanceInfo;

#define MAX_SERVICE_DEFINE 16
#define MAX_SERVICE_INSTANCE 32

#define MAX_DB_NAME 32
#define MAX_DB_HOST 32
#define MAX_DB_USER_NAME 32
#define MAX_DB_PASSWORD_NAME 32

typedef struct tagDatabaseInfo
{
	char name[MAX_DB_NAME + 1];
	char host[MAX_DB_HOST + 1];
	char user[MAX_DB_USER_NAME + 1];
	char password[MAX_DB_PASSWORD_NAME + 1];
}DatabaseInfo;

class ServiceConfigMgr : public ConfigLoader
{
public:
	ServiceConfigMgr();
	virtual ~ServiceConfigMgr();

	virtual int deal_config(int config_id, xmlNodePtr rootNode);

	ACE_UINT32 get_service_define_id(char *defineName);
	ACE_UINT32 get_service_instance_id(char *instanceName);
	ServiceInstanceInfo *get_service_instance(char *instanceName);
	ServiceInstanceInfo *get_service_instance(ACE_UINT32 unServiceID);

	ConfigAddress m_multicastAdr;

	ServiceDefineInfo m_serviceDefineList[MAX_SERVICE_DEFINE];
	ACE_UINT32 m_unServiceDefineCount;
	ServiceInstanceInfo m_serviceInstanceList[MAX_SERVICE_INSTANCE];
	ACE_UINT32 m_unServiceInstanceCount;

	DatabaseInfo m_dbInfo;
	DatabaseInfo m_dblogInfo;//xxj 2015/04/26 16:03:53 日志文件数据库

	ACE_UINT32 m_unServiceMgrID;
	ACE_UINT32 m_unServiceMgrIP;
	ACE_UINT32 m_unServiceMgrPort;
	ACE_UINT32 m_unServiceMgrTypeID;
private:
	void parse_address(xmlNodePtr rootNode, ConfigAddress &adr,bool isZone = false);
	void parse_database(xmlNodePtr rootNode);
	void parse_database_log(xmlNodePtr rootNode);//xxj 2015/04/26 16:13:30 日志数据信息
	void parse_service_define_list(xmlNodePtr rootNode);
	void parse_service_define(xmlNodePtr rootNode, ServiceDefineInfo &info);
	void parse_service_instance_list(xmlNodePtr rootNode);
	void parse_service_instance(xmlNodePtr rootNode, ServiceInstanceInfo &info);
public:
	static int zone;
};

typedef ACE_Singleton<ServiceConfigMgr, ACE_Thread_Mutex> SERVICE_CONFIG_MGR_INSTANCE;