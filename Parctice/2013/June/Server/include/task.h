/* 
		文件类型：头文件
		文件名称：npc.h
		文件作用：实体类npc的属性以及方法的定义
		完成时间：2012.5.10
		  完成人：Evan		
*/

#ifndef TASK_H
#define TASK_H
#include<string>
#include<set>
#include<map>
#include<vector>
#include"data_structure_struct.h"
#include"task_configuration.h"

#define DIALOG_TASK_NEED_TYPE			0			//对话任务
#define KILL_TASK_NEED_TYPE				1			//杀怪任务
#define PICKUP_TASK_NEED_TYPE			2			//采集任务
#define COLLECT_TASK_NEED_TYPE			3			//收集任务
#define	WAGON_TASK_NEED_TYPE			4			//护送任务
#define TOTEM_TASK_NEED_TYPE			5			//图腾任务
#define LOCATION_TASK_NEED_TYPE			6			//位置验证任务
#define USE_TASK_NEED_TYPE				7			//使用物品任务
#define JOIN_CAMP_TASK_NEED_TYPE		10			//选择阵营任务
#define	KILL_LIMIT_TASK_NEED_TYPE		11			//杀限制等级怪任务
#define EQUIP_CUILI_TASK_NEED_TYPE		12			//装备淬砺任务
#define	EQUIP_JINGLIAN_TASK_NEED_TYPE	16			//装备精炼任务		
#define	JOIN_GUILD_TASK_NEED_TYPE		13			//加入帮派任务
#define TREASURE_MAP_TASK_NEED_TYPE		14			//找藏宝图任务
#define CYCLE_TASK_NEED_TYPE			20			//循环任务主任务
#define RESCUE_TASK_NEED_TYPE			15			//救治伤员任务
#define BUY_EQUIP_TASK_NEED_TYPE		17			//买装备的需求
#define BUY_DAOJU_TASK_NEED_TYPE		18			//买道具的需求
#define PK_OTHER_HERO_TASK_NEED_TYPE	19			//PK需求的任务
#define PASS_ECTYPE_TASK_NEED_TYPE		21			//通关副本需求
#define KILL_NPC_BOSS_TASK_NEED_TYPE	22			//杀死NPC变的boss需求
#define PASS_TOWER_LAYER_TASK_NEED_TYPE	23			//需要通关青衣楼的需求

//task存到数据库的状态数据
typedef struct TaskData_S
{ 
	//bool noTaskFlag;					//数据是否为无效
	long taskFlag;						//任务标志，为-1表明未使用
	char taskId[10];					//任务ID
	int status[5];						//任务的状态数据
	TaskData_S()
	{
		taskFlag = -1;				//默认置为无效，表示没有存task数据
		memset(taskId, 0, sizeof(taskId));
		status[0] = 0;status[1] = 0;status[2] = 0;status[3] = 0;status[4] = 0;
	}
	void operator =(const TaskData_S &data)
	{
		taskFlag = data.taskFlag;
		strncpy(taskId, data.taskId, sizeof(taskId));
		memcpy(status, data.status, sizeof(status));
	}
}TaskData_T;

typedef struct CyCleTaskSet_S
{
	
} CyCleTaskSet_T;

extern map<int, vector<string> > levelCycleTaskSet;

extern map<int, vector<double> > cycleTaskRewardFactor;

class Task
{
private:
	int	   taskType;			//任务类型
	char taskId[51];			//任务ID
	char taskName[51];  	 	//任务名称
	char recNpcId[51];      	//接任务NPC id
	char finNpcId[51];      	//交任务NPC id
	//modified by bison
	list<taskStatus_T*> taskStatus;		//任务状态
	set<give_t*> taskReward;			//任务奖励,经过讨论，这里以后只做奖励物品时使用，金钱和经验的拿出来另外存
	set<recv_t*> taskRecv;				//任务接受时所给内容
	unsigned inFors;					//内力
	unsigned prestige;					//声望
	unsigned taskGold;					//任务奖励金钱
	unsigned taskExp;					//任务奖励经验
	int giveType;						//任务完成后物品奖励方式：0：系统默认；1：玩家选择
	int chapt;							//任务所在章节
	int subType;						//任务子类型
	int frequency;						//任务一天之内可接次数
	bool isLastOfThisChapt;				//是否是本章节的最后一个任务
public:
	Task(int _taskType, int freq, char* _taskId, char* _taskName, char* _RecNpcId, char* _FinNpcId,
		int _chapt, unsigned _inFors, unsigned _prestige, unsigned _gold,unsigned _exp, int _giveType, list<taskStatus_T*> _taskStatus,
		set<give_t*> _taskReward, set<recv_t*> _taskRecv, int subType, bool _isLastOfThisChapt);
	
	//由配置类初始化task实例
	Task(Task_Configuration *task_configuration);
	//由memcache中上来的状态数据构造task实例
	Task(TaskData_T taskData);
	~Task(void);
	//通过对任务状态检查判断任务是否完成
	bool isTaskFinish(void);
	//更新任务状态数据
	int taskUpdate(char* _needId, int _value);
	//检查奖励和任务应该的奖励是否匹配
	int taskCheckReward(char* _giveId, int _num);
	
	//任务奖励 返回奖励的一串消息，包括奖励物品id和数量
	int taskGetReward(char* _giveId, map<string, int> &rewardList);
	
	//把开始任务时需要给玩家的道具添加到玩家背包
	int getBeginTaskGive(char* beginGive);
	//回收任务需要的物品
	int recycleTaskNeedGoods(map<string, int> &needRecycle);
	//得到任务道具ID
	char* getTaskGoods(void);
	//得到任务的某个需求的状态数据值
	int getTaskStatusValue(char* _needId);
	//void setTask_Monster_Accout(int _task_monster_accout);
	//int  getTask_Monster_Accout(void);
	
	//获取任务一天内可接的次数
	int getFreq(void);
	//获取任务类型
	int getTaskType(void);
	int getNeedType(char* needId);
	int getTaskChapt(void);
	unsigned getInFors();
	unsigned getPrestige();
	unsigned getTaskGold(void);
	unsigned getTaskExp(void);
	int getGiveType(void);
	int getSubType(void);
	bool getIsLastOfThisChapt();
	list<taskStatus_T*> getTaskStatus(void);
	set<give_t*> getTaskReward(void);
	set<recv_t*> getTaskRecv(void);
	char* getTaskId(void);
	char* getTaskName(void);
	//string getTask_Type(void);
	char* getRecNpcId(void);
	char* getFinNpcId(void);
	//初始任务数据
	TaskData_T initTaskData(void);
	
	//是否还需要继续收集某种道具
	bool needMoreCollection(char* collectionId);
	//由任务的needType找任务的needId, 只针对同一个任务中同一个needType不会出现多次的情况
	int getSpecialNeedId(int needType, char* needId);		//最不希望有这种函数，但多级任务的放弃时又是需要的
	//string getTask_Monster_Id(void);
	//int    getTask_Monster_Num(void);
	//set<string> getTask_Goods_Id(void);
	//int    getTask_Gold_Num(void);
	//int    getTask_Exp(void);
};
#endif