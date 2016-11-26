/*
		文件类型：头文件
		文件名称：user_role_accept_task.h
		文件作用：实现解析客户端发送给服务器玩家是否接受任务的方法，并返回给客户端消息
		  实现者：Evan
		完成时间：2012.5.18
*/
#include"user_role_accept_task.h"
#include"command_return_define_data.h"
#include"hero.h"
#include"task.h"
#include"hero_fight.h"
#include"task_configuration.h"
#include"task_touch_configuration.h"
#include<string.h>
#include<iostream>
#include <arpa/inet.h>
#include <stdlib.h>
#include<map>
#include"wagon.h"
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;
using namespace std;

extern map<string,Task_Configuration*> id_to_task; //任务全局变量
extern map<string, Task_Touch_Configuration*> id_to_touch; //任务触发条件
extern map<string, Hero*> heroId_to_pHero;
extern map<string,Wagon*> wagonConfMap;				//马车配置文件
extern map<string, string> heroId_2_colorWagon;		//玩家有彩色马车

//任务配置检查
static int confCheckBeforeAccept(Hero *hero, char* taskId,
	list<recv_t> &upDateInfo, long &taskFlag, bool isGM)
{
	//已接任务数检查
	list<Task*> task_list_accepted;
	task_list_accepted = hero->getAccepted_Task_List();         //获取玩家已接任务列表
	int accepted_list_size = hero->getMaxAcceptedSize();
	if(task_list_accepted.size() >= accepted_list_size)
	{
		cout<<"BisonWarning: Hero can't accept task because hero's MaxAcceptedSize is 10"<<endl;
		return ACCEPT_TASK_ACCEPTED_FULL_ERROR;
	}
	
	//任务ID合法性检查
	map<string,Task_Configuration*>::iterator iter_conf;
	iter_conf = id_to_task.find(taskId);
	if (iter_conf == id_to_task.end())
	{
		cout<<"BisonWarning: Hero can't accept task because of no taskId is"<<taskId<<endl;
		return ACCEPT_TASK_NO_THIS_TASK_ERROR;
	}
	
	Task_Configuration *task_conf;
	task_conf = iter_conf->second;
	
	int taskLevel = task_conf->getTask_level();				//任务接受等级
	int taskType = task_conf->getTask_type();				//任务类型
	int heroLevel = hero->getLevel();						//角色等级
	int camp = hero->getCamp();								//角色阵营
	
	//在已接任务中不能再接
	if (hero->findAcceptedTaskList(taskId) != NULL)
	{
		cout<<"BisonWarning: Hero can't accept task because he has aready accepted it!"<<endl;
		return ACCEPT_TASK_ALREADY_ACCEPT_ERROR;
	}
	
	//此任务已在完成任务列表中
	if (hero->isTaskFinish(taskId))
	{
		if (isGM)
		{
			hero->clrOneFinishTaskMap(taskId);
		} else {
			cout<<"BisonWarning: Hero can't accept task because he has aready finished it!"<<endl;
			return ACCEPT_TASK_ALREADY_FINISH_ERROR;
		}
	}
	
	if (!isGM)
	{
		//为日更新有限制次数的任务
		if (taskType != 1 && taskType != 3)
		{
			//限制次数已达到
			if (hero->dayLmtFindGroup.isOneItemFull(taskId) == 1)
			{
				cout<<"BisonWarning: Hero can't accept task because its reach the limit times!"<<endl;
				return ACCEPT_TASK_TIMES_LIMIT_ERROR;
			}
		}
		
		//等级达不到
		if (taskLevel > heroLevel)
		{
			cout<<"BisonWarning: Hero can't accept task because his level is too low!"<<endl;
			return ACCEPT_TASK_LEVEL_IS_LOW_ERROR;
		}
		
		//等级太高，环任务只能接自己当前等级段的环任务
		if (taskType == 4 && heroLevel - taskLevel >= 10)
		{
			cout<<"BisonWarning: Hero can't accept task because his level is too high!"<<endl;
			return ACCEPT_TASK_LEVEL_IS_HIGH_ERROR;
		}
		
		//帮派任务的触发，要检查玩家是否有帮派
		if (taskType == 2 && hero->getGuildTitle() == -1)
		{
			//玩家没加入帮派
			cout<<"BisonWarning: Hero can't accept task because he hasn't join guild!"<<endl;
			return ACCEPT_TASK_NOT_JOIN_GUILD_ERROR;
		}
		
		//阵营任务在玩家未加入阵营的时候不能触发
		if (taskType == 8 && (camp < 0 || camp > 3))
		{
			cout<<"BisonWarning: Hero can't accept task because he hasn't join camp!"<<endl;
			return ACCEPT_TASK_NOT_JOIN_CAMP_ERROR;
		}
		
		if (taskType == 9)
		{
			int cycleTaskRet = hero->getTaskFinishFlag(taskId);
			if (cycleTaskRet == -1)
			{
				return ACCEPT_TASK_SERVER_CONF_ERROR;
			} else if (cycleTaskRet == 1)
			{
				return ACCEPT_TASK_ALREADY_ACCEPT_ERROR;
			} else if (cycleTaskRet == 2) {
				//循环任务已完成
				return ACCEPT_TASK_ALREADY_FINISH_ERROR;
			}
		}
		
		//检验任务触发条件
		set<touch_t*> touch = task_conf->getTask_touch();
		set<touch_t*>::iterator iter_touch;
		iter_touch = touch.begin();
		
		//没有touch属性就直接跳过不判断
		for (iter_touch; iter_touch != touch.end(); iter_touch++)
		{
			char* preTaskId = (*iter_touch)->pretask;
			if ((*iter_touch)->type == 0)
			{
				//触发类型为前置任务已经完成
				if (!(hero->isTaskFinish(preTaskId)))
				{
					cout<<"BisonWarning: Hero can't accept task because the before task hasn't finished!"<<endl;
					return ACCEPT_TASK_PRE_NOT_FINISH_ERROR;
				}
			}
			else if ((*iter_touch)->type == 1)
			{
				//触发类型为前置任务已接
				if (hero->findAcceptedTaskList(preTaskId) == NULL)
				{
					cout<<"BisonWarning: Hero can't accept task because the before task hasn't accepted!"<<endl;
					return ACCEPT_TASK_PRE_NOT_ACCEPT_ERROR;
					
				}
			}
			else if ((*iter_touch)->type == 2)
			{
				//触发类型为角色为相应阵营
				int needCamp = atoi(preTaskId);
				if (camp != needCamp)
				{
					cout<<"BisonWarning: Hero can't accept task because his camp isn't the camp need!"<<endl;
					return ACCEPT_TASK_NOT_THIS_CAMP_ERROR;
				}
		
			}
		}
		
	}//end of if isGM
	
	//检验任务接受时的recv
	set<recv_t*> recv = task_conf->getTask_recv();
	set<recv_t*>::iterator iter_recv;
	iter_recv = recv.begin();
	for (iter_recv; iter_recv != recv.end(); iter_recv++)
	{
		char* recvId = (*iter_recv)->id;
		int recvNum = (*iter_recv)->num;
		int type = (*iter_recv)->type;
		//接任务时给任务道具
		if (type == 0)
		{
			if (strlen(recvId) == 0 || recvNum < 0)
			{
				cout<<"BisonWarning: can't accept task because the taskConf of "<<taskId<<" is error!"<<endl;
				return ACCEPT_TASK_SERVER_CONF_ERROR;
			}
			
			Bag *bag = hero->getBag();
			int bagremain = bag->remainGridNum();
			if (bagremain < recvNum || recvNum < 0)
			{
				cout<<"BisonWarning: Hero can't accept task because his bag is FULL !"<<endl;
				return ACCEPT_TASK_BAG_IS_FULL_ERROR;
			} else {
				//这里以后不允许接任务失败
				//把任务道具给玩家
				saveGoodsInBag(hero, recvId, recvNum);
				recv_t oneUpdate(COLLECT_TASK_NEED_TYPE, recvId, recvNum);
				upDateInfo.push_back(oneUpdate);
			}
		}
		else if (type == 1)
		{ 
#if 0		
			char* oldWagonId = hero->memHero->wagonId;
			if (strlen(oldWagonId) != 0 || hero->findAcceptedTaskList("task00419") == NULL)
			{
				cout<<"BisonWarning: Hero can't accept task because he has aready accepted it!"<<endl;
				return ACCEPT_TASK_ALREADY_ACCEPT_ERROR;
			}
			//护送帮派镖任务
			map<string, string>::iterator iter_color;
			//检查玩家是否花钱刷出了好马车
			iter_color = heroId_2_colorWagon.find(hero->getIdentity());
			if (iter_color != heroId_2_colorWagon.end())
			{
				recvId = const_cast<char*>(iter_color->second.c_str());
			}
			map<string,Wagon*>::iterator it_wagon;
			it_wagon = wagonConfMap.find(recvId);
			if (it_wagon == wagonConfMap.end())
			{
				cout<<"BisonWarning: can't accept task because the taskConf of "<<taskId<<" is error!"<<endl;	
				cout<<"can't accept because of wagon id can't find a wagon"<<endl;
				return ACCEPT_TASK_SERVER_CONF_ERROR;
			}
			
			Point heroPt = hero->getLocation();
			Point npcPt(6815,3165);
			if (GET_DISTANCE(heroPt, npcPt) > 400)
			{
				cout<<"distance is too far when the hero want to get wagon"<<endl;
				return ACCEPT_TASK_TOO_FAR_ERROR;
			}
			
			//复制个马车出来
			Wagon *srcWagon = it_wagon->second;
			Wagon *myWagon = srcWagon->copyWagon();
			//设置马车主人并在地图上刷出马车
			myWagon->dirveWagon(hero->getIdentity());
			
			//人物下保存马车的实例ID
			char* wagonId = myWagon->getIdentity();
			strncpy(hero->memHero->wagonId, wagonId, strlen(wagonId) + 1);
			cout<<"BisonTell: Now wagon have its owner."<<endl;
#endif
		}
		else if (type == 2)
		{ 
			//护送阵营镖任务
			char* oldWagonId = hero->memHero->wagonId;
			if (strlen(oldWagonId) != 0 || hero->findAcceptedTaskList("task00295") != NULL)
			{
				cout<<"BisonWarning: Hero can't accept task because he has aready accepted it!"<<endl;
				return ACCEPT_TASK_SAME_TYPE_ERROR;
			}
			map<string,Wagon*>::iterator it_wagon;
			it_wagon = wagonConfMap.find(recvId);
			if (it_wagon == wagonConfMap.end())
			{
				cout<<"BisonWarning: can't accept task because the taskConf of "<<taskId<<" is error!"<<endl;	
				cout<<"can't accept because of wagon id can't find a wagon"<<endl;
				return ACCEPT_TASK_SERVER_CONF_ERROR;
			}
			
			//复制个马车出来
			Wagon *srcWagon = it_wagon->second;
			Wagon *myWagon = srcWagon->copyWagon();
			//设置马车主人并在地图上刷出马车
			myWagon->dirveWagon(hero->getIdentity());
			
			//人物下保存马车的实例ID
			char* wagonId = myWagon->getIdentity();
			strncpy(hero->memHero->wagonId, wagonId, strlen(wagonId) + 1);
			cout<<"BisonTell: Now wagon have its owner."<<endl;
		} else if (type == 3)
		{
			Map_Inform* heroMap = hero->getMap();
			if (heroMap == NULL)
			{
				return ACCEPT_TASK_SERVER_CONF_ERROR;
			}
			
			char *npcBossId = heroMap->brushTaskMon(hero, recvId);
			if (npcBossId == NULL)
			{
				cout<<"BisonWarning: can't accept task because brush the NPC boss Error!"<<endl;
				return ACCEPT_TASK_SERVER_CONF_ERROR;
			}
			hero->setTaskNeedKillNpcBossId(npcBossId);
		}
	}
	
	//从这里之后就不会再返回失败
	
	//检查任务的需求
	list<need_t*> need = task_conf->getTask_need();
	list<need_t*>::iterator iter_need;
	iter_need = need.begin();
	for (iter_need; iter_need != need.end(); iter_need++)
	{
		int needType = (*iter_need)->type;
		char* needId = (*iter_need)->id;
		int needNum = (*iter_need)->num;
		
		if (needType == KILL_TASK_NEED_TYPE || needType == KILL_LIMIT_TASK_NEED_TYPE)
		{
			int index = hero->SetInTskStFstTenBit();
			taskFlag |= (1 << index);
		}
		else if (needType == PICKUP_TASK_NEED_TYPE
					|| needType == COLLECT_TASK_NEED_TYPE
					|| needType == TREASURE_MAP_TASK_NEED_TYPE
					|| needType == RESCUE_TASK_NEED_TYPE)
		{
			int index = hero->SetInTskStScdTenBit();
			if (index == -1)
			{	
				cout<<"BisonWarning You Should retreat the taskState scdTen size In Hero for pick"<<endl;
			} else {
				taskFlag |= (1 << index);
			}
		}			
		else if (needType == JOIN_GUILD_TASK_NEED_TYPE)
		{
			if (hero->getGuildTitle() != -1)
			{
				recv_t oneUpdate(JOIN_GUILD_TASK_NEED_TYPE, needId, needNum);
				upDateInfo.push_back(oneUpdate);
			}
			else
			{
				hero->setTskStSomeBit(TASK_NEED_JOIN_GUILD );
				taskFlag |= TASK_NEED_JOIN_GUILD;
			}
		}
		else if (needType == JOIN_CAMP_TASK_NEED_TYPE)
		{	
			hero->setTskStSomeBit(TASK_NEED_JOIN_CAMP);
			taskFlag |= TASK_NEED_JOIN_CAMP;
			if (camp >= 0 && camp < 3)
			{
				recv_t oneUpdate(JOIN_CAMP_TASK_NEED_TYPE, needId, needNum);
				upDateInfo.push_back(oneUpdate);
			}
		}
		else if (needType == EQUIP_CUILI_TASK_NEED_TYPE)
		{
			hero->setTskStSomeBit(TASK_NEED_FIRST_CUILI);
			taskFlag |= TASK_NEED_FIRST_CUILI;
			
		}
		else if (needType == EQUIP_JINGLIAN_TASK_NEED_TYPE)
		{
			hero->setTskStSomeBit(TASK_NEED_FIRST_JINGLIAN);
			taskFlag |= TASK_NEED_FIRST_JINGLIAN;
		}
		else if (needType == BUY_EQUIP_TASK_NEED_TYPE)
		{
			hero->setTskStSomeBit(TASK_NEED_BUY_EQUIP);
			taskFlag |= TASK_NEED_BUY_EQUIP;
		}
		else if (needType == BUY_DAOJU_TASK_NEED_TYPE)
		{
			hero->setTskStSomeBit(TASK_NEED_BUY_DAOJU);
			taskFlag |= TASK_NEED_BUY_DAOJU;
		}
		else if (needType == PK_OTHER_HERO_TASK_NEED_TYPE)
		{
			hero->setTskStSomeBit(TASK_NEED_PK_HERO);
			taskFlag |= TASK_NEED_PK_HERO;
		}
		else if (needType == PASS_ECTYPE_TASK_NEED_TYPE)
		{
			if (hero->getCpyRecord()->isPassCpy(needId))
			{
				recv_t oneUpdate(PASS_ECTYPE_TASK_NEED_TYPE, needId, needNum);
				upDateInfo.push_back(oneUpdate);
			}
			else
			{
				hero->setTskStSomeBit(TASK_NEED_PASS_ECTYPE );
				taskFlag |= TASK_NEED_PASS_ECTYPE;
			}
		}
		else if (needType == KILL_NPC_BOSS_TASK_NEED_TYPE)
		{
			hero->setTskStSomeBit(TASK_NEED_KILL_NPC_BOSS);
			taskFlag |= TASK_NEED_KILL_NPC_BOSS;
		}
		
		else if (needType == PASS_TOWER_LAYER_TASK_NEED_TYPE)
		{
			if (hero->isPassTowerLayer(needId))
			{
				recv_t oneUpdate(PASS_TOWER_LAYER_TASK_NEED_TYPE, needId, needNum);
				upDateInfo.push_back(oneUpdate);
			} else {				
				hero->setTskStSomeBit(TASK_NEED_PASS_TOWER_LAYER);
				taskFlag |= TASK_NEED_PASS_TOWER_LAYER;
			}
		}
		
	}
	
	//任务配置检查成功
	return 0;
}

static void taskAcceptManage(Hero *hero, char* taskId, bool isGM);

void taskAccept(char *buff)
{
	char *heroId;	  //角色Id
	char *taskId;     //任务Id
	char *NPCId;      //玩家交任务的NPCId 
	
	
	MSG_BEGIN(buff, g_msg_len);
	MSG_CHAR(heroId);
	MSG_CHAR(taskId);
	MSG_CHAR_END(NPCId);
	Hero *hero = pg_hero;
	
	taskAcceptManage(hero, taskId, false);
}

void GM_accept_one_task(char *buffer)
{
	// char len_arg = buffer[0];     //参数长度
	// buffer[len_arg + 1] = 0;
	// cout<<"Gm accept task id buffer is "<<buffer<<endl;
	Hero *hero = pg_hero;
	taskAcceptManage(hero, buffer, true);
}

static void taskAcceptManage(Hero *hero, char* taskId, bool isGM)
{	
	char msg_task[64];
	// string msg_head = "5";
	// msg_task = msg_task + msg_head + intTostring(TASK_ACCEPT_RETURN);
	
	// msg_task = msg_task + "," + taskId; 
	
	Task *task;
	Task_Configuration *task_conf;
	
	list<recv_t> updateInfo;
	long taskFlag = 0;
	//任务配置检查
	int confCheckResult = confCheckBeforeAccept(hero, taskId, updateInfo, taskFlag, isGM);
	
	
	cout<<"BisonShow accept task return is "<<confCheckResult<<endl;
	//检查结果为不可接
	if (confCheckResult != 0)
	{
		// msg_task = msg_task + intTostring(FAILED); 
		// msg_task += intTostring(confCheckResult);
		sprintf(msg_task, "5,%d,%s,0,%d", TASK_ACCEPT_RETURN, taskId, confCheckResult);
		send_msg(hero->getFd(),msg_task);
		
		cout<<"BisonWarning: Hero can't accept task because of taskConf check failed!"<<endl;
		if (updateInfo.size() != 0)
		{
			cout<<"BisonWarn you to check task.xml!"<<endl;
			updateInfo.clear();
		}
		return ;
	}
	
	//任务配置检查成功，对其进行实例化
	map<string,Task_Configuration*>::iterator iter_conf;
	iter_conf = id_to_task.find(taskId);
	if (iter_conf == id_to_task.end())
	{
		cout<<"Fuck the world!!!!!!!!!!!!!!"<<endl;
		return;
	}
	
	task_conf = iter_conf->second;
	task = new Task(task_conf);
	//把任务放到玩家的已接列表，有上面的严格检查，后面不检查返回值也不会添加失败
	int testReturn = hero->incAcceptedTaskList(task);
	TaskData_T taskData = task->initTaskData();
	for (int i = 0; i < 10; i++)
	{
		//从memcache需要保存的已接任务的结构体数组中找到未使用的位来使用
		if (hero->memHero->taskSaveData.acced[i].taskFlag == -1)
		{
			hero->memHero->taskSaveData.acced[i] = taskData;
			hero->memHero->taskSaveData.acced[i].taskFlag = taskFlag;
			//hero->memSet();
			break;
		}
	}
	
	int taskType = task->getTaskType();
	
	//不是主线和支线任务，就有可能是日限制次数的任务
	if (taskType != 1 && taskType != 3)
	{
		//把已接次数加1
		int index = hero->dayLmtFindGroup.incOneItem(taskId);
		if (index != -1)
		{
			//更新到memcached保存数据
			hero->memHero->dayLmtItemArr[index].incVal();
		}
	}
	
	if (taskType == 9)
	{
		hero->setCycleTaskAccepted(taskId);
	}
	
	//循环任务，如果是循环任务的主任务，就把该任务的子任务之前的完成状态都清掉
	if (task->getTaskType() == 4)
	{
		char sonTaskIdSet[100];
		memset(sonTaskIdSet, 0, sizeof(sonTaskIdSet));
		task->getSpecialNeedId(20, sonTaskIdSet);
		cout<<"BisonTest: sonTaskIdSet is "<<sonTaskIdSet<<endl;
		if(strlen(sonTaskIdSet) != 0)
		{
			char *temp = sonTaskIdSet;
			int len = strlen(temp);
			int pos = 0;
			char sonTaskId[150] = {0};
			while(len > 0)
			{
				pos = findChar(temp, ',', len);
				if (pos == -1)
				{
					strncpy(sonTaskId, temp, len + 1);
					temp = temp + len;
				} else {
					sub_str(sonTaskId, temp, 0, pos);
					temp = temp + pos + 1;
				}
				
				len = strlen(temp);
				
				cout<<"BisonTest sonTask Id is "<<sonTaskId<<endl;
				//清除子任务的完成状态，不论状态是否为已完成
				hero->clrOneFinishTaskMap(sonTaskId);
			}
		}
	}
	
	//通知客户端，任务接受成功
	// msg_task = msg_task + intTostring(SUCCESS); 
	sprintf(msg_task, "5,%d,%s,1", TASK_ACCEPT_RETURN, taskId);
	send_msg(hero->getFd(),msg_task);
	
	//对前面压着的数据处理
	if (updateInfo.size() != 0)
	{ 
		list<recv_t>::iterator it_update;
		for (it_update = updateInfo.begin(); it_update != updateInfo.end(); it_update++)
		{
			recv_t *oneUpdate = &(*it_update);
			hero->updateHeroTaskStatus(oneUpdate->type, oneUpdate->id, oneUpdate->num);
		}
	}
}