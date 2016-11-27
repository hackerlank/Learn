#ifndef GATE_TASK_CMD_DISPATCH_H
#define GATE_TASK_CMD_DISPATCH_H

#include <string.h>
#include "Fir.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "GatewayTask.h"
#include "login.pb.h"

class GateTaskCmdHandle : public zCmdHandle
{
    public:
        GateTaskCmdHandle()
        {
        }

        virtual void init()
        {
            GatewayTask::gate_task_cmd_dispatcher.func_reg<ProtoMsgData::ReqLoginGateway>(ProtoCmdCallback<GatewayTask,ProtoMsgData::ReqLoginGateway>::ProtoFunction(this, &GateTaskCmdHandle::reqLoginGateway));
        }

        //请求登陆网关
        bool reqLoginGateway(GatewayTask *task,const ProtoMsgData::ReqLoginGateway *message);
};

#endif
          
