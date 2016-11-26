/*
		文件类型：头文件
		文件名称：user_role_manage_skill.h
		文件作用：技能处理
		  实现者：Evan
		完成时间：2012.5.17
*/
#ifndef USER_ROLE_MANAGE_SKILL
#define USER_ROLE_MANAGE_SKILL
#include"hero.h"
#include"skill.h"
#include"libev.h"
#include<vector>
void  beidonglearn(Hero *hero,Skill *skill);
void skillupgrade(char *buffer);
void zhudongupgrade(Hero *hero,Skill *skill);
void yiliaoupgrade(Hero *hero,Skill *skill);
void buffupgrade(Hero *hero,Skill *skill);
void beidongupgrade(Hero *hero,Skill *skill);
unsigned int  skillneedexp(int level);
int  skillneedmoney(int hero_grade,int skill_grade,int control_grade);
#endif