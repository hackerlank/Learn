#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

void print_client(struct sockaddr_in *addr)
{
    int port = ntohs(addr->sin_port);
    char ip[16];
    bzero(ip,sizeof(ip));
    inet_ntop(AF_INET,&addr->sin_addr.s_addr,ip,sizeof(ip));
    printf("client connect :%s,%d\n",ip,port);
}

int do_server(const int fd)
{
    int ret = 0;
    do
    {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        char buffer[1024];
        bzero(buffer,sizeof(buffer));
        if(recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,&len) <= 0)
        {
            perror("recvfrom error");
            break;
        }
        printf("recvfrom msg :%s\n",buffer);
        if(sendto(fd,buffer,strlen(buffer),0,(struct sockaddr*)&addr,len) <= 0)
        {
            perror("sendto msg error");
            break;
        }
        printf("sendto msg :%s\n",buffer);
        print_client(&addr);
        ret = 1;
    }while(0);
    return ret;
}

int main(int argc,char *argv[])
{
    int ret = 0;
    do
    {
        if(argc < 2)
        {
            perror("argc error");
            break;
        }
        int port = atol(argv[1]);
        int fd = socket(AF_INET,SOCK_DGRAM,0);
        if(fd < 0)
        {
            perror("socket error");
            break;
        }
        
        struct sockaddr_in addr;
        bzero(&addr,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;

        if(bind(fd,(struct sockaddr*)(&addr),sizeof(addr)) < 0)
        {
            perror("bind error");
            break;
        }
        ret = 1;
        while(ret || 1)
        {
            //一个fd可以跟所有的客户端来通信
            ret = do_server(fd);
        }
        close(fd);
    }while(0);
    return ret;
}

