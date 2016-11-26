/************************************************************
	文件名：mapAction.cpp
	文件作用：实现地图思考回调函数
	作者：chenzhen
	创建日期：2012.06.11
************************************************************/
#include"mapAction.h"
#include"map_src.h"
#include"map_inform.h"
#include"monsterBase.h"
#include"monsterPassivity.h"
#include"monsterPatrol.h"
#include"data_structure_struct.h"
#include"command_other_function_all_over.h"
#include"command_return_define_data.h"
#include"libev.h"
#include"cpy.h"
#include<set>
#include"timerContainer.h"
#include"cpyLimit.h"
#include"cpyAsist.h"
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string,Map_Src*>mapId_connect_map;
extern set<string>map_timer;    //地图计时器（用来刷怪）
extern map<string,Map_Src*>mapId_connect_map;  //把地图的id跟地图实类相关联 
extern TimerContainer<Map_Inform*> *mapThkContain;
void MapThkCalBak(struct ev_loop *loop,ev_timer *think,int revents)
{	
	Map_Inform *mapNow;
	Map_Cpy *mapCpy;
	Map_Src* mapSrc;		
	
	ev_timer_stop(loop,think); 
	
	
	mapNow = (Map_Inform*)think->target;
	
	if(mapNow->getFlgCpy())
	{
		mapCpy = (Map_Cpy*)think->target;
		
		/*调用思考对象成员函数*/
		mapCpy->mapThkCalBak();
		
		/*且是否回收<注意，这个很重要>*/
		if(mapCpy->recoverCpy())
		{
			return;
		}
	}
	else
	{
		mapSrc = (Map_Src*)think->target;
		
		if(mapSrc->getIsVipRom())
		{
			/*vip包厢回收*/
			if(mapSrc->vipCallBack())
			{
				return;
			}
		}
		else
		{
			if(mapSrc->getIsPartyRom())
			{
				/*帮派包厢回收*/
				if(mapSrc->partyCallBack())
				{
					return;
				}
			}
			else if(mapSrc->getIsCampRom())
			{
				/*帮派大本营包厢回收*/
				if(mapSrc->campCallBack())
				{
					return;
				}
			}
			else
			{
				/*普通场景成员函数*/
				mapSrc->mapThkCalBak();
			}
		}
	}	
	/*地图对象和地图定时器监听已绑定，start则能重启计时器 Tory*/	
	ev_timer_start(loop,think);
}




// void MapThkCalBak(struct ev_loop *loop,ev_timer *think,int revents)
// {	
	// char mapId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	// Map_Cpy *mapCpy;
	// Map_Src* mapSrc;	
	// int mapType;	
	
	// ev_timer_stop(loop,think); //added by benliao
	
	// strncpy(mapId,think->targetId,strlen(think->targetId));	
	// think->target = NULL;	
	// memset(think->targetId,'\0',sizeof(think->targetId));
	
	// mapType = IsCpyMap(mapId);
	
	// /*什么地图都不是*/
	// if(mapType == 0)
	// {
		// return;
	// }
	
	// /*副本地图*/
	// else if(mapType == 1)
	// {
		// mapCpy = findCpyMap(mapId);
		// if(mapCpy == NULL)
		// {
			// return;
		// }
		
		// /*调用思考对象成员函数*/
		// mapCpy->mapThkCalBak();
		
		// /*且是否回收<注意，这个很重要>*/
		// if(mapCpy->recoverCpy())
		// {
			// return;
		// }
		// think->target = mapCpy;
	// }
	
	// /*场景地图*/
	// else
	// {		
		// mapSrc = findSrcMap(mapId);
		// if(mapSrc == NULL)
		// {			
			// return;
		// }
		// /*调用思考对象成员函数*/
		// mapSrc->mapThkCalBak();
		// think->target = mapSrc;		
	// }
	
	// strncpy(think->targetId,mapId,strlen(mapId));
	// /*地图对象和地图定时器监听已绑定，start则能重启计时器 Tory*/	
	// ev_timer_start(loop,think);
// }




/*刷出野外boss*/
void brushMonsterActiveBoss(void)
{
	map<string,Map_Src*>::iterator src_it;
	for(src_it = mapId_connect_map.begin();src_it != mapId_connect_map.end();src_it++)
	{
		src_it->second->brushMonBoss();
	}
}
	
/*重置野外boss*/
void initMonsterActiveBoss(void)
{
	map<string,Map_Src*>::iterator src_it;
	for(src_it = mapId_connect_map.begin();src_it != mapId_connect_map.end();src_it++)
	{
		src_it->second->initMonBoss();
	}
}

/*找到副本地图实例*/
Map_Cpy* findCpyMap(char *cpyMapId)
{
	char mapId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char cpyId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char numStr[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	char cpyTypeId[SHOR_MID_VALUE_LENGTH + 1] = {'\0'};
	map<string,CpyLimit*>::iterator cpyLimt_it;
	
	int room;
	if(cpyMapId == NULL || strlen(cpyMapId) == 0)
	{
		return NULL;
	}
	
	// cout<<"cpyMapId:"<<cpyMapId<<endl;
	strncpy(cpyId,cpyMapId + strlen(cpyMapId) - 10,10);
	// cout<<"cpyId:"<<cpyId<<endl;
	
	if(!dealSerNumStr(cpyId,numStr,cpyTypeId))
	{
		cout<<"cpyId is error:"<<cpyId<<endl;
		return NULL;
	}
	// cout<<"numStr:"<<numStr<<endl;
	// cout<<"cpyTypeId:"<<cpyTypeId<<endl;
	room = atoi(numStr);
	
	
	 /*先在普通副本中进行查找*/
    cpyLimt_it = cpyId_to_cpyLimit.find(cpyTypeId);
	if(cpyLimt_it == cpyId_to_cpyLimit.end())
	{
		return NULL;
	}
	return cpyLimt_it->second->getMapCpy(room,cpyMapId);
}

/*判断地图id为何种地图*/
int IsCpyMap(char *mapId)
{
	char *p;
	if(mapId == NULL || strlen(mapId) == 0)
	{
		return 0;
	}
	p = mapId;
	/*副本地图*/
	if(*p == 'e')
	{
		return 1;
	}
	/*非副本地图*/
	return -1;
}

/*找到普通地图实例*/
Map_Src* findSrcMap(char *mapId)
{
	if(mapId == NULL || strlen(mapId) == 0)
	{
		return NULL;
	}
	map<string,Map_Src*>::iterator src_it;
	src_it = mapId_connect_map.find(mapId);
	if(src_it == mapId_connect_map.end())
	{
		return NULL;
	}
	return src_it->second;
}
	

	
	
