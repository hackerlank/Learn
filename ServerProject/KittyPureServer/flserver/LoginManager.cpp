/**
 * \file
 * \version  $Id: LoginManager.cpp 2699 2005-08-30 13:53:37Z yhc $
 * \author  Songsiliang,
 * \date 2004年12月17日 13时17分28秒 CST
 * \brief 登陆连接管理容器
 *
 * 
 */

#include "zMisc.h"
#include "LoginTask.h"
#include "LoginManager.h"
#include "FLCommand.h"
#include "GYListManager.h"
#include "ServerManager.h"
#include "SlaveCommand.h"
#include "login.pb.h"
#include "extractProtoMsg.h"

DWORD LoginManager::maxGatewayUser=MAX_GATEWAYUSER;

/**
 * \brief 向容器中添加一个连接
 *
 * \param task 一个连接任务
 * \return 添加是否成功
 */
bool LoginManager::add(LoginTask *task)
{
	if (task)
	{
		zRWLock_scope_wrlock scope_wrlock(rwlock);
		task->genTempID();
		LoginTaskHashmap_const_iterator it = loginTaskSet.find(task->getTempID());
		DWORD taskID = task->getTempID();
		Fir::logger->debug("向容器中添加一个连接,ID:%d", taskID);
		if (it != loginTaskSet.end())
		{
			Fir::logger->error("向容器中添加一个连接error");
			return false;
		}
		std::pair<LoginTaskHashmap_iterator, bool> p = loginTaskSet.insert(LoginTaskHashmap_pair(task->getTempID(), task));
		return p.second;
	}
	else
	{
		Fir::logger->error("连接任务error");
		return false;
	}
}

/**
 * \brief 从一个容器中移除一个连接
 *
 * \param task 一个连接任务
 */
void LoginManager::remove(LoginTask *task)
{
	if (task)
	{
		zRWLock_scope_wrlock scope_wrlock(rwlock);
		loginTaskSet.erase(task->getTempID());
	}
}

/**
 * \brief 广播指令到指定的登陆连接
 *
 * \param loginTempID 登陆连接的唯一编号
 * \param pstrCmd 待转发的指令
 * \param nCmdLen 待转发的指令长度
 * \return 转发是否成功
 */
bool LoginManager::broadcast(const DWORD loginTempID, const void *pstrCmd, int nCmdLen)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	LoginTaskHashmap_iterator it = loginTaskSet.find(loginTempID);
	if (it != loginTaskSet.end())
		return it->second->sendCmd(pstrCmd, nCmdLen);
	else
	{
		Fir::logger->error("广播指令到指定的登陆连接error");
		return false;
	}
}

bool LoginManager::broadcastNewSession(const DWORD loginTempID, const t_NewLoginSession &session)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	LoginTaskHashmap_iterator it = loginTaskSet.find(loginTempID);
    LoginTask *task = NULL;
	if (it != loginTaskSet.end())
	{
		task = it->second;
        ProtoMsgData::AckGateway ackGateway;
        ackGateway.set_gatewayip(session.pstrIP);
        ackGateway.set_gatewayport(session.wdPort);
        ackGateway.set_ret(true);
        std::string ret;
        encodeMessage(&ackGateway,ret);
		task->sendCmd(ret.c_str(),ret.size());
	}
    Fir::logger->debug("[请求管理服网关返回] (%s,%u,%s,%u,%s)", !task ? "0.0.0.0":task->getIP(),session.loginTempID, session.pstrIP, session.wdPort,session.accountInfo.account);
    //此时需要断开连接
    task->Terminate();
    return true;
}

/**
 * \brief 验证错误时返回新的坐标到指定的客户端
 * \param loginTempID 指定的客户端连接临时编号
 * \param retcode 待返回的代码
 * \param tm 返回信息以后是否断开连接，缺省是断开连接
 */
void LoginManager::loginReturnMtcard(const DWORD loginTempID,const char *name,CMD::stServerReturnLoginFailedCmd *tCmd, const bool tm)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	LoginTaskHashmap_iterator it = loginTaskSet.find(loginTempID);
	if (it != loginTaskSet.end())
	{
#if 0
		LoginTask *task = it->second;
		if (!task->checkACCNAME(name))
		{
			Fir::logger->error("%s 串号，服务器繁忙，断开连接 %s, %s", __PRETTY_FUNCTION__, name, task->getACCNAME());
			tCmd->byReturnCode = CMD::LOGIN_RETURN_TIMEOUT;
			task->LoginReturnMtcard(tCmd);
		}
		else
			task->LoginReturnMtcard(tCmd, tm);
#endif
	}
	else
		Fir::logger->debug("找不到该连接！！！");
}

/**
 * \brief 返回错误代码到指定的客户端
 * \param loginTempID 指定的客户端连接临时编号
 * \param retcode 待返回的代码
 * \param tm 返回信息以后是否断开连接，缺省是断开连接
 */
#if 0
void LoginManager::loginReturn(const DWORD loginTempID, const BYTE retcode, const bool tm)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	LoginTaskHashmap_iterator it = loginTaskSet.find(loginTempID);
	if (it != loginTaskSet.end())
	{
		LoginTask *task = it->second;
		if(NULL != task)
		{
			task->LoginReturn(retcode, tm);
		}
	}
	else
		Fir::logger->debug("找不到该连接！！！");
}
#endif

/**
 * \brief 对容器中的所有元素调用回调函数
 * \param cb 回调函数实例
 */
void LoginManager::execAll(LoginTaskCallback &cb)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(LoginTaskHashmap_iterator it = loginTaskSet.begin(); it != loginTaskSet.end(); ++it)
	{
		cb.exec(it->second);
	}
}

#if 0
bool LoginManager::CallBackLogin(const DWORD loginTempID, const HelloKittyMsgData::ReqLogin *message)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	LoginTaskHashmap_iterator it = loginTaskSet.find(loginTempID);
	if (it != loginTaskSet.end())
	{
		LoginTask *task = it->second;
		if (task)
		{
			task->requireLogin(message);
			return true;
		}
	}
	return false;
}

void LoginManager::callBackLoginFail(const DWORD loginTempID, const HelloKittyMsgData::LoginFailReason error)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	LoginTaskHashmap_iterator it = loginTaskSet.find(loginTempID);
	if (it != loginTaskSet.end())
	{
		LoginTask *task = it->second;
		if (task)
		{
			task->LoginReturnMsg("登陆错误返回",error);
		}
	}
}
#endif
