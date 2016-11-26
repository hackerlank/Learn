/*
		文件类型：头文件
		文件名称：user_role_zhudong.h
		文件作用：主动攻击技能的效果实现
*/

#ifndef USER_ROLE_ZHUDONG
#define USER_ROLE_ZHUDONG
#include"hero.h"
#include"skill.h"
#include"monsterBase.h"
int heroVShero(Hero *hero,Hero *hited,Skill *skill);
int heroVSmonster(Hero *attack,MonsterBase *hited,Skill *skill);
#endif