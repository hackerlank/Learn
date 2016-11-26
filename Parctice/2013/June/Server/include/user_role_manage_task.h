/*
		文件类型：头文件
		文件名称：user_role_manage_task.h
		文件作用：声明客户端发送给服务器玩家可接任务列表信息方法
		  实现者：Evan
		完成时间：2012.5.17
*/
#ifndef USER_ROLE_MANAGE_TASK
#define USER_ROLE_MANAGE_TASK

#include"command_return_define_data.h"
#include"hero.h"
#include"task.h"
#include<iostream>
#include <arpa/inet.h>
#include <stdlib.h>
using namespace std;

//任务是否可接判断
void taskAction(char *buffer);
//请求玩家任务信息
void taskInfoComm(char *buffer);
//放弃任务
void taskAband(char *buffer);
//放弃任务处理
void dealAbandTask(Hero *hero, char *taskId, bool offlineFlag = false, int flag = 0);
//任务可接验证和发送可接消息
void checkAcceptAndSendMsg(Hero *hero, set<string> taskIdSet, char* canAcc, int flag = 0);
//发送玩家任务信息
void sendHeroTaskInfo(Hero *myHero, int flag);
//重置日常任务
void resetDailyTask(Hero *myHero);

void getTaskChaptRewardComm(char* buffer);

void freshHeroCycleTask(Hero* hero);

void viewHeroCycleTaskInfo(char* buffer);
#endif
