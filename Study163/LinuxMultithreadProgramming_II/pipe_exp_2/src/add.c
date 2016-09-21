#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int x,y;
    if(read(STDIN_FILENO,&x,sizeof(x)) != sizeof(x))
    {
        perror("read from stdin error");
    }
    if(read(STDIN_FILENO,&y,sizeof(y)) != sizeof(y))
    {
        perror("read from stdin error");
    }
    int ret = x + y;
    if(write(STDOUT_FILENO,&ret,sizeof(ret)) != sizeof(ret))
    {
        perror("write to stdout error");
    }
    return 0;
}
