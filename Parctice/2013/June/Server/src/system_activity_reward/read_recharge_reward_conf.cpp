/********************************************************************
    created:   2012/12/2
    filename:  read_recharge_reward_conf.cpp
    author:    xhm 
    depend:    libxml2.lib 
*********************************************************************/
#include"function_read_configuration_files.h"

#include<libxml/parser.h>
#include<iostream>

#include "data_structure_struct.h"
#include "system_activity_reward_assist.h"

using namespace std;

extern Recharge_reward_time_T reward_time_conf;//时间配置文件；
extern Recharge_reward_detail_T reward_detail_conf;//奖励配置文件；

int read_recharge_reward_conf(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	
	int index=0;
	char* tempInfo=NULL;
	int tempSize=0;
	int memSize=sizeof(reward_detail_conf.reward_goods_id[0]);
	reward_time_conf.init();//时间配置初始化；
	reward_detail_conf.init();//奖励配置初始化；
	
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		cout<<"[XHM WARNING] xmlReadFile ERROR(read_recharge_reward_conf.cpp)!"<<endl;
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		cout<<"[XHM WARNING] xmlDocGetRootElement ERROR(read_recharge_reward_conf.cpp)!"<<endl;	
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_time;
	xmlNodePtr propNodePtr_reward;
	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"date"))
		{
			propNodePtr_time=curNode;
			xmlAttrPtr attrPtr=propNodePtr_time->properties;
			while(attrPtr!=NULL)
			{	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"year"))
				{
					xmlChar *year=xmlGetProp(propNodePtr_time,(const xmlChar*)"year");
					reward_time_conf.year=atoi(const_cast<char*>(reinterpret_cast<const char*>(year)));
					xmlFree(year);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"month"))
				{
					xmlChar *month=xmlGetProp(propNodePtr_time,(const xmlChar*)"month");
					reward_time_conf.month=atoi(const_cast<char *>(reinterpret_cast<const char *>(month)));
					xmlFree(month);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dayStart"))
				{
					xmlChar *dayStart=xmlGetProp(propNodePtr_time,(const xmlChar*)"dayStart");
					reward_time_conf.start_day=atoi(const_cast<char *>(reinterpret_cast<const char *>(dayStart)));
					xmlFree(dayStart);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dayEnd"))
				{
					xmlChar *dayEnd=xmlGetProp(propNodePtr_time,(const xmlChar*)"dayEnd");
					reward_time_conf.end_day=atoi(const_cast<char *>(reinterpret_cast<const char *>(dayEnd)));
					xmlFree(dayEnd);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"levelSize"))
				{
					xmlChar *levelSize=xmlGetProp(propNodePtr_time,(const xmlChar*)"levelSize");
					reward_detail_conf.levelcounts=atoi(const_cast<char *>(reinterpret_cast<const char *>(levelSize)));
					xmlFree(levelSize);
				}
				
				attrPtr=attrPtr->next;
			}
		}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"reward"))
		{
			propNodePtr_reward=curNode;
			xmlAttrPtr attrPtr=propNodePtr_reward->properties;
			while(attrPtr!=NULL)
			{	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"level"))
				{	
					xmlChar *level=xmlGetProp(propNodePtr_reward,(const xmlChar*)"level");
					index=atoi(const_cast<char *>(reinterpret_cast<const char *>(level)));
					if(reward_detail_conf.levelcounts < index)
					{
						cout<<"[XHM MSG] read_recharge_reward_conf.cpp read config ERROR!"<<endl;
					}
					xmlFree(level);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goodsIdA"))
				{	
					xmlChar *goodsIdA=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goodsIdA");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goodsIdA));
					memcpy(reward_detail_conf.reward_goods_id[index],tempInfo,memSize);
					xmlFree(goodsIdA);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goodsIdB"))
				{	
					xmlChar *goodsIdB=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goodsIdB");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goodsIdB));
					memcpy(reward_detail_conf.reward_goods_id2[index],tempInfo,memSize);
					xmlFree(goodsIdB);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rechargeNum"))
				{	
					xmlChar *rechargeNum=xmlGetProp(propNodePtr_reward,(const xmlChar*)"rechargeNum");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(rechargeNum)));
					reward_detail_conf.levelSize[index]=tempSize;
					xmlFree(rechargeNum);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"sizeA"))
				{	
					xmlChar *sizeA=xmlGetProp(propNodePtr_reward,(const xmlChar*)"sizeA");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(sizeA)));
					reward_detail_conf.reward_goods_num[index]=tempSize;
					xmlFree(sizeA);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"sizeB"))
				{	
					xmlChar *sizeB=xmlGetProp(propNodePtr_reward,(const xmlChar*)"sizeB");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(sizeB)));
					reward_detail_conf.reward_goods_num2[index]=tempSize;
					xmlFree(sizeB);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"bind_gold"))
				{	
					xmlChar *bind_gold=xmlGetProp(propNodePtr_reward,(const xmlChar*)"bind_gold");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(bind_gold)));
					reward_detail_conf.bind_gold[index]=tempSize;
					xmlFree(bind_gold);
				}						
				attrPtr=attrPtr->next;					
			}

		}
		curNode=curNode->next;
	}
	
	xmlFreeDoc(doc);		
	return 0;
}

