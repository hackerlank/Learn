#include"function_read_configuration_files.h"
#include"petSkill_config.h"
#include<libxml/parser.h>
#include<string.h>
using namespace std;
extern map<string,PetSkill_Config*> id_to_petSkill;
int read_files_petSkill(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char id[20]={'\0'};
	int flag;
	int initEffect;
	int increaseRatio;
	int range;
	int limit;
	int addLimit;
	int maxLimit;
	int needNumber;
	int needCount;	
	int addNeedCount;	
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(id,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(id));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"flag"))
				{
					cTem= xmlNodeGetContent(curNode);
					flag=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					initEffect=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"increase"))
				{
					cTem= xmlNodeGetContent(curNode);
					increaseRatio=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"range"))
				{
					cTem= xmlNodeGetContent(curNode);
					range=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"limit"))
				{
					cTem= xmlNodeGetContent(curNode);
					limit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"addLimit"))
				{
					cTem= xmlNodeGetContent(curNode);
					addLimit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"maxLimit"))
				{
					cTem= xmlNodeGetContent(curNode);
					maxLimit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"needNumber"))
				{
					cTem= xmlNodeGetContent(curNode);
					needNumber=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"needCount"))
				{
					cTem= xmlNodeGetContent(curNode);
					needCount=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"addNeedCount"))
				{
					cTem= xmlNodeGetContent(curNode);
					addNeedCount=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					PetSkill_Config *petskill; 
					petskill = new PetSkill_Config(id,flag,initEffect,increaseRatio,range,limit,addLimit,maxLimit,needNumber,needCount,addNeedCount);			
					id_to_petSkill.insert(map<string,PetSkill_Config*>::value_type(id,petskill));
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
