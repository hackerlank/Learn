/*
		文件类型：头文件
		文件名称：user_role_manage_task.h
		文件作用：客户端发送给服务器玩家可接任务列表信息方法实现
		  实现者：Evan
		完成时间：2012.5.17
*/

#include"user_role_manage_task.h"
#include"wagon.h"
#include"wholeDefine.h"
extern int sock_fd;
extern map<string,Task_Configuration*> id_to_task; //任务全局变量   Evan add
extern set<string> guildTaskList;			//帮派任务列表
extern set<string> dayTaskList;				//日常任务
extern set<string> campTaskList;			//阵营任务
extern set<string> allCycleTaskList;				//循环任务集合
extern map<string,Wagon*> wagonInstMap;						//马车实例

//added by benliao
extern int g_msg_len; 
extern Hero* pg_hero; 

void taskAction(char *buffer)
{	
	char *heroId;	  		//玩家Id
	int  task_num = 0;    	//玩家可接任务数
	char *taskId;     		//任务Id
	set<string> task_list;	//任务列表
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR(heroId);
	
	/*解析玩家可接任务数*/
	MSG_INT(task_num);
	
	if (task_num > 100)
	{
		return;
	}
	for(int i=0;i<task_num - 1;i++)
	{
		MSG_CHAR(taskId);
		task_list.insert(taskId);
	}
	
	char canAcc[1024] = {0};
	checkAcceptAndSendMsg(pg_hero, task_list, canAcc, 0);

}

void checkAcceptAndSendMsg(Hero *hero, set<string> taskIdSet, char* canAcc, int flag)
{
	/* 验证客户端发来的可接任务id是否确实可接，沿用命令51 */
	// string task_msg_head = "5";                //消息头
	/* 发送可接任务信息 */
	char taskAcceptMsg[2000] = {0};
	// char msgTemp[2000] = {0};
	int checkAcceptOK = 0;                      //验证成功的数量
	//信息头
	// taskAcceptMsg = task_msg_head + intTostring(TASK_LOGIN_NOACCEPT_RETURN);
	
	char taskId[10] = {0};
	set<string>::iterator it_taskId;
	//cout<<"BisonTest: 11111111111111111111111111111111"<<endl;
	for(it_taskId = taskIdSet.begin(); it_taskId != taskIdSet.end(); it_taskId++)
	{
		strncpy(taskId, (*it_taskId).c_str(), 10);

		map<string,Task_Configuration*>::iterator iter_conf;
		iter_conf = id_to_task.find(taskId);
#if 1		
		//如果该任务已接完成过，就不再可接，至少对主线任务是如此
		if (hero->isTaskFinish(taskId))
		{
			//cout<<"BisonTest: 222222222222222222222222222222"<<endl;
			continue;
		}
		if (hero->findAcceptedTaskList(taskId) != NULL)
		{
			continue;
		}
#endif	
	
		if (iter_conf == id_to_task.end())
		{
			//配置中没有此任务信息
			//跳过以下内容
			continue;
		}
		Task_Configuration *task_conf;
		task_conf = iter_conf->second;
		
		// 判断等级是否足够
		int level = task_conf->getTask_level();
		
		if (level > hero->getLevel())
		{
			//等级达不到
			//cout<<"BisonTest: 2222222222222222222222222222"<<endl;
			continue;
		} else if (task_conf->getTask_type() == 4 && hero->getLevel() - level >= 10)
		{
			//循环任务只接受当前等级可接的
			continue;
		} else if (task_conf->getTask_type() == 2 && hero->getGuildTitle() == -1) {
			//帮派任务的触发，要检查玩家是否有帮派
			cout<<"BisonWarning: hero can't accept guildTask when he doesn't join guild!"<<endl;
			continue;
		} else if (task_conf->getTask_type() == 9)
		{
			continue;
		}
		
		//检验任务触发条件
		set<touch_t*> touch = task_conf->getTask_touch();
		set<touch_t*>::iterator iter_touch;
		iter_touch = touch.begin();
		
		//没有touch属性就直接跳过不判断
		bool  touchFlag = true;
		//玩家阵营
		int camp = hero->getCamp();
		for (iter_touch; iter_touch != touch.end(); iter_touch++)
		{
			char* preTaskId = (*iter_touch)->pretask;
			if ((*iter_touch)->type == 0)
			{
				//触发类型为前置任务已经完成
				if (!(hero->isTaskFinish(preTaskId)))
				{
				
					//前置任务没完成
					touchFlag = false;
					//cout<<"BisonTest: 333333333333333333333333333333"<<endl;
					break;
				}
			} else if ((*iter_touch)->type == 1)
			{
				//触发类型为前置任务已接
				if (hero->findAcceptedTaskList(preTaskId) == NULL)
				{
					touchFlag = false;
					//cout<<"BisonTest: the pretask hasn't been accepted!"<<endl;
					break;
				}
			} else if ((*iter_touch)->type == 2)
			{
				//触发类型为加入阵营--即阵营任务
				if (camp < 0 || camp > 2)
				{
					//玩家没加入阵营不能接
					touchFlag = false;
				} else {
					int needCamp = atoi(preTaskId);
					if (camp != needCamp)
					{
						//不是本阵营的阵营任务
						touchFlag = false;
					}
				}
			}
		}
		
		if (!touchFlag)
		{
			//cout<<"BisonTest: 44444444444444444444444444444444"<<endl;
			continue;
		}

		//cout<<"BisonTest: 666666666666666666666666666"<<endl;
		//任务状态置为可接
		checkAcceptOK++;
		// msgTemp += "," + taskId;
		sprintf(canAcc +strlen(canAcc), ",%s", taskId);
	}

	// taskAcceptMsg += intTostring(checkAcceptOK);
	// taskAcceptMsg += msgTemp;
	sprintf(taskAcceptMsg, "5,%d,%d,%s", TASK_LOGIN_NOACCEPT_RETURN, checkAcceptOK, canAcc);
	if (flag == 0)
	{
		send_msg(hero->getFd(), taskAcceptMsg);
	}
	// return msgTemp;
	
}

//请求玩家任务信息
void taskInfoComm(char *buffer)
{
	sendHeroTaskInfo(pg_hero, 0);
}

//日常任务重置
void resetDailyTask(Hero *myHero)
{
	//把已接的日更新的任务清除
	list<Task*> map_task = myHero->getAccepted_Task_List();
	list<Task*>::iterator task_it;
	for (task_it = map_task.begin(); task_it != map_task.end(); task_it++)
	{
		Task* task = (*task_it);
		//日常任务
		char* taskId = task ->getTaskId();
		if (dayTaskList.find(taskId) != dayTaskList.end())
		{
			//在hero的已接列表中删除掉
			myHero->delAcceptedTaskList(taskId);
			delete task;
			continue;
		}
		//帮派任务也要清
		if (guildTaskList.find(taskId) != guildTaskList.end())
		{
			//删除帮派任务
			myHero->delAcceptedTaskList(taskId);
			delete task;
			continue;
		}
		//阵营任务
		if (campTaskList.find(taskId) != campTaskList.end())
		{
			//删除阵营任务
			myHero->delAcceptedTaskList(taskId);
			delete task;
			continue;
		}
		//每日循环也清掉
		if (task->getTaskType() == 9)
		{
			myHero->delAcceptedTaskList(taskId);
			delete task;
			continue;
		}
	}
	
	//把已完成的日可接任务位图重置
	//根据已经完成位图直接置位
	//myHero->clrDayTaskFinishMap();
	set<string>::iterator it_task;
	//非今天完成的日常任务
	for (it_task = dayTaskList.begin(); it_task != dayTaskList.end(); it_task++)
	{
		// char* taskId = (*it_task);
		myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
	}
	//非今天完成的帮派任务
	for (it_task = guildTaskList.begin(); it_task != guildTaskList.end(); it_task++)
	{
		// string taskId = (*it_task);
		myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
	}
	//非今天完成的阵营任务
	for (it_task = campTaskList.begin(); it_task != campTaskList.end(); it_task++)
	{
		// string taskId = (*it_task);
		myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
	}
	//每日循环任务
	for (it_task = allCycleTaskList.begin(); it_task != allCycleTaskList.end(); it_task++)
	{
		// string taskId = (*it_task);
		myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
	}
}


//发送玩家任务信息,flag = 1表示0:00没下线的玩家
void sendHeroTaskInfo(Hero *myHero, int flag)
{
	char taskInfoMsg[16000] = {0};
	//信息头
	// taskInfoMsg = task_msg_head + intTostring(TASK_INFO_APPLY_RETURN);
#if 0	
	if (flag == 1 || myHero->isFirstLogin())
	{
		cout<<"BisonShow: It is his first time of log in today!"<<endl;
		//把已接的日更新的任务清除
		list<Task*> map_task = myHero->getAccepted_Task_List();
		list<Task*>::iterator task_it;
		for (task_it = map_task.begin(); task_it != map_task.end(); task_it++)
		{
			Task* task = (*task_it);
			//日常任务
			char* taskId = task ->getTaskId();
			if (dayTaskList.find(taskId) != dayTaskList.end())
			{
				//在hero的已接列表中删除掉
				myHero->delAcceptedTaskList(taskId);
				delete task;
			}
			//帮派任务也要清
			if (guildTaskList.find(taskId) != guildTaskList.end())
			{
				//删除帮派任务
				myHero->delAcceptedTaskList(taskId);
				delete task;
			}
			//阵营任务
			if (campTaskList.find(taskId) != campTaskList.end())
			{
				//删除阵营任务
				myHero->delAcceptedTaskList(taskId);
				delete task;
			}
		}
		
		//把已完成的日可接任务位图重置
		//根据已经完成位图直接置位
		//myHero->clrDayTaskFinishMap();
		set<string>::iterator it_task;
		//非今天完成的日常任务
		for (it_task = dayTaskList.begin(); it_task != dayTaskList.end(); it_task++)
		{
			// char* taskId = (*it_task);
			myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
		}
		//非今天完成的帮派任务
		for (it_task = guildTaskList.begin(); it_task != guildTaskList.end(); it_task++)
		{
			// string taskId = (*it_task);
			myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
		}
		//非今天完成的阵营任务
		for (it_task = campTaskList.begin(); it_task != campTaskList.end(); it_task++)
		{
			// string taskId = (*it_task);
			myHero->clrOneFinishTaskMap(const_cast<char*>((*it_task).c_str()));
		}
		
	}
#endif

	//发送已完成任务位图
	// taskInfoMsg += intTostring(sizeof(myHero->finishTaskMap) / sizeof(int));
	sprintf(taskInfoMsg, "5,%d,%d", TASK_INFO_APPLY_RETURN, int(sizeof(myHero->finishTaskMap) / sizeof(int)));
	for (int i = 0; i < MAX_TASK_MAP_SIZE; i++)
	{
		// taskInfoMsg += intTostring(myHero->finishTaskMap[i]);
		sprintf(taskInfoMsg + strlen(taskInfoMsg), ",%d", myHero->finishTaskMap[i]);
	}
	
	// 发送已接任务的信息
	list<Task*> acceptedTaskList = myHero->getAccepted_Task_List();
	int task_size = acceptedTaskList.size();
	// taskInfoMsg += intTostring(task_size);
	sprintf(taskInfoMsg + strlen(taskInfoMsg), ",%d", task_size);
	list<Task*>::iterator iter_tasks;
	iter_tasks = acceptedTaskList.begin();
	for(iter_tasks; iter_tasks != acceptedTaskList.end(); iter_tasks++)
	{
		Task *acceptedTask;
		acceptedTask = (*iter_tasks);
		// string msgTemp;
		// msgTemp = msgTemp + acceptedTask->getTaskId();
		sprintf(taskInfoMsg + strlen(taskInfoMsg), ",%s", acceptedTask->getTaskId());
		//状态数据发送
		//cout<<"Come here by bison."<<endl;
		list<taskStatus_T*> status = acceptedTask->getTaskStatus();
		list<taskStatus_T*>::iterator iter_status;
		iter_status = status.begin();
		int needType; 
		char* needId;
		int statusVal;
		for (iter_status; iter_status != status.end(); iter_status++)
		{
			needType = (*iter_status)->type;
			needId = (*iter_status)->id;
			statusVal = (*iter_status)->value;
			if (needType == 6)
			{
				//坐标点验证的类型,客户端不需要处理但是服务器要处理，所以给客户端的数据改成-1
				statusVal = -1;
			}
			// msgTemp += ";" + itos(needType) + 
					   // ";" + needId +
					   // ";" + itos(statusVal);
					   
			sprintf(taskInfoMsg + strlen(taskInfoMsg), ";%d;%s;%d", 
				needType, needId, statusVal);
		}
		
		// taskInfoMsg += "," + msgTemp;
		// msgTemp = "";
	}
	
	int chaptSize = chapt_2_taskReward.size();
	for (int i = 0; i < chaptSize; i++)
	{
		sprintf(taskInfoMsg + strlen(taskInfoMsg), ",%d", myHero->isTaskChaptReward(i + 1));
	}
	send_msg(myHero->getFd(), taskInfoMsg);
	// char isPassChaptMsg[1024] = {0};
	// sprintf(isPassChaptMsg, "5,41");
	// for (int i = 0; i < chaptSize; i++)
	// {
		// sprintf(isPassChaptMsg + strlen(isPassChaptMsg), ",%d", myHero->isChaptTaskPass(i + 1));
	// }
	// send_msg(myHero->getFd(), isPassChaptMsg);

}

void taskAband(char *buffer)
{
	char *taskId = NULL;
	MSG_BEGIN(buffer, g_msg_len);
	MSG_CHAR_END(taskId);
	dealAbandTask(pg_hero, taskId, false, 1);
}

void dealAbandTask(Hero *hero, char *taskId, bool offlineFlag, int flag)
{
	cout<<"aband task's taskId is:"<<taskId<<endl;
	char msg[400] = {0};
	Task* task = NULL;
	task = hero->findAcceptedTaskList(taskId);
	if (task == NULL)
	{
		if (!offlineFlag)
		{
			// msg = msg + intTostring(SUCCESS);     //已接任务列表中没有此任务
			sprintf(msg, "5,4,1");
			send_msg(hero->getFd(),msg);
		}
		return ;
	}
	
	if (!strcmp(taskId, "task00295") || !strcmp(taskId, "task00419")) 
	{
		map<string,Wagon*>::iterator it_wagon;
		//cout<<"BisonTest：wagonInstMap size is "<<wagonInstMap.size()<<endl;
		it_wagon = wagonInstMap.find(hero->memHero->wagonId);
		if (it_wagon != wagonInstMap.end())
		{
			Wagon *wagon = it_wagon->second;
			//向九宫格发马车死亡消息
			wagon->disperMsg();
			//hero的马车没有了
			//strncpy(hero->memHero->wagonId, "\0", 2);		
			memset(hero->memHero->wagonId, 0, sizeof(hero->memHero->wagonId));
			wagonInstMap.erase(wagonInstMap.find(wagon->getId()));
			
			delete wagon;
		}
	}
	//memcache中delete掉它
	hero->delAcceptedTaskList(taskId);
	if (task->getTaskType() != 1 && task->getTaskType() != 3)
	{
		hero->setFinishTaskMap(taskId);
	}
	//本任务涉及的任务道具都要回收
	char* needRecycleGoods = task->getTaskGoods();
	if (needRecycleGoods != NULL)
	// if (needRecycleGoods.size() != 0)
	{
		useAllGoods(hero, needRecycleGoods);
	}
	
	bool canAcceptAgain = false; 
	int taskType = task->getTaskType();
	//主线或者支线任务
	if (taskType == 1 || taskType == 3)
	{
		canAcceptAgain = true;
	}
	
	//不是主线也不是支线
	else//if (taskType != 1 && taskType != 3)
	{
		if (hero->dayLmtFindGroup.isOneItemFull(taskId) != 1)
		{
			canAcceptAgain = true;
		}
		
	}
	
	if (!offlineFlag)
	{
		sprintf(msg, "5,4,1,%s,%d", taskId, canAcceptAgain);
		send_msg(sock_fd, msg);
	}	
	
#if 0   //多级任务现在没有了
	else if (task->getTaskType() == 4)
	{
		//日常任务之多级任务之主任务放弃
		//顺带清除子任务
		//只有多级任务之主任务的needType 才会为20
		string sonTaskIdSet = task->getSpecialNeedId(20);
		cout<<"BisonTest: sonTaskIdSet is "<<sonTaskIdSet<<endl;
		if(sonTaskIdSet.size() != 0)
		{
			while(sonTaskIdSet.size() != 0)
			{
				string sonTaskId;
				int pos = sonTaskIdSet.find(",");
				if (pos == -1)
				{
					sonTaskId = sonTaskIdSet;
					sonTaskIdSet = "";
				} else {
					sonTaskId = sonTaskIdSet.substr(0, pos);
					sonTaskIdSet = sonTaskIdSet.substr(pos + 1);
				}
				cout<<"BisonTest sonTask Id is "<<sonTaskId<<endl;
				Task *sonTask = NULL;
				sonTask = hero->delAcceptedTaskList(sonTaskId);
				if(sonTask){//by benliao 20121124	
					hero->clrOneFinishTaskMap(sonTaskId);
				}
				string aband_msg = msg_head + intTostring(TASK_ABAND_RETURN) + intTostring(SUCCESS);
				aband_msg += "," + sonTaskId;
				send_msg(sock_fd, aband_msg);
				cout<<"Have send aband son Task"<<endl;
				if (sonTask != NULL)
				{
					delete sonTask;
				}
			}
		} else {	
		
		}
	}
#endif	
	if (flag == 1 && task->getSubType() == 1)
	{
		char* npcBossId = hero->getTaskNeedKillNpcBossId();
		if (strlen(npcBossId) != 0)
		{
			Map_Inform* heroMap = hero->getMap();
			MonsterBase* mon = heroMap->getMonsterObj(npcBossId);
			if (mon != NULL && mon->getIsUsed())
			{
				mon->taskMonCalBack();
			}
			hero->setTaskNeedKillNpcBossId(NULL);
		}
	}
	delete task;
}

void getTaskChaptRewardComm(char *buffer)
{
	int chapt = 0;
	char msg[128] = {0};
	MSG_BEGIN(buffer, g_msg_len);
	MSG_INT(chapt);
	int ret = pg_hero->getTaskChaptReward(chapt);
	if (ret != 0)
	{
		sprintf(msg, "5,9,0,%d", ret);
	} else {
		sprintf(msg,"5,9,1,%d", chapt);
	}
	send_msg(pg_hero->getFd(), msg);
}

void freshHeroCycleTask(Hero* hero)
{
	if (hero == 0)
	{
		return;
	}
	
	int level = hero->getLevel();
	
	int cycleLevel = level - (level % 10);
	map<int, vector<string> >::iterator it_set = levelCycleTaskSet.find(cycleLevel);
	if (it_set == levelCycleTaskSet.end())
	{
		return;
	}
	
	vector<string> *pCycleTaskLevelSet = &it_set->second;
	int sizeOfThisLevelSet = pCycleTaskLevelSet->size();
	set<int> rankNumSet;
	while (rankNumSet.size() != 10)
	{
		rankNumSet.insert(rand() % sizeOfThisLevelSet);
	}
	
	set<int>::iterator it_index = rankNumSet.begin();
	int i = 0;
	for (;it_index != rankNumSet.end(); it_index++)
	{
		cout<<"[freshCycleTask] rank num["<<i<<"] is "<<*it_index<<endl;
		hero->setOneCycleTask(i++, const_cast<char*>((*pCycleTaskLevelSet)[*it_index].c_str()));
	}
}


void viewHeroCycleTaskInfo(char* buffer)
{
	pg_hero->viewCycleTaskInfo();
}