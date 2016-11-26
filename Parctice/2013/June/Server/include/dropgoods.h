#ifndef DROPGOODS_H
#define DROPGOODS_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <set>
#include "droplist_configuration.h"
#include "monster_configuration.h"
#include "user_role_manage_growup.h"
#include "monsterBase.h"
#include "hero.h"
#include "ointment.h"
#include "pick.h"
#include "map_inform.h"
#include "nbox.h"
#include "team.h"
#include "task.h"
#include "task_goods_info.h"
void dropgoods(char* drop_goods_id,DropList_Configuration *droplist);	
void saveInPick(char* heroId,Map_Inform *dropmap,int loop,char *stage,Point deadPoint,int bound=0,int accountFlag=1);
char* idToName(char* goodsid);
int randompercent(void);
int randomgold(void);
int randomlocation(void);
void getexperience(Hero *hero,MonsterBase* monster);
int getmoney(char* monster_typeid);
void pickgoods(char *buffer);
void send_nbox(Map_Inform *map_now,char* _msg,char* flag);
int monstertype(MonsterBase *hit);
void dropTaskGoods(Hero *attack,MonsterBase *hit);
vector<Point> drop_location(Point monsterPoint,int number,Map_Inform *dropmap);	//掉落位置判定
void send_msg_dropGoods(char* msg,char *flag,Map_Inform *map_now);
bool pick_success(char* goodsid,Hero *hero,char* _msg,char* flag,Team *team);
void pick_failed();
void pickPetToBox(char *buffer);
void killThreeTimer(char* flag);
void killFiveTimer(char* flag);
// void pickTaskGoods(char *buffer);			//added by bison
void collectGoodsComm(char* buffer);		//采集物通信
bool isTeamGoods(Hero *hero,char* killPerson,Team *team);				//判断该物品是不是队伍内的玩家打掉的,若是,则返回true,否则返回false
void initPickTimer(Pick *pick);
void send_error_nbox(Hero *hero,char* _msg);
void boxDropMoney(void);
void pickMoney(char* buffer);
void monsterDropGoods(char *heroId,MonsterBase *monster);			//打怪掉落

//打碎瓶罐掉落
void dropTaskGoods(Hero *attack, Bottle *hit);

#endif