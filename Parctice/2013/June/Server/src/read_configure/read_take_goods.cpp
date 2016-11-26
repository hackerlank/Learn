
/********************************************************************

    created:	2012/2/22  15:24
	
	文件名：	read_take_goods.cpp

    author:     ChenZhen 

    purpose:  	用来读取可以采摘的任务道具的配置文件（格式为xml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"takeGoods.h"
using namespace std;

extern map<string,TakeGoods*> takeGoodsConfMap;

int read_take_goods(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	//cout<<"in the configuration_files_map.cpp file:"<<fileName<<endl;
	//读取地图配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml的相关变量
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	flgItem = 0;
	
	//循环读取xml的子节点，并取出相对应的内容	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			string typeId;
			string name;
			string photoId;
			string goodsId;
			string offerWords;
			TakeGoods *takeGoods = NULL;
			bool isDis,trigByMsg = false;
			int takeModle;           //可采集物品同时可采集的类型
			int taskStyle;           //可采集物品的类型
			int brandType;
			double takeTme;         //采集持续时间
			bool isMove = false;            //是否会动
			int durTme;             //宴席的持续时间
			bool isInterrupt = false;       //是否可以打断
	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*取出可摘取物品的类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					typeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));					
					xmlFree(_typeId);
				}
				/*取出可摘取物品的物品id*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goodsId"))
				{
					xmlChar *_goodsId=xmlGetProp(propNodePtr_item,(const xmlChar*)"goodsId");
					goodsId = const_cast<char *>(reinterpret_cast<const char *>(_goodsId));					
					xmlFree(_goodsId);
				}
				
				/*读取可摘取物品的名称*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*读取可摘取物品触发方式*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"trigByMsg"))
				{
					int trigFlg;
					xmlChar *_trigByMsg=xmlGetProp(propNodePtr_item,(const xmlChar*)"trigByMsg");			
					trigFlg=atoi(reinterpret_cast<const char *>(_trigByMsg));					
					xmlFree(_trigByMsg);
					if(trigFlg == 0)
					{
						trigByMsg = false;
					}
					else
					{
						trigByMsg = true;
					}
				}
				
				/*读取可摘取物品相应提示信息的名称*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"offerWords"))
				{
					xmlChar *_offerWords=xmlGetProp(propNodePtr_item,(const xmlChar*)"offerWords");
					
					offerWords = const_cast<char *>(reinterpret_cast<const char *>\
					(_offerWords));
					
					xmlFree(_offerWords);
				}
				
				/*读取可摘取物是否可动*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"durTme"))
				{
					xmlChar *_durTme=xmlGetProp(propNodePtr_item,(const xmlChar*)"durTme");			
					durTme=atoi(reinterpret_cast<const char *>(_durTme));			
					xmlFree(_durTme);
				}
				
				/*读取可摘取物是否可动*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isMove"))
				{
					int moveFlg;
					xmlChar *_isMove=xmlGetProp(propNodePtr_item,(const xmlChar*)"isMove");			
					moveFlg=atoi(reinterpret_cast<const char *>(_isMove));					
					xmlFree(_isMove);
					if(moveFlg == 0)
					{
						isMove = false;
					}
					else
					{
						isMove = true;
					}
				}
				
				/*读取可摘取物品摘取后是否消失*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isDis"))
				{
					int flgDis;
					xmlChar *_isDis=xmlGetProp(propNodePtr_item,(const xmlChar*)"isDis");			
					flgDis=atoi(reinterpret_cast<const char *>(_isDis));					
					xmlFree(_isDis);
					if(flgDis == 0)
					{
						isDis = false;
					}
					else
					{						
						isDis = true;
					}
				}
				
				/*读取可采集物品同时可采集的类型*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"takeModle"))
				{
					xmlChar *_takeModle=xmlGetProp(propNodePtr_item,(const xmlChar*)"takeModle");			
					takeModle=atoi(reinterpret_cast<const char *>(_takeModle));					
					xmlFree(_takeModle);
				}
				
				/*读取可采集物品的类型*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"taskStyle"))
				{
					xmlChar *_taskStyle=xmlGetProp(propNodePtr_item,(const xmlChar*)"taskStyle");			
					taskStyle=atoi(reinterpret_cast<const char *>(_taskStyle));					
					xmlFree(_taskStyle);
				}
				
				/*读取采集持续时间*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"takeTme"))
				{
					xmlChar *_takeTme=xmlGetProp(propNodePtr_item,(const xmlChar*)"takeTme");			
					takeTme=atof(reinterpret_cast<const char *>(_takeTme));					
					xmlFree(_takeTme);
				}
				
				
				/*读取采集子类型*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"brandType"))
				{
					xmlChar *_brandType=xmlGetProp(propNodePtr_item,(const xmlChar*)"brandType");			
					brandType=atoi(reinterpret_cast<const char *>(_brandType));					
					xmlFree(_brandType);
				}
				
				/*读取采集子类型*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isInterrupt"))
				{
					xmlChar *_isInterrupt=xmlGetProp(propNodePtr_item,(const xmlChar*)"isInterrupt");			
					int interFlg=atoi(reinterpret_cast<const char *>(_isInterrupt));					
					xmlFree(_isInterrupt);
					if(interFlg == 1)
					{
						isInterrupt = true;
					}
				}
				
				
				/*读取可摘取物品的图片id*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
					flgItem = 1;
				}
				
				/*实例化可摘取物品的图片id*/	
				if(flgItem == 1)
				{
					takeGoods = new TakeGoods(const_cast<char*>(typeId.c_str()),\
					const_cast<char*>(goodsId.c_str()),const_cast<char*>\
					(name.c_str()),const_cast<char*>(photoId.c_str()),\
					isDis,trigByMsg,takeModle,taskStyle,brandType,takeTme,\
					const_cast<char*>(offerWords.c_str()),durTme,isMove,isInterrupt);
					takeGoodsConfMap[typeId] = takeGoods;
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

