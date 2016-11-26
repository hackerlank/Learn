#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<string>
using namespace std;
extern map<string,int> goodsId_to_price_shengWang; 
int read_files_shengWangBussiness(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	
	char goodsid[20]={'\0'};
	int price;
	
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
			if(!xmlStrcmp(curNode->name,(const xmlChar *)"goodsId"))
			{
				cTem= xmlNodeGetContent(curNode);
				strncpy(goodsid,const_cast<char *>(reinterpret_cast<const char *>(cTem)),sizeof(goodsid));
				xmlFree(cTem);
				// cout<<goodsid<<endl;
			}
			else if(!xmlStrcmp(curNode->name,(const xmlChar *)"price"))
			{
				cTem= xmlNodeGetContent(curNode);
				price=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
				xmlFree(cTem);			
				goodsId_to_price_shengWang.insert(map<string,int>::value_type(goodsid,price));
			}
			curNode=curNode->next;
		}
		curnow=curnow->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
