/************************************************************
	文件名：read_cpyPassOlder.cpp
	文件作用：读取副本副本通关顺序配置文件
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"heroCpyRecord.h"

extern list<CpyStateFlg> CPYEntState;

int read_cpyPassOlder(char *fileName)  
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
	string cpyId;             
	while(curNode != NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"Older"))
		{
			propNodePtr_Limit = curNode;
			xmlAttrPtr attrPtr = propNodePtr_Limit->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取cpyId属性*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyId"))
				{					
					xmlChar *_cpyId = xmlGetProp(propNodePtr_Limit,(const xmlChar*)"cpyId");
					cpyId = reinterpret_cast<const char *>(_cpyId);
					xmlFree(_cpyId);
					CpyStateFlg stage(const_cast<char *>(cpyId.c_str()));
					CPYEntState.push_back(stage);
					
				}
				attrPtr = attrPtr->next;
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	
	
	/*帮派副本置1*/
	list<CpyStateFlg>::iterator older_it;
	list<CpyStateFlg>::iterator state_it;
	int ctn;
	for(ctn = 0,older_it = CPYEntState.begin() ; older_it !=\
		CPYEntState.end() && ctn < 1; ++older_it,ctn++)
	{
			older_it->flg = 1;
	
	}
	
	/*第一级副本置1*/
	state_it = CPYEntState.begin();

	state_it->flg = 1;
	
	return 0;
}
	
	
