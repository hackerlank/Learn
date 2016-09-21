#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    if(mkfifo("text.pipe",0777) < 0)
    {
        perror("mkfifo error");
    }
    int fd = open("text.pipe",O_WRONLY);
    if(fd < 0)
    {
        perror("fopen pipe error");
    }
    char buffer[100];
    bzero(buffer,sizeof(buffer));
    strncpy(buffer,"123456",sizeof(buffer));
    if(write(fd,buffer,sizeof(buffer)) < 0)
    {
        perror("write data error");
    }
    close(fd);
    return 0;
}

