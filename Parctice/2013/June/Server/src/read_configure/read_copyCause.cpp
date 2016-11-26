#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>

using namespace std;
extern map<string,string> mapIdToGoodsId;
int read_copyCause(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	xmlChar *carrier;
	char szDocName[50]={0};
	
	string id;
	int number;
	int times;
	string mapId;
	
	
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"goods"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*取出瓶罐的类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"id"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"id");
					id = const_cast<char *>(reinterpret_cast<const char *>(carrier));						
					xmlFree(carrier);
				}
				/*取出瓶罐的生命值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId1"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId1");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(carrier));		
					mapIdToGoodsId.insert(pair<string,string>(mapId,id));
					xmlFree(carrier);
				}
				
				/*取出瓶罐的伤害值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId2"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId2");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(carrier));	
					mapIdToGoodsId.insert(pair<string,string>(mapId,id));					
					xmlFree(carrier);
				}
				
				/*读取瓶罐的名称*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId3"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId3");
					
					mapId = const_cast<char *>(reinterpret_cast<const char *>(carrier));	
					mapIdToGoodsId.insert(pair<string,string>(mapId,id));
					xmlFree(carrier);
				}
				
				/*读取瓶罐的图片id*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId4"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId4");
					
					mapId = const_cast<char *>(reinterpret_cast<const char *>(carrier));	
					mapIdToGoodsId.insert(pair<string,string>(mapId,id));
					xmlFree(carrier);
					
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId5"))
				{
					carrier=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId5");
					
					mapId = const_cast<char *>(reinterpret_cast<const char *>(carrier));	
					mapIdToGoodsId.insert(pair<string,string>(mapId,id));
					xmlFree(carrier);
					
				}
				
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
/* 
	for(map<string,string>::iterator i=mapIdToGoodsId.begin();i!=mapIdToGoodsId.end();++i)
	{
		cout<<i->first<<endl;
		cout<<i->second<<endl;
	} */
	xmlFreeDoc(doc);
	return 0;
}