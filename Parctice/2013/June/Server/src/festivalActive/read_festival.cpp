
/********************************************************************

    created:	2012/9/05  15:24
	
	文件名：	read_bottle.cpp

    author:     ChenZhen 

    purpose:  	用来读取瓶罐配置文件（格式为xml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
using namespace std;

extern FestivalGoods festivalGoods;

int read_festivalGoods(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"rewardgoods"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{						
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"number"))
				{
					xmlChar *_level=xmlGetProp(propNodePtr_item,(const xmlChar*)"number");
					festivalGoods.num =atoi(reinterpret_cast<const char *>(_level));					
					xmlFree(_level);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods1"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"goods1");
					strncpy(festivalGoods.goods[0] , const_cast<char *>(reinterpret_cast<const char *>(_factor)),20);					
					xmlFree(_factor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods2"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"goods2");
					strncpy(festivalGoods.goods[1] , const_cast<char *>(reinterpret_cast<const char *>(_factor)),20);					
					xmlFree(_factor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods3"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"goods3");
					strncpy(festivalGoods.goods[2] , const_cast<char *>(reinterpret_cast<const char *>(_factor)),20);					
					xmlFree(_factor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods4"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"goods4");
					strncpy(festivalGoods.goods[3] , const_cast<char *>(reinterpret_cast<const char *>(_factor)),20);					
					xmlFree(_factor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods5"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"goods5");
					strncpy(festivalGoods.goods[4] , const_cast<char *>(reinterpret_cast<const char *>(_factor)),20);					
					xmlFree(_factor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods6"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"goods6");
					strncpy(festivalGoods.goods[5] , const_cast<char *>(reinterpret_cast<const char *>(_factor)),20);					
					xmlFree(_factor);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"reward"))
				{
					xmlChar *_factor=xmlGetProp(propNodePtr_item,(const xmlChar*)"reward");
					strncpy(festivalGoods.rewardGoods,const_cast<char *>(reinterpret_cast<const char *>(_factor)),sizeof(festivalGoods.rewardGoods));					
					xmlFree(_factor);
				}					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

