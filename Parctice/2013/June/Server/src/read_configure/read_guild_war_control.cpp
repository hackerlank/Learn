/****************************************************************
 * Filename: read_camp_res_war_control.cpp
 * 
 * Description: 读取阵营资源战配置
 *
 * Original Author : bison, 2012-3-29
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "guild_war_room.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

GuildWarControl_T guildWarCtl;

int read_guild_war_control(char *fileName)
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"guild_war_control"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"quickStartNeedHeroNum"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"quickStartNeedHeroNum");
					guildWarCtl.quickStartNeedHeroNum = atoi((char*)_item);
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
							guildWarCtl.lockTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"perpareTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"perpareTime");
							guildWarCtl.perpareTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"readyTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"readyTime");
							guildWarCtl.readyTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"pkTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"pkTime");
							guildWarCtl.pkTime = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardTime");
							guildWarCtl.rewardTime = atoi((char*)_item);
							xmlFree(_item);
						}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"protectTime"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"protectTime");
							guildWarCtl.protectTime = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"score_item")) 
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"killScoreOfHero"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"killScoreOfHero");
							guildWarCtl.killScoreOfHero = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"killScoreOfGuild"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"killScoreOfGuild");
							guildWarCtl.killScoreOfGuild = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"AFlagScoreOfHero"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"AFlagScoreOfHero");
							guildWarCtl.flagScoreOfHero[0] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"AFlagScoreOfGuild"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"AFlagScoreOfGuild");
							guildWarCtl.flagScoreOfGuild[0] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"BFlagScoreOfHero"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"BFlagScoreOfHero");
							guildWarCtl.flagScoreOfHero[1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"BFlagScoreOfGuild"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"BFlagScoreOfGuild");
							guildWarCtl.flagScoreOfGuild[1] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"MFlagScoreOfHero"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"MFlagScoreOfHero");
							guildWarCtl.flagScoreOfHero[2] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"MFlagScoreOfGuild"))
						{	
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"MFlagScoreOfGuild");
							guildWarCtl.flagScoreOfGuild[2] = atoi((char*)_item);
							xmlFree(_item);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"reward_item")) 
				{
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"joinReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.joinReward.money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.joinReward.glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.joinReward.reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"scoreReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"moneyBase"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"moneyBase");
									guildWarCtl.scoreRewardBase.money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"gloryBase"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"gloryBase");
									guildWarCtl.scoreRewardBase.glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.scoreRewardBase.reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"winGuildFirstReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[0].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[0].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[0].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"winGuildSecondReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[1].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[1].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[1].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"winGuildThirdReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[2].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[2].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[2].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"winGuildOtherReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[3].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[3].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[3].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						}  else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"loseGuildFirstReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[0].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[0].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[0].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"loseGuildSecondReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[1].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[1].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[1].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"loseGuildThirdReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[2].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[2].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[2].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						} else if (!xmlStrcmp(forthNode->name, (const xmlChar*)"loseGuildOtherReward")) 
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"money"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"money");
									guildWarCtl.winRankReward[3].money = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"glory"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"glory");
									guildWarCtl.winRankReward[3].glory = atoi((char*)_item);
									xmlFree(_item);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"reserved"))
								{	
									xmlChar *_item = xmlGetProp(forthNode, (const xmlChar*)"reserved");
									guildWarCtl.winRankReward[3].reserved = atoi((char*)_item);
									xmlFree(_item);
								}
							}
						}
					}
				}
			}	
		}
	}
	cout<<"[BisonShow] read_guild_war_control "<<endl;
	xmlFreeDoc(doc);
	return 0;
}