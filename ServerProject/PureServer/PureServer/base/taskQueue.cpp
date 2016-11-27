#include "taskQueue.h"

void TaskQueue::addTask(boost::shared_ptr<Task> task)
{
    pthread_mutex_lock(&m_mutex);
    m_queue.push(task);
    pthread_mutex_unlock(&m_mutex);
}

void TaskQueue::checkQueue()
{
    pthread_mutex_lock(&m_mutex);
    while(!m_queue.empty())
    {
        boost::shared_ptr<Task> task = m_queue.front();
        m_queue.pop();
        m_tempQueue.push(task);
    }
    pthread_mutex_unlock(&m_mutex);

    while(!m_tempQueue.empty())
    {
        boost::shared_ptr<Task> task = m_tempQueue.front();
        m_tempQueue.pop();
        add(task);
    }
}
