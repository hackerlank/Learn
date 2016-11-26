/****************************************************************
 * Filename: read_guild_activity.cpp
 * 
 * Description: 读取帮派活动信息
 *
 * Original Author : bison, 2012-9-13
 *
 ****************************************************************/
 
#include"guild_activity.h"
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

extern map<string, GuildActivity*> id_2_guildAct;		//帮派活动实例

int read_guild_activity_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	int guildLevelLimit;				//帮派等级限制
	char id[51];							//活动ID
	int weekDay;						//天数
	int beginHour;						//开始时数
	int beginMin;						//开始分数
	int endHour;						//活动结束时间点
	int endMin;							//活动结束的分钟数

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
		//逐个读取帮派活动节点
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Activity"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//活动名
					xmlChar *_id = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);
					xmlFree(_id);
					
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"guildLevelLimit")) {
					//活动对帮派等级的限制
					xmlChar *_limit = xmlGetProp(secondNode, (const xmlChar*)"guildLevelLimit");
					guildLevelLimit = atoi(reinterpret_cast<const char*>(_limit));
					xmlFree(_limit);
				}
			}
			
			//读取活动时间节点
			
			set<ActivityTime_T*> timeSet;
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Time"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"weekDay"))
						{	
							//活动日
							xmlChar *_weekDay = xmlGetProp(thirdNode, (const xmlChar*)"weekDay");
							weekDay = atoi(reinterpret_cast<const char*>(_weekDay));
							xmlFree(_weekDay);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"beginHour")) {
							//活动开始时
							xmlChar *_beginHour = xmlGetProp(thirdNode, (const xmlChar*)"beginHour");
							beginHour = atoi(reinterpret_cast<const char*>(_beginHour));
							xmlFree(_beginHour);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"beginMin")) {
							//活动开始分
							xmlChar *_beginMin = xmlGetProp(thirdNode, (const xmlChar*)"beginMin");
							beginMin = atoi(reinterpret_cast<const char*>(_beginMin));
							xmlFree(_beginMin);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"endHour")) {
							//活动结束时
							xmlChar *_endHour = xmlGetProp(thirdNode, (const xmlChar*)"endHour");
							endHour = atoi(reinterpret_cast<const char*>(_endHour));
							xmlFree(_endHour);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"endMin")) {
							//活动结束分
							xmlChar *_endMin = xmlGetProp(thirdNode, (const xmlChar*)"endMin");
							endMin = atoi(reinterpret_cast<const char*>(_endMin));
							xmlFree(_endMin);
						}
					}
				
					ActivityTime_T *actTime = new ActivityTime_T(weekDay, beginHour, 
						beginMin, endHour, endMin);
						//cout<<"BisonTest: id "<<id<<": "<<weekDay<<"-"<<beginHour<<"-"<<beginMin<<"-"<<endHour<<"-"<<endMin<<endl;
					timeSet.insert(actTime);
				}
			}
			GuildActivity *guildAct = new GuildActivity(id, guildLevelLimit, timeSet);
			id_2_guildAct.insert(pair<string, GuildActivity*>(id, guildAct));
		}
	}
	cout<<"BisonTest: @read_guild_activity.cpp: "<<id_2_guildAct.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}