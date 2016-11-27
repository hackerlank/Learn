#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include "thread.h"
#include "singleton.h"
#include "taskQueue.h"
#include <map>

class MainThread : public Thread,public TaskQueue,public Singleton<MainThread>
{
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_epollEventVec;
        std::map<unsigned long,boost::shared_ptr<Task> > m_taskSet;
    private:
        friend class Singleton<MainThread>;
        MainThread() : Thread("主线程")
        {
            m_epfd = epoll_create(THREAD_PROCESS_MAX_TASK_NUM);
        }
        ~MainThread()
        {
            TEMP_FAILURE_RETRY(::close(m_epfd));
        }
    public:
        bool add(boost::shared_ptr<Task> task);
        virtual void run();
};

#endif


