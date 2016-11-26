/*
		文件类型：头文件
		
		文件名称：game_fight_assist.h
		
		文件作用：在游戏打斗部分起辅助作用的函数的定义
*/

#ifndef COMMAND_OTHER_FUNCTION_GAME_FIGHT_H
#define COMMAND_OTHER_FUNCTION_GAME_FIGHT_H

#include"libev.h"

#include"data_structure_struct.h"

#include"monsterBase.h"

#include"hero.h"

#include"skill.h"

class MonsterBase;

class Hero;        //by chenzhen 4.23

class Skill;

int attackRangePoint(Point pt_attack,Point pt_hited,int attack_range);  //判断攻击者与被攻击者之间的距离是否合法

void send_success(Hero *attack,Hero *hited,Skill *skill,int redlose);//攻击玩家成功给client发送消息

void attack_monster_success(Hero *attack,MonsterBase *hited,Skill *skill,int redlose);//攻击怪物成功发给client消息
#endif
