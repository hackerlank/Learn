#include"gameSer.h"
GameSer::GameSer(const char *_ip,const char *_name,size_t _port,size_t _upperNum)
{
    init();
    strncpy(ip,_ip,sizeof(ip));
    strncpy(name,_name,sizeof(name));
    port = _port;
    upperNum = _upperNum;
}

GameSer::~GameSer(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    close(listenerFd);
}


void GameSer::init(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    listenerFd = 0;
    port = 0;
    upperNum = 0;
    base = NULL;
}

void GameSer::runLoop(void)
{
    if(base)
    {
        perror("GameSer::runLoop error base is exist");
        throw 1;
    }
    base = event_base_new();
    if(!base)
    {
        perror("GameSer::runLoop error base is NULL");
        throw 1;
    }
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip);
    
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("GameSer::runLoop error listener");
        throw 1;
    }
    listenerFd = fd;
    evutil_make_socket_nonblocking(listenerFd);
    if(bind(listenerFd,(sockaddr *)&sin,sizeof(sockaddr)) < 0)
    {
        perror("GameSer::runLoop error bind");
        throw 1;
    }
    if(listen(listenerFd,1024) < 0)
    {
        perror("GameSer::runLoop error listen");
        throw 1;
    }
    
    event *listen_event = event_new(base,listenerFd,EV_READ|EV_PERSIST,do_accept,this);
    event_add(listen_event, NULL);
    event_base_dispatch(base);
}





void do_accept(evutil_socket_t listenerFd,short event,void *arg)
{
    GameSer *gameSer = (GameSer *)arg;
    sockaddr sin;
    socklen_t len = sizeof(sin);
    int newfd = accept(listenerFd,(sockaddr *)&sin,&len);
    if(newfd < 0)
    {
        cout<<"warning newfd less 0"<<newfd<<endl;
        return;
    }
    else if(newfd > FD_SETSIZE)
    {
        cout<<"warning newfd more than FDSIZE"<<newfd<<endl;
        close(newfd);
    }
	else
	{
		cout<<" connect new :"<<endl;
	}
}
    

