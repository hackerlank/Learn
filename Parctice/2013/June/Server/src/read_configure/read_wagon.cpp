
/********************************************************************

    created:	2012/9/05  15:24
	
	文件名：	read_wagon.cpp

    author:     ChenZhen 

    purpose:  	用来读取马车配置文件（格式为xml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"wagon.h"
using namespace std;

extern map<string,Wagon*> wagonConfMap;
extern map<string, wagonColorRank_T*> wagonId_2_rankRate;	//每种马车颜色刷新率

int read_wagon(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem;
	string typeId;
	string name;
	string photoId;
	string goodsId;
	string color;
	int lifeVal;
	int hurt;
	float rewardTimes = 1.0f;					//马车品级奖励系数
	bool haveSpeedGame;
	int blackSpeed;
	int yellowSpeed;
	int redSpeed;
	double gameLastTime;
	double gameCdTime;
	double incSpeedTime;
	
	//马车颜色刷新概率
	int upRate;							//马车品质提升概率
	int downRate;						//马车品质奖励概率
	int stillRate;						//马车品质不变的概率
	char prevId[51] = {0};				//低一品质马车Id
	char nextId[51] = {0};				//高一品级马车Id
	Wagon *newWagon;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	//读取地图配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
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
	newWagon = NULL;
	
	//循环读取xml的子节点，并取出相对应的内容	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
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
				/*取出马车的生命值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lifeVal"))
				{
					xmlChar *_lifeVal=xmlGetProp(propNodePtr_item,(const xmlChar*)"lifeVal");
					lifeVal = atoi(reinterpret_cast<const char *>(_lifeVal));					
					xmlFree(_lifeVal);
				}
				/*取出马车的伤害值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"hurt"))
				{
					xmlChar *_hurt=xmlGetProp(propNodePtr_item,(const xmlChar*)"hurt");
					hurt = atoi(reinterpret_cast<const char *>(_hurt));					
					xmlFree(_hurt);
				}
				
				//读取马车奖励倍数
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardTimes"))
				{
					xmlChar *_rewardTimes=xmlGetProp(propNodePtr_item, (const xmlChar*)"rewardTimes");
					
					rewardTimes = atof(reinterpret_cast<const char *>(_rewardTimes));
					
					xmlFree(_rewardTimes);
				}
				
				//读取马车颜色刷新进阶率
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upRate"))
				{
					xmlChar *_upRate=xmlGetProp(propNodePtr_item, (const xmlChar*)"upRate");
					
					upRate = atoi(reinterpret_cast<const char *>(_upRate));
					
					xmlFree(_upRate);
				}
				//读取马车颜色刷新后退率
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"downRate"))
				{
					xmlChar *_downRate=xmlGetProp(propNodePtr_item, (const xmlChar*)"downRate");
					
					downRate = atoi(reinterpret_cast<const char *>(_downRate));
					
					xmlFree(_downRate);
				}
				//读取马车颜色刷新不变率
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"stillRate"))
				{
					xmlChar *_stillRate=xmlGetProp(propNodePtr_item, (const xmlChar*)"stillRate");
					
					stillRate = atoi(reinterpret_cast<const char *>(_stillRate));
					
					xmlFree(_stillRate);
				}
				
				//低一品级马车ID		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prevId"))
				{
					xmlChar *_prevId=xmlGetProp(propNodePtr_item, (const xmlChar*)"prevId");
					
					strncpy(prevId, (char*)_prevId, sizeof (prevId));
					
					xmlFree(_prevId);
				}
				
				//高一品级马车ID		
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"nextId"))
				{
					xmlChar *_nextId = xmlGetProp(propNodePtr_item, (const xmlChar*)"nextId");
					
					strncpy(nextId, (char*)_nextId, sizeof (nextId));
					
					xmlFree(_nextId);
				}
				
				/*取出马车的颜色*/		
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"color"))
				{
					xmlChar *_color=xmlGetProp(propNodePtr_item,(const xmlChar*)"color");
					
					color = const_cast<char *>(reinterpret_cast<const char *>(_color));
					
					xmlFree(_color);
				}
				
				/*读取可摘取物品的名称*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*读取可摘取物品的图片id*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"haveSpeedGame"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"haveSpeedGame");
					
					haveSpeedGame = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"blackSpeed"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"blackSpeed");
					
					blackSpeed = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"yellowSpeed"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"yellowSpeed");
					
					yellowSpeed = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"redSpeed"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"redSpeed");
					
					redSpeed = atoi((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"gameLastTime"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"gameLastTime");
					
					gameLastTime = atof((char*)_item);
					
					xmlFree(_item);
				}
				
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"gameCdTime"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"gameCdTime");
					
					gameCdTime = atof((char*)_item);
					
					xmlFree(_item);
				}
				
				else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"incSpeedTime"))
				{
					xmlChar *_item=xmlGetProp(propNodePtr_item, (const xmlChar*)"incSpeedTime");
					
					incSpeedTime = atof((char*)_item);
					
					xmlFree(_item);
					
					flgItem = 1;
				}
				
				/*实例化可摘取物品的图片id*/	
				if(flgItem == 1)
				{
					newWagon = new Wagon(const_cast<char*>(typeId.c_str()),\
										lifeVal,hurt,const_cast<char*>(color.c_str()),\
										 const_cast<char*>(name.c_str()),\
										 const_cast<char*>(photoId.c_str()), rewardTimes,
										 haveSpeedGame, blackSpeed, yellowSpeed, redSpeed,
										 gameLastTime, gameCdTime, incSpeedTime);
					wagonConfMap[typeId] = newWagon;
					wagonColorRank_T *oneItem = new wagonColorRank_T(upRate, downRate, stillRate, prevId, nextId);
					wagonId_2_rankRate[typeId] = oneItem;
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

