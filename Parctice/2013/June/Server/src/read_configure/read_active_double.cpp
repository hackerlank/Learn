#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

extern ActiveDouble activeDouble;

int read_active_double(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	char flag[50]={0};
	TimeActiveDouble temp;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	//读取地图配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml的相关变量
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	
	//循环读取xml的子节点，并取出相对应的内容	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"activeDouble"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{						
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"id"))
				{
					xmlChar *_id=xmlGetProp(propNodePtr_item,(const xmlChar*)"id");
					strncpy(flag ,reinterpret_cast<const char *>(_id),sizeof(flag));					
					xmlFree(_id);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginYear"))
				{
					xmlChar *_beginYear=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginYear");
					temp.beginYear = atoi(reinterpret_cast<const char *>(_beginYear));					
					xmlFree(_beginYear);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginMouth"))
				{
					xmlChar *_beginMouth=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginMouth");
					temp.beginMouth = atoi(reinterpret_cast<const char *>(_beginMouth));					
					xmlFree(_beginMouth);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginDay"))
				{
					xmlChar *_beginDay=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginDay");
					temp.beginDay = atoi(reinterpret_cast<const char *>(_beginDay));					
					xmlFree(_beginDay);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"beginHour"))
				{
					xmlChar *_beginHour=xmlGetProp(propNodePtr_item,(const xmlChar*)"beginHour");
					temp.beginHour = atoi(reinterpret_cast<const char *>(_beginHour));					
					xmlFree(_beginHour);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endYear"))
				{
					xmlChar *_endYear=xmlGetProp(propNodePtr_item,(const xmlChar*)"endYear");
					temp.endYear = atoi(reinterpret_cast<const char *>(_endYear));					
					xmlFree(_endYear);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endMouth"))
				{
					xmlChar *_endMouth=xmlGetProp(propNodePtr_item,(const xmlChar*)"endMouth");
					temp.endMouth = atoi(reinterpret_cast<const char *>(_endMouth));					
					xmlFree(_endMouth);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endDay"))
				{
					xmlChar *_endDay=xmlGetProp(propNodePtr_item,(const xmlChar*)"endDay");
					temp.endDay = atoi(reinterpret_cast<const char *>(_endDay));					
					xmlFree(_endDay);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endHour"))
				{
					xmlChar *_endHour=xmlGetProp(propNodePtr_item,(const xmlChar*)"endHour");
					temp.endHour = atoi(reinterpret_cast<const char *>(_endHour));					
					xmlFree(_endHour);
					
					if (strcmp(flag,"shengyan")==0)
					{
						activeDouble.shengyan=temp;
					}
					else if (strcmp(flag,"daguai")==0)
					{
						activeDouble.daguai=temp;
					}
					else if (strcmp(flag,"yabiao")==0)
					{
						activeDouble.yabiao=temp;
					}
				}					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
