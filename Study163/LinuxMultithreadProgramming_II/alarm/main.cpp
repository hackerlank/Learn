#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
using namespace std;

void signal_handler(int signo)
{
    std::cout << "accept the signal :" << signo << std::endl;
    if(signo == SIGALRM)
    {
        std::cout << "time out ..." << pthread_self() << std::endl;
    }
    alarm(2);
    return;
}

void* fun(void *arg)
{
    if(signal(SIGALRM,signal_handler) == SIG_ERR)
    {
        std::cout << "signal sigalrm error" << std::endl;
    }
    alarm(2);
    for(int cnt = 0;cnt < 100;++cnt)
    {
        std::cout << "child run:" << cnt << std::endl;
        sleep(1);
    }
    return NULL;
}

void* cancel(void *arg)
{
#if 0
    pthread_t *tid = (pthread_t*)arg;
    pthread_cancel(*tid);
    //如果不取消,后面会一直触发
    alarm(0);
#endif
    for(int cnt = 0;cnt < 100;++cnt)
    {
        std::cout << "cancel run:" << cnt << std::endl;
        sleep(1);
        if(cnt == 5)
        {
            pthread_t *tid = (pthread_t*)arg;
            pthread_cancel(*tid);
            //alarm(0);
        }
    }
    return NULL;
}


int main()
{
#if 0
    //放这里,主线程和子线程都会屏蔽此信号
    sigset_t sigSet;
    sigemptyset(&sigSet);
    sigaddset(&sigSet,SIGALRM);
    pthread_sigmask(SIG_SETMASK,&sigSet,NULL);
#endif
    pthread_t pth,pth1;
    if(pthread_create(&pth,NULL,fun,NULL))
    {
        return 0;
    }
#if 1
    if(pthread_create(&pth1,NULL,cancel,(void*)&pth))
    {
        return 0;
    }
#endif
#if 0
    //放这里,主线程会屏蔽此信号,但是子线程会捕捉
    sigset_t sigSet;
    sigemptyset(&sigSet);
    sigaddset(&sigSet,SIGALRM);
    pthread_sigmask(SIG_SETMASK,&sigSet,NULL);
#endif
    while(true)
    {
        std::cout << "main thread running..." << pthread_self() << std::endl;
        sleep(10);
    }
    pthread_join(pth,NULL);
    pthread_join(pth1,NULL);
    return 0;
}
