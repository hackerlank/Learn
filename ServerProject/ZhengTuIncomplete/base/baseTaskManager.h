#ifndef BASE_TASK_MANAGER_H
#define BASE_TASK_MANAGER_H

#include "baseEntry.h"
#include "baseLock.h"

template<typename T>
class TaskManager : public EntryManager<EntryID>
{
	public:
		TaskManager() {}
		~TaskManager() {}
		bool addTask(T *task)
		{
			m_rwLock.wrlock();
			bool bret = addEntry(task);
			m_rwLock.unlock();
			return bret;
		}

		void removeTask(T *task)
		{
			m_rwLock.wrlock();
			removeEntry(task);
			m_rwLock.unlock();
		}

		DWORD getSize()
		{
			return (DWORD)size();
		}

		T *getTaskByID(const DWORD id)
		{
			m_rwLock.rdlock();
			T *ret = (T*)getEntryByID(id);
			m_rwLock.unlock();
			return ret;
		}

		DWORD getTaskSizeByType(const DWORD taskType)
		{
			struct GetTaskCountExec : EntryCallBack<T>
			{
				const DWORD taskType;
				DWORD num;
				GetTaskCountExec(const DWORD _taskType) : taskType(_taskType),num(0) {} ;
				bool exec(T *entry)
				{
					if(entry->getType() == taskType)
					{
						++num;
					}
					return true;
				}
			}exec(taskType);

			execEveryTask(exec);
			return exec.num;
		}

		/// @brief 唯一性认证
		bool uniqueVerify(const DWORD id)
		{
			return NULL == getTaskByID(id);
		}

		bool uniqueAdd(T *task)
		{
			return addEntry(task);
		}

		bool uniqueRemove(T *task)
		{
			removeTask(task);
			return true;
		}
		
		bool broadcast(const void *cmd,const DWORD cmdLen)
		{
			struct Broadcast : public EntryCallBack<T>
			{
				const void *cmd;
				const DWORD cmdLen;
				Broadcast(const void *_cmd,const DWORD _cmdLen) : cmd(_cmd),cmdLen(_cmdLen)
				{
				}
				bool exec(T *task)
				{
					task->sendCmd(cmd,cmdLen);
					return true;
				}
			};

			Broadcast exec(cmd,cmdLen);
			execEveryTask(exec);
			return true;
		}

		bool brocastToID(const DWORD serverID,const void *cmd,const DWORD cmdLen)
		{
			bool ret = false;
			m_rwLock.rdlock();
			T *task = (T*)getEntryByID(serverID);
			if(task)
			{
				ret = task->sendCmd(cmd,cmdLen);
			}
			m_rwLock.unlock();
			return ret;
		}
		
		///广播到某种类型的服务器
		bool broadcastToTypeExceptOne(const DWORD taskType,const DWORD exceptID,const void *cmd,const DWORD cmdLen)
		{
			struct Broadcast : public EntryCallBack<T>
			{
				const void *cmd;
				const DWORD cmdLen;
				const DWORD taskType;
				const DWORD exceptID;
				Broadcast(const void *_cmd,const DWORD _cmdLen,const DWORD _taskType,const DWORD _exceptID) : cmd(cmd),cmdLen(_cmdLen),taskType(_taskType),exceptID(_exceptID)
				{
				}
				bool exec(T *task)
				{
					if(task->getType() == taskType && task->id != exceptID)
					{
						task->sendCmd(cmd,cmdLen);
					}
					return true;
				}
			};

			Broadcast exec(cmd,cmdLen,taskType,exceptID);
			execEveryTask(exec);
			return true;
		}
		
		template<typename YourEntry>
		bool execEveryTask(EntryCallBack<YourEntry> &callback)
		{
			m_rwLock.rdlock();
			bool ret = execEveryEntry<>(callback);
			m_rwLock.unlock();
			return ret;
		}
	protected:
		RWLock m_rwLock;
};

#endif
