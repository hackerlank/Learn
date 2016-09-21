#include "head.h"
#include <sys/shm.h>

int main(void)
{
    int ret = 0;
    do
    {
        if(initPipe() < 0)
        {
            break;
        }
        int shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT | IPC_EXCL | 0777);
        if(shmid < 0)
        {
            perror("shmget error");
            break;
        }
        pid_t pid = fork();
        if(pid < 0)
        {
            perror("fork error");
            break;
        }
        else if(pid == 0)
        {
            waitPipe();
            void *ptr = shmat(shmid,NULL,0);
            int *begin = (int*)ptr;
            printf("read the share memory:%d,%d\n",*begin,*(begin+1));
            shmdt(ptr);
            destroyPipe();
        }
        else
        {
            //获得共享内存指针
            void *ptr = shmat(shmid,NULL,0);
            int *begin = (int*)ptr;
            if(*begin == -1)
            {
                perror("shmat error");
                break;
            }
            *begin = 100;
            *(begin+1) = 200;
            //通知子进程已经有数据写入共享内存数据
            notifyPipe();
            //关闭共享内存
            shmdt(ptr);
            //关闭管道
            destroyPipe();
            //等待子进程结束
            wait(0);
            //删除此共享内存(需要手动)
            shmctl(shmid,IPC_RMID,NULL);
        }
    }while(0);
    return ret;
}
