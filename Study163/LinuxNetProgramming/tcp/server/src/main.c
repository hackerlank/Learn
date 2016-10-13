#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>

void printClient(const int fd,const struct sockaddr_in *addr)
{
    int port = ntohs(addr->sin_port);
    char ip[16];
    bzero(ip,sizeof(ip));
    inet_ntop(AF_INET,&addr->sin_addr.s_addr,ip,sizeof(ip));
    printf("connect lient:%s(%d,%d)\n",ip,port,fd);
}

void doWrite(const int fd)
{
    do
    {
        long sec = time(0);
        char *buffer = ctime(&sec);
        if(write(fd,buffer,strlen(buffer)) != strlen(buffer))
        {
            perror("write error");
            break;
        }
        printf("write success:%s\n",buffer);
    }while(0);
}

void doRead(const int fd)
{
    char buffer[1024];
    bzero(buffer,sizeof(buffer));
    do
    {
        if(read(fd,buffer,sizeof(buffer)) < 0)
        {
            perror("read error");
            break;
        }
    }while(0);
}

int main(int argc,char *argv[])
{
    int flag = 0;
    do
    {
        if(argc < 2)
        {
            perror("port error");
            break;
        }
        int port = atol(argv[1]);
        int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0)
        {
            perror("socket error");
            break;
        }
        printf("port:%d\n",port);
        struct sockaddr_in addr;
        bzero(&addr,sizeof(struct sockaddr_in));
        addr.sin_family = AF_INET;
        //这里填充网络字节序
        addr.sin_port = htons(port);
        //这里表示是所有网卡
        addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
        {
            perror("bind error");
            break;
        }
        if(listen(fd,20) < 0)
        {
            perror("listen error");
            break;
        }
        while(1)
        {
            struct sockaddr_in client;
            bzero(&client,sizeof(client));
            socklen_t len = sizeof(client); 
            int newFd = accept(fd,(struct sockaddr*)&client,&len);
            printClient(newFd,&client);
            doWrite(newFd);
            close(newFd);
        }
        close(fd);
        flag = 1;
    }while(0);
    return flag;
}
