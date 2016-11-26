/* 
* author: tory
* date:	2013.1.14
* describe:读取宝石合成配置文件
 */
#include <iostream>

#include <sstream>

#include <map>

#include <set>

#include <libxml/parser.h>

#include "function_read_configuration_files.h"

#include "equipment.h"

extern HeChengConfig g_heChengConfig;			//宝石合成配置数据

int read_heCheng_config(char *fileName)
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

    for(curNode=curNode->xmlChildrenNode; curNode != NULL; curNode=curNode->next)
    {		
        if(!xmlStrcmp(curNode->name, BAD_CAST "level_two"))
        {
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
				
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "cost"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "cost");
				//	cout<<"get cost = "<<szAttr<<endl;
					g_heChengConfig.cost[0] = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "rate"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "rate");
				//	cout<<"get rate = "<<szAttr<<endl;
					g_heChengConfig.rate[0] = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }            
				attrPtr = attrPtr->next;
            }		
        }		
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "level_three"))
        {
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "cost"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "cost");
				//	cout<<"get cost = "<<szAttr<<endl;
					g_heChengConfig.cost[1] = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "rate"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "rate");
				//	cout<<"get rate = "<<szAttr<<endl;
					g_heChengConfig.rate[1] = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }            
				attrPtr = attrPtr->next;
            }		
        }
		
		if(!xmlStrcmp(curNode->name, BAD_CAST "level_four"))
        {
			xmlNodePtr propNodePtr = curNode;
            xmlAttrPtr attrPtr = curNode->properties;
			while(attrPtr != NULL)
            {
				if(!xmlStrcmp(attrPtr->name, BAD_CAST "cost"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "cost");
				//	cout<<"get cost = "<<szAttr<<endl;
					g_heChengConfig.cost[2] = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }				
			
                if(!xmlStrcmp(attrPtr->name, BAD_CAST "rate"))
                {
                    xmlChar* szAttr = xmlGetProp(propNodePtr,BAD_CAST "rate");
				//	cout<<"get rate = "<<szAttr<<endl;
					g_heChengConfig.rate[2] = atoi(reinterpret_cast<const char *>(szAttr));
                    xmlFree(szAttr);
                }            
				attrPtr = attrPtr->next;
            }		
        }
    }   
	// int i = 0;
	// for(i; i < 3; i++)
	// {
		// cout<<"@@Tory, cost:"<<g_heChengConfig.cost[i]<<" rate:"<<g_heChengConfig.rate[i]<<endl;
	// }
	free(szDocName);
    xmlFreeDoc(doc);
	return 0;
}