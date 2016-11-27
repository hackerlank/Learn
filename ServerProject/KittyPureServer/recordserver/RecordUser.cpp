#include "Fir.h"
#include "zDBConnPool.h"
#include "RecordServer.h"
#include "RecordUser.h"
#include "RecordTask.h"
#include "zMemDB.h"
#include "serialize.pb.h"
#include "RedisMgr.h"

RecordUser::RecordUser()
{
    charid = 0;
}

RecordUser::~RecordUser()
{
}

bool RecordUser::readCharBase()
{
    using namespace CMD::RECORD;
    connHandleID handle = RecordService::dbConnPool->getHandle();
    if ((connHandleID)-1 == handle)
    {
        Fir::logger->error("[DB]不能获取数据库句柄");
        return false;
    }

    struct ReadData
    {
        ReadData()
        {
            role_size = 0;
            bzero(role, sizeof(role));
        }
        CharBase charbase;
        //角色档案数据大小
        DWORD role_size;
        //角色档案数据,二进制数据
        unsigned char role[zSocket::MAX_DATASIZE];

    }__attribute__ ((packed)) read_data;

    char where[128]={0};
    snprintf(where, sizeof(where) - 1, "f_charid=%lu", this->charid);
    unsigned int retcode = RecordService::dbConnPool->exeSelectLimit(handle, "t_charbase", record_charbase, where, "f_charid DESC", 1, (BYTE *)(&read_data));

    //释放handler
    RecordService::dbConnPool->putHandle(handle);
    if (1 != retcode)
    {
        Fir::logger->error("[角色读写]:0,charid=%lu,读取档案失败，没有找到记录",this->charid);
        return false;
    }

    this->charid = read_data.charbase.charid;
    strncpy(this->m_accountInfo.email, read_data.charbase.email,sizeof(this->m_accountInfo.email));
    strncpy(this->m_accountInfo.account, read_data.charbase.account,sizeof(this->m_accountInfo.account));
    strncpy(this->m_accountInfo.phoneNum, read_data.charbase.phoneNum,sizeof(this->m_accountInfo.phoneNum));
    zMemDB* redishandle = zMemDBPool::getMe().getMemDBHandle(read_data.charbase.charid % MAX_MEM_DB+1);
    if (redishandle==NULL)
    {
        CharBase& tmp = read_data.charbase;
        Fir::logger->error("[读取角色],获取内存数据库失败,account=%s,charid=%lu",tmp.account,tmp.charid);
        return false;
    }

    // 同步
    if (!redishandle->setBin("charbase", read_data.charbase.charid, "charbase", (const char*)&read_data.charbase, sizeof(read_data.charbase)))
    {
        CharBase& tmp = read_data.charbase;
        Fir::logger->error("[读取角色],同步内存数据库charbase失败,in readCharBase,account=%s,charid=%lu",tmp.account,tmp.charid);
        return false;
    }

    if (!redishandle->setBin("charbase", read_data.charbase.charid, "allbinary", (const char*)read_data.role, read_data.role_size))
    {
        CharBase& tmp = read_data.charbase;
        Fir::logger->error("[读取角色],同步内存数据库allbinary失败,account=%s,charid=%lu",tmp.account,tmp.charid);
        return false;
    }

    ProtoMsgData::Serialize binary;
    if(!RedisMgr::getMe().get_binary(this->charid,binary))
    {
        return false;
    }

    Fir::logger->trace("[角色读写],charid=%lu,%s, 找到合格的角色记录", read_data.charbase.charid, read_data.charbase.account);
    Fir::logger->debug("读取档案服务器数据,压缩数据大小(size = %u)" , read_data.role_size);
    return true;
}

bool RecordUser::syncBaseMemDB()
{
    zMemDB* charhandle = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
    if (charhandle == NULL) 
    {
        return false;
    }
    
    bool ret = true;
    ret = ret && charhandle->set("charbaseinfo", this->charid, "email",m_accountInfo.email);
    ret = ret && charhandle->set("charbaseinfo", this->charid, "phonenum",m_accountInfo.phoneNum);
    ret = ret && charhandle->setInt("charbaseinfo", this->charid, "dbserver", RecordService::getMe().getServerID());
    charhandle = zMemDBPool::getMe().getMemDBHandle();
    if(!charhandle)
    {
        return false;
    }
    if(strlen(m_accountInfo.phoneNum))
    {
        ret = ret && charhandle->setInt("charbaseinfo",m_accountInfo.phoneNum, "charid", charid);
    }
    if(strlen(m_accountInfo.email))
    {
        ret = ret && charhandle->setInt("charbaseinfo",m_accountInfo.email, "charid", charid);
    }

    ProtoMsgData::Serialize binary;
    if(!RedisMgr::getMe().get_binary(this->charid,binary))
    {
        return false;
    }
    return true;
}
