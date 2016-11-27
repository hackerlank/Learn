#ifndef RECYCLE_THREAD_H
#define RECYCLE_THREAD_H
#include "singleton.h"
#include "taskQueue.h"
#include "head.h"

class RecycleThread : public Thread,public TaskQueue,public Singleton<RecycleThread>
{
    private:
        std::map<unsigned long,boost::shared_ptr<Connect> > m_taskSet;
    private:
        friend class Singleton<RecycleThread>;
        RecycleThread() : Thread("回收线程")
        {
        }
        ~RecycleThread()
        {
        }
    public:
        bool add(boost::shared_ptr<Connect> task);
        virtual void run();
};

#endif


