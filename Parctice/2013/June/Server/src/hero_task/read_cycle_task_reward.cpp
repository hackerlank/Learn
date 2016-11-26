/****************************************************************
 * Filename: read_cycle_task_reward.cpp
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
#include "task.h"
using namespace std;

map<int, vector<double> > cycleTaskRewardFactor;

int read_cycle_task_reward_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	int cycleTaskLevel = 0;
	int cycleTaskLoop = 0;
	double rewardFactor = 0.;

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

	cout<<"BisonTest:begin @read_cycle_task_reward.cpp"<<endl;

	vector<string> tempCycleLevelSet;
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//逐个读取每日限制项目
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"cycleTaskReward"))
		{	
			attrPtr = secondNode->properties;
			xmlChar *_itemLevel = xmlGetProp(secondNode, (const xmlChar *)"level");
			int cycleLevel = atoi((char*)_itemLevel);
			xmlFree(_itemLevel);
			vector<double> factor;
			factor.clear();
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rewardFactor")) {
							//每天可做次数
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"rewardFactor");
							rewardFactor = atof((char*)_item);
							xmlFree(_item);
							factor.push_back(rewardFactor);
						}
					}
				}
			}
			
			cycleTaskRewardFactor.insert(pair<int, vector<double> >(cycleLevel, factor));
		}
	}
	cout<<"BisonTest: @read_cycle_task_reward.cpp end: "<<endl;
	xmlFreeDoc(doc);
	return 0;
}