#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<int,int> exp_upgrade_list;
int read_files_update(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
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
	int grade = 1;
	unsigned int num;

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
		
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"num001"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num002"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num003"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num004"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num005"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num006"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num007"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num008"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num009"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num010"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num011"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num012"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num013"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num014"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num015"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num016"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num017"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num018"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num019"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num020"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num021"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num022"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num023"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num024"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num025"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num026"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num027"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num028"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num029"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num030"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num031"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num032"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num033"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num034"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num035"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num036"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num037"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num038"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num039"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num040"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num041"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num042"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num043"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num044"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num045"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num046"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num047"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num048"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num049"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num050"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num051"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num052"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num053"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num054"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num055"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num056"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num057"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num058"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num059"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num060"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num061"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num062"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num063"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num064"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num065"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num066"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num067"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num068"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num069"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num070"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num071"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num072"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num073"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num074"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num075"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num076"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num077"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num078"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num079"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"num080"))
				{
					cTem= xmlNodeGetContent(curNode);
					num=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					exp_upgrade_list.insert(pair<int,int>(grade, num));
					grade +=1;
					xmlFree(cTem);
				}
			curNode = curNode->next;		
			}
		curnow=curnow->next;
	}
	// cout<<"####################################################################"<<endl;
	// cout<<"the size of lists is :"<<exp_upgrade_list.size()<<endl;
	// cout<<"####################################################################"<<endl;
	xmlFreeDoc(doc);
	return 0;	
}