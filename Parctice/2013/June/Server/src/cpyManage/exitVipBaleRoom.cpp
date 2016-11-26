/************************************************************
    文件名：exitVipBaleRoom.cpp
    文件作用：退出vip包间函数
    作者：chenzhen
    创建日期：2012.12.14
************************************************************/
#include"entCpy.h"
#include"cpyAsist.h"
#include"vipBaleRoomLimit.h"
#include "instancing_manage.h"
#include"map_src.h"
extern int g_msg_len;
extern Hero* pg_hero;
void exitVipBaleRoom(char *buffer)
{
	vector<string> herIdVec;
	Map_Src *mapNow;
	char *heroId;
	Hero *myHero;
	
	myHero = pg_hero;
	
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(heroId);			
	herIdVec.push_back(heroId);	
	
	if(heroId == NULL || strlen(heroId) == 0)
	{
		cout<<"the heroId is NULL:"<<endl;
		return;
	}
	
	mapNow = (Map_Src*)(myHero->getMap());
	
	mapNow->exitVipRoom(herIdVec);
}