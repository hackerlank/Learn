//游戏服务器实现文件
#include"gameSer.h"
#include"hallSer.h"
GameSer::GameSer(const IpInfo *_ipInfo,size_t _index,HallSer *_hallSer)
{
    nowNum = 0;
    connectFd = 0; 
    ipInfo = _ipInfo;
    index = _index;
    hallSer = _hallSer;
    connect_game();
}
bool GameSer::isFull(void)
{
    return nowNum >= ipInfo->upperNum;
}
void GameSer::connect_game(void)
{
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(ipInfo->port);
    sin.sin_addr.s_addr = inet_addr(ipInfo->ip);
	cout<<"ip:"<<ipInfo->ip<<" port:"<<ipInfo->port<<endl;
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd <= 0)
    {
        perror("GameSer::connect_game socket is error");
        throw 1;
    }
    connectFd = fd;
    if(connect(connectFd,(sockaddr*)&sin,sizeof(sin)) < 0)
    {
        perror("GameSer::connect_game connect error");
        throw 1;
    }
    evutil_make_socket_nonblocking(connectFd);
}
void GameSer::add_person(void)
{
    ++nowNum;
}
GameSer::~GameSer(void)
{
    close(connectFd);
    hallSer = NULL;
    ipInfo = NULL;
}



    

