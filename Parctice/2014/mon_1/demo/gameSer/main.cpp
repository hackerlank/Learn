#include"readConf.h"
int main(void)
{
    char path[] = "config/gameSer.xml";
    GameSer *gameSer = readGameSer(path);
    if(!gameSer)
    {
        perror("game is error");
        exit(0);
    }
    try
    {
        gameSer->runLoop();
    }
    catch(...)
    {
        perror("main gameSer->runLoop() is error");
        exit(0);
    }
    
    return 1;
}

