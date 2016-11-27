//大厅服务器类声明
#ifndef HALL_SER_H
#define HALL_SER_H
#include<event2/event.h>
#include<event2/buffer.h>
#include<event2/bufferevent.h>
#include<event2/util.h>
#include"com.h"
typedef ULI UID_TYPE;
typedef ULI CONNECT_TYPE;
typedef size_t INDEX_TYPE;
class GameSer;
class HallSer
{
    private:
        char ip[IPADDR];
        char name[SERNAME];
        size_t port; 
        ULI upperNum;
        ULI listenerFd;                            //监听客户端fd  
        event_base *base;
        UID_TYPE uid;
        vector<GameSer*> gameSerVec;
        map<UID_TYPE,CONNECT_TYPE> uidFdMap;         //uid对应connectfd
        map<CONNECT_TYPE,UID_TYPE> fdUidMap;          //connectfd对应uid
        map<INDEX_TYPE,set<UID_TYPE> > indexUidMap;   //游戏服务器下表对应uid集合
        map<UID_TYPE,INDEX_TYPE> uidIndexMap;          //uid对应index
        
        HallSer& operator=(const HallSer &hallSer);
        HallSer(const HallSer &hallSer);
        void closeGameSerFd(size_t index);           //关闭某个游戏服务器的所有连接
        void delAllGameSer(void);
        void initGameSer(void);
        void init(void);
        void runLoop(void);
        bool check_connect(CONNECT_TYPE connectFd);
        int find_empty_gameSer(void);
        bool insert_connect(CONNECT_TYPE connectFd,INDEX_TYPE index);
        bool accept_connect(CONNECT_TYPE connectFd);
    public:
        HallSer(void);
        ~HallSer(void);
};
void do_accept(evutil_socket_t listenerFd,short event,void *arg);              
#endif
