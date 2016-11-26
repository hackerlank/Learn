/*
		文件类型：头文件
		文件名称：command_other_function_user_manage.h
		文件作用：其中包含一些在用户角色管理部分起辅助作用的函数
*/

#ifndef COMMAND_OTHER_FUNCTION_USER_MANAGE
#define COMMAND_OTHER_FUNCTION_USER_MANAGE

#include"data_structure_struct.h"

#include"hero.h"

#include"hero_configuration.h"

int stringToint(string value);

void sendLogMsg(Hero *myHero);   //add chenzhen 5.14 

void revival(char *buffer);		//add jolly 7.12

void onlineReturn(Hero *hero);	//add jolly 10.10

void heroWearEquip(char *buffer);		//add jolly 10.14

void heroWearEquipDestory(char *buffer);		//add jolly 10.14

void showCampSelect(char *buffer);		//add jolly 

void sendRevivalMsg(Hero *hero, int flag);	//复活处理及发送复活消息

#endif
