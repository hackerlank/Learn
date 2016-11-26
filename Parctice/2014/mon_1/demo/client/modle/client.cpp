#include"client.h"
Client::Client(const char *_ip,const char *_name,size_t _port)
{
    init();
    strncpy(ip,_ip,sizeof(ip));
    strncpy(name,_name,sizeof(name));
    port = _port;
}

Client::~Client(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    port = 0;
    close(connectFd);
}


void Client::init(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    connectFd = 0;
    port = 0;
}

void Client::runConnect(void)
{
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip);
    
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("Client::runConnect error socket");
        throw 1;
    }
    connectFd = fd;
    socklen_t len = sizeof(sin);
    if(connect(connectFd,(sockaddr *)&sin,len) < 0)
    {
        perror("Client::runConnect error connect");
        throw 1;
    }
    evutil_make_socket_nonblocking(connectFd);
}
