
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
#include"monsterActive.h"
#include"monsterBase.h"
#include"monsterPatrol.h"
#include"monsterPassivity.h"
#include"monsterPasstrol.h"
#include"monsterCamp.h"
#include "monsterTowerDefence.h"
#include"takeGoods.h"
#include"bottle.h"
#include"trap.h"
#include"map_src.h"
#include"map_cpy.h"
#include"monsterAttRed.h"
#include"monsterEscape.h"
#include"monsterByHero.h"
#include"monsterStatuary.h"
#include"monsterStill.h"
using namespace std;

#include "data_structure_struct.h"
#define Map_Val(a,b) ( map<string,const jumpId_infor*>::value_type( (a),(b)) )

extern map<string,Map_Src*>mapId_connect_map;
extern map<string,Monster_Inform*>monTypeId_connect_property;

extern set<string>map_timer;
extern map<string,Map_Cpy*> cpyMapConf;

extern map<string,const jumpId_infor*> jumpId2mapInfo;
extern map<string,TakeGoods*> takeGoodsConfMap;
extern map<string,Bottle*> bottleConfMap;
extern map<string,Trap*> trapConfMap;
extern map<string,Map_Src*> confVipRoom;
extern map<string,Map_Src*> confPartyRoom;
extern map<string,Map_Src*> confCampRoom; 
extern MapType_T mapTypeInfo;
int read_files_map(char *fileName)
{

	
	xmlDocPtr doc;              
	xmlNodePtr curNode;
	char szDocName[50]={0};
	strcpy(szDocName,fileName);
	
	//cout<<"in the configuration_files_map.cpp file:"<<fileName<<endl;
	//读取地图配置文件
	doc=xmlReadFile(szDocName,"UTF-8",XML_PARSE_RECOVER);
	if(NULL==doc)
	{
		return -1;
	}
	//得到xml文件的root
	curNode=xmlDocGetRootElement(doc);
	if(NULL==curNode)
	{
		xmlFreeDoc(doc);
		return -3;
	}
	//xml的相关变量
	curNode=curNode->xmlChildrenNode;
	xmlNodePtr propNodePtr_map;
	xmlNodePtr propNodePtr_floor;
	xmlNodePtr propNodePtr_jumpId;
	xmlNodePtr propNodePtr_item;
	xmlNodePtr propNodePtr_mon;
	xmlNodePtr propNodePtr_gro;
	xmlNodePtr propNodePtr_itemBottle;
	xmlNodePtr propNodePtr_trap;
	xmlNodePtr propNodePtr_dishPt;
	//生成地图实类的相关变量
	Map_Inform *map_instance = NULL;
	TakeGoods *newTakeGoods = NULL;
	Bottle *myBottle = NULL;
	Trap *newTrap = NULL;
	map<string,Bottle*> botInMap;
	string mapId;
	string mapFilePath;
	string name;
	
	int width;
	int height;
	int row;
	int col;
	int baseDigst;
	
	
	Point entPt;
	Point outPt(-1,-1);
	
	Point tribesPt(-1,-1);			//阵营邪派诞生地；
	Point religionPt(-1,-1);		//阵营宗教诞生地；
	Point rangerPt(-1,-1);			//阵营游侠诞生地； added by xhm 2012-8-28;
	
	int mapType=1;					//地图类型 int 0主城 1场景 2副本 3帮派战 4阵营战 5守卫扬州,6阵营边境；
	int warType=1;					//地图作战模式；
	int changePkType=0;				//切换作战模式；
	
		
	int	campEntFlag;		//不加阵营是否可进图该地图标记值（0，可进入 1，不可进入）；
	int	levelLowerLimit;	//跳转点等级下限制；
	int levelUpperLimit;	//地图跳转点等级上限值；
	
	
	int flgCpy;
	
	
	int flgMon;   
	
	int sumMon;                   //怪物总数量
	map<string,MonsterBase*> monMap;
	map<string,BruMonInfor*> bruRecod;
	vector< vector<int> > hinder;
		
	map<string,const jumpId_infor*> _jumpId_infor;  //added by xhm;	
	
	vector<BruGro> bruGropVec;
	
	vector<int> bruEachTme;
	
	BruGro bruGro;
	
	set<string>groMonId;
	
	map<string,TakeGoods*> _takeGoodsMap;
	vector<TakeGoods*> takeGoodsVec;
	map<string,Trap*> trapVec;
	set<Point> dishPtSet;
	//循环读取xml的子节点，并取出相对应的内容
	
	
	flgMon = -1;	
	
	/*中心点和半径默认值*/
	Point centerPt(-1,-1);
	size_t radius = 0;
	
	
	
	
	/*在每张地图上控制怪物走动频率*/
	int MonKindCtn[11] = {0};
	sumMon = 0;
	
	list<string>monAttRedList;
	while(curNode!=NULL)
	{	
		if(!xmlStrcmp(curNode->name,(const xmlChar *)"map"))
		{
			propNodePtr_map=curNode;
			xmlAttrPtr attrPtr=propNodePtr_map->properties;
			while(attrPtr!=NULL)
			{			
				int len;
				//取出地图的id（char*型）
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapId"))
				{
					xmlChar *_mapId=xmlGetProp(propNodePtr_map,(const xmlChar*)"mapId");
					mapId = const_cast<char *>(reinterpret_cast<const char *>(_mapId));		
									
					xmlFree(_mapId);
				}
				//读取地图的路径
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapFilePath"))
				{
					xmlChar *_mapFilePath=xmlGetProp(propNodePtr_map,(const xmlChar*)"mapFilePath");
					
					mapFilePath = const_cast<char *>(reinterpret_cast<const char *>(_mapFilePath));
					
					xmlFree(_mapFilePath);
				}
				//读取地图的名字
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapName"))
				{
					xmlChar *_mapName=xmlGetProp(propNodePtr_map,(const xmlChar*)"mapName");
					
					name = const_cast<char *>(reinterpret_cast<const char *>(_mapName));
					
					xmlFree(_mapName);
				}
				//读取地图是否为副本地图标志
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"flagCpy"))
				{
					xmlChar *_flagCpy=xmlGetProp(propNodePtr_map,(const xmlChar*)"flagCpy");
					flgCpy = atoi(reinterpret_cast<const char *>(_flagCpy));
					xmlFree(_flagCpy);
				}
				
				//读取地图入点横坐标
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"entPt_x"))
				{
					xmlChar *_entPt_x=xmlGetProp(propNodePtr_map,(const xmlChar*)"entPt_x");
					entPt._x = atoi(reinterpret_cast<const char *>(_entPt_x));
					xmlFree(_entPt_x);
				}
				//读取地图入点纵坐标
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"entPt_y"))
				{
					xmlChar *_entPt_y=xmlGetProp(propNodePtr_map,(const xmlChar*)"entPt_y");
					entPt._y = atoi(reinterpret_cast<const char *>(_entPt_y));
					xmlFree(_entPt_y);
				}
				//读取地图出点横坐标
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"outPt_x"))
				{
					xmlChar *_outPt_x=xmlGetProp(propNodePtr_map,(const xmlChar*)"outPt_x");
					outPt._x = atoi(reinterpret_cast<const char *>(_outPt_x));
					xmlFree(_outPt_x);
				}
				//读取地图出点纵坐标
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"outPt_y"))
				{
					xmlChar *_outPt_y=xmlGetProp(propNodePtr_map,(const xmlChar*)"outPt_y");
					outPt._y = atoi(reinterpret_cast<const char *>(_outPt_y));
					xmlFree(_outPt_y);
				}
				//读取邪教配置出生点；			
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"tribesPt_x"))
				{
					xmlChar *_tribesPt_x=xmlGetProp(propNodePtr_map,(const xmlChar*)"tribesPt_x");
					tribesPt._x = atoi(reinterpret_cast<const char *>(_tribesPt_x));
					xmlFree(_tribesPt_x);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"tribesPt_y"))
				{
					xmlChar *_tribesPt_y=xmlGetProp(propNodePtr_map,(const xmlChar*)"tribesPt_y");
					tribesPt._y = atoi(reinterpret_cast<const char *>(_tribesPt_y));
					xmlFree(_tribesPt_y);
				}
				//读取宗教配置出生点；	
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"religionPt_x"))
				{
					xmlChar *_religionPt_x=xmlGetProp(propNodePtr_map,(const xmlChar*)"religionPt_x");
					religionPt._x = atoi(reinterpret_cast<const char *>(_religionPt_x));
					xmlFree(_religionPt_x);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"religionPt_y"))
				{
					xmlChar *_religionPt_y=xmlGetProp(propNodePtr_map,(const xmlChar*)"religionPt_y");
					religionPt._y = atoi(reinterpret_cast<const char *>(_religionPt_y));
					xmlFree(_religionPt_y);
				}
			    //读取游侠配置出生点；	
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rangerPt_x"))
				{
					xmlChar *_rangerPt_x=xmlGetProp(propNodePtr_map,(const xmlChar*)"rangerPt_x");
					rangerPt._x = atoi(reinterpret_cast<const char *>(_rangerPt_x));
					xmlFree(_rangerPt_x);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"rangerPt_y"))
				{
					xmlChar *_rangerPt_y=xmlGetProp(propNodePtr_map,(const xmlChar*)"rangerPt_y");
					rangerPt._y = atoi(reinterpret_cast<const char *>(_rangerPt_y));
					xmlFree(_rangerPt_y);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"warType"))
				{
					xmlChar *_war_type=xmlGetProp(propNodePtr_map,(const xmlChar*)"warType");
					warType = atoi(reinterpret_cast<const char *>(_war_type));
					xmlFree(_war_type);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"changePkType"))
				{
					xmlChar *_changePK_type=xmlGetProp(propNodePtr_map,(const xmlChar*)"changePkType");
					changePkType = atoi(reinterpret_cast<const char *>(_changePK_type));
					xmlFree(_changePK_type);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"maptype"))
				{
					xmlChar *_changePK_type=xmlGetProp(propNodePtr_map,(const xmlChar*)"maptype");
					mapType = atoi(reinterpret_cast<const char *>(_changePK_type));					
					xmlFree(_changePK_type);
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"campEntFlag"))
				{
					xmlChar *_changePK_type=xmlGetProp(propNodePtr_map,(const xmlChar*)"campEntFlag");
					campEntFlag = atoi(reinterpret_cast<const char *>(_changePK_type));
					xmlFree(_changePK_type);
				}				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"levelLowerLimit"))
				{
					xmlChar *_changePK_type=xmlGetProp(propNodePtr_map,(const xmlChar*)"levelLowerLimit");
					levelLowerLimit = atoi(reinterpret_cast<const char *>(_changePK_type));
					xmlFree(_changePK_type);
				}				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"levelUpperLimit"))
				{
					xmlChar *_changePK_type=xmlGetProp(propNodePtr_map,(const xmlChar*)"levelUpperLimit");
					levelUpperLimit = atoi(reinterpret_cast<const char *>(_changePK_type));
					xmlFree(_changePK_type);
				}
				//读取地图的宽度（像素）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapWidth"))
				{
					xmlChar *_mapWidth=xmlGetProp(propNodePtr_map,(const xmlChar*)"mapWidth");
					width=atoi(reinterpret_cast<const char *>(_mapWidth));
					xmlFree(_mapWidth);
				}
				//读取地图的长度（像素）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"mapHeight"))
				{
					xmlChar *_mapHeight=xmlGetProp(	propNodePtr_map,(const xmlChar*)"mapHeight");
					height=atoi(reinterpret_cast<const char *>(_mapHeight));
					xmlFree(_mapHeight);
				}
				//读取地图的横数（网格）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"row"))
				{
					xmlChar *_row=xmlGetProp(propNodePtr_map,(const xmlChar*)"row");
					row=atoi(reinterpret_cast<const char *>(_row));
					xmlFree(_row);
				}
				//读取地图的列数（网格）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"col"))
				{
					xmlChar *_col=xmlGetProp(propNodePtr_map,(const xmlChar*)"col");
					col=atoi(reinterpret_cast<const char *>(_col));
					xmlFree(_col);
				}
				//读取地图的偏移量
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"baseDigst"))
				{
					xmlChar *_baseDigst=xmlGetProp(propNodePtr_map,(const xmlChar*)"baseDigst");
					baseDigst=atoi(reinterpret_cast<const char *>(_baseDigst));
					xmlFree(_baseDigst);	
				}
				attrPtr=attrPtr->next;
			}
		}
		
		/*读取中心点和随机半径*/
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"randPtRule"))
		{
		    propNodePtr_dishPt = curNode;
			xmlAttrPtr attrPtr=propNodePtr_dishPt->properties;
			while(attrPtr!=NULL)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"centerPt._x"))
				{
				    xmlChar *centPt_x=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"centerPt._x");
					centerPt._x = atoi(reinterpret_cast<const char *>(centPt_x));
					xmlFree(centPt_x);	
					
	//				cout<<"centerPt._x:"<<centerPt._x<<endl;
				}
				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"centerPt._y"))
				{
				    xmlChar *centPt_y=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"centerPt._y");
					centerPt._y = atoi(reinterpret_cast<const char *>(centPt_y));
					xmlFree(centPt_y);	
	//				cout<<"centerPt._y:"<<centerPt._y<<endl;
				}
				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"radius"))
				{
				    xmlChar *_radius=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"radius");
					radius = atoi(reinterpret_cast<const char *>(_radius));
					xmlFree(_radius);	
	//				cout<<"radius:"<<radius<<endl;
				}				
				attrPtr=attrPtr->next;
			}
		}
		
		
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"dishSet"))
		{
			Point dishPt;
			map<string,Bottle*>::iterator bottle_it;
		    propNodePtr_dishPt = curNode;
			xmlAttrPtr attrPtr=propNodePtr_dishPt->properties;
			while(attrPtr!=NULL)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt1._x"))
				{
				    xmlChar *dish_x=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt1._x");
					dishPt._x = atoi(reinterpret_cast<const char *>(dish_x));
					xmlFree(dish_x);	
				}
				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt1._y"))
				{
				    xmlChar *dish_y=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt1._y");
					dishPt._y = atoi(reinterpret_cast<const char *>(dish_y));
					xmlFree(dish_y);	
					dishPtSet.insert(dishPt);
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt2._x"))
				{
				    xmlChar *dish_x=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt2._x");
					dishPt._x = atoi(reinterpret_cast<const char *>(dish_x));
					xmlFree(dish_x);	
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt2._y"))
				{
				    xmlChar *dish_y=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt2._y");
					dishPt._y = atoi(reinterpret_cast<const char *>(dish_y));
					xmlFree(dish_y);
					dishPtSet.insert(dishPt);					
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt3._x"))
				{
				    xmlChar *dish_x=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt3._x");
					dishPt._x = atoi(reinterpret_cast<const char *>(dish_x));
					xmlFree(dish_x);	
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt3._y"))
				{
				    xmlChar *dish_y=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt3._y");
					dishPt._y = atoi(reinterpret_cast<const char *>(dish_y));
					xmlFree(dish_y);
					dishPtSet.insert(dishPt);					
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt4._x"))
				{
				    xmlChar *dish_x=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt4._x");
					dishPt._x = atoi(reinterpret_cast<const char *>(dish_x));
					xmlFree(dish_x);	
				}
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"dishPt4._y"))
				{
				    xmlChar *dish_y=xmlGetProp(propNodePtr_dishPt,(const xmlChar*)"dishPt4._y");
					dishPt._y = atoi(reinterpret_cast<const char *>(dish_y));
					xmlFree(dish_y);
					dishPtSet.insert(dishPt);					
				}
				attrPtr=attrPtr->next;
			}
		}
		
		
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"itemBottle"))
		{
			string botTypeId;
			Point bottlePt;
			bool itemBotFlg;
			map<string,Bottle*>::iterator bottle_it;
		    propNodePtr_itemBottle = curNode;
			itemBotFlg = false;
			xmlAttrPtr attrPtr=propNodePtr_itemBottle->properties;
			while(attrPtr!=NULL)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
				    xmlChar *_typeId=xmlGetProp(propNodePtr_itemBottle,(const xmlChar*)"typeId");
					botTypeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));
					xmlFree(_typeId);	
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
				    xmlChar *_x = xmlGetProp(propNodePtr_itemBottle,(const xmlChar*)"x");
					bottlePt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);	
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
				    xmlChar *_y = xmlGetProp(propNodePtr_itemBottle,(const xmlChar*)"y");
					bottlePt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);	
					itemBotFlg = true;
				}
				if(itemBotFlg)
				{					
					bottle_it = bottleConfMap.find(botTypeId);
					if(bottle_it != bottleConfMap.end())
					{
					   myBottle = bottle_it->second->copyBottle(bottlePt);					   
					   botInMap[myBottle->getId()] = myBottle;
					}
					itemBotFlg = false;
				}
				attrPtr=attrPtr->next;
			}
		}
		
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"item"))
		{
			string itemTypeId;
			Point takeGoodsPt;
			bool itemFlg,isResource;
			map<string,TakeGoods*>::iterator take_it;
			itemFlg = false;
			isResource = false;
			int resorceCount = 1;
		    propNodePtr_item = curNode;
			xmlAttrPtr attrPtr=propNodePtr_item->properties;
			while(attrPtr!=NULL)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
				    xmlChar *_typeId=xmlGetProp(propNodePtr_item,(const xmlChar*)"typeId");
					itemTypeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));
					xmlFree(_typeId);	
				}
				/*阵营战里面的资源*/
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isResource"))
				{
				     xmlChar *_isResource = xmlGetProp(propNodePtr_item,(const xmlChar*)"isResource");
					int boolVal = atoi(reinterpret_cast<const char *>(_isResource));
					xmlFree(_isResource);	
					if(boolVal == 1)
					{
						isResource = true;
					}
				}
				
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"resorceCount"))
				{
				    xmlChar *_resorceCount = xmlGetProp(propNodePtr_item,(const xmlChar*)"resorceCount");
					resorceCount = atoi(reinterpret_cast<const char *>(_resorceCount));
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
				    xmlChar *_x = xmlGetProp(propNodePtr_item,(const xmlChar*)"x");
					takeGoodsPt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);	
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
				    xmlChar *_y = xmlGetProp(propNodePtr_item,(const xmlChar*)"y");
					takeGoodsPt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);	
					itemFlg = true;
				}
				if(itemFlg)
				{					
					take_it = takeGoodsConfMap.find(itemTypeId);
					if(take_it != takeGoodsConfMap.end())
					{
						for(size_t ctn = 0;ctn < resorceCount;++ctn)
						{
							newTakeGoods = take_it->second->copyTakeGoods(takeGoodsPt,isResource);
							_takeGoodsMap[newTakeGoods->getId()] = newTakeGoods;
						}
					}
					itemFlg = false;
				}
				attrPtr=attrPtr->next;
			}
		}
		
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"itemTrap"))
		{
			string trapTypeId;
			Point trapPt;
			bool trapFlg;
			bool isCalled = false;
			map<string,Trap*>::iterator trap_it;
			trapFlg = false;
		    propNodePtr_trap = curNode;
			xmlAttrPtr attrPtr=propNodePtr_trap->properties;
			while(attrPtr!=NULL)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
				    xmlChar *_typeId=xmlGetProp(propNodePtr_trap,(const xmlChar*)"typeId");
					trapTypeId = const_cast<char *>(reinterpret_cast<const char *>(_typeId));
					xmlFree(_typeId);	
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isCalled"))
				{
				    xmlChar *_isCalled = xmlGetProp(propNodePtr_trap,(const xmlChar*)"isCalled");
					int callFlg = atoi(reinterpret_cast<const char *>(_isCalled));
					xmlFree(_isCalled);	
					if(callFlg == 1)
					{
						isCalled = true;
					}
				}
				
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{
				    xmlChar *_x = xmlGetProp(propNodePtr_trap,(const xmlChar*)"x");
					trapPt._x = atoi(reinterpret_cast<const char *>(_x));
					xmlFree(_x);	
				}
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
				    xmlChar *_y = xmlGetProp(propNodePtr_trap,(const xmlChar*)"y");
					trapPt._y = atoi(reinterpret_cast<const char *>(_y));
					xmlFree(_y);	
					trapFlg = true;
				}
				if(trapFlg)
				{					
					trap_it = trapConfMap.find(trapTypeId);
					if(trap_it != trapConfMap.end())
					{
						
					   newTrap = trap_it->second->copyTrap(trapPt,isCalled);
					   trapVec[newTrap->getId()] = newTrap;
					}
					trapFlg = false;
				}
				attrPtr=attrPtr->next;
			}
		}
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"skip"))
		{
		    string jumpId_val;
		    propNodePtr_jumpId=curNode;
			xmlAttrPtr attrPtr=propNodePtr_jumpId->properties;
			while(attrPtr!=NULL)
			{
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
				    xmlChar *_typeId=xmlGetProp(propNodePtr_jumpId,(const xmlChar*)"typeId");
					jumpId_val = const_cast<char *>(reinterpret_cast<const char *>(_typeId));
					map<string,const jumpId_infor*>::iterator iter = jumpId2mapInfo.find(jumpId_val);
					if(iter != jumpId2mapInfo.end())
					{
					   if(NULL != iter->second)
					     _jumpId_infor.insert(Map_Val(jumpId_val,iter->second));
					}
					xmlFree(_typeId);
				}
				attrPtr=attrPtr->next;
			}
		
		}
		
		//读取地图的像素的障碍情况
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"floor"))
		{
			propNodePtr_floor=curNode;
			xmlChar *_mapFloor=xmlNodeGetContent(propNodePtr_floor);
			char *mapFloor=const_cast<char *>(reinterpret_cast<const char *>(_mapFloor));
			int i,j,k,len;
			len=strlen(mapFloor);
			char p[2];
			
			for(i=0,k=0;i<col&&k<len;i++)
			{
				vector<int>line_hinder;
				for(j=0;j<row&&k<len;j++)
				{
					strncpy(p,mapFloor+k,1);
					p[1]='\0';
					int values=atoi(p);
					line_hinder.push_back(values);
					k+=2;
				}
				for(j;j<row;j++)
				{
					line_hinder.push_back(1);
				}
				hinder.push_back(line_hinder);
			}
			//Tory add；如果地图配置有误，则按col*row大小设置障碍点信息，无数据来源的点设为“1”
			for(i; i < col; i++)
			{
				vector<int>line_hinder(row, 1);
				hinder.push_back(line_hinder);
			}

			xmlFree(mapFloor);
		
		}	
		
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"group"))
		{
			if(!groMonId.empty())
			{
				BruGro groBruMonId(groMonId);
				bruGropVec.push_back(groBruMonId);
				groMonId.clear();
			}				
			propNodePtr_gro=curNode;
			xmlAttrPtr attrPtr=propNodePtr_gro->properties;
			while(attrPtr!=NULL)
			{
				//读取怪物的类型id
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"bruTme"))
				{
					double bruTme;
					int ctnTme;
					xmlChar *_bruTme=xmlGetProp(propNodePtr_gro,(const xmlChar*)"bruTme");		
					bruTme=atof(reinterpret_cast<const char *>(_bruTme));
					xmlFree(_bruTme);
					ctnTme = ceil(1.0 * bruTme/MAP_THINK_TIME);
					ctnTme = 9;
					bruEachTme.push_back(ctnTme);
				}
				attrPtr = attrPtr->next;
			}
		}
			
		//读取怪物节点的信息
		else if(!xmlStrcmp(curNode->name,(const xmlChar*)"monster"))
		{
			sumMon += 1; //默认加一，如果发现有参数，后面加上参数减一 by benliao 2012.12.7
			flgMon = 0;
			MonsterBase *mon= NULL;
			Point mon_pt;
			
			string typeId;
			string nickName;
			string uniqueId;
			string photoId;
			
			int lifeUpperVal;
			int lifeVal;
			int magicUpperVal;
			int magicVal;
			
			int sum;
			int walkRange;
			int attackRange;
			
			Point logicEndPt;
			int count;
			
			
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
			LveCtnManger lveCtnMager(1,2);      //怪物存活次数管理器
			
			int fiveEleInt;      //五行属性代表值
			int fiveEleRank;     //五行等级值
			int fiveHurt;        //五行伤害值
			
			int goFor;           //走动频率
			int expTme;           //经验倍数
			int monyTme;          //金钱倍数
			int campFlg;          //阵营模式
			
			char *genAttId;       //普通攻击id
			char *stage;          //掉落阶段
			
			int _ownerAttriType;  //怪物所属阵营，帮派类型
			char* _ownerAttri;    //怪物所属阵，帮派营值
			double attackRatio;          //击杀红名怪按比例来算
			ValueRatio valueRatio; //怪物属性系数
			bool isInnerAttack;      //偏内功为真，否则为假
			list<Point> endListPt;   //打红名的怪物寻路终点集合
			Point endFinPt;          //打红名的怪物寻路终点
			bool isCallType = false;           //召唤怪类型标志
			Monster_Inform *mon_inform = NULL;
			
			map<string,BruMonInfor*>::iterator typeId_it;
			
			map<string,Monster_Inform*>::iterator it;
			propNodePtr_mon=curNode;
			xmlAttrPtr attrPtr=propNodePtr_mon->properties;
			while(attrPtr!=NULL)
			{
				//读取怪物的类型id
				if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"typeId"))
				{
					xmlChar *_typeId=xmlGetProp(propNodePtr_mon,(const xmlChar*)"typeId");
					
					typeId = "MP";				
					
					typeId += const_cast<char *>(reinterpret_cast<const char *>(_typeId));
	
					xmlFree(_typeId);
					
					//注意：typeId_it 是在这张地图上怪物的相关数据的一个迭代器
					typeId_it = bruRecod.find(typeId);
					if(typeId_it == bruRecod.end())
					{						
						BruMonInfor *node = new BruMonInfor(const_cast<char *>(typeId.c_str()),0,0,0);		
						bruRecod[typeId] = node;						
					}	

					it = monTypeId_connect_property.find(typeId);			//it为特定怪物类型在monTypeId_connect_property中的迭代器
       				if(it == monTypeId_connect_property.end())
					{
					
						cout<<"read_files_map the monster typeId is error in map:"<<"error monsterId:"<<typeId<<"mapId:"<<mapId<<endl;
						exit(1);
						return -5;										//地图配置文件错误，无该类型的怪，返回-5
					}		
					it->second->sum+=1;			  						//整个游戏中，这种怪的数目		
					
					typeId_it = bruRecod.find(typeId);
					if(typeId_it == bruRecod.end())
					{
						continue;
					}
					int len_sum;
					sum = typeId_it->second->getSumCnt();         //这张地图中，这种怪的数目
					int Sum = sum;
					for(sum += 1,len_sum =0;sum >= 1;sum /= 10)
					{
						len_sum++;
					}						
					char *sum_str=new char[len_sum+1];
					sprintf(sum_str,"%d",Sum+1);
					uniqueId = typeId;
					uniqueId += "_";
				//	uniqueId += mapId;
				//	uniqueId += "_";
					uniqueId += sum_str;		
					delete [] sum_str;
					typeId_it->second->inputBruId(const_cast<char *>(uniqueId.c_str()));	
					
		//			groMonId.insert(uniqueId);
				}
				
				//读取怪物是否为召唤怪标志
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"isCallType"))
				{					
					xmlChar *_isCallType=xmlGetProp(propNodePtr_mon,(const xmlChar*)"isCallType");		
					int callFlg = atoi(reinterpret_cast<const char *>(_isCallType));
					xmlFree(_isCallType);
					if(callFlg == 1)
					{
						isCallType = true;
					}					
				}
				
				//读取怪物的刷出的次数
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"lveCtn"))
				{					
					xmlChar *_lveCtn=xmlGetProp(propNodePtr_mon,(const xmlChar*)"lveCtn");		
					lveCtnMager.sumLveCtn = atoi(reinterpret_cast<const char *>(_lveCtn));
					xmlFree(_lveCtn);
					if(!isCallType)
					{
						sumMon += lveCtnMager.sumLveCtn -1;
					}
					else
					{
						sumMon -=  1;
					}
				}
				//读取怪物的刷出的频率
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"durTme"))
				{					
					double durTme;
					xmlChar *_durTme=xmlGetProp(propNodePtr_mon,(const xmlChar*)"durTme");		
					durTme = atof(reinterpret_cast<const char *>(_durTme));
					xmlFree(_durTme);
					lveCtnMager.durTme = durTme;
					// lveCtnMager.durTme = (ceil(1.0 * durTme/MONSTER_THINK_TIME)) + 2.0;
				}
				//读取阵营怪的阵营属性
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"campFlg"))
				{					
					xmlChar *_campFlg=xmlGetProp(propNodePtr_mon,(const xmlChar*)"campFlg");		
					campFlg = atoi(reinterpret_cast<const char *>(_campFlg));
					xmlFree(_campFlg);
				}
				//读取打红名怪的巡逻终点横左边
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endFinPt1._x"))
				{					
					xmlChar *_endFinPt=xmlGetProp(propNodePtr_mon,(const xmlChar*)"endFinPt1._x");		
					endFinPt._x = atoi(reinterpret_cast<const char *>(_endFinPt));
					xmlFree(_endFinPt);
				}
				//读取打红名怪的巡逻终点横左边
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endFinPt1._y"))
				{					
					xmlChar *_endFinPt=xmlGetProp(propNodePtr_mon,(const xmlChar*)"endFinPt1._y");		
					endFinPt._y = atoi(reinterpret_cast<const char *>(_endFinPt));
					xmlFree(_endFinPt);					
					endListPt.push_back(endFinPt);
				}
				//读取打红名怪的巡逻终点横左边
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endFinPt2._x"))
				{					
					xmlChar *_endFinPt=xmlGetProp(propNodePtr_mon,(const xmlChar*)"endFinPt2._x");		
					endFinPt._x = atoi(reinterpret_cast<const char *>(_endFinPt));
					xmlFree(_endFinPt);
				}
				//读取打红名怪的巡逻终点横左边
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endFinPt2._y"))
				{					
					xmlChar *_endFinPt=xmlGetProp(propNodePtr_mon,(const xmlChar*)"endFinPt2._y");		
					endFinPt._y = atoi(reinterpret_cast<const char *>(_endFinPt));
					xmlFree(_endFinPt);					
					endListPt.push_back(endFinPt);
				}
				//读取打红名怪的巡逻终点横左边
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endFinPt3._x"))
				{					
					xmlChar *_endFinPt=xmlGetProp(propNodePtr_mon,(const xmlChar*)"endFinPt3._x");		
					endFinPt._x = atoi(reinterpret_cast<const char *>(_endFinPt));
					xmlFree(_endFinPt);
				}
				//读取打红名怪的巡逻终点横左边
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"endFinPt3._y"))
				{					
					xmlChar *_endFinPt=xmlGetProp(propNodePtr_mon,(const xmlChar*)"endFinPt3._y");		
					endFinPt._y = atoi(reinterpret_cast<const char *>(_endFinPt));
					xmlFree(_endFinPt);					
					endListPt.push_back(endFinPt);
				}
				//读取怪物的x坐标（像素）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"x"))
				{					
					xmlChar *_mon_x=xmlGetProp(propNodePtr_mon,(const xmlChar*)"x");		
					mon_pt._x=atoi(reinterpret_cast<const char *>(_mon_x));
					xmlFree(_mon_x);
				}
				//读取怪物的y坐标（像素）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"y"))
				{
					xmlChar *_mon_y=xmlGetProp(propNodePtr_mon,(const xmlChar*)"y");
					mon_pt._y=atoi(reinterpret_cast<const char *>(_mon_y));
					xmlFree(_mon_y);
					
					if(strcmp(it->second->type,"Patrol") == 0 )
					{
					
						flgMon = 1;
					}
					else
					{
						flgMon = 1;
					}						
				}
				
				
				//读取被动怪物或者主动怪的数目（只有被动怪和主动怪才好这样）
				//读取之后，且把它new出来，
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"count"))
				{	
					string _uniqueId;
					xmlChar *_count=xmlGetProp(propNodePtr_mon,(const xmlChar*)"count");		
					count=atoi(reinterpret_cast<const char *>(_count));
					xmlFree(_count);
					
					
					it=monTypeId_connect_property.find(typeId);
					if(it == monTypeId_connect_property.end())
					{
						return -5;
					}
					mon_inform=it->second;			//取map迭代器对应的值
					
					lifeUpperVal=mon_inform->lifeUpperVal;
					lifeVal=mon_inform->lifeVal;
					magicUpperVal=mon_inform->magicUpperVal;
					magicVal=mon_inform->magicVal;
					hrtSud=mon_inform->hrtSud;
					outHrt=mon_inform->outHrt;
					inHrt = mon_inform->inHrt;
					outAttVal=mon_inform->outAttVal;
					inAttVal=mon_inform->inAttVal;
					outDefVal=mon_inform->outDefVal;
					defSumVal=mon_inform->defSumVal;
					inDefVal=mon_inform->inDefVal;
					defSumVal=mon_inform->defSumVal;
					
					
					hit=mon_inform->hit;
					crit=mon_inform->crit;
					voids=mon_inform->voids;
					
					tenacity=mon_inform->tenacity;
					hatRange=mon_inform->hatRange;
					failGoodsLess=mon_inform->failGoodsLess;
					failGoodsMost = mon_inform->failGoodsMost;
					hatVal=mon_inform->hatVal;
					gold=mon_inform->gold;
					failList=mon_inform->failList;
					
					nickName=mon_inform->nickName;
					walkRange=mon_inform->walk_range;
					attackRange=mon_inform->attack_range;
					photoId=mon_inform->photoId;
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
					attackRatio  = mon_inform->attackRatio;
					isInnerAttack = mon_inform->isInnerAttack;
					if(strcmp(mon_inform->type,"MonByHero") == 0)
					{
						valueRatio.lifeUpperValRatio = mon_inform->lifeUpperVal;
					
						valueRatio.lifeValRatio = mon_inform->lifeVal;
					
						valueRatio.outHrtRatio = mon_inform->outHrt;
					
						valueRatio.inHrtRatio = mon_inform->inHrt;
					
						valueRatio.outAttValRatio = mon_inform->outAttVal;
					
						valueRatio.inAttValRatio = mon_inform->inAttVal;
					
						valueRatio.outDefValRatio = mon_inform->outDefVal;
					
						valueRatio.inDefValRatio = mon_inform->inDefVal;
					
						valueRatio.hitRatio = mon_inform->hit;
					
						valueRatio.critRatio = mon_inform->crit;					
					
						valueRatio.voidsRatio = mon_inform->voids;
					
						valueRatio.tenacityRatio = mon_inform->tenacity;
						
						valueRatio.rankRatio = mon_inform->rank;
					}
					
					
					
					int i;					
					for(i = 1;i < count;i++)
					{
						_uniqueId = "";
						int len_sum;
						sum = typeId_it->second->getSumCnt();
						int Sum = sum;

						for(sum += 1,len_sum =0;sum >= 1;sum /= 10)
						{
							len_sum++;
						}						
						char *sum_str=new char[len_sum+1];
						sprintf(sum_str,"%d",Sum+1);
						_uniqueId += typeId;
						_uniqueId += "_";
						_uniqueId += sum_str;		
						delete [] sum_str;
						
						typeId_it->second->inputBruId(const_cast<char *>(_uniqueId.c_str()));
						if(strcmp(mon_inform->type,"Active") == 0)
						{
							MonKindCtn[0]++;
							goFor = MonKindCtn[0];
							
							mon = new MonsterActive(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(_uniqueId.c_str()),type,kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
						}	
					
						else if(strcmp(mon_inform->type,"Passivity") == 0)
						{
							MonKindCtn[1]++;
							goFor = MonKindCtn[1];
						
						mon = new MonsterPassivity(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
						}
						
						else if(strcmp(mon_inform->type,"MonByHero") == 0)
						{
							MonKindCtn[8]++;
							goFor = MonKindCtn[8];
						
							mon = new MonsterByHero(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
							const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
							kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
							outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
							walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
							rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,\
							const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,\
							attackRatio,isInnerAttack,lveCtnMager,valueRatio);
						}
						
						else if(strcmp(mon_inform->type,"MonStill") == 0)
						{
							MonKindCtn[10]++;
							goFor = MonKindCtn[10];
						
							mon = new MonsterStill(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
							const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
							kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
							outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
							walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,\
							failList,mon_pt,rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,\
							const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,\
							_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);		
						}
						
						/*设置召唤标记值*/
						if(mon)
						{
							mon->setIsCallType(isCallType);
							if(!isCallType)
							{
								//如果是召唤怪，就不放在每一批里面刷出
								groMonId.insert(uniqueId);
							}
						}
						
					}
					
					flgMon = 0;
				}
				//读取巡逻怪的巡逻终点x坐标（先定为像素）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"logPt_x"))
				{					
					xmlChar *_logicEnd_x=xmlGetProp(propNodePtr_mon,(const xmlChar*)"logPt_x");		
					logicEndPt._x=atoi(reinterpret_cast<const char *>(_logicEnd_x));
					xmlFree(_logicEnd_x);
				}
				
				//读取巡逻怪的巡逻终点y坐标（先定为像素）
				else if(!xmlStrcmp(attrPtr->name,(const xmlChar*)"logPt_y"))
				{
					xmlChar *_logicEnd_y=xmlGetProp(propNodePtr_mon,(const xmlChar*)"logPt_y");		
					logicEndPt._y=atoi(reinterpret_cast<const char *>(_logicEnd_y));
					xmlFree(_logicEnd_y);					
					flgMon = 1;
				}
				if(flgMon == 1)
				{
					it=monTypeId_connect_property.find(typeId);
					if(it==monTypeId_connect_property.end())
					{
						return -5;
					}
					if(mon_inform == NULL)
					{
				
				
						mon_inform=it->second;			//取map迭代器对应的值
					
						lifeUpperVal=mon_inform->lifeUpperVal;
						lifeVal=mon_inform->lifeVal;
						magicUpperVal=mon_inform->magicUpperVal;
						magicVal=mon_inform->magicVal;
						hrtSud=mon_inform->hrtSud;
						outHrt=mon_inform->outHrt;
						inHrt = mon_inform->inHrt;
						outAttVal=mon_inform->outAttVal;
						inAttVal=mon_inform->inAttVal;
						outDefVal=mon_inform->outDefVal;
						defSumVal=mon_inform->defSumVal;
						inDefVal=mon_inform->inDefVal;
						defSumVal=mon_inform->defSumVal;
					
					
						hit=mon_inform->hit;
						crit=mon_inform->crit;
						voids=mon_inform->voids;
					
						tenacity=mon_inform->tenacity;
						hatRange=mon_inform->hatRange;
						failGoodsLess=mon_inform->failGoodsLess;
					
						hatVal=mon_inform->hatVal;
						gold=mon_inform->gold;
						failList=mon_inform->failList;
					
						nickName=mon_inform->nickName;
						walkRange=mon_inform->walk_range;
						attackRange=mon_inform->attack_range;
						photoId=mon_inform->photoId;
						type = mon_inform->type;
						kind = mon_inform->kind;          //add chenzhen 5.11
						radius = mon_inform->radius;        //add chenzhen 5.29
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
						attackRatio  = mon_inform->attackRatio;
						isInnerAttack = mon_inform->isInnerAttack;
						
						if(strcmp(mon_inform->type,"MonByHero") == 0)
						{
							valueRatio.lifeUpperValRatio = mon_inform->lifeUpperVal;						
					
							valueRatio.lifeValRatio = mon_inform->lifeVal;
					
							valueRatio.outHrtRatio = mon_inform->outHrt;
					
							valueRatio.inHrtRatio = mon_inform->inHrt;
					
							valueRatio.outAttValRatio = mon_inform->outAttVal;
					
							valueRatio.inAttValRatio = mon_inform->inAttVal;
					
							valueRatio.outDefValRatio = mon_inform->outDefVal;
					
							valueRatio.inDefValRatio = mon_inform->inDefVal;
					
							valueRatio.hitRatio = mon_inform->hit;
					
							valueRatio.critRatio = mon_inform->crit;					
					
							valueRatio.voidsRatio = mon_inform->voids;
					
							valueRatio.tenacityRatio = mon_inform->tenacity;
							
							valueRatio.rankRatio = mon_inform->rank;
						}
						
					}		
					//根据怪物的类型，实例化对应的怪
					if(strcmp(mon_inform->type,"Active") == 0)
					{
						MonKindCtn[0]++;
						goFor = MonKindCtn[0];
							
						mon = new MonsterActive(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);											
					}
					
					else if(strcmp(mon_inform->type,"Passivity") == 0)
					{
						MonKindCtn[1]++;
						goFor = MonKindCtn[1];
						
						mon = new MonsterPassivity(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
											
					}
					else if(strcmp(mon_inform->type,"Passtrol") == 0)
					{		
						MonKindCtn[2]++;
						goFor = MonKindCtn[2];
						
						mon = new MonsterPasstrol(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);
					}
					else if(strcmp(mon_inform->type,"Patrol") == 0)
					{
						MonKindCtn[3]++;
						goFor = MonKindCtn[3];
						
						logicEndPt._x = 0;     //add chenzhen 5.29
						logicEndPt._y = 0;     //add chenzhen 5.29
						mon = new MonsterPatrol(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager,logicEndPt,radius);
					}				
					else if(strcmp(mon_inform->type,"Tower") == 0)
					{
						MonKindCtn[4]++;
						goFor = MonKindCtn[4];
						
						logicEndPt._x = 0;    
						logicEndPt._y = 0;    
						mon = new monsterTowerDefence(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);					
					}
					else if(strcmp(mon_inform->type,"CampMon") == 0)
					{
						MonKindCtn[5]++;
						goFor = MonKindCtn[5];
						
						mon = new MonsterCamp(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>\
											(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,\
											isInnerAttack,lveCtnMager,campFlg);
					}
					else if(strcmp(mon_inform->type,"AttRedMon") == 0)
					{
					
						MonKindCtn[6]++;
						goFor = MonKindCtn[6];
						
						mon = new MonsterAttRed(const_cast<char *>(mapId.c_str()),\
											const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager,endListPt);
					}
					else if(strcmp(mon_inform->type,"EscapeMon") == 0)
					{
						
						MonKindCtn[7]++;
						goFor = MonKindCtn[7];
						
						mon = new MonsterEscape(const_cast<char *>(mapId.c_str()),\
											const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager,endListPt);
					}
					else if(strcmp(mon_inform->type,"MonByHero") == 0)
					{
							MonKindCtn[8]++;
							goFor = MonKindCtn[8];
						
							mon = new MonsterByHero(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
							const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
							kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
							outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
							walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
							rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,\
							const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,\
							_ownerAttri,attackRatio,isInnerAttack,lveCtnMager,valueRatio);
					}
					
					else if(strcmp(mon_inform->type,"MonStatuary") == 0)
					{
							MonKindCtn[9]++;
							goFor = MonKindCtn[9];
						
							mon = new MonsterStatuary(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
											const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
											kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
											outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
											walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,failList,mon_pt,\
											rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);				
					}
					else if(strcmp(mon_inform->type,"MonStill") == 0)
					{
							MonKindCtn[10]++;
							goFor = MonKindCtn[10];
						
							mon = new MonsterStill(const_cast<char *>(mapId.c_str()),const_cast<char *>(typeId.c_str()),\
							const_cast<char *>(nickName.c_str()),const_cast<char *>(uniqueId.c_str()),type,\
							kind,experience,cdTime,lifeUpperVal,lifeVal,magicUpperVal,magicVal,hrtSud,outHrt,inHrt,\
							outAttVal, inAttVal,outDefVal, inDefVal,defSumVal,hit,crit,voids,tenacity,\
							walkRange, hatRange,attackRange,failGoodsLess,failGoodsMost,hatVal,gold,\
							failList,mon_pt,rank,speed,fiveEleInt,fiveHurt,fiveEleRank,goFor,expTme,monyTme,stage,\
							const_cast<char *>(photoId.c_str()),skiIdSet,genAttId,angVal,_ownerAttriType,\
							_ownerAttri,attackRatio,isInnerAttack,lveCtnMager);		
					}
					
					/*设置召唤标记值*/
					if(mon)
					{
						mon->setIsCallType(isCallType);
						if(!isCallType)
						{
							//如果是召唤怪，就不放在每一批里面刷出
							groMonId.insert(uniqueId);
						}
					}						
					else
					{
						continue;
					}
					skiIdSet.clear();
					monMap[uniqueId] = mon;
				
					mon_inform = NULL;
					
					flgMon = 0;
				}
				attrPtr=attrPtr->next;						
			}
			
		}
		
		curNode=curNode->next;
	}
	
	xmlFreeDoc(doc);
	
	if(outPt._x == -1 && outPt._y == -1)
	{
		outPt = entPt;
	}
	
	if(tribesPt._x == -1 || tribesPt._y == -1)	//如果配置文件没有配置阵营出生点，默认设置为地图进入点；有疑问 RTX xhm;
	{
		tribesPt = entPt;
	}
	if(religionPt._x == -1 || religionPt._y == -1)
	{
		religionPt = entPt;
	}
	if(rangerPt._x == -1 || rangerPt._y == -1)
	{
		rangerPt = entPt;
	}
	// cout<<mapId<<": "<<tribesPt._x<<","<<tribesPt._y<<endl;
	// cout<<mapId<<": "<<religionPt._x<<","<<religionPt._y<<endl;
	// cout<<mapId<<": "<<rangerPt._x<<","<<rangerPt._y<<endl<<endl<<endl;
	
	if(!groMonId.empty())
	{
		BruGro groBruMonId(groMonId);
		bruGropVec.push_back(groBruMonId);
		groMonId.clear();
	}	
	
	deleteBruRec(bruRecod);		
	if(flgCpy)
	{
		map_instance=new Map_Cpy(const_cast<char *>(mapId.c_str()),\
		const_cast<char *>(mapFilePath.c_str()),const_cast<char *>\
		(name.c_str()),width,height,row,col,baseDigst,entPt,outPt,\
		tribesPt,religionPt,rangerPt,monMap,bruGropVec,bruEachTme,\
		_jumpId_infor,_takeGoodsMap,botInMap,trapVec,dishPtSet,\
		centerPt,radius,true,sumMon,warType,changePkType,mapType,\
		campEntFlag,levelLowerLimit,levelUpperLimit);		
	}
	
	else
	{
		map_instance = new Map_Src(const_cast<char *>(mapId.c_str()),\
		const_cast<char *>(mapFilePath.c_str()),const_cast<char *>\
		(name.c_str()),width,height,row,col,baseDigst,entPt,outPt,\
		tribesPt,religionPt,rangerPt,monMap,_jumpId_infor,_takeGoodsMap,\
		botInMap,trapVec,dishPtSet,centerPt,radius,false,warType,\
		changePkType,mapType,campEntFlag,levelLowerLimit,levelUpperLimit);	
	}
	
	map_instance->setMapHinder(hinder);//这里很特别，由于返回的引用
	map_instance->InitBox();	
	map_instance->setMonMap();
	map_instance->setTakeGoodsMap();
	
	/*测试用的，其实，瓶罐是在副本地图里面*/
	map_instance->setBotMap();
	
	/*测试用的，其实，陷阱是在副本地图里面*/
	map_instance->setTrapMap();
	
	/*测试*/
	// cout<<"the warType:"<<warType<<" pkType:"<<changePkType<<endl;
	// cout<<"in the configuration_filses_map,cpp --->the mapId:"<<mapId<<endl;
		
	if(flgCpy == 0)
	{	
		/*vip包厢配置读取*/
		if(strcmp(mapId.c_str(),"map_025") == 0 || strcmp(mapId.c_str(),"map_026") == 0 ||\
		  strcmp(mapId.c_str(),"map_027") == 0 || strcmp(mapId.c_str(),"map_028") == 0)
		{
			confVipRoom[mapId] = (Map_Src*)map_instance;
		}
		
		/*帮派宴席*/
		else if(strcmp(mapId.c_str(),"map_029") == 0)
		{
			confPartyRoom[mapId] = (Map_Src*)map_instance;
		}
		/*帮派大本营*/
		else if(strcmp(mapId.c_str(),"map_030") == 0 || strcmp(mapId.c_str(),"map_031") == 0)
		{
			cout<<"campMapId:"<<mapId<<endl;
			confCampRoom[mapId] = (Map_Src*)map_instance;
		}
		
		/*普通场景*/
		else
		{
			mapId_connect_map[mapId] = (Map_Src*)map_instance;
			map_instance->initTimer();    //启动地图的计时	
		}
	}
	else 
	{			
		cpyMapConf[mapId] = (Map_Cpy*)map_instance;	
	}

	
	//读取特殊地图的ID；有疑问RTX xhm;
	switch(mapType)
	{
		case 0:
		mapTypeInfo.mainCityMapId=mapId;
			break;
		case 3:
		mapTypeInfo.guidWarMapId=mapId;		
			break;
		case 4:
		mapTypeInfo.campWarMapId=mapId;		
			break;
		case 5:
		mapTypeInfo.towerDefMapId=mapId;		
			break;
		case 6:
		mapTypeInfo.campSenceMapId=mapId;			
			break;
		case 7:
		mapTypeInfo.mainCityMapId2=mapId;			
			break;
		case 9:
		mapTypeInfo.campResWarMapId = mapId;
			break;
		default:
			break;
	}
	// cout<<"read the mapId in configurate end:"<<mapId<<endl;
	return 0;
}

