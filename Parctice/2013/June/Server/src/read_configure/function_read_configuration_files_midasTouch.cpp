#include"function_read_configuration_files.h"
#include "data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern MidasTouchNumber midasTouchNumber;	
int read_files_midasTouchReward(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	int number;
	int money[6];
	int popularity[6];
	int percent;
	
	int i=0;
	
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
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"number"))
			{
				cTem= xmlNodeGetContent(curNode);
				number=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money1"))
			{
				cTem= xmlNodeGetContent(curNode);
				money[0]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money2"))
			{
				cTem= xmlNodeGetContent(curNode);
				money[1]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money3"))
			{
				cTem= xmlNodeGetContent(curNode);
				money[2]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money4"))
			{
				cTem= xmlNodeGetContent(curNode);
				money[3]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money5"))
			{
				cTem= xmlNodeGetContent(curNode);
				money[4]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money6"))
			{
				cTem= xmlNodeGetContent(curNode);
				money[5]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"popularity1"))
			{
				cTem= xmlNodeGetContent(curNode);
				popularity[0]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"popularity2"))
			{
				cTem= xmlNodeGetContent(curNode);
				popularity[1]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"popularity3"))
			{
				cTem= xmlNodeGetContent(curNode);
				popularity[2]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"popularity4"))
			{
				cTem= xmlNodeGetContent(curNode);
				popularity[3]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"popularity5"))
			{
				cTem= xmlNodeGetContent(curNode);
				popularity[4]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"popularity6"))
			{
				cTem= xmlNodeGetContent(curNode);
				popularity[5]=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"percent"))
			{
				cTem= xmlNodeGetContent(curNode);
				percent=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);		
				for (int i=0;i<6;i++)
				{
					midasTouchNumber.midasTouch[number-1].money[i]=money[i];
					midasTouchNumber.midasTouch[number-1].popularity[i]=popularity[i];
					midasTouchNumber.midasTouch[number-1].percent=percent;
				}		
			}
			curNode=curNode->next;
		}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
