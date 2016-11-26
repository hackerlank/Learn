/****************************************************************
 * Filename: read_happy_map.cpp
 * 
 * Description: 读取娱乐地图奖励基数
 *
 * Original Author : bison, 2012-10-11
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

HappyMapReward_T HappyMapRewardConf;			//娱乐图奖励配置

int read_happy_map(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	int grade = 0;
	int expIndex = 0;
	int monIndex = 0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"reward"))
		{
					
			expIndex = 0;
			monIndex = 0;
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"grade")) {
					//玩家等级
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"grade");
					grade = atoi((char*)_item);
					xmlFree(_item);
					if (grade < 0 || grade > 80)
					{
						cout<<"hero level in happy map conf is error!"<<endl;
						return -1;
					}
				} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"vipExp", 6)) {
					//普通玩家当前等级经验奖励系数
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					HappyMapRewardConf.rewardLevel[grade].ExpFactor[expIndex++] = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrncmp(attrPtr->name, (const xmlChar*)"vipMon", 6)) {
					//普通玩家当前等级金钱奖励系数
					xmlChar *_item = xmlGetProp(secondNode, attrPtr->name);
					HappyMapRewardConf.rewardLevel[grade].MonFactor[monIndex++] = atoi((char*)_item);
					xmlFree(_item);
				}
			}
		}
	}

	// cout<<"BisonTest: @read_happy_map.cpp: "<<endl;
	// cout<<"incHappyExpBase and incHappyMoneyBase are "<<endl;
	// cout<<incHappyExpBase[0]<<"\t"<<incHappyExpBase[1]<<"\t"<<incHappyExpBase[2]<<"\t"<<incHappyExpBase[3]<<endl;
	// cout<<incHappyMoneyBase[0]<<"\t"<<incHappyMoneyBase[1]<<"\t"<<incHappyMoneyBase[2]<<"\t"<<incHappyMoneyBase[3]<<endl;
	xmlFreeDoc(doc);
	return 0;
}