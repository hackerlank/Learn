#include <iostream>
#include <pthread.h>
#include "head.h"

pthread_mutex_t mutex;
pthread_rwlock_t rwlock;
void* fun(void *arg)
{
    int *val = (int*)(arg);
    std::cout << "begin:" << pthread_self() << "," << *val << std::endl;
    pthread_mutex_lock(&mutex);
    *val += 1;
    pthread_mutex_unlock(&mutex);
    std::cout << "end:" << pthread_self() << "," << *val << std::endl;
    return NULL;
}

using namespace std;

int main(void)
{
    int arg = 10;
    pthread_mutex_init(&mutex,NULL);
    pthread_rwlock_init(&rwlock,NULL);
    pthread_t tid1,tid2;
    if(pthread_create(&tid1,NULL,fun,(void*)(&arg)))
    {
        return 0;
    }
    if(pthread_create(&tid2,NULL,fun,(void*)(&arg)))
    {
        return 0;
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_rwlock_wrlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);
    return 0;
}
