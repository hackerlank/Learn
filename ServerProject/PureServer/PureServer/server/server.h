#ifndef SERVER_H
#define SERVER_H
#include <string>
#include "singleton.h"
#include <map>
#include <vector>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <iostream>
using namespace std;

class Server : public Singleton<Server>
{
    private:
        //static const std::string s_ip = "121.40.77.217";
        static const int s_port = 10000;
        static const int s_timeOut = 1000;
        static const int s_maxClient = 2000;
        std::map<int,int> m_socketPortMap;
        std::vector<struct epoll_event> m_epollEventVec; 
        int m_fd;
        int m_epfd;
    private:
        int accept(std::map<int,int> &socketMap);
    public:
        bool init();
        void serverCallBack();
    private:
        friend class Singleton<Server>;
        Server();
        ~Server()
        {
            TEMP_FAILURE_RETRY(::close(m_fd));
            TEMP_FAILURE_RETRY(::close(m_epfd));
        }
};

#endif
