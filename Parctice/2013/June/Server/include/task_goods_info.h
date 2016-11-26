/****************************************************************
 * Filename: task_goods.cpp
 * 
 * Description: 任务道具信息
 *
 * Original Author : bison, 2012-7-6
 *
 ****************************************************************/

#ifndef _TASK_GOODS_H_
#define _TASK_GOODS_H_

#include"command_other_function_all_over.h"
#include<time.h>

//任务道具信息
class TaskGoodsInfo
{
	private:
		char taskGoodsId[51];
		char monsterId[1024];
		double rate;
		
	public:
		TaskGoodsInfo(char* _taskGoodsId, char* _monsterId, double _rate);
		//该次是否掉落
		bool dropTaskGoodsOk(void);
		//获取任务道具ID
		char* getTaskGoodsId(void);
		//获取对应怪物ID
		char* getMonsterId(void);
		//检查死亡的怪物是否掉落该道具
		bool isMonsterDrop(char* deadMonsterId);
};
#endif
