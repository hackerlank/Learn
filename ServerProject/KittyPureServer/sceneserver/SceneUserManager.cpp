/**
 * \file	SceneUser.h
 * \version  	$Id: SceneUserManager.cpp 37 2013-04-08 01:52:56Z  $
 * \author  	,
 * \date 	2013年04月07日 15时48分31秒 CST
 * \brief 	场景用户管理器定义
 *
 * 
 */

#include "SceneUserManager.h"
#include "SceneServer.h"
#include "SceneTaskManager.h"
#include "zMetaData.h"
#include "RedisMgr.h"


SceneUserManager::SceneUserManager()
{
}

SceneUserManager::~SceneUserManager()
{
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SAFE_DELETE(itr->second);
    }
    m_mapUsers.clear();
}

bool SceneUserManager::addUser(SceneUser *user)
{   
    return true;
}   

SceneUser* SceneUserManager::getUserByID(QWORD charid)
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁

    auto itr=m_mapUsers.find(charid);
    if(itr == m_mapUsers.end())
        return NULL;

    return itr->second;
}

void SceneUserManager::removeUser(QWORD charid)
{

    zRWLock_scope_rdlock lock(rwlock); // 获取读锁

    auto itr = m_mapUsers.find(charid); 
    if(itr == m_mapUsers.end())
        return;
    zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if(handle2)
        handle2->setInt("playerscene",charid,"sceneid",0);  
    //保存数据
    SceneUser *temp = itr->second;
    if(temp)
    {
        temp->save();
    }
    SAFE_DELETE(itr->second);
    m_mapUsers.erase(itr);
    Fir::logger->info("删除 %lu,%u", charid,DWORD(handle2->getInt("playerscene",charid,"sceneid")));  


}


void SceneUserManager::loop()
{
    std::vector<QWORD> vecDel;
    {
        zRWLock_scope_rdlock lock(rwlock); // 获取读锁
        for(auto itr = m_mapUsers.begin(); itr != m_mapUsers.end();itr++ )
        {
            SceneUser* user = itr->second;
            if(NULL == user) 
            {
                vecDel.push_back(itr->first);
                continue;
            }
            if(!user->loop())
            {
                vecDel.push_back(itr->first);
            }

        }
    }
    for(auto iter = vecDel.begin();iter != vecDel.end(); iter++)
    {
        zMemDB* handle2 = zMemDBPool::getMe().getMemDBHandle(*iter % MAX_MEM_DB+1);
        if( handle2 && handle2->isLock("playerlock",*iter,"newplayer"))
        {
            continue;
        }
        removeUser(*iter);
    }
}

void SceneUserManager::update()
{
    static DWORD saveGroup = 0;

    saveGroup = (saveGroup+1)%SceneService::getMe().writeBackGroup;

    zRWLock_scope_rdlock lock(rwlock); // 获取读锁

    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
        if(u->charid%SceneService::getMe().writeBackGroup == saveGroup)
            u->save();
    }	
}

void SceneUserManager::saveAll()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
        u->save();
    }
}

void SceneUserManager::execAll(UserFunction func)
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
        func(u);
    }
}
void SceneUserManager::delAll()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for (auto it = m_mapUsers.begin(); it != m_mapUsers.end(); ++it)
    {
        SAFE_DELETE(it->second);
    }
}

void SceneUserManager::oneDay()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
    }	
}

void SceneUserManager::oneHour()
{
    zRWLock_scope_rdlock lock(rwlock); // 获取读锁
    for(auto itr=m_mapUsers.begin(); itr!=m_mapUsers.end(); itr++)
    {
        SceneUser* u = itr->second;
        if(NULL == u) continue;
    }	
}
