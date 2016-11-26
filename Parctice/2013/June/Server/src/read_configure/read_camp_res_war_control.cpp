/****************************************************************
 * Filename: read_camp_res_war_control.cpp
 * 
 * Description: 读取阵营资源战配置
 *
 * Original Author : bison, 2012-3-29
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "camp_res_war.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

CRW_Control_T campResWarCtl;

int read_camp_res_war_control(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	//解析文件
	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER);
	if (doc == NULL)
	{
		return -1;
	}

	//得到xml文件的root
	rootNode = xmlDocGetRootElement(doc);
	if (rootNode == NULL)
	{
		xmlFreeDoc(doc);
		return -1;
	}
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"room_control"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"brushNumPerTimes"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"brushNumPerTimes");
					campResWarCtl.brushNumPerTimes = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pickScore"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"pickScore");
					campResWarCtl.pickScore = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"perCampLimitHeros"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"perCampLimitHeros");
					campResWarCtl.perCampLimitHeros = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"roomLimitHeros"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"roomLimitHeros");
					campResWarCtl.roomLimitHeros = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"time_ctl"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prepareTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prepareTime");
							campResWarCtl.prepareTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pkTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"pkTime");
							campResWarCtl.pkTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"brushTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"brushTime");
							campResWarCtl.brushTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardTime");
							campResWarCtl.rewardTime = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"from_location")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fromMap"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"fromMap");
							strncpy(campResWarCtl.from.mapId, (char*)_item, 51);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fromPt_X"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"fromPt_X");
							campResWarCtl.from.pixelPt._x = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fromPt_Y"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"fromPt_Y");
							campResWarCtl.from.pixelPt._y = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"camp_win_reward")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"minScore"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"minScore");
							campResWarCtl.winCampRewardMinScore = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"money");
							campResWarCtl.winCampRewardMoney = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prestige");
							campResWarCtl.winCampRewardPtg = atoi((char*)_item);
							xmlFree(_item);
						}
					}		
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"join_reward")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"money");
							campResWarCtl.joinRewardMoney = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prestige");
							campResWarCtl.joinRewardPtg = atoi((char*)_item);
							xmlFree(_item);
						}
					}			
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"res_num_reward")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"moneyBase"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"moneyBase");
							campResWarCtl.resNumRewardMoneyBase = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestigeBase"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prestigeBase");
							campResWarCtl.resNumRewardPtgBases = atoi((char*)_item);
							xmlFree(_item);
						}
					}	
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"rank_fst_reward")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"minScore"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"minScore");
							campResWarCtl.rankReward[0].minScore = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"money");
							campResWarCtl.rankReward[0].money = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prestige");
							campResWarCtl.rankReward[0].prestige = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsId"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"goodsId");
							strncpy(campResWarCtl.rankReward[0].goodsId, (char*)_item, 51);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"rank_scd_reward")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"minScore"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"minScore");
							campResWarCtl.rankReward[1].minScore = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"money");
							campResWarCtl.rankReward[1].money = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prestige");
							campResWarCtl.rankReward[1].prestige = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsId"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"goodsId");
							strncpy(campResWarCtl.rankReward[1].goodsId, (char*)_item, 51);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"rank_thd_reward")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"minScore"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"minScore");
							campResWarCtl.rankReward[2].minScore = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"money");
							campResWarCtl.rankReward[2].money = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prestige");
							campResWarCtl.rankReward[2].prestige = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"goodsId"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"goodsId");
							strncpy(campResWarCtl.rankReward[2].goodsId, (char*)_item, 51);
							xmlFree(_item);
						}
					}
				}
			}	
		}
	}
	cout<<"[BisonShow] read_camp_res_war_control "<<endl;
	xmlFreeDoc(doc);
	return 0;
}