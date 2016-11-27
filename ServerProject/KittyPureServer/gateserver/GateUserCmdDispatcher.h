/**
 * \file
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#ifndef _GATE_USER_CMD_DISPATCHER
#define _GATE_USER_CMD_DISPATCHER

#include <string.h>
#include "Fir.h"
#include "Command.h"
#include "GatewayServer.h"
#include "dispatcher.h"
#include "zCmdHandle.h"
#include "LoginUserCommand.h"
#include "SuperCommand.h"
#include "login.pb.h"
#include "userinfo.pb.h"

class GateUser;
class GatewayTask;

enum LoginState
{
	LOGIN_NONE = 0, // 初始状态
	LOGIN_WAIT, // 通过平台验证，等待玩家登录
	LOGIN_LOGINING, //正在登录，其它网关，不再允许重复登录,登录流程结束，回到初始状态,或者删除这个KEY
};


class GateUserCmdHandle : public zCmdHandle
{
	public:

		virtual void init()
		{
			GatewayTask::gate_user_cmd_dispatcher.func_reg<ProtoMsgData::ReqCreateRole>(ProtoCmdCallback<GateUser,ProtoMsgData::ReqCreateRole>::ProtoFunction(this, &GateUserCmdHandle::create_role));

		}

		bool create_role(GateUser* u, const ProtoMsgData::ReqCreateRole *message);
};

#endif
