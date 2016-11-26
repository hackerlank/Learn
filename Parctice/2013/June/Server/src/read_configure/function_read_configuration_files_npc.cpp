#include"function_read_configuration_files.h"
#include"npc_configuration.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string,Npc_Configuration*> id_to_npc; 
int read_files_npc(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	string npc_id;//npcid
	string npc_name;  //npc名称
	
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
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"Id"))
				{
					cTem= xmlNodeGetContent(curNode);
					npc_id=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
					//cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%::::"<<taskId<<endl;
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"Name"))
				{
					cTem= xmlNodeGetContent(curNode);
					npc_name=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
					Npc_Configuration *npc;
					npc = new Npc_Configuration(npc_id,npc_name);
					id_to_npc[npc_id] = npc;
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	//cout<<"&&&&&&&&&&&&&&&&&&&&&&::::"<<id_to_npc.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}