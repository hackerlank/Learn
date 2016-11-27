#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include "head.h"
#include "task.h"

class TaskManager : public Singleton<TaskManager>
{
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
        boost::shared_ptr<Task> getTask(const unsigned long id);
        inline size_t size() const
        {
            return m_taskMap.size();
        }
        void eraseTask(const unsigned long taskID);
        void randCloseFd(const unsigned long cnt);
        void randOpDB(const unsigned long cnt);
        bool sendServerMsg(const unsigned int serverID,const google::protobuf::Message &message);
        boost::shared_ptr<Task> getServerTask(const unsigned int serverID);
        void sendHeartMsg(const unsigned cycle);
        bool addGatewayTask(const unsigned charID,const unsigned long id);
        boost::shared_ptr<Task> getGatewayTask(const unsigned charID);
        boost::shared_ptr<Task> getServerTaskByType(const ProtoMsgData::ServerType type);
    private:
        std::map<unsigned long,boost::shared_ptr<Task> > m_taskMap;
        //专门用来装gatewayTask的
        std::map<unsigned long,unsigned long>m_charIDMap;
};

#endif

