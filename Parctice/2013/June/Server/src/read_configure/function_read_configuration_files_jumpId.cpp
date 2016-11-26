/********************************************************************
    created:   2012/7/20
    filename:  function_read_configuration_files_jumpId.cpp
    author:    xhm 
    depend:    libxml2.lib 
*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include<map>
#include<string>
#include<iostream>
#include "data_structure_struct.h"

#define Map_Val(a,b) ( map<string,const jumpId_infor*>::value_type( (a),(b)) )
using namespace std;

extern map<string,const jumpId_infor*>jumpId2mapInfo;

int read_files_jumpId(char *fileName)
{

	xmlDocPtr doc;
	xmlNodePtr curnow;
	xmlNodePtr curNode;
	char szDocName[50]={0};
	xmlChar *cTem;
	strcpy(szDocName,fileName);
	string jumpId;          
	string mapId;       
	int currentPt_x;
	int currentPt_y;
	int targetPt_x;
	int targetPt_y;
	int levelLowerLimit;
	int campEntFlag;
	int levelUpperLimit;
	
	
	//读取equip配置文件
	xmlKeepBlanksDefault(0);
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//得到xml文件的root
	curnow=xmlDocGetRootElement(doc);
	if(NULL==curnow)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curnow=curnow->xmlChildrenNode;
	
	while(curnow!=NULL)
	{	
		
		curNode = curnow->xmlChildrenNode;
			if(NULL==curNode)
			{
				xmlFreeDoc(doc);
				return -3;
			}	
			while(curNode != NULL)
			{
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"jumpId"))
				{
					cTem= xmlNodeGetContent(curNode);
					jumpId=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"mapId"))
				{
					cTem= xmlNodeGetContent(curNode);
					mapId=const_cast<char *>(reinterpret_cast<const char *>(cTem));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"currentPt_x"))
				{
					cTem= xmlNodeGetContent(curNode);
					currentPt_x=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"currentPt_y"))
				{
					cTem= xmlNodeGetContent(curNode);
					currentPt_y=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"targetPt_x"))
				{
					cTem= xmlNodeGetContent(curNode);
					targetPt_x=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	 
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"targetPt_y"))
				{
					cTem= xmlNodeGetContent(curNode);
					targetPt_y=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"maxLimit"))
				{
					cTem= xmlNodeGetContent(curNode);
					levelUpperLimit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	 
				}	
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"gradeLimit"))
				{
					cTem= xmlNodeGetContent(curNode);
					levelLowerLimit=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
				}
				if(!xmlStrcmp(curNode->name,(const xmlChar *)"camp"))
				{
					cTem= xmlNodeGetContent(curNode);
					campEntFlag=atoi(const_cast<char *>(reinterpret_cast<const char *>(cTem)));
					xmlFree(cTem);	
					
					Point currentPt(currentPt_x,currentPt_y);
					Point targetPt(targetPt_x,targetPt_y);
					const jumpId_infor* jumpIdinfo = new jumpId_infor(jumpId,mapId,currentPt,targetPt,levelLowerLimit,levelUpperLimit,campEntFlag);
					if(NULL != jumpIdinfo)
					    jumpId2mapInfo.insert(Map_Val(jumpId,jumpIdinfo));
				}		
				curNode=curNode->next;
			}
		curnow = curnow->next;
	}
	xmlFreeDoc(doc);
	
	//using for test,check the skip Point is or not right;

/* 	for(map<string,const jumpId_infor*>::iterator iter=jumpId2mapInfo.begin();iter != jumpId2mapInfo.end();iter++)
	{
	  cout<<" mapId:"<<iter->second->mapId<<endl;
	  cout<<"%%% JumpId:"<<iter->second->jumpId<<endl;
	  cout<<"*** camp:  "<<iter->second->campEntFlag<<endl;
	  cout<<"*** levelUpperLimit:"<<iter->second->levelUpperLimit<<endl<<endl<<endl;
	} */
	
	return 0;
}
