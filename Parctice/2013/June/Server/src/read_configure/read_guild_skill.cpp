/****************************************************************
 * Filename: read_guild_skill.cpp
 * 
 * Description: 读取帮派技能数据
 *
 * Original Author : bison, 2012-11-29
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

#define MAX_GUILD_SKILL_LEVEL 21				//帮派技能的最大等级

int read_guild_skill(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	char skillId[51] = {0};
	unsigned order = 0;
	unsigned openNeedGuildMoney = 0;
	unsigned openNeedGuildGlory = 0;
	unsigned initval = 0;
	unsigned addFactor = 0;
	unsigned upNeedMoneyBase = 0;
	unsigned upNeedMoneyFactor = 0;
	unsigned upNeedGloryFactor = 0;
	unsigned guildLevel = 0;
	unsigned canUpTo = 0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"guildSkill"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取一个帮派技能
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"skill"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
						{	
							//帮派技能Id
							xmlChar *_skillId = xmlGetProp(thirdNode, (const xmlChar*)"id");
							strncpy(skillId, const_cast<char *>(reinterpret_cast<const char *>(_skillId)), 51);
							xmlFree(_skillId);
						}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"order")) {
							//帮派技能的顺序
							xmlChar *_order = xmlGetProp(thirdNode, (const xmlChar*)"order");
							order = atoi(reinterpret_cast<const char*>(_order));
							xmlFree(_order);
						}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"openNeedGuildMoney")) {
							//开启需要帮派资金
							xmlChar *_openNeedGuildMoney = xmlGetProp(thirdNode, (const xmlChar*)"openNeedGuildMoney");
							openNeedGuildMoney = atoi(reinterpret_cast<const char*>(_openNeedGuildMoney));
							xmlFree(_openNeedGuildMoney);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"openNeedGuildGlory")) {
							//开启需要帮派帮贡
							xmlChar *_openNeedGuildGlory = xmlGetProp(thirdNode, (const xmlChar*)"openNeedGuildGlory");
							openNeedGuildGlory = atoi(reinterpret_cast<const char*>(_openNeedGuildGlory));
							xmlFree(_openNeedGuildGlory);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"initval")) {
							//技能初始值
							xmlChar *_initval = xmlGetProp(thirdNode, (const xmlChar*)"initval");
							initval = atoi(reinterpret_cast<const char*>(_initval));
							xmlFree(_initval);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addFactor")) {
							//技能增长值
							xmlChar *_addFactor = xmlGetProp(thirdNode, (const xmlChar*)"addFactor");
							addFactor = atoi(reinterpret_cast<const char*>(_addFactor));
							xmlFree(_addFactor);
						}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upNeedMoneyBase")) {
							//帮派技能升级金钱需求基数
							xmlChar *_upNeedMoneyBase = xmlGetProp(thirdNode, (const xmlChar*)"upNeedMoneyBase");
							upNeedMoneyBase = atoi(reinterpret_cast<const char*>(_upNeedMoneyBase));
							xmlFree(_upNeedMoneyBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upNeedMoneyFactor")) {
							//帮派技能升级金钱需求系数
							xmlChar *_upNeedMoneyFactor = xmlGetProp(thirdNode, (const xmlChar*)"upNeedMoneyFactor");
							upNeedMoneyFactor = atoi(reinterpret_cast<const char*>(_upNeedMoneyFactor));
							xmlFree(_upNeedMoneyFactor);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upNeedGloryFactor")) {
							//帮派技能升级帮贡需求系数
							xmlChar *_upNeedGloryFactor = xmlGetProp(thirdNode, (const xmlChar*)"upNeedGloryFactor");
							upNeedGloryFactor = atoi(reinterpret_cast<const char*>(_upNeedGloryFactor));
							xmlFree(_upNeedGloryFactor);
						} 
					}
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						//读取帮派技能升级限制
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"limit"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"guildLevel"))
								{
									//读取帮派等级
									xmlChar *_guildLevel = xmlGetProp(forthNode, (const xmlChar*)"guildLevel");
									guildLevel = atof(reinterpret_cast<const char*>(_guildLevel));
									xmlFree(_guildLevel);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"canUpTo")) {
									//读取当前等级下帮派能升到的级数
									xmlChar *_canUpTo = xmlGetProp(forthNode, (const xmlChar*)"canUpTo");
									canUpTo = atof(reinterpret_cast<const char*>(_canUpTo));
									xmlFree(_canUpTo);
								}
							}
							global_guild_skill[order].limit[guildLevel - 1] = canUpTo;
						}
					}
					memset(global_guild_skill[order].skillId, 0, sizeof(global_guild_skill[order].skillId));
					strncpy(global_guild_skill[order].skillId, skillId, strlen(skillId) + 1);
					global_guild_skill[order].skillOrder = order;
					global_guild_skill[order].openNeedGuildMoney = openNeedGuildMoney;
					global_guild_skill[order].openNeedGuildGlory = openNeedGuildGlory;
					global_guild_skill[order].addFactor = addFactor;
					global_guild_skill[order].upNeedGloryFactor = upNeedGloryFactor;
					global_guild_skill[order].upNeedMoneyFactor = upNeedMoneyFactor;
					global_guild_skill[order].addAttr[0] = initval;
					global_guild_skill[order].upNeedMoney[0] = upNeedMoneyBase;
					global_guild_skill[order].upNeedGlory[0] = 0;
					global_guild_skill[order].addTotal[0] = 0;
					
				}		
			}	
		}
	}
	
	cout<<"[BisonShow]@ read guild skill "<<endl;
	if (order != 9 || guildLevel != 5)
	{
		cout<<"order is "<<order<<" guildLevel is "<<guildLevel<<endl;
		cout<<"[BisonWarn] @read_guild_skill wellion's config of guild_skill is error!"<<endl;
	}
	
	// cout<<"|*********************FOR------TEST******************|"<<endl;
	for (order = 0; order < 10; order++)
	{
		// cout<<"-guildSkillId is "<<global_guild_skill[order].skillId<<"\t";
		// cout<<"guildSkillOrder is "<<global_guild_skill[order].skillOrder<<endl;
		// cout<<"-openNeedGuildMoney is "<<global_guild_skill[order].openNeedGuildMoney<<"\t";
		// cout<<"openNeedGuildGlory is "<<global_guild_skill[order].openNeedGuildGlory<<endl;
		// cout<<"-addAttr[0] is "<<global_guild_skill[order].addAttr[0]<<"\t";
		// cout<<"addTotal[0] is "<<global_guild_skill[order].addTotal[0]<<endl;
		// cout<<"-upNeedMoney[0] is "<<global_guild_skill[order].upNeedMoney[0]<<"\t";
		// cout<<"upNeedGlory[0] is "<<global_guild_skill[order].upNeedGlory[0]<<endl;
		for (int level = 1; level < MAX_GUILD_SKILL_LEVEL; level++)
		{
			// cout<<"--guildSkillLevel is "<<level<<endl;
			unsigned sqrLevel = level * level; 
			
			
			if (level == 1)
			{
				
				if (order == 0 || order == 1)
				{
					global_guild_skill[order].addAttr[level] = global_guild_skill[order].addAttr[level - 1];
					
				} else {
					global_guild_skill[order].addAttr[level] = global_guild_skill[order].addAttr[level - 1];
				}
				
				global_guild_skill[order].upNeedMoney[level] = global_guild_skill[order].upNeedMoney[0];
			}
			else {
				if (order == 0 || order == 1)
				{
					global_guild_skill[order].addAttr[level] = global_guild_skill[order].addFactor * sqrLevel;
					
				} else {
					global_guild_skill[order].addAttr[level] = global_guild_skill[order].addFactor * level;
				}
				
				global_guild_skill[order].upNeedMoney[level] = global_guild_skill[order].upNeedMoney[level - 1]
															 + global_guild_skill[order].upNeedMoneyFactor * sqrLevel;
			}
			
			global_guild_skill[order].upNeedGlory[level] = level * global_guild_skill[order].upNeedGloryFactor;
			
			global_guild_skill[order].addTotal[level] = global_guild_skill[order].addTotal[level - 1]
															 + global_guild_skill[order].addAttr[level];
															 
			// cout<<"---addAttr["<<level<<"] is "<<global_guild_skill[order].addAttr[level]<<"\t";
			// cout<<"addTotal["<<level<<"] is "<<global_guild_skill[order].addTotal[level]<<endl;
			// cout<<"----upNeedMoney["<<level<<"] is "<<global_guild_skill[order].upNeedMoney[level]<<"\t";
			// cout<<"upNeedGlory["<<level<<"] is "<<global_guild_skill[order].upNeedGlory[level]<<endl;
		}
		
		
		/************************************************FOR------TEST******************************************************/
		
		
	}
	
	xmlFreeDoc(doc);
	return 0;
}