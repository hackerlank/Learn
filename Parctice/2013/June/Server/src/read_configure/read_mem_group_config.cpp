/* 
* author: tory
* date:	2013.3.12
* describe:读取缓存服务器管理类配置
 */
#include <iostream>
#include <map>
#include <libxml/parser.h>
#include "function_read_configuration_files.h"
#include "my_memcached.h"

using namespace std;

extern map<int, Mem_configure*> mem_group_table;

int read_mem_group_config(char *fileName)
{
    xmlDocPtr doc;           //定义解析文档指针
    xmlNodePtr curNode;      //定义结点指针(你需要它为了在各个结点间移动) 
    xmlChar *szKey;          //临时字符串变量
	
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

	int 	index;
	char 	ip[20] = {0};
	int  	port;
    for(curNode=curNode->xmlChildrenNode; curNode != NULL; curNode=curNode->next)
    {					
		if(!xmlStrcmp(curNode->name, BAD_CAST "mem_config"))
        {		
			xmlNodePtr propNodePtr = curNode;
			xmlAttrPtr attrPtr = curNode->properties;
			while(attrPtr != NULL)
			{
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "index"))
				{
					xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "index");
					cout<<"get index = "<<szAttr<<endl;
					index = atoi(reinterpret_cast<const char *>(szAttr));
					xmlFree(szAttr);
				}		
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "ip"))
				{
					xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "ip");
					// cout<<"get ip = "<<szAttr<<endl;
					strncpy(ip, reinterpret_cast<const char *>(szAttr), 20);
					xmlFree(szAttr);
				}	
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "port"))
				{
					xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "port");
					// cout<<"get port = "<<szAttr<<endl;
					port = atoi(reinterpret_cast<const char *>(szAttr));
					xmlFree(szAttr);
				}					
				attrPtr = attrPtr->next;
			}

			Mem_configure *mem_config_ptr = new Mem_configure(ip, port);
			pair<map<int, Mem_configure*>::iterator, bool> ret;
			ret =  mem_group_table.insert(map<int, Mem_configure*>::value_type (index, mem_config_ptr));
 			if(ret.second == true)
			{
				cout<<"insert Mem_configure to mem_group_table success"<<endl;
			} else
			{
				cout<<"insert Mem_configure to mem_group_table failure"<<endl;
			}
		}		
		
    }   
	
	free(szDocName);
    xmlFreeDoc(doc);
	return 0;
}