//此文件为user的序列化和反序列化函数

#include "SceneUser.h"
#include "zMetaData.h"
#include <stdarg.h>
#include "SceneServer.h"
#include "zMetaData.h"
#include "TimeTick.h"
#include "SceneUserManager.h"
#include <zlib.h>
#include <bitset>
#include "RecordClient.h"
#include "LoginUserCommand.h"
#include "firMD5.h"
#include "xmlconfig.h"
#include <limits>
#include "RedisMgr.h"
#include "json/json.h"
#include "login.pb.h"
#include "extractProtoMsg.h"
#include "serialize.pb.h"
#include "dataManager.h"
#include "tbx.h"

/**
 * \brief 压缩存档数据 , 没有检测数据超过最大值
 * \pUser 存档数据所属用户
 * \zlib 压缩输出buf
 * \return 压缩后数据大小 , 0 表示压缩出错
 */
int checkSaveData(SceneUser *pUser , unsigned char *zlib,bool &canSave)
{
    if (!pUser)
    {
        Fir::logger->error("[压缩档案数据失败] 人物指针为空，存档失败");
        return 0;
    }

    unsigned char unBuf[MAX_UZLIB_CHAR];
    bzero(unBuf, sizeof(unBuf));

    // 得到二进制存档
    int uzSize = 0;
    uzSize = pUser->saveBinaryArchive(unBuf, MAX_UZLIB_CHAR);

    uLongf zsize = zSocket::MAX_DATASIZE ;

    //数据过大，内存越界
    if (uzSize >= MAX_UZLIB_CHAR)
    {
        Fir::logger->error("[压缩档案数据]charid=%lu,超过最大数值MAX_UZLIB_CHAR=%u, uzsize=%d, zsize=%u", pUser->charid,MAX_UZLIB_CHAR,uzSize ,(DWORD)zsize);
        return 0;
    }

    if (SceneService::getMe().md5Verify)
    {
        unsigned char md5[16];
        bzero(md5,16);
        MD5SPACE::MD5Data((unsigned char *)unBuf,uzSize,md5);
        if (strncmp((const char*)md5,pUser->lastSaveMD5,16) != 0)
        {
            canSave = true;
        }
        bcopy(md5,pUser->lastSaveMD5,16);
    }

    // 压缩数据
    int retcode = 0;
    retcode = compress((unsigned char *)zlib , &zsize , (unsigned char *)unBuf , (uLongf)uzSize);
    switch(retcode)
    {
        case Z_OK:
            {
                Fir::logger->debug("压缩档案数据成功(charid=%lu) , uzsize = %d , size = %u)", pUser->charid,uzSize , (DWORD)zsize);
                break;
            }
        case Z_MEM_ERROR:
        case Z_BUF_ERROR:
            {
                Fir::logger->debug("压缩档案数据失败(charid=%lu)",pUser->charid);
                zsize = 0;
                break;
            }
        default:
            {
                Fir::logger->debug("压缩档案数据失败,未知原因(charid=%lu)",pUser->charid);
                zsize = 0;
                break;
            }
    }
    return zsize;
}

/**
 * \brief 加载二进制数据
 *
 */
void SceneUser::setupBinaryArchive(ProtoMsgData::Serialize& binary)
{
    ProtoMsgData::CharBin *dataCharBin = binary.mutable_charbin();
    *(&charbin) = *dataCharBin;
    m_package.load(binary);
}

/**
 * \brief 保存二进制数据
 *
 */
DWORD SceneUser::saveBinaryArchive(unsigned char *out , const int maxsize)
{
    // 二进制数据
    ProtoMsgData::Serialize binary; 
    ProtoMsgData::CharBin *dataCharBin = binary.mutable_charbin();
    *dataCharBin = charbin;
    m_package.save(binary);
    binary.SerializeToArray(out,maxsize);
    return binary.ByteSize();
}

std::string SceneUser::getBinaryArchive()
{
    unsigned char unBuf[MAX_UZLIB_CHAR];
    bzero(unBuf, sizeof(unBuf));

    // 得到二进制存档
    int uzSize = 0; 
    uzSize = saveBinaryArchive(unBuf, MAX_UZLIB_CHAR);

    std::string result((const char*)unBuf,uzSize);
    return result;
}


/**
 * \brief  保存角色数据到record服务器
 * \return 保存成功，返回TRUE,否则返回FALSE
 *
 */
bool SceneUser::save()
{
    bool ret = false;
    do
    {
        bool canSave = true;
        if (SceneService::getMe().md5Verify)
        {
            unsigned char md5[16];
            bzero(md5,sizeof(md5));
            MD5SPACE::MD5Data((unsigned char *)(&charbase),sizeof(CharBase),md5);
            if (strncmp((const char*)md5,lastSaveCharBaseMD5,16) == 0)
            {
                canSave = false;
            }
            bcopy(md5,lastSaveCharBaseMD5,16);
        }
        unsigned char data[MAX_UZLIB_CHAR];
        bzero(data, sizeof(data));
        DWORD dataSize = checkSaveData(this,data,canSave);
        if (!canSave)
        {
            ret = true;
            break;
        }
        zMemDB* redishandle = zMemDBPool::getMe().getMemDBHandle(charid % MAX_MEM_DB+1);
        if (redishandle==NULL)
        {
            Fir::logger->error("[读取角色],获取内存数据库失败,account=%s,charid=%lu",charbase.account,charbase.charid);
            ret = false;
            break;
        }

        // 同步
        if (!redishandle->setBin("charbase", charbase.charid, "charbase", (const char*)&charbase, sizeof(charbase)))
        {
            Fir::logger->error("[读取角色],同步内存数据库charbase失败，in refreshSaveBase,account=%s,charid=%lu",charbase.account,charbase.charid);
            ret = false;
            break;
        }

        if (!redishandle->setBin("charbase", charbase.charid, "allbinary", (const char*)data, dataSize))
        {
            Fir::logger->error("[读取角色],同步内存数据库allbinary失败,account=%s,charid=%lu",charbase.account,charbase.charid);
            ret = false;
            break;
        }
        zMemDB* redishandleAll = zMemDBPool::getMe().getMemDBHandle(); 
        if(!redishandleAll)
        { 
            Fir::logger->error("[读取全体],获取内存数据库失败,account=%s,charid=%lu",charbase.account,charbase.charid);
            ret = false;
            break;
        }
        DWORD RecordId =  charid >> 32;
        redishandleAll->setSet("charbase",RecordId,"update",charid);
    }while(0);
    //保存角色档案信息
    return ret ;
}

RecordClient* SceneUser::getSelfRecord()
{
    DWORD RecordId =  charid >> 32;
    return MgrrecordClient.GetRecordByServerId(RecordId);
}
