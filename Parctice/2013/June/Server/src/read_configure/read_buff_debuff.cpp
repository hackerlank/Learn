/****************************************************************
 * Filename: read_buff_debuff.cpp
 * 
 * Description: 读取技能buff和debuff
 *
 * Original Author : bison, 2012-12-10
 *
 ****************************************************************/
 
#include"function_read_configuration_files.h"
#include "buff_debuff.h"
#include<libxml/parser.h>
#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
using namespace std;

map<string, Buff_debuff_conf_T*> buf_debuf_conf;	//buff和debuff的配置

int read_buff_debuff(char *fileName)
{
	xmlDocPtr doc;
	xmlNodePtr rootNode;				//根节点
	xmlNodePtr secondNode;
	xmlNodePtr thirdNode;
	xmlNodePtr forthNode;
	xmlAttrPtr attrPtr;					//节点属性值
	char szDocName[50]={0};
	xmlChar *cTem;						//项的值

	char skillId[51] = {0};
	int effect = 0;
	int lastTimeBase = 0;
	int lastTimeFactor = 0;
	int effectBase = 0;
	int effectIncFactor = 0;
	
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
		if (!xmlStrcmp(secondNode->name, (const xmlChar*)"debuff"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取一个debuff项
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skillId"))
						{	
							//对应的技能ID
							xmlChar *_skillId = xmlGetProp(thirdNode, (const xmlChar*)"skillId");
							strncpy(skillId, const_cast<char *>(reinterpret_cast<const char *>(_skillId)), 51);
							xmlFree(_skillId);
						}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effect")) {
							//debuff效果编号
							xmlChar *_effect = xmlGetProp(thirdNode, (const xmlChar*)"effect");
							effect = atoi(reinterpret_cast<const char*>(_effect));
							xmlFree(_effect);
						}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeBase")) {
							//持续时间基数
							xmlChar *_lastTimeBase = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeBase");
							lastTimeBase = atoi(reinterpret_cast<const char*>(_lastTimeBase));
							xmlFree(_lastTimeBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeFactor")) {
							//持续时间系数
							xmlChar *_lastTimeFactor = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeFactor");
							lastTimeFactor = atoi(reinterpret_cast<const char*>(_lastTimeFactor));
							xmlFree(_lastTimeFactor);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectBase")) {
							//debuff作用基数
							xmlChar *_effectBase = xmlGetProp(thirdNode, (const xmlChar*)"effectBase");
							effectBase = atoi(reinterpret_cast<const char*>(_effectBase));
							xmlFree(_effectBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectIncFactor")) {
							//debuff作用系数
							xmlChar *_effectIncFactor = xmlGetProp(thirdNode, (const xmlChar*)"effectIncFactor");
							effectIncFactor = atoi(reinterpret_cast<const char*>(_effectIncFactor));
							xmlFree(_effectIncFactor);
						}
					}
					Buff_debuff_conf_T *debuff = new Buff_debuff_conf_T(skillId, effect, lastTimeBase,
						lastTimeFactor, effectBase, effectIncFactor);
					buf_debuf_conf.insert(pair<string, Buff_debuff_conf_T*>(skillId, debuff));
				}		
			}	
		} else if (!xmlStrcmp(secondNode->name, (const xmlChar*)"buff"))
		{
			for (thirdNode = secondNode->xmlChildrenNode; thirdNode != NULL; thirdNode = thirdNode->next)
			{
				//读取一个debuff项
				if (!xmlStrcmp(thirdNode->name, (const xmlChar*)"Item"))
				{
					for (attrPtr = thirdNode->properties; attrPtr != NULL; attrPtr = attrPtr->next)
					{
						if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"skillId"))
						{	
							//对应的技能ID
							xmlChar *_skillId = xmlGetProp(thirdNode, (const xmlChar*)"skillId");
							strncpy(skillId, const_cast<char *>(reinterpret_cast<const char *>(_skillId)), 51);
							xmlFree(_skillId);
						}else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effect")) {
							//buff效果编号
							xmlChar *_effect = xmlGetProp(thirdNode, (const xmlChar*)"effect");
							effect = atoi(reinterpret_cast<const char*>(_effect));
							xmlFree(_effect);
						}  else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeBase")) {
							//持续时间基数
							xmlChar *_lastTimeBase = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeBase");
							lastTimeBase = atoi(reinterpret_cast<const char*>(_lastTimeBase));
							xmlFree(_lastTimeBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"lastTimeFactor")) {
							//持续时间系数
							xmlChar *_lastTimeFactor = xmlGetProp(thirdNode, (const xmlChar*)"lastTimeFactor");
							lastTimeFactor = atoi(reinterpret_cast<const char*>(_lastTimeFactor));
							xmlFree(_lastTimeFactor);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectBase")) {
							//buff作用基数
							xmlChar *_effectBase = xmlGetProp(thirdNode, (const xmlChar*)"effectBase");
							effectBase = atoi(reinterpret_cast<const char*>(_effectBase));
							xmlFree(_effectBase);
						} else if (!xmlStrcmp(attrPtr->name, (const xmlChar*)"effectIncFactor")) {
							//buff作用系数
							xmlChar *_effectIncFactor = xmlGetProp(thirdNode, (const xmlChar*)"effectIncFactor");
							effectIncFactor = atoi(reinterpret_cast<const char*>(_effectIncFactor));
							xmlFree(_effectIncFactor);
						}
					}
					
					Buff_debuff_conf_T *debuff = new Buff_debuff_conf_T(skillId, effect, lastTimeBase,
						lastTimeFactor, effectBase, effectIncFactor);
					// cout<<"[BisonShow] skillId is "<<skillId<<endl;
					buf_debuf_conf.insert(pair<string, Buff_debuff_conf_T*>(skillId, debuff));
					
				}		
			}	
		}
	}
	// cout<<"[BisonShow] buf_debuf_conf size is "<<buf_debuf_conf.size()<<endl;
	xmlFreeDoc(doc);
	return 0;
}