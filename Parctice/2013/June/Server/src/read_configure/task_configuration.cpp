#include"task_configuration.h"
Task_Configuration::Task_Configuration(char* _id, char* _name, char* _recNpcId,
	char* _finNpcId, int _freq, int _type, unsigned _inFors, unsigned _prestige, unsigned _gold, unsigned _exp, int _giveType, int _chapt,
	unsigned _level, list<need_t*> _need, set<give_t*> _give, set<touch_t*> _touch,
	set<recv_t*> _recv, int _subType, bool _isLastOfThisChapt)
{
	strncpy(taskId, _id, sizeof(taskId));
	strncpy(taskName, _name, sizeof(taskName));
	strncpy(recNpcId, _recNpcId, sizeof(recNpcId));
	strncpy(finNpcId, _finNpcId, sizeof(finNpcId));
	frequency = _freq;
	taskType = _type;
	taskChapt = _chapt;
	taskLevel = _level;
	inFors = _inFors;
	prestige = _prestige;
	taskGold = _gold;
	taskExp = _exp;
	giveType = _giveType;
	taskNeed = _need;
	taskGive = _give;
	taskTouch = _touch;
	taskRecv = _recv;
	subType = _subType;
	isLastOfThisChapt = _isLastOfThisChapt;
}

char* Task_Configuration::getTaskId(void)
{
	return taskId;
}
char* Task_Configuration::getTaskName(void)
{
	return taskName;
}
char* Task_Configuration::getRecNpcId(void)
{
	return recNpcId;
}
char* Task_Configuration::getFinNpcId(void)
{
	return finNpcId;
}

//任务一天可接的次数
int Task_Configuration::getFrequency(void)
{
	return frequency;
}

int Task_Configuration::getTask_type(void)
{
	return taskType;
}

int Task_Configuration::getTask_chapt(void)
{
	return taskChapt;
}

unsigned Task_Configuration::getTask_level(void)
{
	return taskLevel;
}

unsigned Task_Configuration::getInFors(void)
{
	return inFors;
}
unsigned Task_Configuration::getPrestige(void)
{
	return prestige;
}

unsigned Task_Configuration::getTask_gold(void)
{
	return taskGold;
}

unsigned Task_Configuration::getTask_exp(void)
{
	return taskExp;
}

int Task_Configuration::getTask_giveType(void)
{
	return giveType;
}

int Task_Configuration::getSubType()
{
	return subType;
}

bool Task_Configuration::getIsLastOfThisChapt()
{
	return isLastOfThisChapt;
}

list<need_t*> Task_Configuration::getTask_need(void)
{
	return taskNeed;
}

set<give_t*> Task_Configuration::getTask_give(void)
{
	return taskGive;
}

set<touch_t*> Task_Configuration::getTask_touch(void)
{
	return taskTouch;
}

set<recv_t*> Task_Configuration::getTask_recv(void)
{
	return taskRecv;
}