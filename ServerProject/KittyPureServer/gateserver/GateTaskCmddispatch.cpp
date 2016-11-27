#include "GateTaskCmddispatch.h"

bool GateTaskCmdHandle::reqLoginGateway(GatewayTask *task,const ProtoMsgData::ReqLoginGateway *message)
{
    if(!task || !message) 
    {
        return false;
    }
    return task->loginGateway(message);
}

