/************************************************************
	文件名：read_partyRoom.cpp
	文件作用：读取帮派限制配置文件
	作者：chenzhen
	创建日期：2012.12.14
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"partyRoomLimit.h"
extern map<string,PartyRoomLimit*> mapIdToPartyRomLimit;
int read_files_partyRomLimit(char *fileName)     
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
	string partyLimitId;       
	string partyMapId;          
	int partyNum;                 
	int partyRank;              
	int room;                 
	int flgPartyLimit;           
	
	flgPartyLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"partyLimit"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取partyLimitId属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyLimitId"))
				{					
					xmlChar *_partyLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyLimitId");
					partyLimitId = reinterpret_cast<const char *>(_partyLimitId);
					xmlFree(_partyLimitId);
				}
				
				/*读取partyMapId属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyMapId"))
				{					
					xmlChar *_partyMapId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyMapId");
					partyMapId = reinterpret_cast<const char *>(_partyMapId);
					xmlFree(_partyMapId);
				}
				/*读取partyNum属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyNum"))
				{					
					xmlChar *_partyNum = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyNum");
					partyNum = atoi(reinterpret_cast<const char *>(_partyNum));
					xmlFree(_partyNum);
				}
				
				/*读取partyRank属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"partyRank"))
				{					
					xmlChar *_partyRank = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"partyRank");
					partyRank = atoi(reinterpret_cast<const char *>(_partyRank));
					xmlFree(_partyRank);
	
				}
				
				/*读取room属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgPartyLimit = 1;
				}
				
				/*实例化partyRoomLimit类*/
				if(flgPartyLimit == 1)
				{
					room = 100;
					PartyRoomLimit *newPartyRoomLimit = new PartyRoomLimit(const_cast<char *>\
					(partyLimitId.c_str()),const_cast<char *>(partyMapId.c_str()),partyNum,\
					partyRank,room);
					
					mapIdToPartyRomLimit[partyMapId] = newPartyRoomLimit;
					newPartyRoomLimit->setMapPartyRoom();
					flgPartyLimit = 0;
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
