#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
using namespace std;

sem_t sem;

void* aFun(void *arg)
{
    unsigned int cnt = 1;
    while(true)
    {
        sem_wait(&sem);
        std::cout << "running a thread :" << cnt << std::endl;
        cnt += 1;
        sem_post(&sem);
        usleep(100);
    }
    return NULL;
}

void* bFun(void *arg)
{
    unsigned int cnt = 1;
    while(true)
    {
        sem_wait(&sem);
        std::cout << "running b thread:" << cnt << std::endl;
        cnt += 1;
        sem_post(&sem);
        usleep(100);
    }
    return NULL;
}

int main(void)
{
    sem_init(&sem,0,1);
    pthread_t a,b;
    if(pthread_create(&a,NULL,aFun,NULL))
    {
        return 0;
    }
    if(pthread_create(&b,NULL,bFun,NULL))
    {
        return 0;
    }
    pthread_join(a,NULL);
    pthread_join(b,NULL);
    sem_destroy(&sem);
    return 0;
}

