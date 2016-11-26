#include"guild_club.h"
#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

extern map<string, GuildFeastConf_T> feastId_2_feastConf;

int read_guild_feast_info(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;		//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;			//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;				//项的值

	char id[51];					//宴席类型ID
	int cost;					//宴席花费元宝数
	int lastTime;				//宴席持续时间
	int contb;					//请宴者对帮派贡献度
	int hostMoney;				//请宴者获得金钱值
	int hostGlory;				//请宴者获得帮贡值
	int hostReputation;			//请宴者获得声望值
	int joinMoney;				//赴宴者获得金钱值
	int joinGlory;				//赴宴者获得帮贡值
	int joinReputation;			//赴宴者获得声望值

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

	cout<<"jolly: begin read_guild_feast"<<endl;
	
	for (secondNode = rootNode->xmlChildrenNode; secondNode != NULL; secondNode = secondNode->next)
	{
		//逐个读取帮派活动节点
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"Feast"))
		{
			for (attrPtr = secondNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
			{
				if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"id"))
				{	
					//宴席级别Id
					xmlChar *_id = xmlGetProp(secondNode, (const xmlChar*)"id");
					strncpy(id, const_cast<char *>(reinterpret_cast<const char *>(_id)), 51);
					xmlFree(_id);
					
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"cost")) {
					//宴席花费
					xmlChar *_cost = xmlGetProp(secondNode, (const xmlChar*)"cost");
					cost = atoi(reinterpret_cast<const char*>(_cost));
					xmlFree(_cost);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTime")) {
					//宴席持续时间
					xmlChar *_lastTime = xmlGetProp(secondNode, (const xmlChar*)"lastTime");
					lastTime = atoi(reinterpret_cast<const char*>(_lastTime));
					xmlFree(_lastTime);
				} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"contb")) {
					//请宴者对帮派贡献度
					xmlChar *_contb = xmlGetProp(secondNode, (const xmlChar*)"contb");
					contb = atoi(reinterpret_cast<const char*>(_contb));
					xmlFree(_contb);
				}
			}
			
			//读取宴席福利
			
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"HostReward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hostMoney"))
						{	
							//请宴者获得金钱值
							xmlChar *_hostMoney = xmlGetProp(thirdNode, (const xmlChar*)"hostMoney");
							hostMoney = atoi(reinterpret_cast<const char*>(_hostMoney));
							xmlFree(_hostMoney);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hostGlory")) {
							//请宴者获得帮贡值
							xmlChar *_hostGlory = xmlGetProp(thirdNode, (const xmlChar*)"hostGlory");
							hostGlory = atoi(reinterpret_cast<const char*>(_hostGlory));
							xmlFree(_hostGlory);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"hostReputation")) {
							//请宴者获得声望值
							xmlChar *_hostReputation = xmlGetProp(thirdNode, (const xmlChar*)"hostReputation");
							hostReputation = atoi(reinterpret_cast<const char*>(_hostReputation));
							xmlFree(_hostReputation);
						}
					}
				} else if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"JoinReward"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"joinMoney"))
						{	
							//赴宴者获得金钱值
							xmlChar *_joinMoney = xmlGetProp(thirdNode, (const xmlChar*)"joinMoney");
							joinMoney = atoi(reinterpret_cast<const char*>(_joinMoney));
							xmlFree(_joinMoney);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"joinGlory")) {
							//赴宴者获得帮贡值
							xmlChar *_joinGlory = xmlGetProp(thirdNode, (const xmlChar*)"joinGlory");
							joinGlory = atoi(reinterpret_cast<const char*>(_joinGlory));
							xmlFree(_joinGlory);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"joinReputation")) {
							//赴宴者获得声望值
							xmlChar *_joinReputation = xmlGetProp(thirdNode, (const xmlChar*)"joinReputation");
							joinReputation = atoi(reinterpret_cast<const char*>(_joinReputation));
							xmlFree(_joinReputation);
						}
					}
				}
			}
			GuildFeastConf_T feastConf(id, cost, lastTime, contb, hostMoney, hostGlory,
				hostReputation, joinMoney, joinGlory, joinReputation);
				
			feastId_2_feastConf.insert(pair<string, GuildFeastConf_T>(id, feastConf));
		}
	}
	cout<<"BisonTest: @read_guild_feast.cpp: "<<feastId_2_feastConf.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}