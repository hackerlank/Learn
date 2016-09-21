#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

typedef struct Arg
{
    int begin;
    int end;
    Arg(const int begin = 0,const int end = 10) : begin(begin),end(end)
    {
    }
}Arg;

int main(void)
{
    int fd[2];
    bzero(fd,sizeof(fd));
    if(pipe(fd))
    {
        std::cout << "pipe error" << std::endl;
    }
    pid_t pid = fork();
    if(pid < 0)
    {
        std::cout << "fore error" << std::endl;
    }
    else if(pid > 0)
    {
        close(fd[0]);
        Arg arg(10,100);
        if(write(fd[1],&arg,sizeof(arg)) != sizeof(arg))
        {
            std::cout << "father pid write error" << std::endl;
        }
        std::cout << "write arg(" << arg.begin << "," << arg.end << ")" << std::endl;
        //父进程先运行,之后等待子进程运行结束
        wait(NULL);
        std::cout << "wait children pid ending ..." << std::endl;
    }
    else
    {
        close(fd[1]);
        Arg arg(0,0);
        if(read(fd[0],&arg,sizeof(arg)) != sizeof(arg))
        {
            std::cout << "children pid read error" << std::endl;
        }
        std::cout << "read arg(" << arg.begin << "," << arg.end << ")" << std::endl;
    }
    return 0;
}

    



