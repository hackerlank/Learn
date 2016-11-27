/**
 * \file
 * \version  $Id: SceneClientToOtherManager.cpp 42 2013-04-10 07:33:59Z  $
 * \author  王海军, wanghaijun@ztgame.com 
 * \date 2006年01月04日 16时56分05秒 CST
 * \brief 场景到场景数据缓冲发送
 *
 * 
 */

#include "zTCPClientTask.h"
#include "zTCPClientTaskPool.h"
#include "SceneClientToOther.h"
#include "SceneToOtherManager.h"
#include "zXMLParser.h"
#include "SceneServer.h"
#include "SceneTaskManager.h"
#include "SceneUserManager.h"
#include "TimeTick.h"
/**
 ** \brief 类的唯一实例指针
 **/
SceneClientToOtherManager *SceneClientToOtherManager::instance = NULL;

/**
 ** \brief 构造函数
 **/
SceneClientToOtherManager::SceneClientToOtherManager()
{
    SceneClientToOtherPool = NULL;
}

/**
 ** \brief 析构函数
 **/
SceneClientToOtherManager::~SceneClientToOtherManager()
{
    SAFE_DELETE(SceneClientToOtherPool);
}

void SceneClientToOtherManager::final()
{
    allClients.clear();
    SAFE_DELETE(SceneClientToOtherPool);

}

/**
 ** \brief 初始化管理器
 ** \return 初始化是否成功
 **/
bool SceneClientToOtherManager::init()
{
    const CMD::SUPER::ServerEntry *serverEntry = SceneService::getMe().getServerEntryByType(SCENESSERVER);
    SceneClientToOtherPool = new zTCPClientTaskPool(10,8000);
    if (NULL == SceneClientToOtherPool
            || !SceneClientToOtherPool->init())
        return false;

    while(serverEntry)
    {
        SceneClientToOther *pclient = new SceneClientToOther("Scene服务器", serverEntry);
        if (NULL == pclient)
        {
            Fir::logger->error("没有足够内存，不能建立Scene服务器客户端实例");
            return false;
        }
        if(SceneClientToOtherPool->put(pclient))
        {
            if(!pclient->connect())
            {
                Fir::logger->error("can not connect");
                return false;
            }
            SceneClientToOtherPool->addCheckwait(pclient);

        }
        serverEntry = SceneService::getMe().getNextServerEntryByType(SCENESSERVER, &serverEntry);
    }
    return true;
}

/**
 ** \brief 周期间隔进行连接的断线重连工作
 ** \param ct 当前时间
 **/
void SceneClientToOtherManager::timeAction(const zTime &ct)
{
    if (actionTimer.elapse(ct) > 4)
    {
        if (SceneClientToOtherPool)
            SceneClientToOtherPool->timeAction(ct);
        actionTimer = ct;
    }
}

/**
 ** \brief 向容器中添加已经成功的连接
 ** \param SceneClientToOther 待添加的连接
 **/
void SceneClientToOtherManager::add(SceneClientToOther *SceneClientToOther)
{
    if (SceneClientToOther)
    {
        zRWLock_scope_wrlock scope_wrlock(rwlock);
        allClients.insert(value_type(SceneClientToOther->getServerID(), SceneClientToOther));
    }
}

/**
 ** \brief 从容器中移除断开的连接
 ** \param SceneClientToOther 待移除的连接
 **/
void SceneClientToOtherManager::remove(SceneClientToOther *SceneClientToOther)
{
    if (SceneClientToOther)
    {
        zRWLock_scope_wrlock scope_wrlock(rwlock);
        iter it = allClients.find(SceneClientToOther->getServerID());
        if (it != allClients.end())
        {
            allClients.erase(it);
        }
    }
}

void SceneClientToOtherManager::removebyId(const DWORD tempid)
{
    zRWLock_scope_wrlock scope_wrlock(rwlock);
    iter it = allClients.find(tempid);
    if (it != allClients.end())
    {
        SAFE_DELETE(it->second);
        allClients.erase(it);
    }


}

/**
 ** \brief 向成功的所有连接广播指令
 ** \param pstrCmd 待广播的指令
 ** \param nCmdLen 待广播指令的长度
 **/
bool SceneClientToOtherManager::broadcastOne(const void *pstrCmd, int nCmdLen)
{
    return false;
}

bool SceneClientToOtherManager::sendTo(const DWORD tempid, const void *pstrCmd, int nCmdLen)
{
    zRWLock_scope_rdlock scope_rdlock(rwlock);
    iter it = allClients.find(tempid);
    if (it == allClients.end())
        return false;
    else
        return it->second->sendCmd(pstrCmd, nCmdLen);
}

/**
 ** \brief  重新连接场景服务器
 ** \return 是否初始化成功
 **/
bool SceneClientToOtherManager::reConnectScene(const CMD::SUPER::ServerEntry *serverEntry)
{
    if (NULL == SceneClientToOtherPool)
    {
        return false;
    }

    if (serverEntry)
    {
        SceneClientToOther *pclient = FIR_NEW SceneClientToOther("Scene服务器", serverEntry);
        if (NULL == pclient)
        {
            Fir::logger->error("没有足够内存，不能建立Scene服务器客户端实例");
            return false;
        }
        if(SceneClientToOtherPool->put(pclient))
        {
            if(!pclient->connect())
            {
                Fir::logger->error("can not connect");
                return false;
            }
            SceneClientToOtherPool->addCheckwait(pclient);

        }
#ifdef _PQQ_DEBUG
        Fir::logger->debug("[重连场景] 场景重新连接场景 ip=%s,name=%s,port=%d"
                ,serverEntry->pstrIP,serverEntry->pstrName,serverEntry->wdPort);
#endif
    }
    return true;
}

/**
 * \brief 设置到场景的某一连接是否需要重连
 * \param ip 要连接的ip
 * \param port 端口
 * \param reconn 是否重连 true重连，false 不再重连，将会删掉
 */
void SceneClientToOtherManager::setTaskReconnect(const std::string& ip, unsigned short port, bool reconn)
{
    if (SceneClientToOtherPool)
    {
        SceneClientToOtherPool->setTaskReconnect(ip, port, reconn);
    }
}

SceneClientToOther* SceneClientToOtherManager::getSceneByID(DWORD id)
{
    SceneClientToOther_map::iterator iter = allClients.find(id);
    if (iter!=allClients.end())
        return (SceneClientToOther*)iter->second;

    return NULL;

}

bool SceneClientToOtherManager::isAllStartOK()
{
    zRWLock_scope_rdlock scope_rdlock(rwlock);
    if (allClients.empty())
        return false;
    for (auto it = allClients.begin(); it != allClients.end(); ++it)
    {
        if (it->second && !it->second->getStartOK())
            return false;
    }
    return true;
}


bool SceneClientToOtherManager::SendMsgToOtherScene(const DWORD ServerId,const void *pstrCmd, int nCmdLen)
{
    SceneClientToOther* pOther = getSceneByID(ServerId);
    if(pOther)
    {
        return pOther->sendCmd(pstrCmd,nCmdLen);
    }
    SceneTask * pTask = SceneTaskManager::getMe().getTaskByID(ServerId);
    if(pTask)
    {
        return pTask->sendCmd(pstrCmd,nCmdLen);
    }
    return false;

}

bool SceneClientToOtherManager::SendMsgToOtherSceneCharID(const QWORD charid,const _null_cmd_ *message,const DWORD len)
{
    std::string ret;
    encodeMessage(message,len,ret);
    return SceneClientToOtherManager::getMe().SendMsgToOtherSceneCharID(charid,ret.c_str(),ret.size());
}

bool SceneClientToOtherManager::SendMsgToOtherSceneCharID(const QWORD charid,const google::protobuf::Message *message)
{
    std::string ret;
    encodeMessage(message,ret);
    return SceneClientToOtherManager::getMe().SendMsgToOtherSceneCharID(charid,ret.c_str(),ret.size());
}

bool SceneClientToOtherManager::SendMsgToOtherSceneCharID(const QWORD charid,const void *data,const DWORD len)
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if(!handle)
    {
        Fir::logger->error("%s(%lu)", __PRETTY_FUNCTION__,charid);
        return false;
    }
    SceneUser* sceneUser = SceneUserManager::getMe().getUserByID(charid); 
    if(sceneUser)
    {
        return false;
    }
    DWORD senceId = handle->getInt("playerscene",charid,"sceneid");
    if(!senceId)
    {
        Fir::logger->error("%s(%lu,%u)", __PRETTY_FUNCTION__,charid,senceId);
        return false;
    }
    return SceneClientToOtherManager::getMe().SendMsgToOtherScene(senceId,data,len);
}

bool SceneClientToOtherManager::msgParseOtherSceneCmd(const DWORD ServerId,const CMD::SCENE::SceneNull *sceneCmd,const DWORD nCmdLen)
{
    using namespace CMD::SCENE;

    switch(sceneCmd->para)
    {
        default:
            {
                break;
            }
    }
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, sceneCmd->cmd, sceneCmd->para, nCmdLen);
    return false;


}

void SceneClientToOtherManager::execEvery()
{
    zRWLock_scope_wrlock scope_wrlock(rwlock);
    for (auto it = allClients.begin(); it != allClients.end(); ++it)
    {
        if(it->second)
            it->second->doCmd();
    }


}
