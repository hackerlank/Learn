/**
 * \file
 * \version  $Id: GateUserManager.cpp 67 2013-04-23 09:44:20Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时56分57秒 CST
 * \brief 实现网关用户管理类
 */

#include "GateUserManager.h"
#include "GatewayServer.h"
#include "SceneClient.h"
#include "GatewayTask.h"
#include "login.pb.h"
#include "TimeTick.h"
#include "userinfo.pb.h"

GateUserManager::GateUserManager()
{
}

GateUserManager::~GateUserManager()
{
}

struct UnloadAllExec
{
    void operator()(GateUser *u)
    {
        if(NULL == u) 
        {
            return;
        }
        //Fir::logger->trace("用户%dds(%ld)因卸载场景注销",pUser->nickname,pUser->id);
        u->TerminateWait();
    }
};

void GateUserManager::removeAllUser()
{
    UnloadAllExec exec;
    execAll(exec);
}

struct UnloadSceneExec
{
    SceneClient *scene;

    UnloadSceneExec(SceneClient *s):scene(s)
    {}

    void operator()(GateUser *u)
    {
        if(NULL == u) 
        {
            return;
        }

        if(u->scene == scene)
        {
            Fir::logger->trace("用户(charid=%lu)因卸载场景注销",u->charid);
            u->TerminateWait();
        }
    }
};

void GateUserManager::removeUserBySceneClient(SceneClient *scene)
{
    UnloadSceneExec exec(scene);
    execAll(exec);
}

GateUser * GateUserManager::getUserCharid(const QWORD charid)
{
    GateUser *ret = NULL;
    charid_lock.rdlock();
    auto itrFind = m_mapUsers.find(charid);
    if(itrFind != m_mapUsers.end())
    {
        ret = itrFind->second;
    }
    charid_lock.unlock();
    return ret;
}

DWORD GateUserManager::getRoleCount()
{
    DWORD count = 0;
    charid_lock.rdlock();
    count = m_mapUsers.size();
    charid_lock.unlock();
    return count;
}

bool GateUserManager::addUserCharid(GateUser *user)
{
    bool ret = false;
    charid_lock.wrlock();
    ret = m_mapUsers.insert(std::make_pair(user->charid,user)).second;
    charid_lock.unlock();
    return ret;
}


void GateUserManager::removeUserCharid(const QWORD charid)
{
    charid_lock.wrlock();
    m_mapUsers.erase(charid);
    charid_lock.unlock();
}

bool GateUserManager::syncGameTime()
{
    charid_lock.rdlock();
    ProtoMsgData::AckSystemTime message;
    message.set_time(GatewayTimeTick::currentTime.sec());
    std::string ret;
    encodeMessage(&message,ret);
    for(auto iter = m_mapUsers.begin();iter != m_mapUsers.end();++iter)
    {
        iter->second->sendCmd(ret.c_str(),ret.size());
    }
    charid_lock.unlock();

    return true;
}                                       

void GateUserManager::sendCmd(const void *pstrCmd, const DWORD nCmdLen)
{
    charid_lock.rdlock();
    for(auto itr = m_mapUsers.begin();itr != m_mapUsers.end();++itr)
    {
        itr->second->sendCmd(pstrCmd,nCmdLen);
    }
    charid_lock.unlock();
}

bool GateUserManager::addUserAccount(GateUser *user)
{
    bool ret = false;
    charid_lock.wrlock();
    ret = m_accountUserMap.insert(std::make_pair(user->gatewaytask->m_accountInfo,user)).second;
    charid_lock.unlock();
    return ret;
}

GateUser * GateUserManager::getUserByAccount(const AccountInfo &accountInfo)
{
    GateUser *ret = NULL;
    charid_lock.rdlock();
    auto itrFind = m_accountUserMap.find(accountInfo);
    if(itrFind != m_accountUserMap.end())
    {
        ret = itrFind->second;
    }
    charid_lock.unlock();
    return ret;
}


