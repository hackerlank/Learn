#ifndef CONNECT_H
#define CONNECT_H
#include "head.h"
#include "singleton.h"
#include "flyer.h"
#include "messageQueue.h"
#include "timefun.h"
#include "system.pb.h"
#include "messageDispatcher.h"

enum TaskStatus
{
    Task_Status_Close = 0,  //关闭
    Task_Status_Verify = 1, //验证
    Task_Status_Main = 2,  //主循环
    Task_Status_Recycle = 3, //回收
};

class Connect;
typedef MessageDispatcher<Connect*> ConnectMessageDispatcher;
class Connect : private DisCopy
{
    protected:
        int m_socket;
        unsigned long m_id;
        static unsigned long s_tempid;
        TaskStatus m_status;
        TimeTv m_lifeTime; 
        unsigned int m_serverID;
        ProtoMsgData::ServerType m_serverType;
        TimeTv m_heartTime;
        //接收消息缓冲队列
        MessageBuffer m_messageBuffer;
        //消息队列
        MessageQueue m_messageQueue;
    public:
        Connect(const int socket);
        virtual ~Connect()
        {
            char temp[100] = {0};
            snprintf(temp,sizeof(temp),"析构连接(%lu)",getID());
            LOG4CXX_INFO(Flyer::logger,temp);
        }
        inline unsigned long getID() const
        {
            return m_id;
        }
        inline unsigned int getServerID() const
        {
            return m_serverID;
        }
        inline ProtoMsgData::ServerType getServerType() const
        {
            return m_serverType;
        }
        inline void setServerID(const unsigned int severID)
        {
            m_serverID = severID;
        }
        inline void setServerType(const ProtoMsgData::ServerType &serverType)
        {
            m_serverType = serverType;
        }
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message)
        {
            return MR_No_Register;
        }
        void addEpoll(const int epfd,const unsigned long event); 
        void delEpoll(const int epfd,const unsigned long events);
        bool accpetMsg();
        void closeFd();
        void doAcceptMessage();
        bool randTestDB();
        bool sendMsg(const google::protobuf::Message &message);
        TaskStatus getStatus();
        void setStatus(const TaskStatus status);
        void nextStatus();
        bool isElapse();
        void resetLifeTime();
        static bool sendMsg(int fd,const google::protobuf::Message &message);
        bool isHeartElapse();
        void resetHeartTime();
        bool sendHeartMsg();
    public:
        static ConnectMessageDispatcher s_connectMsgDispatcher;
};

#endif

