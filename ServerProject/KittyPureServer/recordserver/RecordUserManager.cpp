/**
 * \file: RecordUserManager.cpp
 * \version  $Id: RecordUserManager.cpp 64 2013-04-23 02:05:08Z  $
 * \author  , @ztgame.com 
 * \date 2007年01月30日 08时15分25秒 CST
 * \brief 档案用户管理器实现
 *
 * 
 */

#include "RecordServer.h"
#include "RecordUserManager.h"
#include "RecordUser.h"
#include "hiredis.h"
#include "zDBConnPool.h"
#include "zMetaData.h"
#include "LoginUserCommand.h"
#include "RecordCommand.h"
#include "RecordTaskManager.h"
#define IDBASE (QWORD(RecordService::getMe().getServerID()) << 32)
const DWORD SAVENUMBYTIMER = 500;

bool RecordUserM::init()
{
    std::set<QWORD> setPlayerId;
    if(RecordService::getMe().hasDBtable("t_charbase"))
    {
        FieldSet* charbase = RecordService::metaData->getFields("t_charbase");
        if(NULL == charbase)
        {
            Fir::logger->error("找不到t_charbase的FieldSet");
            return false;
        }

        connHandleID handle = RecordService::dbConnPool->getHandle();
        if ((connHandleID)-1 == handle)
        {
            Fir::logger->error("不能获取数据库句柄");
            return false;
        }

        RecordSet* recordset = NULL;
        Record col,where;

        col.put("f_charid");
        char buf[255];
        sprintf(buf," f_charid & %lu = %lu",IDBASE,IDBASE);
        where.put("f_charid",buf);

        //得到所有角色id
        recordset = RecordService::dbConnPool->exeSelect(handle, charbase, &col, &where);

        RecordService::dbConnPool->putHandle(handle);
        if(recordset != NULL) 
        {
            for(unsigned int i = 0; i < recordset->size(); i++)
            {   
                Record *rec = recordset->get(i);
                QWORD charid = 0;
                charid = rec->get("f_charid");
                setPlayerId.insert(charid);
            }
        }
        SAFE_DELETE(recordset);    
        for(int i =0 ;i < Max_CHAR_ONCE ;i++)
        {
            datacol[i] = new SaveData();
        }
    }
    // 加载最大的角色id
    if(!loadMaxCharId())
    {
        return false;
    }

    if(!setPlayerId.empty())
    {
        for(auto it = setPlayerId.begin();it != setPlayerId.end();it++)
        {
            RecordUser* u = new RecordUser();
            u->charid = *it;
            if (!u->readCharBase())
            {   
                Fir::logger->error("[角色读写],charid=%lu,初始化档案失败",u->charid);
                SAFE_DELETE(u);
                continue;
            }

            if (RecordUserM::getMe().add(u,false))
            {
                //同步角色基础信息到内存缓存数据库
                u->syncBaseMemDB();
            }
            else
            {
                SAFE_DELETE(u);
                Fir::logger->error("[角色读写],charid=%lu 添加档案失败，角色已存在", u->charid);
            }
            Fir::logger->error("[预加载测试],charid=%lu,初始化档案成功",u->charid);

        }
        synPersonNum();
        Fir::logger->trace("初始化成功，一共读取档案: %u 个角色", DWORD(setPlayerId.size()));

    }
    return true;
}

bool RecordUserM::loadMaxCharId()
{
    if(!RecordService::getMe().hasDBtable("t_charbase"))
    {
        return false;
    }

    connHandleID handle = RecordService::dbConnPool->getHandle();

    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("不能获取数据库句柄");
        return false;
    }

    const dbCol dbCol[] = 
    {
        { "f_maxcharid",   zDBConnPool::DB_QWORD,  sizeof(QWORD) },
        { NULL, 0, 0}
    };

    struct stReadData
    {   
        stReadData()
        {
            maxcharid = 0;
        }   
        QWORD maxcharid;
    }__attribute__ ((packed)) read_data;
    char buf[255];
    sprintf(buf,"select IFNULL(MAX(f_charid),0) as f_maxcharid from t_charbase where f_charid & %lu = %lu ;",IDBASE,IDBASE);

    std::string sql(buf); 
    unsigned int retcode = RecordService::dbConnPool->execSelectSql(handle, sql.c_str(), sql.length(), dbCol, 1, (BYTE *)(&read_data));

    RecordService::dbConnPool->putHandle(handle);
    if (1 == retcode)
    {  
        maxCharId = read_data.maxcharid;
        QWORD qwBase = IDBASE;
        if(maxCharId < qwBase)
        {
            maxCharId = qwBase;
        }
        Fir::logger->info("[加载最大角色id]:读取档案成功，maxcharid=%lu",maxCharId);
        return true;
    }   
    else
    {   
        Fir::logger->error("[加载最大角色id]:读取档案失败，没有找到记录");
        return false;
    }   
}

bool RecordUserM::add(RecordUser* u,bool bNew )
{
    if(!RecordService::getMe().hasDBtable("t_charbase"))
    {
        Fir::logger->info("ServerCanNot get table t_charbase");
        return false;
    }

    if (!u) 
    {
        return false;
    }

    bool retval = false;
    mlock.lock();
    RecordUserHashmap_iterator it = userMap.find(u->charid);
    if (it == userMap.end())
    {
        userMap[u->charid] = u;
        retval = true;
    }

    mlock.unlock();
    if(bNew)
    {
        synPersonNum();
    }
    return retval;
}

RecordUserM::~RecordUserM()
{	
    for(auto itr=userMap.begin(); itr!=userMap.end(); itr++)
    {
        SAFE_DELETE(itr->second);
    }
    for(int i =0 ; i < Max_CHAR_ONCE ;i++)
    {
        SAFE_DELETE(datacol[i]);
    }
    userMap.clear();
}


//仅用于UUID登录时用，并且取出后，需验证UUID
RecordUser* RecordUserM::getUserByCharid(const QWORD charid)
{
    RecordUser* ret = NULL;
    mlock.lock();
    RecordUserHashmap_iterator it = userMap.find(charid);
    if (it!=userMap.end())
    {
        ret = it->second;
    }
    mlock.unlock();
    return ret;
}

void RecordUserM::saveplayer(bool forbit)
{
    if(!RecordService::getMe().hasDBtable("t_charbase"))
    {
        return ;
    }

    zMemDB* redishandle = zMemDBPool::getMe().getMemDBHandle();
    if(redishandle == NULL)
    {
        return ;
    }
    std::set<QWORD> setPlayerId;
    if(!forbit)
    {
        redishandle->getSet("charbase",RecordService::getMe().getServerID(),"update",setPlayerId,SAVENUMBYTIMER);

    }
    else
    {
        redishandle->getSet("charbase",RecordService::getMe().getServerID(),"update",setPlayerId);
    }
    if(setPlayerId.empty())
    {
        return ;
    }
    zRTime stepOnce;
    DWORD nowSize = 0 ;
    DWORD nowcount= 0 ;
    DWORD count = 0;
    std::vector<QWORD> vecdispath;
    for(auto it = setPlayerId.begin();it != setPlayerId.end();it++)
    {
        QWORD playerID = *it;
        zMemDB* playerredishandle = zMemDBPool::getMe().getMemDBHandle(playerID%MAX_MEM_DB+1);
        if(playerredishandle == NULL)
        {
            continue;
        }
        redishandle->delSet("charbase",RecordService::getMe().getServerID(),"update",playerID);
        SaveData &save_data = *(datacol[count]);

        if (!playerredishandle->getBin("charbase", playerID, "charbase", (char*)&save_data.charbase))
        {
            Fir::logger->error("数据存档失败 %lu",playerID);
            continue ;
        }
        save_data.role_size = playerredishandle->getBin("charbase", playerID, "allbinary", (char*)(&save_data.role));
        nowSize  += 300 + save_data.role_size;
        if(nowSize <= RecordService::getMe().getMaxsqlLen())
        {
            nowcount++;
        }
        else
        {
            vecdispath.push_back(nowcount);
            nowSize = 300 + save_data.role_size;
            nowcount = 1;
        }
        count++;
        //超出预留存储空间，那么提前写入，以空出空间
        if(count == Max_CHAR_ONCE)
        {
            if(nowcount > 0)
            {
                vecdispath.push_back(nowcount);
            }
            DWORD offset = 0;
            for(size_t i = 0; i != vecdispath.size();i++)
            {
                zRTime step1;
                do
                {
                    connHandleID DBhandle = RecordService::dbConnPool->getHandle();
                    if ((connHandleID)-1 == DBhandle)
                    {
                        Fir::logger->error("不能获取数据库句柄");
                        break;
                    }
                    unsigned int retcode = RecordService::dbConnPool->exeUpdateMore(DBhandle, "t_charbase", record_charbase, (const unsigned char **)(datacol+offset), vecdispath[i]);
                    Fir::logger->trace("[角色读写],批量保存档案成功 retcode=%u", retcode/2);
                    RecordService::dbConnPool->putHandle(DBhandle);
                    offset += vecdispath[i];
                }while(0);
                zRTime step2;
                Fir::logger->info("save %u players,usetime %lu msecs",DWORD(vecdispath[i]),QWORD(step2.msecs() - step1.msecs()));
            }
            vecdispath.clear();
            //重新计数
            count = 0;
            //重新计数
            nowcount = 0;
            //重新计数
            nowSize = 0;
        }
    }
    if(nowcount > 0)
    {
        vecdispath.push_back(nowcount);
    }
    DWORD offset = 0;
    for(size_t i = 0; i != vecdispath.size();i++)
    {
        zRTime step1;
        do
        {
            connHandleID DBhandle = RecordService::dbConnPool->getHandle();
            if ((connHandleID)-1 == DBhandle)
            {
                Fir::logger->error("不能获取数据库句柄");
                break;
            }
            unsigned int retcode = RecordService::dbConnPool->exeUpdateMore(DBhandle, "t_charbase", record_charbase, (const unsigned char **)(datacol+offset), vecdispath[i]);
            Fir::logger->trace("[角色读写],批量保存档案成功 retcode=%u", retcode/2);
            RecordService::dbConnPool->putHandle(DBhandle);
            offset += vecdispath[i];
        }while(0);
        zRTime step2;
        Fir::logger->info("save %u players,usetime %lu msecs",DWORD(vecdispath[i]),QWORD(step2.msecs() - step1.msecs()));

    }

    zRTime stepOnce1;
    Fir::logger->info("saveonce %u players,usetime %lu msecs",DWORD(setPlayerId.size()),QWORD(stepOnce1.msecs() - stepOnce.msecs()));

}

void RecordUserM::synPersonNum()
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(RecordService::getMe().getServerID() % MAX_MEM_DB+1);
    if (handle!=NULL) 
    {
        handle->setInt("recorder" , QWORD(RecordService::getMe().getServerID()), "personnum", QWORD(userMap.size()));
    };
}


