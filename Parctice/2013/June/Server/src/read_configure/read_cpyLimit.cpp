/************************************************************
	文件名：read_cpyLimit.cpp
	文件作用：读取副本所有限制的配置文件
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"cpyLimit.h"
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
int read_files_cpyLimit(char *fileName)  //读取副本限制类     
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
	string cpyLimitId;        //副本限制id
	string cpyId;             //副本id
	int num;                  //进副本所要求人数
	int rank;                 //进副本所要求等级
	int room;                 //副本房间数
	int flgLimit;             //标志变量
	double jdgGolRat;         //副本打分系数
	int jugTme;               //副本评分时间
	int baseGole = 20;             //通关基础分
	string name;              //名称
	size_t costFatigue = 5;       //体力值
	flgLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"cpyLimit"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取cpyLimitId属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyLimitId"))
				{					
					xmlChar *_cpyLimitId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"cpyLimitId");
					cpyLimitId = reinterpret_cast<const char *>(_cpyLimitId);
					xmlFree(_cpyLimitId);
				}
				
				/*读取cpyId属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyId"))
				{					
					xmlChar *_cpyId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"cpyId");
					cpyId = reinterpret_cast<const char *>(_cpyId);
					xmlFree(_cpyId);
				}
				/*读取jugTme属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"jugTme"))
				{					
					xmlChar *_jugTme = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"jugTme");
					jugTme = atoi(reinterpret_cast<const char *>(_jugTme));
					xmlFree(_jugTme);
				}
				/*读取baseGole属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"baseGole"))
				{					
					xmlChar *_baseGole = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"baseGole");
					baseGole = atoi(reinterpret_cast<const char *>(_baseGole));
					xmlFree(_baseGole);
				}
				/*读取jdgGolRat属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"jdgGolRat"))
				{					
					xmlChar *_jdgGolRat = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"jdgGolRat");
					jdgGolRat = atof(reinterpret_cast<const char *>(_jdgGolRat));
					xmlFree(_jdgGolRat);
				}
				/*读取num属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"num"))
				{					
					xmlChar *_num = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"num");
					num = atoi(reinterpret_cast<const char *>(_num));
					xmlFree(_num);
				}
				
				/*读取rank属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rank"))
				{					
					xmlChar *_rank = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"rank");
					rank = atoi(reinterpret_cast<const char *>(_rank));
					xmlFree(_rank);
				}
				
				/*读取name属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"name"))
				{					
					xmlChar *_name = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"name");
					name = reinterpret_cast<const char *>(_name);
					xmlFree(_name);
				}
				/*读取costFatigue属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"costFatigue"))
				{					
					xmlChar *_costFatigue = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"costFatigue");
					costFatigue = atoi(reinterpret_cast<const char *>(_costFatigue));
					xmlFree(_costFatigue);
				}
				
				/*读取room属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"room"))
				{					
					xmlChar *_room = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"room");
					room = atoi(reinterpret_cast<const char *>(_room));
					xmlFree(_room);
					flgLimit = 1;
				}
				
				/*实例化CpyLimit类*/
				if(flgLimit == 1)
				{
					room = 20;
					CpyLimit *newCpyLimit = new CpyLimit(const_cast<char *>(cpyLimitId.c_str()),\
					const_cast<char *>(cpyId.c_str()),const_cast<char*>(name.c_str()),\
					baseGole,jugTme,jdgGolRat,num,rank,costFatigue,room);
					
					cpyId_to_cpyLimit[cpyId] = newCpyLimit;
					flgLimit = 0;
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}
	
	
