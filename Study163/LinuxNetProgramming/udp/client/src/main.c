#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

int do_client(const int fd,const int time,struct sockaddr_in *addr)
{
    int ret = 0;
    do
    {
        socklen_t len = sizeof(struct sockaddr_in);
        char buffer[1024];
        bzero(buffer,sizeof(buffer));
        sprintf(buffer,"%d,udp fuck you",time);
        if(sendto(fd,buffer,strlen(buffer),0,(struct sockaddr*)addr,len) <= 0)
        {
            perror("sendto msg error");
            break;
        }
        printf("sendto msg :%s\n",buffer);
        bzero(buffer,sizeof(buffer));
        if(recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)addr,&len) <= 0)
        {
            perror("recv msg error");
            break;
        }
        printf("recvfrom msg :%s\n",buffer);
        ret = 1;
    }while(0);
    return ret;
}

               

int main(int argc,char *argv[])
{
    int ret = 0;
    do
    {
        if(argc < 3)
        {
            perror("argc error");
            break;
        }
        char *ip = argv[1];
        int port = atol(argv[2]);
        int fd = socket(AF_INET,SOCK_DGRAM,0);
        if(fd < 0)
        {
            perror("socket error");
            break;
        }
        //客户端不需要绑定端口
        struct sockaddr_in addr;
        bzero(&addr,sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET,ip,&addr.sin_addr.s_addr);

#if 0
        if(bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
        {
            perror("bind error");
            break;
        }
#endif
        int time = 1;
        ret = 1;
        while(ret)
        {
            ret = do_client(fd,time,&addr);
            ++time;
        }
        close(fd);
    }while(0);
    return ret;
}

