/************************************************************
	文件名：read_cpyLimit.cpp
	文件作用：读取副本所有限制的配置文件
	作者：chenzhen
	创建日期：2012.03.11
************************************************************/
/************************************************************
		修改备注
	修改者：chenzhen
	修改日期：2012.06.11
	修改内容：根据副本管理方案，重新作出调整,添加注释
************************************************************/

#include"function_read_configuration_files.h"
#include"cpy.h"
#include"cpyLimit.h"
#include"map_inform.h"
#include<libxml/parser.h>
#include"command_other_function_all_over.h"
#include"cpyManager.h"

/*后面添加的全局变量，建为副本id，值为副本限制实例指针，add chenzhen 2012.06.11*/
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern CpyManger *cpyManger;
int read_files_cpy(char *fileName)
{
	xmlDocPtr doc;              
	xmlNodePtr curNode;    //xml节点类型的临时变量
	
	char szDocName[50]={0};
	
	strcpy(szDocName,fileName);	
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
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
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_cpy;		
	while(curNode!=NULL)
	{
		string MapId;         //副本地图id，临时变量
		string cpyId;        //副本id
		string cpyLimitId;   //副本限制id
		int mapSum;          //副本地图数目
		list<string> cpyMapSet;   //装副本地图id
		int room;            //副本房间数
		int flgCpy;          //标志临时变量
		flgCpy = -1;
		map<string,CpyLimit*>::iterator cpyLimit_it;  //迭代器
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"cpy"))
		{
		
			propNodePtr_cpy=curNode;
			xmlAttrPtr attrPtr=propNodePtr_cpy->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取副本id */
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyId"))
				{
					xmlChar *_cpyId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"cpyId");
					cpyId = reinterpret_cast<const char *>(_cpyId);					
					xmlFree(_cpyId);						
				}
				
				/*读取副本限制id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyLimitId"))
				{
					xmlChar *_cpyLimitId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"cpyLimitId");
					cpyLimitId = reinterpret_cast<const char *>(_cpyLimitId);					
					xmlFree(_cpyLimitId);						
				}				
				
				/*读取副本地图id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId1"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId1");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}	
				
				/*读取副本地图id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId2"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId2");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}
				
				/*读取副本地图id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId3"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId3");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}	
				
				/*读取副本地图id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId4"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId4");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}
				
				/*读取副本地图id*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"MapId5"))
				{
					xmlChar *_MapId=xmlGetProp(propNodePtr_cpy,(const xmlChar*)"MapId5");
					MapId = reinterpret_cast<const char *>(_MapId);					
					xmlFree(_MapId);
					cpyMapSet.push_back(MapId);
				}	
				
				/*读取mapSum属性*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapSum"))
				{					
					xmlChar *_mapSum = xmlGetProp(propNodePtr_cpy,(const xmlChar*)"mapSum");
					mapSum = atoi(reinterpret_cast<const char *>(_mapSum));
					xmlFree(_mapSum);
					flgCpy = 1;
				}
				attrPtr=attrPtr->next;	
				
				/*生成副本房间*/			
				if(flgCpy == 1 && cpyMapSet.size() == mapSum)
				{
					cpyLimit_it = cpyId_to_cpyLimit.find(cpyId);
					if(cpyLimit_it == cpyId_to_cpyLimit.end())
					{
						cout<<"the config cpyId.xml is error :"<<cpyId<<endl;
						exit(1);
					}
					room = cpyLimit_it->second->getRoom();
					int i;					
					for(i = 0;i < room;i++)
					{							
						char initCpyId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};        //副本实例id，即副本id后面追加流水号
						strncpy(initCpyId,cpyId.c_str(),strlen(cpyId.c_str()));
						strncat(initCpyId,"_",strlen("_"));
						appendNum(initCpyId,i,4);	//房间号占四位					
						Cpy *newCpy = new Cpy(initCpyId,cpyMapSet,cpyLimit_it->second);
						cpyLimit_it->second->PushCpy(newCpy);
					}
					flgCpy = 0;
				}				
			}	
		}
		curNode=curNode->next;
	}
	
	xmlFreeDoc(doc);
	return 0;
}
