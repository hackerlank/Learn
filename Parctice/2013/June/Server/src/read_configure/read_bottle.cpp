
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
#include"bottle.h"
using namespace std;

extern map<string,Bottle*> bottleConfMap;

int read_bottle(char *fileName)
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
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			int flgItem = 0;
			string typeId;
			string name;
			string photoId;
			string goodsId;
			string dropStage;
			int lifeVal;
			int hurt;
			int brushStyle = 0;
			double bloodPre = 0.2;
			double magicPre = 0.2;
			Bottle *newBottle = NULL;
			int dropNum = 0;
			
	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*取出瓶罐的类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					typeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));					
					xmlFree(_typeId);
				}
				/*取出瓶罐的生命值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lifeVal"))
				{
					xmlChar *_lifeVal=xmlGetProp(propNodePtr_item,(const xmlChar*)"lifeVal");
					lifeVal = atoi(reinterpret_cast<const char *>(_lifeVal));					
					xmlFree(_lifeVal);
				}
				
				/*取出瓶罐的伤害值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hurt"))
				{
					xmlChar *_hurt=xmlGetProp(propNodePtr_item,(const xmlChar*)"hurt");
					hurt = atoi(reinterpret_cast<const char *>(_hurt));					
					xmlFree(_hurt);
				}
				/*取出瓶罐的刷出模式*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"brushStyle"))
				{
					xmlChar *_brushStyle=xmlGetProp(propNodePtr_item,(const xmlChar*)"brushStyle");
					brushStyle = atoi(reinterpret_cast<const char *>(_brushStyle));					
					xmlFree(_brushStyle);
				}
				/*取出瓶罐的回血百分比*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"bloodPre"))
				{
					xmlChar *_bloodPre=xmlGetProp(propNodePtr_item,(const xmlChar*)"bloodPre");
					bloodPre = atof(reinterpret_cast<const char *>(_bloodPre));					
					xmlFree(_bloodPre);
				}
				/*取出瓶罐的回蓝百分比*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"magicPre"))
				{
					xmlChar *_magicPre=xmlGetProp(propNodePtr_item,(const xmlChar*)"magicPre");
					magicPre = atof(reinterpret_cast<const char *>(_magicPre));					
					xmlFree(_magicPre);
				}
				/*读取瓶罐的名称*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*读取瓶罐掉落数量*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dropNum"))
				{
					xmlChar *_dropNum=xmlGetProp(propNodePtr_item,(const xmlChar*)"dropNum");
					
					dropNum = atof(reinterpret_cast<const char *>(_dropNum));		
					
					xmlFree(_dropNum);
				}
				
				/*读取瓶罐掉落阶段*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dropStage"))
				{
					xmlChar *_dropStage=xmlGetProp(propNodePtr_item,(const xmlChar*)"dropStage");
					
					dropStage = const_cast<char *>(reinterpret_cast<const char *>(_dropStage));
					
					xmlFree(_dropStage);
				}
				
				/*读取瓶罐的图片id*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
					flgItem = 1;
				}
				
				/*实例化瓶罐的图片id*/	
				if(flgItem == 1)
				{
					newBottle = new Bottle(const_cast<char*>(typeId.c_str()),\
					lifeVal,hurt,brushStyle,bloodPre,magicPre,const_cast<char*>(name.c_str()),\
					dropNum,const_cast<char*>(dropStage.c_str()),const_cast<char*>(photoId.c_str()));
					
					bottleConfMap[typeId] = newBottle;
					flgItem = 0;
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

