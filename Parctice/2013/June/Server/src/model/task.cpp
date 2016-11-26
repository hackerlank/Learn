/* 
		文件类型：头文件
		文件名称：task.cpp
		文件作用：任务实体类task的属性以及方法的定义
		完成时间：2012.5.10
		  完成人：Evan
*/
#include"task.h"
#include"command_other_function_all_over.h"

extern map<string,Task_Configuration*> id_to_task;

Task::Task(int _taskType, int freq, char* _taskId, char* _taskName, char* _recNpcId, char* _finNpcId,
		int _chapt, unsigned _inFors, unsigned _prestige, unsigned _gold, unsigned _exp, int _giveType, list<taskStatus_T*> _taskStatus,
		set<give_t*> _taskReward, set<recv_t*> _taskRecv, int _subType, bool _isLastOfThisChapt)
{
	taskType = _taskType;
	frequency = freq;
	strncpy(taskId, _taskId, sizeof(taskId));
	strncpy(taskName, _taskName, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskStatus = _taskStatus;
	taskReward = _taskReward;
	taskRecv = _taskRecv;
	chapt = _chapt;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
}

//根据task配置类初始task实例
Task::Task(Task_Configuration *task_configuration)
{
	/* 从任务配置中读取相关数据来初始化任务实例 */
	int	_taskType = task_configuration->getTask_type();				//任务类型
	int _freq = task_configuration->getFrequency();					//任务一天可接次数
	char* _taskId = task_configuration->getTaskId();		      //任务id; 这可以省了，已经有startTaskId了
	char* _taskName = task_configuration->getTaskName();        //任务名
	char* _recNpcId = task_configuration->getRecNpcId();      //接任务NPC的id
	char* _finNpcId = task_configuration->getFinNpcId();      //交任务NPC的id
	unsigned _inFors = task_configuration->getInFors();
	unsigned _prestige = task_configuration->getPrestige();
	unsigned _gold = task_configuration->getTask_gold();           //完成任务的金钱奖励
	unsigned _exp = task_configuration->getTask_exp();			  //完成任务的经验奖励
	int _giveType = task_configuration->getTask_giveType();		  //任务奖励物品的方式
	int _chapt = task_configuration->getTask_chapt();				  //任务所在章节
	int _subType = task_configuration->getSubType();				//任务子类型
	bool _isLastOfThisChapt = task_configuration->getIsLastOfThisChapt();
	/* task_configuration的need序列转换成task的status序列 */
	list<need_t*> need = task_configuration->getTask_need();
	list<taskStatus_T*> _taskStatus;                               //记录任务状态的成员变量
	list<need_t*>::iterator iter_need;
	iter_need = need.begin();
	if (iter_need != need.end())
		cout<<"BisonShow "<<(*iter_need)->type<<" "<<(*iter_need)->id<<"  "<<(*iter_need)->num<<endl;
	for (iter_need; iter_need != need.end(); iter_need++)
	{
		//使用need构造status,初始状态数据设为0
		taskStatus_T *status = new taskStatus_T((*iter_need), 0);
		_taskStatus.push_back(status);
	}
	
	set<give_t*> give = task_configuration->getTask_give();		  //获得give序列
	set<recv_t*> recv = task_configuration->getTask_recv();		  //获得recv序列
	
	//调用上一个构造函数
	//this(_taskId, _taskName, _recNpcId, finNpcId, _gold, _exp, _giveType, _taskStatus, give, recv);
	taskType = _taskType;
	frequency = _freq;
	strncpy(taskId, _taskId, sizeof(taskId));
	strncpy(taskName, _taskName, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskStatus = _taskStatus;
	taskReward = give;
	taskRecv = recv;
	chapt = _chapt;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
}

//由memcache上来的task数据恢复task实例
Task::Task(TaskData_T taskData)
{
	char* taskIdSrc = taskData.taskId;
	Task_Configuration *task_configuration;
	
	map<string,Task_Configuration*>::iterator iter_conf;
	iter_conf = id_to_task.find(taskIdSrc);
	if(iter_conf == id_to_task.end())
	{
		cout<<"Bison Warning @task.cpp:82."<<endl;
		cout<<"very Bad, there is no the specified task with the id of "<<taskIdSrc<<endl;
		return ;
	}
	
	task_configuration = iter_conf->second;
	
	/* 从任务配置中读取相关数据来初始化任务实例 */
	int _taskType = task_configuration->getTask_type();				//任务类型
	int _freq = task_configuration->getFrequency();					//任务一天可接次数
	char* _taskId = task_configuration->getTaskId();				//任务id; 这可以省了，已经有startTaskId了
	char* _taskName = task_configuration->getTaskName();			//任务名
	char* _recNpcId = task_configuration->getRecNpcId();		//接任务NPC的id
	char* _finNpcId = task_configuration->getFinNpcId();		//交任务NPC的id
	unsigned _inFors = task_configuration->getInFors();
	unsigned _prestige = task_configuration->getPrestige();
	unsigned _gold = task_configuration->getTask_gold();			//完成任务的金钱奖励
	unsigned _exp = task_configuration->getTask_exp();				//完成任务的经验奖励
	int _giveType = task_configuration->getTask_giveType();			//任务奖励物品的方式
	int _chapt = task_configuration->getTask_chapt();				//任务所在章节
	int _subType = task_configuration->getSubType();				//任务子类型
	bool _isLastOfThisChapt = task_configuration->getIsLastOfThisChapt();
	
	/* task_configuration的need序列转换成task的status序列 */
	list<need_t*> need = task_configuration->getTask_need();
	list<taskStatus_T*> _taskStatus;                               //记录任务状态的成员变量
	list<need_t*>::iterator iter_need;
	iter_need = need.begin();
	if (iter_need != need.end())
		cout<<(*iter_need)->type<<" "<<(*iter_need)->id<<"  "<<(*iter_need)->num<<endl;
	for (iter_need; iter_need != need.end(); iter_need++)
	{
		//使用need构造status,初始状态数据设为0
		taskStatus_T *status = new taskStatus_T((*iter_need), 0);
		_taskStatus.push_back(status);
	}
	
	set<give_t*> give = task_configuration->getTask_give();		  //因为give是固定的不对give实例，和任务配置中give使用相同内存
	set<recv_t*> recv = task_configuration->getTask_recv();		  //recv也固定，不会在task中变化
	
	//调用上一个构造函数
	//this(_taskId, _taskName, _recNpcId, finNpcId, _gold, _exp, _giveType, _taskStatus, give, recv);
	frequency = _freq;
	taskType = _taskType;
	strncpy(taskId, _taskId, sizeof(taskId));
	strncpy(taskName, _taskName, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskStatus = _taskStatus;
	taskReward = give;
	taskRecv = recv;
	chapt = _chapt;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int i = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{	
		(*iter)->value = taskData.status[i];
		i++;
	}
	
}

char* Task::getTaskId(void)
{
	return taskId;
}
char* Task::getTaskName(void)
{
	return taskName;
}
/*string Task::getTask_Type(void)
{
	return task_type;
}
*/
char* Task::getRecNpcId(void)
{
	return recNpcId;
}
char* Task::getFinNpcId(void)
{
	return finNpcId;
}

unsigned Task::getInFors(void)
{
	return inFors;
}

unsigned Task::getPrestige(void)
{
	return prestige;
}

unsigned Task::getTaskGold(void)
{
	return taskGold;
}

unsigned Task::getTaskExp(void)
{
	return taskExp;
}

//返回一天任务可接的次数
int Task::getFreq(void)
{
	return frequency;
}

int Task::getGiveType(void)
{
	return giveType;
}

/* 获取任务的状态序列 */
list<taskStatus_T*> Task::getTaskStatus(void)
{
	return taskStatus;
}
/* 获取任务的奖励序列 */
set<give_t*> Task::getTaskReward(void)
{
	return taskReward;
}

/* 获取任务接受时所给内容 */
set<recv_t*> Task::getTaskRecv(void)
{
	return taskRecv;
}
/* 判断任务是否完成，如果完成返回true,否则返回false */
bool Task::isTaskFinish(void)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	bool finishFlag = true;
	for (iter; iter != taskStatus.end(); iter++)
	{
		/* type为0，对话任务，不做数字相关的验证*/
		
		//需要验证位置的任务保证位置已经验证过
		if ((*iter)->type == 6)
		{
			if ((*iter)->value != 1)
			{
				cout<<"BisonWarn @task.cpp: the targer location is out finishing task range"<<endl;
				finishFlag = false;
			}
		}
		//0是对话，4是马车，都不要检查
		else if ((*iter)->type != 0 && (*iter)->type != 4)
		{
			if ((*iter)->num != (*iter)->value) 
			{
				finishFlag = false;
				break;
			}
		}
	}
	return finishFlag;
}

/* getBeginTaskGive -- 得到开始任务时需要给玩家的道具信息 */
int Task::getBeginTaskGive(char *beginGive)
{
	set<recv_t*>::iterator iter_recv;
	iter_recv = taskRecv.begin();
	// string giveMsg;
	for (iter_recv; iter_recv != taskRecv.end(); iter_recv++)
	{
		//任务道具类型物品
		if ((*iter_recv)->type == 0)
		{
			// giveMsg = giveMsg + (*iter_recv)->id + intTostring((*iter_recv)->num);
			sprintf(beginGive, "%s,%d", (*iter_recv)->id, (*iter_recv)->num);
			//这种任务道具最多只能给一种，得到后就可以停止后面的判断返回了
			return 0;
			//add to bag
		}
		if ((*iter_recv)->type != 0)
		{ 
			//护送任务，把护送ID发了
			// giveMsg = (*iter_recv)->id;
			strncpy(beginGive, (*iter_recv)->id, sizeof((*iter_recv)->id));
			return 0;
		}
	}
	//give列表中没有接任务时候需要给的道具
	return -1;
}

//回收任务需要的物品
int Task::recycleTaskNeedGoods(map<string, int> &needRecycle)
{
	//Bag *bag = hero->bag;
	// string msg;
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		if ((*iter)->type == 2 || (*iter)->type == 18)
		{
			//道具类型时，需要多少个就回收多上个
			//bag->remove((*iter)->id, (*iter)->num, hero->getFd());
			// msg = (*iter)->id + intTostring((*iter)->num);
			// sprintf(needRecycle, "%s,%d", (*iter)->id, (*iter)->num);
			needRecycle.insert(pair<string, int>((*iter)->id, (*iter)->num));
			//主线任务没有一个任务需求两种类型道具的情况
			// return 0;
		}
		else if ((*iter)->type == 3)
		{
			//任务道具，全部回收
			//bag->removeAll((*iter)->id, hero->getFd()); 
			//不全部回收了，只回收需要的个数个，多余的让玩家自己销毁
			// msg = (*iter)->id + intTostring((*iter)->num);
			// sprintf(needRecycle, "%s,%d", (*iter)->id, (*iter)->num);
			needRecycle.insert(pair<string, int>((*iter)->id, (*iter)->num));
			// return 0;
		}
	}
	if (needRecycle.size() == 0)
	{
		return -1;
	} else {
		return 0;
	}
}

static Point str2point(char* str)
{
	int pos = findChar(str, ',', strlen(str));
	if (pos == -1)
	{
		pos = findChar(str, ':', strlen(str));
		if (pos == -1)
		{
			cout<<"BisonWarning if you failed task ,please check this @task.cpp!"<<endl;
			cout<<"BisonWarning @task.cpp: You have given a str that can't exchange to Point"<<endl;
			pos = strlen(str);
		}
	}
	char xstr[16];
	sub_str(xstr, str, 0, pos);
	int PointX = atoi(xstr);
	sub_str(xstr, str, pos + 1, 0);
	int PointY = atoi(xstr);
	Point pt(PointX, PointY);
	return pt;
}

/**
 * taskUpdate -- 更新任务状态
 * @_needId: 该任务需求的id
 * @_value:  所要设置的状态数据
 * @return: 更新成功返回need的序号，更新失败返回-1,表明value值有误或者无效更新，或者_needId不在该任务的need序列中；
 */
int Task::taskUpdate(char* _needId, int _value)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int ret = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{
		char* temp = (*iter)->id;
		int pos = 0;
		char oneNeedId[51];
		
		//需要验证位置的任务需求, 验证坐标的更新时_value都传-1，以区别一个need多Id的情况
		if ((*iter)->type == 6 && _value == -1)
		{
			//发送点坐标有误
			if (findChar(temp, ':', strlen(temp)) == -1 || findChar(_needId, ',', strlen(_needId)) == -1)
			{
				return -1;
			}
			
			Point ptNeed = str2point(temp);
			Point ptGiven = str2point(_needId);
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			cout<<"ptNeed._x "<<ptNeed._x<<endl;
			cout<<"ptNeed._y "<<ptNeed._y<<endl;
			cout<<"ptGiven._x "<<ptGiven._x<<endl;
			cout<<"ptGiven._y "<<ptGiven._y<<endl;
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			cout<<"@@@@@@@@@@@@@@@@@@@@@BisonTest distance check@@@@@@@@@@@@@@@@@@@@@"<<endl; 
			int deltaX = ptNeed._x - ptGiven._x;
			int deltaY = ptNeed._y - ptGiven._y;
			int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (distance > 400)
			{
				return -1;
			} else {
				//taskStatus_T *statusTemp = (*iter); //还沿用前面taskStatus结构内存
				//statusTemp->value = _value;
				//taskStatus.erase(iter);
				//taskStatus.insert(statusTemp);
				//任务距离验证成功后value都更新成1
				(*iter)->value = 1;
				return ret;
			}
		}
		if ((*iter)->type == 11)
		{
			if (_value < 0 || _value > (*iter)->num || _value <= (*iter)->value)
			{
				return -1;
			}
			(*iter)->value = _value;
			return ret;
		}
		
		int len = strlen(temp);
		while (len > 0)
		{
			pos = findChar(temp, ':', len);
			if (pos == -1)
			{
				strncpy(oneNeedId, temp, len + 1);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneNeedId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			if (!strcmp(oneNeedId, _needId))
			{
				if (_value < 0 || _value > (*iter)->num)
				{
					//invalid value
					cout<<"taskUpdate Invalid value"<<endl;
					return -1; 
					
				} else if (_value <= (*iter)->value) {
					//error update or no need to update;
					cout<<"taskUpdate little value now value is "<<(*iter)->value<<endl;
					return -1;
					
				} else {
					//valid update
					//还沿用前面taskStatus结构内存
					(*iter)->value = _value;
					return ret;
				}
			}
		}
		//need序号加1
		ret++;
	}
	
	cout<<"taskUpdate No Need"<<endl;
	return -1;
}

/**
 * getNeedType -- 查找任务的needType
 * @needId: 该任务需求的id
 * @return: 查找到返回任务该needId对应的类型，查找失败返回-2
 */
int Task::getNeedType(char* needId)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int ret = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{
		char* temp = (*iter)->id;
		int pos = 0;
		char oneNeedId[51];
		int len = strlen(temp);
		while (len > 0)
		{
			pos = findChar(temp, ':', len);
			if (pos == -1)
			{
				strncpy(oneNeedId, temp, len + 1);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneNeedId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			if (!strcmp(oneNeedId, needId))
			{
				return (*iter)->type;
			}
		}
	}
	
	return -2;
}

/* XXX:todo: */
int Task::taskCheckReward(char* _giveId, int _num)
{
	
}
/**
 * taskReward -- 获得任务奖励，
 * @_giveId：玩家选择的物品id, 该参数当giveType为0，即系统默认分配时可以为空
 * @return: 返回“,物品id,数量……”的string格式。如果giveType为0，系统默认分配。
 * 	返回任务的全部Reward物品序列，如果giveType不为0时：
 * 	情形1:客户端发来的giveId在奖励物品序列中，返回字符串“,giveId,num"
 * 	情形2：giveId是冒领的，返回字符串”,_giveId,0"
 */
int Task::taskGetReward(char* _giveId, map<string, int> &rewardList)
{
	
	set<give_t*>::iterator iter_give;
	iter_give = taskReward.begin();
	cout<<"giveType:"<<giveType<<endl;
	if (giveType == 0)
	{
		for (iter_give; iter_give != taskReward.end(); iter_give++)
		{
			//不是开始任务时需要给玩家的道具
			if ((*iter_give)->type != 3)
			{
				rewardList.insert(pair<string, int>((*iter_give)->id, (*iter_give)->num));
				// msg = msg + "," + (*iter_give)->id + intTostring((*iter_give)->num);
			}
		}
		return 0;
	} else {
		for (iter_give; iter_give != taskReward.end(); iter_give++)
		{
			if (!strcmp((*iter_give)->id, _giveId))
			{
				rewardList.insert(pair<string, int>((*iter_give)->id, (*iter_give)->num));
				// msg = msg + "," + (*iter_give)->id + intTostring((*iter_give)->num);
				return 0;
			}
		}
		return -1;
	}
	
	// return msg;
}

/************************************************************
 * getTaskGoods -- 得到任务道具id
 * Return: 如果是搜集任务道具的任务，返回要搜集的任务道具ID
 *		   否则，返回空string
 ************************************************************/
char* Task::getTaskGoods(void)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		//任务道具
		if ((*iter)->type == 3 || (*iter)->type == 2)
		{
			if ((*iter)->value < (*iter)->num)
			{
				// taskGoodsId = (*iter)->id;
				return (*iter)->id;
			}
		}
	}
	
	return NULL;
}

//由任务的needType找任务的needId, 只针对同一个任务中同一个needType不会出现多次的情况
int Task::getSpecialNeedId(int needType, char* needId)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		//任务道具
		if ((*iter)->type == needType)
		{
			strncpy(needId, (*iter)->id, sizeof((*iter)->id));
			return 0;
		}
	}
	
	return -1;
}

Task::~Task(void)
{
	list<taskStatus_T*>::iterator iter_status;
	iter_status = taskStatus.begin();
	for (iter_status; iter_status != taskStatus.end(); )
	{
		taskStatus_T *status = (*iter_status);
		//临时记录当前量以便安全删除
		iter_status++;
		//taskStatus.erase(iter_temp);
		delete status;
	}
	taskStatus.clear();
}

/**
 * getTaskStatusValue -- 得到任务的某条需求的状态数据
 * @_needId: 该任务需求的id
 * @return: value：_needId的当前状态值；-1：needId不在任务需求列表中
 */
int Task::getTaskStatusValue(char* _needId)
{
	int ret = -1;
	char oneNeedId[51];
	int pos;
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		char *temp = (*iter)->id;
		int len = strlen(temp);
		while (len > 0)
		{
			pos = findChar(temp, ',', len);
			if (pos == -1)
			{
				strncpy(oneNeedId, temp, len + 1);
				temp = temp + len;
			}
			else 
			{
				sub_str(oneNeedId, temp, 0, pos);
				//strncpy(oneGuildId, temp, pos);
				temp = temp + pos + 1;
			}
			len = strlen(temp);
			if (!strcmp(oneNeedId, _needId))
			{
				ret = (*iter)->value;
				goto LE;
			}
		}
	}
LE: ;	
	return ret;
}

int Task::getTaskChapt(void)
{
	return chapt;
}

//初始任务数据
TaskData_T Task::initTaskData(void)
{
	TaskData_T taskData; 
	taskData.taskFlag = 0;					//标志为有效任务
	strncpy(taskData.taskId, taskId, sizeof(taskData.taskId));
	
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	int i = 0;
	for (iter; iter != taskStatus.end(); iter++)
	{	
		taskData.status[i] = (*iter)->value;
		i++;
	}
	return taskData;
}

//获取任务类型
int Task::getTaskType(void)
{
	return taskType;
}

//获取任务子类型
int Task::getSubType(void)
{
	return subType;
}

//是否还需要继续收集某种道具
bool Task::needMoreCollection(char* collectionId)
{
	list<taskStatus_T*>::iterator iter;
	iter = taskStatus.begin();
	for (iter; iter != taskStatus.end(); iter++)
	{
		if ((*iter)->type == 2 || (*iter)->type == 14 || (*iter)->type == 15)
		{
			if (!strcmp((*iter)->id, collectionId) && (*iter)->value < (*iter)->num)
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Task::getIsLastOfThisChapt()
{
	return isLastOfThisChapt;
}
/*
void Task::setTask_Monster_Accout(int _task_monster_accout)
{
	task_monster_accout = _task_monster_accout;
}
int Task::getTask_Monster_Accout()
{
	return task_monster_accout;
}

string Task::getTaskId(void)
{
	return taskId;
}
string Task::getTaskName(void)
{
	return taskName;
}
string Task::getTask_Type(void)
{
	return task_type;
}
string Task::getRecNpcId(void)
{
	return recNpcId;
}
string Task::getFinNpcId(void)
{
	return finNpcId;
}
string Task::getTask_Monster_Id(void)
{
	return task_monster_id;
}
int    Task::getTask_Monster_Num(void)
{
	return task_monster_num;
}
set<string> Task::getTask_Goods_Id(void)
{
	return task_goods_id;
}
int    Task::getTask_Gold_Num(void)
{
	return task_gold_num;
}
int    Task::getTask_Exp(void)
{
	return task_exp;
}
*/