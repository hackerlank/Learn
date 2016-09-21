#include "head.h"

static int fd[2];

int initPipe()
{
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("create pipe error");
    }
    return ret;
}

void waitPipe()
{
    int ret = 0;
    if(read(fd[0],&ret,sizeof(ret)) < 0)
    {
        perror("read pipe error");
    }
}

void notifyPipe()
{
    int ret = 1;
    if(write(fd[1],&ret,sizeof(ret)) < 0)
    {
        perror("write pipe error");
    }
}

void destroyPipe()
{
    close(fd[0]);
    close(fd[1]);
}
