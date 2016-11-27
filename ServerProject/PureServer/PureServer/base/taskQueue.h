#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include "task.h"
#include <deque>
#include <queue>
#include <pthread.h>

class TaskQueue
{
    private:
        pthread_mutex_t m_mutex;
        std::queue<boost::shared_ptr<Task>,std::deque<boost::shared_ptr<Task> > > m_queue;
        std::queue<boost::shared_ptr<Task>,std::deque<boost::shared_ptr<Task> > > m_tempQueue;
    public:
        TaskQueue()
        {
            pthread_mutex_init(&m_mutex,NULL);
        }
        virtual ~TaskQueue()
        {
        }
        void addTask(boost::shared_ptr<Task> task);
        virtual bool add(boost::shared_ptr<Task> task) = 0;
        void checkQueue();
};

#endif

