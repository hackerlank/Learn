#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{
    int fd = open("text.pipe",O_RDONLY);
    if(fd < 0)
    {
        perror("open pipe error");
    }
    char buffer[1000];
    bzero(buffer,sizeof(buffer));
    if(read(fd,&buffer,sizeof(buffer)) < 0)
    {
        perror("read pipe error");
    }
    printf("read content :%s\n",buffer);
    return 0;
}


