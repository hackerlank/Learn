/**
 * \file
 * \version  $Id: LoginCmdDispatcher.h 42 2013-04-10 07:33:59Z  $
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#ifndef _LOGIN_USER_CMD_DISPATCHER
#define _LOGIN_USER_CMD_DISPATCHER

#include <string.h>
#include "Fir.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "LoginTask.h"
#include "login.pb.h"

class LoginCmdHandle : public zCmdHandle
{
	public:
		LoginCmdHandle()
		{
		}

		void init()
		{
            LoginTask::login_user_dispatcher.func_reg<ProtoMsgData::ReqRegister>(ProtoCmdCallback<LoginTask,ProtoMsgData::ReqRegister>::ProtoFunction(this, &LoginCmdHandle::reqRegister));

            LoginTask::login_user_dispatcher.func_reg<ProtoMsgData::ReqGateway>(ProtoCmdCallback<LoginTask,ProtoMsgData::ReqGateway>::ProtoFunction(this, &LoginCmdHandle::reqGateway));

        }
        //请求注册
        bool reqRegister(LoginTask* task, const ProtoMsgData::ReqRegister *message);
        //请求网关信息
        bool reqGateway(LoginTask* task, const ProtoMsgData::ReqGateway *message);
};

#endif
