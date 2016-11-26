/*
		文件类型：头文件
		文件名称：user_role_manage_task.h
		文件作用：声明客户端发送给服务器玩家是否完成任务信息
		  实现者：Evan 
		完成时间：2012.5.18
*/
#include"user_role_finish_task.h"
#include"command_return_define_data.h"
#include"hero.h"
#include"task.h"
#include"task_configuration.h"
#include<string.h>
#include<iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include"command_other_function_all_over.h"
#include<map>
#include"pet_config.h"
#include"pet.h"
#include"pet_box.h"
#include"wagon.h"
#include"guild_asist.h"
#include"systemMessage.h"
#include"money_operator.h"
using namespace std;
#include"wholeDefine.h"
extern int g_msg_len;
extern Hero* pg_hero;

extern map<string, Hero*> heroId_to_pHero;
extern map<string,Pet_Config*>id_to_pet;
extern map<string,Wagon*> wagonInstMap;						//马车实例
extern int yabiaoDouble;

#define TASK_VARY_REWARD

#if defined(TASK_VARY_REWARD)
//0-日常，帮派；1 - 阵营，活动;3-循环任务
const int moneyFactor[3] = {10, 5, 5};
const int expFactor[3][8] =
{
							0, 150, 150, 300, 500, 800, 1200, 1500,
							0, 70, 70, 120, 200, 300, 650, 1000,
							0, 100, 150, 250, 400, 700, 1200, 2000
};

#endif

void taskFinish(char *buff)
{
	cout<<"finish task check!"<<endl;
	char *heroId;	  //角色Id
	char *taskId;     //任务Id
	char *NPCId;      //玩家交任务的NPCId 
	char *goodId;     //奖励物品Id
	
	
	MSG_BEGIN(buff, g_msg_len);
	MSG_CHAR(heroId);
	MSG_CHAR(taskId);
	MSG_CHAR(NPCId);
	MSG_CHAR_END(goodId);
	Hero *hero = pg_hero;
	
	char msg_task[64];
	
	sprintf(msg_task, "5,%d,%s,0", TASK_FINISH_RETURN, taskId);
	
	Task *task;
	map<string,Task*> task_list;
	
	task = hero->findAcceptedTaskList(taskId);
	if (task == NULL)
	{
		// msg_task = msg_task + intTostring(FAILED); 
		send_msg(hero->getFd(),msg_task);
		cout<<"[BisonWarn] Not find hero accepted this task taskid is "<<taskId<<endl;
		return ;
	}
	
	// string type = task->getTask_Type();
	// if(type == "1")  //状态判断  后期由策划提供的文档完成
	// {
		
	// }
	char* npcId_task = task->getFinNpcId();
	//cout<<"come here finid"<<endl;
	if(strcmp(NPCId, npcId_task))   //客户端要交任务的NPC是否与服务器任务配置文件中记录的要交任务的NPC是否一致
	{
		cout<<"[BisonWarn] the finishnpc is error when finish Task;"<<endl;
		// msg_task = msg_task + intTostring(FAILED); 
		send_msg(hero->getFd(),msg_task);
		return ;
	}
	
	//马车任务的特殊处理
	Wagon *wagon = NULL;
	if (!strcmp(taskId, "task00295") || !(strcmp(taskId, "task00419")))
	{
		char* wagonId = hero->memHero->wagonId;
		
		cout<<"BisonTest: You have come here with a wagon "<<wagonId<<endl;
		if (strlen(wagonId) == 0)
		{
			cout<<"Wagon is dead so can't finish wagon task!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		map<string,Wagon*>::iterator it_wagon;
		cout<<"BisonTest：wagonInstMap size is "<<wagonInstMap.size()<<endl;
		it_wagon = wagonInstMap.find(wagonId);
		if (it_wagon == wagonInstMap.end())
		{
			//没有这个马车
			cout<<"Wagon is dead so can't finish wagon task!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		wagon = it_wagon->second;
		
		//比较马车的主人是不是这个玩家
		Hero *owner = wagon->getOwner();
		if (owner == NULL)
		{
			cout<<"Wagon doesn't have owner when finish Task!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		char* ownerId = owner->getIdentity();
		if (strcmp(ownerId, hero->getIdentity()))
		{
			//马车的主人不是这个玩家
			cout<<"Wagon's owner is not this hero!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		//更新马车坐标
		Point pt = wagon->getPt();
		// string pointStr = intTostring(pt._x).substr(1);
		// pointStr += intTostring(pt._y);
		char pointStr[32];
		sprintf(pointStr, "%d,%d", pt._x, pt._y);
		cout<<"BisonTest wagon Point is "<<pointStr<<endl;
		int ret = task->taskUpdate(pointStr, -1);
		if (ret == -1)
		{
			cout<<"The wagon is too far away from the finish NPC!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		
		//看马车是否还有血
		if (wagon->getLifeVal() <= 0)
		{
			//马车已经挂了
			cout<<"Wagon's is dead!"<<endl;
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			return ;
		}
		cout<<"BisonTest: all Ok with wagon!"<<endl;
	}
	//验证完成条件是否满足
	if (!task->isTaskFinish())
	{
		// msg_task = msg_task + intTostring(FAILED); 
		send_msg(hero->getFd(),msg_task);
		cout<<" finish Fail"<<endl;
		return;
	} else {
		cout<<" finish Success"<<endl;
	}

	unsigned inFors = task->getInFors();
	unsigned prestige = task->getPrestige();
	unsigned gold = task->getTaskGold();						//获取任务奖励金钱
	unsigned exp = task->getTaskExp();							//获取完成的任务奖励的经验
	int giveType = task->getGiveType();							//获取任务奖励物品方式
	
	int taskType = task->getTaskType();
	int heroLevel = hero->getLevel();
	if (taskType == 2 || taskType == 5)
	{
		gold = gold * heroLevel * heroLevel;
		exp = exp * heroLevel * heroLevel * heroLevel;
	} else if (taskType == 8 || taskType == 7)
	{
		gold = gold * heroLevel * heroLevel;
		exp = exp * heroLevel * heroLevel * heroLevel;
	} else if (taskType == 4)
	{
		gold = gold * heroLevel * heroLevel;
		exp = exp * heroLevel * heroLevel * heroLevel;
	} else if (taskType == 9)
	{
		double cycleFactor = hero->getCycleTaskRewardFactor();
		gold = gold * heroLevel * heroLevel * cycleFactor;
		exp = exp * heroLevel * heroLevel * heroLevel * cycleFactor;
	}
	
	if (taskType == 1)
	{
		pg_hero->updataSingleTarget(0,0);			//武林目标
	}
	
	//jolly added 做某些活动的时候,个别人物需要多倍经验,在此处添加,有疑问请咨询 start
	//帮派拉镖 双倍经验
	if (strcmp(taskId, "task00295")==0)		
	{
		exp=exp*yabiaoDouble;
	}
	//jolly added 做某些活动的时候,个别人物需要多倍经验,在此处添加,有疑问请咨询 end
	
	map<string, int> rewardList;
	//如果不是系统分配物品且玩家还没有选择领取奖励物品，作完成任务失败处理
	if (giveType != -1)
	{
		if (giveType != 0 && goodId[0] == '\0')
		{
			// msg_task = msg_task + intTostring(FAILED); 
			send_msg(hero->getFd(),msg_task);
			cout<<"BisonTest in user_role_finish_task.cpp:161!"<<endl;
			cout<<"If you see this , it shows that the giveType of task.xml in server not same with the client's!"<<endl;
			cout<<"The server's giveType is "<<giveType<<endl;
			return ;
		}
		rewardList.clear();
		task->taskGetReward(goodId, rewardList);
		Bag *bag=hero->getBag();
		if (bag->bagIsFull(rewardList.size()))
		{
			send_msg(hero->getFd(),msg_task);
			cout<<"Bison Test: user_role_finish_task.cpp:205. reward size is "<<rewardList.size()<<endl;
			cout<<"There is not enough idle spaces in bag to store the rewards!"<<endl;
			return ;
		}
		
		hero->addInternalForces(inFors);
		hero->addPrestigeValue(prestige);
		hero->setExpNow(exp);
		increaseBoundGameMoney(hero,gold);
		map<string, int>::iterator it_reward;
		it_reward = rewardList.begin();
		for (it_reward; it_reward != rewardList.end(); it_reward++)
		{
			saveGoodsInBag(hero, const_cast<char*>(it_reward->first.c_str()), it_reward->second);
		}
		
	} else {			
		hero->setExpNow(exp);
		increaseBoundGameMoney(hero,gold);
	}
	
	//从这一步后就不能返回failed了
	int chapt = task->getTaskChapt();
	hero->delAcceptedTaskList(taskId);							//删除对应的已接任务

	//hero->memHero->taskSaveData.acced[chapt];
	//把任务需要的物品回收，
	rewardList.clear();
	int needRecycle = task->recycleTaskNeedGoods(rewardList);			//获取需要回收的任务道具信息 added by bison 7.5
	Bag *bag = hero->getBag();
	if (needRecycle == 0)
	{
		map<string, int>::iterator it_rec = rewardList.begin();
		for (;it_rec != rewardList.end(); it_rec++)
		{
			if (it_rec->second == 0)
			{
				useAllGoods(hero, const_cast<char *>(it_rec->first.c_str()));
			}
			else {
				int _index=bag->searchIndex(const_cast<char *>(it_rec->first.c_str()));
				// if (bag->finishTask(it_rec->second, _index))
				if (useBagGoods(hero, const_cast<char *>(it_rec->first.c_str()),it_rec->second)==0)
				{
					send_msg_useSuccess(hero,_index);
				}
			}
		}
		
	}
	
	// msg_task = msg_task + intTostring(SUCCESS);
	
	//先设置物品，再设置经验金钱，可以防止背包已满，不能设置物品的情形
	//hero_add_exp(hero,exp);             //将完成任务获得经验加到人物属
	
	float rewardTimes = 1.0f;
	if (wagon != NULL)
	{
		rewardTimes = wagon->getRewardTimes();
	}
	//如果是帮派任务的话还有帮派奖励
	if (task->getTaskType() == 2)
	{
		char guildTaskReward[200] = {0};
		// string guildTaskReward = getGuildTaskReward(hero, taskId);
		int ret = getGuildTaskReward(hero, taskId, guildTaskReward, rewardTimes);
		if (ret != 0 || strlen(guildTaskReward) != 0)
		{ 
			systemSendMssage(hero, guildTaskReward, 3);
		}
		//send_msg(hero->getFd(), guildRewardMsg);
	}
	//马车回收
	if (wagon != NULL)
	{
		wagon->disperMsg();
		if (wagonInstMap.find(wagon->getId()) != wagonInstMap.end())
		{
			wagonInstMap.erase(wagonInstMap.find(wagon->getId()));
		}
		delete wagon;
		wagon = NULL;
		strncpy(hero->memHero->wagonId, "\0", 2);
	}   
	if (strcmp(taskId,"task00419")==0)//阵营拉镖
	{
		hero->updataSingleTarget(1,5);
	}   
	else if (strcmp(taskId,"task00005")==0)
	{
		hero->updataSingleTarget(0,2);
	}
	else if (strcmp(taskId,"task00381")==0||strcmp(taskId,"task00385")==0||strcmp(taskId,"task00389")==0||strcmp(taskId,"task00393")==0 \
	||strcmp(taskId,"task00397")==0||strcmp(taskId,"task00401")==0)//阵营抢旗
	{
		hero->updataSingleTarget(2,11);
	}
	else if (strcmp(taskId,"task00398")==0||strcmp(taskId,"task00394")==0||strcmp(taskId,"task00390")==0||strcmp(taskId,"task00386")==0 \
	||strcmp(taskId,"task00382")==0||strcmp(taskId,"task00378")==0)		//大侠
	{
		hero->updataSingleTarget(2,12);
	}
	else if (strcmp(taskId,"task00399")==0||strcmp(taskId,"task00395")==0||strcmp(taskId,"task00391")==0||strcmp(taskId,"task00387")==0 \
	||strcmp(taskId,"task00383")==0||strcmp(taskId,"task00379")==0)	//信使
	{
		hero->updataSingleTarget(2,13);
	}
	
	//map<string,Task*> task_list_finish;
/*
	set<string> task_list_finish;
	task_list_finish = hero->getFinish_Task_List();         //获取玩家已接任务列表
	
	task_list_finish.insert(taskId);
//	task_list_finish[taskId] = task;  

	hero->setFinish_Task_List(task_list_finish);
*/
	
	// msg_task = msg_task + intTostring(gold) + intTostring(hero->getExpNow()); 
	sprintf(msg_task, "5,%d,%s,1,%d,%d", TASK_FINISH_RETURN, taskId, gold, hero->getExpNow());
	send_msg(hero->getFd(),msg_task);
	//用位图操作替换,放在后面，以防有环任务
	hero->setFinishTaskMap(taskId);
	
	if (task->getSubType() == 1)
	{
		hero->setTaskNeedKillNpcBossId(NULL);
	}
	
	if (task->getIsLastOfThisChapt())
	{
		hero->setTaskPassChapt(chapt);
	}
	
	if (task->getTaskType() == 9)
	{
		hero->setCycleTaskFinish(taskId);
	}
	
	//多级任务
	if (task->getTaskType() == 4)
	{
		//日常任务之多级任务之主任务接受
		//把该主任务的子任务置为可接
		//只有多级任务之主任务的needType 才会为20
		char sonTaskIdSet[100];
		memset(sonTaskIdSet, 0, sizeof(sonTaskIdSet));
		task->getSpecialNeedId(20, sonTaskIdSet);
		cout<<"BisonTest: sonTaskIdSet is "<<sonTaskIdSet<<endl;
		if(strlen(sonTaskIdSet) == 0)
		{	
			//多级任务的子任务完成，要更新主任务的状态
			cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&taskId is "<<taskId<<endl;
			hero->updateHeroTaskStatus(CYCLE_TASK_NEED_TYPE, taskId); 
		}
	}
	
	delete task; 
}