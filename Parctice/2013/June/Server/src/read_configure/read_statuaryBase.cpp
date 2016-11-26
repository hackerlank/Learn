/************************************************************
	文件名：read_statuaryBase.cpp
	文件作用：读取StatuaryBase类的配置文件
	作者：chenzhen
	创建日期：2013.03.01
************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"map_inform.h"
#include<iostream>
#include<string.h>
#include"statuaryBase.h"
using namespace std;

extern map<string,StatuaryBase*> vocationToStatuaryBaseConf;
extern set<Point> statuaryPtSet;
int read_statuaryBase(char *fileName)
{
	
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	
	int flgItem = 0;
	string vocationId,mapId;     
	Point piexPt(-1,-1);
	map<string,string>limitToPhotoId;
	StatuaryBase *newStatuaryBase;
	
	strncpy(szDocName,fileName,strlen(fileName));
	
	
	
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
	newStatuaryBase = NULL;
	
	//循环读取xml的子节点，并取出相对应的内容	
	while(curNode!=NULL)
	{
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"statuaryPt"))
		{	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*取出x*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x1"))
				{
					xmlChar *_x=xmlGetProp(propNodePtr_item,(const xmlChar*)"x1");
					piexPt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);
				}
				
				/*取出y*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y1"))
				{
					xmlChar *_y=xmlGetProp(propNodePtr_item,(const xmlChar*)"y1");
					piexPt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);
					
					if(piexPt._x > 0 && piexPt._y > 0)
					{
						statuaryPtSet.insert(piexPt);
						piexPt._x = -1;
						piexPt._y = -1;
					}
				}
				
				
				/*取出x*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x2"))
				{
					xmlChar *_x=xmlGetProp(propNodePtr_item,(const xmlChar*)"x2");
					piexPt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);
				}
				
				/*取出y*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y2"))
				{
					xmlChar *_y=xmlGetProp(propNodePtr_item,(const xmlChar*)"y2");
					piexPt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);
					if(piexPt._x > 0 && piexPt._y > 0)
					{
						statuaryPtSet.insert(piexPt);
						piexPt._x = -1;
						piexPt._y = -1;
					}
				}
				
				/*取出x*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x3"))
				{
					xmlChar *_x=xmlGetProp(propNodePtr_item,(const xmlChar*)"x3");
					piexPt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);
				}
				
				/*取出y*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y3"))
				{
					xmlChar *_y=xmlGetProp(propNodePtr_item,(const xmlChar*)"y3");
					piexPt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);
					if(piexPt._x > 0 && piexPt._y > 0)
					{
						statuaryPtSet.insert(piexPt);
						piexPt._x = -1;
						piexPt._y = -1;
					}
				}
				
				/*取出x*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x4"))
				{
					xmlChar *_x=xmlGetProp(propNodePtr_item,(const xmlChar*)"x4");
					piexPt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);
				}
				
				/*取出y*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y4"))
				{
					xmlChar *_y=xmlGetProp(propNodePtr_item,(const xmlChar*)"y4");
					piexPt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);
					if(piexPt._x > 0 && piexPt._y > 0)
					{
						statuaryPtSet.insert(piexPt);
						piexPt._x = -1;
						piexPt._y = -1;
					}
				}
				attrPtr = attrPtr->next;	
			}
		}				
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"statuary"))
		{	
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			
			string requre;
			string photoId;
			
			while(attrPtr!=NULL)
			{			
				/*取出职业类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"vocationId"))
				{
					xmlChar *_vocationId=xmlGetProp(propNodePtr_item,(const xmlChar*)"vocationId");
					vocationId = const_cast<char *>(reinterpret_cast<const char *>(_vocationId));					
					xmlFree(_vocationId);
				}
				/*取出requre1*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"requre1"))
				{
					xmlChar *_requre=xmlGetProp(propNodePtr_item,(const xmlChar*)"requre1");
					requre = const_cast<char *>(reinterpret_cast<const char *>(_requre));
					xmlFree(_requre);
				}
				/*取出photoId1*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"statuaryColour1"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"statuaryColour1");
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));	
					xmlFree(_photoId);
					if(!requre.empty() && !photoId.empty())
					{
						limitToPhotoId[requre] = photoId;
						photoId.erase();
						requre.erase();
					}
				}
				
				/*取出requre2*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"requre2"))
				{
					xmlChar *_requre=xmlGetProp(propNodePtr_item,(const xmlChar*)"requre2");
					requre = const_cast<char *>(reinterpret_cast<const char *>(_requre));
					xmlFree(_requre);
				}
				/*取出photoId2*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"statuaryColour2"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"statuaryColour2");
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));	
					xmlFree(_photoId);
					if(!requre.empty() && !photoId.empty())
					{
						limitToPhotoId[requre] = photoId;
						photoId.erase();
						requre.erase();
					}
				}
				
				/*取出requre3*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"requre3"))
				{
					xmlChar *_requre=xmlGetProp(propNodePtr_item,(const xmlChar*)"requre3");
					requre = const_cast<char *>(reinterpret_cast<const char *>(_requre));
					xmlFree(_requre);
				}
				/*取出photoId3*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"statuaryColour3"))
				{
					xmlChar *_photoId=xmlGetProp(propNodePtr_item,(const xmlChar*)"statuaryColour3");
					photoId = const_cast<char *>(reinterpret_cast<const char *>(_photoId));	
					xmlFree(_photoId);
					if(!requre.empty() && !photoId.empty())
					{
						limitToPhotoId[requre] = photoId;
						photoId.erase();
						requre.erase();
					}
				}
				
				/*取出mapId*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					xmlChar *_mapId=xmlGetProp(propNodePtr_item,(const xmlChar*)"mapId");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(_mapId));	
					xmlFree(_mapId);
					
					flgItem = 1;
				}
				
				/*实例化*/	
				if(flgItem == 1)
				{
					newStatuaryBase = new StatuaryBase(const_cast<char*>\
					(vocationId.c_str()),limitToPhotoId,piexPt,\
					const_cast<char *>(mapId.c_str()));
					
					// cout<<"test the read_statuaryBase vocationId begin :"<<vocationId<<endl;
					vocationToStatuaryBaseConf[vocationId] = newStatuaryBase;			
					// cout<<"test the read_statuaryBase vocationId end :"<<vocationId<<endl;
					flgItem = 0;					
					limitToPhotoId.clear();
				}		
					
				attrPtr = attrPtr->next;	
			}
		}
		curNode = curNode->next;
	}
	xmlFreeDoc(doc);
	return 0;
}

