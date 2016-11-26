#ifndef TASK_CONFIGURATION_H
#define TASK_CONFIGURATION_H
#include<iostream>
#include<string>
#include<list>
#include<set>
using namespace std;

#include"data_structure_struct.h"

typedef struct TaskChaptReward_S
{
	char rewardId[51];
	int rewardNum;
	TaskChaptReward_S()
	{
		memset(rewardId, 0, sizeof rewardId);
		rewardNum = 0;
	}
} TaskChaptReward_T;

extern map<int, TaskChaptReward_T> chapt_2_taskReward;

class Task_Configuration
{
private:  
	char taskId[51];			//npcid
	char taskName[51];   	//任务名称
	char recNpcId[51];      //接任务NPC id
	char finNpcId[51];      //交任务NPC id
	
	int frequency;			//该任务一天内可接次数
	int taskType;			//任务类型：1：主线类型任务；……
	int taskChapt;			//任务章节：1：0-10级任务；……
	unsigned taskLevel;     //任务等级
	unsigned inFors;		//内力
	unsigned prestige;		//声望
	unsigned taskGold;		//任务奖励金钱数
	unsigned taskExp;		//任务经验数
	int giveType;			//任务奖励物品方式，0：系统默认奖励，1：玩家选择奖励
	int subType;			//任务子类型
	bool isLastOfThisChapt;	//是否是本章最后一个任务
	
	
	/* 任务完成条件 --决定了任务的类型 */
	list<need_t*> taskNeed;
	/* 任务奖励，金钱，装备，经验等 */
	set<give_t*> taskGive;
	/* 任务的触发条件序列 */
	set<touch_t*> taskTouch;
	/* 接受任务所给的序列 */
	set<recv_t*> taskRecv;
	
public:
	Task_Configuration(char* _id, char* _name, char* _recNpcId, char* _finNpcId, int _frequecy, int _type, unsigned _inFors, unsigned _prestige, unsigned _gold, unsigned _exp, int _giveType, int _chapt, unsigned _level, list<need_t*> _need, set<give_t*> _give, set<touch_t*> _touch, set<recv_t*> _recv, int _subType, bool _isLastOfThisChapt);	
	char* getTaskId(void);
	char* getTaskName(void);
	char* getRecNpcId(void);
	char* getFinNpcId(void);
	
	int getFrequency(void);
	int getTask_type(void);
	int getTask_chapt(void);
	unsigned getTask_level(void);
	unsigned getPrestige();
	unsigned getInFors();
	unsigned getTask_gold();
	unsigned getTask_exp();
	int getTask_giveType();
	int getSubType();
	bool getIsLastOfThisChapt();
	/* get任务的需要属性和完成奖励 */
	list<need_t*> getTask_need(void);
	set<give_t*> getTask_give(void);
	set<touch_t*> getTask_touch(void);
	set<recv_t*> getTask_recv(void);
/*	set<string> getTask_Goods_Id(void);
	int    getTask_Gold_Num(void);
	int    getTask_Exp(void);
*/	
};
#endif