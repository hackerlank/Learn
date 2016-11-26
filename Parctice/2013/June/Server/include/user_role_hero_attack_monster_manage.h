/*
		文件类型：头文件
		文件名称：user_role_hero_attack_manage.h
		文件作用：玩家角色在战斗时使用技能调用的技能方法
*/

#ifndef USER_ROLE_HERO_ATTACK_MANAGE
#define USER_ROLE_HERO_ATTACK_MANAGE
#include"hero.h"
#include"monsterBase.h"
#include"skill.h"
#include"dropgoods.h"
int general_attack_monster(Hero *attack,MonsterBase *hited,Skill *skill);

int heroTomonster_attack(Hero *attack,MonsterBase *hited,Skill *skill);

int hq(int _dj,int _rdj);			//经验值掉落计算公式,cookie实现
#endif