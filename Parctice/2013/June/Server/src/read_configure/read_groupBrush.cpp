/************************************************************
	文件名：read_groupBrush.cpp
	文件作用：读取刷怪模式的配置文件
	作者：chenzhen
	创建日期：2012.07.06
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"groupBrush.h"
#include<map>
extern map<string,GroupBrush*> groupBrush;
int read_files_groupBrush(char *fileName)
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
	xmlNodePtr propNodePtr_group;
	
	string groupId;           //批次id
	double generRatio;        //普通怪所占比例
	double eliteRatio;        //精英怪所占比例
	double activeRatio;       //主动怪所占比例	
	double passRatio;         //被动怪所占比例
	double patRatio;          //巡逻怪所占比例
	bool randFlg;             //boss怪是否随机涮出
	int bossNum;              //BOSS如果随机涮出，则数量
	
	int flgLimit;             //标志变量
	
	flgLimit = -1;
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"groupType"))
		{
			propNodePtr_group = curNode;
			xmlAttrPtr attrPtr = propNodePtr_group->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取groupId属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"groupId"))
				{					
					xmlChar *_groupId = xmlGetProp(propNodePtr_group,(const xmlChar*)"groupId");
					groupId = reinterpret_cast<const char *>(_groupId);
					xmlFree(_groupId);
				}
				
				/*读取普通怪所占比例*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"generRatio"))
				{					
					xmlChar *_generRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"generRatio");
					generRatio = atof(reinterpret_cast<const char *>(_generRatio));
					xmlFree(_generRatio);
				}
				
				/*读取精英怪所占比例*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"eliteRatio"))
				{					
					xmlChar *_eliteRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"eliteRatio");
					eliteRatio = atof(reinterpret_cast<const char *>(_eliteRatio));
					xmlFree(_eliteRatio);
				}
				
				/*读取boss怪是否随机刷出*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"randFlg"))
				{
					int flg;
					xmlChar *_randFlg = xmlGetProp(propNodePtr_group,(const xmlChar*)"randFlg");
					flg = atoi(reinterpret_cast<const char *>(_randFlg));
					xmlFree(_randFlg);
					if(flg == 1)
					{
						randFlg = true;
					}
					else
					{
						false;
					}
					
				}
				
				/*读取boss怪数量*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"bossNum"))
				{
					int flg;
					xmlChar *_bossNum = xmlGetProp(propNodePtr_group,(const xmlChar*)"bossNum");
					bossNum = atoi(reinterpret_cast<const char *>(_bossNum));
					xmlFree(_bossNum);
				}
				
				/*读取被动怪所占比例*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"passRatio"))
				{					
					xmlChar *_passRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"passRatio");
					passRatio = atof(reinterpret_cast<const char *>(_passRatio));
					xmlFree(_passRatio);
					
				}
								
				/*读取主动怪所占比例*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"activeRatio"))
				{					
					xmlChar *_activeRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"activeRatio");
					activeRatio = atof(reinterpret_cast<const char *>(_activeRatio));
					xmlFree(_activeRatio);
				}
				
				/*读取巡逻怪所占比例*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"patRatio"))
				{					
					xmlChar *_patRatio = xmlGetProp(propNodePtr_group,(const xmlChar*)"patRatio");
					patRatio = atof(reinterpret_cast<const char *>(_patRatio));
					xmlFree(_patRatio);
					flgLimit = 1;
				}
				
				/*实例化GroupBrush类*/
				if(flgLimit == 1)
				{
					GroupBrush *group_Brush = new GroupBrush(const_cast<char *>(groupId.c_str()),generRatio,\
															randFlg,bossNum,eliteRatio,passRatio,activeRatio,\
															patRatio);
								
					groupBrush[groupId] = group_Brush;
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