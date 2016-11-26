/****************************************************************
 * Filename: read_task_goods.cpp
 * 
 * Description: 读任务道具信息
 *
 * Original Author : bison, 2012-6-13
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include"task_goods_info.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

//任务道具的全局变量
extern map<string, TaskGoodsInfo*> id2taskGoodsInfo;

int read_task_goods_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	char taskGoodsId[51] = {0};						//任务道具ID
	char monsterId[1024] = {0};						//怪物ID
	double rate;							//怪物掉落该任务道具的概率

	strcpy(szDocName, fileName);
	doc = xmlReadFile(szDocName, "UTF-8", XML_PARSE_RECOVER); //解析文件
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Item"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"taskGoodsId"))
				{
					//读取任务道具id
					xmlChar *_taskGoodsId = xmlGetProp(secondNode, (const xmlChar*)"taskGoodsId");
					strncpy(taskGoodsId, const_cast<char *>(reinterpret_cast<const char *>(_taskGoodsId)), sizeof taskGoodsId);
					xmlFree(_taskGoodsId);
					
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"monsterId")) {
					//读取怪物id
					xmlChar *_monsterId = xmlGetProp(secondNode, (const xmlChar*)"monsterId");
					strncpy(monsterId, const_cast<char *>(reinterpret_cast<const char *>(_monsterId)), sizeof monsterId);
					xmlFree(_monsterId);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"rate")) {
					//读取怪物掉落该物品的概率
					xmlChar *_rate = xmlGetProp(secondNode, (const xmlChar*)"rate");
					rate = atof(reinterpret_cast<const char*>(_rate));
					xmlFree(_rate);
				} 
			}
			TaskGoodsInfo* tskGoodsInfo = new TaskGoodsInfo(taskGoodsId, monsterId, rate);
			id2taskGoodsInfo.insert(pair<string, TaskGoodsInfo*>(taskGoodsId, tskGoodsInfo));
		}
	}
	xmlFreeDoc(doc);
	
	map<string, TaskGoodsInfo*>::iterator iter;
	iter = id2taskGoodsInfo.begin();
	TaskGoodsInfo *tinf = iter->second;
	
	return 0;
}