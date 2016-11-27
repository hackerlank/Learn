#include "robotClient.h"
#include "clientManager.h"
#include "clientThread.h"

RobotClientMessageDispatcher RobotClient::s_robotClientMsgDispatcher("机器人消息处理器");
RobotClient::RobotClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd),m_phone()
{
}

RobotClient::~RobotClient()
{
}

MsgRet RobotClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    do
    {
        ret = Client::dispatcher(message);
        if(ret == MR_No_Register)
        {
            boost::shared_ptr<RobotClient>robotClient = boost::dynamic_pointer_cast<RobotClient>(getPtr());
            ret = s_robotClientMsgDispatcher.dispatch(robotClient,message);
        }
    }while(false);
    return ret;
}

bool RobotClient::reqLoginGateway(const std::string &ip,const unsigned int port)
{
    bool ret = false;
    do
    {
        int fd = -1;
        if(!Client::connectOwner(fd,ip,port))
        {
            break;
        }
        boost::shared_ptr<RobotClient> client(new RobotClient("机器人",ip,port,fd));
        if(!ClientManager::getInstance().add(client))
        {
            break;
        }
        if(!ClientThread::getInstance().add(client->getID()))
        {
            break;
        }
        ProtoMsgData::ReqLoginGateway cmd;
        client->setPhone(m_phone);
        cmd.set_phone(m_phone);
        cmd.set_passwd(m_phone);
        ret = client->sendMsg(cmd);
        ClientThread::getInstance().addRecycle(getID());
    }while(false);
    return ret; 
}
