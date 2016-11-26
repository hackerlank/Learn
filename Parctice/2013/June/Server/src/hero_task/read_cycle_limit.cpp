/****************************************************************
 * Filename: read_cycle_limit.cpp
 * 
 * Description: 读取每日循环的项目
 *
 * Original Author : bison, 2012-9-24
 *
 ****************************************************************/
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<string>
#include"day_limit_item.h"
using namespace std;
extern DayLmtFindGroup_T dayLmtGroupForAll;	//全局的日限制项目
extern set<string> guildTaskList;			//帮派任务列表
extern set<string> dayTaskList;				//日常任务
extern set<string> campTaskList;			//阵营任务
set<string> allCycleTaskList;				//循环任务集合
map<int, vector<string> >levelCycleTaskSet;

int read_cycle_limit_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	char id[51];						//活动ID
	int limitTimes;						//限制次数

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

	cout<<"BisonTest:begin @read_cycle_limit.cpp"<<endl;

	vector<string> tempCycleLevelSet;
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//逐个读取每日限制项目
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"everyDay"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"dayTask"))
				{
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"Item"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
								{	
									//项目id
									xmlChar *_id = xmlGetProp(forthNode, (const xmlChar*)"id");
									strncpy(id, (char*)_id, 51);
									xmlFree(_id);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"limitTimes")) {
									//每天可做次数
									xmlChar *_limitTimes = xmlGetProp(forthNode, (const xmlChar*)"limitTimes");
									limitTimes = atoi((char*)_limitTimes);
									xmlFree(_limitTimes);
								}
							}
							// cout<<"BisonTest id is "<<id<<" limitTimes is "<<limitTimes<<endl;
							DayLimitItem_T dayItem(id, limitTimes);
							dayLmtGroupForAll.addOneItem(dayItem);
							dayTaskList.insert(id);
						}
					}	
				} else if(!xmlStrcmp(thirdNode->name, (const xmlChar*)"guildTask")) {
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"Item"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
								{	
									//项目id
									xmlChar *_id = xmlGetProp(forthNode, (const xmlChar*)"id");
									strncpy(id, (char*)_id, 51);
									xmlFree(_id);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"limitTimes")) {
									//每天可做次数
									xmlChar *_limitTimes = xmlGetProp(forthNode, (const xmlChar*)"limitTimes");
									limitTimes = atoi((char*)_limitTimes);
									xmlFree(_limitTimes);
								}
							}
							// cout<<"BisonTest id is "<<id<<" limitTimes is "<<limitTimes<<endl;
							DayLimitItem_T dayItem(id, limitTimes);
							dayLmtGroupForAll.addOneItem(dayItem);
							guildTaskList.insert(id);
						}
					}
				} else if(!xmlStrcmp(thirdNode->name, (const xmlChar*)"campTask")) {
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"Item"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
								{	
									//项目id
									xmlChar *_id = xmlGetProp(forthNode, (const xmlChar*)"id");
									strncpy(id, (char*)_id, 51);
									xmlFree(_id);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"limitTimes")) {
									//每天可做次数
									xmlChar *_limitTimes = xmlGetProp(forthNode, (const xmlChar*)"limitTimes");
									limitTimes = atoi((char*)_limitTimes);
									xmlFree(_limitTimes);
								}
							}
							// cout<<"BisonTest id is "<<id<<" limitTimes is "<<limitTimes<<endl;
							DayLimitItem_T dayItem(id, limitTimes);
							dayLmtGroupForAll.addOneItem(dayItem);
							campTaskList.insert(id);
						}
					}
				} else if(!xmlStrcmp(thirdNode->name, (const xmlChar*)"otherItem")) {
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"Item"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
								{	
									//项目id
									xmlChar *_id = xmlGetProp(forthNode, (const xmlChar*)"id");
									strncpy(id, (char*)_id, 51);
									xmlFree(_id);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"limitTimes")) {
									//每天可做次数
									xmlChar *_limitTimes = xmlGetProp(forthNode, (const xmlChar*)"limitTimes");
									limitTimes = atoi((char*)_limitTimes);
									xmlFree(_limitTimes);
								}
							}
							// cout<<"BisonTest id is "<<id<<" limitTimes is "<<limitTimes<<endl;
							DayLimitItem_T dayItem(id, limitTimes);
							dayLmtGroupForAll.addOneItem(dayItem);
							
						}
					}
				} else if(!xmlStrcmp(thirdNode->name, (const xmlChar*)"cycleTask")) {
					
					attrPtr = thirdNode->properties;
					xmlChar *_itemLevel = xmlGetProp(thirdNode, (const xmlChar *)"level");
					int cycleLevel = atoi((char*)_itemLevel);
					xmlFree(_itemLevel);
						
					for (forthNode = thirdNode->xmlChildrenNode; forthNode != NULL; forthNode = forthNode->next)
					{
						if (!xmlStrcmp(forthNode->name, (const xmlChar*)"Item"))
						{
							for (attrPtr = forthNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
							{
								if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
								{	
									//项目id
									xmlChar *_id = xmlGetProp(forthNode, (const xmlChar*)"id");
									strncpy(id, (char*)_id, 51);
									xmlFree(_id);
								} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"limitTimes")) {
									//每天可做次数
									xmlChar *_limitTimes = xmlGetProp(forthNode, (const xmlChar*)"limitTimes");
									limitTimes = atoi((char*)_limitTimes);
									xmlFree(_limitTimes);
								}
							}
							// cout<<"BisonTest id is "<<id<<" limitTimes is "<<limitTimes<<endl;
							DayLimitItem_T dayItem(id, limitTimes);
							dayLmtGroupForAll.addOneItem(dayItem);
							allCycleTaskList.insert(id);
							tempCycleLevelSet.push_back(id);
						}
					}
					levelCycleTaskSet.insert(pair<int, vector<string> >(cycleLevel, tempCycleLevelSet));
				}
			}
			
		}
	}
	cout<<"BisonTest: @read_cycle_limit.cpp end: "<<dayLmtGroupForAll.lastUsedIndex<<endl;
	xmlFreeDoc(doc);
	return 0;
}