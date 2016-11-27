/**
 * \file
 * \version  $Id: GYListManager.cpp 2877 2005-09-12 12:16:19Z whj $
 * \author  ,
 * \date 2004年12月26日 16时42分44秒 CST
 * \brief 网关信息列表
 *
 * 登陆服务器需要保存最新的所有网关的信息列表，便于分配网关
 * 
 */


#include <map>

#include "zType.h"
#include "zMisc.h"
#include "GYListManager.h"
#include "Fir.h"
#include "LoginManager.h"

GYListManager::GYListManager()
{
}

GYListManager::~GYListManager()
{
	m_gatewayData.clear();
}
/**
 * \brief 添加网关信息
 * 如果已经存在，直接更新信息，没有需要新建立记录
 * \param gameZone 游戏区信息
 * \param gy 网关信息
 * \return 添加是否成功
 */
bool GYListManager::put(const GYList &gy)
{
	zRWLock_scope_wrlock scope_wrlock(rwlock);
    auto iter = m_gatewayData.find(gy);
    if(iter == m_gatewayData.end())
    {
        return false;
    }
    GYList &temp = const_cast<GYList&>(*iter);
    temp = gy;
    return true;
}

void GYListManager::disableAll()
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	for(std::set<GYList>::iterator it = m_gatewayData.begin(); it != m_gatewayData.end(); ++it)
	{
        GYList &temp = const_cast<GYList&>(*it);
		temp.wdPort = 0;
		temp.wdNumOnline = 0;
		if(temp.state != state_normal_maintain) 
		{
			temp.state = state_maintain;
		}
	}
}

GYList *GYListManager::getAvl(WORD wdNetType)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
	GYList *ret = NULL, *temp = NULL;
    for(std::set<GYList>::iterator iter = m_gatewayData.begin();iter != m_gatewayData.end();++iter)
    {
        temp = const_cast<GYList*>(&(*iter));
        if (state_none == temp->state && wdNetType == temp->wdNetType && (NULL == ret	|| ret->wdNumOnline >= temp->wdNumOnline))
		{
			ret = temp;
		}
	}
	if (ret != NULL && ret->wdNumOnline >= (LoginManager::maxGatewayUser - 10))		
	{
		Fir::logger->error("网关类型(%d) 用户数满,当前数量%d, 将分配到其他类型网关" ,wdNetType, ret->wdNumOnline);
		ret = NULL;
	}
    //没找到相同网络类型的网关，则分配其它网关
	if(NULL == ret)	
	{
		for(std::set<GYList>::iterator it = m_gatewayData.begin(); it != m_gatewayData.end(); ++it)
		{
            temp = const_cast<GYList*>(&(*it));
			if (state_none == temp->state && (NULL == ret || ret->wdNumOnline >= temp->wdNumOnline))
			{
				ret = temp;
			}
		}
	}
    if (ret != NULL && ret->wdNumOnline >= (LoginManager::maxGatewayUser - 10))		
	{
		Fir::logger->error("网关类型(%d) 用户数满,当前数量%d, 无网关可进行分配" ,wdNetType, ret->wdNumOnline);
		ret = NULL;
	}
	if(NULL == ret)
    {
		Fir::logger->debug("客户请求登陆网关网络类型（%d）",wdNetType);
    }
	else
    {
		Fir::logger->debug("客户请求登陆网关网络类型（%d）,服务器网关网络类型（%d）", wdNetType,ret->wdNetType);
    }
	return ret;
}

void GYListManager::getAll(std::vector<GYList> &vec)
{
	zRWLock_scope_rdlock scope_rdlock(rwlock);
    for(auto iter = m_gatewayData.begin();iter != m_gatewayData.end();++iter)
    {
        vec.push_back(*iter);
    }
}

