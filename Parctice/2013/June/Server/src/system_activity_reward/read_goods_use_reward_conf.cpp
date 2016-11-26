/********************************************************************
    created:   2012/12/2
    filename:  read_goods_use_reward.cpp
    author:    xhm 
    depend:    libxml2.lib 
*********************************************************************/
#include"function_read_configuration_files.h"

#include<libxml/parser.h>
#include<iostream>

#include "system_activity_reward_assist.h"

using namespace std;

extern Goods_oper_reward_T flowers_send_reward_detail;//送鲜花奖励
extern Goods_oper_reward_T flowers_gain_reward_detail;//得到鲜花奖励

int read_good_use_reward_conf(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	
	int tempSize=0;
	char* tempInfo=NULL;
	flowers_send_reward_detail.init();
	flowers_gain_reward_detail.init();
	
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		cout<<"[XHM WARNING] xmlReadFile ERROR(read_goods_use_reward.cpp)!"<<endl;
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		cout<<"[XHM WARNING] xmlDocGetRootElement ERROR(read_goods_use_reward.cpp)!"<<endl;	
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
					flowers_send_reward_detail.year=atoi(const_cast<char*>(reinterpret_cast<const char*>(year)));
					flowers_gain_reward_detail.year = flowers_send_reward_detail.year;
					xmlFree(year);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"month"))
				{
					xmlChar *month=xmlGetProp(propNodePtr_time,(const xmlChar*)"month");
					flowers_send_reward_detail.month=atoi(const_cast<char *>(reinterpret_cast<const char *>(month)));
					flowers_gain_reward_detail.month = flowers_send_reward_detail.month;					
					xmlFree(month);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dayStart"))
				{
					xmlChar *dayStart=xmlGetProp(propNodePtr_time,(const xmlChar*)"dayStart");
					flowers_send_reward_detail.start_day=atoi(const_cast<char *>(reinterpret_cast<const char *>(dayStart)));
					flowers_gain_reward_detail.start_day = flowers_send_reward_detail.start_day;	
					xmlFree(dayStart);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dayEnd"))
				{
					xmlChar *dayEnd=xmlGetProp(propNodePtr_time,(const xmlChar*)"dayEnd");
					flowers_send_reward_detail.end_day=atoi(const_cast<char *>(reinterpret_cast<const char *>(dayEnd)));
					flowers_gain_reward_detail.end_day = flowers_send_reward_detail.end_day;	
					xmlFree(dayEnd);
				}
				
				attrPtr=attrPtr->next;
			}
		}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"use_goods"))
		{
			propNodePtr_reward=curNode;
			xmlAttrPtr attrPtr=propNodePtr_reward->properties;
			while(attrPtr!=NULL)
			{	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods_id_1"))
				{	
					xmlChar *goods_id_1=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goods_id_1");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goods_id_1));
					memcpy(flowers_send_reward_detail.good_id[0],tempInfo,sizeof(flowers_send_reward_detail.good_id[0]));
					xmlFree(goods_id_1);
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods_id_2"))
				{	
					xmlChar *goods_id_2=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goods_id_2");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goods_id_2));
					memcpy(flowers_send_reward_detail.good_id[1],tempInfo,sizeof(flowers_send_reward_detail.good_id[1]));
					xmlFree(goods_id_2);
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods_id_3"))
				{	
					xmlChar *goods_id_3=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goods_id_3");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goods_id_3));
					memcpy(flowers_send_reward_detail.good_id[2],tempInfo,sizeof(flowers_send_reward_detail.good_id[2]));
					xmlFree(goods_id_3);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"size_1"))
				{	
					xmlChar *size_1=xmlGetProp(propNodePtr_reward,(const xmlChar*)"size_1");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(size_1)));
					flowers_send_reward_detail.goods_reward_obj[0].size=tempSize;
					xmlFree(size_1);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"size_2"))
				{	
					xmlChar *size_2=xmlGetProp(propNodePtr_reward,(const xmlChar*)"size_2");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(size_2)));
					flowers_send_reward_detail.goods_reward_obj[1].size=tempSize;
					xmlFree(size_2);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"size_3"))
				{	
					xmlChar *size_3=xmlGetProp(propNodePtr_reward,(const xmlChar*)"size_3");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(size_3)));
					flowers_send_reward_detail.goods_reward_obj[2].size=tempSize;
					xmlFree(size_3);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"present_id1"))
				{	
					xmlChar *present_id1=xmlGetProp(propNodePtr_reward,(const xmlChar*)"present_id1");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(present_id1));
					memcpy(flowers_send_reward_detail.goods_reward_obj[0].reward_goods_id,tempInfo,sizeof(flowers_send_reward_detail.good_id[2]));
					xmlFree(present_id1);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"present_id2"))
				{	
					xmlChar *present_id2=xmlGetProp(propNodePtr_reward,(const xmlChar*)"present_id2");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(present_id2));
					memcpy(flowers_send_reward_detail.goods_reward_obj[1].reward_goods_id,tempInfo,sizeof(flowers_send_reward_detail.good_id[2]));
					xmlFree(present_id2);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"present_id3"))
				{	
					xmlChar *present_id3=xmlGetProp(propNodePtr_reward,(const xmlChar*)"present_id3");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(present_id3));
					memcpy(flowers_send_reward_detail.goods_reward_obj[2].reward_goods_id,tempInfo,sizeof(flowers_send_reward_detail.good_id[2]));
					xmlFree(present_id3);
				}		
				
				attrPtr=attrPtr->next;					
			}

		}else if(!xmlStrcmp(curNode->name,(const xmlChar *)"gain_goods"))
		{
			propNodePtr_reward=curNode;
			xmlAttrPtr attrPtr=propNodePtr_reward->properties;
			while(attrPtr!=NULL)
			{	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods_id_1"))
				{	
					xmlChar *goods_id_1=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goods_id_1");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goods_id_1));
					memcpy(flowers_gain_reward_detail.good_id[0],tempInfo,sizeof(flowers_gain_reward_detail.good_id[0]));
					xmlFree(goods_id_1);
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods_id_2"))
				{	
					xmlChar *goods_id_2=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goods_id_2");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goods_id_2));
					memcpy(flowers_gain_reward_detail.good_id[1],tempInfo,sizeof(flowers_gain_reward_detail.good_id[1]));
					xmlFree(goods_id_2);
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"goods_id_3"))
				{	
					xmlChar *goods_id_3=xmlGetProp(propNodePtr_reward,(const xmlChar*)"goods_id_3");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(goods_id_3));
					memcpy(flowers_gain_reward_detail.good_id[2],tempInfo,sizeof(flowers_gain_reward_detail.good_id[2]));
					xmlFree(goods_id_3);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"size_1"))
				{	
					xmlChar *size_1=xmlGetProp(propNodePtr_reward,(const xmlChar*)"size_1");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(size_1)));
					flowers_gain_reward_detail.goods_reward_obj[0].size=tempSize;
					// cout<<"[XHM MSG] read_goods_use_reward_conf.cpp size1:"<<tempSize<<endl;
					xmlFree(size_1);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"size_2"))
				{	
					xmlChar *size_2=xmlGetProp(propNodePtr_reward,(const xmlChar*)"size_2");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(size_2)));
					// cout<<"[XHM MSG] read_goods_use_reward_conf.cpp size3:"<<tempSize<<endl;
					flowers_gain_reward_detail.goods_reward_obj[1].size=tempSize;
					xmlFree(size_2);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"size_3"))
				{	
					xmlChar *size_3=xmlGetProp(propNodePtr_reward,(const xmlChar*)"size_3");
					tempSize=atoi(const_cast<char *>(reinterpret_cast<const char *>(size_3)));
					// cout<<"[XHM MSG] read_goods_use_reward_conf.cpp size3:"<<tempSize<<endl;
					flowers_gain_reward_detail.goods_reward_obj[2].size=tempSize;
					xmlFree(size_3);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"present_id1"))
				{	
					xmlChar *present_id1=xmlGetProp(propNodePtr_reward,(const xmlChar*)"present_id1");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(present_id1));
					memcpy(flowers_gain_reward_detail.goods_reward_obj[0].reward_goods_id,tempInfo,sizeof(flowers_gain_reward_detail.good_id[2]));
					// cout<<"[XHM MSG] read_goods_use_reward_conf.cpp flowers_gain_reward_detail.goods_reward_obj[0].reward_goods_id:"<<flowers_gain_reward_detail.goods_reward_obj[0].reward_goods_id<<endl;
					xmlFree(present_id1);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"present_id2"))
				{	
					xmlChar *present_id2=xmlGetProp(propNodePtr_reward,(const xmlChar*)"present_id2");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(present_id2));
					memcpy(flowers_gain_reward_detail.goods_reward_obj[1].reward_goods_id,tempInfo,sizeof(flowers_gain_reward_detail.good_id[2]));
					// cout<<"[XHM MSG] read_goods_use_reward_conf.cpp flowers_gain_reward_detail.goods_reward_obj[1].reward_goods_id:"<<flowers_gain_reward_detail.goods_reward_obj[1].reward_goods_id<<endl;
					xmlFree(present_id2);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"present_id3"))
				{	
					xmlChar *present_id3=xmlGetProp(propNodePtr_reward,(const xmlChar*)"present_id3");
					tempInfo=const_cast<char *>(reinterpret_cast<const char *>(present_id3));
					memcpy(flowers_gain_reward_detail.goods_reward_obj[2].reward_goods_id,tempInfo,sizeof(flowers_gain_reward_detail.good_id[2]));
					// cout<<"[XHM MSG] read_goods_use_reward_conf.cpp flowers_gain_reward_detail.goods_reward_obj[2].reward_goods_id:"<<flowers_gain_reward_detail.goods_reward_obj[2].reward_goods_id<<endl;					
					xmlFree(present_id3);
				}		
				
				attrPtr=attrPtr->next;					
			}

		}
		curNode=curNode->next;
	}
	
	xmlFreeDoc(doc);		
	return 0;
}

