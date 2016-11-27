//游戏服务器类声明
#ifndef GAME_SER_H
#define GAME_SER_H
#include<event2/event.h>
#include<event2/buffer.h>
#include<event2/bufferevent.h>
#include<event2/util.h>
#include"com.h"
class GameSer
{
    private:
        char ip[IPADDR];
        char name[SERNAME];
        size_t port; 
        ULI upperNum;
        ULI listenerFd;                            //监听客户端fd  
        event_base *base;
      
        GameSer& operator=(const GameSer &gameSer);
        GameSer(const GameSer &gameSer);
        void init(void);
        
    public:
       GameSer(const char *_ip,const char *_name,size_t _port,size_t _upperNum);
        ~GameSer(void);
        void runLoop(void);
};
void do_accept(evutil_socket_t listenerFd,short event,void *arg);              
#endif
