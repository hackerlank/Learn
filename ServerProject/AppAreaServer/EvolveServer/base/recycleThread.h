#ifndef RECYCLE_THREAD_H
#define RECYCLE_THREAD_H
#include "taskQueue.h"
#include "head.h"
#include "flyer.h"
#include "thread.h"

class RecycleThread : public Thread,public TaskQueue
{
    private:
        std::set<unsigned long> m_taskSet;
    public:
        RecycleThread(unsigned int id); 
        ~RecycleThread();
        bool init();
        unsigned long size();
        bool add(const unsigned long id);
        virtual void run();
};

#endif


