#include "task.h"
#include "cmdFunManager.h"
//#include "parseMessage.h"
#include "serialize.pb.h"
#include "mysqlPool.h"

unsigned long Task::s_tempid = 0;
bool Task::s_initFlg = false;
std::vector<std::string> Task::s_msgVec;

Task::Task(const int socket) : m_socket(socket)
{
    ++s_tempid;
    m_id = s_tempid;
    if(!s_initFlg)
    {
        initMsgVec();
        s_initFlg = true;
    }
}

void Task::addEpoll(const int epfd,const unsigned long events)
{
    struct epoll_event event;
    event.data.u64 = m_id;
    event.events = events;
    epoll_ctl(epfd,EPOLL_CTL_ADD,m_socket,&event);
}

void Task::delEpoll(const int epfd,const unsigned long events)
{
    struct epoll_event event;
    event.data.u64 = m_id;
    event.events = events;
    epoll_ctl(epfd,EPOLL_CTL_DEL,m_socket,&event);
}

bool Task::accpetMsg()
{
    bool ret = false;
    do
    {
        if(!m_messageBuffer.adjustPos())
        {
            break;
        }
        unsigned int len = recv(m_socket,m_messageBuffer.beginWrite(),m_messageBuffer.ableWriteSize(),0);
        if(len == 0)
        {
            break;
        }
        else if(len < 0)
        {
            if(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
            {
                break;
            }
            ret = true;
            break;
        }
        m_messageBuffer.moveWritePos(len);
        MessageData *messageData = m_messageBuffer.beginRead();
        while(messageData)
        {
            boost::shared_ptr<MessageData> message(messageData);
            m_messageQueue.putMessage(message);
            messageData = m_messageBuffer.beginRead();
            google::protobuf::Message *messge = decodeMessage(message);
            if(!messge)
            {
                continue;
            }
            boost::shared_ptr<google::protobuf::Message> sharedMessage(messge);
            Debug(Flyer::logger,"接受消息(" << m_id << "," << sharedMessage->GetTypeName() << ")");
        }
        ret = true;
    }while(false);

    return ret;
}

void Task::sendMsg()
{
    ProtoMsgData::ReqTest test;
    std::string ret;
    encodeMessage(&test,ret);
    send(m_socket,ret.c_str(),ret.size(),0);
    Debug(Flyer::logger,"发送消息(" << m_id << "," << test.GetTypeName() << ")");
}

void Task::initMsgVec()
{
    s_msgVec.push_back("你好呀!");
    s_msgVec.push_back("真的不错!");
    s_msgVec.push_back("上海");
    s_msgVec.push_back("湖北");
    Info(Flyer::logger,"s_msgVec长度为(" << s_msgVec.size() << ")");
}

void Task::closeFd()
{
    close(m_socket);
}

void Task::doAcceptMessage()
{
    while(!m_messageQueue.empty())
    {
        boost::shared_ptr<MessageData> messageData = m_messageQueue.getMessage();
        std::string messageName = CmdFunManager::getInstance().getProtoName(messageData->key);
        if(messageName.empty())
        {
            Error(Flyer::logger,"接受到未知消息(" << messageData->key << ")");
            continue;
        }
        google::protobuf::Message *message = createMessage(messageName.c_str());
        if(!message)
        {
            Error(Flyer::logger,"没有生成消息实例(" << messageName << ")");
            continue;
        }
        shared_ptr<google::protobuf::Message> sharedMessage(message);
        sharedMessage->ParseFromArray(&messageData->data[0], messageData->size);
    }
}

bool Task::randTestDB()
{
    bool ret = false;
    char temp[100] = {0};
    do
    {
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        snprintf(temp,sizeof(temp),"INSERT INTO test VALUES(0,%lu)",m_id);
        if(!handle->execSql(temp,strlen(temp)))
        {
            break;
        }
        ret = true;
    }while(false);

    char mark[100] = {0};
    snprintf(mark,sizeof(mark),"[数据库操作] 插入%s(%s)",ret ? "成功" : "失败",temp);
    Info(Flyer::logger,mark);
    return ret;
}
