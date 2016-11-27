#ifndef TASK_H
#define TASK_H
#include "head.h"
#include "connect.h"

class Task;
typedef MessageDispatcher<boost::shared_ptr<Task> > TaskMessageDispatcher;

class Task: public Connect 
{
    public:
        Task(const int socket);
        virtual ~Task();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
    public:
        static TaskMessageDispatcher s_taskMsgDispatcher;
};

#endif
