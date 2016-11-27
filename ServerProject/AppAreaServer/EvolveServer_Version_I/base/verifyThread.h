#ifndef VERIFY_THREAD_H
#define VERIFY_THREAD_H
#include "singleton.h"
#include "taskQueue.h"
#include "head.h"
#include "thread.h"
#include "flyer.h"

class VerifyThread : public Thread,public TaskQueue,public Singleton<VerifyThread>
{
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_epollEventVec;
        std::set<unsigned long> m_taskSet;
    private:
        friend class Singleton<VerifyThread>;
        VerifyThread() : Thread("验证线程")
        {
            m_epfd = epoll_create(atol(Flyer::globalConfMap["threadprocesstask"].c_str()));
        }
        ~VerifyThread()
        {
            TEMP_FAILURE_RETRY(::close(m_epfd));
        }
    public:
        bool add(const unsigned long id);
        virtual void run();
        void addRecycle(const unsigned long id,const bool del = true);
        void addMain(const unsigned long id);
};

#endif


