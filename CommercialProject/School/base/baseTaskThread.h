#ifndef BASE_TASK_THREAD_H
#define BASE_TASK_THREAD_H
#include "baseThread.h"
class TaskThread : public Thread
{
	public:
		TaskThread(const char *name,bool joinable = true);
		virtual ~TaskThread();
		virtual SWORD taskSize() const = 0;
		virtual SWORD maxTaskSize() const = 0;
};
#endif
