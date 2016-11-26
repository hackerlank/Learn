#include"readConf.h"
int main(void)
{
    char path[] = "config/client.xml";
    Client *client = readClient(path);
    if(!client)
    {
        perror("main error client is NULL");
        exit(0);
    }
    try
    {
        client->runConnect();
    }
    catch(...)
    {
        perror("client->runConnect() error");
        exit(0);
    }
    
    return 1;
}

