#include "ServiceConfigMgr.h"
#include "ace\OS_NS_stdlib.h"
#include "ace\OS_NS_String.h"
#include "service_config.h"
#include "ace\INET_Addr.h"

int ServiceConfigMgr::zone = 0;


ServiceConfigMgr::ServiceConfigMgr()
{
	m_unServiceDefineCount = 0;
	m_unServiceInstanceCount = 0;
	m_unServiceMgrIP = 0;
}

ServiceConfigMgr::~ServiceConfigMgr()
{
}

ACE_UINT32 ServiceConfigMgr::get_service_define_id(char *defineName)
{
	for(ACE_UINT32 i = 0;i < m_unServiceDefineCount;i ++)
	{
		if(ACE_OS::strcmp(m_serviceDefineList[i].name, defineName) == 0)
		{
			return m_serviceDefineList[i].unID;
		}
	}

	return 0;
}

ACE_UINT32 ServiceConfigMgr::get_service_instance_id(char *instanceName)
{
	for(ACE_UINT32 i = 0;i < m_unServiceInstanceCount;i ++)
	{
		if(ACE_OS::strcmp(m_serviceInstanceList[i].name, instanceName) == 0)
		{
			return m_serviceInstanceList[i].unID;
		}
	}

	return 0;
}

ServiceInstanceInfo *ServiceConfigMgr::get_service_instance(char *instanceName)
{
	for(ACE_UINT32 i = 0;i < m_unServiceInstanceCount;i ++)
	{
		if(ACE_OS::strcmp(m_serviceInstanceList[i].name, instanceName) == 0)
		{
			return &m_serviceInstanceList[i];
		}
	}

	return NULL;
}

ServiceInstanceInfo *ServiceConfigMgr::get_service_instance(ACE_UINT32 unServiceID)
{
	for(ACE_UINT32 i = 0;i < m_unServiceInstanceCount;i ++)
	{
		if(m_serviceInstanceList[i].unID == unServiceID)
		{
			return &m_serviceInstanceList[i];
		}
	}

	return NULL;
}

int ServiceConfigMgr::deal_config(int config_id, xmlNodePtr rootNode)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"multicast") == 0)
		{
			parse_address(childNode, m_multicastAdr,true);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"database") == 0)
		{
			parse_database(childNode);
		} 
		else if (xmlStrcasecmp(childNode->name,BAD_CAST"database_log") == 0)//xxj 2015/04/26 16:04:58 日志数据库连接信息
		{
			parse_database_log(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"service_define_list") == 0)
		{
			parse_service_define_list(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"service_instance_list") == 0)
		{
			parse_service_instance_list(childNode);
		}

		childNode = childNode->next;
	}

	return 0;
}

void ServiceConfigMgr::parse_address(xmlNodePtr rootNode, ConfigAddress &adr,bool isZone)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"ip") == 0)
		{
			ACE_OS::strncpy(adr.ip, (char *)xmlNodeGetContent(childNode), 32);
			adr.ip[31] = '\0';
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"port") == 0)
		{
			adr.port = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(isZone && xmlStrcasecmp(childNode->name, BAD_CAST"zone") == 0)
		{
			zone = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		childNode = childNode->next;
	}
}

void ServiceConfigMgr::parse_database(xmlNodePtr rootNode)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"name") == 0)
		{
			ACE_OS::strncpy(m_dbInfo.name, (char *)xmlNodeGetContent(childNode), MAX_DB_NAME);
			m_dbInfo.name[MAX_DB_NAME] = '\0';

			//ACE_OS::sprintf(m_dbInfo.name, "test_sns_db");
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"host") == 0)
		{
			ACE_OS::strncpy(m_dbInfo.host, (char *)xmlNodeGetContent(childNode), MAX_DB_HOST);
			m_dbInfo.host[MAX_DB_HOST] = '\0';
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"user") == 0)
		{
			ACE_OS::strncpy(m_dbInfo.user, (char *)xmlNodeGetContent(childNode), MAX_DB_USER_NAME);
			m_dbInfo.user[MAX_DB_USER_NAME] = '\0';
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"password") == 0)
		{
			ACE_OS::strncpy(m_dbInfo.password, (char *)xmlNodeGetContent(childNode), MAX_DB_PASSWORD_NAME);
			m_dbInfo.password[MAX_DB_PASSWORD_NAME] = '\0';
		}
		childNode = childNode->next;
	}
}

void ServiceConfigMgr::parse_database_log(xmlNodePtr rootNode)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"name") == 0)
		{
			ACE_OS::strncpy(m_dblogInfo.name, (char *)xmlNodeGetContent(childNode), MAX_DB_NAME);
			m_dblogInfo.name[MAX_DB_NAME] = '\0';

			//ACE_OS::sprintf(m_dbInfo.name, "test_sns_db");
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"host") == 0)
		{
			ACE_OS::strncpy(m_dblogInfo.host, (char *)xmlNodeGetContent(childNode), MAX_DB_HOST);
			m_dblogInfo.host[MAX_DB_HOST] = '\0';
		}
		if(xmlStrcasecmp(childNode->name, BAD_CAST"user") == 0)
		{
			ACE_OS::strncpy(m_dblogInfo.user, (char *)xmlNodeGetContent(childNode), MAX_DB_USER_NAME);
			m_dblogInfo.user[MAX_DB_USER_NAME] = '\0';
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"password") == 0)
		{
			ACE_OS::strncpy(m_dblogInfo.password, (char *)xmlNodeGetContent(childNode), MAX_DB_PASSWORD_NAME);
			m_dblogInfo.password[MAX_DB_PASSWORD_NAME] = '\0';
		}
		childNode = childNode->next;
	}
}

void ServiceConfigMgr::parse_service_define_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		parse_service_define(childNode, m_serviceDefineList[m_unServiceDefineCount]);
		m_unServiceDefineCount ++;

		childNode = childNode->next;
	}
}

void ServiceConfigMgr::parse_service_define(xmlNodePtr rootNode, ServiceDefineInfo &info)
{
	info.isServiceMgr = false;

	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"name") == 0)
		{
			ACE_OS::strncpy(info.name, (char *)xmlNodeGetContent(childNode), MAX_SERVICE_INFO_NAME);
			info.name[MAX_SERVICE_INFO_NAME] = '\0';
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			info.unID = ACE_OS::atoi((char *)xmlNodeGetContent(childNode));
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"is_serviceMgr") == 0)
		{
			info.isServiceMgr = true;
			m_unServiceMgrTypeID = info.unID;
		}

		childNode = childNode->next;
	}
}

void ServiceConfigMgr::parse_service_instance_list(xmlNodePtr rootNode)
{
	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	while(childNode != NULL)
	{
		parse_service_instance(childNode, m_serviceInstanceList[m_unServiceInstanceCount]);
		m_unServiceInstanceCount ++;

		childNode = childNode->next;
	}
}

void ServiceConfigMgr::parse_service_instance(xmlNodePtr rootNode, ServiceInstanceInfo &info)
{
	ACE_OS::memset(&info, 0, sizeof(ServiceInstanceInfo));

	xmlNodePtr childNode = rootNode->xmlChildrenNode;

	info.isServiceMgr = false;
	//info.unPublicIP = 0;

	char *strType;

	while(childNode != NULL)
	{
		if(xmlStrcasecmp(childNode->name, BAD_CAST"name") == 0)
		{
			ACE_OS::strncpy(info.name, (char *)xmlNodeGetContent(childNode), MAX_SERVICE_INFO_NAME);
			info.name[MAX_SERVICE_INFO_NAME] = '\0';
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"type") == 0)
		{
			strType = (char *)xmlNodeGetContent(childNode);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"id") == 0)
		{
			//info.unID = ACE_OS::atoi((char *)xmlNodeGetContent(subNode));
			ACE_UINT32 tmpID = get_service_define_id(strType);

			info.unID = MAKE_SERVICE_ID(tmpID, ACE_OS::atoi((char *)xmlNodeGetContent(childNode)));

			if(tmpID == m_unServiceMgrTypeID)
			{
				m_unServiceMgrID = info.unID;
				info.isServiceMgr = true;
			}
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"lan") == 0)
		{
			parse_address(childNode, info.lanAdr);			
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"wlan") == 0)
		{
			parse_address(childNode, info.wlanAdr);
		}
		else if(xmlStrcasecmp(childNode->name, BAD_CAST"public") == 0)
		{
			ACE_INET_Addr t_adr(100, ACE_OS::atoi((char *)xmlNodeGetContent(childNode)));
			parse_address(childNode, info.publicAdr);
		}

		childNode = childNode->next;
	}

	if(info.unID == m_unServiceMgrID)
	{
		ACE_INET_Addr t_adr(info.lanAdr.port, info.lanAdr.ip);
		m_unServiceMgrIP = t_adr.get_ip_address();
		m_unServiceMgrPort = info.lanAdr.port;
	}
}