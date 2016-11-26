/*
		文件类型：头文件
		文件名称：command_other_function_user_manage.h
		文件作用：其中包含一些在用户角色管理部分起辅助作用的函数
*/

#ifndef COMMAND_OTHER_FUNCTION_USER_MANAGE
#define COMMAND_OTHER_FUNCTION_USER_MANAGE

#include"data_structure_struct.h"

#include"role.h"

#include"hero.h"

#include"hero_configuration.h"

int checkOut(UserInform &user);      	//对注册用户的合法性进行检查

char* getLocalTime(char *time_string);

bool send_msg(int fd, string &msg_body);

Hero* create_hero(char *nickname);		//创建Hero对象
#endif
