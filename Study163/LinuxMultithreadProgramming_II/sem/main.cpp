#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

using namespace std;
sem_t sem1,sem2;

void* aFun(void *arg)
{
    sem_wait(&sem1);
    std::cout << "runing a thread" << std::endl;
    return NULL;
}

void* bFun(void *arg)
{
    sem_wait(&sem2);
    std::cout << "runing b thread" << std::endl;
    sem_post(&sem1);
    return NULL;
}

void* cFun(void *arg)
{
    std::cout << "runing c thread" << std::endl;
    sem_post(&sem2);
    return NULL;
}


int main()
{
    sem_init(&sem1,0,0);
    sem_init(&sem2,0,0);
    pthread_t a,b,c;
    if(pthread_create(&a,NULL,aFun,NULL))
    {
        return 0;
    }
    if(pthread_create(&b,NULL,bFun,NULL))
    {
        return 0;
    }
    if(pthread_create(&c,NULL,cFun,NULL))
    {
        return 0;
    }
    pthread_join(a,NULL);
    pthread_join(b,NULL);
    pthread_join(c,NULL);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}
