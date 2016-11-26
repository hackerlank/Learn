
/********************************************************************

    created:	2012/9/05  15:24
	
	文件名：	read_outer_active_code.cpp

    author:     ChenZhen 

    purpose:  	用来读取外部激活码文件（格式为xml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
using namespace std;

extern set<AvtiveCode> outerActiveCodeMap;

int read_outer_active_code(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	string codeId;	
	string goodsId;
	
	set<AvtiveCode>::iterator code_it;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
//	cout<<"read the out active code begin:"<<endl;
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"order"))
		{
//			cout<<"read the out active code order bein:"<<endl;
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*物品类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goodsId"))
				{
					xmlChar *_goodsId=xmlGetProp(propNodePtr_item,(const xmlChar*)"goodsId");
					goodsId = const_cast<char *>(reinterpret_cast<const char *>(_goodsId));					
					xmlFree(_goodsId);
				}					
				attrPtr = attrPtr->next;	
			}
	//		cout<<"read the out active code order end:"<<goodsId<<endl;
		}
		else if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*激活码id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"code"))
				{
					xmlChar *_code=xmlGetProp(propNodePtr_item,(const xmlChar*)"code");
					codeId = const_cast<char *>(reinterpret_cast<const char *>(_code));			
					xmlFree(_code);
					
					if(goodsId.size() > 1 && codeId.size() > 1)
					{
						AvtiveCode newActiveCode(const_cast<char*>\
						(codeId.c_str()),const_cast<char*>\
						(goodsId.c_str()));
						
						code_it = outerActiveCodeMap.find(newActiveCode);
						
						if(code_it == outerActiveCodeMap.end())
						{
							outerActiveCodeMap.insert(newActiveCode);
						}
					}
				}					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
//	cout<<"read the out active code end:"<<endl;
}

