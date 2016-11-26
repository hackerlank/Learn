/**
 * 文件名：task_update_status.h
 * 文件描述：定义更新任务状态数据的方法，同时向客户端返回是否更新成功
 * 作者：bison 2012.6.1
 */
 
#include"task_update_status.h"
#include"command_return_define_data.h"
#include"hero.h"
#include"task.h"
#include"task_configuration.h"
#include"monster_configuration.h"
#include<string.h>
#include<iostream>
#include <arpa/inet.h>
#include <stdlib.h>
#include<map>

#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

using namespace std;

extern map<string, Hero*> heroId_to_pHero;
extern map<string,Monster_Inform*>	monTypeId_connect_property;		//怪物配置类
void taskUpdate(char *buffer)
{
	char *heroId;	  //角色Id
	char *taskId;     //任务Id
	int status_type;
	char *status_id;
	int status_value;

	MSG_BEGIN(buff, g_msg_len);
	MSG_CHAR(heroId);
	MSG_CHAR(taskId);
	MSG_INT(status_type);
	MSG_CHAR(status_id);
	MSG_INT(status_value);
	
	Hero *hero = pg_hero;
	Task *task;
	
	string msg_task;
	string msg_head = "5";
	msg_task = msg_task + msg_head + intTostring(TASK_UPDATE_RETURN);
	msg_task = msg_task + "," + taskId; 
	
	task = hero->findAcceptedTaskList(taskId);
	
	if (task == NULL)
	{
		msg_task = msg_task + intTostring(FAILED);     //已接任务列表中没有此任务
		send_msg(hero->getFd(),const_cast<char *>(msg_task.c_str()));
		return ;
	}
#if 0	

	if (status_type == 11)
	{
		string monsterId = status_id;
		map<string,Monster_Inform*>::iterator it_monsterConf;
		it_monsterConf = monTypeId_connect_property.begin();
		if (it_monsterConf == monTypeId_connect_property.end())
		{
			cout<<"BisonTest: update fail becanse monsterId can't find monsterConfInst"<<endl;
			msg_task = msg_task + intTostring(FAILED);     //怪物类型ID错误
			send_msg(hero->getFd(),const_cast<char *>(msg_task.c_str()));
			return ;
		} else {
			Monster_Inform* monConf = it_monsterConf->second;
			int monsterLevel = monConf->getRank();
			int heroLevel = hero->getLevel();
			if (heroLevel + 5 > monsterLevel)
			{
				cout<<"BisonTest: monster level is not OK to update"<<endl;
				msg_task = msg_task + intTostring(FAILED);     //怪物类型ID错误
				send_msg(hero->getFd(),const_cast<char *>(msg_task.c_str()));
				return ;
			} else {
				task->taskUpdate("-1", 1);
			}
		}
	}
#endif

	int updateRet = task->taskUpdate(status_id, status_value);
	if (updateRet == -1)
	{
		msg_task = msg_task + intTostring(FAILED);     //更新任务状态失败
		msg_task += charTostring(status_id);
		msg_task += intTostring(task->getTaskStatusValue(status_id));
		send_msg(hero->getFd(),const_cast<char *>(msg_task.c_str()));
		cout<<"invalid update value"<<endl;
		return;
	} else {
		msg_task = msg_task + intTostring(SUCCESS);     //更新成功
		//msg_task += intTostring(task->getNeedType(status_id));
		msg_task += intTostring(status_type);
		msg_task += charTostring(status_id);
		msg_task += intTostring(status_value);
		send_msg(hero->getFd(),const_cast<char *>(msg_task.c_str()));
		//成功了就要同时更新到memcache
		for(int i = 0; i < 10; i++)
		{
			if (!strcmp(hero->memHero->taskSaveData.acced[i].taskId, taskId))
			{
				hero->memHero->taskSaveData.acced[i].status[updateRet] = status_value;
				//hero->memSet();
			}
		}
	}
}

	