//客户端类声明
#ifndef CLIENT_H
#define CLIENT_H
#include<event2/event.h>
#include<event2/buffer.h>
#include<event2/bufferevent.h>
#include<event2/util.h>
#include"com.h"
class Client
{
    private:
        char ip[IPADDR];
        char name[SERNAME];
        size_t port; 
        ULI connectFd;                     
      
        Client& operator=(const Client &client);
        Client(const Client &client);
        void init(void);
        
    public:
       Client(const char *_ip,const char *_name,size_t _port);
        ~Client(void);
        void runConnect(void);
};
       
#endif
