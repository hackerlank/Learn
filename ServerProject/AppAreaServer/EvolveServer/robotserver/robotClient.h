#ifndef ROBOT_CLIENT_H
#define ROBOT_CLIENT_H 
#include "client.h"
#include "messageDispatcher.h"
#include "login.pb.h"

class RobotClient;
typedef MessageDispatcher<boost::shared_ptr<RobotClient> > RobotClientMessageDispatcher;
class RobotClient : public Client
{
    public:
        RobotClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd);
        virtual ~RobotClient();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        inline const std::string getPhone() const
        {
            return m_phone;
        }
        inline void setPhone(const std::string &phone)
        {
            m_phone = phone;
        }
    public:
        static RobotClientMessageDispatcher s_robotClientMsgDispatcher;
    public:
        bool reqLoginGateway(const std::string &ip,const unsigned int port);
    private:
        std::string m_phone;
};

#endif
