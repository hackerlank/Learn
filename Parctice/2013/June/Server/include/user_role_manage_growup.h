/*
		文件类型：头文件
		文件名称：user_role_manage_growup.h
		文件作用：成长系统处理
		  实现者：Evan
		完成时间：2012.6.13
*/
#ifndef USER_ROLE_MANAGE_GROWUP
#define USER_ROLE_MANAGE_GROWUP
#include"hero.h"
void herogrowup(Hero *hero);
int ratio(int mon);
int exp(int mon);
//打怪经验计算函数，参数r:组队人数，mon:怪物当前等级，role:人物等级
int gExp(int r,int mon,int role);
#endif