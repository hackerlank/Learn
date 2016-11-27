/**
 * \file
 * \version  $Id: LoginTask.cpp 2935 2005-09-20 09:00:37Z whj $
 * \author  Songsiliang,
 * \date 2004年11月23日 10时20分01秒 CST
 * \brief 定义登陆连接任务
 *
 */

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <ext/hash_map>

#include "zTCPServer.h"
#include "zTCPTask.h"
#include "zService.h"
#include "zMisc.h"
#include "LoginTask.h"
#include "LoginManager.h"
#include "zType.h"
#include "FLCommand.h"
#include "zDBConnPool.h"
#include "FLServer.h"
#include "GYListManager.h"
#include "zMisc.h"
#include "FLCommand.h"
#include "ServerManager.h"
#include "zTime.h"
#include "LoginCommand.h"
#include "AccountMgr.h"
#include "login.pb.h"
#include "LoginCmdDispatcher.h"
#include "extractProtoMsg.h"
#include "wordFilter.h"

LoginUserCmdDispatcher LoginTask::login_user_dispatcher("login_task_logincmd");
DWORD LoginTask::uniqueID = 0;
LoginTask::LoginTask(zTCPTaskPool *pool, const int sock) : zTCPTask(pool, sock, NULL, true, false), lifeTime(), tempid(0)
{
    m_verify = false;
}

int LoginTask::verifyConn()
{
    int retcode = mSocket.recvToBuf_NoPoll();
    if (retcode > 0)
    {
        BYTE pstrCmd[zSocket::MAX_DATASIZE];
        int nCmdLen = mSocket.recvToCmd_NoPoll(pstrCmd, sizeof(pstrCmd));
        if (nCmdLen <= 0)
        {
            return 0;
        }

        BYTE messageType = *(BYTE*)pstrCmd;
        nCmdLen -= sizeof(BYTE);
        if(messageType != PROTOBUF_TYPE or nCmdLen <= 0)
        {
            Fir::logger->error("[认证_1]:客户端连接验证失败(消息非法)");
            return -1;
        }

        bool ret = msgParseProto(pstrCmd+sizeof(BYTE),nCmdLen);
        if(ret && m_verify)
        {
            Fir::logger->error("[认证_1]:客户端连接验证成功");
            return 1;
        }
        Fir::logger->error("[认证_1]:客户端连接验证失败(消息不对)");
        return -1;
    }
    else
    {
        return retcode;
    }
}

int LoginTask::recycleConn()
{
    mSocket.force_sync();
    return 1;
}

bool LoginTask::uniqueAdd()
{
    return LoginManager::getMe().add(this);
}

bool LoginTask::uniqueRemove()
{
    LoginManager::getMe().remove(this);
    return true;
}

bool LoginTask::msgParseProto(const BYTE *data, const DWORD nCmdLen)
{
    google::protobuf::Message *message = extraceProtoMsg(data,nCmdLen);
    if(!message)
    {
        return false;
    }
    bool ret = this->login_user_dispatcher.dispatch(this,message) ? true : false;
    if(!ret)
    {
        Fir::logger->error("%s(%s, %u)", __PRETTY_FUNCTION__, message->GetTypeName().c_str(),nCmdLen);
    }
    SAFE_DELETE(message);
    return ret;
}

bool LoginTask::msgParseStruct(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen)
{
    if(CMD::CMD_NULL == ptNullCmd->cmd && CMD::PARA_NULL == ptNullCmd->para)
    {
        std::string ret;
        if(encodeMessage(ptNullCmd,nCmdLen,ret) && sendCmd(ret.c_str(),ret.size()))
        {
            return true;
        }
        return false;
    }

    Fir::logger->error("%s(%u, %u, %u), %s", __PRETTY_FUNCTION__, ptNullCmd->cmd, ptNullCmd->para, nCmdLen, getIP());
    return false;
}

void LoginTask::getClientIP(char *clientIP)
{
    char tmpIP[MAX_IP_LENGTH+1];
    bzero(tmpIP, MAX_IP_LENGTH+1);
    strncpy(tmpIP, getIP(), MAX_IP_LENGTH);
    std::vector<std::string> ip_para;
    Fir::stringtok(ip_para, tmpIP, ".", 3);
    std::ostringstream os_ip;
    for(int i =0; i < 4; i++)
    {
        int zeroLen = 3-ip_para[i].size();
        for(int j = 0; j < zeroLen; j++)
        {
            os_ip << "0";
        }
        os_ip << ip_para[i] <<".";
    }
    strncpy(clientIP, os_ip.str().c_str(), MAX_IP_LENGTH);
    return;
}

bool LoginTask::registerAccount(const ProtoMsgData::ReqRegister *message)
{
    ProtoMsgData::AckRegister ackRegister;
    ackRegister.set_ret(false);
    ProtoMsgData::RegisterError error = ProtoMsgData::RE_Default;
    AccountInfo accountInfo;
    do
    {
        if(message->registeruint().account().empty())
        {
            error = ProtoMsgData::RE_Account_Illegal;
            break;
        }

        if(message->registeruint().registertype() == ProtoMsgData::RT_Phone)
        {
            if(message->registeruint().registerkey().empty())
            {
                error = ProtoMsgData::RE_Phone_Illegal;
                break;
            }
        }
        else
        {
            if(message->registeruint().registerkey().empty())
            {
                error = ProtoMsgData::RE_Email_Illegal;
                break;
            }
        }
        if(message->registeruint().passwd().empty())
        {
            error = ProtoMsgData::RE_Passwd_Illegal;
            break;
        }
        strncpy(accountInfo.account,message->registeruint().account().c_str(),sizeof(accountInfo.account));
        if(message->registeruint().registertype() == ProtoMsgData::RT_Phone)
        {
            strncpy(accountInfo.phoneNum,message->registeruint().registerkey().c_str(),sizeof(accountInfo.phoneNum));
        }
        else
        {
            strncpy(accountInfo.email,message->registeruint().registerkey().c_str(),sizeof(accountInfo.email));
        }
        strncpy(accountInfo.passwd,message->registeruint().passwd().c_str(),sizeof(accountInfo.passwd));
        if(AccountMgr::getMe().findAccount(accountInfo))
        {
            error = message->registeruint().registertype() == ProtoMsgData::RT_Phone ? ProtoMsgData::RE_Phone_Again : ProtoMsgData::RE_Email_Again;
            break;
        }
        if(!AccountMgr::getMe().dbInsert(accountInfo))
        {
            break;
        }
        ackRegister.set_ret(true);
    }while(false);
    
    ackRegister.set_failreason(error);
    std::string ret;
    encodeMessage(&ackRegister,ret);
    sendCmd(ret.c_str(),ret.size());
    if(ackRegister.ret())
    {
        ProtoMsgData::ReqGateway reqGateway;
        ProtoMsgData::RegisterUint *temp = reqGateway.mutable_login();
        if(temp)
        {
            *temp = message->registeruint();
        }
        login_user_dispatcher.dispatch(this,&reqGateway);
    }
    Fir::logger->debug("[请求注册] (%s,%s,%s,%u,%u)",accountInfo.account,accountInfo.phoneNum,accountInfo.email,ackRegister.ret(),ackRegister.failreason());
    m_verify = ackRegister.ret();
    return m_verify;
}

bool LoginTask::getGatewayInfo(const ProtoMsgData::ReqGateway *message)
{
    ProtoMsgData::AckGateway ackGateway;
    ackGateway.set_ret(false);
    AccountInfo accountInfo;
    do
    {
        strncpy(accountInfo.account,message->login().account().c_str(),sizeof(accountInfo.account));
        if(message->login().registertype() == ProtoMsgData::RT_Phone)
        {
            strncpy(accountInfo.phoneNum,message->login().registerkey().c_str(),sizeof(accountInfo.phoneNum));
        }
        else
        {
            strncpy(accountInfo.email,message->login().registerkey().c_str(),sizeof(accountInfo.email));
        }
        strncpy(accountInfo.passwd,message->login().passwd().c_str(),sizeof(accountInfo.passwd));
        if(!AccountMgr::getMe().findAccount(accountInfo))
        {
            ackGateway.set_failreason(ProtoMsgData::LE_Account_Error);
            break;
        }
        if(!AccountMgr::getMe().verifyPasswd(accountInfo))
        {
            ackGateway.set_failreason(ProtoMsgData::LE_Passwd_Error);
            break;
        }
        GYList *gateway = GYListManager::getMe().getAvl();
        if(!gateway)
        {
            ackGateway.set_failreason(ProtoMsgData::LE_Gateway_Close);
            break;
        }

        t_NewLoginSession session;
        bzero(&session, sizeof(session));
        session.loginTempID = tempid;
        strncpy(session.client_ip, getIP(), MAX_IP_LENGTH);
        session.accountInfo = accountInfo;
        
        session.wdGatewayID = gateway->wdServerID;
        bcopy(gateway->pstrIP, session.pstrIP, sizeof(session.pstrIP));
        session.wdPort = gateway->wdPort;
        CMD::FL::t_NewSession_Session fl_tCmd; 
        fl_tCmd.session = session;
        std::string ret;
        encodeMessage(&fl_tCmd,sizeof(fl_tCmd),ret);
        ServerManager::getMe().sendCmdToZone(ret.c_str(),ret.size());
        ackGateway.set_ret(true);
    }while(false);

    //失败就返回
    if(!ackGateway.ret())
    {
        std::string ret;
        encodeMessage(&ackGateway,ret);
        sendCmd(ret.c_str(),ret.size());
    }
    Fir::logger->debug("[请求网关] (%s,%s,%s,%u,%u,%s,%u)",accountInfo.account,accountInfo.phoneNum,accountInfo.email,ackGateway.ret(),ackGateway.failreason(),ackGateway.gatewayip().c_str(),ackGateway.gatewayport());
    return ackGateway.ret();
}
