/**
 * \file
 * \version  $Id: RecordTaskManager.h 36 2013-04-07 11:42:48Z  $
 * \author  ,
 * \date 2013年04月07日 15时28分53秒 CST
 * \brief 管理记录连接的容器
 *
 * 
 */


#ifndef _RecordTaskMANAGER_H_
#define _RecordTaskMANAGER_H_

#include <iostream>
#include <unordered_map>

#include "RecordTask.h"
#include "zRWLock.h"

/**
 * \brief 计费服务器子连接管理器
 *
 */
class RecordTaskManager : public Singleton<RecordTaskManager>
{	
	friend class Singleton<RecordTaskManager>;
	public:
		~RecordTaskManager() {};
		bool uniqueAdd(RecordTask *task);
		bool uniqueRemove(RecordTask *task);
		//bool broadcastByID(const WORD wdServerID, const void *pstrCmd, int nCmdLen);
//		RecordTask *getTaskByID(const WORD wdServerID);
		bool sceneTaskEmpty();
        bool broadcastByType(ServerType type,const void *pstrCmd, int nCmdLen);

	private:
		static RecordTaskManager *instance;
		RecordTaskManager() {};
		typedef std::unordered_map<WORD, RecordTask *> RecordTaskHashmap;
		typedef RecordTaskHashmap::iterator RecordTaskHashmap_iterator;
		typedef RecordTaskHashmap::const_iterator RecordTaskHashmap_const_iterator;
		typedef RecordTaskHashmap::value_type RecordTaskHashmap_pair;
        //brief 容器访问互斥变量
		zRWLock rwlock;
		RecordTaskHashmap RecordTaskSet;

};

#endif

