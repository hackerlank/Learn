
/********************************************************************

    created:	2012/9/05  15:24
	
	文件名：	read_trap.cpp

    author:     ChenZhen 

    purpose:  	用来读取瓶罐配置文件（格式为xml)
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include<math.h>
#include"trap.h"
#include"other_define_data.h"

using namespace std;

extern map<string,Trap*> trapConfMap;

int read_trap(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem;
	string typeId;
	string name;
	string photoId;	
	int attackRge;	
	double cdTme;
	Trap *newTrap;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	//读取地图配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL == doc)
	{
		return -1;
	}
	
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL == curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	
	//xml的相关变量
	curNode = curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_item;
	flgItem = 0;
	newTrap = NULL;
	
	//循环读取xml的子节点，并取出相对应的内容	
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"item"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			
			/*默认值*/
			int attStyle = 2;
			double attack = 0.3;
			bool isWarning = true;
			double warnTime = 1;
			
			while(attrPtr!=NULL)
			{			
				/*取出陷阱的类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					typeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));					
					xmlFree(_typeId);
				}
				/*取出陷阱的生命值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"attack"))
				{
					xmlChar *_attack=xmlGetProp(propNodePtr_item,(const xmlChar*)"attack");
					attack = atof(reinterpret_cast<const char *>(_attack));					
					xmlFree(_attack);
				}
				
				/*取出陷阱的伤害值*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"attackRge"))
				{
					xmlChar *_attackRge=xmlGetProp(propNodePtr_item,(const xmlChar*)"attackRge");
					attackRge = atoi(reinterpret_cast<const char *>(_attackRge));					
					xmlFree(_attackRge);
				}
				
				/*取出陷阱的cd时间*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cd"))
				{
					xmlChar *_cd = xmlGetProp(propNodePtr_item,(const xmlChar*)"cd");
					cdTme = atof(reinterpret_cast<const char *>(_cd));					
					xmlFree(_cd);
					
				}
				
				/*取出陷阱的攻击类型*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"attStyle"))
				{
					xmlChar *_attStyle = xmlGetProp(propNodePtr_item,(const xmlChar*)"attStyle");
					attStyle = atoi(reinterpret_cast<const char *>(_attStyle));					
					xmlFree(_attStyle);
					
				}
				
				/*取出陷阱示警类型*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isWarning"))
				{
					xmlChar *_isWarning = xmlGetProp(propNodePtr_item,(const xmlChar*)"isWarning");
					int flg = atoi(reinterpret_cast<const char *>(_isWarning));		
					if(flg == 1)
					{
						isWarning = true;
					}
					xmlFree(_isWarning);
					
				}
				
				/*取出陷阱示警时间*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"warnTime"))
				{
					xmlChar *_warnTime = xmlGetProp(propNodePtr_item,(const xmlChar*)"warnTime");
					warnTime = atof(reinterpret_cast<const char *>(_warnTime));					
					xmlFree(_warnTime);
					
				}
				
				
				/*读取陷阱的名称*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{
					xmlChar *_name=xmlGetProp(propNodePtr_item,(const xmlChar*)"name");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_name));
					
					xmlFree(_name);
				}
				
				/*读取陷阱的图片id*/				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"photoId"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"photoId");
					
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));
					
					xmlFree(_photoId);
					flgItem = 1;
				}
				
				/*实例化陷阱的图片id*/	
				if(flgItem == 1)
				{
					newTrap = new Trap(const_cast<char*>(typeId.c_str()),attack,attackRge,attStyle,cdTme,isWarning,warnTime,\
					const_cast<char*>(name.c_str()),const_cast<char*>(photoId.c_str()));
					trapConfMap[typeId] = newTrap;
					flgItem = 0;
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

