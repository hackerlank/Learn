/****************************************************************
 * Filename: read_hero_conf.cpp
 * 
 * Description: 读取人物基础及成长数据
 *
 * Original Author : bison, 2012-11-20
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "hero_conf.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

map<string, Hero_Conf_T> party_2_heroConf;		//各门派的角色配置

int read_hero_conf(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	Hero_Conf_T tempHeroConf;			//角色配置
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
	
	party_2_heroConf.clear();
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"hero"))
		{
			Point tempPt;
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"party"))
				{	
					//门派ID
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"party");
					strncpy(tempHeroConf.party, (char*)_item, sizeof (tempHeroConf.party));
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pt_x")) {
					//出生点x
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"pt_x");
					tempPt._x = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pt_y")) {
					//出生点y
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"pt_y");
					tempPt._y = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"mapId"))
				{	
					//出生图ID
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"mapId");
					strncpy(tempHeroConf.mapId, (char*)_item, sizeof (tempHeroConf.mapId));
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attkType")) {
					//攻击类型
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"attkType");
					tempHeroConf.attkType = atoi((char*)_item);
					xmlFree(_item);
				}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lifeUpperVal")) {
					//出生生命
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"lifeUpperVal");
					tempHeroConf.lifeUpperVal = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"magicUpperVal")) {
					//出生魔法
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"magicUpperVal");
					tempHeroConf.magicUpperVal = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outDef")) {
					//外防御
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"outDef");
					tempHeroConf.outDef = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inDef")) {
					//内防御
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"inDef");
					tempHeroConf.inDef = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outAttack")) {
					//外功攻击
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"outAttack");
					tempHeroConf.outAttack = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inAttack")) {
					//内功攻击
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"inAttack");
					tempHeroConf.inAttack = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hited")) {
					//命中
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"hited");
					tempHeroConf.hited = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"crit")) {
					//暴击
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"crit");
					tempHeroConf.crit = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"dodge")) {
					//闪避
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"dodge");
					tempHeroConf.dodge = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"tenacity")) {
					//韧性
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"tenacity");
					tempHeroConf.tenacity = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"outHurt")) {
					//外伤害
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"outHurt");
					tempHeroConf.outHurt = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"inHurt")) {
					//内伤害
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"inHurt");
					tempHeroConf.inHurt = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"yueliReward")) {
					//内伤害
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"yueliReward");
					tempHeroConf.bornHeroSkillExp = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			//出生点
			tempHeroConf.bornPt = tempPt;
			// cout<<"************************party:"<<tempHeroConf.party<<"****************************"<<endl;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取等级影响项
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"level"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lvl")) {
							//技能等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"lvl");
							level = atoi((char*)_item);
							if (level < 1 || level > 200)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of hero conf "<<tempHeroConf.party<<" is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
							// cout<<"level:"<<level<<endl;
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needExp")) {
							//人物升级需要经验
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needExp");
							tempHeroConf.upgradeNeedExp[level - 1] = atoi((char*)_item);
							xmlFree(_item);
							// printf("nedExp[%d]: %d", level - 1, tempHeroConf.upgradeNeedExp[level - 1]);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addLife")) {
							//升级增加生命
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addLife");
							tempHeroConf.addLife[level - 1] = atoi((char*)_item);
							// printf("\taddLife[%d]: %d", level - 1, tempHeroConf.addLife[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addMagic")) {
							//升级增加魔法
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addMagic");
							tempHeroConf.addMagic[level - 1] = atoi((char*)_item);
							// printf("\taddMagic[%d]: %d", level - 1, tempHeroConf.addMagic[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addOutDef")) {
							//升级增加外功防御
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addOutDef");
							tempHeroConf.addOutDef[level - 1] = atoi((char*)_item);
							// printf("\taddOutDef[%d]: %d", level - 1, tempHeroConf.addOutDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addInDef")) {
							//升级增加内功防御
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addInDef");
							tempHeroConf.addInDef[level - 1] = atoi((char*)_item);
							// printf("\taddInDef[%d]: %d", level - 1, tempHeroConf.addInDef[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addOutAttack")) {
							//升级增加外功攻击
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addOutAttack");
							tempHeroConf.addOutAttack[level - 1] = atoi((char*)_item);
							// printf("\taddOutAttack[%d]: %d", level - 1, tempHeroConf.addOutAttack[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addInAttack")) {
							//升级增加内功攻击
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addInAttack");
							tempHeroConf.addInAttack[level - 1] = atoi((char*)_item);
							// printf("\taddInAttack[%d]: %d", level - 1, tempHeroConf.addInAttack[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addHited")) {
							//升级增加命中
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addHited");
							tempHeroConf.addHited[level - 1] = atoi((char*)_item);
							// printf("\taddHited[%d]: %d", level - 1, tempHeroConf.addHited[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addCrit")) {
							//升级增加暴击
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addCrit");
							tempHeroConf.addCrit[level - 1] = atoi((char*)_item);
							// printf("\taddCrit[%d]: %d", level - 1, tempHeroConf.addCrit[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addDodge")) {
							//升级增加闪避
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addDodge");
							tempHeroConf.addDodge[level - 1] = atoi((char*)_item);
							// printf("\taddDodge[%d]: %d", level - 1, tempHeroConf.addDodge[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addTenacity")) {
							//升级增加韧性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addTenacity");
							tempHeroConf.addTenacity[level - 1] = atoi((char*)_item);
							// printf("\taddTenacity[%d]: %d", level - 1, tempHeroConf.addTenacity[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addOutHurt")) {
							//升级增加外功伤害
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addOutHurt");
							tempHeroConf.addOutHurt[level - 1] = atoi((char*)_item);
							// printf("\taddOutHurt[%d]: %d", level - 1, tempHeroConf.addOutHurt[level - 1]);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"addInHurt")) {
							//升级增加的内功伤害
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"addInHurt");
							tempHeroConf.addInHurt[level - 1] = atoi((char*)_item);
							// printf("\taddInHurt[%d]: %d", level - 1, tempHeroConf.addInHurt[level - 1]);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				}
			}
			party_2_heroConf.insert(pair<string, Hero_Conf_T>(tempHeroConf.party, tempHeroConf));
			
		}
	}
	
	// cout<<"[BisonShow]@read_hero_conf.cpp all heroConf size is "<<sizeof(Hero_Conf_T) * 4<<endl;
	// cout<<"have read conf by pary size is "<<party_2_heroConf.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}
