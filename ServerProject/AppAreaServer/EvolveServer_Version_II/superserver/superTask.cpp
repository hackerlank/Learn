#include "superTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "superServer.h"
#include "taskManager.h"

SuperMessageDispatcher SuperTask::s_superMsgDispatcher("管理服务器消息处理器");
SuperTask::SuperTask(const int fd) : Task(fd),m_notifyFlg(false)
{
}

SuperTask::~SuperTask()
{
}

MsgRet SuperTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    ret = Task::dispatcher(message);
    if(ret == MR_No_Register)
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(m_id);
        boost::shared_ptr<SuperTask> superTask = boost::dynamic_pointer_cast<SuperTask>(task);
        if(superTask)
        {
            ret = s_superMsgDispatcher.dispatch(superTask,message);
        }
    }
    return ret;
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
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        if(m_notifyFlg)
        {
            ret = true;
            break;
        }
        m_dependMap.clear();
        std::ostringstream oss;
        oss << "select id,ip,port,servertype from t_serverinfo where servertype < " << serverType;
        if(!handle->select(oss.str().c_str(),oss.str().size(),ipVec))
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
    handle->resetStatus();
    return ret;
}

bool SuperTask::notifyDepend()
{
    do
    {
        if(m_notifyFlg)
        {
            break;
        }
        ProtoMsgData::AckUpdateServerInfo ackMsg;
        ProtoMsgData::ServerInfo *selfInfo = SuperServer::getInstance().getServer(m_serverID);
        if(!selfInfo)
        {
            break;
        }
        ProtoMsgData::ServerInfo *serverInfo = ackMsg.mutable_serverinfo();
        if(!serverInfo)
        {
            break;
        }
        bool flag = true;
        *serverInfo = *selfInfo;
        for(auto iter = m_dependMap.begin();iter != m_dependMap.end();++iter)
        {
            if(!TaskManager::getInstance().sendServerMsg(iter->first,ackMsg))
            {
                flag = false;
                break;
            }
        }
        m_notifyFlg = flag;
    }while(false);
    return m_notifyFlg;
}

bool SuperTask::verifyIp(const ProtoMsgData::ServerType &serverType)
{
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        if(m_notifyFlg)
        {
            ret = true;
            break;
        }
        std::ostringstream oss;
        oss << "select id,ip,port from t_serverinfo where servertype = " << serverType;
        if(!handle->select(oss.str().c_str(),oss.str().size(),ipVec))
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
    handle->resetStatus();
    return ret;
}

bool SuperTask::notifyMe()
{
    bool ret = false;
    do
    {
        if(!m_notifyFlg)
        {
            break;
        }
        bool flag = true; 
        ProtoMsgData::AckNotifyMe ackMsg;
        for(auto iter = m_dependMap.begin();iter != m_dependMap.end();++iter)
        {
            if(!iter->second)
            {
                flag = false;
                break;
            }
        }
        if(!flag)
        {
            break;
        }
        //自己的数据
        ProtoMsgData::ServerInfo* selfInfo = SuperServer::getInstance().getServer(m_serverID);
        if(!selfInfo)
        {
            break;
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
                flag = false;
                break;
            }
            ProtoMsgData::ServerInfo *info = SuperServer::getInstance().getServer(iter->first);
            if(!info)
            {
                flag = false;
                break;
            }
            ProtoMsgData::ServerInfo *temp = ackMsg.add_serverinfo();
            if(temp)
            {
                *temp = *info;
            }
        }
        ret = flag ? true : false;
        if(ret)
        {
            sendMsg(ackMsg);
            SuperServer::getInstance().verifyOtherNotify(temp->servertype());
            setVerify(true);
        }
    }while(false);
    return ret;
}

bool SuperTask::verify(const ProtoMsgData::ServerType &serverType)
{
    bool ret = false;
    do
    {
        if(!m_serverID)
        {
            if(!verifyIp(serverType))
            {
                break;
            }
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
