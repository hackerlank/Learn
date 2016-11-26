/************************************************************
	文件名：read_party_base_camp.cpp
	文件作用：读取帮派限制配置文件
	作者：chenzhen
	创建日期：2012.12.14
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"partyBaseCampLimit.h"
#include"cpyAsist.h"
extern map<string,PartyBaseCampLimit*> mapIdToCampRomLimit;
extern map<int,string> levelToMapId;
int read_party_base_camp(char *fileName)     
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;     //xml中间节点临时变量
	
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	doc = xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	
	if(NULL == doc)
	{
		return -1;
	}
	//得到xml文件的root
	curNode = xmlDocGetRootElement(doc);		
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_Limit;
	string campLimitId;        //限制id
	string campMapId;          //包间mapid
	int num;               //包间所要求人数
	int partyLevel;              //包间所要求帮派等级
	int room;                 	//房间数
	int flgCampLimit;         //标志变量
	
	flgCampLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"partyBaseCamp"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取campLimitId属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"campLimitId"))
				{					
					xmlChar *_campLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"campLimitId");
					campLimitId = reinterpret_cast<const char *>(_campLimitId);
					xmlFree(_campLimitId);
				}
				
				/*读取campMapId属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"campMapId"))
				{					
					xmlChar *_campMapId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"campMapId");
					campMapId = reinterpret_cast<const char *>(_campMapId);
					xmlFree(_campMapId);
				}
				/*读取num属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"num"))
				{					
					xmlChar *_num = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"num");
					num = atoi(reinterpret_cast<const char *>(_num));
					xmlFree(_num);
				}
				
				/*读取partyLevel属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyLevel"))
				{					
					xmlChar *_partyLevel = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyLevel");
					partyLevel = atoi(reinterpret_cast<const char *>(_partyLevel));
					xmlFree(_partyLevel);
	
				}
				
				/*读取room属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgCampLimit = 1;
				}
				
				/*实例化PartyBaseCampLimit类*/
				if(flgCampLimit == 1)
				{
					room = 100;
					PartyBaseCampLimit *newPartyBaseCampLimit = new PartyBaseCampLimit(const_cast<char *>(campLimitId.c_str()),const_cast<char *>\
					(campMapId.c_str()),num,partyLevel,room);
					
					mapIdToCampRomLimit[campMapId] = newPartyBaseCampLimit;
					newPartyBaseCampLimit->setMapCampRoom();
					flgCampLimit = 0;
					insertLevelCampMap(partyLevel,campMapId);
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	insertHightestLevelCampMap();
	testPrintLevelCampMap();
	xmlFreeDoc(doc);
	return 0;
}
	
	
