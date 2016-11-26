#include <iostream>

#include <sstream>

#include <map>

#include <set>

#include <libxml/parser.h>

#include "function_read_configuration_files.h"

#include "my_memcached.h"

//缓存服务器配置表
extern map<string, Mem_configure> mem_configure_table;

//邮件数据存放路径 added by Tory
extern string mail_data_url_T;

extern string GM_verify_password;

extern set<string> innerIPSet;

extern char server_name[10];

extern int dataVersion;

int read_server_config(char *fileName)
{

    xmlDocPtr doc;           //定义解析文档指针
    xmlNodePtr curNode;      //定义结点指针(你需要它为了在各个结点间移动) 
    xmlChar *szKey;          //临时字符串变量
	char ok_ip[20] = {0};

    char *szDocName = (char*)malloc(strlen(fileName)+1);
    strcpy(szDocName, fileName);
    doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER); //解析文件    
    if(NULL == doc)
    {
        fprintf(stderr,"Document not parsed successfully.\n");     

        return -1; 
    }
    curNode = xmlDocGetRootElement(doc); //确定文档根元素
    //检查确认当前文档中包含内容
    if(NULL == curNode)
    {
        fprintf(stderr,"empty document\n"); 
        xmlFreeDoc(doc); 
        return -1; 
    }

    for(curNode=curNode->xmlChildrenNode; curNode != NULL; curNode=curNode->next)
    {
		string 	description;
		char 	ip[20] = {0};
		int  	port;		
		
		/************************ xhm add start,增加同名检测缓存服务器 有疑问RTX xhm 不要删除**********************/
		if(!xmlStrcmp(curNode->name, BAD_CAST "nickname_inspection_mem_configure"))
        {
            xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "description"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "description");
					// cout<<"[XHM WARNING] nickname_inspection_mem get description = "<<szAttr<<endl;
					description = reinterpret_cast<const char *>(szAttr);
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "ip"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "ip");
					// cout<<"[XHM WARNING] nickname_inspection_mem get ip = "<<szAttr<<endl;
					strncpy(ip, reinterpret_cast<const char *>(szAttr), 20);
                    xmlFree(szAttr);
                }
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "port"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "port");
					// cout<<"[XHM WARNING] nickname_inspection_mem get port = "<<szAttr<<endl;
					port = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }

                attrPtr = attrPtr->next;
            }
			Mem_configure mem_configure(ip, port);

			pair<map<string, Mem_configure>::iterator, bool> ret;
			ret =  mem_configure_table.insert(map<string, Mem_configure>::value_type (description, mem_configure));
			
			// if(ret.second == true)
			// {
				// cout<<"[XHM WARNING] insert Mem_configure to nickname_inspection_mem_configure success"<<endl;
			// } else
			// {
				// cout<<"[XHM WARNING] insert Mem_configure to nickname_inspection_mem_configure failure"<<endl;
			// } 		
        } 
		/************************ xhm add end,增加同名检测缓存服务器 有疑问RTX xhm **********************/		
		
		/****************************日志服务器*************************************/
		if(!xmlStrcmp(curNode->name, BAD_CAST "log_mem_configure"))
        {
            xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "description"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "description");
					description = reinterpret_cast<const char *>(szAttr);
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "ip"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "ip");
					strncpy(ip, reinterpret_cast<const char *>(szAttr), 20);
                    xmlFree(szAttr);
                }
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "port"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "port");
					port = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }

                attrPtr = attrPtr->next;
            }
			Mem_configure mem_configure(ip, port);
			
			pair<map<string, Mem_configure>::iterator, bool> ret;
			ret =  mem_configure_table.insert(map<string, Mem_configure>::value_type (description, mem_configure));
		
        }
		
		/****************************充值服务器*************************************/
		if(!xmlStrcmp(curNode->name, BAD_CAST "recharge_mem_configure"))
        {
            xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "description"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "description");
					description = reinterpret_cast<const char *>(szAttr);
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "ip"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "ip");
					strncpy(ip, reinterpret_cast<const char *>(szAttr), 20);
                    xmlFree(szAttr);
                }
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "port"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "port");
					port = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }

                attrPtr = attrPtr->next;
            }
			Mem_configure mem_configure(ip, port);
			
			pair<map<string, Mem_configure>::iterator, bool> ret;
			ret =  mem_configure_table.insert(map<string, Mem_configure>::value_type (description, mem_configure));
			//加判断是否成功；
		
        }
		
		/****************************cdKey服务器*************************************/
		if(!xmlStrcmp(curNode->name, BAD_CAST "cdkey_mem_configure"))
        {
            xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "description"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "description");
					description = reinterpret_cast<const char *>(szAttr);
					cout<<"have read mem_configure with id of "<<description<<endl;
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "ip"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "ip");
					strncpy(ip, reinterpret_cast<const char *>(szAttr), 20);
                    xmlFree(szAttr);
					cout<<"have read mem_configure with ip of "<<ip<<endl;
                }
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "port"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "port");
					port = atoi(reinterpret_cast<const char *>(szAttr));
					cout<<"have read mem_configure with port of "<<port<<endl;
                    xmlFree(szAttr);
                }

                attrPtr = attrPtr->next;
            }
			Mem_configure mem_configure(ip, port);
			
			pair<map<string, Mem_configure>::iterator, bool> ret;
			ret =  mem_configure_table.insert(map<string, Mem_configure>::value_type (description, mem_configure));
		
        }
		
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "mail_data_url"))
		{
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "url"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "url");
				//	cout<<"get url = "<<szAttr<<endl;
					mail_data_url_T = reinterpret_cast<const char *>(szAttr);
                    xmlFree(szAttr);
                }				
			
                attrPtr = attrPtr->next;
            }
		}
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "gm_verify"))
		{
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "passward"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "passward");
				//	cout<<"get url = "<<szAttr<<endl;
					GM_verify_password = reinterpret_cast<const char *>(szAttr);
                    xmlFree(szAttr);
					// cout<<GM_verify_password<<endl;
                }				
			
                attrPtr = attrPtr->next;
            }
		}
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "ok_ip"))
		{
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "ip"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "ip");
				//	cout<<"get url = "<<szAttr<<endl;
					strncpy(ok_ip, reinterpret_cast<const char *>(szAttr), 20);
					innerIPSet.insert(ok_ip);
                    xmlFree(szAttr);
					// cout<<GM_verify_password<<endl;
                }				
			
                attrPtr = attrPtr->next;
            }
		}
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "serverName"))
		{
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "name"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "name");
					strncpy(server_name,reinterpret_cast<const char *>(szAttr),sizeof(server_name));
                    xmlFree(szAttr);
                }				
			
                attrPtr = attrPtr->next;
            }
		}
		
		
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "dataVersion"))
		{
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "data"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "data");
					dataVersion = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }				
			
                attrPtr = attrPtr->next;
            }
		}
    }   
	
	free(szDocName);
    xmlFreeDoc(doc);
	return 0;
}

