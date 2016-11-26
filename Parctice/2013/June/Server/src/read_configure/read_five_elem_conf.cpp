/****************************************************************
 * Filename: read_five_elem_conf.cpp
 * 
 * Description: 读取五行配置
 *
 * Original Author : bison, 2012-1-18
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "five_elements.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

FiveElemConf_T heroFiveElemConf;				//人物五行配置

int read_five_elem_conf(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值
	int elem;							//五行项
	int level = 0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"FiveElem"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"startLevel")) {
					//五行开始激活需要的玩家等级
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"startLevel");
					heroFiveElemConf.startLevel = atoi((char*)_item);
					xmlFree(_item);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"changeNeedGold")) {
					//更换五行需要的元宝
					xmlChar *_item = xmlGetProp(secondNode, (const xmlChar*)"changeNeedGold");
					heroFiveElemConf.changeNeedGold = atoi((char*)_item);
					xmlFree(_item);
				}
			}
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取五行抗性系数
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"Elem")) {
							//技能等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"Elem");
							elem = atoi((char*)_item);
							xmlFree(_item);
							if (elem < 1 || elem > 6)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of fiveElem conf is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
							elem -= 1;
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defGoldFactor")) {
							//该五行属性对金的抗性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defGoldFactor");
							heroFiveElemConf.defFactor[elem][0] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defWoodFactor")) {
							//该五行属性对木的抗性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defWoodFactor");
							heroFiveElemConf.defFactor[elem][1] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defEarthFactor")) {
							//该五行属性对土的抗性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defEarthFactor");
							heroFiveElemConf.defFactor[elem][2] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defWaterFactor")) {
							//该五行属性对水的抗性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defWaterFactor");
							heroFiveElemConf.defFactor[elem][3] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defFireFactor")) {
							//该五行属性对火的抗性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defFireFactor");
							heroFiveElemConf.defFactor[elem][4] = atof((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"defNoElemFactor")) {
							//该五行属性对无的抗性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"defNoElemFactor");
							heroFiveElemConf.defFactor[elem][5] = atof((char*)_item);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"level"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lvl")) {
							//五行等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"lvl");
							level = atoi((char*)_item);
							xmlFree(_item);
							if (level < 0 || level > 100)
							{
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								cout<<"the config of fiveElem conf is error"<<endl;
								cout<<"[BisonWarn] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
								return -1;
							}
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"needHeroLevel")) {
							//五行等级需要的玩家等级
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"needHeroLevel");
							heroFiveElemConf.needHeroLevel[level] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"upgradeNeedExp")) {
							//升到下一级需要的经验
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"upgradeNeedExp");
							heroFiveElemConf.upgradeNeedExp[level] = atoi((char*)_item);
							xmlFree(_item);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"fiveValue")) {
							//该等级的五行属性
							xmlChar *_item = xmlGetProp(thirdNode, (const xmlChar*)"fiveValue");
							heroFiveElemConf.fiveValue[level] = atoi((char*)_item);
							xmlFree(_item);
						}
					}
					// cout<<endl;
				}
			}
			
		}
	}
	
	cout<<"[BisonShow]@read_five_elem_conf.cpp"<<endl;
	xmlFreeDoc(doc);
	return 0;
}
