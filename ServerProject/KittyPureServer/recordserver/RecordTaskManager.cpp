/**
 * \file
 * \version  $Id: RecordTaskManager.cpp 36 2013-04-07 11:42:48Z  $
 * \author  ,
 * \date 2013年04月07日 15时28分53秒 CST
 * \brief 管理记录连接的容器
 *
 * 
 */


#include <iostream>

#include "RecordTask.h"
#include "RecordTaskManager.h"

RecordTaskManager *RecordTaskManager::instance = NULL;

/**
 * \brief 向唯一性验证容器中添加一个子连接任务
 *
 * \param task 子连接任务
 * \return 添加连接是否成功
 */
bool RecordTaskManager::uniqueAdd(RecordTask *task)
{
	RecordTaskHashmap_const_iterator it;
	rwlock.wrlock();
	it = RecordTaskSet.find(task->getID());
	if (it != RecordTaskSet.end())
	{
		Fir::logger->error(__PRETTY_FUNCTION__);
		rwlock.unlock();
		return false;
	}
	RecordTaskSet.insert(RecordTaskHashmap_pair(task->getID(), task));
	rwlock.unlock();
	return true;
}

/**
 * \brief 从唯一性容器中移除一个子连接任务
 *
 * \param task 子连接任务
 * \return 移除是否成功
 */
bool RecordTaskManager::uniqueRemove(RecordTask *task)
{
	RecordTaskHashmap_iterator it;
	rwlock.wrlock();
	it = RecordTaskSet.find(task->getID());
	if (it != RecordTaskSet.end())
	{
		RecordTaskSet.erase(it);
	}
	else
		Fir::logger->warn(__PRETTY_FUNCTION__);
	rwlock.unlock();
	return true;
}

bool RecordTaskManager::broadcastByType(ServerType type,const void *pstrCmd, int nCmdLen)
{
	rwlock.rdlock();                             
	for(RecordTaskHashmap_iterator it = RecordTaskSet.begin(); it != RecordTaskSet.end() ; it ++)    
	{
		if (it->second && it->second->getType() == type)
		{
            it->second->sendCmd(pstrCmd, nCmdLen); 
		}
	}                                            
	rwlock.unlock();                             
	return true;
}

bool RecordTaskManager::sceneTaskEmpty()
{
	RecordTaskHashmap_iterator it;               
	rwlock.rdlock();                             
	it = RecordTaskSet.begin();                  
	for (; it != RecordTaskSet.end() ; it ++)    
	{
		if (it->second && it->second->getType() == SCENESSERVER)
		{
			rwlock.unlock();                             
			return false;
		}
	}                                            
	rwlock.unlock();                             
	return true;
}
