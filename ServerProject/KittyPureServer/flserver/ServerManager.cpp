/**
 * \file
 * \version  $Id: ServerManager.cpp 855 2005-04-04 13:53:18Z song $
 * \author  Songsiliang,
 * \date 2004年12月13日 18时44分39秒 CST
 * \brief 实现服务器管理容器
 *
 * 这个容器包括全局容器和唯一性验证容器
 * 
 */


#include <iostream>

#include "ServerTask.h"
#include "zRWLock.h"
#include "zNoncopyable.h"
#include "ServerManager.h"
#include "Fir.h"
#include "GYListManager.h"
#include "SlaveCommand.h"

void ServerManager::add(ServerTask *task)
{
	zRWLock_scope_wrlock scope_wrlock(rwlock);
	m_mapper.insert(value_type(NetType_near, task));
}

void ServerManager::remove(ServerTask *task)
{
	zRWLock_scope_wrlock scope_wrlock(rwlock);
	for(iter it = m_mapper.begin(); it != m_mapper.end(); ++it)
	{
		if (task == it->second)
		{
			m_mapper.erase(it);
			break;
		}
	}
	if (m_mapper.empty())
	{
		//没有这个区的连接，把这个区设置为维护状态
		GYListManager::getMe().disableAll();
	}
}
bool ServerManager::sendCmdToZone(const void *pstrCmd, int nCmdLen)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
    NetType netType = NetType_near;
    std::pair<iter, iter> eqp = m_mapper.equal_range(netType);
    for(iter it = eqp.first; it != eqp.second; ++it)
    {
        ServerTask *task = it->second;
        if (task)
        {
            task->sendCmd(pstrCmd, nCmdLen);
        }
    }
    eqp = m_mapper.equal_range(NetType_near);
    for(iter it = eqp.first; it != eqp.second; ++it)
    {
        ServerTask *task = it->second;
        if (task)
        {
            task->sendCmd(pstrCmd, nCmdLen);
        }
    }
    return true;
}
// 获得注册人数最少的区
DWORD ServerManager::getRegRoleMinZone()
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	DWORD role_count = 0;
    for(NetServer_multimap::iterator itr = m_mapper.begin(); itr != m_mapper.end(); itr++)
    {
        ServerTask *task = itr->second;
        if(task != NULL)
        {
            if(!role_count || task->getRegRoleCount() < role_count)
            {
                role_count = task->getRegRoleCount();
            }
        }
    }
	return 0;
}

