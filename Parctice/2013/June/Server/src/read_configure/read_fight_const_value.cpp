/****************************************************************
 * Filename: read_fight_const_value.cpp
 * 
 * Description: 读取战斗公式中的常量
 *
 * Original Author : bison, 2012-3-29
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "hero_fight.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

FightConst_T fightConst;

int read_fight_const_value(char *fileName)
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"FightConst"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"attkFactor"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"attkFactor");
					fightConst.attkFactor = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defFactor"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"defFactor");
					fightConst.defFactor = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hitFactor"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"hitFactor");
					fightConst.hitFactor = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"critFactor"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"critFactor");
					fightConst.critFactor = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"tencFactor"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"tencFactor");
					fightConst.tencFactor = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"critBase"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"critBase");
					fightConst.critBase = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"tencBase"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"tencBase");
					fightConst.tencBase = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"tencMax"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"tencMax");
					fightConst.tencMax = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"critDivisor"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"critDivisor");
					fightConst.critDivisor = atof((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"critTimes"))
				{	
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"critTimes");
					fightConst.critTimes = atof((char*)_item);
					xmlFree(_item);
				}
			}
		}
	}
	
	xmlFreeDoc(doc);
	return 0;
}	
		