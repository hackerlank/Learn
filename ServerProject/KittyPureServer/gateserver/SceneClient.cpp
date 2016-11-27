/**
 * \file
 * \version  $Id: SceneClient.cpp 65 2013-04-23 09:34:49Z  $
 * \author  ,@163.com
 * \date 2004年11月05日 13时58分55秒 CST
 * \brief 定义场景服务器连接客户端
 *
 */

#include <unistd.h>
#include <iostream>

#include "zTCPClient.h"
#include "SceneCommand.h"
#include "RecordCommand.h"
#include "SceneClient.h"
#include "GatewayServer.h"
#include "GateUserManager.h"
#include "Fir.h"
#include "Command.h"
#include "GatewayTask.h"
#include "RecordClient.h"
#include <time.h>
#include "GatewayTask.h"
#include "RecordClient.h"
#include "SceneClientManager.h"
#include "extractProtoMsg.h"
#include "TimeTick.h"
#include "RedisMgr.h"

std::map<DWORD, QWORD> SceneClient::cmdCount;
std::map<DWORD, QWORD> SceneClient::forwardCount;
BYTE SceneClient::cmdCountSwitch = 0;
CmdAnalysis SceneClient::analysisScene(5, "SceneClient", 300);
CmdAnalysis SceneClient::analysisForward(6, "SceneForward", 300);


#if 0
SceneClientManager *SceneClientManager::instance = NULL;
#endif

/**
 * \brief 创建到场景服务器的连接
 *
 * \return 连接是否成功
 */
bool SceneClient::connectToSceneServer()
{
    if (!zTCPClientTask::connect())
    {
        Fir::logger->error("连接场景服务器失败");
        return false;
    }

    CMD::SUPER::t_restart_ServerEntry_NotifyOther notify; 
    notify.srcID = GatewayService::getMe().getServerID();
    notify.dstID = this->getServerID();

    std::string retNotify;
    encodeMessage(&notify,sizeof(notify),retNotify);
    GatewayService::getMe().sendCmdToSuperServer(retNotify.c_str(), retNotify.size());

    using namespace CMD::SCENE;
    t_LoginScene tCmd;
    tCmd.wdServerID = GatewayService::getMe().getServerID();
    tCmd.wdServerType = GatewayService::getMe().getServerType();

    std::string ret;
    return encodeMessage(&tCmd,sizeof(tCmd),ret) && sendCmd(ret.c_str(),ret.size());
}

#if 0
/**
 * \brief 把一个场景服务器从连接添加到容器中删除
 *
 * \param client 场景服务器连接
 */
void SceneClientManager::remove(SceneClient *client)
{
    //Fir::logger->debug(__PRETTY_FUNCTION__);
    mlock.lock();
    std::vector<SceneClient *>::iterator iter = sceneClients.begin();
    for(;iter != sceneClients.end(); iter ++)
    {
        if(*iter == client)
        {
            sceneClients.erase(iter);
            mlock.unlock();
            return;
        }
    }
    mlock.unlock();
}
/**
 * \brief 把一个场景服务器的连接添加到容器中
 *
 * \param client 场景服务器连接
 */
void SceneClientManager::add(SceneClient *client)
{
    //Fir::logger->debug(__PRETTY_FUNCTION__);
    mlock.lock();
    sceneClients.push_back(client);
    mlock.unlock();
}

/**
 * \brief 通过服务器编号获取场景服务器连接
 *
 * \param serverid 服务器编号
 * \return 场景服务器连接
 */
SceneClient *SceneClientManager::getByServerID(WORD serverid)
{
    mlock.lock();
    for(int i=0,n=sceneClients.size();i<n;i++)
    {
        if(sceneClients[i]->getServerID()==serverid)
        {
            mlock.unlock();
            return sceneClients[i];
        }
    }
    mlock.unlock();
    return NULL;
}

/**
 * \brief 关闭管理器容器，释放资源
 *
 * 将关闭所有的与场景服务器的连接
 *
 */
void SceneClientManager::final()
{
    mlock.lock();
    while(!sceneClients.empty())
    {
        Fir::logger->debug(__PRETTY_FUNCTION__);
        std::vector<SceneClient *>::reference ref = sceneClients.back();
        sceneClients.pop_back();
        if (ref)
        {
            (ref)->final();
            (ref)->join();
            SAFE_DELETE(ref);
        }
    }
    mlock.unlock();
}
#endif 
int SceneClient::checkRebound()
{
    return 1;
}
void SceneClient::addToContainer()
{
    SceneClientManager::getMe().add(this);
}

void SceneClient::removeFromContainer()
{
    SceneClientManager::getMe().remove(this);
    GateUserManager::getMe().removeUserBySceneClient(this);
}
bool SceneClient::connect()
{
    return connectToSceneServer();
}

#if 0
/**
 * \brief 线程回调函数
 *
 */
void SceneClient::run()
{
    zTCPBufferClient::run();
    while(!GatewayService::getMe().isTerminate())
    {
        SceneClientManager::getMe().remove(this);
        GateUserManager::getMe().removeUserBySceneClient(this); 
        while(!connect())
        {
            Fir::logger->error("连接场景服务器失败");
            zThread::msleep(1000);
        }
        CMD::SUPER::t_restart_ServerEntry_NotifyOther notify;
        notify.srcID=GatewayService::getMe().getServerID();
        notify.dstID=this->getServerID();
        GatewayService::getMe().sendCmdToSuperServer(&notify, sizeof(notify));
        zThread::msleep(2000);
        connect();
        SceneClientManager::getMe().add(this);
        using namespace ;
        t_LoginScene tCmd;
        tCmd.wdServerID = GatewayService::getMe().getServerID();
        tCmd.wdServerType = GatewayService::getMe().getServerType();

        if(sendCmd(&tCmd, sizeof(tCmd)))
        {
            zTCPBufferClient::run();
        }
        // */
        zThread::msleep(1000);
    }

    //与场景服务器连接断开，关闭服务器
    GatewayService::getMe().Terminate();
}
#endif

bool SceneClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("SceneClient::msgParseProto 消息没处理");
    return true;
}

bool SceneClient::msgParseSceneFresh(const CMD::SCENE::t_Refresh_LoginScene *cmd,const DWORD nCmdLen)
{
    GateUser *pUser=(GateUser *)GateUserManager::getMe().getUserCharid(cmd->charid);

    if (!pUser) 
    {
        Fir::logger->trace("[登录],charid=%lu,0,0, 会话用户注册成功，网关未找到用户", cmd->charid);
        return true;
    }

    if (!pUser->isWaitPlayState())
    {
        Fir::logger->trace("[登录],charid=%lu,0,0, 会话用户注册成功，网关用户不在等待状态", cmd->charid);
        return true;
    }

    if (!pUser->gatewaytask)
    {
        Fir::logger->trace("[登录],charid=%lu,0,0, 会话用户注册成功，网关用户不在等待状态", cmd->charid);
        return true;
    }

    if (pUser->gatewaytask->isTerminateWait() || pUser->gatewaytask->isTerminate())
    {
        Fir::logger->trace("[登录],charid=%lu,0,0, 会话用户注册成功，网关用户不在等待状态", cmd->charid);
        return true;
    }

    pUser->playState(this, this->getServerID());
    Fir::logger->trace("[登录],charid=%lu,0, 用户登录成功", pUser->charid);
    return true;
}

bool SceneClient::msgParseSceneCmd(const CMD::SCENE::SceneNull *sceneCmd,const DWORD nCmdLen)
{
    using namespace CMD::SCENE;

    switch(sceneCmd->para)
    {
        case PARA_SCENE_USER: 
            {
                t_User_FromScene* rev = (t_User_FromScene*)sceneCmd;
                GateUser* u = GateUserManager::getMe().getUserCharid(rev->charid);
                if (u && !u->isTerminateWait() && !u->isTerminate())
                {
                    u->sendCmd(rev->data, rev->size);
                }
                return true;
            }
            break;
        case PARA_REFRESH_LOGIN_SCENE:
            {
                return msgParseSceneFresh((t_Refresh_LoginScene*)sceneCmd,nCmdLen);
            }
        case PARA_START_OK_SCENE_GATE:
            {
                this->isStartOK = true;
                Fir::logger->debug("场景网关连接启动完成:%u",this->getServerID());
                return true;
            }
            break;
        default:
            break;

    }
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, sceneCmd->cmd, sceneCmd->para, nCmdLen);
    return true;
}


/**
 * \brief 解析来自场景服务器的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 待处理的指令长度
 * \return 解析是否成功
 */
bool SceneClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

    using namespace CMD::SCENE;
    if (cmdCountSwitch) 
    {
        analysisScene.add(ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    }
    bool ret = false;

    switch(ptNullCmd->cmd)
    {
        case SCENECMD:
            {
                ret = msgParseSceneCmd((SceneNull*)ptNullCmd,nCmdLen);
            }
            break;
    }
    if(ret== false)
        Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return true;
}
