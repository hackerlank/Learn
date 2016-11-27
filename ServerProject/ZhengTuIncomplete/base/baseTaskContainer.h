#ifndef BASE_TASK_CONTAINER_H
#define BASE_TASK_CONTAINER_H
#include "baseLock.h"
#include "baseEntry.h"
#include <queue>
#include <ext/pool_allocator.h>

template<typename T>
class TaskQueue
{
	public:
		TaskQueue():_size(0)
		{
		}
		virtual ~TaskQueue()
		{
		}
		inline void add(T *task)
		{
			mlock.lock();
			_queue.push(task);
			++_size;
			mlock.unlock();
		}
		inline void check_queue()
		{
			mlock.lock();
			while(!_queue.empty())
			{
				_temp_queue.push(_queue.front());
				_queue.pop();
			}
			_size = 0;
			mlock.unlock();
			while(!_temp_queue.empty())
			{
				T *task = _temp_queue.front();
				_temp_queue.pop();
				_add(task);
			}
		}
	protected:
		virtual void _add(T *task) = 0;
		DWORD _size;
		Mutex mlock;
		std::queue<T*,std::deque<T*,__gnu_cxx::__pool_alloc<T*> > > _queue;
		std::queue<T*,std::deque<T*,__gnu_cxx::__pool_alloc<T*> > > _temp_queue;
};

#endif

