#include "taskQueue.h"

void TaskQueue::addTask(const unsigned long id)
{
    pthread_mutex_lock(&m_mutex);
    m_queue.push(id);
    pthread_mutex_unlock(&m_mutex);
}

void TaskQueue::checkQueue()
{
    pthread_mutex_lock(&m_mutex);
    while(!m_queue.empty())
    {
        unsigned long id = m_queue.front();
        m_queue.pop();
        m_tempQueue.push(id);
    }
    pthread_mutex_unlock(&m_mutex);

    while(!m_tempQueue.empty())
    {
        unsigned long id = m_tempQueue.front();
        m_tempQueue.pop();
        add(id);
    }
}
