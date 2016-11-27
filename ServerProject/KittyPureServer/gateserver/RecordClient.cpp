/**
 * \file
 * \version  $Id: RecordClient.cpp 64 2013-04-23 02:05:08Z  $
 * \author  ,@163.com
 * \date 2005年04月01日 11时57分23秒 CST
 * \brief 实现网关服务器到档案服务器的连接客户端
 */

#include "RecordClient.h"
#include "RecordCommand.h"
#include "GatewayServer.h"
#include "Fir.h"
#include "GateUserManager.h"
#include "SuperCommand.h"
#include "GatewayServer.h"
#include "SceneClient.h"
#include "TimeTick.h"
#include "GatewayTaskManager.h"
#include "extractProtoMsg.h"

///RecordClient的唯一实例
//RecordClient *recordClient = NULL;
ManagerRecordClient MgrrecordClient;


/**
 * \brief 创建到档案服务器的连接
 *
 * \return 连接是否成功
 */
bool RecordClient::connectToRecordServer()
{
    if (!zTCPClientTask::connect())
    {
        Fir::logger->error("连接档案服务器失败");
        return false;
    }

    using namespace CMD::RECORD;
    t_LoginRecord tCmd;
    tCmd.wdServerID = GatewayService::getMe().getServerID();
    tCmd.wdServerType = GatewayService::getMe().getServerType();

    std::string ret;
    if(encodeMessage(&tCmd,sizeof(t_LoginRecord),ret))
    {
        return sendCmd(ret.c_str(),ret.size());
    }
    return false;
}
bool RecordClient::connect()
{
    return connectToRecordServer();
}
QWORD RecordClient::playerNum()
{
    zMemDB* handle = zMemDBPool::getMe().getMemDBHandle(wdServerID % MAX_MEM_DB+1);
    if (handle!=NULL)
    {
        return handle->getInt("recorder" , QWORD(wdServerID), "personnum");
    }
    return 0;
}

void RecordClient::addToContainer()
{
    MgrrecordClient.add(this);
}

void RecordClient::removeFromContainer()
{
    MgrrecordClient.remove(this);
}
bool RecordClient::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    Fir::logger->error("RecordClient::msgParseProto 消息没处理");
    return true;
}

bool RecordClient::msgParseRecordCmd(const CMD::RECORD::RecordNull *recordNull,const DWORD nCmdLen)
{
    using namespace CMD::RECORD;
    switch(recordNull->para)
    {
        case PARA_GATE_CREATECHAR_RETURN:
            {
                t_CreateChar_Return_GateRecord* cmd = (t_CreateChar_Return_GateRecord*)recordNull;
                GateUser* gateUser = GateUserManager::getMe().getUserByAccount(cmd->accountInfo);
                if (!gateUser || !gateUser->gatewaytask)
                {
                    Fir::logger->debug("[登录网关]:创建新角色db返回失败(网关use不存在,%lu)",cmd->charID);
                    return true;
                }

                if (gateUser->isTerminateWait() || gateUser->isTerminate() || !gateUser->isCreateState())
                {
                    Fir::logger->debug("[登录网关]:创建新角色db返回失败(不在创建角色状态,%lu)",cmd->charID);
                    gateUser->ackLoginGateway(ProtoMsgData::LE_Time_Out);
                    return true;
                }

                if (cmd->retcode == 0)
                {
                    //创建成功,先写个简单版，但这儿是线程不安全的，回头，在task上，再加个定时器，用来处理这类事件
                    gateUser->charid = cmd->charID;
                    Fir::logger->debug("[登录网关]:创建新角色db返回成功(新建角色成功,%lu)",cmd->charID);

                    if (gateUser->gatewaytask) 
                    {
                        gateUser->gatewaytask->setCharID(cmd->charID);
                        if(!gateUser->beginSelect())
                        {
                            Fir::logger->debug("[登录网关]:创建新角色db返回失败(beginSelect失败,%lu)",cmd->charID);
                            return false;
                        }
                        if (!GateUserManager::getMe().addUserCharid(gateUser))
                        {
                            Fir::logger->debug("[登录网关]:创建新角色db返回失败(addUserCharid失败,%lu)",cmd->charID);
                            gateUser->ackLoginGateway(ProtoMsgData::LE_Other_Error);
                            return false;
                        }
                        GatewayService::getMe().notifyLoginServer();
                        gateUser->ackLoginGateway(ProtoMsgData::LE_Default,true);
                    }
                    return true;
                }
                gateUser->ackLoginGateway(ProtoMsgData::LE_No_Char);
                return true;
            }
            break;
        default:
            break;
    }

    Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, recordNull->cmd, recordNull->para, nCmdLen);
    return false;
}

/**
 * \brief 解析来自档案服务器的指令
 *
 * \param ptNullCmd 待解析的指令
 * \param nCmdLen 待解析的指令长度
 * \return 解析指令是否成功
 */
bool RecordClient::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(msgParseNullCmd(ptNullCmd,nCmdLen))
    {
        return true;
    }
    using namespace CMD::RECORD;
    bool ret = false;
    switch(ptNullCmd->cmd)
    {
        case RECORDCMD:
            {
                ret = msgParseRecordCmd((RecordNull*)ptNullCmd,nCmdLen);
            }
            break;
    }
    if(ret == false)
        Fir::logger->error("%s(%u, %u, %u)", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen);
    return true;
}

bool ManagerRecordClient::init()
{
    const CMD::SUPER::ServerEntry *serverEntry = GatewayService::getMe().getServerEntryByType(RECORDSERVER);
    recordclientPool = new zTCPClientTaskPool(100,8000);
    if (NULL == recordclientPool
            || !recordclientPool->init())
        return false;

    while(serverEntry)
    {
        RecordClient *recordclient = new RecordClient(serverEntry->pstrIP, serverEntry->wdPort,serverEntry->wdServerID);
        if (NULL == recordclient)
        {
            Fir::logger->error("没有足够内存，不能建立record服务器客户端实例");
            return false;
        }

        if(recordclientPool->put(recordclient))
        {
            if(!recordclient->connect())
            {
                Fir::logger->error("connect record err");
                return false;

            }
            recordclientPool->addCheckwait(recordclient);
        }
        serverEntry = GatewayService::getMe().getNextServerEntryByType(RECORDSERVER, &serverEntry);
    }

    return true;
}

/**
 ** \brief 周期间隔进行连接的断线重连工作
 ** \param ct 当前时间
 **/
void ManagerRecordClient::timeAction(const zTime &ct)
{
    if (actionTimer.elapse(ct) > 4)
    {
        if (recordclientPool)
            recordclientPool->timeAction(ct);
        actionTimer = ct;
    }
}
/**
 ** \brief 向容器中添加已经成功的连接
 ** \param recordclient 待添加的连接
 **/
void ManagerRecordClient::add(RecordClient *recordclient)
{
    if (recordclient)
    {
        zRWLock_scope_wrlock scope_wrlock(rwlock);
        m_mapRecord.insert(std::make_pair(recordclient->getServerID(), recordclient));
    }
}

/**
 ** \brief 从容器中移除断开的连接
 ** \param recordclient 待移除的连接
 **/
void ManagerRecordClient::remove(RecordClient *recordclient)
{
    if (recordclient)
    {
        zRWLock_scope_wrlock scope_wrlock(rwlock);
        auto it = m_mapRecord.find(recordclient->getServerID());
        if (it != m_mapRecord.end())
        {
            m_mapRecord.erase(it);
        }
    }
}

bool ManagerRecordClient::reConnectrecord(const CMD::SUPER::ServerEntry *serverEntry)
{
    if (NULL == recordclientPool)
    {
        return false;
    }

    if (serverEntry)
    {
        RecordClient *recordclient = FIR_NEW RecordClient(serverEntry->pstrIP, serverEntry->wdPort,serverEntry->wdServerID);
        if (NULL == recordclient)
        {
            Fir::logger->error("没有足够内存，不能建立record服务器客户端实例");
            return false;
        }
        if(recordclientPool->put(recordclient))
        {
            if(!recordclient->connect())
            {
                Fir::logger->error("connect record err");
                return false;

            }
            recordclientPool->addCheckwait(recordclient);
        }

#ifdef _PQQ_DEBUG
        Fir::logger->debug("[重连档案] 网关重新连接档案 ip=%s,name=%s,port=%d"
                ,serverEntry->pstrIP,serverEntry->pstrName,serverEntry->wdPort);
#endif
    }
    return true;
}

/**
 * \brief 设置到档案的某一连接是否需要重连
 * \param ip 要连接的ip
 * \param port 端口
 * \param reconn 是否重连 true重连，false 不再重连，将会删掉
 */
void ManagerRecordClient::setTaskReconnect(const std::string& ip, unsigned short port, bool reconn)
{
    if (recordclientPool)
    {
        recordclientPool->setTaskReconnect(ip, port, reconn);
    }
}


RecordClient* ManagerRecordClient::GetRecordByServerId(DWORD wServerId)
{
    auto it = m_mapRecord.find(wServerId);
    if(it == m_mapRecord.end())
    {
        return NULL;
    }
    return it->second;

}


RecordClient*  ManagerRecordClient::GetMinPlayerRecord()
{
    DWORD NowNum = 0 ;
    DWORD MinId =  0 ;
    for(auto it = m_mapRecord.begin(); it != m_mapRecord.end(); it++)
    {
        if(!it->second)
        {
            continue;
        }
        if(!GatewayService::getMe().OtherServerhasDBtable(it->first,"t_charbase"))
        {
            continue;
        }
        if(MinId == 0 || it->second->playerNum() < NowNum)
        {
            NowNum = it->second->playerNum();
            MinId = it->first;

        }

    }
    return GetRecordByServerId(MinId);

}

void  ManagerRecordClient::final()
{
    SAFE_DELETE(recordclientPool);
}
