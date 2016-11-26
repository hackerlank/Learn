/*
		文件类型：头文件
		文件名称：user_role_buff.h
		文件作用：buff技能的效果实现
*/

#ifndef USER_ROLE_BUFF
#define USER_ROLE_BUFF
#include"hero.h"
#include"skill.h"
void usebuff(char *buffer);
void herousebuff(Hero *hero,Skill *skill);
void dropbuff(char *buffer);
#endif