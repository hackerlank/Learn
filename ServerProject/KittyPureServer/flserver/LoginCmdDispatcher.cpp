/**
 * \file
 * \version  $Id: LoginCmdDispatcher.cpp 64 2013-04-23 02:05:08Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#include "LoginCmdDispatcher.h"
bool LoginCmdHandle::reqRegister(LoginTask* task, const ProtoMsgData::ReqRegister *message)
{
    if(task && message)
    {
        return task->registerAccount(message);
    }
    return false;
}

bool LoginCmdHandle::reqGateway(LoginTask* task, const ProtoMsgData::ReqGateway *message)
{
    if(task && message)
    {
        return task->getGatewayInfo(message);
    }
    return false;
}
