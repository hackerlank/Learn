/****************************************************************
 * Filename: read_guild_reward.cpp
 * 
 * Description: 读取人物基础及成长数据
 *
 * Original Author : bison, 2012-11-20
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "guild.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

map<string, GuildReward_T> id_2_guildReward;		//帮派奖励

int read_guild_reward(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	GuildReward_T tempGuildReward;		//帮派奖励
	int guildLevel = 0;
	
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
	
	id_2_guildReward.clear();
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Item"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//奖励项ID
					xmlChar *_id = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(tempGuildReward.id, (char*)_id, sizeof (tempGuildReward.id));
					xmlFree(_id);
				}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"brandType")) {
					//写到帮派历史的分类索引
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"brandType");
					tempGuildReward.brandType = atoi((char*)_item);
					xmlFree(_item);		
				}
			}
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//奖励数随等级变化
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Level"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"guildLevel")) {
							//帮派等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"guildLevel");
							guildLevel = atoi((char*)_item);
							xmlFree(_item);
							if (guildLevel < 1 || guildLevel > 5)
							{
								cout<<"Fuck wellion, you give an error guild reward config!!!"<<endl;
							}
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardGuildGlory")) {
							//奖励的帮派帮贡
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardGuildGlory");
							tempGuildReward.rewardGuildGlory[guildLevel - 1] = atoi((char*)_item);
							xmlFree(_item);
							
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardGuildExp")) {
							//奖励帮派经验
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardGuildExp");
							tempGuildReward.rewardGuildExp[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddLife[%d]: %d", level - 1, tempGuildReward.addLife[level - 1]);
							xmlFree(_item);
						}
#if 0						
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardGuildMoney")) {
							//奖励帮派资金
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardGuildMoney");
							tempGuildReward.rewardGuildMoney[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddMagic[%d]: %d", level - 1, tempGuildReward.addMagic[level - 1]);
							xmlFree(_item);
						}
#endif						
						else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardSelfGlory")) {
							//奖励个人帮贡
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardSelfGlory");
							tempGuildReward.rewardSelfGlory[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddOutDef[%d]: %d", level - 1, tempGuildReward.addOutDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardSelfExp")) {
							//奖励的个人经验
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardSelfExp");
							tempGuildReward.rewardSelfExp[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddInDef[%d]: %d", level - 1, tempGuildReward.addInDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardSelfMoney")) {
							//奖励的个人金钱
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardSelfMoney");
							tempGuildReward.rewardSelfMoney[guildLevel - 1] = atoi((char*)_item);
							// printf("\taddOutAttack[%d]: %d", level - 1, tempGuildReward.addOutAttack[level - 1]);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				}
			}
			
			id_2_guildReward.insert(pair<string, GuildReward_T>(tempGuildReward.id, tempGuildReward));
			
		}
	}
	
	// cout<<"have read conf by pary size is "<<id_2_guildReward.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}
