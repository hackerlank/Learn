#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <map>
#include "task.h"

class TaskManager : public Singleton<TaskManager>
{
    private:
        std::map<unsigned long,boost::shared_ptr<Task> > m_taskMap;
    private:
        friend class Singleton<TaskManager>;
        TaskManager()
        {
        }
        ~TaskManager()
        {
        }
    public:
        bool addTask(boost::shared_ptr<Task> task);
        inline size_t size() const
        {
            return m_taskMap.size();
        }
        void randSendMsg(const unsigned long cnt);
        void randCloseFd(const unsigned long cnt);
        void randOpDB(const unsigned long cnt);
};

#endif

