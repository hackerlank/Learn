#include "superTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "superServer.h"
#include "taskManager.h"

SuperMessageDispatcher SuperTask::s_superMsgDispatcher("管理服务器消息处理器");
SuperTask::SuperTask(const int fd) : Connect(fd),m_notifyFlg(false)
{
}

SuperTask::~SuperTask()
{
}

MsgRet SuperTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<SuperTask> task = boost::dynamic_pointer_cast<SuperTask>(TaskManager::getInstance().getTask(m_id));
    return s_superMsgDispatcher.dispatch(task,message);
}

bool SuperTask::accepteResp(const unsigned int serverID)
{
    bool ret = false;
    if(m_dependMap.find(serverID) != m_dependMap.end())
    {
        m_dependMap[serverID] = true;
        verify(m_serverType);
        ret = true;
    }
    return ret;
}

bool SuperTask::getDependMap(const ProtoMsgData::ServerType &serverType)
{
    bool ret = false;
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        if(m_notifyFlg)
        {
            ret = true;
            break;
        }
        m_dependMap.clear();
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"select id,ip,port,servertype from t_serverinfo where servertype < %u",serverType);
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        bool breakFlg = false;
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("id") == tempMap.end())
            {
                continue;
            }
            unsigned int id = tempMap["id"];
            std::string ip = tempMap["ip"];
            unsigned int kindType = tempMap["servertype"];
            if(kindType == ProtoMsgData::ST_Login || kindType == ProtoMsgData::ST_Super)
            {
                continue;
            }
            ProtoMsgData::ServerInfo *depend = SuperServer::getInstance().getServer(id);
            if(!depend)
            {
                breakFlg = true;
                break;
            }
            if(depend->status() != ProtoMsgData::ST_Start)
            {
                breakFlg = true;
                break;
            }
            m_dependMap.insert(std::pair<unsigned int,bool>(id,false));
        }
        ret = breakFlg ? false : true;
    }while(false);
    return ret;
}

bool SuperTask::notifyDepend()
{
    if(m_notifyFlg)
    {
        return true;
    }
    ProtoMsgData::AckUpdateServerInfo ackMsg;
    ProtoMsgData::ServerInfo *selfInfo = SuperServer::getInstance().getServer(m_serverID);
    if(!selfInfo)
    {
        return false;
    }
    ProtoMsgData::ServerInfo *serverInfo = ackMsg.mutable_serverinfo();
    if(!serverInfo)
    {
        return false;
    }
    *serverInfo = *selfInfo;
    for(auto iter = m_dependMap.begin();iter != m_dependMap.end();++iter)
    {
        if(!TaskManager::getInstance().sendServerMsg(iter->first,ackMsg))
        {
            return false;
        }
    }
    m_notifyFlg = true;
    return true;
}

bool SuperTask::verifyIp(const ProtoMsgData::ServerType &serverType)
{
    bool ret = false;
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        if(m_notifyFlg)
        {
            ret = true;
            break;
        }
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"select id,ip,port from t_serverinfo where servertype = %u",serverType);
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("id") == tempMap.end())
            {
                continue;
            }
            unsigned int id = tempMap["id"];
            unsigned int port = tempMap["port"];
            std::string ip = tempMap["ip"];
            if(SuperServer::getInstance().findServer(id))
            {
                continue;
            }
            ProtoMsgData::ServerInfo info;
            info.set_servertype(serverType);
            info.set_id(id);
            info.set_ip(ip);
            info.set_port(port);
            m_serverID = id;
            m_serverType = serverType;
            SuperServer::getInstance().addServer(info);
            ret = true;
            break;
        }
    }while(false);
    return ret;
}

bool SuperTask::notifyMe()
{
    if(!m_notifyFlg)
    {
        return false;
    }
    ProtoMsgData::AckNotifyMe ackMsg;
    for(auto iter = m_dependMap.begin();iter != m_dependMap.end();++iter)
    {
        if(!iter->second)
        {
            return false;
        }
    }
    //自己的数据
    ProtoMsgData::ServerInfo* selfInfo = SuperServer::getInstance().getServer(m_serverID);
    if(!selfInfo)
    {
        return false;
    }
    selfInfo->set_status(ProtoMsgData::ST_Start);
    ProtoMsgData::ServerInfo *temp = ackMsg.add_serverinfo();
    if(temp)
    {
        *temp = *selfInfo;
    }

    //别的数据
    for(auto iter = m_dependMap.begin();iter != m_dependMap.end();++iter)
    {
        if(!iter->second)
        {
            return false;
        }
        ProtoMsgData::ServerInfo *info = SuperServer::getInstance().getServer(iter->first);
        if(!info)
        {
            return false;
        }
        ProtoMsgData::ServerInfo *temp = ackMsg.add_serverinfo();
        if(temp)
        {
            *temp = *info;
        }
    }
    nextStatus();
    sendMsg(ackMsg);
    SuperServer::getInstance().verifyOtherNotify(temp->servertype());
    return true;
}



bool SuperTask::verify(const ProtoMsgData::ServerType &serverType)
{
    bool ret = false;
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        if(!verifyIp(serverType))
        {
            break;
        }
        if(!getDependMap(serverType))
        {
            break;
        }
        if(!notifyDepend())
        {
            break;
        }
        notifyMe();
        ret = true;
    }while(false);
    return ret;
}
