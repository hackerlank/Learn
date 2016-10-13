#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

void doRead(const int fd)
{
    do
    {
        char buffer[100];
        bzero(buffer,sizeof(buffer));
        if(read(fd,buffer,sizeof(buffer)) < 0)
        {
            perror("read error");
            break;
        }
        printf("read message:%s",buffer);
    }while(0);
    
}

int main(int argc,char *argv[])
{
    int flag = 0;
    do
    {
        if(argc < 3)
        {
            perror("client error");
            break;
        }
        char *ip = argv[1];
        int port = atol(argv[2]);
        int fd = socket(AF_INET,SOCK_STREAM,0);
        if(fd < 0)
        {
            perror("socket error");
            break;
        }
        struct sockaddr_in addr;
        bzero(&addr,sizeof(addr));

        addr.sin_family = AF_INET;
        addr.sin_port = ntohs(port);
        inet_pton(fd,ip,addr.sin_addr.s_addr,sizeof(addr.sin_addr.s_addr));
        if(connect(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
        {
            perror("connect error");
            break;
        }
        doRead(fd);
        close(fd);
        flag = 1;
    }while(0);
    return flag;
}
        
