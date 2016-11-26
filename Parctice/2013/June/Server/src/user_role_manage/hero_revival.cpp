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
#include "money_operator.h"
#include "hero.h"
#include "revival_config.h"
#include"cpy_series_command_function.h"
#include"cpyLimit.h"
#include"boxAsist.h"
#include"cpyAsist.h"
extern map<string,Map_Inform*>mapId_connect_map;
extern map<string,CpyLimit*> cpyId_to_cpyLimit;
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Revival_Config*> mapId_to_revival;		//复活点坐标信息
using namespace std;
extern MapType_T mapTypeInfo;		//默写特殊地图的ID；
extern int g_msg_len; //除去消息头的有效消息长度
extern Hero* pg_hero; //当前角色对象
extern char g_out_buf[20480];

void sendRevivalMsg(Hero *hero, string flag);

void revival(char *buffer)
{
	int flag;
	MSG_BEGIN(buffer,g_msg_len);
	MSG_INT(flag);
	
	cout<<"4,6,"<<flag<<endl;
	puts("I don't know whether it is come from here");
	sendRevivalMsg(pg_hero, flag);
}

//发送复活消息
void sendRevivalMsg(Hero *hero,int flag)
{
	// cout<<"Fuck the world!!!!!!!!!!!!!!!!!!!!!! "<<flag<<endl;
	hero->stopRevivalTimer();
	int revival_life;
	int revival_magic;
	Map_Inform *mapNow;
	if (flag==0) //原地复活
	{
		cout<<"------------------------------revival.cpp 57------------------------------"<<endl;
		if (hero->isInGuildWarRoom()||useBoundGold(hero,5))
		{	
			mapNow = hero->getMap();
			if(mapNow == NULL)
			{
				cout<<"recover in map is error:"<<endl;
				return;
			}
			/*计数副本里面死亡次数*/
			if(mapNow->getFlgCpy())
			{
				hero->addCpyRecTme();
			}
			
			revival_life=hero->getLifeUpperVal();
			revival_magic=hero->getMagicUpperVal();
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",7,0,revival_life,revival_magic);
			
			hero->setLifeStation(1);
			hero->setLifeVal(revival_life);
			hero->setMagicVal(revival_magic);
			send_msg(hero->getFd(),g_out_buf);		
			Nbox *box = hero->getMap()->getBox();
			if(box == NULL)
			{
				return;
			}
			StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);		
			box->getStaInSrcVec(obj);
			string strLog = CreateMessage::come_into_view(hero);	
			box->sentBoxMsg(const_cast<char*>(strLog.c_str()),hero->getIdentity());
		}
		else
		{
			msg_error(g_out_buf,49);
			send_msg(hero->getFd(),g_out_buf);
		}
	} 
	else if (flag==1) //回城复活
	{		
		Map_Inform *mapnow=hero->getMap();
		char* mapnowid=mapnow->getMapId();
		
		revival_life=hero->getLifeUpperVal();
		revival_magic=hero->getMagicUpperVal();
		hero->setLifeVal(revival_life);
		hero->setMagicVal(revival_magic);
		if (mapnow->getFlgCpy())
		{
			outCpy(hero);					
		}
		else
		{
			map<string,Revival_Config*>::iterator it;
			if (strlen(mapnowid)>10 && !strstr(mapnowid,mapTypeInfo.campWarMapId.c_str()) && !strstr(mapnowid,mapTypeInfo.campResWarMapId.c_str()))
			{
				strncpy(mapnowid,mapTypeInfo.mainCityMapId.c_str(),sizeof(mapTypeInfo.mainCityMapId));
			}
			it=mapId_to_revival.find(mapnowid);
			cout<<"map id is :"<<mapnowid<<endl;
			if (it==mapId_to_revival.end())
			{
				cout<<"jolly:revival error hero_revival.cpp 154"<<endl;
			}
			else
			{			
				
				Revival_Config *revival=it->second;
				char* revival_map=revival->getRevivalMap();					
				map<string,Map_Inform*>::iterator map_it;
				map_it = mapId_connect_map.find(revival_map);
				if(map_it == mapId_connect_map.end())
				{
					cout<<"Acording to mapid can't find the Mapinform (in hero_revival)"<<endl;
				}
				else
				{					
					Map_Inform *scene_map = map_it->second;
					int ptx=revival->getPtx();
					int pty=revival->getPty();
					Point revival_pt;
					revival_pt._x=ptx;
					revival_pt._y=pty;
					cout<<"Point :"<<ptx<<"   "<<pty<<endl;
					hero->quit_scene();
					hero->setMap(scene_map);
					hero->setMapId(revival_map);
					hero->setLocation(revival_pt);              	//设置角色的当前逻辑坐标之前，需先设置角色所在场景的Map_Inform Tory add 2012.5.21
					snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d",2,CHANGE_SCENE,SUCCESS,revival_map,revival_pt._x,revival_pt._y);
					send_msg(hero->getFd(),g_out_buf);
					hero->setWalkingFlg(false);
					// cout<<msg_body<<endl;
					// hero->enter_scene();
				}
			}
		}
		hero->setLifeStation(1);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",7,0,revival_life,revival_magic);
		send_msg(hero->getFd(),g_out_buf);	
	}
	else if (flag==2)
	{
		cout<<"------------------------------revival.cpp 151------------------------------"<<endl;
		Map_Inform *mapnow=hero->getMap();
		char* mapnowid=mapnow->getMapId();				
		if (mapnow->getFlgCpy())
		{
			msg_error(g_out_buf,21);
			send_msg(hero->getFd(),g_out_buf);
		}
		
		else 
		{	
			if (strlen(mapnowid)>10 && !(hero->isInGuildWarRoom()))
			{
				msg_error(g_out_buf,24);
				send_msg(hero->getFd(),g_out_buf);
				return;
			}
			
			revival_life=hero->getLifeUpperVal()/2;
			revival_magic=hero->getMagicUpperVal()/2;
			
			hero->quit_scene();
			Point pt=mapnow->getEntPt(); //进入新场景的入点坐标	
			if (hero->isInGuildWarRoom() || strcmp(mapnowid,mapTypeInfo.guidWarMapId.c_str())==0)
			{
				pt = mapnow->getCampWarPt(hero->getCamp());
				dealCpyId(mapnowid);
				revival_life=revival_life*2;
				revival_magic=revival_magic*2;
			}
			else if (strcmp(mapnowid,mapTypeInfo.campSenceMapId.c_str()))
			{
				pt=mapnow->getCampWarPt(hero->getCamp());
			}
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d",2,CHANGE_SCENE,SUCCESS,mapnowid,pt._x,pt._y);
			send_msg(hero->getFd(),g_out_buf);
			hero->setLifeVal(revival_life);
			hero->setMagicVal(revival_magic);
			snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",7,0,revival_life,revival_magic);
			send_msg(hero->getFd(),g_out_buf);
			hero->setLocation(pt);   
			hero->setLifeStation(1);
			// cout<<msg_body<<endl;
			// hero->enter_scene();
		}
	}
	else if (flag==5)
	{
		Map_Inform *map_now;
		Nbox *box;
		StyObj obj(hero->getIdentity(),HERO_STYLE_TYPE);
		revival_life=hero->getLifeUpperVal();
		revival_magic=hero->getMagicUpperVal();
		
		map_now = hero->getMap();
		
		if(map_now == NULL)
		{
			return;
		}
		box = map_now->getBox();
		if(box == NULL)
		{
			return;
		}
		
		map_now->deleteID(obj); 
		
		string strLog;
				
		Point pt;//进入新场景的入点坐标		
		pt._x=4034;
		pt._y=3747;
		char msg_body[100]={'\0'};
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d",2,CHANGE_SCENE,SUCCESS,"map_022",pt._x,pt._y);
		send_msg(hero->getFd(),g_out_buf);
		hero->setLifeVal(revival_life);
		hero->setMagicVal(revival_magic);
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",7,0,revival_life,revival_magic);
		send_msg(hero->getFd(),g_out_buf);
		hero->setLocation(pt);   
		hero->setLifeStation(1);
		cout<<msg_body<<endl;
		strLog = CreateMessage::come_into_view(hero);		
		map_now->insertID(obj); 
		box->getStaInSrcVec(obj);
		box->sentBoxMsg(const_cast<char*>(strLog.c_str()),hero->getIdentity());
		
		//贞子处复活,如果身上还穿着送的时装 则脱下
		// fasionDestory(hero,0,);
	}
}


void onlineReturn(Hero *myHero)
{	
	Nbox *box;
	Map_Inform *map_now;
	
	map_now = myHero->getMap();

	StyObj obj(myHero->getIdentity(),HERO_STYLE_TYPE);
	
    map_now->insertID(obj);  
	
    map_now->inPutFd(myHero->getFd());      
	
	if(map_now == NULL)
	{
		return;
	}	
	
	box = map_now->getBox();
	if(box == NULL)
	{
		return;
	}
	
	box->getStaInSrcVec(obj);
	
	box->heroEnter(myHero,1);	
  
	return ;	
}
