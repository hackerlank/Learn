#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"five_configuration.h"
#include<map>
#include<string>
#include<iostream>
using namespace std;
extern map<string,Five_Configuration*>id_to_five;
int read_files_five(char *fileName)
{

	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	
	string id;
	int gold;
	int wood;
	int water;
	int fire;
	int soil;
	
	
	//读取five配置文件
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
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
			{
				cTem= xmlNodeGetContent(curNode);
				id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
				xmlFree(cTem);
			}
			curNode = curNode->next;
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"skillName"))
			{
				cTem= xmlNodeGetContent(curNode);
				gold=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			curNode=curNode->next;
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"startHurt"))
			{
				cTem= xmlNodeGetContent(curNode);
				wood=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			curNode=curNode->next;
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"hurtIncreaseRat"))
			{
				cTem= xmlNodeGetContent(curNode);
				water=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			curNode=curNode->next;
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"startHurtLast"))
			{
				cTem= xmlNodeGetContent(curNode);
				fire=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
			curNode=curNode->next;
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"lastIncreaseRat"))
			{
				cTem= xmlNodeGetContent(curNode);
				soil=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);
			}
		
			Five_Configuration *five;			
			five=new Five_Configuration(id,gold,wood,water,fire,soil);
			id_to_five[id]=five;
		
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
