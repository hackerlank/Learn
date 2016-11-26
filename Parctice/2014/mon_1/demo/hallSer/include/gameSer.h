//游戏服务器类声明
#ifndef GAME_SER_H
#define GAME_SER_H
#include"com.h"
class HallSer;
class GameSer
{
    private:
        const IpInfo *ipInfo; //服务器ip信息                    
        ULI connectFd;                            //链接游戏服务器fd  
        size_t nowNum;                            //当前服务器人数
        HallSer *hallSer;
        size_t index;                         //当前游戏服务器在大厅中的下标
        GameSer& operator=(const GameSer &gameSer);
        GameSer(const GameSer &gameSer);
    public:
        GameSer(const IpInfo *_ipInfo,size_t _index,HallSer *hallSer);
        bool isFull(void);
        void connect_game(void);
        void add_person(void);
        ~GameSer(void);
};
#endif
