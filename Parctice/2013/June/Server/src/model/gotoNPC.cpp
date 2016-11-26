#include <string>
#include "hero.h"
#include"cpyLimit.h"
#include "map_inform.h"
#include "jumpId_to_changeSence.h"
#include"cpy_series_command_function.h"

#include"command_other_function_all_over.h"
 
extern map<string,Map_Inform*> mapId_connect_map;
extern map<string, Hero*> heroId_to_pHero;
extern map<int, Role*> fd_to_pRole;
extern map<string , map <string ,Point > > npc; //npc容器
extern int sock_fd;
extern map<string,Goods_Config*> id_to_cl;

#include "wholeDefine.h"
extern int g_msg_len;
extern Hero *pg_hero;
extern char g_out_buf[20480];

void gotoNPC(Point pt,Map_Inform* map_next)
{		
	pg_hero->quit_scene();
	pg_hero->setMap(map_next);
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%s,%d,%d,%d,%d,%d",2,CHANGE_SCENE,SUCCESS,map_next->getIdentity(),pt._x,pt._y,\
	map_next->getWarType(),map_next->getChangePkType(),map_next->getMapType());
	send_msg(pg_hero->getFd(),g_out_buf); 
	memset(g_out_buf,0,sizeof(g_out_buf));
	snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d",9,14);
	send_msg(pg_hero->getFd(),g_out_buf);
	
	pg_hero->setLocation(pt);
}
void goByNPC(char *buffer)
{
	Point pt;
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *mapId)
	MSG_INT(pt._x)
	MSG_INT(pt._y)
	
	cout<<"17,0,"<<mapId<<","<<pt._x<<","<<pt._y<<endl;
	
	Hero *hero = pg_hero;	

	map<string,Goods_Config*> ::iterator i=id_to_cl.find("b_cl_107_100");
	if(i==id_to_cl.end())					//找不到物品实例,返回
	{
		return;
	}
	Goods_Config *goods=i->second;
	if(hero->getLevel()<goods->getLevelLimit())			//玩家等级小于使用等级,返回
	{
		return;
	}
	if (hero->isInGuildWarRoom())			//帮战中不准用疾行甲马传送	
	{		
		return;
	}
	if (hero->isInCampResWar())
	{
		return;
	}
	// Map_Inform *map=pg_hero->getMap();
	Map_Inform *mapInst = NULL;
	map<string, Map_Inform*>::iterator iter_map = mapId_connect_map.find(mapId);
	if(iter_map == mapId_connect_map.end())  //Ordinary duplicate scene not find the mapId；
	{
	   return;
	}
	mapInst = iter_map->second;
	
	if (mapInst==NULL)						//地图指针错误,返回
	{
		return;
	}
	Map_Inform *heroMap = pg_hero->getMap();
	if (heroMap == NULL)
	{
		return;
	}
	memset(g_out_buf,0,sizeof(g_out_buf));
	if (heroMap->getFlgCpy()!=0)				//在副本中,不允许用,返回
	{
		msg_error(g_out_buf,60);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	if (hero->getHeroState()==5)				//摆摊中,不允许使用,返回
	{
		msg_error(g_out_buf,71);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	if (heroMap->getMapType()==4)				//阵营战中,无法使用疾行甲马
	{
		msg_error(g_out_buf,73);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	if (heroMap->getWarType()==2)				//PK地图中,无法使用疾行甲马
	{		
		msg_error(g_out_buf,74);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	char wagonId[40]={'\0'};
	strncpy(wagonId,hero->memHero->wagonId,sizeof(wagonId));
	if (strlen(wagonId) != 0)				//拉马车中,不许用,返回
	{
		return;
	}
	
	int digst=mapInst->getBaseDigst();
	Point temp=MapExchangeLogical(pt);
	Point logPoint;
	logPoint._x=temp._x;
	logPoint._y=temp._y+digst;
	cout<<"logPoint._x:"<<logPoint._x<<endl;
	cout<<"logPoint._y:"<<logPoint._y<<endl;
		
	//判断是否是障碍点.若是则重新随即
	int number=random_number(0,3);
	if (number==0)
	{
		logPoint._x++;
	}
	else if (number==1)
	{
		logPoint._y++;
	}
	else if (number==2)
	{
		logPoint._y++;
		logPoint._x++;
	}
	else if (number==3)
	{
		logPoint._x--;
		logPoint._y++;
	}
	else if (number==4)
	{
		logPoint._x--;
	}
	
	// if(pg_hero->getGradeNow() > mapInst->getLevelUpperLimit())
	// {
		// cout<<"the pg_hero->getGradeNow():"<<pg_hero->getGradeNow()<<"iter->second->levelUpperLimit:"<<mapInst->getLevelUpperLimit()<<endl;
	   // cout<<"in the jumpId_to_changesence.cpp Hero level is levelUpperLimit!"<<endl;
	   // snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",2,CHANGE_SCENE,3,mapInst->getLevelUpperLimit());
	   // send_msg(pg_hero->getFd(),g_out_buf);
	   // return;
	// }
	if(pg_hero->getGradeNow() < mapInst->getLevelLowerLimit())
	{
	   cout<<"in the jumpId_to_changesence.cpp Hero level is levelLowerLimit!"<<endl;	   
	   // snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d,%d",2,CHANGE_SCENE,2,mapInst->getLevelLowerLimit());
	   // send_msg(pg_hero->getFd(),g_out_buf);
	   msg_error(g_out_buf,141);
	   send_msg(pg_hero->getFd(),g_out_buf);
	   return;
	}
	
	if (!mapInst->judgeLogPtHind(logPoint))
	{
		logPoint._x=temp._x;
		logPoint._y=temp._y+digst;
		if (!mapInst->judgeLogPtHind(logPoint))
		{
			cout<<"jolly:this point is hind point in dropgoods 382"<<endl;
			msg_error(g_out_buf,100);
			send_msg(pg_hero->getFd(),g_out_buf);
			return;
		}		
	}
	
	
	if((pg_hero->getCamp() < 0 || pg_hero->getCamp() > 2) && mapInst->getCampEntFlag())
	{
	   cout<<"in the jumpId_to_changesence.cpp Hero level is campEntFlag!"<<endl;	   
	   snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,CHANGE_SCENE,4);
	   send_msg(pg_hero->getFd(),g_out_buf);
	   return;
	}
	
	if (pg_hero->isInCampResWar())
	{
	   snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,CHANGE_SCENE,5);
	   send_msg(pg_hero->getFd(),g_out_buf);
	   return;
	}
	
	if (pg_hero->isInGuildWarRoom())
	{
	   snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,CHANGE_SCENE,5);
	   send_msg(pg_hero->getFd(),g_out_buf);
	   return;
	}
	
	if (hero->memHero->vipDailyData.flyTimes==0)
	{
		if(useBagGoods(hero,"b_cl_107_100",1)==0||useBagGoods(hero,"f_cl_107_100",1)==0)
		{		
			gotoNPC(pt,mapInst);
		}
		else 
		{
			msg_error(g_out_buf,101);
			send_msg(hero->getFd(),g_out_buf);
		}
	}
	else if (hero->memHero->vipDailyData.flyTimes==-1)
	{
		gotoNPC(pt,mapInst);
	}
	else
	{
		hero->memHero->vipDailyData.flyTimes--;
		gotoNPC(pt,mapInst);
		memset(g_out_buf,0,sizeof(g_out_buf));
		snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",9,35,hero->memHero->vipDailyData.flyTimes);
		send_msg(pg_hero->getFd(),g_out_buf);
	}
}

void goActive(char *buffer)
{
	Point pt;
	MSG_BEGIN(buffer,g_msg_len)
	MSG_CHAR(char *mapId)
	MSG_INT(pt._x)
	MSG_INT(pt._y)
	
	cout<<"17,1,"<<mapId<<","<<pt._x<<","<<pt._y<<endl;
	
	Map_Inform *heroMap = pg_hero->getMap();
	if (heroMap == NULL)
	{
		return;
	}
	
	if (heroMap->getFlgCpy()!=0)				//在副本中,不允许用,返回
	{
		msg_error(g_out_buf,60);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	
	if (pg_hero->getHeroState()==5)				//摆摊中,不允许使用,返回
	{
		msg_error(g_out_buf,71);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	if (heroMap->getMapType()==4)				//阵营战中,无法使用疾行甲马
	{
		msg_error(g_out_buf,73);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	if (heroMap->getWarType()==2)				//PK地图中,无法使用疾行甲马
	{		
		msg_error(g_out_buf,74);
		send_msg(pg_hero->getFd(),g_out_buf);
		return;
	}
	char wagonId[40]={'\0'};
	strncpy(wagonId,pg_hero->memHero->wagonId,sizeof(wagonId));
	if (strlen(wagonId) != 0)				//拉马车中,不许用,返回
	{
		return;
	}
	
	
	Map_Inform *mapInst = NULL;
	map<string, Map_Inform*>::iterator iter_map = mapId_connect_map.find(mapId);
	if(iter_map == mapId_connect_map.end())  //Ordinary duplicate scene not find the mapId；
	{
	   return;
	}
	mapInst = iter_map->second;
	if (mapInst==NULL)						//地图指针错误,返回
	{
		return;
	}
	
	
	int digst=mapInst->getBaseDigst();
	Point temp=MapExchangeLogical(pt);
	Point logPoint;
	logPoint._x=temp._x;
	logPoint._y=temp._y+digst;
		
	//判断是否是障碍点.若是则重新随即
	int number=random_number(0,3);
	if (number==0)
	{
		logPoint._x++;
	}
	else if (number==1)
	{
		logPoint._y++;
	}
	else if (number==2)
	{
		logPoint._y++;
		logPoint._x++;
	}
	else if (number==3)
	{
		logPoint._x--;
		logPoint._y++;
	}
	else if (number==4)
	{
		logPoint._x--;
	}
	
	if (!mapInst->judgeLogPtHind(logPoint))
	{
		logPoint._x=temp._x;
		logPoint._y=temp._y+digst;
		if (!mapInst->judgeLogPtHind(logPoint))
		{
			cout<<"jolly:this point is hind point in dropgoods 382"<<endl;
			msg_error(g_out_buf,100);
			return;
		}		
	}
	
	map<string,Map_Inform*>::iterator iter = mapId_connect_map.find(mapId);
	if(iter == mapId_connect_map.end())  //Ordinary duplicate scene not find the mapId；
	{
	   cout<<"in the jumpId_to changeSence.cpp can't find the nextMapId:"<<mapId<<endl;
	   snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,CHANGE_SCENE,FAILED);
	   send_msg(sock_fd, g_out_buf);
	   return;
	}
	Map_Inform *map_next = iter->second;
	
	if (pg_hero->isInCampResWar())
	{
	   snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,CHANGE_SCENE,5);
	   send_msg(pg_hero->getFd(),g_out_buf);
	   return;
	}
	
	if (pg_hero->isInGuildWarRoom())
	{
	   snprintf(g_out_buf,sizeof(g_out_buf),"%d,%d,%d",2,CHANGE_SCENE,5);
	   send_msg(pg_hero->getFd(),g_out_buf);
	   return;
	}
	
	gotoNPC(pt,mapInst);
}
