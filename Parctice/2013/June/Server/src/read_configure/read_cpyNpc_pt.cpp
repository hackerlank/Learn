/************************************************************
	文件名：read_cpyNpc_pt.cpp
	文件作用：读取副本npc的坐标信息
	作者：chenzhen
	创建日期：2012.12.29
************************************************************/
#include"function_read_configuration_files.h"
#include"data_structure_struct.h"
#include<libxml/parser.h>

/*金陵普通副本npc传送点*/
extern Point JLGENPT;

/*开封普通副本npc传送点*/
extern Point KFGENPT;

/*开封帮派副本npc传送点*/
extern Point KFPARPT;

/*金陵帮派副本npc传送点*/
extern Point JLPARPT;

/*角色离帮派副本npc传送点多少距离才能传送*/
extern int LIMPRTRAG;

/*角色离普通副本npc传送点多少距离才能传送*/
extern int LIMGENRAG;

int read_Npc_cpy_pt(char *fileName)
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
	xmlNodePtr propNodePtr_npc;		
	while(curNode!=NULL)
	{
		string mapId;         //此npc地图id
		Point piexPt;         //此npc的像素点坐标
		int cpyType;             //此npc掌管的副本类型
		int range;            //副本地图数目
		
		int npcFlg = -1;
	
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"NpcPt"))
		{		
			propNodePtr_npc=curNode;
			xmlAttrPtr attrPtr=propNodePtr_npc->properties;
			
			while(attrPtr!=NULL)
			{	
				/*读取地图id */
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					xmlChar *_mapId=xmlGetProp(propNodePtr_npc,(const xmlChar*)"mapId");
					mapId = reinterpret_cast<const char *>(_mapId);					
					xmlFree(_mapId);						
				}
				
				/*掌管副本类型*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"cpyType"))
				{
					xmlChar *_cpyType=xmlGetProp(propNodePtr_npc,(const xmlChar*)"cpyType");			
					cpyType = atoi(reinterpret_cast<const char *>(_cpyType));				
					xmlFree(_cpyType);						
				}				
				
				/*读取npc的横坐标*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
					xmlChar *x=xmlGetProp(propNodePtr_npc,(const xmlChar*)"x");
					piexPt._x = atoi(reinterpret_cast<const char *>(x));			
					xmlFree(x);					
				}	
				/*读取npc的纵坐标*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
					xmlChar *y=xmlGetProp(propNodePtr_npc,(const xmlChar*)"y");
					piexPt._y = atoi(reinterpret_cast<const char *>(y));			
					xmlFree(y);					
				}	
				/*读取npc的掌管距离*/
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"range"))
				{
					xmlChar *_range=xmlGetProp(propNodePtr_npc,(const xmlChar*)"range");
					range = atoi(reinterpret_cast<const char *>(_range));			
					xmlFree(_range);	
					npcFlg = 1;
				}
				
				attrPtr=attrPtr->next;
				
				if(npcFlg == 1)
				{
					if(mapId.compare("map_001") == 0)
					{
						if(cpyType == 1)
						{
							KFGENPT = piexPt;
							
							LIMGENRAG = range;
						}
						else
						{
							KFPARPT = piexPt;
							
							LIMPRTRAG = range;
						}						
					}
					
					else if(mapId.compare("map_010") == 0)
					{
						if(cpyType == 1)
						{
							JLGENPT = piexPt;
							
							LIMGENRAG = range;
						}
						else
						{
							JLPARPT = piexPt;
							
							LIMPRTRAG = range;
						}
							
					}
					npcFlg = 0;
				}					
			}	
		}
		curNode=curNode->next;
	}	
	xmlFreeDoc(doc);
	return 0;
}
