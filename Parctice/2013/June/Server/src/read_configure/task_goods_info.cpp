/****************************************************************
 * Filename: task_goods.cpp
 * 
 * Description: 任务道具信息
 *
 * Original Author : bison, 2012-7-6
 *
 ****************************************************************/
#include"task_goods_info.h"
#include"my_time.h"

TaskGoodsInfo::TaskGoodsInfo(char* _taskGoodsId, char* _monsterId, double _rate)
{
	strncpy(taskGoodsId, _taskGoodsId, sizeof(taskGoodsId));
	strncpy(monsterId, _monsterId, sizeof(monsterId));
	rate = _rate;
	//cout<<"taskGoodsId "<<taskGoodsId<<"monsterId "<<monsterId<<" rate "<<rate<<endl;
}
 
bool TaskGoodsInfo::dropTaskGoodsOk(void)
{
	//srand(MY_TV_USEC + MY_TV_SEC);
	int randNum = rand() % 100;
	if (randNum < rate)
	{
		return true;
	} else {
		return false;
	}
}

//获取任务道具ID
char* TaskGoodsInfo::getTaskGoodsId(void)
{
	return taskGoodsId;
}

//获取对应怪物ID
char* TaskGoodsInfo::getMonsterId(void)
{
	return monsterId;
}

bool TaskGoodsInfo::isMonsterDrop(char* deadMonsterId)
{
	char* temp = monsterId;
	cout<<"[Bison Test drop task goods] MonsterIdSet is "<<temp<<endl;
	int pos = 0;
	char oneMonsterId[51];
	int len = strlen(temp);
	while (len > 0)
	{
		pos = findChar(temp, ',', len);
		if (pos == -1)
		{
			//防止最后一个没加冒号
			strncpy(oneMonsterId, temp, len + 1);
			temp = temp + len;
		} else {
			sub_str(oneMonsterId, temp, 0, pos);
			temp = temp + pos + 1;
		}
		len = strlen(temp);
		
		if (!strcmp(oneMonsterId, deadMonsterId))
		{
			cout<<"[Bison Test drop task goods] oneMonsterId "<<oneMonsterId<<endl;
			return true;
		}
	}
	cout<<"[Bison test drop task goods monid is "<<deadMonsterId<<endl;
	return false;
}