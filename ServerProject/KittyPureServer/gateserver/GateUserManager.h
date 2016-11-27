/**
 * \file
 * \version  $Id: GateUserManager.h 53 2013-04-17 05:03:41Z  $
 * \author  ,
 * \date 2013年04月11日 09时55分24秒 CST
 * \brief 定义网关用户管理类
 */

#ifndef _GATEUSERMANAGER_H_
#define _GATEUSERMANAGER_H_
#include "GateUser.h"
#include "zUniqueID.h"
#include <unordered_map>
#include <functional>

class GateUserManager : public Singleton<GateUserManager>
{
	friend class Singleton<GateUserManager>;
	private:
		zRWLock charid_lock;
		GateUserManager();
		~GateUserManager();
	public:
		void removeUserBySceneClient(SceneClient *scene);
		void removeAllUser();

		// charid map
		GateUser * getUserCharid(const QWORD charid);
		bool addUserCharid(GateUser *user);
		void removeUserCharid(const QWORD charid);

		DWORD getRoleCount();

		typedef std::function<void (GateUser*)> UserFunction;
		void execAll(UserFunction func)
		{
			charid_lock.rdlock();
			for(auto itr=m_mapUsers.begin();itr!=m_mapUsers.end();++itr)
			{
				func(itr->second);
			}
			charid_lock.unlock();
		}
        void sendCmd(const void *pstrCmd, const DWORD nCmdLen);
        //给客户端同步时间
        bool syncGameTime();
        //增加accountInfo
        bool addUserAccount(GateUser *user);
        //获得gateuser
        GateUser* getUserByAccount(const AccountInfo &accountInfo);
	private:
        // 所有gateuser
		std::map<QWORD, GateUser*> m_mapUsers; 
        std::map<AccountInfo,GateUser*> m_accountUserMap;
		zRWLock arwlock;
		zRWLock urwlock;
};
#endif
