#ifndef RECYCLE_THREAD_H
#define RECYCLE_THREAD_H
#include "singleton.h"
#include "taskQueue.h"
#include "head.h"
#include "flyer.h"
#include "thread.h"

class RecycleThread : public Thread,public TaskQueue,public Singleton<RecycleThread>
{
    private:
        std::set<unsigned long> m_taskSet;
    private:
        friend class Singleton<RecycleThread>;
        RecycleThread() : Thread("回收线程")
        {
        }
        ~RecycleThread()
        {
        }
    public:
        bool add(const unsigned long id);
        virtual void run();
};

#endif


