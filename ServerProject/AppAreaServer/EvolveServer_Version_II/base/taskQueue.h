#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H
#include <deque>
#include <queue>
#include <pthread.h>

class TaskQueue
{
    private:
        pthread_mutex_t m_mutex;
        std::queue<unsigned long,std::deque<unsigned long> >m_queue;
        std::queue<unsigned long,std::deque<unsigned long> >m_tempQueue;
    public:
        TaskQueue()
        {
            pthread_mutex_init(&m_mutex,NULL);
        }
        virtual ~TaskQueue()
        {
        }
        void addTask(const unsigned long id);
        virtual bool add(const unsigned long id)
        {
            return false;
        }
        void checkQueue();
};

#endif

