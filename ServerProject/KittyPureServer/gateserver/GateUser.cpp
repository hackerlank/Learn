/**
 * \file
 * \version  $Id: GateUser.cpp 67 2013-04-23 09:44:20Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时56分41秒 CST
 * \brief 实现网关用户类
 */

#include <stdlib.h>
#include "GateUser.h"
#include "GateUserManager.h"
#include "RecordCommand.h"
#include "RecordClient.h"
#include "GatewayTask.h"
#include "SceneClient.h"
#include "GatewayServer.h"
#include "TimeTick.h"
#include "SceneClientManager.h"


GateUser::GateUser(const QWORD charid,GatewayTask *histask)
{
    this->charid = charid;		
    initState();
    gatewaytask=histask;
    scene=NULL;
    scene_id=0;
    m_byCreate = 0;
    if(gatewaytask)
    {
        gatewaytask->m_pUser=this;
    }
}

GateUser::~GateUser()
{
    Fir::logger->debug(__PRETTY_FUNCTION__);
}


/**
 * \brief 卸载一个网关用户的信息
 *
 *
 */
void GateUser::final()
{
    lock();

    GateUserManager::getMe().removeUserCharid(this->charid);

    unlock();

    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if (handle) 
    {
        if(strlen(gatewaytask->m_accountInfo.phoneNum))
        {
            handle->setInt("gatewaylogin", gatewaytask->m_accountInfo.phoneNum, "state", GATEWAY_USER_LOGINSESSION_STATE_NONE);
        }
        else if(gatewaytask->m_accountInfo.email)
        {
            handle->setInt("gatewaylogin", gatewaytask->m_accountInfo.email, "state",GATEWAY_USER_LOGINSESSION_STATE_NONE);
        }
    }
}


/**
 * \brief 设置游戏状态
 *
 *
 */
void GateUser::playState(SceneClient *s , DWORD scene_tempid)
{
    lock();
    if(scene_tempid)
    {
        this->scene_id=scene_tempid;
    }
    if(s)
    {
        this->scene=s;
    }
    systemstate = SYSTEM_STATE_PLAY;
    unlock();
}

/**
 * \brief 对选择到一个角色进行初始处理
 *
 *
 * \return 处理是否成功
 */
bool GateUser::beginSelect()
{
    zMutex_scope_lock lock(mlock);
    if (!this->syncMemDBBase())
    {
        Fir::logger->debug("[登陆网关]:网关选择登录失败(网关向rides获取昵称失败,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
        return false;
    }
    //进入等待游戏状态，然后开始向会话注册，会话注册到场景，成功读档后，返回场景注册成功消息，再进入游戏状态
    if(!this->reg())
    {
        Fir::logger->debug("[登陆网关]:网关选择登录失败(网关向场景注册失败,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
        return false;
    }
    
    Fir::logger->debug("[登陆网关]:网关选择登录成功(等待网关向场景注册,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
    return true;
}
/**
 * \brief 发送数据给客户端
 *
 *
 * \param pstrCMD: 发送的指令
 * \param nCmdLen: 指令长度
 * \return 发送是否成功
 */
bool GateUser::sendCmd(const void *pstrCmd, const unsigned int nCmdLen,const bool hasPacked)
{
    if (!hasPacked)
    {
        if(gatewaytask)
        {
            return gatewaytask->sendCmd(pstrCmd,nCmdLen);
        }
    }else
    {
        if(gatewaytask)
        {
            return gatewaytask->sendCmdNoPack(pstrCmd,nCmdLen);
        }
    }
    return false;
}

/**
 * \brief 网关注销一个用户
 * \param out: false by default
 *
 */
void GateUser::unreg()
{
    //防止锁加的太大
    bool need=false;

    if (isWaitUnregState())
    {
        return;
    }

    lock();

    if(isWaitPlayState() || isPlayState())
    {
        need=true;

        this->waitUnregState();
    }

    unlock();

    if(need)
    {
        CMD::SCENE::t_unregUser_gatescene send;
        send.charid=charid;
        send.retcode=CMD::SCENE::UNREGUSER_RET_LOGOUT;
        SceneClient * pScene = SceneClientManager::getMe().getSceneByID(scene_id);
        if(pScene)
        {
            std::string ret;
            encodeMessage(&send,sizeof(send),ret);
            pScene->sendCmd(ret.c_str(),ret.size());
            Fir::logger->trace("[登录注销],charid=%lu,account=%s, 向会话注销",charid,gatewaytask->m_accountInfo.account);
        }
    }
}

/**
 * \brief 网关注册一个用户
 *
 */
bool GateUser::reg()
{
    CMD::SCENE::t_regUser_Gatescene send;
    send.charid = charid;
    send.byCreate = m_byCreate;
    send.accountInfo = gatewaytask->m_accountInfo;
    //先查看玩家在哪一个scene,如果找不到，那么选个最小的
    SceneClient *pScene = NULL;
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if(handle)
    {
        DWORD sceneid = handle->getInt("playerscene",charid,"sceneid");
        if(sceneid > 0)
        {
            pScene = SceneClientManager::getMe().getSceneByID(sceneid);      
        }
        else
        {
            pScene = SceneClientManager::getMe().getMinScene();

        }
        Fir::logger->debug("[登录网关]:网关向场景注册成功(选择场景服务器,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
    }
    if(!pScene)
    {
        Fir::logger->debug("[登录网关]:网关向场景注册失败(场景服务器为空,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
        return false;
    }
    else
    {
        if(!handle->getLock("playerlock",charid,"newplayer",30))
        {
            Fir::logger->debug("[登录网关]:网关向场景注册失败(锁定注册场景角色,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
            return false;
        }
    }

    std::string ret;
    encodeMessage(&send,sizeof(send),ret);
    pScene->sendCmd(ret.c_str(),ret.size());
    waitPlayState();
    Fir::logger->debug("[登录网关]:网关向场景注册成功(网关向场景服务器注册,%lu,%s)",charid,gatewaytask->m_accountInfo.account);
    return true;
}

/**
 * \brief 中断连接
 *
 */
void GateUser::TerminateWait()
{
    if(gatewaytask)
        gatewaytask->TerminateWait();
}

/**
 * \brief 是否处于等于中断状态
 *
 */
bool GateUser::isTerminateWait()
{
    if(gatewaytask)
        return gatewaytask->isTerminateWait();

    return true;
}

void GateUser::Terminate()
{
    if (gatewaytask)
        return gatewaytask->Terminate();
}

/**
 * \brief 是否已经中断
 *
 */
bool GateUser::isTerminate()
{
    if (gatewaytask)
    {
        return gatewaytask->isTerminate();
    }
    return true;
}

bool GateUser::syncMemDBBase()
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();
    if(!handle)
    {
        unlock();
        return false;
    }
    return true;
}

bool GateUser::ackLoginGateway(const ProtoMsgData::LoginError &error,const bool flag)
{
    ProtoMsgData::AckLoginGateway ack;
    ack.set_ret(flag);
    ack.set_failreason(error);

    std::string ret;
    encodeMessage(&ack,ret);
    return sendCmd(ret.c_str(),ret.size());
}
