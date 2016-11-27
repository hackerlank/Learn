#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "singleton.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

class Client : public Singleton<Client>
{
    private:
        friend class Singleton<Client>;
        Client() {};
        ~Client() {};
    public:
        bool connectServer();
    private:
        static std::string s_ip;
        static int s_port;
};

#endif
