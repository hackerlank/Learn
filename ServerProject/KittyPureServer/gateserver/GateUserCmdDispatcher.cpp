/**
 * \file
 * \author   ,
 * \date 2013年03月27日 12时14分48秒 CST
 * \brief 定义用户登录相关命令处理文件，注册给dispatcher
 *
 */

#include "GatewayTask.h"
#include "GateUserCmdDispatcher.h"
#include "GatewayServer.h"
#include "SceneClientManager.h"
#include "RecordClient.h"
#include "zMisc.h"

bool GateUserCmdHandle::create_role(GateUser* u, const ProtoMsgData::ReqCreateRole *message)
{
	if (!u)
    {
        return true;
    }

	if (!u->isCreateState())
	{ 
        Fir::logger->debug("[登录网关]:网关请求db创建角色失败(用户不在创建状态,%s)",u->gatewaytask->m_accountInfo.account);
		return true;
	}
	if (!u->gatewaytask)
	{
        Fir::logger->debug("[登录网关]:网关请求db创建角色失败(gatewaytask为空,%s)",u->gatewaytask->m_accountInfo.account);
		return true;
	}

    RecordClient* recordClient = MgrrecordClient.GetMinPlayerRecord();
    if(recordClient == NULL)
    {
        Fir::logger->debug("[登录网关]:网关请求db创建角色失败(创建角色db出错,%s)",u->gatewaytask->m_accountInfo.account);
		return true;
    }

    CMD::RECORD::t_CreateChar_GateRecord req;
    req.accountInfo = u->gatewaytask->m_accountInfo;
    std::string ret;
    encodeMessage(&req,sizeof(req),ret);
	recordClient->sendCmd(ret.c_str(),ret.size());
    Fir::logger->debug("[登录网关]:网关请求db创建角色成功(向db注册新角色,%s)",u->gatewaytask->m_accountInfo.account);
	return true;
}
