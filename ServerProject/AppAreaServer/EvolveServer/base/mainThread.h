#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H
#include "taskQueue.h"
#include "head.h"
#include "thread.h"
#include "flyer.h"

class MainThread : public Thread,public TaskQueue
{
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_epollEventVec;
        std::set<unsigned long> m_taskSet;
    public:
        MainThread(const unsigned int id); 
        ~MainThread();
        bool init();
        unsigned long size();
        bool add(const unsigned long id);
        virtual void run();
        void addRecycle(const unsigned long id,const bool del = true);
};

#endif


