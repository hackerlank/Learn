/********************************************************************
    created:   2012/12/2
    filename:  read_campWar_reward_conf.cpp
    author:    xhm 
    depend:    libxml2.lib 
*********************************************************************/
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<iostream>
#include "camp_war_reward.h"
#include "data_structure_struct.h"

extern CampRewardData_T camp_reward_info[CAMP_WAR_REWARD_SIZE];			 //奖励	

using namespace std;

int read_campWar_reward_conf(char *fileName)
{
	int	index=0;
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	
	int tempValue=0;
	
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		cout<<"[XHM WARNING] xmlReadFile ERROR(read_campWar_reward_conf.cpp)!"<<endl;
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		cout<<"[XHM WARNING] xmlDocGetRootElement ERROR(read_campWar_reward_conf.cpp)!"<<endl;	
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_ordinary_campWar;
	xmlNodePtr propNodePtr_winner_leader_campWar;
	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"ordinary_campWar_reward"))
		{
			propNodePtr_ordinary_campWar=curNode;
			xmlAttrPtr attrPtr=propNodePtr_ordinary_campWar->properties;
			while(attrPtr!=NULL)
			{	
				tempValue=0;
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"gold_base_value"))
				{
					xmlChar *gold_base_value=xmlGetProp(propNodePtr_ordinary_campWar,(const xmlChar*)"gold_base_value");
					camp_reward_info[0].gold_base_value=atoi(const_cast<char*>(reinterpret_cast<const char*>(gold_base_value)));
					xmlFree(gold_base_value);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"gold_dec_value"))
				{
					xmlChar *gold_dec_value=xmlGetProp(propNodePtr_ordinary_campWar,(const xmlChar*)"gold_dec_value");
					camp_reward_info[0].gold_dec_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(gold_dec_value)));
					xmlFree(gold_dec_value);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"prestige_base_value"))
				{
					xmlChar *prestige_base_value=xmlGetProp(propNodePtr_ordinary_campWar,(const xmlChar*)"prestige_base_value");
					camp_reward_info[0].prestige_base_value=atoi(const_cast<char*>(reinterpret_cast<const char*>(prestige_base_value)));
					xmlFree(prestige_base_value);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"prestige_dec_value"))
				{
					xmlChar *prestige_dec_value=xmlGetProp(propNodePtr_ordinary_campWar,(const xmlChar*)"prestige_dec_value");
					camp_reward_info[0].prestige_dec_value=atoi(const_cast<char*>(reinterpret_cast<const char*>(prestige_dec_value)));
					xmlFree(prestige_dec_value);
				}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank_limit_value"))
				{
					xmlChar *rank_limit_value=xmlGetProp(propNodePtr_ordinary_campWar,(const xmlChar*)"rank_limit_value");
					camp_reward_info[0].rank_limit_value=atoi(const_cast<char*>(reinterpret_cast<const char*>(rank_limit_value)));			
					xmlFree(rank_limit_value);
				}
				attrPtr=attrPtr->next;
			}
		}else{
			index=0;
			if(!xmlStrcmp(curNode->name,(const xmlChar*)"winner_leader_campWar_reward"))
				index=1;
			if(!xmlStrcmp(curNode->name,(const xmlChar*)"failure_leader_campWar_reward"))
				index=2;
			if(!xmlStrcmp(curNode->name,(const xmlChar*)"first_chief_campWar_reward"))
				index=3;
			if(!xmlStrcmp(curNode->name,(const xmlChar*)"second_chief_campWar_reward"))
				index=4;
			if(!xmlStrcmp(curNode->name,(const xmlChar*)"third_chief_campWar_reward"))
				index=5;

			if(index > 0)
			{
				propNodePtr_winner_leader_campWar = curNode;
				xmlAttrPtr attrPtr=propNodePtr_winner_leader_campWar->properties;
				while(attrPtr!=NULL)
				{		
					if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"gold_base_value"))
					{
						xmlChar *gold_base_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"gold_base_value");
						camp_reward_info[index].gold_base_value=atoi(const_cast<char *>(reinterpret_cast<const char*>(gold_base_value)));
						xmlFree(gold_base_value);
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"gold_dec_value"))
					{
						xmlChar *gold_dec_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"gold_dec_value");
						camp_reward_info[index].gold_dec_value=atoi(const_cast<char *>(reinterpret_cast<const char*>(gold_dec_value)));
						xmlFree(gold_dec_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"prestige_base_value"))
					{
						xmlChar *prestige_base_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"prestige_base_value");
						camp_reward_info[index].prestige_base_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(prestige_base_value)));
						xmlFree(prestige_base_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"prestige_dec_value"))
					{
						xmlChar *prestige_dec_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"prestige_dec_value");
						camp_reward_info[index].prestige_dec_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(prestige_dec_value)));
						xmlFree(prestige_dec_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"guidGlory_base_value"))
					{
						xmlChar *guidGlory_base_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"guidGlory_base_value");
						camp_reward_info[index].guidGlory_base_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(guidGlory_base_value)));
						xmlFree(guidGlory_base_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"guidGlory_dec_value"))
					{
						xmlChar *guidGlory_dec_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"guidGlory_dec_value");
						camp_reward_info[index].guidGlory_dec_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(guidGlory_dec_value)));
						xmlFree(guidGlory_dec_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"guidExp_base_value"))
					{
						xmlChar *guidExp_base_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"guidExp_base_value");
						camp_reward_info[index].guidExp_base_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(guidExp_base_value)));
						xmlFree(guidExp_base_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"guidExp_dec_value"))
					{
						xmlChar *guidExp_dec_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"guidExp_dec_value");
						camp_reward_info[index].guidExp_dec_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(guidExp_dec_value)));
						xmlFree(guidExp_dec_value);	
					}else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank_limit_value"))
					{
						xmlChar *rank_limit_value=xmlGetProp(propNodePtr_winner_leader_campWar,(const xmlChar*)"rank_limit_value");
						camp_reward_info[index].rank_limit_value=atoi(const_cast<char *>(reinterpret_cast<const char *>(rank_limit_value)));
						xmlFree(rank_limit_value);	
					}
					attrPtr=attrPtr->next;
				}
			}
		}
		
		curNode=curNode->next;
	}
	
	xmlFreeDoc(doc);	
	#if 0
	//printf the value for test added by xhm
	for(int row = 0;row < 6;row ++)
	{
		cout<<camp_reward_info[row].gold_base_value<<",";	
		cout<<camp_reward_info[row].gold_dec_value<<",";				
		cout<<camp_reward_info[row].prestige_base_value<<",";		
		cout<<camp_reward_info[row].prestige_dec_value<<",";		
		cout<<camp_reward_info[row].guidGlory_base_value<<",";		
		cout<<camp_reward_info[row].guidGlory_dec_value<<",";		
		cout<<camp_reward_info[row].guidExp_base_value<<",";			
		cout<<camp_reward_info[row].guidExp_dec_value<<",";			
		cout<<camp_reward_info[row].rank_limit_value<<endl;		
	}
	#endif
	
	return 0;
}

