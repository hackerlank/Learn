/************************************************************
	文件名：read_vip_bale_room.cpp
	文件作用：读取vip包间限制配置文件
	作者：chenzhen
	创建日期：2012.12.14
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"vipBaleRoomLimit.h"
extern map<string,VipBaleRoomLimit*> mapIdToVipBaleRomLimit;
int read_files_vipBaleRomLimit(char *fileName)  //读取VIP限制类     
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
	string vipLimitId;        //vip限制id
	string vipMapId;          //vip包间mapid
	int num;                  //进vip包间所要求人数
	int vipRank;              //进vip包间所要求vip等级
	int room;                 //副本房间数
	int flgVipLimit;             //标志变量
	
	flgVipLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"vipBaleLimit"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取vipLimitId属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vipLimitId"))
				{					
					xmlChar *_vipLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"vipLimitId");
					vipLimitId = reinterpret_cast<const char *>(_vipLimitId);
					xmlFree(_vipLimitId);
				}
				
				/*读取vipMapId属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vipMapId"))
				{					
					xmlChar *_vipMapId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"vipMapId");
					vipMapId = reinterpret_cast<const char *>(_vipMapId);
					xmlFree(_vipMapId);
				}
				/*读取num属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"num"))
				{					
					xmlChar *_num = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"num");
					num = atoi(reinterpret_cast<const char *>(_num));
					xmlFree(_num);
				}
				
				/*读取vipRank属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vipRank"))
				{					
					xmlChar *_vipRank = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"vipRank");
					vipRank = atoi(reinterpret_cast<const char *>(_vipRank));
					xmlFree(_vipRank);
				}
				
				/*读取room属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgVipLimit = 1;
				}
				
				/*实例化CpyLimit类*/
				if(flgVipLimit == 1)
				{
					room = 500;
					VipBaleRoomLimit *newVipBaleRoomLimit = new VipBaleRoomLimit(\
					const_cast<char *>(vipLimitId.c_str()),const_cast<char *>\
					(vipMapId.c_str()),num,vipRank,room);
					mapIdToVipBaleRomLimit[vipMapId] = newVipBaleRoomLimit;
					newVipBaleRoomLimit->setMapVipRoom();
					flgVipLimit = 0;
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
