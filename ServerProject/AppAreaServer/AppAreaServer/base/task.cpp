#include "task.h"
#include "flyer.h"

TaskMessageDispatcher Task::s_taskMsgDispatcher("task消息处理器");

Task::Task(const int socket) : Connect(socket)
{
}

Task::~Task()
{
}

MsgRet Task::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_False;
#if 0
    do
    {
        boost::shared_ptr<Task> task = boost::dynamic_pointer_cast<Task>(getPtr());
        if(task)
        {
            ret = s_taskMsgDispatcher.dispatch(task,message);
        }
    }while(false);
#endif
    return ret;
}
