/****************************************************************
 * Filename: read_hero_skill.cpp
 * 
 * Description: 读取人物技能数据
 *
 * Original Author : bison, 2012-11-14
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "hero_skill.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;
extern map<string, HeroSkill*> skillId_2_heroSkill;		//角色技能
HeroMemSkill_T M_SkillBase[HERO_SKILL_MAX_NUM];
HeroMemSkill_T H_SkillBase[HERO_SKILL_MAX_NUM];
HeroMemSkill_T G_SkillBase[HERO_SKILL_MAX_NUM];
HeroMemSkill_T X_SkillBase[HERO_SKILL_MAX_NUM];

int read_hero_skill(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	HeroSkill_T tempSkill;				//技能数据
	unsigned level = 0;
	
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
	
	skillId_2_heroSkill.clear();
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"skill"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//人物技能ID
					xmlChar *_skillId = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(tempSkill.skillId, (char*)_skillId, sizeof (tempSkill.skillId));
					xmlFree(_skillId);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"type")) {
					//人物技能类型
					xmlChar *_type = xmlGetProp(secondNode, (const xmlChar*)"type");
					tempSkill.type = atoi((char*)_type);
					xmlFree(_type);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"buffType")) {
					//技能附带buff类型
					xmlChar *_buffType = xmlGetProp(secondNode, (const xmlChar*)"buffType");
					tempSkill.buffType = atoi((char*)_buffType);
					xmlFree(_buffType);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attackDistance")) {
					//技能攻击范围
					xmlChar *_attackRange = xmlGetProp(secondNode, (const xmlChar*)"attackDistance");
					tempSkill.attackRange = atoi((char*)_attackRange);
					xmlFree(_attackRange);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hurtRange")) {
					//技能伤害范围
					xmlChar *_attackRange = xmlGetProp(secondNode, (const xmlChar*)"hurtRange");
					tempSkill.hurtRange = atoi((char*)_attackRange);
					xmlFree(_attackRange);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"animationTime")) {
					//技能动画时间
					xmlChar *_animationTime = xmlGetProp(secondNode, (const xmlChar*)"animationTime");
					tempSkill.animationTime = atof((char*)_animationTime);
					xmlFree(_animationTime);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"partyFactor")) {
					//门派伤害系数（普攻系数）
					xmlChar *_partyFactor = xmlGetProp(secondNode, (const xmlChar*)"partyFactor");
					tempSkill.partyFactor = atof((char*)_partyFactor);
					xmlFree(_partyFactor);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attkType")) {
					//攻击类型
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"attkType");
					tempSkill.attkType = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取技能等级影响项
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"upgrade"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"level")) {
							//技能等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"level");
							level = atoi((char*)_item);
							if (level > 20)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of hero skill"<<tempSkill.skillId<<" is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"heroLevel")) {
							//技能升级需要的人物等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"heroLevel");
							tempSkill.upgradeNeedHeroLevel[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needMoney")) {
							//技能升级需要的金钱
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needMoney");
							tempSkill.upgradeNeedMoney[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needExp")) {
							//技能升级需要的经验
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needExp");
							tempSkill.upgradeNeedExp[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cdTime")) {
							//技能CD时间
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"cdTime");
							tempSkill.cdTime[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"magic")) {
							//技能耗魔
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"magic");
							tempSkill.needMagic[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skillFactor")) {
							//技能伤害系数
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"skillFactor");
							tempSkill.factor[level - 1] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value")) {
							//技能数值
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"value");
							tempSkill.value[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value1")) {
							//技能附加总数值
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"value1");
							tempSkill.totalVal[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"value2")) {
							//技能附加总数值
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"value2");
							tempSkill.attkNum[level - 1] = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				}
			}
			HeroSkill *heroSkill = new HeroSkill(tempSkill);
			skillId_2_heroSkill.insert(pair<string, HeroSkill*>(tempSkill.skillId, heroSkill));
			
		}
	}
	
	// cout<<"[BisonShow]@read_hero_skill.cpp all heroSkill size is "<<skillId_2_heroSkill.size()<<endl;
	for (int i = 0; i < HERO_SKILL_MAX_NUM; i++)
	{
		memset(M_SkillBase, 0, sizeof(M_SkillBase));
		sprintf(M_SkillBase[i].skillId, "M%03d", i);
		M_SkillBase[i].level = 0;
		memset(H_SkillBase, 0, sizeof(H_SkillBase));
		sprintf(H_SkillBase[i].skillId, "H%03d", i);
		H_SkillBase[i].level = 0;
		memset(G_SkillBase, 0, sizeof(G_SkillBase));
		sprintf(G_SkillBase[i].skillId, "G%03d", i);
		G_SkillBase[i].level = 0;
		memset(X_SkillBase, 0, sizeof(X_SkillBase));
		sprintf(X_SkillBase[i].skillId, "X%03d", i);
		X_SkillBase[i].level = 0;
		// cout<<"init one skillId and skillId is "<<X_SkillBase[i].skillId<<endl;
		
	}
	xmlFreeDoc(doc);
	return 0;
}
