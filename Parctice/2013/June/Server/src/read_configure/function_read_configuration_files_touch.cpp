#include"function_read_configuration_files.h"
#include"task_touch_configuration.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string, Task_Touch_Configuration*> id_to_touch;

int read_files_touch(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	string touch_id;
	string taskId;
	string touch_type;
	unsigned int hero_level;
	
	strcpy(szDocName,fileName);
	
	xmlKeepBlanksDefault(0);
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//得到xml文件的root
	curnow=xmlDocGetRootElement(doc);
	if(NULL==curnow)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curnow=curnow->xmlChildrenNode;
	
	while(curnow!=NULL)
	{	
		
		curNode = curnow->xmlChildrenNode;
		if(NULL==curNode)
		{
			xmlFreeDoc(doc);
			return -3;
		}
		while(curNode != NULL)
		{
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"touch_id"))
			{
				cTem= xmlNodeGetContent(curNode);
				touch_id = const_cast<char *>(reinterpret_cast<const char *>(cTem));
				xmlFree(cTem);
				//cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%::::"<<touch_id<<endl;
			}
			
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"taskId"))
			{
				cTem= xmlNodeGetContent(curNode);
				taskId = const_cast<char *>(reinterpret_cast<const char *>(cTem));
				xmlFree(cTem);
				//cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%::::"<<taskId<<endl;
			}
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"touch_type"))
			{
				cTem= xmlNodeGetContent(curNode);
				touch_type = const_cast<char *>(reinterpret_cast<const char *>(cTem));
				xmlFree(cTem);
				//cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%::::"<<touch_type<<endl;
			}
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"hero_level"))
			{
				cTem= xmlNodeGetContent(curNode);
				hero_level = atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
				//cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%::::"<<hero_level<<endl;
				Task_Touch_Configuration *Touch;
				Touch = new Task_Touch_Configuration(touch_id, taskId, touch_type, hero_level);
				id_to_touch[taskId] = Touch;
			}
			
			curNode=curNode->next;
		}
		curnow=curnow->next;
	}
	//cout<<"&&&&&&&&&&&&&&&&&&&&&&::::"<<id_to_touch.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}