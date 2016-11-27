#include "task.h"
#include "flyer.h"
#include "taskManager.h"

TaskMessageDispatcher Task::s_taskMsgDispatcher("task消息处理器");

Task::Task(const int socket) : Connect(socket)
{
}

Task::~Task()
{
}

MsgRet Task::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    do
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(m_id);
        if(task)
        {
            ret = s_taskMsgDispatcher.dispatch(task,message);
        }
    }while(false);
    return ret;
}
