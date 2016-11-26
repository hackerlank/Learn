#include "hero.h"
#include"map_inform.h"
#include "user_role_manage_status.h"
#include"command_other_function_all_over.h"
#include"command_game_fight_manage.h"
#include"command_return_define_data.h"
#include <string>
#include <iostream>
#include<stdlib.h>
#include<map>
using namespace std;
extern map<string, Hero*> heroId_to_pHero;

#include "wholeDefine.h"
extern Hero * pg_hero;
extern int g_msg_len;

void ChangePKstatus(char *buffer)
{//cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	string msg="3";
	msg = msg + intTostring(HERO_FIGHT_STATUS);
	int count=6;                            		//buffer里面真正的参数是从第六个开始的
	char len_arg;     								//参数长度
	
	MSG_BEGIN(buffer, g_msg_len)
	MSG_CHAR(char *hero_id)
	MSG_CHAR_END(char *status)
	int PKstatus = atoi(status);

	Hero *hero = pg_hero;

	if(hero == NULL)
	{	//////cout<<"hero not"<<endl;
		return;
	}

	Map_Inform *map_now;        			
	map_now = hero->getMap();//获取玩家所处地图的实例指针
	if(map_now == NULL)
	{
		cout<<"return from ChangePKstatus::cause map_now is NULL"<<endl;
		return ;
	}
	if(map_now->getChangePkType()==0)
	{
		msg = msg + intTostring(FAILED);
		msg = msg + intTostring(map_now->getWarType());
		send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
		return;
	}
	msg = msg + intTostring(SUCCESS);
	msg = msg + intTostring(PKstatus);
	send_msg(hero->getFd(),const_cast<char*>(msg.c_str()));
	//cout<<"******PK***************************************"<<endl;
	hero->sethero_PK_status(PKstatus);
	heroId_to_pHero[hero_id] = hero;
	//cout<<"PK msg:"<<msg<<endl;
	//cout<<"*********************************************"<<endl;
	
}
/*
判断两个玩家是否能战斗
*/
bool isAttack(Hero *hero,Hero *hiter)
{
	
	string teamId_hero = hero->getTeamerId();//攻击者队伍
	int     camp_hero = hero->getCamp();//攻击者阵营
	string  guildName_hero = hero->getGuildName();//攻击者帮派
	int 	PKstatus = hero->gethero_PK_status();//攻击者PK模式状态
	
	string  teamId_hiter = hiter->getTeamerId();//受击者队伍
	int     camp_hiter = hiter->getCamp();//受击者阵营
	string  guildName_hiter = hiter->getGuildName();//受击者帮派
	cout<<"**************************************************"<<endl;
	cout<<"teamId_hero:"<<teamId_hero<<endl;
	cout<<"camp_hero:"<<camp_hero<<endl;
	cout<<"guildName_hero:"<<guildName_hero<<endl;
	cout<<"PKstatus:"<<PKstatus<<endl;
	cout<<"teamId_hiter:"<<teamId_hiter<<endl;
	cout<<"camp_hiter:"<<camp_hiter<<endl;
	cout<<"guildName_hiter:"<<guildName_hiter<<endl;
	cout<<"**************************************************"<<endl;
	switch(PKstatus)
	{
		case 1:
			return false;
			break;
		case 2:
			//自由模式：阵营，帮派可攻击，队伍不可攻击
			if(teamId_hero!="" && teamId_hero==teamId_hiter)
			return false;
			break;
		case 3:
			//阵营模式：阵营，帮派，自己队伍都不可以攻击
			if(teamId_hero!="" && teamId_hero==teamId_hiter)
			return false;
			if(camp_hero!=-1 && camp_hero==camp_hiter)
			return false;
			if(guildName_hero!="" && guildName_hero==guildName_hiter)
			return false;
			break;
		case 4:
			//帮派模式：阵营可攻击；帮派，自己队伍都不可以攻击；
			if(teamId_hero!="" && teamId_hero==teamId_hiter)
			return false;
			if(guildName_hero!="" && guildName_hero==guildName_hiter)
			return false;
			break;
	}
	return true;
	
}
