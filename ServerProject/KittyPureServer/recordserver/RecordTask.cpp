/**
 * \file
 * \version  $Id: RecordTask.cpp 64 2013-04-23 02:05:08Z  $
 * \author  ,@163.com
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 实现读档连接类
 *
 * 
 */


#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "RecordTask.h"
#include "Fir.h"
#include "zDBConnPool.h"
#include "zString.h"
#include "RecordCommand.h"
#include "RecordServer.h"
#include "RecordUserManager.h"
#include "RecordUser.h"
#include "zMetaData.h"
#include <string>
#include <vector>
#include "LoginUserCommand.h"
#include "xmlconfig.h"
#include "tbx.h"
#include "RecordTaskManager.h"
#include "extractProtoMsg.h"
#include "dataManager.h"
#include "TimeTick.h"

/**
 * \brief 验证登陆档案服务器的连接指令
 *
 * 如果验证不通过直接断开连接
 *
 * \param ptCmd 登陆指令
 * \return 验证是否成功
 */
bool RecordTask::verifyLogin(const CMD::RECORD::t_LoginRecord *ptCmd)
{
    using namespace CMD::RECORD;

    if (RECORDCMD == ptCmd->cmd && PARA_LOGIN == ptCmd->para)
    {
        const CMD::SUPER::ServerEntry *entry = RecordService::getMe().getServerEntry(ptCmd->wdServerID);
        char strIP[32];
        strncpy(strIP, getIP(), sizeof(strIP)-1);
        if (entry && ptCmd->wdServerType == entry->wdServerType	&& 0 == strcmp(strIP, entry->pstrIP))
        {
            wdServerID = ptCmd->wdServerID;
            wdServerType = ptCmd->wdServerType;
            return true;
        }
    }

    return false;
}

/**
 * \brief 等待接受验证指令并进行验证
 *
 * 实现虚函数<code>zTCPTask::verifyConn</code>
 *
 * \return 验证是否成功，或者超时
 */
int RecordTask::verifyConn()
{
    int retcode = mSocket.recvToBuf_NoPoll();
    if (retcode > 0)
    {
        BYTE pstrCmd[zSocket::MAX_DATASIZE];
        int nCmdLen = mSocket.recvToCmd_NoPoll(pstrCmd, sizeof(pstrCmd));
        //这里只是从缓冲取数据包，所以不会出错，没有数据直接返回
        if (nCmdLen <= 0)
        {
            return 0;
        }

        BYTE messageType = *(BYTE*)pstrCmd;
        nCmdLen -= sizeof(BYTE);
        if(messageType != STRUCT_TYPE || nCmdLen <= 0)
        {
            Fir::logger->error("%s(%u, %u)", __PRETTY_FUNCTION__, messageType,nCmdLen-1); 
            return -1;
        }

        using namespace CMD::RECORD;
        if (verifyLogin((t_LoginRecord *)(pstrCmd+sizeof(BYTE))))
        {
            Fir::logger->debug("客户端连接通过验证");
            return 1;
        }
        Fir::logger->error("客户端连接验证失败");
        return -1;
    }
    else
        return retcode;
}

/**
 * \brief 确认一个服务器连接的状态是可以回收的
 *
 * 当一个连接状态是可以回收的状态，那么意味着这个连接的整个生命周期结束，可以从内存中安全的删除了：）<br>
 * 实现了虚函数<code>zTCPTask::recycleConn</code>
 *
 * \return 是否可以回收
 */
int RecordTask::recycleConn()
{
    Fir::logger->debug("关闭服务器:%u", getID());
    //TODO 需要保证存档指令处理完成了
    return 1;
}

bool RecordTask::uniqueAdd()
{
    return RecordTaskManager::getMe().uniqueAdd(this);
}

bool RecordTask::uniqueRemove()
{
    return RecordTaskManager::getMe().uniqueRemove(this);
}

//0成功 1失败 2账号已有角色 3角色名称重复
DWORD RecordTask::create_role_inner(const AccountInfo &accountInfo,QWORD &charID)
{
    connHandleID handle = RecordService::dbConnPool->getHandle();
    if ((connHandleID)-1 == handle)
    {
        Fir::logger->debug("[创建角色]:db创建角色失败(数据库连接失败,%s)",accountInfo.account);
        return 1;
    }

    QWORD charid = RecordUserM::getMe().generateCharId();
    Record record;
    zRTime currentTime;
    record.put("f_charid",charid);
    record.put("f_account",accountInfo.account);
    record.put("f_createtime",currentTime.sec());
    record.put("f_email",accountInfo.email);
    record.put("f_phonenum",accountInfo.phoneNum);
    record.put("f_createtime",RecordTimeTick::currentTime.sec());

    DWORD retcode = RecordService::dbConnPool->exeInsert(handle, "t_charbase", &record);
    RecordService::dbConnPool->putHandle(handle);
    if ((DWORD)-1 == retcode)
    {
        Fir::logger->debug("[创建角色]:db创建角色失败(向表插入新角色,%lu,%s,%s,%s)",charid,accountInfo.account,accountInfo.email,accountInfo.phoneNum);
        return 1;
    }

    RecordUser* u = new RecordUser();
    u->charid = charid;
    if (!u->readCharBase())
    {
        Fir::logger->debug("[创建角色]:db创建角色失败(读取档案失败,%lu,%s,%s,%s)",charid,accountInfo.account,accountInfo.email,accountInfo.phoneNum);
        SAFE_DELETE(u);
        return 1;
    }

    if (!RecordUserM::getMe().add(u))
    {
        Fir::logger->debug("[创建角色]:db创建角色失败(添加用户管理器失败,%lu,%s,%s,%s)",charid,accountInfo.account,accountInfo.email,accountInfo.phoneNum);
        SAFE_DELETE(u);
        return 1;
    }

    if (!u->syncBaseMemDB())
    {
        Fir::logger->debug("[创建角色]:db创建角色失败(同步rides失败,%lu,%s,%s,%s)",charid,accountInfo.account,accountInfo.email,accountInfo.phoneNum);
        return 1;
    }
    Fir::logger->debug("[创建角色]:db创建角色成功(新建角色,%lu,%s,%s,%s)",charid,accountInfo.account,accountInfo.email,accountInfo.phoneNum);
    charID = charid;
    return 0;
}

QWORD RecordTask::getCharID(const char *phoneNum,const char *email)
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle();      
    if(!handle)
    {
        return 0;
    }
    if(phoneNum)
    {
        return handle->getInt("rolebaseinfo",phoneNum,"charid");
    }
    return handle->getInt("rolebaseinfo",email,"charid");
}

bool RecordTask::create_role(const CMD::RECORD::t_CreateChar_GateRecord* rev)
{
    if(!rev || getCharID(rev->accountInfo.phoneNum,rev->accountInfo.email))
    {
        Fir::logger->debug("[创建新角色] 重复创建(%s,%s,%s)",rev->accountInfo.phoneNum,rev->accountInfo.email,rev->accountInfo.account);
        return false;
    }

    CMD::RECORD::t_CreateChar_Return_GateRecord ret;
    ret.accountInfo = rev->accountInfo;
    Fir::logger->debug("[创建角色]:db创建新角色(创建新角色,%s)",rev->accountInfo.account);
    ret.retcode = create_role_inner(rev->accountInfo,ret.charID);
    if(ret.retcode == 0)
    {
        Fir::logger->debug("[创建角色]:db创建角色成功(创建新角色,%lu,%s)",ret.charID,rev->accountInfo.account);
    }

    std::string sendRet;
    if(encodeMessage(&ret,sizeof(ret),sendRet))
    {
        sendCmd(sendRet.c_str(),sendRet.size());
    }
    return true;
}

bool RecordTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("RecordTask::msgParseProto 消息没处理");
    return true;
}

bool RecordTask::msgParseRecordCmd(const CMD::RECORD::RecordNull *ptNullCmd, const DWORD nCmdLen)
{
    using namespace CMD::RECORD;
    switch(ptNullCmd->para)
    {
        case PARA_GATE_CREATECHAR:
            {
                t_CreateChar_GateRecord* rev = (t_CreateChar_GateRecord*)ptNullCmd;
                return create_role(rev);
            }
            break;
        case PARA_CLONE_USER_WRITE:
            {
                return true;
            }
            break;
        default:
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return false;
}

/**
 * \brief 解析来自各个服务器连接的指令
 *
 * \param ptNullCmd 待处理的指令
 * \param nCmdLen 指令长度
 * \return 处理是否成功
 */
bool RecordTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }

    using namespace CMD::RECORD;
    switch(ptNullCmd->cmd)
    {
        case RECORDCMD:
            {
                return msgParseRecordCmd((RecordNull*)ptNullCmd,nCmdLen);
            }
            break;
    }
    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return false;
}
