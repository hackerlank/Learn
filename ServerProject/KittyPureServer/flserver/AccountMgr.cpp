#include "FLCommand.h"
#include "zRWLock.h"
#include "zNoncopyable.h"
#include "AccountMgr.h"
#include "zXMLParser.h"
#include "FLCommand.h"
#include "ServerManager.h"
#include "zMemDBPool.h"
#include "RedisMgr.h"

AccountMgr::AccountMgr() : dbConnPool(NULL), metaData(NULL), invitcode_mysql_hashcode(0)
{
}

AccountMgr::~AccountMgr()
{
}

bool AccountMgr::setDBConnPool(zDBConnPool *dbConnPool)
{
	invitcode_mysql_hashcode = atoi(Fir::global["invitcode_mysql_hashcode"].c_str());
	if (NULL == dbConnPool || !dbConnPool->putURL(invitcode_mysql_hashcode, Fir::global["invitcode_mysql"].c_str(), false))
	{
		return false;
	}
	this->dbConnPool = dbConnPool;
	metaData = MetaData::newInstance("");
	if (!metaData || !metaData->init(Fir::global["invitcode_mysql"].c_str()))
	{
		return false;
	}

	if(!init())
    {
        return false;
    }

	return true;
}

bool AccountMgr::init()
{
    if (NULL == dbConnPool || NULL == metaData)
    {
        return false;
    }
	connHandleID handle = dbConnPool->getHandle((const void*)invitcode_mysql_hashcode);
	if ((connHandleID)-1 == handle)
    {
        return false;
    }
	FieldSet* fields = metaData->getFields("account_zone");
	if (NULL == fields)
	{   
		dbConnPool->putHandle(handle);
		return false;
	}   
    
	RecordSet* result = dbConnPool->exeSelect(handle, fields, NULL, NULL);
	if(result && result->size())
	{   
        zMemDB* tempHandle = zMemDBPool::getMe().getMemDBHandle();
        if(!tempHandle)
        {
            return false;
        }
        for(DWORD index = 0;index < result->size();++index)
        {
            Record* record = result->get(index);
            if(!record)
            {
                continue;
            }
            AccountInfo accountInfo;
            strncpy(accountInfo.account,(const char*)(record->get("account")),sizeof(accountInfo.account));
            strncpy(accountInfo.passwd,(const char*)(record->get("passwd")),sizeof(accountInfo.passwd));
            strncpy(accountInfo.email,(const char*)(record->get("email")),sizeof(accountInfo.email));
            strncpy(accountInfo.phoneNum,(const char*)(record->get("phonenum")),sizeof(accountInfo.phoneNum));
            bool ret = true;
            if(strlen(accountInfo.email))
            {
                ret = ret && tempHandle->setBin("accountinfo",accountInfo.email, "email",(const char*)&accountInfo,sizeof(accountInfo));
            }
            if(strlen(accountInfo.phoneNum))
            {
                ret = ret && tempHandle->setBin("accountinfo",accountInfo.phoneNum, "phonenum",(const char*)&accountInfo,sizeof(accountInfo));
            }
            if(ret)
            {
                Fir::logger->debug("[登录服务器] 加载账号信息(%s,%s,%s,%s)",accountInfo.account,accountInfo.passwd,accountInfo.email,accountInfo.phoneNum);
            }
        }
    }
    SAFE_DELETE(result);
	dbConnPool->putHandle(handle);
	return true;
}

bool AccountMgr::dbInsert(const AccountInfo &accountInfo)
{
    if (NULL == dbConnPool || NULL == metaData)
    {
        return false;
    }
    connHandleID handle = dbConnPool->getHandle((const void*)invitcode_mysql_hashcode);
    if ((connHandleID)-1 == handle)
    {
        return false;
    }
    FieldSet* fields = metaData->getFields("account_zone");
    if (NULL == fields)
    {
        dbConnPool->putHandle(handle);
        return false;
    }

    Record record;
    record.put("account", accountInfo.account,sizeof(accountInfo.account));
    record.put("email",accountInfo.email,sizeof(accountInfo.email));
    record.put("phonenum",accountInfo.phoneNum,sizeof(accountInfo.phoneNum));
    record.put("passwd", accountInfo.passwd,sizeof(accountInfo.passwd));
    unsigned int recode = dbConnPool->exeInsert(handle, fields, &record);
    dbConnPool->putHandle(handle);
    if ((unsigned int)-1==recode)
    {
        return false;
    }
    
    zMemDB* tempHandle = zMemDBPool::getMe().getMemDBHandle();
    if(!tempHandle)
    {
        return false;
    }
    bool ret = true;
    if(strlen(accountInfo.email))
    {
        ret = ret && tempHandle->setBin("accountinfo",accountInfo.email, "email",(const char*)&accountInfo,sizeof(accountInfo));
    }
    if(strlen(accountInfo.phoneNum))
    {
        ret = ret && tempHandle->setBin("accountinfo",accountInfo.phoneNum, "phonenum",(const char*)&accountInfo,sizeof(accountInfo));
    }
    return ret;
}

bool AccountMgr::dbUpdate(const AccountInfo &accountTemp)
{
	if (NULL == dbConnPool || NULL == metaData)
    {
        return false;
    }
    if(!RedisMgr::getMe().updateRedisAccount(accountTemp))
    {
        return false;
    }
    connHandleID handle = dbConnPool->getHandle((const void*)invitcode_mysql_hashcode);
    if ((connHandleID)-1 == handle)
    {
        return false;
    }

    FieldSet* fields = metaData->getFields("account_zone");
    if (NULL == fields)
    {
        dbConnPool->putHandle(handle);
        return false;
    }

    Record record,where;
    record.put("account", accountTemp.account,sizeof(accountTemp.account));
    record.put("email",accountTemp.email,sizeof(accountTemp.email));
    record.put("phonenum",accountTemp.phoneNum,sizeof(accountTemp.phoneNum));
    record.put("passwd", accountTemp.passwd,sizeof(accountTemp.passwd));
    std::ostringstream oss;
    if(strlen(accountTemp.phoneNum))
    {
        oss << "phonenum='" << accountTemp.phoneNum << "'";
        where.put("phonenum", oss.str());
    }
    else
    {
        oss << "email='" << accountTemp.email << "'";
        where.put("email", oss.str());
    }


    unsigned int retcode = dbConnPool->exeUpdate(handle,fields, &record, &where);
    dbConnPool->putHandle(handle);
    return (DWORD)-1 != retcode;
}

bool AccountMgr::findAccount(const AccountInfo &accountInfo)
{
    bool ret = false;
    AccountInfo temp;
    if(strlen(accountInfo.phoneNum))
    {
        ret = RedisMgr::getMe().getRedisAccountByPhoneNum(accountInfo.phoneNum,temp);
    }
    else if(strlen(accountInfo.email))
    {
        ret = RedisMgr::getMe().getRedisAccountByEmail(accountInfo.email,temp);
    }
    return ret;
}

DWORD AccountMgr::getZoneidByAccount()
{
    return ServerManager::getMe().getRegRoleMinZone();
}

bool AccountMgr::verifyPasswd(const AccountInfo &accountInfo)
{
    AccountInfo temp;
    if(strlen(accountInfo.phoneNum))
    {
        RedisMgr::getMe().getRedisAccountByPhoneNum(accountInfo.phoneNum,temp);
    }
    else if(strlen(accountInfo.email))
    {
        RedisMgr::getMe().getRedisAccountByEmail(accountInfo.email,temp);
    }
    return strncmp(temp.passwd,accountInfo.passwd,sizeof(accountInfo.passwd)) == 0;
}

