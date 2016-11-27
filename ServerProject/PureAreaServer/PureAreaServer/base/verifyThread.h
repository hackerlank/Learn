#ifndef VERIFY_THREAD_H
#define VERIFY_THREAD_H
#include "singleton.h"
#include "taskQueue.h"
#include "head.h"

class VerifyThread : public Thread,public TaskQueue,public Singleton<VerifyThread>
{
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_epollEventVec;
        std::map<unsigned long,boost::shared_ptr<Connect> > m_taskSet;
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
        bool add(boost::shared_ptr<Connect> task);
        virtual void run();
};

#endif


