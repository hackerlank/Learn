#ifndef _ACCOUNT_MGR_H_
#define _ACCOUNT_MGR_H_

#include <string>
#include <map>
#include <vector>
#include <set>
#include <unordered_map>

#include "zType.h"
#include "zMisc.h"
#include "Fir.h"
#include "zRWLock.h"
#include "zDBConnPool.h"
#include "zMetaData.h"

class AccountMgr : public Singleton<AccountMgr>
{
	private:
		friend class Singleton<AccountMgr>;
		AccountMgr();
		~AccountMgr();
	public:
		bool setDBConnPool(zDBConnPool *dbConnPool);
		bool init();
        //验证密码
        bool verifyPasswd(const AccountInfo &accountInfo);
        //获得区号ID
        DWORD getZoneidByAccount();
        //判断账号是否存在
        bool findAccount(const AccountInfo &accountInfo);
        //插入数据库
        bool dbInsert(const AccountInfo &accountInfo);
	private:
        //更新账号信息
        bool dbUpdate(const AccountInfo &accountTemp);
	private:
        //数据库连接池 
		zDBConnPool *dbConnPool;       
        //封装好的数据库操作对象
		MetaData* metaData;             
		unsigned int invitcode_mysql_hashcode;
		zRWLock rwlock;
};

#endif

