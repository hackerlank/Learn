#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include <deque>
#include <queue>
#include <pthread.h>
#include "connect.h"

class TaskQueue
{
    private:
        pthread_mutex_t m_mutex;
        std::queue<boost::shared_ptr<Connect>,std::deque<boost::shared_ptr<Connect> > > m_queue;
        std::queue<boost::shared_ptr<Connect>,std::deque<boost::shared_ptr<Connect> > > m_tempQueue;
    public:
        TaskQueue()
        {
            pthread_mutex_init(&m_mutex,NULL);
        }
        virtual ~TaskQueue()
        {
        }
        void addTask(boost::shared_ptr<Connect> task);
        virtual bool add(boost::shared_ptr<Connect> task)
        {
            return false;
        }
        void checkQueue();
};

#endif

