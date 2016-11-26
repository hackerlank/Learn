/**************************************************
文件类型：角色管理，选择角色

文件名称：role_manage_change_scene.cpp

创建时间：2012.4.16

author  ：	Tory

修改	：2012.12,4 xhm

******************************************************/
#include"command_user_role_manage.h"
//包含所有宏定义的头文件
#include"other_define_data.h"
//返回头命令的宏定义头文件
#include"command_return_define_data.h"
//用户角色管理辅助函数头文件
#include"user_role_manage_assist.h"
//所有工具函数的头文件
#include"command_other_function_all_over.h"

#include"map_inform.h"

// #include "TD_Instancing.h"
#include "pet.h"
#include "instancing_manage.h"
#include "pick.h"
#include "map_inform.h"
#include"entCpy.h"
#include"cpyAsist.h"
extern int sock_fd;
extern int g_msg_len;
extern Hero* pg_hero;       
extern map<string,Map_Inform*>mapId_connect_map;

using namespace std;

int happyMapCheck(Hero *hero, char *oldMap, char *newMap);
extern MapType_T mapTypeInfo;		//某些特殊地图的ID；

void change_scene(char *buffer)
{
	int fd=sock_fd;
	char msg_body[200]={0};
	MSG_BEGIN(buffer, g_msg_len);	
	MSG_CHAR_END(char* map_id);			
	
	if(map_id == NULL || strlen(map_id) == 0)
	{
		return;
	}
		
	/*进入金陵限制 80 级*/	//add xhm
	if(strcmp(map_id,mapTypeInfo.mainCityMapId2.c_str()) == 0)
	{
		if(pg_hero->getLevel() < 80)
		{
			sprintf(msg_body,"2,6,2,80");//低于80级；	
			send_msg(fd,msg_body);		
			return;
		}
	}
	
	
	/*进入vip包厢*/
	if((strcmp(map_id,"map_025") == 0 || strcmp(map_id,"map_026") == 0 ||\
	  strcmp(map_id,"map_027") == 0 || strcmp(map_id,"map_028") == 0))
	  {
			entVipBaleRoom(buffer);
			return;
	  }
	
	/*进入忠义堂，吃饭*/	
	if(strcmp(map_id,"map_029") == 0)
	{
		cout<<"go eat first:"<<map_id<<endl;
		enterPartyEat(pg_hero->getIdentity(),map_id);
		return;
	}
	
	/*进任务副本法海不懂爱*/
	if(strncmp(map_id,"ectype_map_047",14) == 0)
	{
		cout<<"go to the task copy begin:"<<map_id<<endl;
		entTaskCpy(pg_hero->getIdentity(),"021_0");
		cout<<"go to the task copy end:"<<map_id<<endl;
		return;
	}
	
    map<string,Map_Inform*>::iterator map_it;
    map_it = mapId_connect_map.find(map_id);
	int happyResult = 0;
    if(map_it == mapId_connect_map.end())
    {
		cout<<"in change_scene,can't find des_map!"<<endl;
		sprintf(msg_body,"2,%d,%d",CHANGE_SCENE,FAILED);		
		send_msg(fd,msg_body);
		return ;       
    }

#if 0
	else if ((happyResult = happyMapCheck(pg_hero, pg_hero->getMapId(), map_id)) != 0)
	{
		cout<<"Change map limited!!"<<endl;
		sprintf(msg_body,"2,%d,%d,%d",CHANGE_SCENE, FAILED, happyResult);		
		send_msg(fd,msg_body);
		return ; 
	}
#endif
	else
	{   
		Map_Inform *scene_map = map_it->second;
		Map_Inform *nowMap = pg_hero->getMap();
		
		if(nowMap == NULL)
		{
			cout<<"change map error:"<<pg_hero->getIdentity()<<endl;
			return;
		}
		
		/*娱乐地图，pk地图，副本地图，不允许对跳，也禁止直跳,add chenzhen 20130411*/
		if(scene_map->getWarType() !=1 || isHappyMap(scene_map->getMapId()))
		{
			if(nowMap->getFlgCpy() || nowMap->getWarType() !=1 || isHappyMap(nowMap->getMapId()))
			{				
				cout<<"do not jump the map:"<<pg_hero->getIdentity()<<endl;
				sprintf(msg_body,"2,%d,5",CHANGE_SCENE);   
				send_msg(fd, msg_body);
				return;
			}
		}       
		if((pg_hero->getCamp() < 0 || pg_hero->getCamp() > 2) && scene_map->campEntFlag)
		{
			sprintf(msg_body,"2,%d,4",CHANGE_SCENE);   
			send_msg(fd, msg_body);
			return;
		}
		pg_hero->quit_scene();			
        pg_hero->setMap(scene_map);			
//		pg_hero->setMapId(map_id);
		Point myPt=scene_map->getEntPt();
   		pg_hero->setLocation(myPt);              	//设置角色的当前逻辑坐标之前，需先设置角色所在场景的Map_Inform Tory add 2012.5.21	

		sprintf(msg_body,"2,%d,%d,%s,%d,%d,%d,%d,%d",CHANGE_SCENE,SUCCESS,map_id,myPt._x,myPt._y,scene_map->getWarType(),\
													scene_map->getChangePkType(),scene_map->getMapType());
        send_msg(fd, msg_body);	
	}
	
	return;
}

int happyMapCheck(Hero *hero, char *oldMap, char *newMap)
{
	int vipClass = hero->memHero->vipDailyData.stage;
	if (vipClass < 0 || vipClass > 3)
	{
		cout<<"[BisonShow] the hero vipClass is "<<vipClass<<endl;
		return -1;
	}
	if (strcmp(newMap, "map_023") == 0)
	{
		if (strcmp(oldMap, "map_001") != 0)
		{
			return -2;
		}
	}
	else if (strcmp(newMap, "map_024") == 0)
	{
		if (strcmp(oldMap, "map_010") != 0)
		{
			return -3;
		}
	}
	else if (strcmp(newMap, "map_025") == 0)
	{
		if (vipClass < 1 || strcmp(oldMap, "map_023") != 0)
		{
			return -4;
		}
	}
	else if (strcmp(newMap, "map_026") == 0)
	{
		if (vipClass < 2 || strcmp(oldMap, "map_023") != 0)
		{
			return -5;
		}
	}
	else if (strcmp(newMap, "map_027") == 0)
	{
		if (vipClass < 1 || strcmp(oldMap, "map_024") != 0)
		{
			return -6;
		}
	}
	else if (strcmp(newMap, "map_028") == 0)
	{
		if (vipClass < 2 || strcmp(oldMap, "map_024") != 0)
		{
			return -7;
		}
	}
	return 0;
}
