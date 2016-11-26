#ifndef COMMAND_USER_ROLE_MANAGE_H
#define COMMAND_USER_ROLE_MANAGE_H

#include"role.h"

#define DEFAULT_DB	1				//默认当前测试都是连接1号缓存服务器，待后期由客户端选择 tory

void loginUser(char *buffer);       		//处理登陆命令函数

void login_from_web(char* buffer);			//从web登录

void exit_accident(int sock_fd);           	//处理非命令退出命令函数

void exit_normal(char *buffer);           	//处理命令退出命令函数

void createHero(char *buffer);				//角色创建处理函数

void selectHero(char *buffer);				//角色选择处理函数

void deleteHero(char *buffer);				//删除角色 cookie

void heroLearnSkill(char *buffer);          //角色学习技能

void change_scene(char *buffer);			//场景切换

void closeServerDeal(Hero *myHero);  		//服务器关闭处理

void doneline_operate(char *buffer);		//角色下线；

void temp_guest_change_name(char* buffer);	//更改用户名（仅对临时用户有效）

#endif 
