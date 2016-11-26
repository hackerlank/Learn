// #include"function_read_configuration_files.h"
#include"goods_config.h"
#include"bag_operator.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string,Goods_Config*> id_to_dj;
extern map<string,Goods_Config*> id_to_cl;
int read_files_goods(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char id[20]={'\0'};
	char name[50]={'\0'};
	char effect[1024]={'\0'};
	int order;
	int repeat;
	int type;
	int levelLimit;
	int gold;
	int goldBound;
	int moneyBound;
	int money;
	int price;
	
	int i = 0;	

	map<int,string> drop_goods_id;
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
				int len;
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"id"))
				{					
					cTem= xmlNodeGetContent(curNode);					
					strncpy(id,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(id));
					xmlFree(cTem);
					// cout<<id<<endl;
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"name"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(name,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(name));
					xmlFree(cTem);					
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"effect"))
				{
					cTem= xmlNodeGetContent(curNode);
					strncpy(effect,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(effect));
					xmlFree(cTem);	
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"order"))
				{
					cTem= xmlNodeGetContent(curNode);
					order=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"repeat"))
				{
					cTem= xmlNodeGetContent(curNode);
					repeat=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"type"))
				{
					cTem= xmlNodeGetContent(curNode);
					type=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);					
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"levelLimit"))
				{
					cTem= xmlNodeGetContent(curNode);
					levelLimit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"money"))
				{
					cTem= xmlNodeGetContent(curNode);
					money=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
				
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"moneyBound"))
				{
					cTem= xmlNodeGetContent(curNode);
					moneyBound=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"price"))
				{
					cTem= xmlNodeGetContent(curNode);
					price=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gold"))
				{
					cTem= xmlNodeGetContent(curNode);
					gold=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				else if(!xmlStrcmp(curNode->name,(const xmlChar *)"goldBound"))
				{
					cTem= xmlNodeGetContent(curNode);
					goldBound=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
					Goods_Config *goods_config; 
					goods_config = new Goods_Config(id,name,effect,order,repeat,type,levelLimit,gold,goldBound,money,moneyBound,price);
					// string test=id.substr(2,2);
					int _type=getGoodsType(id);
					// cout<<_type<<endl;
					if (_type==4)
					{
						id_to_cl.insert(map<string,Goods_Config*>::value_type(id,goods_config));
					}
					else
					{
						id_to_dj.insert(map<string,Goods_Config*>::value_type(id,goods_config));
					}
				}
				curNode=curNode->next;
			}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
