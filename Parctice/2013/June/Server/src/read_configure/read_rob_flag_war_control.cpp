/****************************************************************
 * Filename: read_rob_flag_war_control.cpp
 * 
 * Description: 读取夺旗战配置
 *
 * Original Author : bison, 2013-4-12
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "rob_flag_war.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

RobFlagWarControl_T robFlagWarCtl;

int read_rob_flag_war_control(char *fileName)
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"rob_flag_war_control"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"quickStartNeedHeroNum"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"quickStartNeedHeroNum");
					robFlagWarCtl.quickStartNeedHeroNum = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"radius"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"radius");
					robFlagWarCtl.scoreRadius = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"time_item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lockTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"lockTime");
							robFlagWarCtl.lockTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prepareTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"prepareTime");
							robFlagWarCtl.prepareTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"readyTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"readyTime");
							robFlagWarCtl.readyTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pkTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"pkTime");
							robFlagWarCtl.pkTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardTime");
							robFlagWarCtl.rewardTime = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"location_item")) 
				{
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"scoreLoc1")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"mapId"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"mapId");
									strncpy(robFlagWarCtl.scorePlace[0].mapId, (char*)_item, 51);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"x"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"x");
									robFlagWarCtl.scorePlace[0].pixelPt._x = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"y"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"y");
									robFlagWarCtl.scorePlace[0].pixelPt._y = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"scoreLoc2")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"mapId"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"mapId");
									strncpy(robFlagWarCtl.scorePlace[1].mapId, (char*)_item, 51);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"x"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"x");
									robFlagWarCtl.scorePlace[1].pixelPt._x = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"y"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"y");
									robFlagWarCtl.scorePlace[1].pixelPt._y = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						}
					}
				}  else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"score_item")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"flagScore"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"flagScore");
							robFlagWarCtl.flagScore = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"reward_item")) 
				{
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"winGuildReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									robFlagWarCtl.winGuildReward.money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									robFlagWarCtl.winGuildReward.glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"prestige");
									robFlagWarCtl.winGuildReward.prestige = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									robFlagWarCtl.winGuildReward.reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"loseGuildReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									robFlagWarCtl.loseGuildReward.money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									robFlagWarCtl.loseGuildReward.glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"prestige");
									robFlagWarCtl.loseGuildReward.prestige = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									robFlagWarCtl.loseGuildReward.reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"encourageReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									robFlagWarCtl.encourageReward.money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									robFlagWarCtl.encourageReward.glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"prestige"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"prestige");
									robFlagWarCtl.encourageReward.prestige = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									robFlagWarCtl.encourageReward.reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						}
					}
				}
			}	
		}
	}
	cout<<"[BisonShow] read_rob_flag_war_control "<<endl;
	xmlFreeDoc(doc);
	return 0;
}