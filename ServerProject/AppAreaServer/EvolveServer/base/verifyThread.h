#ifndef VERIFY_THREAD_H
#define VERIFY_THREAD_H
#include "taskQueue.h"
#include "head.h"
#include "thread.h"
#include "flyer.h"

class VerifyThread : public Thread,public TaskQueue
{
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_epollEventVec;
        std::set<unsigned long> m_taskSet;
    public:
        VerifyThread(const unsigned int id);
        ~VerifyThread();
        bool init();
        unsigned long size();
        bool add(const unsigned long id);
        virtual void run();
        bool addMain(const unsigned long id);
        void addRecycle(const unsigned long id,const bool del = true);
};

#endif


