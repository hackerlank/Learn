#ifndef BASE_THREAD_MANAGER_H
#define BASE_THREAD_MANAGER_H
#include "baseEntry.h"
#include "baseLock.h"
#include "baseThread.h"

template<typename T>
class TaskThreadManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>
{
	private:
		DWORD m_maxCount;
		DWORD m_minCount;
		RWLock rwlock;
		DWORD getMaxCount()
		{
			return m_maxCount;
		}
		DWORD getMinCount()
		{
			return m_minCount;
		}
		void setMaxCount(const DWORD count)
		{
			m_maxCount = count;
		}
		void setMinCount(const DWORD count)
		{
			m_minCount = count;
		}
	public:
		TaskThreadManager()
		{
			m_minCount = 0;
			m_maxCount = 0;
		}
		~TaskThreadManager()
		{
		}
		bool init(const DWORD min = 1,const DWORD max = 1,const std::string name = "thread",void *param = NULL)
		{
			setMinCount(min);
			setMaxCount(max);
			bool bret = true;
			rwlock.wrlock();
			for(size_t index = 0;index < getMaxCount();++index)
			{
				T *thread = new T;
				if(thread)
				{
					thread->initParam(param);
					if(index < getMinCount() && !thread->start())
					{
						DELETE(thread);
						bret = false;
						break;
					}
					if(!addEntry(thread))
					{
						DELETE(thread);
						bret = false;
						break;
					}
				}
				else
				{
					bret = false;
					break;
				}
			}
			rwlock.unlock();
			return bret;
		}
		T* getAverageOne()
		{
			struct GetBest : public EntryCallBack<T>
			{
				T *thread;
				bool findFlg;
				GetBest() : thread(NULL),findFlg(false){}
				bool exec(T *entry)
				{
					if(!entry->isAlive())
					{
						if(!entry->start())
						{
							return false;
						}
						findFlg = true;
						thread = entry;
					}
					if(!thread || (entry->taskSize() < thread->maxTaskSize()))
					{
						thread = entry;
					}
					return true;
				}
			};
			GetBest exec;
			rwlock.rdlock();
			execEveryEntry<T>(exec);
			rwlock.unlock();
			return exec.thred;
		}
		T *getOne()
		{
			struct GetBest : public EntryCallBack<T>
			{
				T *thread;
				GetBest() : thread(NULL){}
				bool exec(T *entry)
				{
					if(!entry->isAlive())
					{
						if(!entry->start())
						{
							return false;
						}	
					}
					if(entry->taskSize() < entry->maxTaskSize())
					{
						thread = entry;
						return false;
					}
					return true;
				}
			};
			GetBest exec;
			rwlock.rdlock();
			execEveryEntry<T>(exec);
			rwlock.unlock();
			return exec.thread;
		}
		DWORD taskCount()
		{
			struct GetBest : public EntryCallBack<T>
			{
				DWORD size;
				GetBest() : size(0){}
				bool exec(T *thread)
				{
					size += thread->taskSize();
					return true;
				}
			};
			GetBest exec;
			rwlock.rdlock();
			execEveryEntry<T>(exec);
			rwlock.unlock();
			return exec.size;
		}
		void final()
		{
			struct RemoveAll : public RemoveEntry_Pred<T>
			{
				bool isIt(T *entry)
				{
					if(entry)
					{
						entry->final();
						entry->join();
					}
					return true;
				}
			};
			rwlock.wrlock();
			RemoveAll exec;
			removeEntry_if<T>(exec);
			rwlock.unlock();
		}
	
		template<class YourEntry>
		bool execEvery(EntryCallBack<YourEntry> &exec)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return ret;
		}
		bool addThread(Thread *entry)
		{
			bool bret = false;
			rwlock.wrlock();
			bret = addEntry(entry);
			return bret;
		}
		void removeThread(Thread *entry)
		{
			rwlock.wrlock();
			removeEntry(entry);
			rwlock.unlock();
		}
		T* getThreadByID(const WORD id)
		{
			T *ret = NULL;
			rwlock.rdlock();
			ret = (T*)getEntryByID(id);
			return ret;
		}
};

#endif
		

