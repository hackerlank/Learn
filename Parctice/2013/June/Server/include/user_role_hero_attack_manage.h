/*
		文件类型：头文件
		文件名称：user_role_hero_attack_manage.h
		文件作用：玩家角色在战斗时使用技能调用的技能方法
*/

#ifndef USER_ROLE_HERO_ATTACK_MANAGE
#define USER_ROLE_HERO_ATTACK_MANAGE
#include"hero.h"
#include"skill.h"
int general_attack(Hero *attack,Hero *hited,Skill *skill);
int oneToone_attack(Hero *attack,Hero *hited,Skill *skill);
#endif