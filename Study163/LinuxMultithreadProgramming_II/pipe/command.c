#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *cmd1[] = {"/bin/cat","/etc/passwd",NULL};
char *cmd2[] = {"/bin/grep","root",NULL};

int main(void)
{
    int fd[2];
    bzero(fd,sizeof(fd));
    int cnt = 0;
    for(;cnt < 2;++cnt)
    {
        pid_t pid = fork();
        if(pid < 0)
        {
            perror("fork error");
        }
        else if(pid == 0)
        {
            //第一个子进程
            if(cnt == 0)
            {
                close(fd[0]);
                //把stdout重定向到fd[1]
                if(dup2(fd[1],STDOUT_FILENO) != STDOUT_FILENO)
                {
                    perror("dup2 stdin error");
                }
                //执行cat /etc/passwd 命令
                if(execvp(cmd1[0],cmd1) < 0)
                {
                    perror("execvp error");
                }
                close(fd[1]);
                break;
            }
            //第二个子进程
            if(cnt == 1)
            {
                close(fd[1]);
                //把stdin重定向到fd[0]
                if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO)
                {
                    perror("dup2 stdin error");
                }
                //执行grep root 命令
                if(execvp(cmd2[0],cmd2) < 0)
                {
                    perror("execvp error");
                }
                break;
            }
        }
        else
        {
            if(cnt == 1)
            {
                close(fd[0]);
                close(fd[1]);
                wait(NULL);
                wait(NULL);
            }
        }
    }
    return 0;
}
