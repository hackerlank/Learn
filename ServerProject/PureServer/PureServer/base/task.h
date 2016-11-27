#ifndef TASK_H
#define TASK_H
#include "head.h"
#include "singleton.h"
#include "flyer.h"
#include "messageQueue.h"

class Task : public SharedPtr , private DisCopy
{
    private:
        int m_socket;
        unsigned long m_id;
        static unsigned long s_tempid;
        static bool s_initFlg;
        static std::vector<std::string> s_msgVec;
        //接收消息缓冲队列
        MessageBuffer m_messageBuffer;
        //消息队列
        MessageQueue m_messageQueue;
    public:
        Task(const int socket);
        ~Task()
        {
            char temp[100] = {0};
            snprintf(temp,sizeof(temp),"析构任务(%lu)",getID());
            LOG4CXX_INFO(Flyer::logger,temp);
        }
        inline unsigned long getID() const
        {
            return m_id;
        }
        void addEpoll(const int epfd,const unsigned long event); 
        void delEpoll(const int epfd,const unsigned long events);
        void sendMsg();
        bool accpetMsg();
        void closeFd();
        void doAcceptMessage();
        bool randTestDB();
        static void initMsgVec();
};

#endif

