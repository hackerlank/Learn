#include "superClient.h"
#include "flyer.h"
#include "system.pb.h"
#include "client.h"
#include "server.h"

SuperClientMessageDispatcher SuperClient::s_dispatcher("管理服务器客户端消息处理器");
SuperClient::SuperClient(Server *server) : Connect(-1),Thread("管理服务器客户端"),m_epfd(-1),m_server(server)
{
}

SuperClient::~SuperClient()
{
    TEMP_FAILURE_RETRY(::close(m_epfd));
    TEMP_FAILURE_RETRY(::close(m_socket));
    m_server = NULL;
}

bool SuperClient::init()
{
    bool ret = false;
    do
    {
        if(m_epfd != -1)
        {
            break;
        }
        m_epfd = epoll_create(1);
        if(m_epfd == -1)
        {
            break;
        }
        int fd = 0;
        if(!Client::connectOwner(fd,Flyer::globalConfMap["superip"],atol(Flyer::globalConfMap["superport"].c_str())))
        {
            LOG4CXX_INFO(Flyer::logger,"[管理服务器客户端] 连接错误");
            break;
        }
        m_socket = fd;
        if(m_eventVec.empty())
        {
            m_eventVec.resize(1);
        }
        addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
        ProtoMsgData::ReqServerInfo reqServerInfo;
        reqServerInfo.set_servertype(m_server->getType());
        if(!sendMsg(reqServerInfo))
        {
            break;
        }
        ret = true;
    }while(false);

    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[管理服务器客户端] 连接%s(%s,%s)",ret ? "成功" : "失败",Flyer::globalConfMap["superip"].c_str(),Flyer::globalConfMap["superport"].c_str());
    LOG4CXX_INFO(Flyer::logger,temp);
    return ret;
}

void SuperClient::close()
{
    if(m_epfd != -1)
    {
        TEMP_FAILURE_RETRY(::close(m_epfd));
    }
    m_epfd = -1;
    closeFd();
    final();
    end();
}

void SuperClient::run()
{
    while(!isFinal())
    {
        while(m_epfd == -1)
        {
            if(!init())
            {
                close();
            }
        }
        bool breakFlg = true;
        do
        {
            int ret = epoll_wait(m_epfd,&m_eventVec[0],1,0);
            if(ret)
            {
                struct epoll_event &event = m_eventVec[0];
                if(event.events & EPOLLPRI)
                {
                    break;
                }
                if(event.events & EPOLLERR)
                {
                    break;
                }
                if(event.events & EPOLLIN)
                {
                    accpetMsg();
                }
                if(event.events & EPOLLOUT)
                {
                }
                event.events = 0;
            }
            breakFlg = false;
        }while(false);

        if(breakFlg)
        {
           close(); 
        }
        msleep(10);
    }
    close();
}

MsgRet SuperClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<SuperClient> superClient = boost::dynamic_pointer_cast<SuperClient>(getPtr());
    return s_dispatcher.dispatch(superClient,message);
}

