
/********************************************************************

    created:	2012/2/22  15:24
	
	文件名：	function_read_configuration_files_map.cpp

    author:     ChenZhen 

    purpose:  	用来读取所有地图的配置文件（格式为xml)
	
	修	改：	Tory 	2012/2/28
	
	修改内容：	将data_structure_struct中的Monster_Inform结构体改为Monster_Inform类，
				无任何逻辑改动，仅仅为了与hero_configuration类保持统一

*********************************************************************/

#include"function_read_configuration_files.h"
#include<libxml/parser.h>
#include"data_structure_struct.h"
#include"monster_configuration.h"
#include"map_inform.h"
#include<iostream>
#include<vector>
#include<string.h>
#include"monsterBase.h"
#include"monsterTool.h"

using namespace std;


extern map<string,Monster_Inform*>monTypeId_connect_property;
extern map<string,MonsterTool*> toolToMonster;
int read_tool_brush_monster(char *fileName)
{	
	map<string,Monster_Inform*>::iterator it;
	Monster_Inform *mon_inform;
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	MonsterTool *monsterTool;
	char szDocName[50]={'\0'};		
	string toolTypId,typeId;
	int flgItem;	
	
	strncpy(szDocName,fileName,strlen(fileName));
	string nickName,photoId,mapId,uniqueId,toolTypeId;		
	Point piexPt;
	int lifeUpperVal;
	int lifeVal;
	int magicUpperVal;
	int magicVal;
		
	int walkRange;
	int attackRange;
			
			
	int hrtSud;      //秒伤
	int outHrt;     //外伤
	int inHrt;      //内伤
	int outAttVal;    //外功攻击值
	int inAttVal;    //内功攻击值
	int outDefVal;    //外功防御值
	int inDefVal;    //内功防御值
	int defSumVal;   //防御值总和
	int hit;        //命中
	int crit;       //暴击
	int voids;    	  //闪避
	int tenacity;       //韧性	
	int hatRge;               //仇恨范围
	int hatVal;               //仇恨值
	
	int failGoodsLess;   //怪物掉落最大值
	int failGoodsMost;   //怪物掉落最大值
	int hatRange;      //仇恨范围
	int gold;       //金币
	set<string> failList;  //掉落列表
	int radius;
	char *type;          //add chenzhen 5.30 （有被动，主动，巡逻三种）
	char *kind;          //add chenzhen 5.30 （有普通，精英，Boss三种）
	double cdTime;       //cd时间
	int experience;      //经验
	int angVal;          //怒气值
	vector<string>skiIdSet;   //技能id列表
	int rank;            //等级
	int speed;           //移动速度
	LveCtnManger lveCtnMager(1,3);      //怪物存活次数管理器
			
	int fiveEleInt;      //五行属性代表值
	int fiveEleRank;     //五行等级值
	int fiveHurt;        //五行伤害值
			
	int goFor;           //走动频率
	int expTme;           //经验倍数
	int monyTme;          //金钱倍数
	char *genAttId; 
	char *stage;
	int _ownerAttriType;  //怪物所属阵营，帮派类型
	char* _ownerAttri;    //怪物所属阵，帮派营值
	double attackRatio;          //击杀红名怪按比例来算
	bool isInnerAttack;   //偏内功为真，否则为假
	
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
	
	//循环读取xml的子节点，并取出相对应的内容	
	while(curNode!=NULL)
	{	
		
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"toolMon"))
		{
			propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{			
				/*取出道具怪的类型id*/				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					
					xmlChar *_typeId = xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");				
					
					typeId = "MP";				
					
					typeId += const_cast<char *>(reinterpret_cast<const char *>(_typeId));
	
					xmlFree(_typeId);
					
					it=monTypeId_connect_property.find(typeId);
					if(it == monTypeId_connect_property.end())
					{
						return -5;
					}
					mon_inform=it->second;			//取map迭代器对应的值
					
					lifeUpperVal = mon_inform->lifeUpperVal;
					lifeVal = mon_inform->lifeVal;
					magicUpperVal = mon_inform->magicUpperVal;
					magicVal = mon_inform->magicVal;
					hrtSud = mon_inform->hrtSud;
					outHrt = mon_inform->outHrt;
					inHrt = mon_inform->inHrt;
					outAttVal = mon_inform->outAttVal;
					inAttVal = mon_inform->inAttVal;
					outDefVal = mon_inform->outDefVal;
					defSumVal = mon_inform->defSumVal;
					inDefVal = mon_inform->inDefVal;
					defSumVal = mon_inform->defSumVal;
					
					
					hit = mon_inform->hit;
					crit = mon_inform->crit;
					voids = mon_inform->voids;
					
					tenacity = mon_inform->tenacity;
					hatRange = mon_inform->hatRange;
					failGoodsLess = mon_inform->failGoodsLess;
					failGoodsMost = mon_inform->failGoodsMost;
					hatVal = mon_inform->hatVal;
					gold = mon_inform->gold;
					failList = mon_inform->failList;
					
					nickName = mon_inform->nickName;
					walkRange = mon_inform->walk_range;
					attackRange = mon_inform->attack_range;
					photoId = mon_inform->photoId;
					type = mon_inform->type;        //add chenzhen 5.30
					kind = mon_inform->kind;          //add chenzhen 5.11
					radius = mon_inform->radius;      //add chenzhen 5.29
					cdTime = mon_inform->cdTime;
					experience = mon_inform->getExperience();
					angVal = mon_inform->getAngVal();
					skiIdSet = mon_inform->getSkiIdSet();
					rank = mon_inform->getRank();
					speed = mon_inform->getSpeed();
					
					fiveEleInt = mon_inform->fiveEleInt;
					fiveEleRank = mon_inform->fiveEleRank;
					fiveHurt =  mon_inform->fiveHurt;  
					goFor = mon_inform->goFor;
					expTme = mon_inform->expTme;
					monyTme = mon_inform->monyTme;
					genAttId = mon_inform->genAttId;
					stage = mon_inform->stage;
					
					_ownerAttriType = mon_inform->ownerAttriType;
					_ownerAttri = mon_inform->ownerAttri;
					attackRatio = mon_inform->attackRatio;
					
					isInnerAttack = mon_inform->isInnerAttack;
				}			
				
				
				/*读取道具的类型id*/	
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"toolTypeId"))
				{
					xmlChar *_toolTypeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"toolTypeId");	
					toolTypeId = const_cast<char *>(reinterpret_cast<const char *>(_toolTypeId));
					xmlFree(_toolTypeId);
					flgItem = 1;				
				}
							
				/*实例化道具怪*/	
				if(flgItem == 1)
				{
					mapId = "map_001";
					uniqueId = "-1";
					piexPt._x = -1;
					piexPt._y = -1;
					
					monsterTool = new MonsterTool(const_cast<char *>(mapId.c_str()),\
												const_cast<char *>(typeId.c_str()),\
												const_cast<char *>(nickName.c_str()),\
												const_cast<char *>(uniqueId.c_str()),type,\
												kind,experience,cdTime,lifeUpperVal,lifeVal,\
												magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
												outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,\
												hit,crit,voids,tenacity,walkRange, hatRange,\
												attackRange,failGoodsLess,failGoodsMost,\
												hatVal,gold,failList,piexPt,rank,speed,\
												fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,\
												monyTme,stage,const_cast<char *>(photoId.c_str()),\
												skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,\
												attackRatio,isInnerAttack,lveCtnMager);	
												
					toolToMonster[toolTypeId] = monsterTool;
					cout<<"toolTypeId:"<<toolTypeId<<endl;
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
