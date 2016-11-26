#include"function_read_configuration_files.h"
#include"revival_config.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string,Revival_Config*> mapId_to_revival;
int read_files_revival(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char mapId[50]={'\0'};
	char revivalMap[50]={'\0'};
	int ptx;
	int pty;
	
	int i = 0;	

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
		int num=0;
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				return -3;
			}
			while(curNode != NULL)
			{
				// int len;
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"map"))
				{			
					cTem= xmlNodeGetContent(curNode);
					strncpy(mapId,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(mapId));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"revivalMap"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(revivalMap,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(revivalMap));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"ptx"))
				{
					cTem= xmlNodeGetContent(curNode);
					ptx=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"pty"))
				{
					cTem= xmlNodeGetContent(curNode);
					pty=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Revival_Config *revival;
					revival=new Revival_Config(mapId,revivalMap,ptx,pty);
					mapId_to_revival.insert(map<string,Revival_Config*>::value_type (mapId,revival));
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
