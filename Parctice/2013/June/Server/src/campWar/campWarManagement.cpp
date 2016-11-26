#include "hero.h"
#include "guild.h"
#include "map_src.h"
#include "guild_asist.h"
#include "camp_war_reward.h"
#include "campWarManagement.h"
#include "my_mem_group.h"	
#include "systemMessage.h"

#include"statuaryAsist.h"
#include"money_operator.h"

// #define CAMP_RES_WAR_TEST_VERSION

extern struct ev_loop *loops;
extern ev_timer *peaceTimer;//安全时间定时器；
extern ev_timer *CampWartimer;//作战时间定时器；
extern MyMemGroup* mem_group;	//缓存组
extern MapType_T mapTypeInfo;//某些特殊地图的ID；
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Map_Src*> mapId_connect_map;
extern int campResWarLastOpenRoomIndex;		//阵营战最后一个开启的房间
extern set<string> joinCampResWarHeroIds;		//所有参加了阵营资源战的角色Id
extern map<string, CampResWarReward_T*> campResWarRewardInfo;
static char allPre[51000];//帮派数据；
static char campWarAwards[200];//阵营奖励数据；
static char campInfo_msg[200];
static char info[1024];

campWarManagement::campWarManagement()
{
	campInfoKey="ZYa3e3e108-1c2f-11e2-a3ce-14dae9035947";
	app_info_key="PMa3e3e108-1c2f-11e2-a3ce-14dae9035947";
	
	leaderCampWar_app_info.init();
	
	for(int index=0;index < ROOM_OF_ORDINARY_CAMP_WAR;index++)
	{
		OrdCampWar[index].setIdentity(intTostring(index));
	}
	
	for(int index=0;index < ROOM_OF_LEADEER_CAMP_WAR;index++)
	{
		app_guild_size[index]=0;
		leaderCampWar[index].setIdentity(index);
	}
	
	// for (int index = 0; index < ROOM_OF_CAMP_RES_WAR; index++)
	// {
		// campResWarGroup[index].setRoomIndex(index);
	// }
	
}

void
campWarManagement::gainInfoFromMem()
{
	if(NULL == mem_group)
		return;
		
	int size=0;		
	int where = 0;
	CampInfo_T* myCampInfoMem=(CampInfo_T*)mem_group->get_data(campInfoKey, &size, &where, PUBLIC_MEMCACHED_INDEX);
	
	if(!myCampInfoMem)
	{
		cout<<"[XHM WARNING] Gain the myCampInfoMem(in the campManagement.cpp) ERROR,myCampInfoMem pointer is NULL!"<<endl;
		return;
	}else{	
		for(int index = 0; index < ROOM_OF_LEADEER_CAMP_WAR; index++)
		{
			memcpy((char*)(&(currCampInfo.leaderCampInfo[index].leaderName)),(char*)&myCampInfoMem->leaderCampInfo[index].leaderName,HERO_MAME_LEN);
			memcpy((char*)(&(currCampInfo.leaderCampInfo[index].leaderHeroId)),(char*)&myCampInfoMem->leaderCampInfo[index].leaderHeroId,HERO_ID_LEN+1);
			memcpy((char*)(&(currCampInfo.leaderCampInfo[index].viceLeaderName)),(char*)&myCampInfoMem->leaderCampInfo[index].viceLeaderName,HERO_MAME_LEN);
			memcpy((char*)(&(currCampInfo.leaderCampInfo[index].viceLeaderHeroId)),(char*)&myCampInfoMem->leaderCampInfo[index].viceLeaderHeroId,HERO_ID_LEN+1);
			memcpy((char*)(&(currCampInfo.leaderCampInfo[index].leaderBroadcast)),(char*)&myCampInfoMem->leaderCampInfo[index].leaderBroadcast,MAX_BROADCAST_LEN);
			memcpy((char*)(&(currCampInfo.leaderCampInfo[index].leaderCampWarFactionName)),(char*)&myCampInfoMem->leaderCampInfo[index].leaderCampWarFactionName,HERO_MAME_LEN);			
		}
		
		for(int index = 0; index < ORD_CAMP_WAR_TITLE_COUNTS; index++)
		{
			memcpy((char*)(&(currCampInfo.ordWarWinnerHeroId[index])),myCampInfoMem->ordWarWinnerHeroId[index],HERO_ID_LEN+1);		
		}
		
		memcpy((char*)(&(currCampInfo.chieferCampInfo.chiefer)),(char*)&myCampInfoMem->chieferCampInfo.chiefer,HERO_MAME_LEN);
		memcpy((char*)(&(currCampInfo.chieferCampInfo.chieferId)),(char*)&myCampInfoMem->chieferCampInfo.chieferId,HERO_ID_LEN+1);
		memcpy((char*)(&(currCampInfo.chieferCampInfo.chiefCampWarName)),(char*)&myCampInfoMem->chieferCampInfo.chiefCampWarName,HERO_MAME_LEN);
	
		for(int row = 0;row < ROOM_OF_LEADEER_CAMP_WAR;row++)
		{
			if(strlen(currCampInfo.leaderCampInfo[row].leaderCampWarFactionName))
				leaderCampWar[row].setWinnerFaction(currCampInfo.leaderCampInfo[row].leaderCampWarFactionName);
			if(strlen(currCampInfo.leaderCampInfo[row].leaderHeroId))
				leaderCampWar[row].setGuildLeaderAId(currCampInfo.leaderCampInfo[row].leaderHeroId);
				
			chiefCampWar.setFactionName(currCampInfo.leaderCampInfo[row].leaderCampWarFactionName,row);//往盟主战里面添加；							
		}
		
		chiefCampWar.setChampion(currCampInfo.chieferCampInfo.chiefCampWarName);
		chiefCampWar.setChiefHeroId(currCampInfo.chieferCampInfo.chieferId);		
	}	
	
	Leader_Apply_Info_T* myAppInfoMem
		= (Leader_Apply_Info_T*)mem_group->get_data(app_info_key, &size, &where, PUBLIC_MEMCACHED_INDEX);//读取统领战报名数据
	if(!myAppInfoMem)
	{
		cout<<"[XHM WARNING] Gain the myAppInfoMem(in the campManagement.cpp) ERROR,myAppInfoMem pointer is NULL"<<endl;
		return;
	}else{
		int flag=8;//位运算标记；
		for(int index = 0; index < MAX_GUILD_NAME; index++)
		{
			if((flag&1)!=1)		
			{
				if(strlen(myAppInfoMem->mizong_app_guildName[index])!=0){
					memcpy((char*)(&(leaderCampWar_app_info.mizong_app_guildName[index])),(char*)&myAppInfoMem->mizong_app_guildName[index],MAX_GUILD_NAME_LEN);
					leaderCampWar[0].applyWarFactionInfo.insert( map<string,int>::value_type(leaderCampWar_app_info.mizong_app_guildName[index],index));
					++app_guild_size[0];
				}else{
					flag |= 1;
				}
			}

			if((flag&2)!=2)		
			{			
				if(strlen(myAppInfoMem->xiejiao_app_guildName[index])!=0){		
					memcpy((char*)(&(leaderCampWar_app_info.xiejiao_app_guildName[index])),(char*)&myAppInfoMem->xiejiao_app_guildName[index],MAX_GUILD_NAME_LEN);
					leaderCampWar[1].applyWarFactionInfo.insert( map<string,int>::value_type(leaderCampWar_app_info.xiejiao_app_guildName[index],index));					
					// cout<<"myAppInfoMem->xiejiao_app_guildName[index]:"<<myAppInfoMem->xiejiao_app_guildName[index]<<"the applyWarFactionInfo.size:"<<leaderCampWar[1].applyWarFactionInfo.size()<<endl;					
					// map<string,int>::iterator curr = leaderCampWar[1].applyWarFactionInfo.begin();
					// cout<<"curr->first:"<<curr->first<<endl;
					++app_guild_size[1];
				}else{
					flag |= 2;
				}
			}
			
			if((flag&4)!=4)		
			{
				if(strlen(myAppInfoMem->youxia_app_guildName[index])!=0){			
					memcpy((char*)(&(leaderCampWar_app_info.youxia_app_guildName[index])),(char*)&myAppInfoMem->youxia_app_guildName[index],MAX_GUILD_NAME_LEN);			
					leaderCampWar[2].applyWarFactionInfo.insert( map<string,int>::value_type(leaderCampWar_app_info.youxia_app_guildName[index],index));							
					++app_guild_size[2];
				}else{
					flag |= 4;
				}
			}
			
			if(flag == 15)
				break;
		}
		//获取报名成功的帮派名字；
		memcpy((char*)(&(leaderCampWar_app_info.mizong_guildName)),(char*)&myAppInfoMem->mizong_guildName,MAX_GUILD_NAME_LEN);
		if(strlen(leaderCampWar_app_info.mizong_guildName))
		{
			leaderCampWar[0].setchallengeGuild(leaderCampWar_app_info.mizong_guildName);
		}
		memcpy((char*)(&(leaderCampWar_app_info.xiejiao_guildName)),(char*)&myAppInfoMem->xiejiao_guildName,MAX_GUILD_NAME_LEN);
		if(strlen(leaderCampWar_app_info.xiejiao_guildName))
		{
			leaderCampWar[1].setchallengeGuild(leaderCampWar_app_info.xiejiao_guildName);
		}		
		memcpy((char*)(&(leaderCampWar_app_info.youxia_guildName)),(char*)&myAppInfoMem->youxia_guildName,MAX_GUILD_NAME_LEN);	
		if(strlen(leaderCampWar_app_info.youxia_guildName))
		{
			leaderCampWar[2].setchallengeGuild(leaderCampWar_app_info.youxia_guildName);
		}		
	}
}

void
campWarManagement::showCampInfo()
{
cout<<"********currCampInfo.ordWarWinnerHeroId[0]:"<<currCampInfo.ordWarWinnerHeroId[0]<<"********"<<endl;
cout<<"********currCampInfo.ordWarWinnerHeroId[1]:"<<currCampInfo.ordWarWinnerHeroId[1]<<"********"<<endl;
cout<<"********currCampInfo.ordWarWinnerHeroId[2]:"<<currCampInfo.ordWarWinnerHeroId[2]<<"********"<<endl;
for(int row=0;row < 3;row++)
{
	cout<<"********currCampInfo.leaderCampInfo["<<row<<"].leaderHeroId:"<<currCampInfo.leaderCampInfo[row].leaderHeroId<<"********"<<endl;
	cout<<"********currCampInfo.leaderCampInfo["<<row<<"].leaderName:"<<currCampInfo.leaderCampInfo[row].leaderName<<"********"<<endl;
	cout<<"********currCampInfo.leaderCampInfo["<<row<<"].viceLeaderHeroId:"<<currCampInfo.leaderCampInfo[row].viceLeaderName<<"********"<<endl;
	cout<<"********currCampInfo.leaderCampInfo["<<row<<"].leaderHeroId:"<<currCampInfo.leaderCampInfo[row].viceLeaderHeroId<<"********"<<endl;
	cout<<"********currCampInfo.leaderCampInfo["<<row<<"].leaderBroadcast:"<<currCampInfo.leaderCampInfo[row].leaderBroadcast<<"********"<<endl;
	cout<<"********currCampInfo.leaderCampInfo["<<row<<"].leaderCampWarFactionName:"<<currCampInfo.leaderCampInfo[row].leaderCampWarFactionName<<"*"<<endl;
}
cout<<"********currCampInfo.chieferCampInfo.chieferId:"<<currCampInfo.chieferCampInfo.chieferId<<"********"<<endl<<endl<<endl<<endl;
}


void
campWarManagement::setInfo2Mem()
{
	if(NULL == mem_group)
		return;

	if(mem_group->set_data(campInfoKey,(char*)&(currCampInfo),(int)(sizeof(CampInfo_T)), PUBLIC_MEMCACHED_INDEX))
		cout<<"[XHM TEST] Save CampInfo into the mem_data(campManagement.cpp) Success!"<<endl;
	else
		cout<<"[XHM TEST] Save CampInfo into the mem_data(campManagement.cpp) ERROR!"<<endl;
	// showCampInfo();
}

void
campWarManagement::setAppInfo2Mem()
{
	if(NULL == mem_group)
		return;

	if(mem_group->set_data(app_info_key,(char*)&(leaderCampWar_app_info),(int)(sizeof(Leader_Apply_Info_T)), PUBLIC_MEMCACHED_INDEX))
		cout<<"[XHM TEST] Save setAppInfo2Mem into the mem_data(campManagement.cpp) Success!"<<endl;
	else
		cout<<"[XHM TEST] Save setAppInfo2Mem into the mem_data(campManagement.cpp) ERROR!"<<endl;
}


/**
	argument：_OrdinaryCampWarLastTime 		普通阵营战持续时间；
			  _leaderCampWarLastTime		统领争夺战持续时间；
			  _ApplyLeaderCampWarLastTime	统领战报名持续时间；
			  _ChiefCampWarLastTime			盟主争夺战持续时间；
			  _LpeaceTime					统领战和平时间；
			  _CpeaceTime					盟主争夺战和平时间；			  
	 return:  void
*/
void
campWarManagement::initCampWarInfo(time_t _OrdinaryCampWarLastTime,time_t _leaderCampWarLastTime,\
									time_t _ApplyLeaderCampWarLastTime,time_t _ChiefCampWarLastTime,time_t _LpeaceTime,time_t _CpeaceTime)
{
 	Map_Src  *warMap = NULL;	
	map<string,Map_Src*>::iterator it_map;
	
	string scene_id = mapTypeInfo.campWarMapId;
	it_map = mapId_connect_map.find(scene_id);
	
	if(it_map != mapId_connect_map.end())
	{
		warMap = it_map->second;
	
		/*复制地图*/
		for(int i=0;i<ROOM_OF_ORDINARY_CAMP_WAR+ROOM_OF_LEADEER_CAMP_WAR+ROOM_OF_CHIEF_CAMP_WAR;i++)
		{
			Map_Src *scene = warMap->copyMap(i);
			if(i >= ROOM_OF_ORDINARY_CAMP_WAR && i < ROOM_OF_ORDINARY_CAMP_WAR+ROOM_OF_LEADEER_CAMP_WAR+ROOM_OF_CHIEF_CAMP_WAR -1)
			{
				scene->setWarType(4);						
				scene->setMapType(3);
			}
			// cout<<"scene->getMapId:"<<scene->getMapId()<<endl;
			mapInfoVector.push_back(scene);
		}
		
	}
	
	scene_id = mapTypeInfo.campResWarMapId;
	// cout<<"[BisonShow BisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShow]"<<endl;
	// cout<<"[BisonShow BisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShow]"<<endl;
	cout<<"scene_id is "<<scene_id<<"campResWarMapId is "<<mapTypeInfo.campResWarMapId<<endl;
	// cout<<"[BisonShow BisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShow]"<<endl;
	// cout<<"[BisonShow BisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShowBisonShow]"<<endl;
	it_map = mapId_connect_map.find(scene_id);
	
	isInCampResWarTime = false;
	if(it_map != mapId_connect_map.end())
	{
		warMap = it_map->second;
		
		for (int j = ROOM_NUM_BEFORE_CAMP_RES_WAR; j < ROOM_NUM_BEFORE_CAMP_RES_WAR + ROOM_OF_CAMP_RES_WAR; j++)
		{
			Map_Src *scene = warMap->copyMap(j);
			mapInfoVector.push_back(scene);
			
			campResWarGroup[j - ROOM_NUM_BEFORE_CAMP_RES_WAR].create(j - ROOM_NUM_BEFORE_CAMP_RES_WAR, scene);
			
		}
	}
	
	/*设置普通阵营战类型基本属性*/
	OrdinaryCampWarLastTime=_OrdinaryCampWarLastTime;//普通阵营战持续时间；
	campResWarLastTime = _OrdinaryCampWarLastTime;
	ApplyLeaderCampWarLastTime=_ApplyLeaderCampWarLastTime;
	LeaderCampWarLastTime=_leaderCampWarLastTime;
	ChiefCampWarLastTime=_ChiefCampWarLastTime;
	Lpeace_time=_LpeaceTime;//和平时间；
	Cpeace_time=_CpeaceTime;//和平时间；
	
/* 	cout<<"[XHM TEST]	OrdinaryCampWarLastTime:"<<_OrdinaryCampWarLastTime<<endl;//普通阵营战持续时间；
	cout<<"[XHM TEST]	leaderCampWarLastTime:"<<_leaderCampWarLastTime<<endl;
	cout<<"[XHM TEST]	ApplyLeaderCampWarLastTime:"<<_ApplyLeaderCampWarLastTime<<endl;
	cout<<"[XHM TEST]	ChiefCampWarLastTime:"<<_ChiefCampWarLastTime<<endl;
	cout<<"[XHM TEST]	Lpeace_time:"<<_LpeaceTime<<endl;//和平时间；
	cout<<"[XHM TEST]	Cpeace_time:"<<_CpeaceTime<<endl;//和平时间；
 */	
	gainInfoFromMem();//获取阵营信息缓存；
	setCampInfo();//设置阵营信息
}


campWarManagement::~campWarManagement()
{


}


/**********************************************************/
/****************** 公共接口 ******************************/
/**********************************************************/
/***
argument：Hero* myHero 英雄实例指针；
return:   int   -1: myHero==NULL,对象指针为空;
				-2:	英雄实例的阵营不属于系统三个阵营之内；
				 0：在阵营tribes（正派）里面。
				 1：在阵营religion（邪派）里面。
				 2：在阵营ranger（游侠）里面。
*/
int 
campWarManagement::findCampType(Hero* myhero)
{
		if(NULL == myhero)
			return -1;
			
		if(myhero->getCamp()==0)
			return 0;
		else if(myhero->getCamp()==1)
			return 1;
		else if(myhero->getCamp()==2)
			return 2;	
		else
			return -2;
}


/***
argument myHero 英雄实例指针；
  return int -1:表示找不到返回地图实例指针；
			 -2:实例指针为空；
			  0：表示成功切换；
*/
int 
campWarManagement::exitCampWarSence(Hero* myHero)
{
	if(NULL == myHero)
		return -2;
		
	string mainSrcId = mapTypeInfo.mainCityMapId;
	map<string,Map_Src*>::iterator mainSrc_it;
	mainSrc_it = mapId_connect_map.find(mainSrcId);
	
	if(mainSrc_it == mapId_connect_map.end())
	{
		cout<<"[XHM WARNING](campWarManagement.cpp)ExitCampWarSence,mainSrcId "<<mainSrcId<<" not find!"<<endl;
		return -1;
	}
	
	Map_Inform *mapDest=mainSrc_it->second;
	Point targetPt=mapDest->getEntPt();	
	
	myHero->quit_scene();
	myHero->setMap(mainSrc_it->second);
	myHero->setMapId(mapDest->getMapId());
	myHero->setLocation(targetPt);		
	sprintf(campInfo_msg,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS, mapDest->getMapId(),targetPt._x,targetPt._y,\
													mapDest->getWarType(),mapDest->getChangePkType(),mapDest->getMapType());	
													
	send_msg(myHero->getFd(),campInfo_msg); 

	// myHero->enter_scene();//TODO 陈真说客户端响应进入地图后，再执行这个函数;
	return 0;
}


/***
argument myHero 英雄实例指针；
  return int -1:表示找不到返回地图实例指针；
			 -2:表示实例指针和地图指针为空；
			  0：表示成功切换；
*/
int 
campWarManagement::enterCampWarSence(Hero* myHero,Map_Inform *mapDest)
{
	if(myHero==NULL || mapDest == NULL)
		return -2;
		
	/*此处根据阵营不同，设置不同的目标点*/
	Point targetPt=mapDest->getCampWarPt(myHero->getCamp());
	

	// cout<<"[XHM TEST]campWarMangement.cpp enterCampWarSence mapDest->getMapId() "<<mapDest->getMapId()<<endl;;
	// cout<<" X: "<<targetPt._x<<" Y: "<<targetPt._y<<endl;
	
	
	myHero->quit_scene();
	myHero->setMap(mapDest);
	myHero->setMapId(mapDest->getMapId());
	myHero->setLocation(targetPt);		
	char mapId[20]={0};
	
	snprintf(mapId,15,"%s",mapDest->getMapId());
	
	
	
	sprintf(campInfo_msg,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,mapId,targetPt._x,targetPt._y,\
													mapDest->getWarType(),mapDest->getChangePkType(),mapDest->getMapType());
	send_msg(myHero->getFd(),campInfo_msg); 
	return 0; 	
}


/**
argument heroId 英雄实例Id；
  return int -1:表示找不到英雄实例；
			 -2:表示该英雄的阵营阵营类型错误；
			 -3:表示该英雄的阵营阵营战类型错误；
function  增加杀敌数；
*/
int 
campWarManagement::addKillsInCampWar(Hero *myHero)
{
	if(NULL == myHero)
		return -1;
		
	int ret=0;	
	CampData_T campWardata= myHero->getCampWarData();			//获取阵营数据；
	// cout<<"[XHM TEST] The campWardata.campWarType:"<<campWardata.campWarType<<endl;
	if(campWardata.campWarType==1)
	{
		ret = OrdCampWar[campWardata.campWarRoomNum].addKills(myHero);
		sprintf(campInfo_msg,"11,30,%d,%ld",ret,OrdinaryCampWarEndTime-time(NULL));
		send_msg(myHero->getFd(),campInfo_msg);
		return ret;
	}
	else if(campWardata.campWarType==2)
	{
		int index=findCampType(myHero);
		if(index < 0 ||  index >= ROOM_OF_LEADEER_CAMP_WAR)
			return -2;
		ret = leaderCampWar[index].addKills(myHero);
		return ret;
	}
	else if(campWardata.campWarType==3)
	{	
		;
	}
	else
		return -3;

}


/**
argument heroId 英雄实例Id；
  return int -1:表示找不到英雄实例；
			 -2:表示该英雄的阵营阵营类型错误；
			 -3:表示该英雄的阵营阵营战类型错误；
			 -4 帮派名字不是当前盟主战的帮派；
			 >0 死亡次数；
*/
int 
campWarManagement::addDeathInCampWar(Hero *myHero)
{
	if(NULL == myHero)
		return -1;
	int campWarType= myHero->getCampWarType();//获取阵营数据；
	
	if(campWarType==2)
	{
		int index=findCampType(myHero);
		if(index < 0 ||  index >= ROOM_OF_LEADEER_CAMP_WAR)
			return -2;
		int ret = leaderCampWar[index].addDeathCounts(myHero);
		if(CAMP_MAX_DEATHS <= ret){//达到最大死亡次数；
			myHero->setLifeVal(myHero->getLifeUpperVal());
			myHero->setMagicVal(myHero->getMagicUpperVal());
			myHero->setLifeStation(1);	
			sprintf(campInfo_msg,"11,1,%d,%d",2,0);
			send_msg(myHero->getFd(),campInfo_msg);	
			
			int revival_life=myHero->getLifeUpperVal();//复活回城
			int revival_magic=myHero->getMagicUpperVal();
			myHero->setLifeVal(revival_life);
			myHero->setMagicVal(revival_magic);	
			myHero->setLifeStation(1);
			
			sprintf(campInfo_msg,"7,0,%d,%d",revival_life,revival_magic);	
			send_msg(myHero->getFd(),campInfo_msg);
			
			exitCampWarSence(myHero);//退出场景；
		}else{
			sprintf(campInfo_msg,"11,21,%d,%lu",ret,leaderCampWar[index].LeaderCampWarEndTime-time(NULL));
			send_msg(myHero->getFd(),campInfo_msg);
		}
		return ret;	
	}
	else if(campWarType==3)
	{	
		int ret = chiefCampWar.addDeathCounts(myHero);
		if(ret >= CAMP_MAX_DEATHS){
			myHero->setLifeVal(myHero->getLifeUpperVal());
			myHero->setMagicVal(myHero->getMagicUpperVal());
			myHero->setLifeStation(1);			
			sprintf(campInfo_msg,"11,1,%d,%d",3,0);
			send_msg(myHero->getFd(),campInfo_msg);
			
			int revival_life=myHero->getLifeUpperVal();//复活回城
			int revival_magic=myHero->getMagicUpperVal();
			myHero->setLifeVal(revival_life);
			myHero->setMagicVal(revival_magic);			
			myHero->setLifeStation(1);	
			
			sprintf(campInfo_msg,"7,0,%d,%d",revival_life,revival_magic);	
			send_msg(myHero->getFd(),campInfo_msg);
			
			exitCampWarSence(myHero);//死亡5次处理出战场；
		}else{
			sprintf(campInfo_msg,"11,22,%d,%lu",ret,chiefCampWar.ChiefCampWarEndTime-time(NULL));
			send_msg(myHero->getFd(),campInfo_msg);
		}
		return ret;
	}
	else
		return -3;

}

char*
campWarManagement::get_apply_camp_war_info(int _index)
{
	if(_index > 2 || _index < 0)
		_index = 0;
		
	if(0==ApplyLeaderCampWarEndTime || ApplyLeaderCampWarEndTime < time(NULL))
	{
		sprintf(campInfo_msg,"11,28,%d,0",_index);
		return campInfo_msg;
	}
	
	return leaderCampWar[_index].viewApplyInfo();
}



/**
argument _index 英雄实例所在的阵营；
  return string 该阵营的统领所在的帮派的名字；
 	 for 史哲轩--->福利需要接口； 
*/
string 
campWarManagement::getLeaderFactionName(int _index)
{
	string guildName;
	if( _index >= ROOM_OF_LEADEER_CAMP_WAR || _index < 0)
		return guildName; 
	else 
		return currCampInfo.leaderCampInfo[_index].leaderCampWarFactionName;
}


/**
  return int 武林盟主所在的帮派的阵营类型 
	 for 史哲轩--->福利需要接口；
*/
int
campWarManagement::getCheifFactionName()
{
	Guild* guild = getGuildWithName(currCampInfo.chieferCampInfo.chiefCampWarName);
	if (guild == NULL)
	{
		return -1;
	}
	return guild->getCamp();
}


/**
	argument: void
	  return: void
	function: 将统领和副统领数据更新到campInfo变量里面；
*/
void 
campWarManagement::setCampInfo()
{
	string tempInfo;
	campInfo=charTostring(currCampInfo.chieferCampInfo.chiefer);//清空；
	
	for(int row = 0;row < ROOM_OF_LEADEER_CAMP_WAR;row++)
	{
		campInfo+=charTostring(currCampInfo.leaderCampInfo[row].leaderName);
		tempInfo+=charTostring(currCampInfo.leaderCampInfo[row].viceLeaderName); //副统领数据；
	}
	campInfo += tempInfo;
	
	setInfo2Mem();//存储缓存；
}


/**
 argument: myHero 查看阵营信息的实例指针；
   return: string 武林盟主所在的帮派的阵营类型信息；
*/
char*
campWarManagement::viewCampInfo(Hero* myHero)
{
	int appointVisible = 0;//当前是否可以任命 0不可以，1,可以任命正派 2，可以任命邪派 3，可以任命游侠;
	
	if(NULL == myHero)
		sprintf(allPre,",0,0,0,0,0,0,0,0,0");
	else{	
		char* heroName = myHero->getNickName();
		switch(myHero->getCamp())
		{
			case 0:
				if(!strcmp(heroName,currCampInfo.leaderCampInfo[0].leaderName))
						appointVisible = 1;
						
				sprintf(allPre,",%d%s,%s",appointVisible,campInfo.c_str(),currCampInfo.leaderCampInfo[0].leaderBroadcast);		
				break;
			case 1:
				if(!strcmp(heroName,currCampInfo.leaderCampInfo[1].leaderName))
					appointVisible = 2;
					
				sprintf(allPre,",%d%s,%s",appointVisible,campInfo.c_str(),currCampInfo.leaderCampInfo[1].leaderBroadcast);						
				break;
			case 2:
				if(!strcmp(heroName,currCampInfo.leaderCampInfo[2].leaderName))
					appointVisible = 3;	
					
				sprintf(allPre,",%d%s,%s",appointVisible,campInfo.c_str(),currCampInfo.leaderCampInfo[2].leaderBroadcast);		
				break;
			default:
				sprintf(allPre,",%d%s,%s",appointVisible,campInfo.c_str(),currCampInfo.leaderCampInfo[0].leaderBroadcast);					
				break;
		}

	}
	
	return allPre;	
}


/**
	argument：myHero 设置公告的英雄实例，要求是当前阵营的统领；
			  broadcastCampInfo 公告内容；
	  return: int 1 实例指针为空；
			      2 不是统领，不能设置；
				  0 设置成功；
*/
int 
campWarManagement::setCampBroadcast(Hero* myHero,char* broadcastCampInfo)
{	
	if(NULL == myHero || broadcastCampInfo==NULL)
		return 1;
		
	char* heroName = myHero->getNickName();
	int retInfo = 2;
	
	switch(myHero->getCamp())
	{
		case 0:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[0].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[0].leaderBroadcast,broadcastCampInfo,strlen(broadcastCampInfo));
				currCampInfo.leaderCampInfo[0].leaderBroadcast[strlen(broadcastCampInfo)] = '\0';
				retInfo = 0;
			}
			break;
		case 1:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[1].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[1].leaderBroadcast,broadcastCampInfo,strlen(broadcastCampInfo));
				currCampInfo.leaderCampInfo[1].leaderBroadcast[strlen(broadcastCampInfo)] = '\0';
				retInfo = 0;
			}	
			break;
		case 2:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[2].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[2].leaderBroadcast,broadcastCampInfo,strlen(broadcastCampInfo));
				currCampInfo.leaderCampInfo[2].leaderBroadcast[strlen(broadcastCampInfo)] = '\0';
				retInfo = 0;
			}
			break;
		default:
			break;
	}

	if(retInfo == 0)
		setCampInfo();
	
	return retInfo;
}


/***
	argument：myHero 设置副统领的英雄实例，要求是当前阵营的统领；
			  _viceLeaderName 被设置成副统领的角色名；
	  return: int 1 实例指针为空；
			      2 统领没有找到阵营；
				  0 设置成功；
*/
int 
campWarManagement::setViceLeaderName(Hero* myHero,string _viceLeaderName,string _viceLeaderId)
{
	if(NULL == myHero || _viceLeaderName.empty() || _viceLeaderId.empty())
		return 1;
		
	char* heroName = myHero->getNickName();
	int retType=2;//默认为2；
	
	switch(myHero->getCamp())
	{
		case 0:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[0].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[0].viceLeaderName,_viceLeaderName.c_str(),strlen(_viceLeaderName.c_str()));
				currCampInfo.leaderCampInfo[0].viceLeaderName[strlen(_viceLeaderName.c_str())] = '\0';
				retType = 0;
			}
			break;
		case 1:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[1].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[1].viceLeaderName,_viceLeaderName.c_str(),strlen(_viceLeaderName.c_str()));
				currCampInfo.leaderCampInfo[1].viceLeaderName[strlen(_viceLeaderName.c_str())] = '\0';
				retType = 0;
			}	
			break;
		case 2:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[2].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[2].viceLeaderName,_viceLeaderName.c_str(),strlen(_viceLeaderName.c_str()));
				currCampInfo.leaderCampInfo[2].viceLeaderName[strlen(_viceLeaderName.c_str())] = '\0';
				retType = 0;
			}
			break;
		default:
			break;
	}
	
	if(retType == 0)//如果设置成功，更新面板显示数据；
		setCampInfo();
	
	return retType;
}


/***
	argument：myHero 撤销副统领的英雄实例，要求是当前阵营的统领；
			  _viceLeaderName 被撤销成副统领的角色名；
	  return: int 1 实例指针为空；
			      2 统领没有找到阵营；
				  0 设置成功；
*/
int 
campWarManagement::cancelViceLeaderName(Hero* myHero,string _viceLeaderName,string _viceLeaderId)
{
	if(NULL == myHero || _viceLeaderName.empty() || _viceLeaderId.empty())
		return 1;
		
	char* heroName = myHero->getNickName();
	int retType=2;
	
	switch(myHero->getCamp())
	{
		case 0:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[0].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[0].viceLeaderName,"0",strlen("0"));//撤销默认为-1，客户端显示为无；
				currCampInfo.leaderCampInfo[0].viceLeaderName[strlen("0")] = '\0';
				retType = 0;
			}
			break;
		case 1:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[1].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[1].viceLeaderName,"0",strlen("0"));
				currCampInfo.leaderCampInfo[1].viceLeaderName[strlen("0")] = '\0';
				retType = 0;
			}	
			break;
		case 2:
			if(!strcmp(heroName,currCampInfo.leaderCampInfo[2].leaderName))
			{
				memcpy(currCampInfo.leaderCampInfo[2].viceLeaderName,"0",strlen("0"));
				currCampInfo.leaderCampInfo[2].viceLeaderName[strlen("0")] = '\0';
				retType = 0;
			}
			break;
		default:
			break;
	}
	
	if(retType == 0)//设置成功，更新面板数据；
		setCampInfo();
		
	return retType;
}


/**
argument: myHero 查看阵营信息的实例指针；
  return: string 所在阵营的帮派列表信息；
*/	
char*  
campWarManagement::viewCampFactionInfo(Hero* myHero)
{	
	sprintf(allPre,",0");
	if(NULL == myHero)
		return allPre;

	int camp = myHero->getCamp();/*调用帮派管理下的帮派数据，参数是阵营的编号；*/
	switch(camp)			
	{
		case 0:
			viewAllPresidInCamp(0, allPre);
			break;
		
		case 1:
			viewAllPresidInCamp(1, allPre);
			break;
			
		case 2:
			viewAllPresidInCamp(2, allPre);
			break;
		default:
			viewAllPresidInCamp(0, allPre);
			break;
	}
	return allPre;	
}


/**
	argument：void
	  return: 是武神，不是武神；
*/			
bool campWarManagement::isFukatsu(Hero* myHero)
{
	if(myHero == NULL)
		return false;
	
	if(strstr(currCampInfo.ordWarWinnerHeroId[0],myHero->getIdentity()))
		return true;
	// else	
	// cout<<"[XHM TEST] Curr currCampInfo.ordWarWinnerHeroId[0]:"<<currCampInfo.ordWarWinnerHeroId[0]<<endl;		
	return false;
}
	
/**
	argument：void
		 return: 是武圣，不是武圣；
*/			
bool campWarManagement::isTakefu(Hero* myHero)
{
	if(myHero == NULL)
		return false;
	
	if(strstr(currCampInfo.ordWarWinnerHeroId[1],myHero->getIdentity()))
		return true;
	// else	
	// cout<<"[XHM TEST] Curr currCampInfo.ordWarWinnerHeroId[1]:"<<currCampInfo.ordWarWinnerHeroId[1]<<endl;
	
	return false;

}

	
/**
	argument：void
		 return: 是武尊，不是武尊；
*/			
bool campWarManagement::isTakeru(Hero* myHero)
{
	if(myHero == NULL)
		return false;
	
	if(strstr(currCampInfo.ordWarWinnerHeroId[2],myHero->getIdentity()))
		return true;
	// else	
	// cout<<"[XHM MSG] Curr currCampInfo.ordWarWinnerHeroId[2]:"<<currCampInfo.ordWarWinnerHeroId[2]<<endl;
	return false;
}

	
/**
	argument：_camp 当前查询的角色阵营；
		 return: 是该阵营统领，不是该阵营统领；
*/		
bool campWarManagement::isCampLeader(Hero* myHero,int _camp)
{
	if(NULL == myHero || _camp < 0 || _camp > 2)
		return false;
		
	if(strstr(currCampInfo.leaderCampInfo[_camp].leaderHeroId,myHero->getIdentity()))
		return true;
	// else	
	// cout<<"[XHM MSG] currCampInfo.leaderCampInfo["<<_camp<<"].leaderHeroId:"<<currCampInfo.leaderCampInfo[_camp].leaderHeroId<<endl;		
	return false;	

}

	
/**
	argument：void
	  return: 是武林盟主，不是武林盟主；
*/			
bool campWarManagement::isCampChief(Hero* myHero)
{
	if(NULL == myHero)
		return false;
		
	if(strstr(currCampInfo.chieferCampInfo.chieferId,myHero->getIdentity()))
		return true;
	// else	
	// cout<<"[XHM TEST] Curr currCampInfo.chieferCampInfo.chieferId:"<<currCampInfo.chieferCampInfo.chieferId<<endl;		
	return false;	

}

/**
	argument Hero* myHero
		 return: void
*/
void 
campWarManagement::initCampTitle(Hero* myHero)
{
	if(NULL == myHero)
		return;
	
	char *heroId = myHero->getIdentity();
	
	if(strstr(currCampInfo.chieferCampInfo.chieferId,heroId))//盟主
	{
		myHero->addTitle(CAMP_CHIEF_TITLE);
	}else{
		myHero->cutTitle(CAMP_CHIEF_TITLE);	
	}	
	
	if(strstr(currCampInfo.ordWarWinnerHeroId[0],heroId))//武神
	{
		myHero->addTitle(FIRST_TITLE);
	}else{
		myHero->cutTitle(FIRST_TITLE);	
	}
	
	if(strstr(currCampInfo.ordWarWinnerHeroId[1],heroId))//武圣
	{
		myHero->addTitle(SECOND_TITLE);
	}else{
		myHero->cutTitle(SECOND_TITLE);	
	}

	if(strstr(currCampInfo.ordWarWinnerHeroId[2],heroId))//武尊
	{
		myHero->addTitle(THIRD_TITLE);
	}else{
		myHero->cutTitle(THIRD_TITLE);	
	}
	

	int camp = myHero->getCamp();
	if(camp < 0 || camp > 2)
		return;
		
	if(strstr(currCampInfo.leaderCampInfo[camp].leaderHeroId,myHero->getIdentity()))//武林盟主
	{
		myHero->addTitle(CAMP_LEADER_TITLE);
	}else{
		myHero->cutTitle(CAMP_LEADER_TITLE);	
	}

}



/**
	更新统领信息；
*/	
bool campWarManagement::updateLeaderInfo(Hero* myHero)
{
	if(myHero == NULL)
		return false;
		
	int camp = myHero->getCamp();
	if(camp < 0 || camp >= ROOM_OF_LEADEER_CAMP_WAR)
		return false;
	
	if(!strcmp(currCampInfo.leaderCampInfo[camp].leaderHeroId,myHero->getIdentity()))
	{
		setCampInfo();
		memcpy(currCampInfo.leaderCampInfo[camp].leaderName,myHero->getNickName(),HERO_MAME_LEN);
		return true;
	}
	else if(!strcmp(currCampInfo.leaderCampInfo[camp].viceLeaderHeroId,myHero->getIdentity()))
	{
		setCampInfo();
		memcpy(currCampInfo.leaderCampInfo[camp].viceLeaderName,myHero->getNickName(),HERO_MAME_LEN);
		return true;
	}else if(!strcmp(currCampInfo.chieferCampInfo.chieferId,myHero->getIdentity()))
	{
		setCampInfo();
		memcpy(currCampInfo.chieferCampInfo.chiefer,myHero->getNickName(),HERO_MAME_LEN);	
		return true;
	}else{
		return false;
	}

}

/**********************************************************/
/******************** 普通阵营战接口 **********************/
/**********************************************************/

/**
	定时函数回调接口；
*/
void 
campWarManagementFinishCall(struct ev_loop *loop,ev_timer *think,int revents)  
{
	if(think == NULL)
		return;
		
    ev_timer_stop(loop,think);								//停止计时器；
	campWarManagement *ordinaryCampWar = (campWarManagement *)think->target;
	
	if(ordinaryCampWar == NULL)
	{
		return;
	}	
	
	ordinaryCampWar->finishOrdinaryCampWar();
}


/**
	argument void
	  return bool 初始化成功 true;
						失败 false;
	初始化所有的普通阵营战数据；
*/
bool
campWarManagement::initOrdinaryCampWar()			
{
	bool ret = true;
	
	OrdinaryCampWarRank.clear();//清空排名容器；
	map<string,int>().swap(OrdinaryCampWarRank);
	
	droppedHeroInfo.clear();//清空下线角色容器；
	map<string,CampData_T>().swap(droppedHeroInfo);
	
	for(int index=0;index<ROOM_OF_ORDINARY_CAMP_WAR;index++)
		ret |= OrdCampWar[index].initCampWar();
		
	return ret;
}

/**
argument  _startTime 普通阵营战开始时间；
 return   bool true 触发成功；
			   false 触发失败，正在进行普通阵营战，不能再触发；
*/
bool 
campWarManagement::startOrdinaryCampWar(time_t _startTime)	//开启相应等级的普通阵营战；
{
		OrdinaryCampWarStartTime=_startTime;//设定初始值
		OrdinaryCampWarEndTime=_startTime+OrdinaryCampWarLastTime;
		initOrdinaryCampWar();
	
		if(NULL == CampWartimer)//启动计时器
			CampWartimer = new ev_timer;
		
		ext_ev_timer_init(CampWartimer,campWarManagementFinishCall,OrdinaryCampWarLastTime,0,this);
		ev_timer_start(loops,CampWartimer);
		
		cout<<"[XHM TEST] startOrdinaryCampWar,Start time:"<<OrdinaryCampWarStartTime<<" End time:"<<OrdinaryCampWarEndTime<<endl;
		return true;
}


/**
	sort比较函数；
*/
static int 
ordinaryCampWarCmp(const ORD_CAMP_WAR_DATA_PAIR& x, const ORD_CAMP_WAR_DATA_PAIR& y)  
{  
	  if(x.second.kills > y.second.kills)
	  {
		return 1;
	  }else if(x.second.kills == y.second.kills && x.second.lastKillTime <= y.second.lastKillTime)
	  {
		return 1;
	  }else{ 
		return 0;
	  }
}


/**
	argument void
	  return bool true 成功；
				  false 失败；
		普通阵营战结束处理；
*/
bool 
campWarManagement::finishOrdinaryCampWar()	
{
	vector<ORD_CAMP_WAR_DATA_PAIR> winner; //每个房间的前9名，用于排序；
	map<string, Hero*>::iterator iter;
	
	for(int index=0;index<ROOM_OF_ORDINARY_CAMP_WAR;index++)//每个房间处理；
	{
		map<string,KillsInfo> currentWinner = OrdCampWar[index].finishCampWar();
		for(map<string,KillsInfo>::iterator curr = currentWinner.begin();curr != currentWinner.end(); ++curr)
		{
			winner.push_back(make_pair(curr->first, curr->second));  
		}
	}
	
	sort(winner.begin(),winner.end(), ordinaryCampWarCmp);//排序；
	
	OrdinaryCampWarRank.clear();
	map<string,int>().swap(OrdinaryCampWarRank);
	
	int size=winner.size();
	
	for(int i=0;i<size;i++)//把排名和英雄id加入到容器中；
	{
		OrdinaryCampWarRank.insert(HeroId_Rank(winner[i].first,i));
		if(i==0)
		{
			//武神
			if(!strstr(currCampInfo.ordWarWinnerHeroId[0],(winner[i].first).c_str()))
			{
				if(strlen(currCampInfo.ordWarWinnerHeroId[0]))
				{
					iter=heroId_to_pHero.find(currCampInfo.ordWarWinnerHeroId[0]);//取消头衔
					if(iter != heroId_to_pHero.end())
					{
						// cout<<"[XHM MSG] (in the campWarManagement.cpp ) The title is over time,Will cut:"<<FIRST_TITLE<<endl;
						iter->second->cutTitle(FIRST_TITLE);
					}//如果下线，上线会检测；
				}
				memcpy(currCampInfo.ordWarWinnerHeroId[0],winner[i].first.c_str(),strlen(winner[i].first.c_str()));
			}
			
			//武神全服广播 jolly add
			Hero *hero=heroid_to_hero(winner[i].first);
			if (hero!=NULL)
			{					
				snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d",7,SYSTEM_WARN,"xf009",2,7,hero->getCamp(),0,0,0,1,hero->getNickName(),hero->getIdentity(),0,0);
				map<string, Hero*>::iterator it_hero;

				for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
				{
					if (it_hero->second!=NULL)
					{						
						send_msg(it_hero->second->getFd(),info);
					}
				}
			}			
		}
		else if(i==1)     
		{	
			//武圣
			if(!strstr(currCampInfo.ordWarWinnerHeroId[1],(winner[i].first).c_str()))
			{
				if(strlen(currCampInfo.ordWarWinnerHeroId[1]))
				{
					iter=heroId_to_pHero.find(currCampInfo.ordWarWinnerHeroId[1]);//取消头衔
					if(iter != heroId_to_pHero.end() )
					{		
						// cout<<"[XHM MSG] (in the campWarManagement.cpp )The title is over time,Will cut:"<<SECOND_TITLE<<endl;
						iter->second->cutTitle(SECOND_TITLE);				
					}else{
						;
					}	
				}
				memcpy(currCampInfo.ordWarWinnerHeroId[1],winner[i].first.c_str(),strlen(winner[i].first.c_str()));
			}
			
			//武圣全服广播 jolly add
			Hero *hero=heroid_to_hero(winner[i].first);
			if (hero!=NULL)
			{				
				snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d",7,SYSTEM_WARN,"xf010",2,7,hero->getCamp(),0,0,0,1,hero->getNickName(),hero->getIdentity(),0,0);
				map<string, Hero*>::iterator it_hero;

				for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
				{
					if (it_hero->second!=NULL)
					{						
						send_msg(it_hero->second->getFd(),info);
					}
				}
			}
		}
		else if(i==2)
		{
			
			if(!strstr(currCampInfo.ordWarWinnerHeroId[2],(winner[i].first).c_str()))
			{
				if(strlen(currCampInfo.ordWarWinnerHeroId[2]))
				{
					iter=heroId_to_pHero.find(currCampInfo.ordWarWinnerHeroId[2]);//取消头衔
					if(iter != heroId_to_pHero.end() )
					{
						// cout<<"[XHM MSG] (in the campWarManagement.cpp ) The title is over time,Will cut:"<<THIRD_TITLE<<endl;
						iter->second->cutTitle(THIRD_TITLE);			
					}else{
						;
					}
				}					
				memcpy(currCampInfo.ordWarWinnerHeroId[2],winner[i].first.c_str(),strlen(winner[i].first.c_str()));
			}
			
			//武尊全服广播 jolly add
			Hero *hero=heroid_to_hero(winner[i].first);
			if (hero!=NULL)
			{			
				snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d",7,SYSTEM_WARN,"xf011",2,7,hero->getCamp(),0,0,0,1,hero->getNickName(),hero->getIdentity(),0,0);
				map<string, Hero*>::iterator it_hero;

				for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
				{
					if (it_hero->second!=NULL)
					{						
						send_msg(it_hero->second->getFd(),info);
					}
				}
			}			
		}
		
		// cout<<"[XHM MSG]:"<<i<<": "<<winner[i].first<<" kills:"<<winner[i].second.kills<<endl;
	}
	
	setInfo2Mem();//存储到缓存
	
	return true;
}




/***
	argument void
	  return int 普通阵营战剩余的秒数；
*/
int 
campWarManagement::getOrdinaryCampWarOverTime()//普通阵营战剩余时间 返回值：秒数
{
	return OrdinaryCampWarEndTime-time(NULL);
}



/***
	argument void
	  return string 普通阵营战房间的人数字符串表示形式，中间用逗号隔开；
*/
string
campWarManagement::getOrdinaryCampWarStatus()
{
	string desString;
	
	for(int index=0;index<ROOM_OF_ORDINARY_CAMP_WAR;index++)
	{
		desString +=intTostring(OrdCampWar[index].getTribesSize())+\
           intTostring(OrdCampWar[index].getReligionSize())+intTostring(OrdCampWar[index].getRangerSize());
	}
	return desString;
}

/**
 *查看资源战房间信息失败原因：
	1：不在阵营资源战时间
	2：玩家还未加入阵营
	3：玩家等级小于30级
 */
int campWarManagement::getCampResWarStatus(Hero* hero, char *result)
{
#if defined(CAMP_RES_WAR_TEST_VERSION)	
	if (isInCampResWarTime == false)
	{
		// isInCampResWarTime = true;
		// campResWarGroup[0].open();
		// campResWarLastOpenRoomIndex = 0;
		setInCampResWarTime(true);
	}
#endif
	if (!isInCampResWarTime)
	{
		return 1;
	}
	
	if (hero->getCamp() == -1)
	{
		return 2;
	}
	
	if (hero->getLevel() < 30)
	{
		return 3;
	}
	
	for (int index = 0; index < ROOM_OF_CAMP_RES_WAR; index++)
	{
		cout<<"Show view index is "<<index<<" timeState is "<<campResWarGroup[index].getTimeState()<<endl;
		sprintf(result + strlen(result), ",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", campResWarGroup[index].getRoomIndex(),
			campResWarGroup[index].getTimeState(), campResWarGroup[index].getRoomState(), campResWarGroup[index].getJoinNum(3),
			campResWarCtl.roomLimitHeros,campResWarGroup[index].getJoinNum(0), campResWarCtl.perCampLimitHeros,
			campResWarGroup[index].getJoinNum(1), campResWarCtl.perCampLimitHeros, campResWarGroup[index].getJoinNum(2),
			campResWarCtl.perCampLimitHeros);
	}
	return 0;
}


/***
argument:	string heroId,英雄Id；
return:  	int	-1:该英雄id不存在；
				-2:表示阵营战已饱和，达到最大允许人数；
				-3:表示插入insert失败；
				-4:英雄实例的阵营不属于系统三个阵营之内；
				-5:英雄ID等级小于30级；
				-6:表示该阵营战人数已满或者未激活；
				-7:阵营战偏移量选择房间数不在系统默认范围内或者参数heroId为空；
				-8:地图信息找不到；
				-9:删除时，在此次阵营战中，在其阵营队列中找不到；
			   -10:表示加入的时间不在活动的时间；
				 0:表示加入成功；		 
*/
int 
campWarManagement::add2OrdinaryCampWar(string heroId,int index)//添加heroId到相应的普通阵营战；
{
	int historyKills=0;
	
	if(index < 0 || index >= ROOM_OF_ORDINARY_CAMP_WAR || heroId.empty())
		return -7;
		
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())	//该英雄id不存在；
		return -1;
		
	Hero *myHero=iter->second;
	
	if(droppedEnt(myHero)<0) //检测是不是 掉线进入；
		return -1;
	
	if(myHero->getGradeNow()<LOW_ENTER_CAMP_WAR_LEVEL)
		return -5;
		

	CampData_T myCampData = myHero->getCampWarData();//判断是否曾参加过阵营战，如果参加，得到杀敌数便于累加，然后从相应的房间删除；
	if(myCampData.campWarType==1)
	{
		if(myCampData.campWarRoomNum>=0 && myCampData.campWarRoomNum < ROOM_OF_ORDINARY_CAMP_WAR)
		{
		    historyKills=OrdCampWar[myCampData.campWarRoomNum].getKills(myHero);
			if(historyKills<0)
				historyKills=0;
		    int ret =OrdCampWar[myCampData.campWarRoomNum].delHeroFromWar(myHero);
			if(ret<0)
				return ret;
		}	
	}else{
		if(!myHero->addActivityCounts(1,1))	//给相应的参加阵营战1加入次数；
			cout<<"[XHM WARNING] (in the campWarManagement.cpp) Add ordCampWarActivity counts Error!"<<endl;
	}

	time_t currTime = time(NULL);	//判断是否是在指定时间内报名
	if(currTime<OrdinaryCampWarStartTime || currTime>=OrdinaryCampWarEndTime )
	{
		return -10;
	}

	if(mapInfoVector.size() <= index)
		return -11;
		
	Map_Inform *mapDest=mapInfoVector[index];
	
	// for(int row = 0; row < mapInfoVector.size();row++)
	// {
		// cout<<"mapInfoVector[row]->getMapId():"<<mapInfoVector[row]->getMapId()<<endl;
	// }
	// cout<<"[XHM MSG] ************mapDest->mapId:"<<mapDest->getMapId()<<endl;
	// cout<<"[XHM MSG] ************index:"<<index<<endl;	
	if(NULL == mapDest)
		return -8;
			
	int ret = OrdCampWar[index].addHero2war(myHero,historyKills);
	if(ret < 0)
		return ret;


	//消耗一定的个人游戏币；
	//jolly add wulintarget 12.4 start
	myHero->updataSingleTarget(2,9);
	//jolly add wulintarget 12.4 end

	myHero->setCampWarData(1,index,true,false);	//设置当前角色阵营战数据；
	
	ret = enterCampWarSence(myHero,mapDest);
	if(ret == 0)
	{
		sprintf(campInfo_msg,"11,30,%d,%ld",ret,OrdinaryCampWarEndTime-time(NULL));
		send_msg(myHero->getFd(),campInfo_msg);
		OrdCampWar[index].update_ord_camp_info();
	}
	
	return ret;
}


/***
argument:	heroId,英雄Id；
			index ,房间数据
  return:  	int -1:没有加入阵营；
				-2:没有加入到普通阵营战；
				-3:该英雄id不存在；
				-4:英雄ID等级小于30级；	
				-5:参数退出的index不在默认的房间号内；
				-6:参数heroId为空；
				 0:表示删除表示成功；		  
*/
int 
campWarManagement::exitFromOrdinayCampWar(string heroId,int index,int _droppedFlg)
{
	if(index<0 || index  >= ROOM_OF_ORDINARY_CAMP_WAR)
		return -5;
		
	if(heroId.empty())
		return -6;
	
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())	//该英雄id不存在；
		return -3;
		
	Hero *myHero=iter->second;
	
	int level=myHero->getGradeNow();
	if(level<LOW_ENTER_CAMP_WAR_LEVEL)
		return -4;
		
	int ret = exitCampWarSence(myHero);
	if(ret < 0)	
		return ret;	
		
	if(_droppedFlg)
		droppedHeroInfo.insert(map<string,CampData_T>::value_type((heroId),(myHero->getCampWarData())));//普通阵营战中角色下线容器；
	ret =OrdCampWar[index].reduceActiveHero(myHero);	
	if(ret == 0)
		OrdCampWar[index].update_ord_camp_info();
		
	return ret;
}


/***
argument:	myHero,英雄实例；
			index，当前查看的参见阵营战的房间号；
  return:  	string retValue(type,int,int,string)
			type:阵营战类型；
			int:金钱;
			int:声望;
			string：物品奖励ID；
			int:0无头衔，1武神，2武圣，3武尊
*/
void 
campWarManagement::viewOrdinaryCampWarAwards(Hero* myHero,int index)//查看奖励设置；
{
	if(NULL == myHero)
	{
		cout<<"[XHM WARNING] viewOrdinaryCampWarAwards NULL == myHero ERROR(campWarManagement.cpp)!"<<endl;
		return;
	}
	
	if(index<0 && index  >= ROOM_OF_ORDINARY_CAMP_WAR)
	{
		cout<<"[XHM WARNING] viewOrdinaryCampWarAwards index<0 && index  >= ROOM_OF_ORDINARY_CAMP_WAR ERROR(campWarManagement.cpp)!"<<endl;
		return;
	}
	
	int rank=-1;//此次阵营战的排名；
	map<string,int>::iterator iter = OrdinaryCampWarRank.find(myHero->getIdentity());
	if(iter!=OrdinaryCampWarRank.end())
		rank=iter->second;

	send_msg(myHero->getFd(),OrdCampWar[index].viewAwards(myHero,rank));
}


/***
argument:	myHero,英雄实例；
			index，当前查看的参见阵营战的房间号；
  return：  int -1 实例英雄指针为空
			    -2 不属于系统默认阵营类型；
				-3 在此房间没有找到英雄战斗痕迹；
				-4 给背包装东西失败；
				-5 读取参加过的阵营房间号错误，不在系统默认范围；
				 0 表示成功；
*/
int 
campWarManagement::receiveOrdinaryCampWarAwards(Hero* myHero,int index)	//领取奖励；
{
	if(NULL == myHero)
		return -1;
		
	if(index<0 && index >= ROOM_OF_ORDINARY_CAMP_WAR)
		return -5;
		
	int rank=ORDINARY_CAMP_WAR_AWARDS_LOWEST_RANGE*5;
	map<string,int>::iterator iter = OrdinaryCampWarRank.find(myHero->getIdentity());
	if(iter!=OrdinaryCampWarRank.end())
		rank=iter->second;
		
	int ret = OrdCampWar[index].receiveAwards(myHero,rank);
	if(ret != -4 && strstr(myHero->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		exitCampWarSence(myHero);	
	
	myHero->setCampWarData(-1,-1,false,true);	
	return ret;
}


/**
	argument:	string heroId角色英雄ID；
	return：  	int 0是掉线进入，数据恢复成功；
					1不是掉线进入；	
	function:   掉线重新进入处理；
*/	
int 
campWarManagement::droppedEnt(Hero* myHero)
{
	if(NULL == myHero)
		return -1;
		
	map<string,CampData_T>::iterator iter = droppedHeroInfo.find(myHero->getIdentity());
	if(iter != droppedHeroInfo.end())
	{
		myHero->setCampWarData(iter->second.campWarType,iter->second.campWarRoomNum,iter->second.campWarStartMark,iter->second.CampWarFinishMark);
		droppedHeroInfo.erase(iter);
		return 0;
	}
	return 1;
}



/**********************************************************/
/******************** 统领阵营战接口 **********************/
/**********************************************************/
void 
startLeaderCampWarPKCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
		
    ev_timer_stop(loop,think);
	
	campWarManagement *leaderCampWarStart = (campWarManagement *)think->target;
	if(NULL == leaderCampWarStart)
	{
		return;
	}
	
	leaderCampWarStart->startLeaderCampWarPK();//开启pk模式；
}


bool 
campWarManagement::startLeaderCampWarPK()
{
	bool ret=true;
	for(int index=0;index<ROOM_OF_LEADEER_CAMP_WAR;index++)
	{
		ret |= leaderCampWar[index].sendMsgStart(LeaderCampWarLastTime);
	}	
	
	Lpeace_time_start=0;//和平时间初始化为零；
	Lpeace_time_end=0;
	
	return ret;
}

/**
	argument void
	return time_t 当前和平剩余时间。
*/
time_t 
campWarManagement::LeaderCampWarPeaceTime()//和平剩余时间
{
	return Lpeace_time_end - time(NULL);
}

bool 
campWarManagement::finishLeaderCampWar(string factionName,int index)
{
	char* presidNick;
	char* heroId;
	Guild *guild=NULL;
	
	// cout<<"[XHM MSG] FinishLeaderCampWar win FactionName:"<<factionName<<endl;
		
	if(!factionName.empty())
	{
		if(strlen(currCampInfo.leaderCampInfo[index].leaderCampWarFactionName))
		{
			guild = getGuildWithName(currCampInfo.leaderCampInfo[index].leaderCampWarFactionName);
				if (guild != NULL)
				{
					guild->setCampTitle(1, 1);
				}
		}
			
		chiefCampWar.setFactionName(factionName,index);	//往盟主战里面添加；		
		memcpy(currCampInfo.leaderCampInfo[index].leaderCampWarFactionName,factionName.c_str(),strlen(factionName.c_str())); //帮派名字；
		currCampInfo.leaderCampInfo[index].leaderCampWarFactionName[strlen(factionName.c_str())] = '\0';
			
		if(strlen(currCampInfo.leaderCampInfo[index].leaderCampWarFactionName))
		{
			guild = getGuildWithName(currCampInfo.leaderCampInfo[index].leaderCampWarFactionName);
			if (guild != NULL)
			{
				guild->setCampTitle(1, 0);
			}
		}			
			// cout<<"[XHM MSG] currCampInfo.leaderCampInfo[index].leaderCampWarFactionName:"<<currCampInfo.leaderCampInfo[index].leaderCampWarFactionName<<endl;
		
		heroId = getGuildPresidId(const_cast<char*>(factionName.c_str())) ;//获取帮派帮主的ID；	
		if(heroId)
		{	
			//阵营统领全服广播 jolly add	
			char info[1024]={'\0'};				
			Hero *hero=heroid_to_hero(heroId);
			if (hero!=NULL)
			{					
				snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d",7,SYSTEM_WARN,"xf008",2,7,hero->getCamp(),0,0,0,1,hero->getNickName(),hero->getIdentity(),0,0);
				map<string, Hero*>::iterator it_hero;

				for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
				{
					if (it_hero->second!=NULL)
					{						
						send_msg(it_hero->second->getFd(),info);
					}
				}
			}
				
			//取消头衔		
			if(!strstr(currCampInfo.leaderCampInfo[index].leaderHeroId,heroId))
			{
				if(strlen(currCampInfo.leaderCampInfo[index].leaderHeroId))
				{
					map<string, Hero*>::iterator iter =heroId_to_pHero.find(currCampInfo.leaderCampInfo[index].leaderHeroId);//取消头衔
					if(iter != heroId_to_pHero.end())
					{
						// cout<<"[XHM MSG] The title over time,I Will Cut:"<<CAMP_LEADER_TITLE<<endl;
						iter->second->cutTitle(CAMP_LEADER_TITLE);
#if 0						
						/*摧毁塑像,add chenzhen 201303081311*/
						string titleStr = "SH_";
						titleStr += CAMP_LEADER_TITLE;
						destoryStatuary(const_cast<char*>((titleStr).c_str()));
#endif
						
					}else{
							;
					}
				}
#if 0				
				//chenzhen TODO 塑建阵营统领雕像
				//统领ID heroId 阵营index(0密宗 1邪教 2游侠 其他错误) 头衔ID CAMP_LEADER_TITLE
				
				string titleStr = "SH_";
				titleStr += CAMP_LEADER_TITLE;
				setUpStatuary(heroId,const_cast<char*>((titleStr).c_str()));
#endif				
				memcpy(currCampInfo.leaderCampInfo[index].leaderHeroId,heroId,strlen(heroId));
				currCampInfo.leaderCampInfo[index].leaderHeroId[strlen(heroId)] = '\0';		
					// cout<<"[XHM MSG] memcpy(currCampInfo.leaderCampInfo[index].leaderHeroId:"<<currCampInfo.leaderCampInfo[index].leaderHeroId<<endl;
				
				heroId=getGuildVicePresidId(const_cast<char*>(factionName.c_str()));//获取帮派副帮主的ID；
				if(heroId)
				{			
					memcpy(currCampInfo.leaderCampInfo[index].viceLeaderHeroId,heroId,strlen(heroId));
					currCampInfo.leaderCampInfo[index].viceLeaderHeroId[strlen(heroId)] = '\0';		
						// cout<<"currCampInfo.leaderCampInfo[index].viceLeaderHeroId:"<<currCampInfo.leaderCampInfo[index].viceLeaderHeroId<<endl;
				}				
				presidNick=viewGuildPresidNick(0,const_cast<char*>(factionName.c_str()));//获取帮主昵称；
			
				if(presidNick)
				{
					memcpy(currCampInfo.leaderCampInfo[index].leaderName,presidNick,strlen(presidNick));
					currCampInfo.leaderCampInfo[index].leaderName[strlen(presidNick)] = '\0';
					//cout<<"memcpy(currCampInfo.leaderCampInfo[index].leaderName:"<<currCampInfo.leaderCampInfo[index].leaderName<<endl;			
				}
		
				presidNick=viewGuildPresidNick(1,const_cast<char*>(factionName.c_str()));//获取副帮主昵称；
		
				if(presidNick)
				{
					memcpy(currCampInfo.leaderCampInfo[index].viceLeaderName,presidNick,strlen(presidNick));
					currCampInfo.leaderCampInfo[index].viceLeaderName[strlen(presidNick)] = '\0';
					// cout<<"currCampInfo.leaderCampInfo[index].viceLeaderName:"<<currCampInfo.leaderCampInfo[index].viceLeaderName<<endl;				
				}				
		
				setCampInfo();//更新阵营信息；				
			}
		}

	}		
	
}


/**
argument hero 英雄实例指针；
  return int -1：实例指针为空；
			 -2：表示实例指针对应对象的帮派名字不是当前作战的帮派名字；
			 -3：表示insert失败，已经参加过，不能参加；
			 -4: 表示阵营类型不是系统默认类型；
			 -5: 表示找不到地图；
			 -6: 表示时间不是最站时间；
			  0：表示成功；			  
*/
int 
campWarManagement::add2LeaderCampWar(string heroId)
{
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())//该英雄id不存在；
		return -1;	
	Hero *myHero=iter->second;
	
	int index=findCampType(myHero);
	if(index < 0)
		return -4;
	if(index+ROOM_OF_ORDINARY_CAMP_WAR >= mapInfoVector.size()){//protected by benliao
		return -5;
	}
	
	Map_Inform *mapDest=mapInfoVector[index+ROOM_OF_ORDINARY_CAMP_WAR];
	if(NULL == mapDest)
		return -5;
		
	time_t currTime =time(NULL);// 判断是否是在指定时间内报名
	// cout<<"[XHM TEST] The add2LeaderCampWar currTime:"<<currTime<<"start time:"<<LeaderCampWarStartTime<<"end time:"<<LeaderCampWarEndTime<<endl;
	if(currTime < Lpeace_time_start || currTime >= Lpeace_time_end )
		return -6;	
	
	int ret =leaderCampWar[index].addHero2Factionwar(myHero);
	if(ret < 0)
		return ret;
	
	myHero->setCampWarData(2,index,false,false);
	
	if(!myHero->addActivityCounts(2,1))	//给相应的参加阵营战2加入次数；
		cout<<"[XHM WARNING] Add LeaderCampWarActivity counts Error(campWarManagement.cpp)!"<<endl;
	
	//消耗一定的个人游戏币；
	/*此处根据阵营不同，设置不同的目标点*/
	Point targetPt=mapDest->getCampWarPt(ret);
	/*use for test*/
	
		cout<<"[XHM TEST] campWarMangement.cpp enterCampWarSence the campWarType: "<<myHero->getCamp()<<endl;

		cout<<" X: "<<targetPt._x<<" Y: "<<targetPt._y<<endl;
	
	myHero->quit_scene();
	myHero->setMap(mapDest);
	
	char mapId[20]={0};
	char* PmapId=mapDest->getMapId();
	
	cout<<"[XHM TEST] PmapId: "<<PmapId<<endl;
	
	char* Pchar = strrchr(PmapId,'_');//获取最后一个出现字符串的位置；
	int size = Pchar-PmapId;
	if(size > 19)
		size = 19;
	memcpy(mapId,PmapId,size);
	
	cout<<"[XHM TEST] Pchar: "<<Pchar<<endl;;		
	cout<<"[XHM TEST] mapId: "<<mapId<<endl;
	
	sprintf(campInfo_msg,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,mapId,targetPt._x,targetPt._y,\
													mapDest->getWarType(),mapDest->getChangePkType(),mapDest->getMapType());
													
	cout<<"[XHM TEST] campInfo_msg: "<<campInfo_msg<<endl;													
													
	send_msg(myHero->getFd(),campInfo_msg); 
	myHero->setLocation(targetPt);	
	return 0;
}


int 
campWarManagement::exitFromLeaderCampWar(string heroId)
{
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())//该英雄id不存在；
		return -1;	
		
	Hero *myHero=iter->second;
	
	int index=findCampType(myHero);
	if(index < 0)
		return -4;
		
	int ret=exitCampWarSence(myHero);	//退出场景
	
	if(ret < 0)
		return ret;
	
	return leaderCampWar[index].reduceActiveHero(myHero);
}


bool 
campWarManagement::initLeaderCampWar()
{
	for(int index=0;index<ROOM_OF_LEADEER_CAMP_WAR;index++)
	{
		leaderCampWar[index].startLeaderCampWar();
	}
}


bool 
campWarManagement::startLeaderCampWar(time_t _startTime)	
{
	initLeaderCampWar();//报名开启时，清除初始化战场；
	
	Lpeace_time_start=_startTime;//开启自由时间定时器；
	Lpeace_time_end=_startTime+Lpeace_time;	
	if(NULL == peaceTimer)
		peaceTimer = new ev_timer;
		
	ext_ev_timer_init(peaceTimer,startLeaderCampWarPKCall,Lpeace_time,0,this);
	ev_timer_start(loops,peaceTimer);
	
	// sprintf(campInfo_msg,"11,7,2");	//通知所有在线玩家，统领战开启；
	// sendActivityMsg(campInfo_msg,Lpeace_time/60 - 1,60);	
	
	cout<<"[XHM MSG] Lpeace_time_start,Start time:"<<Lpeace_time_start<<" Lpeace_time_end time:"<<Lpeace_time_end<<endl;
	return true;
}

/**
	返回当前查询房间的人数string；
*/
string
campWarManagement::getLeaderCampWarStatus()
{
	string gap = ",";
	string desString;
	
	for(int index=0;index<ROOM_OF_LEADEER_CAMP_WAR;index++)
	{
		desString +=intTostring(leaderCampWar[index].getFactionASize())+\
           intTostring(leaderCampWar[index].getFactionBSize());
	}
	
	return desString;
}

/**
return int 返回当前统领战剩余的秒数；
*/
int 
campWarManagement::getLeaderCampWarOverTime(int _index)				//统领阵营战剩余时间 返回值：秒数
{
	if(_index <0 || _index > ROOM_OF_LEADEER_CAMP_WAR)
		_index = 0;
		
	return (leaderCampWar[_index]).LeaderCampWarEndTime-time(NULL);
}

void
campWarManagement::viewLeaderCampWarAwards(Hero* myHero)	//查看统领战奖励奖励设置；
{
	if(myHero==NULL)
	{
		cout<<"[XHM WARNING] viewLeaderCampWarAwards NULL == myHero ERROR(campWarManagement.cpp)!"<<endl;
	}
		
	int index=findCampType(myHero);
	if(index < 0 || index >= ROOM_OF_LEADEER_CAMP_WAR)
	{
		cout<<"[XHM WARNING] viewLeaderCampWarAwards index < 0 || index >= ROOM_OF_LEADEER_CAMP_WAR ERROR(campWarManagement.cpp)!"<<endl;
	}
	
	send_msg(myHero->getFd(),leaderCampWar[index].viewAwards(myHero));
}

int 
campWarManagement::receiveLeaderCampWarAwards(Hero* myHero)//领取统领战奖励；
{
	if(NULL == myHero)
		return -1;
		
	int index=findCampType(myHero);
	if(index < 0 || index >= ROOM_OF_LEADEER_CAMP_WAR)
		return -2;
		
	int ret = leaderCampWar[index].receiveAwards(myHero);
	
	if(strstr(myHero->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		exitCampWarSence(myHero);	
	
	myHero->setCampWarData(-1,-1,false,true);		
	return ret;
}



int
campWarManagement::getRevivalPt(Hero* pg_hero)
{
	if(pg_hero == NULL)
		return 0;
	int index=pg_hero->getCamp();
	if(index < 0 ||  index >= ROOM_OF_LEADEER_CAMP_WAR)
		return 0;
	
	char* pName = pg_hero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string factionName=pName;	
	
	if(factionName == leaderCampWar[index].factionAName)
		return 1;
	else if(factionName == leaderCampWar[index].factionBName)
		return 2;	
	
	else
		return 0;
}



/**********************************************************/
/******************* 统领阵营战报名接口 *******************/
/**********************************************************/
void
ApplyLeaderCampWarFinishCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
		
    ev_timer_stop(loop,think);
	
	campWarManagement *ApplyleaderCampWar = (campWarManagement *)think->target;
	
	if(ApplyleaderCampWar == NULL)
	{
		return;
	}
	
	// cout<<"[XHM MSG] ApplyLeaderCampWar time is over(campWarMangement.cpp),Going to call finishApplyLeaderCampWar()"<<endl;
	ApplyleaderCampWar->finishApplyLeaderCampWar();
}

/**
	-1,英雄id错误
	-2,未加入帮派；
	-3，不是帮主或者副帮主
	-4，帮派等级没有在3级以上
	-5，帮派人数没有在15人以上
	-6，已经报过名；
	-7,不在指定时间报名；
*/

int 
campWarManagement::applyLeaderCampWar(string heroId)
{
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())//该英雄id不存在；
		return -1;	
		
	Hero *myHero=iter->second;
	

	char* pName = myHero->getGuildName();//获取帮派的名字;
	if(NULL == pName)
		return -2;
	string factionName=pName;	
	
	Guild*	myfaction = myHero->getGuild();
	if(NULL == myfaction)
		return -2;
		
	time_t currTime = time(NULL);//判断是否是在指定时间内报名
	if(  currTime >= ApplyLeaderCampWarEndTime || currTime < ApplyLeaderCampWarStartTime)
		return -7;		
		
	if(myfaction->getPresidId()!=heroId && myfaction->getVicePresidId()!=heroId)//判断是不是帮主和副帮主报名,返回	
		return -3;
		
	if(myfaction->getLevel()<LOW_GUILD_LEVEL)//判断帮派等级是否在3级以上；
	{
		cout<<"[XHM WARNING] Faction level less than 3"<<endl;
		return -4;
	}	

	if(myfaction->getCurMembs() < LOW_GUILD_COUNTS)//判断帮派人数是否在15人以上；
	{
		cout<<"[XHM WARNING] Faction members less than 15."<<endl;
		return -5;
	}

	int index=findCampType(myHero);//判断阵营类型；
	if(index < 0 || index >= ROOM_OF_LEADEER_CAMP_WAR)
		return -2;
		
		
	 int ret = leaderCampWar[index].apply2FactionWar(factionName,index);
	 
	 if(ret == 0)
	 {
		switch(index){
		case 0:
			if(app_guild_size[0] < MAX_GUILD_NAME)
			{
				memcpy(leaderCampWar_app_info.mizong_app_guildName[app_guild_size[0]],pName,MAX_GUILD_NAME_LEN-1);
				++app_guild_size[0];
			}
		case 1:
			if(app_guild_size[1] < MAX_GUILD_NAME)
			{
				memcpy(leaderCampWar_app_info.xiejiao_app_guildName[app_guild_size[1]],pName,MAX_GUILD_NAME_LEN-1);
				++app_guild_size[1];
			}
			break;
		case 2:
			if(app_guild_size[2] < MAX_GUILD_NAME)
			{
				memcpy(leaderCampWar_app_info.youxia_app_guildName[app_guild_size[2]],pName,MAX_GUILD_NAME_LEN-1);
				++app_guild_size[2];
			}
			break;
		default:
			break;
		}
		
		setAppInfo2Mem();
	}
	 
	 return ret;
}


bool 
campWarManagement::startApplyLeaderCampWar(time_t _startTime)//开启统领阵营战报名；
{	

		ApplyLeaderCampWarStartTime=_startTime;//设定初始值
		ApplyLeaderCampWarEndTime=_startTime+ApplyLeaderCampWarLastTime;
	
		if(NULL == CampWartimer)//启动计时器
			CampWartimer = new ev_timer;
		
		ext_ev_timer_init(CampWartimer,ApplyLeaderCampWarFinishCall,ApplyLeaderCampWarLastTime,0,this);
		ev_timer_start(loops,CampWartimer);
		
		
		// sprintf(campInfo_msg,"11,7,3");//通知所有在线玩家，统领战报名开启；
		// sendActivityMsg(campInfo_msg,ApplyLeaderCampWarLastTime/180 - 2,180);	
		cout<<"[XHM MSG] startApplyLeaderCampWar,Start time:"<<ApplyLeaderCampWarStartTime<<" End time:"<<ApplyLeaderCampWarEndTime<<endl;
		return true;
}

int 
campWarManagement::CampWarApplyLastTime()
{
	if(ApplyLeaderCampWarEndTime == 0)
		return 0;
		
	return ApplyLeaderCampWarEndTime-time(NULL);
}


bool 
campWarManagement::finishApplyLeaderCampWar()
{
	ApplyLeaderCampWarStartTime=0;//设定初始值
	ApplyLeaderCampWarEndTime=0;

	char* challenge_guild_name=NULL;
	
	leaderCampWar_app_info.init();
	
	for(int i=0;i<ROOM_OF_LEADEER_CAMP_WAR;i++)
	{
		app_guild_size[i]=0;
		challenge_guild_name = leaderCampWar[i].endApplyFactionWar();
		if(challenge_guild_name)//保存帅选成功的帮派名字；
		{
			memcpy((char*)(&(leaderCampWar_app_info.mizong_guildName)),challenge_guild_name,MAX_GUILD_NAME_LEN);
		}
	}
	
	cout<<"[XHM　MSG] finishApplyLeaderCampWar!"<<endl;
	setAppInfo2Mem();	
}



/**********************************************************/
/******************** 盟主阵营战接口 **********************/
/**********************************************************/
void
startChiefCampWarPKCall(struct ev_loop *loop,ev_timer *think,int revents)
{
	if(think == NULL)
		return;
    ev_timer_stop(loop,think);

	campWarManagement *ChiefCampWar = (campWarManagement *)think->target;
	
	if(ChiefCampWar == NULL)
	{
		return;
	}
	ChiefCampWar->startChiefCampWarPK();
}

bool 
campWarManagement::startChiefCampWarPK()
{
	chiefCampWar.sendMsgStartPK(ChiefCampWarLastTime);
	Cpeace_time_start=0;
	Cpeace_time_end=0;
}

bool 
campWarManagement::finishChiefCampWar(string&factionName)
{
	// cout<<"[XHM MSG] The chiefWar winner factionName(campWarManagemennt.cpp):"<<factionName<<endl;
	Guild *guild=NULL;
	if(!factionName.empty())
	{
		if(strlen(currCampInfo.chieferCampInfo.chiefCampWarName))
		{
			guild = getGuildWithName(currCampInfo.chieferCampInfo.chiefCampWarName);
			if (guild != NULL)
			{
				guild->setCampTitle(2, 1);
			}
		}
	
	
		memcpy(currCampInfo.chieferCampInfo.chiefCampWarName,factionName.c_str(),strlen(factionName.c_str()));//帮派名字；
		currCampInfo.chieferCampInfo.chiefCampWarName[strlen(factionName.c_str())] = '\0';		
		
		if(strlen(currCampInfo.chieferCampInfo.chiefCampWarName))
		{
			guild = getGuildWithName(currCampInfo.chieferCampInfo.chiefCampWarName);
			if (guild != NULL)
			{
				guild->setCampTitle(2, 0);
			}
		}		
		
		char* p_hero_id = getGuildPresidId(const_cast<char*>(factionName.c_str()));//获取帮派帮主的ID；	
		if(p_hero_id){
			//武林盟主  jolly add
			char info[1024]={'\0'};
			Hero *hero=heroid_to_hero(p_hero_id);
			if (hero!=NULL)
			{							
				snprintf(info,sizeof(info),"%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d",7,SYSTEM_WARN,"xf007",2,7,hero->getCamp(),0,0,0,1,hero->getNickName(),hero->getIdentity(),0,0);
				map<string, Hero*>::iterator it_hero;

				for (it_hero=heroId_to_pHero.begin();it_hero!=heroId_to_pHero.end();++it_hero)
				{
					if (it_hero->second!=NULL)
					{						
						send_msg(it_hero->second->getFd(),info);
					}
				}
			}
		
		
			//取消头衔		
			if(!strstr(currCampInfo.chieferCampInfo.chieferId,p_hero_id))
			{
				if(strlen(currCampInfo.chieferCampInfo.chieferId))
				{
					map<string, Hero*>::iterator iter =heroId_to_pHero.find(currCampInfo.chieferCampInfo.chieferId);//取消头衔
					if(iter != heroId_to_pHero.end())
					{
						// cout<<"[XHM MSG] The title is over time(campWarManagement.cpp),Will cut:"<<CAMP_CHIEF_TITLE<<endl;
						iter->second->cutTitle(CAMP_CHIEF_TITLE);
						
						/*摧毁塑像,add chenzhen 201303081311*/
						string titleStr = "SH_";
						titleStr += CAMP_CHIEF_TITLE;						
						destoryStatuary(const_cast<char*>((titleStr).c_str()));

						
					}else{
						;
					}
				}

				//塑建雕像 TODO added chenzhen
				//武林盟主角色ID p_hero_id 武林盟主头衔ID CAMP_CHIEF_TITLE
				string titleStr = "SH_";
				titleStr += CAMP_CHIEF_TITLE;	
				setUpStatuary(p_hero_id,const_cast<char*>((titleStr).c_str()));
				
				
				chiefCampWar.setChiefHeroId(p_hero_id);		
				strncpy(currCampInfo.chieferCampInfo.chieferId,p_hero_id,sizeof(currCampInfo.chieferCampInfo.chieferId));
				currCampInfo.chieferCampInfo.chieferId[sizeof(currCampInfo.chieferCampInfo.chieferId)-1] = '\0';		
				
				char* p_hero_nick=viewGuildPresidNick(0,const_cast<char*>(factionName.c_str()));//获取帮主昵称；
				if(p_hero_nick)
				{
					memcpy(currCampInfo.chieferCampInfo.chiefer,p_hero_nick,sizeof(currCampInfo.chieferCampInfo.chiefer));
					currCampInfo.chieferCampInfo.chiefer[sizeof(currCampInfo.chieferCampInfo.chiefer)-1] = '\0';
				}
				
				setCampInfo();
			}			
		}

	}
}


/***
argument hero 英雄id;
  return int -1 hero为空；
			 -2 帮派名字不是当前盟主战的帮派；
			 -3 insert失败，已经参加过比赛；
			 -4 阵营类型不是系统默认三种类型；
			 -5 找不到地图的实例指针；
			  0 加入成功；
*/
int 
campWarManagement::add2ChiefCampWar(string heroId)
{
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())//该英雄id不存在；
		return -1;	
		
	Hero *myHero=iter->second;
	int index=findCampType(myHero);
	if(index < 0)
		return -4;
		
	if((ROOM_OF_ORDINARY_CAMP_WAR+ROOM_OF_LEADEER_CAMP_WAR+ROOM_OF_CHIEF_CAMP_WAR-1) >= mapInfoVector.size())	
	{
		return -5;
	}
	Map_Inform *mapDest=mapInfoVector[ROOM_OF_ORDINARY_CAMP_WAR+ROOM_OF_LEADEER_CAMP_WAR+ROOM_OF_CHIEF_CAMP_WAR-1]; //protected by benliao 20121126
	if(NULL == mapDest)
	{
		return -5;	
	}	

	time_t currTime = time(NULL);// 判断是否是在指定时间内报名
	if(currTime < Cpeace_time_start || currTime >= Cpeace_time_end )
		return -6;	
		
	int ret =chiefCampWar.addHero2Chiefwar(myHero);
	if(ret < 0)
		return ret;

	if(!myHero->addActivityCounts(3,1))
		cout<<"[XHM WARNING] Add the chief activity counts ERROR(campWarMamagement.cpp)! "<<endl;
	
	myHero->setCampWarData(3,1,false,false);	//盟主阵营战就只有一个房间；
	
	return enterCampWarSence(myHero,mapDest);
}

/***
argument hero 英雄id
  return int  -1 hero为空,找不到hero实例；
			  -2 找不到跳回去的地图以及其坐标；
			   0 退出成功；
*/
int 
campWarManagement::exitFromChiefCampWar(string heroId)
{
	map<string, Hero*>::iterator iter = heroId_to_pHero.find(heroId);
	if(iter==heroId_to_pHero.end())//该英雄id不存在；
		return -1;		
		
	Hero *myHero=iter->second;
	chiefCampWar.delHeroFromChiefWar(myHero);
	return exitCampWarSence(myHero);
}

int
campWarManagement::getChiefCampWarOverTime()	
{
	return chiefCampWar.ChiefCampWarEndTime-time(NULL);
}

/**
	argument void
	return time_t 当前和平剩余时间。
*/
time_t 
campWarManagement::ChiefCampWarPeaceTime()//和平剩余时间
{
	return Cpeace_time_end - time(NULL);
}

string 
campWarManagement::getChiefCampWarStatus()
{
	string roomStaus;
	
	return roomStaus;
}

bool 
campWarManagement::startChiefCampWar(time_t _startTime)//开启盟主阵营战；
{
		chiefCampWar.startChiefCampWar(); 
		
		Cpeace_time_start=_startTime;
		Cpeace_time_end=_startTime+Cpeace_time;	
		 if(NULL == peaceTimer)
			 peaceTimer = new ev_timer;
		ext_ev_timer_init(peaceTimer,startChiefCampWarPKCall,Cpeace_time,0,this);
		ev_timer_start(loops,peaceTimer);
		
		// sprintf(campInfo_msg,"11,7,4");//通知所有在线玩家，盟主战开启；
		// sendActivityMsg(campInfo_msg,Cpeace_time/60 - 1,60);	
		
		cout<<"[XHM MSG] startChiefCampWar,Start time:"<<ChiefCampWarStartTime<<" End time:"<<ChiefCampWarEndTime<<endl;
		return true;
}

void
campWarManagement::viewChiefCampWarAwards(Hero* myHero)//查看奖励设置；
{
	if(NULL == myHero)
	{
		cout<<"[XHM WARNING] viewChiefCampWarAwards NULL == myHero ERROR(campWarManagement.cpp)!"<<endl;
	}
	else
		send_msg(myHero->getFd(),chiefCampWar.viewAwards(myHero));
}

int 
campWarManagement::receiveChiefCampWarAwards(Hero* myHero)//领取奖励；
{
	if(NULL == myHero)
		return -1;
	int ret = chiefCampWar.receiveAwards(myHero);
	if(strstr(myHero->getMapId(),(mapTypeInfo.campWarMapId).c_str()))
		exitCampWarSence(myHero);	
	
	myHero->setCampWarData(-1,-1,false,true);	
	return  ret;
}


/**
 *进入阵营资源战失败原因
	1：不在阵营资源战时间
	2：进入房间号错误
	3：玩家没有加入阵营
	4：玩家等级没有达到30级
	5：系统错误（开服时未生成阵营资源战房间）
	6：系统错误（阵营资源战地图为空）
	-1：玩家没在入阵营资源战NPC附近
	-2：房间人数已满
	-3：阵营人数已满
	-4：房间未开启或者房间在发奖
	
 */
int campWarManagement::entCampResWar(Hero* hero, int index)
{
	if (!isInCampResWarTime)
	{
		return 1;
	}
	
	if (index < 0 || index > ROOM_OF_CAMP_RES_WAR - 1)
	{
		return 2;
	}
	
	int camp = hero->getCamp();
	if (camp < 0 || camp > 2)
	{
		return 3;
	}
	
	if (hero->getLevel() < 30)
	{
		return 4;
	}
	
	if (mapInfoVector.size() != ROOM_NUM_BEFORE_CAMP_RES_WAR + ROOM_OF_CAMP_RES_WAR)
	{
		cout<<"mapInfoVector.size() is "<<mapInfoVector.size()<<" need size is "<<ROOM_NUM_BEFORE_CAMP_RES_WAR + ROOM_OF_CAMP_RES_WAR<<endl;
		return 5;
	}
	
	Map_Inform *mapDest = mapInfoVector[ROOM_NUM_BEFORE_CAMP_RES_WAR + index];	//index从0开始
	if(mapDest == NULL)
	{
		return 6;	
	}
	
	int openNext = 0;
	int ret = campResWarGroup[index].join(hero, openNext);
	if (openNext != 0)
	{
		//是否房间人数已满，进入blabla~~判断
		for (int i = 0; i < ROOM_OF_CAMP_RES_WAR; i++)
		{
			if (campResWarGroup[i].isOpen())
			{
				//当再来一个像hero一样的英雄无容身所时
				if (campResWarGroup[i].getRoomState() & (1 << hero->getCamp()))
				{
					continue;
				} else {
					break;
				}
			} else {
				campResWarGroup[i].open();
				campResWarLastOpenRoomIndex = i;
				break;
			}
		}
		
	}
	
	if (ret != 0)
	{
		return ret;
	}
	
	//这里的ret必须等于0,必须的
	ret = enterCampWarSence(hero, mapDest);
	hero->setCampWarData(4, index, true, false);	//设置当前角色阵营战数据；
	campResWarGroup[index].update_room_infor();
	return ret;
}

/**
 * 退出阵营资源战失败原因
	1：玩家未参加阵营资源战
	2：玩家记录资源战房间号错误
	-1：对应房间中无玩家数据
	-2：主城地图配置错误
	
 */
int campWarManagement::exitCampResWar(Hero* hero)
{
	int type = hero->getCampWarType();
	if (!hero->isInCampResWar())
	{
		return 1;
	}
	
	int roomIndex = hero->getCampWarData().campWarRoomNum;
	if (roomIndex < 0 || roomIndex >= ROOM_OF_CAMP_RES_WAR)
	{
		return 2;
	}
	
	int ret = campResWarGroup[roomIndex].exit(hero);
	return ret;
}

int campWarManagement::campResWarCollect(Hero* hero)
{
	int type = hero->getCampWarType();
	if (!hero->isInCampWar())
	{
		return 1;
	}
	
	if (type != 4)
	{
		return 2;
	}
	
	int roomIndex = hero->getCampWarData().campWarRoomNum;
	if (roomIndex < 0 || roomIndex >= ROOM_OF_CAMP_RES_WAR)
	{
		return 3;
	}
	
	int ret = campResWarGroup[roomIndex].collect(hero);
	return ret;
	
}

int campWarManagement::campResWarKill(Hero *atker, Hero* atked)
{
	if (!atker->isInCampWar() || !atked->isInCampWar())
	{
		return 1;
	}
	
	int typeA = atker->getCampWarType();
	int typeB = atked->getCampWarType();
	if (typeA != 4 || typeA != typeB)
	{
		return 2;
	}
	
	
	int campA = atker->getCamp();
	int campB = atked->getCamp();
	if (campA == campB)
	{
		return 3;
	}
	
	int roomIndexA = atker->getCampWarData().campWarRoomNum;
	int roomIndexB = atked->getCampWarData().campWarRoomNum;
	if (roomIndexA != roomIndexB || roomIndexA < 0 || roomIndexA >= ROOM_OF_CAMP_RES_WAR)
	{
		return 4;
	}
	
	int ret = campResWarGroup[roomIndexA].kill(atker, atked);
	return ret;
	
}

//阵营资源战复活
int campWarManagement::campResWarRevival(Hero* hero)
{
	cout<<"in campWarManagement::campResWarRevival"<<endl;
	if (!hero->isInCampResWar())
	{
		return 1;
	}
	
	int roomIndex = hero->getCampWarData().campWarRoomNum;
	if (roomIndex < 0 || roomIndex >= ROOM_OF_CAMP_RES_WAR)
	{
		return 2;
	}
	
	int ret = campResWarGroup[roomIndex].revival(hero);
	return ret;
}

//设置在阵营资源战时间
void campWarManagement::setInCampResWarTime(bool flag)
{
	isInCampResWarTime = flag;
	cout<<"Out have set campResWar start flag:"<<flag<<endl;
	cout<<"Out have set campResWar start flag:"<<flag<<endl;
	cout<<"Out have set campResWar start flag:"<<flag<<endl;
	cout<<"Out have set campResWar start flag:"<<flag<<endl;
	cout<<"Out have set campResWar start flag:"<<flag<<endl;
	if (flag)
	{
		joinCampResWarHeroIds.clear();
		map<string, CampResWarReward_T*>::iterator it;
		it = campResWarRewardInfo.begin();
		for (it; it != campResWarRewardInfo.end(); it++)
		{
			CampResWarReward_T* p_reward = it->second;
			delete p_reward;
		}
		campResWarRewardInfo.clear();
		campResWarGroup[0].open();
		campResWarLastOpenRoomIndex = 0;
	}
}


/**
 * 资源战查看某玩家资源数
	1：玩家未参加阵营资源战
	2：玩家记录资源战房间号错误
	-1：对应房间中无玩家数据
 */
int campWarManagement::viewHeroResNum(Hero* hero, char* heroId)
{
	if (!hero->isInCampResWar())
	{
		return 1;
	}
	
	int roomIndex = hero->getCampWarData().campWarRoomNum;
	if (roomIndex < 0 || roomIndex >= ROOM_OF_CAMP_RES_WAR)
	{
		return 2;
	}
	
	int ret = campResWarGroup[roomIndex].viewResNum(hero, heroId);
	return ret;
}

int campWarManagement::getCampResWarReward(Hero* hero)
{
	map<string, CampResWarReward_T*>::iterator it;
	it = campResWarRewardInfo.find(hero->getIdentity());
	if (it == campResWarRewardInfo.end())
	{
		return 1;
	}
	
	CampResWarReward_T* p_reward = it->second;
	if (strlen(p_reward->goodsId) != 0)
	{
		if (!saveGoodsInBag(hero, p_reward->goodsId, 1))
		{
			return 2;
		}
	}
	
	increaseBoundGameMoney(hero, p_reward->money);
	hero->addPrestigeValue(p_reward->prestige);
	campResWarRewardInfo.erase(hero->getIdentity());
	delete p_reward;
	return 0;
}