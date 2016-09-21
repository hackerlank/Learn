#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd1[2],fd2[2];
    bzero(fd1,sizeof(fd1));
    bzero(fd2,sizeof(fd2));
    if(pipe(fd1) < 0)
    {
        perror("pipe error");
    }
    if(pipe(fd2) < 0)
    {
        perror("pipe error");
    }
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork error");
    }
    else if(pid == 0) //children pid
    {
        close(fd1[1]);
        close(fd2[0]);
        if(dup2(fd1[0],STDIN_FILENO) != STDIN_FILENO)
        {
            perror("dup2 fd1 error");
        }
        if(dup2(fd2[1],STDOUT_FILENO) != STDOUT_FILENO)
        {
            perror("dup2 fd2 error");
        }
        if(execlp("bin/add","bin/add",NULL) < 0)
        {
            perror("excelp error");
        }
        close(fd1[0]);
        close(fd2[1]);
    }
    else
    {
        close(fd1[0]);
        close(fd2[1]);
        int x = 1,y = 2,ret = 0;
        //read 和 water 函数会阻塞,一直到读取或者写入数据
        if(write(fd1[1],&x,sizeof(x)) != sizeof(x))
        {
            perror("write fd1 error");
        }
        if(write(fd1[1],&y,sizeof(y)) != sizeof(y))
        {
            perror("write fd1 error");
        }
        if(read(fd2[0],&ret,sizeof(ret)) != sizeof(ret))
        {
            perror("read fd2 error");
        }
        printf("the result is : %d\n",ret);
        wait(NULL);
        close(fd1[1]);
        close(fd2[0]);
    }
    return 0;
}
